#ifndef VVK_LAYER_CONTEXT_INSTANCE_H
#define VVK_LAYER_CONTEXT_INSTANCE_H

// clang-format off
#include "layer/wsi_support.h"
// clang-format on

#include <grpcpp/grpcpp.h>
#include <vulkan/utility/vk_dispatch_table.h>
#include <vulkan/vulkan_core.h>

#include <map>
#include <memory>

#include "commons/synchronized_bidi_stream.h"
#include "vvk_server.grpc.pb.h"
#include "vvk_server.pb.h"

namespace vvk {

class InstanceInfo {
 public:
  InstanceInfo(VkInstance instance, PFN_vkGetInstanceProcAddr nxt_gipa, std::shared_ptr<grpc::Channel> channel);

  // Dispatch table for calling down the chain
  const VkuInstanceDispatchTable& dispatch_table() const { return dispatch_table_; }

  VvkCommandClientBidiStream& command_stream() { return command_stream_; }
  VvkPresentationClientBidiStream& presentation_stream() { return presentation_stream_; }

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

  std::optional<VkSurfaceKHR> surface() const { return surface_; }
  void set_surface(VkSurfaceKHR surface) { surface_ = surface; }

 private:
  PFN_vkGetInstanceProcAddr nxt_gipa_;
  grpc::ClientContext command_stream_client_context_;
  grpc::ClientContext presentation_stream_client_context_;
  std::shared_ptr<grpc::Channel> channel_;
  vvk::server::VvkServer::Stub stub_;
  VvkCommandClientBidiStream command_stream_;
  VvkPresentationClientBidiStream presentation_stream_;
  std::map<void*, void*> local_to_remote_handle_;
  VkuInstanceDispatchTable dispatch_table_;
  std::optional<VkSurfaceKHR> surface_;
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
