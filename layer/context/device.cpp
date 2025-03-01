#include "device.h"

namespace vvk {

namespace {
std::mutex device_info_lock;
std::map<VkDevice, DeviceInfo> g_device_infos;
std::mutex command_buffer_to_device_lock;
std::map<VkCommandBuffer, VkDevice> g_command_buffer_to_device;
}  // namespace

DeviceInfo::DeviceInfo(PFN_vkGetDeviceProcAddr nxt_gdpa, VkPhysicalDevice physical_device)
    : nxt_gdpa(nxt_gdpa),
      physical_device(physical_device),
      instance(GetInstanceForPhysicalDevice(physical_device)),
      instance_info(GetInstanceInfo(physical_device)) {}

DeviceInfo& GetDeviceInfo(VkDevice device) {
  std::lock_guard lock(device_info_lock);
  return g_device_infos.at(device);
}

DeviceInfo& GetDeviceInfo(VkCommandBuffer command_buffer) {
  return GetDeviceInfo(GetDeviceForCommandBuffer(command_buffer));
}

void SetDeviceInfo(VkDevice device, PFN_vkGetDeviceProcAddr nxt_gdpa, VkPhysicalDevice physical_device,
                   const VmaAllocatorCreateInfo& allocator_create_info) {
  std::lock_guard lock(device_info_lock);
  VkInstance instance = GetInstanceForPhysicalDevice(physical_device);
  auto [iter, inserted] = g_device_infos.try_emplace(device, nxt_gdpa, physical_device);
  assert(inserted);
  vmaCreateAllocator(&allocator_create_info, &iter->second.allocator_);
}

void RemoveDeviceInfo(VkDevice device) {
  std::lock_guard lock(device_info_lock);
  g_device_infos.erase(device);
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

}  // namespace vvk
