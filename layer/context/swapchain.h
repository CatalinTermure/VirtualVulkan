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

class Swapchain {
 public:
  Swapchain(VkSwapchainKHR swapchain, VkDevice device, VmaAllocator remote_allocator,
            const std::vector<VkImage>& swapchain_images, const VkExtent2D& swapchain_image_extent);
  Swapchain(const Swapchain&) = delete;
  Swapchain& operator=(const Swapchain&) = delete;

  VkImage CreateImageRemote(const VkImageCreateInfo& create_info, const VmaAllocationCreateInfo& alloc_info);

  std::span<const std::pair<VkImage, VmaAllocation>> GetRemoteImages() const { return remote_images_; }
  std::span<VkImage> GetLocalSwapchainImages() { return local_swapchain_images_; }

  std::mutex& GetLock() { return lock_; }

  void SetImageAcquired() { acquired_images_.acquire(); }
  void SetImageReleased() { acquired_images_.release(); }

  VkFormat GetRemoteImageFormat() const { return remote_image_format_; }

  ~Swapchain();

 private:
  VkSwapchainKHR swapchain_handle_;
  VkDevice device_;
  Instance& instance_info_;
  VmaAllocator remote_allocator_;
  std::vector<std::pair<VkImage, VmaAllocation>> remote_images_;
  std::vector<VkImage> local_swapchain_images_;
  std::mutex lock_;
  std::counting_semaphore<64> acquired_images_;
  VkFormat remote_image_format_;
};

Swapchain& GetSwapchainInfo(VkSwapchainKHR swapchain);
Swapchain& SetSwapchainInfo(VkSwapchainKHR swapchain, VkDevice device, VmaAllocator remote_allocator,
                            const std::vector<VkImage>& swapchain_images, const VkExtent2D& swapchain_image_extent);
void RemoveSwapchainInfo(VkSwapchainKHR swapchain);

}  // namespace vvk

#endif  // VVK_LAYER_CONTEXT_SWAPCHAIN_H
