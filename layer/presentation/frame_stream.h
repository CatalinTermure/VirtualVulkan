#ifndef VVK_LAYER_PRESENTATION_FRAME_STREAM_H
#define VVK_LAYER_PRESENTATION_FRAME_STREAM_H

#include <vulkan/vulkan_core.h>

#include <memory>

#include "vvk_presentation.pb.h"

namespace vvk {

class FrameStream {
 public:
  // Creates a FrameStream instance.
  static std::unique_ptr<FrameStream> Create(VkInstance local_instance, VkDevice local_device,
                                             VkPhysicalDevice remote_physical_device,
                                             uint32_t remote_graphics_queue_family_index,
                                             const vvk::server::StreamingCapabilities &client_streaming_capabilities);

  virtual void AssociateSwapchain(VkSwapchainKHR swapchain, const VkExtent2D &swapchain_image_extent) = 0;
  virtual void RemoveSwapchain(VkSwapchainKHR swapchain) = 0;

  // Called during command buffer recording for a presentable frame.
  virtual void SetupFrame(VkCommandBuffer remote_command_buffer, uint32_t swapchain_image_index) = 0;

  // Called when a frame should be presented.
  virtual VkResult PresentFrame(VkQueue queue, const VkPresentInfoKHR &original_present_info) = 0;
};

}  // namespace vvk

#endif  // VVK_LAYER_PRESENTATION_FRAME_STREAM_H
