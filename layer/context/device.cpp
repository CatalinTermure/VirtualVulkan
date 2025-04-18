#include "device.h"

#include <algorithm>

namespace vvk {

namespace {
std::mutex device_info_lock;
std::map<VkDevice, DeviceInfo> g_device_infos;
std::mutex command_buffer_to_device_lock;
std::map<VkCommandBuffer, VkDevice> g_command_buffer_to_device;
std::mutex queue_to_device_lock;
std::map<VkQueue, VkDevice> g_queue_to_device;
}  // namespace

DeviceInfo::DeviceInfo(VkDevice device, PFN_vkGetDeviceProcAddr nxt_gdpa, VkPhysicalDevice physical_device,
                       const VmaAllocatorCreateInfo& remote_allocator_create_info)
    : nxt_gdpa_(nxt_gdpa), instance_info_(GetInstanceInfo(physical_device)) {
  if (vmaCreateAllocator(&remote_allocator_create_info, &remote_allocator_) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create remote VMA allocator");
  }
  vkuInitDeviceDispatchTable(device, &dispatch_table_, nxt_gdpa);

  VmaVulkanFunctions vma_vulkan_funcs = {
      .vkGetInstanceProcAddr = nullptr,
      .vkGetDeviceProcAddr = nullptr,
      .vkGetPhysicalDeviceProperties = instance_info_.dispatch_table().GetPhysicalDeviceProperties,
      .vkGetPhysicalDeviceMemoryProperties = instance_info_.dispatch_table().GetPhysicalDeviceMemoryProperties,
      .vkAllocateMemory = dispatch_table_.AllocateMemory,
      .vkFreeMemory = dispatch_table_.FreeMemory,
      .vkMapMemory = dispatch_table_.MapMemory,
      .vkUnmapMemory = dispatch_table_.UnmapMemory,
      .vkFlushMappedMemoryRanges = dispatch_table_.FlushMappedMemoryRanges,
      .vkInvalidateMappedMemoryRanges = dispatch_table_.InvalidateMappedMemoryRanges,
      .vkBindBufferMemory = dispatch_table_.BindBufferMemory,
      .vkBindImageMemory = dispatch_table_.BindImageMemory,
      .vkGetBufferMemoryRequirements = dispatch_table_.GetBufferMemoryRequirements,
      .vkGetImageMemoryRequirements = dispatch_table_.GetImageMemoryRequirements,
      .vkCreateBuffer = dispatch_table_.CreateBuffer,
      .vkDestroyBuffer = dispatch_table_.DestroyBuffer,
      .vkCreateImage = dispatch_table_.CreateImage,
      .vkDestroyImage = dispatch_table_.DestroyImage,
      .vkCmdCopyBuffer = dispatch_table_.CmdCopyBuffer,
      .vkGetBufferMemoryRequirements2KHR = dispatch_table_.GetBufferMemoryRequirements2KHR,
      .vkGetImageMemoryRequirements2KHR = dispatch_table_.GetImageMemoryRequirements2KHR,
      .vkBindBufferMemory2KHR = dispatch_table_.BindBufferMemory2KHR,
      .vkBindImageMemory2KHR = dispatch_table_.BindImageMemory2KHR,
      .vkGetPhysicalDeviceMemoryProperties2KHR = instance_info_.dispatch_table().GetPhysicalDeviceMemoryProperties2KHR,
      .vkGetDeviceBufferMemoryRequirements = dispatch_table_.GetDeviceBufferMemoryRequirements,
      .vkGetDeviceImageMemoryRequirements = dispatch_table_.GetDeviceImageMemoryRequirements,
  };
  VmaAllocatorCreateInfo local_allocator_create_info = {
      .flags = 0,
      .physicalDevice = physical_device,
      .device = device,
      .preferredLargeHeapBlockSize = 0,
      .pAllocationCallbacks = nullptr,
      .pDeviceMemoryCallbacks = nullptr,
      .pHeapSizeLimit = nullptr,
      .pVulkanFunctions = &vma_vulkan_funcs,
      .instance = GetInstanceForPhysicalDevice(physical_device),
      .vulkanApiVersion = VK_API_VERSION_1_0,
      .pTypeExternalMemoryHandleTypes = nullptr,
  };

  if (vmaCreateAllocator(&local_allocator_create_info, &local_allocator_) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create local VMA allocator");
  }
}

DeviceInfo& GetDeviceInfo(VkDevice device) {
  std::lock_guard lock(device_info_lock);
  return g_device_infos.at(device);
}

DeviceInfo& GetDeviceInfo(VkCommandBuffer command_buffer) {
  return GetDeviceInfo(GetDeviceForCommandBuffer(command_buffer));
}

DeviceInfo& GetDeviceInfo(VkQueue queue) { return GetDeviceInfo(GetDeviceForQueue(queue)); }

void SetDeviceInfo(VkDevice device, PFN_vkGetDeviceProcAddr nxt_gdpa, VkPhysicalDevice physical_device,
                   const VmaAllocatorCreateInfo& remote_allocator_create_info) {
  std::lock_guard lock(device_info_lock);
  auto [iter, inserted] =
      g_device_infos.try_emplace(device, device, nxt_gdpa, physical_device, remote_allocator_create_info);
  assert(inserted);
}

void RemoveDeviceInfo(VkDevice device) {
  {
    std::lock_guard lock(command_buffer_to_device_lock);
    for (auto& [command_buffer, associated_device] : g_command_buffer_to_device) {
      if (associated_device == device) {
        throw std::runtime_error("Command buffers should be freed before the device is destroyed");
      }
    }
  }
  {
    std::lock_guard lock(queue_to_device_lock);
    std::erase_if(g_queue_to_device, [device](const auto& pair) { return pair.second == device; });
  }
  {
    std::lock_guard lock(device_info_lock);
    g_device_infos.erase(device);
  }
}

void AssociateCommandBufferWithDevice(VkCommandBuffer command_buffer, VkDevice device) {
  std::lock_guard lock(command_buffer_to_device_lock);
  g_command_buffer_to_device[command_buffer] = device;
}

VkDevice GetDeviceForCommandBuffer(VkCommandBuffer command_buffer) {
  std::lock_guard lock(command_buffer_to_device_lock);
  return g_command_buffer_to_device.at(command_buffer);
}

void RemoveCommandBuffer(VkCommandBuffer command_buffer) {
  std::lock_guard lock(command_buffer_to_device_lock);
  g_command_buffer_to_device.erase(command_buffer);
}

void AssociateQueueWithDevice(VkQueue queue, VkDevice device) {
  std::lock_guard lock(queue_to_device_lock);
  g_queue_to_device[queue] = device;
}

VkDevice GetDeviceForQueue(VkQueue queue) {
  std::lock_guard lock(queue_to_device_lock);
  return g_queue_to_device.at(queue);
}

}  // namespace vvk
