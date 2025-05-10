#ifndef VVK_LAYER_CONTEXT_FENCE_POOL_H
#define VVK_LAYER_CONTEXT_FENCE_POOL_H

#include <vulkan/vulkan_core.h>

#include <mutex>
#include <vector>

namespace vvk {
class FencePool {
 public:
  FencePool(VkDevice device, size_t pool_size, PFN_vkCreateFence create_fence);

  VkFence GetFence();
  void ReturnFence(VkFence fence);

 private:
  std::vector<VkFence> fences_;
  std::mutex mutex_;
};
}  // namespace vvk

#endif  // VVK_LAYER_CONTEXT_FENCE_POOL_H
