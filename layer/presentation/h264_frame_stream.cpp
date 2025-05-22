#include "h264_frame_stream.h"

namespace vvk {
H264FrameStream::H264FrameStream(VkInstance instance, VkDevice device, uint32_t queue_family_index)
    : local_instance(instance), local_device(device), remote_graphics_queue_family_index(queue_family_index) {}

void H264FrameStream::AssociateSwapchain(VkSwapchainKHR swapchain, const VkExtent2D &swapchain_image_extent) {}
void H264FrameStream::RemoveSwapchain(VkSwapchainKHR swapchain) {}

// Called during command buffer recording for a presentable frame.
void H264FrameStream::SetupFrame(VkCommandBuffer remote_command_buffer, uint32_t swapchain_image_index) {}

// Called when a frame should be presented.
VkResult H264FrameStream::PresentFrame(VkQueue queue, const VkPresentInfoKHR &original_present_info) {
  return VK_SUCCESS;
}
}  // namespace vvk
