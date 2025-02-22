#include "context.h"

#include <map>
#include <mutex>

namespace vvk {

namespace {
std::mutex instance_info_lock;
std::map<VkInstance, InstanceInfo> g_instance_infos;
std::mutex device_info_lock;
std::map<VkDevice, DeviceInfo> g_device_infos;
std::mutex physical_device_to_instance_lock;
std::map<VkPhysicalDevice, VkInstance> g_physical_device_to_instance;
std::mutex command_buffer_to_device_lock;
std::map<VkCommandBuffer, VkDevice> g_command_buffer_to_device;
}  // namespace

InstanceInfo& GetInstanceInfo(VkInstance instance) {
  std::lock_guard lock(instance_info_lock);
  return g_instance_infos.at(instance);
}

InstanceInfo& SetInstanceInfo(VkInstance instance, PFN_vkGetInstanceProcAddr nxt_gipa,
                              std::shared_ptr<grpc::Channel> channel) {
  std::lock_guard lock(instance_info_lock);
  auto [iter, inserted] = g_instance_infos.try_emplace(instance, nxt_gipa, channel);
  assert(inserted);
  return iter->second;
}

void RemoveInstanceInfo(VkInstance instance) {
  {
    std::lock_guard lock(instance_info_lock);
    g_instance_infos.erase(instance);
  }

  // Remove all physical devices associated with this instance
  {
    std::lock_guard lock(physical_device_to_instance_lock);
    for (auto it = g_physical_device_to_instance.begin(); it != g_physical_device_to_instance.end();) {
      if (it->second == instance) {
        it = g_physical_device_to_instance.erase(it);
      } else {
        ++it;
      }
    }
  }
}

InstanceInfo& GetInstanceInfo(VkPhysicalDevice physical_device) {
  return GetInstanceInfo(GetInstanceForPhysicalDevice(physical_device));
}

void AssociatePhysicalDeviceWithInstance(VkPhysicalDevice physical_device, VkInstance instance) {
  std::lock_guard lock(physical_device_to_instance_lock);
  g_physical_device_to_instance[physical_device] = instance;
}

VkInstance GetInstanceForPhysicalDevice(VkPhysicalDevice physical_device) {
  std::lock_guard lock(physical_device_to_instance_lock);
  return g_physical_device_to_instance.at(physical_device);
}

InstanceInfo& GetInstanceInfo(VkDevice device) {
  std::lock_guard lock(device_info_lock);
  return g_device_infos.at(device).instance_info;
}

DeviceInfo& GetDeviceInfo(VkDevice device) {
  std::lock_guard lock(device_info_lock);
  return g_device_infos.at(device);
}

DeviceInfo& GetDeviceInfo(VkCommandBuffer command_buffer) {
  return GetDeviceInfo(GetDeviceForCommandBuffer(command_buffer));
}

void SetDeviceInfo(VkDevice device, PFN_vkGetDeviceProcAddr nxt_gdpa, VkPhysicalDevice physical_device) {
  std::lock_guard lock(device_info_lock);
  VkInstance instance = g_physical_device_to_instance.at(physical_device);
  auto [_, inserted] = g_device_infos.try_emplace(device, nxt_gdpa, physical_device);
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

InstanceInfo::InstanceInfo(PFN_vkGetInstanceProcAddr nxt_gipa, std::shared_ptr<grpc::Channel> channel)
    : nxt_gipa(nxt_gipa), channel_(channel), stub_(channel) {
  command_stream = stub_.CallMethods(&client_context_);
}

InstanceInfo::~InstanceInfo() {
  command_stream->WritesDone();
  command_stream->Finish();
}

DeviceInfo::DeviceInfo(PFN_vkGetDeviceProcAddr nxt_gdpa, VkPhysicalDevice physical_device)
    : nxt_gdpa(nxt_gdpa),
      physical_device(physical_device),
      instance(GetInstanceForPhysicalDevice(physical_device)),
      instance_info(GetInstanceInfo(physical_device)) {}

}  // namespace vvk