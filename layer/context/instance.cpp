#include "instance.h"

#include "layer/context/device.h"

namespace vvk {

namespace {
std::mutex instance_info_lock;
std::map<VkInstance, Instance> g_instance_infos;
std::mutex physical_device_to_instance_lock;
std::map<VkPhysicalDevice, VkInstance> g_physical_device_to_instance;
}  // namespace

Instance::Instance(VkInstance instance, PFN_vkGetInstanceProcAddr nxt_gipa,
                           std::shared_ptr<grpc::Channel> channel)
    : nxt_gipa_(nxt_gipa),
      channel_(channel),
      stub_(channel),
      command_stream_(stub_.CallMethods(&command_stream_client_context_)) {
  vkuInitInstanceDispatchTable(instance, &dispatch_table_, nxt_gipa);
  dispatch_table_.CreateDevice = reinterpret_cast<PFN_vkCreateDevice>(nxt_gipa(instance, "vkCreateDevice"));
}

Instance& GetInstanceInfo(VkInstance instance) {
  std::lock_guard lock(instance_info_lock);
  return g_instance_infos.at(instance);
}

Instance& SetInstanceInfo(VkInstance instance, PFN_vkGetInstanceProcAddr nxt_gipa,
                              std::shared_ptr<grpc::Channel> channel) {
  std::lock_guard lock(instance_info_lock);
  auto [iter, inserted] = g_instance_infos.try_emplace(instance, instance, nxt_gipa, channel);
  if (!inserted) {
    throw std::runtime_error("This VkInstance already has an InstanceInfo associated with it");
  }
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

Instance& GetInstanceInfo(VkPhysicalDevice physical_device) {
  return GetInstanceInfo(GetInstanceForPhysicalDevice(physical_device));
}

Instance& GetInstanceInfo(VkDevice device) { return GetDeviceInfo(device).instance_info(); }

void AssociatePhysicalDeviceWithInstance(VkPhysicalDevice physical_device, VkInstance instance) {
  std::lock_guard lock(physical_device_to_instance_lock);
  auto [_, inserted] = g_physical_device_to_instance.try_emplace(physical_device, instance);
  if (!inserted && g_physical_device_to_instance.at(physical_device) != instance) {
    throw std::runtime_error("This VkPhysicalDevice already has a VkInstance associated with it");
  }
}

VkInstance GetInstanceForPhysicalDevice(VkPhysicalDevice physical_device) {
  std::lock_guard lock(physical_device_to_instance_lock);
  return g_physical_device_to_instance.at(physical_device);
}

}  // namespace vvk
