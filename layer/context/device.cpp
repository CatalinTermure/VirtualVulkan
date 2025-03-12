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
                       const VmaAllocatorCreateInfo& allocator_create_info)
    : nxt_gdpa_(nxt_gdpa), instance_info_(GetInstanceInfo(physical_device)) {
  if (vmaCreateAllocator(&allocator_create_info, &allocator_) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create VMA allocator");
  }
  vkuInitDeviceDispatchTable(device, &dispatch_table_, nxt_gdpa);
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
                   const VmaAllocatorCreateInfo& allocator_create_info) {
  std::lock_guard lock(device_info_lock);
  auto [iter, inserted] = g_device_infos.try_emplace(device, device, nxt_gdpa, physical_device, allocator_create_info);
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
