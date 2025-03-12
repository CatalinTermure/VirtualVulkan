#include "device.h"

namespace vvk {

namespace {
std::mutex device_info_lock;
std::map<VkDevice, DeviceInfo> g_device_infos;
std::mutex command_buffer_to_device_lock;
std::map<VkCommandBuffer, VkDevice> g_command_buffer_to_device;
}  // namespace

DeviceInfo::DeviceInfo(PFN_vkGetDeviceProcAddr nxt_gdpa, VkPhysicalDevice physical_device,
                       const VmaAllocatorCreateInfo& allocator_create_info)
    : nxt_gdpa_(nxt_gdpa),
      physical_device_(physical_device),
      instance_(GetInstanceForPhysicalDevice(physical_device)),
      instance_info_(GetInstanceInfo(physical_device)) {
  if (vmaCreateAllocator(&allocator_create_info, &allocator_) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create VMA allocator");
  }
}

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
  auto [iter, inserted] = g_device_infos.try_emplace(device, nxt_gdpa, physical_device, allocator_create_info);
  assert(inserted);
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
