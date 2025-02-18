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
  std::lock_guard lock(physical_device_to_instance_lock);
  return GetInstanceInfo(g_physical_device_to_instance.at(physical_device));
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
  return GetInstanceInfo(g_device_infos.at(device).instance);
}

DeviceInfo& GetDeviceInfo(VkDevice device) {
  std::lock_guard lock(device_info_lock);
  return g_device_infos.at(device);
}

void SetDeviceInfo(VkDevice device, PFN_vkGetDeviceProcAddr nxt_gdpa, VkPhysicalDevice physical_device) {
  std::lock_guard lock(device_info_lock);
  VkInstance instance = g_physical_device_to_instance.at(physical_device);
  g_device_infos[device] = {nxt_gdpa, physical_device, instance};
}

void RemoveDeviceInfo(VkDevice device) {
  std::lock_guard lock(device_info_lock);
  g_device_infos.erase(device);
}

InstanceInfo::InstanceInfo(PFN_vkGetInstanceProcAddr nxt_gipa, std::shared_ptr<grpc::Channel> channel)
    : nxt_gipa(nxt_gipa), channel_(channel), stub_(channel) {
  command_stream = stub_.CallMethods(&client_context_);
}

InstanceInfo::~InstanceInfo() {
  command_stream->WritesDone();
  command_stream->Finish();
}

}  // namespace vvk