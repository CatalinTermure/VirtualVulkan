#ifndef VVK_SERVER_H264_ENCODER_H
#define VVK_SERVER_H264_ENCODER_H

#include <vulkan/vulkan.h>

#include <cstddef>
#include <vector>
#include <vulkan/vulkan.hpp>

#include "server/encoder.h"
#include "server/execution_context.h"

namespace vvk {

class H264Encoder : public Encoder {
 public:
  H264Encoder(const vvk::ExecutionContext& execution_context, VkDevice device, uint32_t video_queue_index,
              vk::Extent2D image_extent)
      : execution_context_(execution_context),
        dev_dispatch_(execution_context.device_dispatch_table()),
        device_(device),
        video_queue_index_(video_queue_index),
        image_extent_(image_extent) {
    InitializeVideoProfile();
    CreateQueryPool();
    AllocateCommandBuffer();
    InitializeVideoSession();
    InitializeRateControl();
  }

  ~H264Encoder() override {
    if (video_session_ != VK_NULL_HANDLE) {
      dev_dispatch_.DestroyVideoSessionKHR(device_, video_session_, nullptr);
      video_session_ = VK_NULL_HANDLE;
    }
    if (command_buffer_ != VK_NULL_HANDLE) {
      dev_dispatch_.FreeCommandBuffers(device_, command_pool_, 1, &command_buffer_);
      command_buffer_ = VK_NULL_HANDLE;
    }
    if (command_pool_ != VK_NULL_HANDLE) {
      dev_dispatch_.DestroyCommandPool(device_, command_pool_, nullptr);
      command_pool_ = VK_NULL_HANDLE;
    }
    if (query_pool_ != VK_NULL_HANDLE) {
      dev_dispatch_.DestroyQueryPool(device_, query_pool_, nullptr);
      query_pool_ = VK_NULL_HANDLE;
    }
  }

  void WriteEncodeCommands(VkCommandBuffer command_buffer, VkImage image) override {
    dev_dispatch_.ResetQueryPool(device_, query_pool_, 0, 1);

    bool is_idr_frame = encoded_frame_count_ % kIdrPeriod == 0;

    std::vector<vk::VideoReferenceSlotInfoKHR> reference_slots;

    vk::VideoBeginCodingInfoKHR video_begin_coding_info = {vk::VideoBeginCodingFlagsKHR{}, video_session_,
                                                           vk::VideoSessionParametersKHR{}, reference_slots,
                                                           encode_rate_control_info_};

    dev_dispatch_.CmdBeginVideoCodingKHR(command_buffer, video_begin_coding_info);
  }

  std::vector<std::byte> GetEncodedData(VkImage image) override { return {}; }

  const vvk::ExecutionContext& execution_context_;
  const VkuDeviceDispatchTable& dev_dispatch_;
  VkDevice device_;
  uint32_t video_queue_index_;
  uint32_t encoded_frame_count_ = 0;
  vk::Extent2D image_extent_;
  vk::VideoEncodeRateControlInfoKHR encode_rate_control_info_;
  vk::VideoEncodeH264RateControlInfoKHR h264_rate_control_info_;
  vk::VideoEncodeRateControlLayerInfoKHR encode_rate_control_layer_info_;
  vk::VideoEncodeH264RateControlLayerInfoKHR h264_rate_control_layer_info_;
  vk::VideoProfileListInfoKHR video_profile_list_info_;
  vk::VideoProfileInfoKHR video_profile_info_;
  vk::VideoEncodeH264ProfileInfoKHR h264_profile_info_;

  VkQueryPool query_pool_ = VK_NULL_HANDLE;
  VkCommandPool command_pool_ = VK_NULL_HANDLE;
  VkCommandBuffer command_buffer_ = VK_NULL_HANDLE;
  VkVideoSessionKHR video_session_ = VK_NULL_HANDLE;

 private:
  void CreateQueryPool() {
    vk::QueryPoolVideoEncodeFeedbackCreateInfoKHR query_pool_video_encode_feedback_create_info = {
        vk::VideoEncodeFeedbackFlagBitsKHR::eBitstreamBufferOffset |
            vk::VideoEncodeFeedbackFlagBitsKHR::eBitstreamBytesWritten,
        video_profile_info_,
    };

    vk::QueryPoolCreateInfo query_pool_create_info = {
        vk::QueryPoolCreateFlags{},
        vk::QueryType::eVideoEncodeFeedbackKHR,
        1,  // Query count
        vk::QueryPipelineStatisticFlags{},
        query_pool_video_encode_feedback_create_info,
    };
    dev_dispatch_.CreateQueryPool(device_, query_pool_create_info, nullptr, &query_pool_);
  }

  void InitializeVideoProfile() {
    h264_profile_info_ = vk::VideoEncodeH264ProfileInfoKHR{
        STD_VIDEO_H264_PROFILE_IDC_BASELINE,
        nullptr,
    };
    video_profile_info_ = vk::VideoProfileInfoKHR{
        vk::VideoCodecOperationFlagBitsKHR::eEncodeH264,
        vk::VideoChromaSubsamplingFlagBitsKHR::e420,
        vk::VideoComponentBitDepthFlagBitsKHR::e8,
        vk::VideoComponentBitDepthFlagBitsKHR::e8,
        h264_profile_info_,
    };
    video_profile_list_info_ = vk::VideoProfileListInfoKHR{video_profile_info_};
  }

  void AllocateCommandBuffer() {
    vk::CommandPoolCreateInfo command_pool_create_info = {
        vk::CommandPoolCreateFlags{},
        video_queue_index_,
    };
    dev_dispatch_.CreateCommandPool(device_, command_pool_create_info, nullptr, &command_pool_);

    vk::CommandBufferAllocateInfo command_buffer_allocate_info = {
        command_pool_,
        vk::CommandBufferLevel::ePrimary,
        1,
    };
    dev_dispatch_.AllocateCommandBuffers(device_, command_buffer_allocate_info, &command_buffer_);
  }

  void InitializeVideoSession() {
    vk::ExtensionProperties h264_std_extension_version;
    strcpy(h264_std_extension_version.extensionName, VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_EXTENSION_NAME);
    h264_std_extension_version.specVersion = VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_SPEC_VERSION;
    dev_dispatch_.CreateVideoSessionKHR(device_,
                                        vk::VideoSessionCreateInfoKHR{
                                            video_queue_index_,
                                            vk::VideoSessionCreateFlagsKHR{},
                                            &video_profile_info_,
                                            vk::Format::eG8B8R82Plane420Unorm,
                                            image_extent_,
                                            vk::Format::eG8B8R82Plane420Unorm,
                                            kMaxDpbSlots,
                                            kMaxActiveReferenceSlots,
                                            &h264_std_extension_version,
                                        },
                                        nullptr, &video_session_);
  }

  void InitializeRateControl() {
    h264_rate_control_layer_info_ = vk::VideoEncodeH264RateControlLayerInfoKHR{
        VK_FALSE,  // no min QP
        {},
        VK_FALSE,  // no max QP
        {},
        VK_FALSE,  // no max frame size
        {},
    };
    encode_rate_control_layer_info_ = vk::VideoEncodeRateControlLayerInfoKHR{
        kAverageBitrate, kMaxBitrate, kFrameRateNumerator, kFrameRateDenominator, h264_rate_control_layer_info_,
    };
    h264_rate_control_info_ = vk::VideoEncodeH264RateControlInfoKHR{
        vk::VideoEncodeH264RateControlFlagBitsKHR::eRegularGop |
            vk::VideoEncodeH264RateControlFlagBitsKHR::eReferencePatternFlat,
        kGopFrameCount,
        kIdrPeriod,
        0,  // No B-frames, since they introduce latency due to re-ordering
        1,  // Temporal layer count
        nullptr,
    };
    encode_rate_control_info_ = vk::VideoEncodeRateControlInfoKHR{
        vk::VideoEncodeRateControlFlagsKHR{},
        vk::VideoEncodeRateControlModeFlagBitsKHR::eVbr,  // should be checked before using
        encode_rate_control_layer_info_,
        kVirtualBufferSizeInMs,
        kInitialVirtualBufferSizeInMs,
        h264_rate_control_info_,
    };

    dev_dispatch_.BeginCommandBuffer(command_buffer_, vk::CommandBufferBeginInfo{});
    dev_dispatch_.CmdBeginVideoCodingKHR(command_buffer_,
                                         vk::VideoBeginCodingInfoKHR{
                                             vk::VideoBeginCodingFlagsKHR{},
                                             video_session_,
                                             {},  // VideoSessionParametersKHR
                                             {},  // Reference slots are not required just to reset the video session
                                         });
    dev_dispatch_.CmdControlVideoCodingKHR(command_buffer_, vk::VideoCodingControlInfoKHR{
                                                                vk::VideoCodingControlFlagBitsKHR::eReset,
                                                                encode_rate_control_info_,
                                                            });
    dev_dispatch_.CmdEndVideoCodingKHR(command_buffer_, vk::VideoEndCodingInfoKHR{});
  }

  constexpr static uint32_t kIdrPeriod = 16;
  constexpr static uint32_t kGopFrameCount = 16;
  constexpr static uint32_t kMaxDpbSlots = 16;
  constexpr static uint32_t kMaxActiveReferenceSlots = 16;
  constexpr static uint32_t kVirtualBufferSizeInMs = 200;
  constexpr static uint32_t kInitialVirtualBufferSizeInMs = 100;
  constexpr static uint32_t kAverageBitrate = 5'000'000;  // 5 Mbps
  constexpr static uint32_t kMaxBitrate = 20'000'000;     // 20 Mbps
  constexpr static uint32_t kFrameRateNumerator = 30;     // 30 fps
  constexpr static uint32_t kFrameRateDenominator = 1;    // 30 fps
};

}  // namespace vvk

#endif  // VVK_SERVER_H264_ENCODER_H
