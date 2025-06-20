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

class Instance {
 public:
  Instance(VkInstance instance, PFN_vkGetInstanceProcAddr nxt_gipa, std::shared_ptr<grpc::Channel> channel);

  // Dispatch table for calling down the chain
  const VkuInstanceDispatchTable& dispatch_table() const { return dispatch_table_; }

  VvkCommandClientBidiStream& command_stream() { return command_stream_; }
  server::VvkServer::Stub& stub() { return stub_; }

  template <typename T>
  T GetRemoteHandle(T local_handle) const {
    return reinterpret_cast<T>(local_to_remote_handle_.at(reinterpret_cast<void*>(local_handle)));
  }

  template <typename T>
  void SetRemoteHandle(T local_handle, T remote_handle) {
    local_to_remote_handle_.emplace(reinterpret_cast<void*>(local_handle), reinterpret_cast<void*>(remote_handle));
  }

  void RemoveRemoteHandle(void* local_handle) { local_to_remote_handle_.erase(local_handle); }

  Instance(const Instance&) = delete;
  Instance& operator=(const Instance&) = delete;

  std::optional<VkSurfaceKHR> surface() const { return surface_; }
  void set_surface(VkSurfaceKHR surface) { surface_ = surface; }

 private:
  PFN_vkGetInstanceProcAddr nxt_gipa_;
  grpc::ClientContext command_stream_client_context_;
  std::shared_ptr<grpc::Channel> channel_;
  server::VvkServer::Stub stub_;
  VvkCommandClientBidiStream command_stream_;
  std::map<void*, void*> local_to_remote_handle_;
  VkuInstanceDispatchTable dispatch_table_;
  std::optional<VkSurfaceKHR> surface_;
};

Instance& GetInstanceInfo(VkInstance instance);
Instance& GetInstanceInfo(VkPhysicalDevice physical_device);
Instance& GetInstanceInfo(VkDevice device);
Instance& SetInstanceInfo(VkInstance instance, PFN_vkGetInstanceProcAddr nxt_gipa,
                          std::shared_ptr<grpc::Channel> channel);
void RemoveInstanceInfo(VkInstance instance);

void AssociatePhysicalDeviceWithInstance(VkPhysicalDevice physical_device, VkInstance instance);
VkInstance GetInstanceForPhysicalDevice(VkPhysicalDevice physical_device);

}  // namespace vvk

#endif  // VVK_LAYER_CONTEXT_INSTANCE_H
