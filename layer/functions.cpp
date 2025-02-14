#include "layer/functions.h"

#include <grpcpp/grpcpp.h>
#include <spdlog/spdlog.h>
#include <vulkan/vk_layer.h>
#include <vvk_server.grpc.pb.h>
#include <vvk_server.pb.h>
#include <vvk_types.pb.h>

#include <cassert>
#include <functional>
#include <memory>
#include <string_view>
#include <unordered_map>
#include <utility>

#include "commons/remote_call.h"

namespace vvk {

namespace {

using vvk::server::VvkServer;

class InstanceInfo {
 public:
  PFN_vkGetInstanceProcAddr nxt_gipa;
  grpc::ClientContext client_context;
  std::shared_ptr<grpc::Channel> channel;
  VvkServer::Stub stub;
  std::unique_ptr<grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>> command_stream;

  InstanceInfo(PFN_vkGetInstanceProcAddr nxt_gipa, std::shared_ptr<grpc::Channel> channel)
      : nxt_gipa(nxt_gipa), channel(channel), stub(channel) {
    command_stream = stub.CallMethods(&client_context);
  }

  InstanceInfo(const InstanceInfo&) = delete;
  InstanceInfo& operator=(const InstanceInfo&) = delete;

  ~InstanceInfo() {
    command_stream->WritesDone();
    command_stream->Finish();
  }
};

std::unordered_map<VkInstance, InstanceInfo> g_instance_infos;
std::unordered_map<VkPhysicalDevice, VkInstance> g_physical_device_to_instance;

template <typename FooType, typename RetType, typename... Args>
RetType CallDownInstanceFunc(std::string_view func_name, VkInstance instance, Args... args) {
  FooType nxt_func = reinterpret_cast<FooType>(g_instance_infos.at(instance).nxt_gipa(instance, func_name.data()));
  if (!nxt_func) {
    spdlog::error("Failed to fetch {} from next layer", func_name);
    return VK_ERROR_UNKNOWN;
  }

  return nxt_func(instance, args...);
}

}  // namespace

VKAPI_ATTR VkResult VKAPI_CALL CreateInstance(const VkInstanceCreateInfo* pCreateInfo,
                                              const VkAllocationCallbacks* pAllocator, VkInstance* pInstance) {
  spdlog::trace("CreateInstance");

  // TODO: what from the pNext chain do we need to pass to remote server?

  // find the next layer's GetInstanceProcAddr(GIPA) function
  const void* p_next_chain = pCreateInfo->pNext;
  const VkLayerInstanceCreateInfo* layer_instance_info = nullptr;
  while (p_next_chain) {
    layer_instance_info = reinterpret_cast<const VkLayerInstanceCreateInfo*>(p_next_chain);
    p_next_chain = layer_instance_info->pNext;
    if (layer_instance_info->sType != VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO) {
      continue;
    }
    spdlog::trace("layer_instance_info->function: {}", static_cast<int>(layer_instance_info->function));
    if (layer_instance_info->function == VK_LAYER_LINK_INFO) {
      break;
    }
  }
  PFN_vkGetInstanceProcAddr nxt_gipa = layer_instance_info->u.pLayerInfo->pfnNextGetInstanceProcAddr;
  assert(nxt_gipa);

  // advance the linked list for the next layer
  {
    VkLayerInstanceCreateInfo* layer_instance_info_mut = const_cast<VkLayerInstanceCreateInfo*>(layer_instance_info);
    layer_instance_info_mut->u.pLayerInfo = layer_instance_info->u.pLayerInfo->pNext;
  }

  PFN_vkCreateInstance nxtCreateInstance =
      reinterpret_cast<PFN_vkCreateInstance>(nxt_gipa(nullptr, "vkCreateInstance"));
  if (!nxtCreateInstance) {
    spdlog::error("Failed to fetch vkCreateInstance from next layer");
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  VkResult result = nxtCreateInstance(pCreateInfo, pAllocator, pInstance);

  // must be this way due to copy/move constructors of grpc objects
  g_instance_infos.emplace(
      std::piecewise_construct, std::forward_as_tuple(*pInstance),
      std::forward_as_tuple(nxt_gipa, grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials())));

  // call remote create instance
  {
    // remove loader instance create info from the pNext chain
    // the loader seems to insert these structs at the beginning of the pNext chain
    // so we can remove it by copying the instance create info and skipping the loader instance create info structs
    VkInstanceCreateInfo remote_create_info = *pCreateInfo;
    VkBaseInStructure* next_struct = reinterpret_cast<VkBaseInStructure*>(const_cast<void*>(remote_create_info.pNext));
    VkBaseInStructure* curr_struct = reinterpret_cast<VkBaseInStructure*>(&remote_create_info);
    while (next_struct) {
      spdlog::debug("next_struct->sType: {}", static_cast<int>(next_struct->sType));
      if (next_struct->sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO) {
        curr_struct->pNext = next_struct->pNext;
        next_struct = const_cast<VkBaseInStructure*>(next_struct->pNext);
      } else {
        curr_struct = reinterpret_cast<VkBaseInStructure*>(next_struct);
        next_struct = const_cast<VkBaseInStructure*>(next_struct->pNext);
      }
    }

    auto reader_writer = g_instance_infos.at(*pInstance).command_stream.get();

    // We don't want to overwrite the local instance handle with the remote one
    VkInstance remote_instance = *pInstance;
    PackAndCallVkCreateInstance(reader_writer, &remote_create_info, pAllocator, &remote_instance);
  }

  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator) {
  spdlog::trace("DestroyInstance");

  // find the next layer's GetInstanceProcAddr(GIPA) function
  PFN_vkGetInstanceProcAddr nxt_gipa = g_instance_infos.at(instance).nxt_gipa;

  PFN_vkDestroyInstance nxtDestroyInstance =
      reinterpret_cast<PFN_vkDestroyInstance>(nxt_gipa(instance, "vkDestroyInstance"));
  if (!nxtDestroyInstance) {
    spdlog::error("Failed to fetch vkDestroyInstance from next layer");
    return;
  }

  nxtDestroyInstance(instance, pAllocator);

  auto reader_writer = g_instance_infos.at(instance).command_stream.get();
  PackAndCallVkDestroyInstance(reader_writer, instance, pAllocator);

  g_instance_infos.erase(instance);
}

VKAPI_ATTR VkResult VKAPI_CALL EnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount,
                                                        VkPhysicalDevice* pPhysicalDevices) {
  spdlog::trace("EnumeratePhysicalDevices");

  VkResult result = CallDownInstanceFunc<PFN_vkEnumeratePhysicalDevices, VkResult>(
      "vkEnumeratePhysicalDevices", instance, pPhysicalDeviceCount, pPhysicalDevices);
  if (result != VK_SUCCESS) {
    return result;
  }

  if (pPhysicalDevices != nullptr) {
    for (uint32_t i = 0; i < *pPhysicalDeviceCount; i++) {
      g_physical_device_to_instance[pPhysicalDevices[i]] = instance;
    }
  }

  return result;
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice,
                                                       VkPhysicalDeviceProperties* pProperties) {
  VkInstance instance = g_physical_device_to_instance.at(physicalDevice);

  PackAndCallVkGetPhysicalDeviceProperties(g_instance_infos.at(instance).command_stream.get(), physicalDevice,
                                           pProperties);
}

}  // namespace vvk