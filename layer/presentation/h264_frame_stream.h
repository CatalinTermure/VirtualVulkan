#ifndef VVK_LAYER_PRESENTATION_H264_FRAME_STREAM_H
#define VVK_LAYER_PRESENTATION_H264_FRAME_STREAM_H

// clang-format off
#include "layer/wsi_support.h"
// clang-format on

#include "frame_stream.h"
#include "memory_to_image_copy.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

#include <list>

namespace vvk {

class H264FrameStream final : public FrameStream {
 public:
  H264FrameStream(VkInstance instance, VkDevice device, uint32_t graphics_queue_family_index,
                  uint32_t video_queue_family_index);

  void AssociateSwapchain(VkSwapchainKHR swapchain, const VkExtent2D &swapchain_image_extent) override;
  void RemoveSwapchain(VkSwapchainKHR swapchain) override;

  // Called during command buffer recording for a presentable frame.
  void SetupFrame(VkCommandBuffer remote_command_buffer, uint32_t swapchain_image_index) override;

  // Called when a frame should be presented.
  VkResult PresentFrame(VkQueue queue, const VkPresentInfoKHR &original_present_info) override;

  ~H264FrameStream() override;

  struct DecodeInfo {
    unsigned char *aux_buffer;
    AVFormatContext *format_context = nullptr;
    const AVCodec *decoder = nullptr;
    AVCodecContext *decoder_context = nullptr;
    AVPixelFormat hw_format;
    AVStream *video = nullptr;
    AVBufferRef *hw_device_ctx = nullptr;
    AVFrame *frame = nullptr;
    AVFrame *sw_frame = nullptr;
    uint8_t *buffer = nullptr;
  };

  struct SwapchainPresentationInfo {
    VkSwapchainKHR swapchain;
    uint64_t remote_session_key;
    std::vector<uint64_t> remote_frame_keys;
    VkExtent2D image_extent;
    std::string decode_buffer;
    std::optional<DecodeInfo> decode_info;
    MemoryToImageCopyContext copy_context;
  };

 private:
  VkInstance local_instance_;
  VkDevice local_device_;
  uint32_t remote_video_queue_family_index_;
  uint32_t remote_graphics_queue_family_index_;
  std::list<SwapchainPresentationInfo> swapchains_;
  VkSemaphore remote_encode_wait_semaphore_ = VK_NULL_HANDLE;
  std::string decode_buffer_;
};
}  // namespace vvk

#endif  // VVK_LAYER_PRESENTATION_H264_FRAME_STREAM_H
