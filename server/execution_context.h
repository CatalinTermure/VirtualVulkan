#ifndef VVK_SERVER_EXECUTION_CONTEXT_H
#define VVK_SERVER_EXECUTION_CONTEXT_H

#include <vulkan/vulkan_core.h>

#include <unordered_map>

namespace vvk {

// TODO: Call vkDestroy functions if the client forgets to call them
class ExecutionContext {
 public:
  VkPhysicalDevice physical_device() const { return physical_device_to_use_; }
  void set_physical_device(VkPhysicalDevice physical_device) { physical_device_to_use_ = physical_device; }

 private:
  VkPhysicalDevice physical_device_to_use_;
};

}  // namespace vvk

#endif  // VVK_SERVER_EXECUTION_CONTEXT_H