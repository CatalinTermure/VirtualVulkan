#include "h264_frame_stream.h"

#include "layer/context/instance.h"
#include "layer/context/swapchain.h"
#include "spdlog/spdlog.h"

namespace vvk {
H264FrameStream::H264FrameStream(VkInstance instance, VkDevice device, uint32_t graphics_queue_family_index,
                                 uint32_t video_queue_family_index)
    : local_instance_(instance),
      local_device_(device),
      remote_video_queue_family_index_(video_queue_family_index),
      remote_graphics_queue_family_index_(graphics_queue_family_index) {}

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
  if (!instance_info.command_stream().Write(request)) {
    throw std::runtime_error("Failed to send setup presentation request");
  }

  vvk::server::VvkResponse response;
  if (!instance_info.command_stream().Read(&response)) {
    throw std::runtime_error("Failed to read setup presentation response");
  }

  std::string encoded_header = response.setuppresentation().h264_stream_info().header();
  spdlog::info("Received H264 stream header of size {} bytes", encoded_header.size());
  spdlog::info("H264 stream header: {}", encoded_header);
  std::vector<uint64_t> remote_frame_keys;
  remote_frame_keys.reserve(response.setuppresentation().frame_keys_size());
  for (int i = 0; i < response.setuppresentation().frame_keys_size(); i++) {
    remote_frame_keys.push_back(response.setuppresentation().frame_keys(i));
  }
  swapchains_.push_back(SwapchainPresentationInfo{.swapchain = swapchain,
                                                  .remote_session_key = response.setuppresentation().session_key(),
                                                  .remote_frame_keys = remote_frame_keys,
                                                  .image_extent = swapchain_image_extent});
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
    vvk::server::VvkGetFrameResponse response;
    grpc::ClientContext context;
    auto reader = instance_info.stub().RequestFrame(&context, request);
    if (!reader->Read(&response)) {
      throw std::runtime_error("Failed to read frame response from server");
    }
    spdlog::info("Received response data with size {} bytes", response.frame_data().size());
  }

  return VK_SUCCESS;
}
}  // namespace vvk
