#ifndef VVK_LAYER_CONTEXT_SWAPCHAIN_H
#define VVK_LAYER_CONTEXT_SWAPCHAIN_H

#include <vk_mem_alloc.h>
#include <vulkan/vulkan_core.h>

#include <vector>

#include "layer/context/instance.h"

namespace vvk {

class SwapchainInfo {
 public:
  SwapchainInfo(VkDevice device, VmaAllocator remote_allocator);
  SwapchainInfo(const SwapchainInfo&) = delete;
  SwapchainInfo& operator=(const SwapchainInfo&) = delete;

  VkImage CreateImageRemote(const VkImageCreateInfo& create_info, const VmaAllocationCreateInfo& alloc_info);

  ~SwapchainInfo();

 private:
  VkDevice device_;
  VmaAllocator remote_allocator_;
  InstanceInfo& instance_info_;
  std::vector<std::pair<VkImage, VmaAllocation>> remote_images_;
};

SwapchainInfo& GetSwapchainInfo(VkSwapchainKHR swapchain);
SwapchainInfo& SetSwapchainInfo(VkSwapchainKHR swapchain, VkDevice device, VmaAllocator remote_allocator);
void RemoveSwapchainInfo(VkSwapchainKHR swapchain);

}  // namespace vvk

#endif  // VVK_LAYER_CONTEXT_SWAPCHAIN_H
