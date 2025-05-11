#ifndef VVK_LAYER_CONTEXT_DEVICE_H
#define VVK_LAYER_CONTEXT_DEVICE_H

// clang-format off
#include "layer/wsi_support.h"
// clang-format on

#include <vk_mem_alloc.h>
#include <vulkan/vulkan_core.h>

#include <list>
#include <map>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "layer/context/fence_pool.h"
#include "layer/context/instance.h"
#include "layer/context/mapped_memory.h"
#include "layer/dispatchable_object.h"
#include "layer/presentation.h"

namespace vvk {
struct DeviceInfo {
  DeviceInfo(VkDevice device, PFN_vkGetDeviceProcAddr nxt_gdpa, VkPhysicalDevice physical_device,
             const VmaAllocatorCreateInfo& remote_allocator_create_info,
             std::optional<uint32_t> present_queue_family_index, uint32_t remote_graphics_queue_family_index);

  VmaAllocator remote_allocator() const { return remote_allocator_; }
  VmaAllocator local_allocator() const { return local_allocator_; }
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

  bool IsLocalFence(VkFence fence) const {
    return local_synchronization_primitives_.find(reinterpret_cast<void*>(fence)) !=
           local_synchronization_primitives_.end();
  }
  void ResetFenceLocal(VkFence fence) { local_synchronization_primitives_.erase(reinterpret_cast<void*>(fence)); }
  void SetFenceLocal(VkFence fence) { local_synchronization_primitives_.insert(reinterpret_cast<void*>(fence)); }

  void AddMappedMemory(void* local_address, void* remote_address, VkDeviceMemory memory_handle, std::size_t map_size);
  void SyncMappedMemory(VkDeviceMemory memory);
  void SyncMappedMemories();
  void RemoveMappedMemory(VkDeviceMemory memory_handle);

  void RegisterMemorySize(VkDeviceMemory memory_handle, std::size_t size);
  std::size_t GetMemorySize(VkDeviceMemory memory_handle);
  void UnregisterMemorySize(VkDeviceMemory memory_handle);

  std::optional<uint32_t> present_queue_family_index() const { return present_queue_family_index_; }
  std::optional<VkQueue> present_queue() const { return present_queue_; }
  PresentationThread* presentation_thread() { return presentation_thread_.get(); }
  FencePool& fence_pool() { return fence_pool_; }

  void CreateFakeQueueFamily(uint32_t queue_family_index, uint32_t queue_count);
  VkQueue GetFakeQueue(uint32_t queue_family_index, uint32_t queue_index);

  std::unordered_map<VkImage, uint32_t> swapchain_images;
  std::unordered_map<VkImageView, uint32_t> swapchain_image_views;
  std::unordered_map<VkFramebuffer, uint32_t> swapchain_framebuffers;
  std::unordered_map<VkCommandBuffer, uint32_t> swapchain_render_command_buffers;

 private:
  std::map<void*, void*> local_to_remote_handle_;
  std::unordered_set<void*> local_synchronization_primitives_;
  VmaAllocator remote_allocator_;
  VmaAllocator local_allocator_;
  PFN_vkGetDeviceProcAddr nxt_gdpa_;
  InstanceInfo& instance_info_;
  VkuDeviceDispatchTable dispatch_table_;
  std::optional<uint32_t> present_queue_family_index_ = std::nullopt;
  std::optional<VkQueue> present_queue_ = std::nullopt;
  std::unordered_map<uint32_t, std::list<DispatchableObject>> fake_queue_families_;
  std::unique_ptr<PresentationThread> presentation_thread_;
  FencePool fence_pool_;
  std::unordered_map<VkDeviceMemory, MappedMemoryInfo> mapped_memory_infos_;
  std::unordered_map<VkDeviceMemory, std::size_t> memory_sizes_;
};

DeviceInfo& GetDeviceInfo(VkDevice device);
DeviceInfo& GetDeviceInfo(VkCommandBuffer command_buffer);
DeviceInfo& GetDeviceInfo(VkQueue queue);
DeviceInfo& SetDeviceInfo(VkDevice device, PFN_vkGetDeviceProcAddr nxt_gdpa, VkPhysicalDevice physical_device,
                          const VmaAllocatorCreateInfo& remote_allocator_create_info,
                          std::optional<uint32_t> present_queue_family_index,
                          uint32_t remote_graphics_queue_family_index);
void RemoveDeviceInfo(VkDevice device);

void AssociateCommandBufferWithDevice(VkCommandBuffer command_buffer, VkDevice device);
VkDevice GetDeviceForCommandBuffer(VkCommandBuffer command_buffer);
void AssociateCommandBufferWithPool(VkCommandBuffer command_buffer, VkCommandPool command_pool);
std::vector<VkCommandBuffer> GetCommandBuffersForPool(VkCommandPool command_pool);
void RemoveCommandBuffer(VkCommandBuffer command_buffer);

void AssociateQueueWithDevice(VkQueue queue, VkDevice device);
VkDevice GetDeviceForQueue(VkQueue queue);
}  // namespace vvk

#endif  // VVK_LAYER_CONTEXT_DEVICE_H
