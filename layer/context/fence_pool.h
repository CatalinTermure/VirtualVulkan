#ifndef VVK_LAYER_CONTEXT_FENCE_POOL_H
#define VVK_LAYER_CONTEXT_FENCE_POOL_H

#include <vulkan/vulkan_core.h>

#include <functional>
#include <mutex>
#include <vector>

namespace vvk {

class FencePool;

class VkFenceProxy {
 public:
  VkFenceProxy(VkFence fence, FencePool& fence_pool) : fence_(fence), fence_pool_(&fence_pool) {}

  VkFenceProxy(const VkFenceProxy&) = delete;
  VkFenceProxy& operator=(const VkFenceProxy&) = delete;
  VkFenceProxy(VkFenceProxy&& other) noexcept;
  VkFenceProxy& operator=(VkFenceProxy&& other) noexcept;

  ~VkFenceProxy();

  VkFence operator*() const { return fence_; }
  const VkFence* get() const { return &fence_; }
  VkFence* get() { return &fence_; }

 private:
  VkFence fence_;
  FencePool* fence_pool_;
};

class FencePool {
 public:
  FencePool(VkDevice device, size_t pool_size, PFN_vkCreateFence create_fence);

  VkFenceProxy GetFence();
  void ReturnFence(VkFence& fence);

  void ForAllFences(const std::function<void(VkFence&)>& func) {
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto& fence : fences_) {
      func(fence);
    }
  }

 private:
  std::vector<VkFence> fences_;
  std::mutex mutex_;
};
}  // namespace vvk

#endif  // VVK_LAYER_CONTEXT_FENCE_POOL_H
