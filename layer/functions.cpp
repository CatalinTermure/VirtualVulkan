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

struct DeviceInfo {
  PFN_vkGetDeviceProcAddr nxt_gdpa;
  VkPhysicalDevice physical_device;
  VkInstance instance;
};

std::unordered_map<VkInstance, InstanceInfo> g_instance_infos;
std::unordered_map<VkDevice, DeviceInfo> g_device_infos;
std::unordered_map<VkPhysicalDevice, VkInstance> g_physical_device_to_instance;

template <typename FooType, typename RetType, typename... Args>
RetType CallDownInstanceFunc(std::string_view func_name, VkInstance instance, Args... args) {
  FooType nxt_func = reinterpret_cast<FooType>(g_instance_infos.at(instance).nxt_gipa(instance, func_name.data()));
  if (!nxt_func) {
    spdlog::critical("Failed to fetch {} from next layer", func_name);
  }

  return nxt_func(instance, args...);
}

template <typename FooType, typename RetType, typename... Args>
RetType CallDownDeviceFunc(std::string_view func_name, VkDevice device, Args... args) {
  FooType nxt_func = reinterpret_cast<FooType>(g_device_infos.at(device).nxt_gdpa(device, func_name.data()));
  if (!nxt_func) {
    spdlog::critical("Failed to fetch {} from next layer", func_name);
  }

  return nxt_func(device, args...);
}

template <typename T, VkStructureType sType>
T* FindLayerLinkInfo(const void* p_next_chain) {
  const T* layer_info = nullptr;
  while (p_next_chain) {
    layer_info = reinterpret_cast<const T*>(p_next_chain);
    p_next_chain = layer_info->pNext;
    if (layer_info->sType != sType) {
      continue;
    }
    if (layer_info->function == VK_LAYER_LINK_INFO) {
      break;
    }
  }
  return const_cast<T*>(layer_info);
}

void RemoveStructsFromChain(VkBaseInStructure* base_struct, VkStructureType sType) {
  VkBaseInStructure* next_struct = const_cast<VkBaseInStructure*>(base_struct->pNext);
  VkBaseInStructure* curr_struct = base_struct;
  while (next_struct) {
    spdlog::trace("next_struct->sType: {}", static_cast<int>(next_struct->sType));
    if (next_struct->sType == sType) {
      curr_struct->pNext = next_struct->pNext;
      next_struct = const_cast<VkBaseInStructure*>(next_struct->pNext);
    } else {
      curr_struct = next_struct;
      next_struct = const_cast<VkBaseInStructure*>(next_struct->pNext);
    }
  }
}

}  // namespace

PFN_vkVoidFunction DefaultGetInstanceProcAddr(VkInstance instance, const char* pName) {
  return g_instance_infos.at(instance).nxt_gipa(instance, pName);
}
PFN_vkVoidFunction DefaultGetDeviceProcAddr(VkDevice device, const char* pName) {
  return g_device_infos.at(device).nxt_gdpa(device, pName);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateInstance(const VkInstanceCreateInfo* pCreateInfo,
                                              const VkAllocationCallbacks* pAllocator, VkInstance* pInstance) {
  spdlog::trace("CreateInstance");

  // TODO: what from the pNext chain do we need to pass to remote server?

  // find the next layer's GetInstanceProcAddr(GIPA) function
  const void* p_next_chain = pCreateInfo->pNext;
  const VkLayerInstanceCreateInfo* layer_instance_info =
      FindLayerLinkInfo<VkLayerInstanceCreateInfo, VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO>(p_next_chain);
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
    RemoveStructsFromChain(reinterpret_cast<VkBaseInStructure*>(&remote_create_info),
                           VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO);

    auto reader_writer = g_instance_infos.at(*pInstance).command_stream.get();

    // We don't want to overwrite the local instance handle with the remote one
    VkInstance remote_instance = *pInstance;
    PackAndCallVkCreateInstance(reader_writer, &remote_create_info, pAllocator, &remote_instance);
  }

  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator) {
  spdlog::trace("DestroyInstance");

  PFN_vkGetInstanceProcAddr nxt_gipa = g_instance_infos.at(instance).nxt_gipa;

  CallDownInstanceFunc<PFN_vkDestroyInstance, void>("vkDestroyInstance", instance, pAllocator);

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

VKAPI_ATTR VkResult VKAPI_CALL CreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo,
                                            const VkAllocationCallbacks* pAllocator, VkDevice* pDevice) {
  // find the next layer's GetDeviceProcAddr(GDPA) function
  const void* p_next_chain = pCreateInfo->pNext;
  const VkLayerDeviceCreateInfo* layer_device_info =
      FindLayerLinkInfo<VkLayerDeviceCreateInfo, VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO>(p_next_chain);
  PFN_vkGetDeviceProcAddr nxt_gdpa = layer_device_info->u.pLayerInfo->pfnNextGetDeviceProcAddr;
  assert(nxt_gdpa);

  // advance the linked list for the next layer
  {
    VkLayerDeviceCreateInfo* layer_device_info_mut = const_cast<VkLayerDeviceCreateInfo*>(layer_device_info);
    layer_device_info_mut->u.pLayerInfo = layer_device_info->u.pLayerInfo->pNext;
  }

  const InstanceInfo& instance_info = g_instance_infos.at(g_physical_device_to_instance.at(physicalDevice));

  PFN_vkCreateDevice nxtCreateDevice =
      reinterpret_cast<PFN_vkCreateDevice>(instance_info.nxt_gipa(nullptr, "vkCreateDevice"));
  if (!nxtCreateDevice) {
    spdlog::error("Failed to fetch vkCreateDevice from next layer");
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  VkResult result = nxtCreateDevice(physicalDevice, pCreateInfo, pAllocator, pDevice);

  DeviceInfo device_info;
  device_info.nxt_gdpa = nxt_gdpa;
  device_info.physical_device = physicalDevice;
  device_info.instance = g_physical_device_to_instance.at(physicalDevice);

  g_device_infos[*pDevice] = device_info;

  {
    VkDeviceCreateInfo remote_create_info = *pCreateInfo;
    RemoveStructsFromChain(reinterpret_cast<VkBaseInStructure*>(&remote_create_info),
                           VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO);
    VkDevice remote_device = *pDevice;

    PackAndCallVkCreateDevice(instance_info.command_stream.get(), physicalDevice, &remote_create_info, pAllocator,
                              &remote_device);
  }

  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) {
  PFN_vkGetDeviceProcAddr nxt_gdpa = g_device_infos.at(device).nxt_gdpa;

  CallDownDeviceFunc<PFN_vkDestroyDevice, void>("vkDestroyDevice", device, pAllocator);

  auto reader_writer = g_instance_infos.at(g_device_infos.at(device).instance).command_stream.get();
  PackAndCallVkDestroyDevice(reader_writer, device, pAllocator);

  g_device_infos.erase(device);
}
}  // namespace vvk