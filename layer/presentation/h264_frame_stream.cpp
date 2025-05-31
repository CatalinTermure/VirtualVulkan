#include "h264_frame_stream.h"

#include <fstream>

#include "commons/remote_call.h"
#include "layer/context/device.h"
#include "layer/context/instance.h"
#include "layer/context/swapchain.h"
#include "layer/sempahore_handle.h"
#include "spdlog/spdlog.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/hwcontext.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
}

namespace vvk {

namespace {
int read_buffer(void *opaque, uint8_t *buf, int buf_size) {
  H264FrameStream::SwapchainPresentationInfo *swapchain_present_info =
      static_cast<H264FrameStream::SwapchainPresentationInfo *>(opaque);
  if (swapchain_present_info->decode_buffer.empty()) {
    return AVERROR_EOF;
  }
  size_t bytes_to_copy = std::min(static_cast<size_t>(buf_size), swapchain_present_info->decode_buffer.size());
  std::memcpy(buf, swapchain_present_info->decode_buffer.data(), bytes_to_copy);
  swapchain_present_info->decode_buffer.erase(0, bytes_to_copy);
  return static_cast<int>(bytes_to_copy);
}
constexpr int kBufferSize = 4096;
constexpr AVHWDeviceType kHwDeviceType = AV_HWDEVICE_TYPE_VAAPI;
}  // namespace

H264FrameStream::H264FrameStream(VkInstance instance, VkDevice device, uint32_t graphics_queue_family_index,
                                 uint32_t video_queue_family_index)
    : local_instance_(instance),
      local_device_(device),
      remote_video_queue_family_index_(video_queue_family_index),
      remote_graphics_queue_family_index_(graphics_queue_family_index) {
  InstanceInfo &instance_info = GetInstanceInfo(local_instance_);
  VkSemaphoreCreateInfo sempahore_create_info = {};
  sempahore_create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
  VkResult result =
      PackAndCallVkCreateSemaphore(instance_info.command_stream(), instance_info.GetRemoteHandle(local_device_),
                                   &sempahore_create_info, nullptr, &remote_encode_wait_semaphore_);
  if (result != VK_SUCCESS) {
    throw std::runtime_error("Failed to create remote encode wait semaphore");
  }
}

H264FrameStream::~H264FrameStream() {
  if (remote_encode_wait_semaphore_ != VK_NULL_HANDLE) {
    InstanceInfo &instance_info = GetInstanceInfo(local_instance_);
    PackAndCallVkDestroySemaphore(instance_info.command_stream(), instance_info.GetRemoteHandle(local_device_),
                                  remote_encode_wait_semaphore_, nullptr);
    remote_encode_wait_semaphore_ = VK_NULL_HANDLE;
  }
}

void H264FrameStream::AssociateSwapchain(VkSwapchainKHR swapchain, const VkExtent2D &swapchain_image_extent) {
  InstanceInfo &instance_info = GetInstanceInfo(local_instance_);
  SwapchainInfo &swapchain_info = GetSwapchainInfo(swapchain);
  vvk::server::VvkRequest request;
  request.set_method("setupPresentation");
  vvk::server::VvkSetupPresentationRequest &setup_presentation = *request.mutable_setuppresentation();
  setup_presentation.set_instance(reinterpret_cast<uint64_t>(instance_info.GetRemoteHandle(local_instance_)));
  setup_presentation.set_device(reinterpret_cast<uint64_t>(instance_info.GetRemoteHandle(local_device_)));
  for (auto &[remote_image, _] : swapchain_info.GetRemoteImages()) {
    setup_presentation.add_remote_images(reinterpret_cast<uint64_t>(remote_image));
  }
  setup_presentation.set_width(swapchain_image_extent.width);
  setup_presentation.set_height(swapchain_image_extent.height);
  vvk::server::H264StreamCreateInfo &h264_stream_create_info = *setup_presentation.mutable_h264_stream_create_info();
  h264_stream_create_info.set_video_queue_family_index(remote_video_queue_family_index_);
  h264_stream_create_info.set_compute_queue_family_index(remote_graphics_queue_family_index_);
  h264_stream_create_info.set_remote_images_format(
      static_cast<vvk::server::VkFormat>(swapchain_info.GetRemoteImageFormat()));
  h264_stream_create_info.set_encode_wait_semaphore(reinterpret_cast<uint64_t>(remote_encode_wait_semaphore_));
  if (!instance_info.command_stream().Write(request)) {
    throw std::runtime_error("Failed to send setup presentation request");
  }

  vvk::server::VvkResponse response;
  if (!instance_info.command_stream().Read(&response)) {
    throw std::runtime_error("Failed to read setup presentation response");
  }

  std::string encoded_header = response.setuppresentation().h264_stream_info().header();
  VkExtent2D remote_images_size = {
      .width = response.setuppresentation().h264_stream_info().remote_images_size().width(),
      .height = response.setuppresentation().h264_stream_info().remote_images_size().height(),
  };
  spdlog::info("Received H264 stream header of size {} bytes", encoded_header.size());
  spdlog::info("H264 stream header: {}", encoded_header);
  std::vector<uint64_t> remote_frame_keys;
  remote_frame_keys.reserve(response.setuppresentation().frame_keys_size());
  for (int i = 0; i < response.setuppresentation().frame_keys_size(); i++) {
    remote_frame_keys.push_back(response.setuppresentation().frame_keys(i));
  }
  swapchains_.push_back(SwapchainPresentationInfo{
      .swapchain = swapchain,
      .remote_session_key = response.setuppresentation().session_key(),
      .remote_frame_keys = remote_frame_keys,
      .image_extent = swapchain_image_extent,
      .decode_buffer = std::move(encoded_header),
      .decode_info = std::nullopt,
      .copy_context = MemoryToImageCopyContext(
          local_device_, swapchain_info.GetLocalSwapchainImages(), swapchain_image_extent,
          BufferLayout{.offset = 0, .row_length = remote_images_size.width, .image_height = remote_images_size.height},
          false, true)});
}

void H264FrameStream::RemoveSwapchain(VkSwapchainKHR swapchain) {
  swapchains_.erase(std::remove_if(swapchains_.begin(), swapchains_.end(),
                                   [swapchain](const SwapchainPresentationInfo &swapchain_present_info) {
                                     return swapchain_present_info.swapchain == swapchain;
                                   }),
                    swapchains_.end());
}

// Called during command buffer recording for a presentable frame.
void H264FrameStream::SetupFrame(VkCommandBuffer remote_command_buffer, uint32_t swapchain_image_index) {
  InstanceInfo &instance_info = GetInstanceInfo(local_instance_);
  DeviceInfo &device_info = GetDeviceInfo(local_device_);
  device_info.additional_semaphores[remote_command_buffer] = remote_encode_wait_semaphore_;
  for (auto &swapchain_present_info : swapchains_) {
    vvk::server::VvkRequest request;
    request.set_method("setupFrame");
    auto *setup_frame = request.mutable_setupframe();
    setup_frame->set_session_key(swapchain_present_info.remote_session_key);
    setup_frame->set_frame_key(swapchain_present_info.remote_frame_keys[swapchain_image_index]);
    setup_frame->set_command_buffer(reinterpret_cast<uint64_t>(remote_command_buffer));
    google::protobuf::Empty response;
    grpc::ClientContext context;
    instance_info.command_stream().Write(request);
  }
}

// Called when a frame should be presented.
VkResult H264FrameStream::PresentFrame(VkQueue queue, const VkPresentInfoKHR &original_present_info) {
  InstanceInfo &instance_info = GetInstanceInfo(local_instance_);

  std::vector<VkSemaphore> remote_wait_semaphores;
  std::vector<VkSemaphore> local_wait_semaphores;
  local_wait_semaphores.reserve(original_present_info.waitSemaphoreCount + original_present_info.swapchainCount);

  for (uint32_t i = 0; i < original_present_info.waitSemaphoreCount; i++) {
    VkSemaphore semaphore = original_present_info.pWaitSemaphores[i];
    if (semaphore->state == SemaphoreState::kToBeSignaledRemote) {
      remote_wait_semaphores.push_back(semaphore);
      semaphore->state = SemaphoreState::kUnsignaled;
    } else if (semaphore->state == SemaphoreState::kToBeSignaledLocal) {
      local_wait_semaphores.push_back(semaphore->local_handle);
      semaphore->state = SemaphoreState::kUnsignaled;
    } else {
      throw std::runtime_error(
          std::format("Invalid semaphore state in QueuePresentKHR for semaphore: {}", (void *)semaphore));
    }
  }

  for (int i = 0; i < original_present_info.swapchainCount; i++) {
    auto swapchain_present_info =
        std::find_if(swapchains_.begin(), swapchains_.end(),
                     [swapchain = original_present_info.pSwapchains[i]](const SwapchainPresentationInfo &info) {
                       return info.swapchain == swapchain;
                     });
    if (swapchain_present_info == swapchains_.end()) {
      spdlog::warn("Swapchain not found in H264FrameStream for presentation");
      continue;
    }

    vvk::server::VvkGetFrameRequest request;
    request.set_session_key(swapchain_present_info->remote_session_key);
    request.set_frame_key(swapchain_present_info->remote_frame_keys[original_present_info.pImageIndices[i]]);
    request.set_stream_type(vvk::server::VvkStreamType::VVK_STREAM_TYPE_H264);
    vvk::server::VvkGetFrameResponse response;
    grpc::ClientContext context;
    auto reader = instance_info.stub().RequestFrame(&context, request);
    if (!reader->Read(&response)) {
      throw std::runtime_error("Failed to read frame response from server");
    }
    swapchain_present_info->decode_buffer += std::move(*response.mutable_frame_data());
    if (!swapchain_present_info->decode_info.has_value()) {
      swapchain_present_info->decode_info = DecodeInfo{};
      DecodeInfo &decode_info = swapchain_present_info->decode_info.value();
      decode_info.aux_buffer = static_cast<unsigned char *>(av_malloc(kBufferSize));
      AVFormatContext *format_context = nullptr;
      const AVCodec *decoder = nullptr;
      AVCodecContext *decoder_context = nullptr;
      AVPixelFormat hw_format;
      AVStream *video = nullptr;
      AVBufferRef *hw_device_ctx = nullptr;
      format_context = avformat_alloc_context();
      if (!format_context) {
        throw std::runtime_error("Failed to allocate AVFormatContext");
      }
      format_context->pb = avio_alloc_context(decode_info.aux_buffer, kBufferSize, 0, &*swapchain_present_info,
                                              read_buffer, nullptr, nullptr);
      if (!format_context->pb) {
        throw std::runtime_error("Failed to allocate AVIOContext");
      }
      int ret = avformat_open_input(&format_context, nullptr, nullptr, nullptr);
      if (ret < 0) {
        throw std::runtime_error("Failed to open input for AVFormatContext");
      }
      if (avformat_find_stream_info(format_context, nullptr) < 0) {
        throw std::runtime_error("Failed to find stream info for AVFormatContext");
      }
      int best_stream_index = av_find_best_stream(format_context, AVMEDIA_TYPE_VIDEO, -1, -1, &decoder, 0);
      if (best_stream_index < 0) {
        throw std::runtime_error("Failed to find best video stream in AVFormatContext");
      }
      for (int i = 0;; i++) {
        const AVCodecHWConfig *config = avcodec_get_hw_config(decoder, i);
        if (!config) {
          throw std::runtime_error("No hardware codec configuration found for decoder");
        }
        if (config->methods & AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX && config->device_type == kHwDeviceType) {
          hw_format = config->pix_fmt;
          break;
        }
      }
      decoder_context = avcodec_alloc_context3(decoder);
      if (!decoder_context) {
        throw std::runtime_error("Failed to allocate AVCodecContext");
      }
      video = format_context->streams[best_stream_index];
      ret = avcodec_parameters_to_context(decoder_context, video->codecpar);
      if (ret < 0) {
        throw std::runtime_error("Failed to copy codec parameters to AVCodecContext");
      }
      decoder_context->opaque = reinterpret_cast<void *>(hw_format);
      decoder_context->get_format = [](AVCodecContext *ctx, const enum AVPixelFormat *pix_fmts) {
        for (int i = 0; pix_fmts[i] != AV_PIX_FMT_NONE; i++) {
          if (pix_fmts[i] == static_cast<AVPixelFormat>(reinterpret_cast<uintptr_t>(ctx->opaque))) {
            return pix_fmts[i];
          }
        }
        spdlog::error("No suitable pixel format found for decoder");
        return AV_PIX_FMT_NONE;
      };
      av_opt_set_int(decoder_context, "refcounted_frames", 1, 0);
      ret = av_hwdevice_ctx_create(&hw_device_ctx, kHwDeviceType, "/dev/dri/renderD129", nullptr, 0);
      if (ret < 0) {
        throw std::runtime_error("Failed to create hardware device context");
      }
      decoder_context->hw_device_ctx = av_buffer_ref(hw_device_ctx);
      ret = avcodec_open2(decoder_context, decoder, nullptr);
      if (ret < 0) {
        throw std::runtime_error("Failed to open codec for AVCodecContext");
      }

      decode_info.format_context = format_context;
      decode_info.decoder = decoder;
      decode_info.decoder_context = decoder_context;
      decode_info.hw_format = hw_format;
      decode_info.video = video;
      decode_info.hw_device_ctx = hw_device_ctx;
    }
    DecodeInfo &decode_info = swapchain_present_info->decode_info.value();
    AVPacket packet;
    int ret = av_read_frame(decode_info.format_context, &packet);
    if (ret < 0) {
      if (ret == AVERROR_EOF) {
        spdlog::info("End of stream reached for H264 frame");
      } else {
        throw std::runtime_error("Failed to read frame from AVFormatContext");
      }
    }
    AVFrame *frame = av_frame_alloc();
    if (!frame) {
      throw std::runtime_error("Failed to allocate AVFrame");
    }
    ret = avcodec_send_packet(decode_info.decoder_context, &packet);
    if (ret < 0) {
      throw std::runtime_error("Failed to send packet to decoder");
    }
    ret = avcodec_receive_frame(decode_info.decoder_context, frame);
    if (ret < 0) {
      if (ret == AVERROR(EAGAIN)) {
        spdlog::info("Decoder needs more input data");
      } else if (ret == AVERROR_EOF) {
        spdlog::info("End of stream reached for H264 frame");
      } else {
        throw std::runtime_error("Failed to receive frame from decoder");
      }
    } else {
      spdlog::info("Decoded frame successfully");
      AVFrame *sw_frame = av_frame_alloc();
      if (!sw_frame) {
        throw std::runtime_error("Failed to allocate AVFrame for hw to sw transfer");
      }
      sw_frame->format = AV_PIX_FMT_BGRA;
      ret = av_hwframe_transfer_data(sw_frame, frame, 0);
      if (ret < 0) {
        throw std::runtime_error("Failed to transfer frame from hardware to software");
      }
      int size =
          av_image_get_buffer_size(static_cast<AVPixelFormat>(sw_frame->format), sw_frame->width, sw_frame->height, 1);
      if (size < 0) {
        char buf[4096];
        av_strerror(size, buf, 4096);
        throw std::runtime_error(std::format("Failed to get buffer size for decoded frame {}", (char *)buf));
      }
      uint8_t *buffer = static_cast<uint8_t *>(av_malloc(size));
      if (!buffer) {
        throw std::runtime_error("Failed to allocate buffer for decoded frame");
      }
      ret = av_image_copy_to_buffer(buffer, size, static_cast<const uint8_t *const *>(sw_frame->data),
                                    static_cast<const int *>(sw_frame->linesize),
                                    static_cast<AVPixelFormat>(sw_frame->format), sw_frame->width, sw_frame->height, 1);
      if (ret < 0) {
        throw std::runtime_error("Failed to copy image data to buffer");
      }
      spdlog::info("Decoded frame size: {} bytes", size);
      av_frame_free(&frame);

      swapchain_present_info->copy_context.CopyMemoryToImage(
          original_present_info.pImageIndices[i], std::string_view(reinterpret_cast<const char *>(buffer), size));
      local_wait_semaphores.push_back(*swapchain_present_info->copy_context.GetSemaphoreToSignal());
    }
  }

  DeviceInfo &device_info = GetDeviceInfo(local_device_);

  for (auto &remote_semaphore : remote_wait_semaphores) {
    remote_semaphore->remote_to_local_semaphore.acquire();
    // Unsignal the semaphore on the remote side
    {
      VkPipelineStageFlags wait_dst_stage_mask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
      VkSubmitInfo submit = {
          .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
          .pNext = nullptr,
          .waitSemaphoreCount = 1,
          .pWaitSemaphores = &remote_semaphore->remote_handle,
          .pWaitDstStageMask = &wait_dst_stage_mask,
          .commandBufferCount = 0,
          .pCommandBuffers = nullptr,
          .signalSemaphoreCount = 0,
          .pSignalSemaphores = nullptr,
      };
      PackAndCallVkQueueSubmit(instance_info.command_stream(), device_info.GetRemoteHandle(queue), 1, &submit, nullptr);
    }
  }

  VkPresentInfoKHR present_info = original_present_info;
  present_info.waitSemaphoreCount = local_wait_semaphores.size();
  present_info.pWaitSemaphores = local_wait_semaphores.data();

  device_info.dispatch_table().QueuePresentKHR(*device_info.present_queue(), &present_info);
  for (uint32_t i = 0; i < original_present_info.swapchainCount; i++) {
    GetSwapchainInfo(original_present_info.pSwapchains[i]).SetImageReleased();
    spdlog::info("Released image {} for swapchain {}", original_present_info.pImageIndices[i],
                 (void *)original_present_info.pSwapchains[i]);
  }

  return VK_SUCCESS;
}
}  // namespace vvk
