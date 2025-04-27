#ifndef VVK_LAYER_PRESENTATION_H
#define VVK_LAYER_PRESENTATION_H

#include <vulkan/vulkan_core.h>

#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <span>
#include <thread>
#include <vector>

namespace vvk {

struct SwapchainPresentationInfo {
  VkSwapchainKHR swapchain;
  uint64_t remote_session_key;
  std::vector<uint64_t> remote_buffers;
  std::vector<uint64_t> remote_frame_keys;
  VkExtent2D image_extent;
  uint32_t swapchain_image_index;
};

struct PresentationThread {
  VkInstance local_instance;
  VkDevice local_device;
  uint32_t remote_graphics_queue_family_index;
  std::queue<std::function<void()>> work_queue;
  std::counting_semaphore<64> work_queue_semaphore;
  bool should_exit;
  std::vector<SwapchainPresentationInfo> swapchains;
  std::jthread thread;

  PresentationThread(VkInstance instance, VkDevice device, uint32_t queue_family_index);
};

// Creates a worker thread for presenting frames from the remote server to the local device.
std::unique_ptr<PresentationThread> PresentationThreadCreate(VkInstance local_instance, VkDevice local_device,
                                                             uint32_t remote_graphics_queue_family_index);
void PresentationThreadAssociateSwapchain(PresentationThread& presentation_thread, VkSwapchainKHR swapchain,
                                          const VkExtent2D& swapchain_image_extent);
// Called during command buffer recording for a presentable frame.
void PresentationThreadSetupFrame(PresentationThread& presentation_thread, VkCommandBuffer remote_command_buffer);
// Called when a frame should be presented.
void PresentationThreadPresentFrame(PresentationThread& presentation_thread, VkPresentInfoKHR* present_info);

}  // namespace vvk

#endif  // VVK_LAYER_PRESENTATION_H
