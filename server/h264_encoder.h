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
  H264Encoder(const vvk::ExecutionContext& execution_context, VkDevice device)
      : execution_context_(execution_context),
        dev_dispatch_(execution_context.device_dispatch_table()),
        device_(device) {
    CreateQueryPool();

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
        vk::VideoEncodeRateControlFlagsKHR{}, {}, {}, kVirtualBufferSizeInMs, kInitialVirtualBufferSizeInMs, nullptr};
  }

  ~H264Encoder() override {
    if (query_pool_ != VK_NULL_HANDLE) {
      dev_dispatch_.DestroyQueryPool(device_, query_pool_, nullptr);
      query_pool_ = VK_NULL_HANDLE;
    }
  }

  void WriteEncodeCommands(VkCommandBuffer command_buffer, VkImage image) override {
    dev_dispatch_.ResetQueryPool(device_, query_pool_, 0, 1);

    bool is_idr_frame = encoded_frame_count_ % kIdrPeriod == 0;

    std::vector<vk::VideoReferenceSlotInfoKHR> reference_slots;

    vk::VideoBeginCodingInfoKHR video_begin_coding_info = {vk::VideoBeginCodingFlagsKHR{}, vk::VideoSessionKHR{},
                                                           vk::VideoSessionParametersKHR{}, reference_slots,
                                                           encode_rate_control_info_};

    dev_dispatch_.CmdBeginVideoCodingKHR(command_buffer, video_begin_coding_info);
  }

  std::vector<std::byte> GetEncodedData(VkImage image) override { return {}; }

  const vvk::ExecutionContext& execution_context_;
  const VkuDeviceDispatchTable& dev_dispatch_;
  VkDevice device_;
  uint32_t encoded_frame_count_ = 0;
  vk::VideoEncodeRateControlInfoKHR encode_rate_control_info_;
  vk::VideoEncodeH264RateControlInfoKHR h264_rate_control_info_;

  VkQueryPool query_pool_ = VK_NULL_HANDLE;

 private:
  void CreateQueryPool() {
    vk::QueryPoolVideoEncodeFeedbackCreateInfoKHR query_pool_video_encode_feedback_create_info = {
        vk::VideoEncodeFeedbackFlagBitsKHR::eBitstreamBufferOffset |
            vk::VideoEncodeFeedbackFlagBitsKHR::eBitstreamBytesWritten,
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

  constexpr static uint32_t kIdrPeriod = 16;
  constexpr static uint32_t kGopFrameCount = 16;
  constexpr static uint32_t kVirtualBufferSizeInMs = 200;
  constexpr static uint32_t kInitialVirtualBufferSizeInMs = 100;
};

}  // namespace vvk

#endif  // VVK_SERVER_H264_ENCODER_H
