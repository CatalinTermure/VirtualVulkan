#include "fence_pool.h"

#include "layer/context/device.h"

namespace vvk {

VkFenceProxy::VkFenceProxy(VkFenceProxy&& other) noexcept : fence_(other.fence_), fence_pool_(other.fence_pool_) {
  other.fence_ = VK_NULL_HANDLE;
}

VkFenceProxy& VkFenceProxy::operator=(VkFenceProxy&& other) noexcept {
  if (this != &other) {
    if (fence_) {
      fence_pool_->ReturnFence(fence_);
    }
    fence_ = other.fence_;
    fence_pool_ = other.fence_pool_;
    other.fence_ = VK_NULL_HANDLE;
  }
  return *this;
}

VkFenceProxy::~VkFenceProxy() {
  if (fence_) {
    fence_pool_->ReturnFence(fence_);
  }
}

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

VkFenceProxy FencePool::GetFence() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (fences_.empty()) {
    throw std::runtime_error("No available fences in the pool");
  }
  VkFence fence = fences_.back();
  fences_.pop_back();
  return VkFenceProxy{fence, *this};
}

void FencePool::ReturnFence(VkFence& fence) {
  std::lock_guard<std::mutex> lock(mutex_);
  fences_.push_back(fence);
  fence = VK_NULL_HANDLE;
}

}  // namespace vvk
