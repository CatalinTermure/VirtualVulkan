#ifndef VVK_LAYER_CONTEXT_SWAPCHAIN_H
#define VVK_LAYER_CONTEXT_SWAPCHAIN_H

// clang-format off
#include "layer/wsi_support.h"
// clang-format on

#include <vk_mem_alloc.h>
#include <vulkan/vulkan_core.h>

#include <vector>

#include "layer/context/instance.h"

namespace vvk {

class SwapchainInfo {
 public:
  SwapchainInfo(VkDevice device, VmaAllocator remote_allocator, const std::vector<VkImage>& swapchain_images,
                const VkExtent2D& swapchain_image_extent);
  SwapchainInfo(const SwapchainInfo&) = delete;
  SwapchainInfo& operator=(const SwapchainInfo&) = delete;

  VkImage CreateImageRemote(const VkImageCreateInfo& create_info, const VmaAllocationCreateInfo& alloc_info);

  ~SwapchainInfo();

 private:
  VkDevice device_;
  VmaAllocator remote_allocator_;
  InstanceInfo& instance_info_;
  std::vector<std::pair<VkImage, VmaAllocation>> remote_images_;
  VkCommandPool command_pool_;
  std::vector<VkBuffer> staging_buffers_;
  std::vector<VmaAllocation> buffer_allocations_;
  std::vector<VkCommandBuffer> command_buffers_;
};

SwapchainInfo& GetSwapchainInfo(VkSwapchainKHR swapchain);
SwapchainInfo& SetSwapchainInfo(VkSwapchainKHR swapchain, VkDevice device, VmaAllocator remote_allocator,
                                const std::vector<VkImage>& swapchain_images, const VkExtent2D& swapchain_image_extent);
void RemoveSwapchainInfo(VkSwapchainKHR swapchain);

}  // namespace vvk

#endif  // VVK_LAYER_CONTEXT_SWAPCHAIN_H
