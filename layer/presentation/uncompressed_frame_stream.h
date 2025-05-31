#ifndef VVK_LAYER_PRESENTATION_UNCOMPRESSED_FRAME_STREAM_H
#define VVK_LAYER_PRESENTATION_UNCOMPRESSED_FRAME_STREAM_H

#include "layer/presentation/frame_stream.h"
#include "layer/presentation/memory_to_image_copy.h"

namespace vvk {
class UncompressedFrameStream final : public FrameStream {
 public:
  UncompressedFrameStream(VkInstance instance, VkDevice device, uint32_t queue_family_index);

  void AssociateSwapchain(VkSwapchainKHR swapchain, const VkExtent2D &swapchain_image_extent) override;
  void RemoveSwapchain(VkSwapchainKHR swapchain) override;

  // Called during command buffer recording for a presentable frame.
  void SetupFrame(VkCommandBuffer remote_command_buffer, uint32_t swapchain_image_index) override;

  // Called when a frame should be presented.
  VkResult PresentFrame(VkQueue queue, const VkPresentInfoKHR &original_present_info) override;

  ~UncompressedFrameStream() override = default;

 private:
  struct SwapchainPresentationInfo {
    VkSwapchainKHR swapchain;
    uint64_t remote_session_key;
    std::vector<uint64_t> remote_buffers;
    std::vector<uint64_t> remote_frame_keys;
    VkExtent2D image_extent;
    MemoryToImageCopyContext copy_context;
  };

  VkInstance local_instance;
  VkDevice local_device;
  uint32_t remote_graphics_queue_family_index;
  std::vector<SwapchainPresentationInfo> swapchains;
};
}  // namespace vvk

#endif  // VVK_LAYER_PRESENTATION_UNCOMPRESSED_FRAME_STREAM_H
