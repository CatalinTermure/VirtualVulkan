#ifndef VVK_LAYER_PRESENTATION_H
#define VVK_LAYER_PRESENTATION_H

#include <vulkan/vulkan_core.h>

#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <semaphore>
#include <span>
#include <thread>
#include <vector>

namespace vvk {

struct PresentationThread {
  // Creates a worker thread for presenting frames from the remote server to the local device.
  static std::unique_ptr<PresentationThread> Create(VkInstance local_instance, VkDevice local_device,
                                                    VkPhysicalDevice remote_physical_device,
                                                    uint32_t remote_graphics_queue_family_index);

  void AssociateSwapchain(VkSwapchainKHR swapchain, const VkExtent2D& swapchain_image_extent);

  void RemoveSwapchain(VkSwapchainKHR swapchain);

  // Called during command buffer recording for a presentable frame.
  void SetupFrame(VkCommandBuffer remote_command_buffer, uint32_t swapchain_image_index);

  // Called when a frame should be presented.
  VkResult PresentFrame(VkQueue queue, const VkPresentInfoKHR& original_present_info);

 private:
  struct SwapchainPresentationInfo {
    VkSwapchainKHR swapchain;
    uint64_t remote_session_key;
    std::vector<uint64_t> remote_buffers;
    std::vector<uint64_t> remote_frame_keys;
    VkExtent2D image_extent;
  };

  VkInstance local_instance;
  VkDevice local_device;
  uint32_t remote_graphics_queue_family_index;
  std::vector<SwapchainPresentationInfo> swapchains;

  PresentationThread(VkInstance instance, VkDevice device, uint32_t queue_family_index);
};

}  // namespace vvk

#endif  // VVK_LAYER_PRESENTATION_H
