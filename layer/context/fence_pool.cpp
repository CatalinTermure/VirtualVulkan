#include "fence_pool.h"

#include "layer/context/device.h"

namespace vvk {

FencePool::FencePool(VkDevice device, size_t pool_size, PFN_vkCreateFence create_fence) {
  fences_.resize(pool_size);
  for (size_t i = 0; i < pool_size; ++i) {
    VkFenceCreateInfo fence_create_info = {
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
    };
    VkResult result = create_fence(device, &fence_create_info, nullptr, &fences_[i]);
    if (result != VK_SUCCESS) {
      throw std::runtime_error("Failed to create fence");
    }
  }
}

VkFence FencePool::GetFence() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (fences_.empty()) {
    throw std::runtime_error("No available fences in the pool");
  }
  VkFence fence = fences_.back();
  fences_.pop_back();
  return fence;
}

void FencePool::ReturnFence(VkFence fence) {
  std::lock_guard<std::mutex> lock(mutex_);
  fences_.push_back(fence);
}

}  // namespace vvk
