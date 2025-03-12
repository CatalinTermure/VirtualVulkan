#ifndef VVK_LAYER_CONTEXT_DEVICE_H
#define VVK_LAYER_CONTEXT_DEVICE_H

#include <vk_mem_alloc.h>
#include <vulkan/vulkan_core.h>

#include <map>
#include <memory>

#include "layer/context/instance.h"

namespace vvk {
struct DeviceInfo {
  DeviceInfo(VkDevice device, PFN_vkGetDeviceProcAddr nxt_gdpa, VkPhysicalDevice physical_device,
             const VmaAllocatorCreateInfo& allocator_create_info);

  VmaAllocator allocator() const { return allocator_; }
  InstanceInfo& instance_info() { return instance_info_; }
  const VkuDeviceDispatchTable& dispatch_table() { return dispatch_table_; }

  template <typename T>
  T GetRemoteHandle(T local_handle) const {
    return reinterpret_cast<T>(local_to_remote_handle_.at(reinterpret_cast<void*>(local_handle)));
  }

  bool HasRemoteHandle(void* local_handle) const {
    return local_to_remote_handle_.find(local_handle) != local_to_remote_handle_.end();
  }

  template <typename T>
  void SetRemoteHandle(T local_handle, T remote_handle) {
    local_to_remote_handle_.emplace(reinterpret_cast<void*>(local_handle), reinterpret_cast<void*>(remote_handle));
  }

 private:
  std::map<void*, void*> local_to_remote_handle_;
  VmaAllocator allocator_;
  InstanceInfo& instance_info_;
  PFN_vkGetDeviceProcAddr nxt_gdpa_;
  VkuDeviceDispatchTable dispatch_table_;
};

DeviceInfo& GetDeviceInfo(VkDevice device);
DeviceInfo& GetDeviceInfo(VkCommandBuffer command_buffer);
void SetDeviceInfo(VkDevice device, PFN_vkGetDeviceProcAddr nxt_gdpa, VkPhysicalDevice physical_device,
                   const VmaAllocatorCreateInfo& allocator_create_info);
void RemoveDeviceInfo(VkDevice device);

void AssociateCommandBufferWithDevice(VkCommandBuffer command_buffer, VkDevice device);
VkDevice GetDeviceForCommandBuffer(VkCommandBuffer command_buffer);
void RemoveCommandBuffer(VkCommandBuffer command_buffer);
}  // namespace vvk

#endif  // VVK_LAYER_CONTEXT_DEVICE_H
