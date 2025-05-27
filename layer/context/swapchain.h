#ifndef VVK_LAYER_CONTEXT_SWAPCHAIN_H
#define VVK_LAYER_CONTEXT_SWAPCHAIN_H

// clang-format off
#include "layer/wsi_support.h"
// clang-format on

#include <vk_mem_alloc.h>
#include <vulkan/vulkan_core.h>

#include <mutex>
#include <semaphore>
#include <span>
#include <vector>

#include "layer/context/instance.h"

namespace vvk {

class SwapchainInfo {
 public:
  SwapchainInfo(VkSwapchainKHR swapchain, VkDevice device, VmaAllocator remote_allocator,
                const std::vector<VkImage>& swapchain_images, const VkExtent2D& swapchain_image_extent);
  SwapchainInfo(const SwapchainInfo&) = delete;
  SwapchainInfo& operator=(const SwapchainInfo&) = delete;

  VkImage CreateImageRemote(const VkImageCreateInfo& create_info, const VmaAllocationCreateInfo& alloc_info);

  std::span<const std::pair<VkImage, VmaAllocation>> GetRemoteImages() const { return remote_images_; }
  std::span<const VkImage> GetLocalSwapchainImages() const { return local_swapchain_images_; }

  VkResult CopyMemoryToImage(uint32_t image_index, std::string_view data, std::span<VkSemaphore> semaphores_to_wait,
                             std::span<VkPipelineStageFlags> wait_stages, std::span<VkSemaphore> semaphores_to_signal,
                             VkFence fence_to_signal);

  std::mutex& GetLock() { return lock_; }

  void SetImageAcquired() { acquired_images_.acquire(); }
  void SetImageReleased() { acquired_images_.release(); }

  ~SwapchainInfo();

 private:
  VkSwapchainKHR swapchain_handle_;
  VkDevice device_;
  InstanceInfo& instance_info_;
  VmaAllocator remote_allocator_;
  std::vector<std::pair<VkImage, VmaAllocation>> remote_images_;
  VkCommandPool command_pool_;
  std::vector<VkBuffer> staging_buffers_;
  std::vector<VmaAllocation> buffer_allocations_;
  std::vector<VkCommandBuffer> command_buffers_;
  std::vector<VkImage> local_swapchain_images_;
  std::mutex lock_;
  std::counting_semaphore<64> acquired_images_;
};

SwapchainInfo& GetSwapchainInfo(VkSwapchainKHR swapchain);
SwapchainInfo& SetSwapchainInfo(VkSwapchainKHR swapchain, VkDevice device, VmaAllocator remote_allocator,
                                const std::vector<VkImage>& swapchain_images, const VkExtent2D& swapchain_image_extent);
void RemoveSwapchainInfo(VkSwapchainKHR swapchain);

}  // namespace vvk

#endif  // VVK_LAYER_CONTEXT_SWAPCHAIN_H
