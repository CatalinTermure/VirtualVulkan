#include "functions.h"

#include <grpcpp/grpcpp.h>
#include <spdlog/spdlog.h>
#include <vulkan/vk_layer.h>
#include <vvk_server.grpc.pb.h>
#include <vvk_server.pb.h>
#include <vvk_types.pb.h>

#include <cassert>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <string_view>
#include <utility>

#include "commons/remote_call.h"
#include "layer/context.h"

namespace vvk {

namespace {

template <typename FooType, typename RetType, typename... Args>
RetType CallDownInstanceFunc(std::string_view func_name, VkInstance instance, Args... args) {
  FooType nxt_func = reinterpret_cast<FooType>(GetInstanceInfo(instance).nxt_gipa(instance, func_name.data()));
  if (!nxt_func) {
    spdlog::critical("Failed to fetch {} from next layer", func_name);
  }

  return nxt_func(instance, args...);
}

template <typename FooType, typename RetType, typename... Args>
RetType CallDownDeviceFunc(std::string_view func_name, VkDevice device, Args... args) {
  FooType nxt_func = reinterpret_cast<FooType>(GetDeviceInfo(device).nxt_gdpa(device, func_name.data()));
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
  return GetInstanceInfo(instance).nxt_gipa(instance, pName);
}
PFN_vkVoidFunction DefaultGetDeviceProcAddr(VkDevice device, const char* pName) {
  return GetDeviceInfo(device).nxt_gdpa(device, pName);
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

  InstanceInfo& instance_info =
      SetInstanceInfo(*pInstance, nxt_gipa, grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

  // call remote create instance
  {
    // remove loader instance create info from the pNext chain
    // the loader seems to insert these structs at the beginning of the pNext chain
    // so we can remove it by copying the instance create info and skipping the loader instance create info structs
    VkInstanceCreateInfo remote_create_info = *pCreateInfo;
    RemoveStructsFromChain(reinterpret_cast<VkBaseInStructure*>(&remote_create_info),
                           VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO);

    auto reader_writer = instance_info.command_stream.get();

    // We don't want to overwrite the local instance handle with the remote one
    VkInstance remote_instance = *pInstance;
    PackAndCallVkCreateInstance(reader_writer, &remote_create_info, pAllocator, &remote_instance);
    instance_info.SetRemoteHandle(*pInstance, remote_instance);
  }

  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator) {
  spdlog::trace("DestroyInstance");

  InstanceInfo& instance_info = GetInstanceInfo(instance);
  CallDownInstanceFunc<PFN_vkDestroyInstance, void>("vkDestroyInstance", instance, pAllocator);

  auto reader_writer = instance_info.command_stream.get();
  PackAndCallVkDestroyInstance(reader_writer, instance_info.GetRemoteHandle(instance), pAllocator);

  RemoveInstanceInfo(instance);
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
      AssociatePhysicalDeviceWithInstance(pPhysicalDevices[i], instance);
    }
  }

  return result;
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice,
                                                       VkPhysicalDeviceProperties* pProperties) {
  PackAndCallVkGetPhysicalDeviceProperties(GetInstanceInfo(physicalDevice).command_stream.get(), physicalDevice,
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

  InstanceInfo& instance_info = GetInstanceInfo(physicalDevice);

  PFN_vkCreateDevice nxtCreateDevice =
      reinterpret_cast<PFN_vkCreateDevice>(instance_info.nxt_gipa(nullptr, "vkCreateDevice"));
  if (!nxtCreateDevice) {
    spdlog::error("Failed to fetch vkCreateDevice from next layer");
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  VkResult result = nxtCreateDevice(physicalDevice, pCreateInfo, pAllocator, pDevice);

  SetDeviceInfo(*pDevice, nxt_gdpa, physicalDevice);

  {
    VkDeviceCreateInfo remote_create_info = *pCreateInfo;
    RemoveStructsFromChain(reinterpret_cast<VkBaseInStructure*>(&remote_create_info),
                           VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO);
    VkDevice remote_device = *pDevice;

    PackAndCallVkCreateDevice(instance_info.command_stream.get(), physicalDevice, &remote_create_info, pAllocator,
                              &remote_device);
    instance_info.SetRemoteHandle(*pDevice, remote_device);
  }

  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) {
  CallDownDeviceFunc<PFN_vkDestroyDevice, void>("vkDestroyDevice", device, pAllocator);

  InstanceInfo& instance_info = GetInstanceInfo(device);

  auto reader_writer = instance_info.command_stream.get();
  PackAndCallVkDestroyDevice(reader_writer, instance_info.GetRemoteHandle(device), pAllocator);

  RemoveDeviceInfo(device);
}

VKAPI_ATTR VkResult VKAPI_CALL EnumerateInstanceExtensionProperties(const char* pLayerName, uint32_t* pPropertyCount,
                                                                    VkExtensionProperties* pProperties) {
  if (!pLayerName || strcmp(pLayerName, "VK_LAYER_VVK_virtual_vulkan") != 0) {
    return VK_ERROR_LAYER_NOT_PRESENT;
  }

  // TODO: implement this
  assert(false);

  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL EnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice,
                                                                  const char* pLayerName, uint32_t* pPropertyCount,
                                                                  VkExtensionProperties* pProperties) {
  if (!pLayerName || strcmp(pLayerName, "VK_LAYER_VVK_virtual_vulkan") != 0) {
    VkInstance instance = GetInstanceForPhysicalDevice(physicalDevice);
    PFN_vkGetInstanceProcAddr nxt_gipa = GetInstanceInfo(instance).nxt_gipa;
    PFN_vkEnumerateDeviceExtensionProperties nxtEnumerateDeviceExtensionProperties =
        reinterpret_cast<PFN_vkEnumerateDeviceExtensionProperties>(
            nxt_gipa(instance, "vkEnumerateDeviceExtensionProperties"));
    if (!nxtEnumerateDeviceExtensionProperties) {
      spdlog::error("Failed to fetch vkEnumerateDeviceExtensionProperties from next layer");
      return VK_ERROR_INITIALIZATION_FAILED;
    }

    return nxtEnumerateDeviceExtensionProperties(physicalDevice, pLayerName, pPropertyCount, pProperties);
  }

  auto command_stream = GetInstanceInfo(physicalDevice).command_stream.get();

  return PackAndCallVkEnumerateDeviceExtensionProperties(command_stream, physicalDevice, pLayerName, pPropertyCount,
                                                         pProperties);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice,
                                                             VkPhysicalDeviceMemoryProperties* pMemoryProperties) {
  // TODO: investigate additional steps needed for this function
  auto command_stream = GetInstanceInfo(physicalDevice).command_stream.get();
  return PackAndCallVkGetPhysicalDeviceMemoryProperties(command_stream, physicalDevice, pMemoryProperties);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice,
                                                     VkPhysicalDeviceFeatures* pFeatures) {
  auto command_stream = GetInstanceInfo(physicalDevice).command_stream.get();
  return PackAndCallVkGetPhysicalDeviceFeatures(command_stream, physicalDevice, pFeatures);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice,
                                                                  uint32_t* pQueueFamilyPropertyCount,
                                                                  VkQueueFamilyProperties* pQueueFamilyProperties) {
  auto command_stream = GetInstanceInfo(physicalDevice).command_stream.get();
  return PackAndCallVkGetPhysicalDeviceQueueFamilyProperties(command_stream, physicalDevice, pQueueFamilyPropertyCount,
                                                             pQueueFamilyProperties);
}

VKAPI_ATTR void VKAPI_CALL GetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex,
                                          VkQueue* pQueue) {
  InstanceInfo& instance_info = GetInstanceInfo(device);

  CallDownDeviceFunc<PFN_vkGetDeviceQueue, void>("vkGetDeviceQueue", device, queueFamilyIndex, queueIndex, pQueue);
  VkQueue remote_queue = VK_NULL_HANDLE;
  PackAndCallVkGetDeviceQueue(instance_info.command_stream.get(), instance_info.GetRemoteHandle(device),
                              queueFamilyIndex, queueIndex, &remote_queue);
  instance_info.SetRemoteHandle(*pQueue, remote_queue);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo,
                                           const VkAllocationCallbacks* pAllocator, VkFence* pFence) {
  InstanceInfo& instance_info = GetInstanceInfo(device);
  VkResult result =
      CallDownDeviceFunc<PFN_vkCreateFence, VkResult>("vkCreateFence", device, pCreateInfo, pAllocator, pFence);
  if (result != VK_SUCCESS) {
    return result;
  }
  VkFence remote_fence = VK_NULL_HANDLE;
  result = PackAndCallVkCreateFence(instance_info.command_stream.get(), instance_info.GetRemoteHandle(device),
                                    pCreateInfo, pAllocator, &remote_fence);
  if (result != VK_SUCCESS) {
    CallDownDeviceFunc<PFN_vkDestroyFence, void>("vkDestroyFence", device, *pFence, pAllocator);
    return result;
  }
  instance_info.SetRemoteHandle(*pFence, remote_fence);
  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator) {
  InstanceInfo& instance_info = GetInstanceInfo(device);
  CallDownDeviceFunc<PFN_vkDestroyFence, void>("vkDestroyFence", device, fence, pAllocator);
  PackAndCallVkDestroyFence(instance_info.command_stream.get(), instance_info.GetRemoteHandle(device),
                            instance_info.GetRemoteHandle(fence), pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo,
                                               const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore) {
  InstanceInfo& instance_info = GetInstanceInfo(device);
  VkResult result = CallDownDeviceFunc<PFN_vkCreateSemaphore, VkResult>("vkCreateSemaphore", device, pCreateInfo,
                                                                        pAllocator, pSemaphore);
  if (result != VK_SUCCESS) {
    return result;
  }
  VkSemaphore remote_semaphore = VK_NULL_HANDLE;
  result = PackAndCallVkCreateSemaphore(instance_info.command_stream.get(), instance_info.GetRemoteHandle(device),
                                        pCreateInfo, pAllocator, &remote_semaphore);
  if (result != VK_SUCCESS) {
    CallDownDeviceFunc<PFN_vkDestroySemaphore, void>("vkDestroySemaphore", device, *pSemaphore, pAllocator);
    return result;
  }
  instance_info.SetRemoteHandle(*pSemaphore, remote_semaphore);
  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroySemaphore(VkDevice device, VkSemaphore semaphore,
                                            const VkAllocationCallbacks* pAllocator) {
  InstanceInfo& instance_info = GetInstanceInfo(device);
  CallDownDeviceFunc<PFN_vkDestroySemaphore, void>("vkDestroySemaphore", device, semaphore, pAllocator);
  PackAndCallVkDestroySemaphore(instance_info.command_stream.get(), instance_info.GetRemoteHandle(device),
                                instance_info.GetRemoteHandle(semaphore), pAllocator);
}

}  // namespace vvk