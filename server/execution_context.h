#ifndef VVK_SERVER_EXECUTION_CONTEXT_H
#define VVK_SERVER_EXECUTION_CONTEXT_H

#include <vk_mem_alloc.h>
#include <vulkan/utility/vk_dispatch_table.h>
#include <vulkan/vulkan_core.h>

#include <functional>
#include <memory>
#include <queue>
#include <unordered_map>

#include "server/encoder.h"

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

  void defer_deletion(std::function<void()> func) { deferred_deletion_queue_.emplace(std::move(func)); }

  void InitInstanceDispatchTable(VkInstance instance) {
    vkuInitInstanceDispatchTable(instance, &instance_dispatch_table_, vkGetInstanceProcAddr);
    instance_dispatch_table_.CreateDevice =
        reinterpret_cast<PFN_vkCreateDevice>(vkGetInstanceProcAddr(instance, "vkCreateDevice"));
  }

  void InitDeviceDispatchTable(VkDevice device) {
    vkuInitDeviceDispatchTable(device, &device_dispatch_table_, vkGetDeviceProcAddr);
  }

  const VkuInstanceDispatchTable& instance_dispatch_table() const { return instance_dispatch_table_; }
  const VkuDeviceDispatchTable& device_dispatch_table() const { return device_dispatch_table_; }

  ~ExecutionContext() {
    while (!deferred_deletion_queue_.empty()) {
      deferred_deletion_queue_.front()();
      deferred_deletion_queue_.pop();
    }
    if (allocator_ != VK_NULL_HANDLE) {
      vmaDestroyAllocator(allocator_);
      allocator_ = VK_NULL_HANDLE;
    }
  }

  // May return nullptr if no encoder is set.
  Encoder* encoder() const { return encoder_.get(); }
  void set_encoder(std::unique_ptr<Encoder> encoder) { encoder_ = std::move(encoder); }

 private:
  VkPhysicalDevice physical_device_to_use_ = VK_NULL_HANDLE;
  VmaAllocator allocator_ = VK_NULL_HANDLE;
  std::queue<std::function<void()>> deferred_deletion_queue_;
  VkuInstanceDispatchTable instance_dispatch_table_;
  VkuDeviceDispatchTable device_dispatch_table_;
  std::unique_ptr<Encoder> encoder_;
};

}  // namespace vvk

#endif  // VVK_SERVER_EXECUTION_CONTEXT_H