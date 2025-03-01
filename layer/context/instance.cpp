#include "instance.h"

#include "layer/context/device.h"

namespace vvk {

namespace {
std::mutex instance_info_lock;
std::map<VkInstance, InstanceInfo> g_instance_infos;
std::mutex physical_device_to_instance_lock;
std::map<VkPhysicalDevice, VkInstance> g_physical_device_to_instance;
}  // namespace

InstanceInfo::InstanceInfo(PFN_vkGetInstanceProcAddr nxt_gipa, std::shared_ptr<grpc::Channel> channel)
    : nxt_gipa(nxt_gipa), channel_(channel), stub_(channel) {
  command_stream_ = stub_.CallMethods(&client_context_);
}

InstanceInfo::~InstanceInfo() {
  command_stream_->WritesDone();
  command_stream_->Finish();
}

InstanceInfo& GetInstanceInfo(VkInstance instance) {
  std::lock_guard lock(instance_info_lock);
  return g_instance_infos.at(instance);
}

InstanceInfo& SetInstanceInfo(VkInstance instance, PFN_vkGetInstanceProcAddr nxt_gipa,
                              std::shared_ptr<grpc::Channel> channel) {
  std::lock_guard lock(instance_info_lock);
  auto [iter, inserted] = g_instance_infos.try_emplace(instance, nxt_gipa, channel);
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

InstanceInfo& GetInstanceInfo(VkPhysicalDevice physical_device) {
  return GetInstanceInfo(GetInstanceForPhysicalDevice(physical_device));
}

InstanceInfo& GetInstanceInfo(VkDevice device) { return GetDeviceInfo(device).instance_info; }

void AssociatePhysicalDeviceWithInstance(VkPhysicalDevice physical_device, VkInstance instance) {
  std::lock_guard lock(physical_device_to_instance_lock);
  auto [_, inserted] = g_physical_device_to_instance.try_emplace(physical_device, instance);
  if (!inserted) {
    throw std::runtime_error("This VkPhysicalDevice already has a VkInstance associated with it");
  }
}

VkInstance GetInstanceForPhysicalDevice(VkPhysicalDevice physical_device) {
  std::lock_guard lock(physical_device_to_instance_lock);
  return g_physical_device_to_instance.at(physical_device);
}

}  // namespace vvk
