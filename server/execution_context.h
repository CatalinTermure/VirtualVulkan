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

  template <typename T>
  void SetHandleAssociation(T* client_handle, T* server_handle) {
    client_to_server_handles_[reinterpret_cast<void*>(client_handle)] = reinterpret_cast<void*>(server_handle);
  }

  template <typename T>
  T* GetServerHandle(T* client_handle) const {
    return reinterpret_cast<T*>(client_to_server_handles_.at(reinterpret_cast<void*>(client_handle)));
  }

  void RemoveAssociatedHandle(void* client_handle) { client_to_server_handles_.erase(client_handle); }

 private:
  std::unordered_map<void*, void*> client_to_server_handles_;
  VkPhysicalDevice physical_device_to_use_;
};

}  // namespace vvk

#endif  // VVK_SERVER_EXECUTION_CONTEXT_H