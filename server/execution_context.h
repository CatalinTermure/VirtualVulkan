#ifndef VVK_SERVER_EXECUTION_CONTEXT_H
#define VVK_SERVER_EXECUTION_CONTEXT_H

#include <vk_mem_alloc.h>
#include <vulkan/vulkan_core.h>

#include <unordered_map>

namespace vvk {

// TODO: Call vkDestroy functions if the client forgets to call them
class ExecutionContext {
 public:
  ExecutionContext() = default;
  ExecutionContext(const ExecutionContext&) = delete;
  ExecutionContext& operator=(const ExecutionContext&) = delete;
  ExecutionContext(ExecutionContext&&) = delete;
  ExecutionContext& operator=(ExecutionContext&&) = delete;

  VkPhysicalDevice physical_device() const { return physical_device_to_use_; }
  void set_physical_device(VkPhysicalDevice physical_device) { physical_device_to_use_ = physical_device; }

  VmaAllocator allocator() const { return allocator_; }
  void set_allocator(VmaAllocator allocator) { allocator_ = allocator; }

  ~ExecutionContext() {
    if (allocator_ != VK_NULL_HANDLE) {
      vmaDestroyAllocator(allocator_);
      allocator_ = VK_NULL_HANDLE;
    }
  }

 private:
  VkPhysicalDevice physical_device_to_use_ = VK_NULL_HANDLE;
  VmaAllocator allocator_ = VK_NULL_HANDLE;
};

}  // namespace vvk

#endif  // VVK_SERVER_EXECUTION_CONTEXT_H