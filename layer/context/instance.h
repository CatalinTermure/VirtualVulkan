#ifndef VVK_LAYER_CONTEXT_INSTANCE_H
#define VVK_LAYER_CONTEXT_INSTANCE_H

#include <grpcpp/grpcpp.h>
#include <vulkan/vulkan_core.h>

#include <map>
#include <memory>

#include "vvk_server.grpc.pb.h"
#include "vvk_server.pb.h"

namespace vvk {

class InstanceInfo {
 public:
  PFN_vkGetInstanceProcAddr nxt_gipa;

  InstanceInfo(PFN_vkGetInstanceProcAddr nxt_gipa, std::shared_ptr<grpc::Channel> channel);

  grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* command_stream() {
    return command_stream_.get();
  }

  template <typename T>
  T GetRemoteHandle(T local_handle) const {
    return reinterpret_cast<T>(local_to_remote_handle_.at(reinterpret_cast<void*>(local_handle)));
  }

  template <typename T>
  void SetRemoteHandle(T local_handle, T remote_handle) {
    local_to_remote_handle_.emplace(reinterpret_cast<void*>(local_handle), reinterpret_cast<void*>(remote_handle));
  }

  InstanceInfo(const InstanceInfo&) = delete;
  InstanceInfo& operator=(const InstanceInfo&) = delete;

  ~InstanceInfo();

 private:
  std::unique_ptr<grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>> command_stream_;
  grpc::ClientContext client_context_;
  std::shared_ptr<grpc::Channel> channel_;
  vvk::server::VvkServer::Stub stub_;
  std::map<void*, void*> local_to_remote_handle_;
};

InstanceInfo& GetInstanceInfo(VkInstance instance);
InstanceInfo& GetInstanceInfo(VkPhysicalDevice physical_device);
InstanceInfo& GetInstanceInfo(VkDevice device);
InstanceInfo& SetInstanceInfo(VkInstance instance, PFN_vkGetInstanceProcAddr nxt_gipa,
                              std::shared_ptr<grpc::Channel> channel);
void RemoveInstanceInfo(VkInstance instance);

void AssociatePhysicalDeviceWithInstance(VkPhysicalDevice physical_device, VkInstance instance);
VkInstance GetInstanceForPhysicalDevice(VkPhysicalDevice physical_device);

}  // namespace vvk

#endif  // VVK_LAYER_CONTEXT_INSTANCE_H
