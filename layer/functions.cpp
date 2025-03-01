#include "functions.h"

#include <grpcpp/grpcpp.h>
#include <spdlog/spdlog.h>
#include <vk_mem_alloc.h>
#include <vulkan/vk_icd.h>
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
#include <type_traits>
#include <utility>

#include "commons/remote_call.h"
#include "layer/context/device.h"
#include "layer/context/instance.h"
#include "layer/context/swapchain.h"

namespace vvk {

namespace {

template <typename FooType, typename... Args>
std::result_of_t<FooType(VkInstance, Args...)> CallDownInstanceFunc(std::string_view func_name, VkInstance instance,
                                                                    Args... args) {
  FooType nxt_func = reinterpret_cast<FooType>(GetInstanceInfo(instance).nxt_gipa(instance, func_name.data()));
  if (!nxt_func) {
    spdlog::critical("Failed to fetch {} from next layer", func_name);
  }

  return nxt_func(instance, args...);
}

template <typename FooType, typename... Args>
std::result_of_t<FooType(VkDevice, Args...)> CallDownDeviceFunc(std::string_view func_name, VkDevice device,
                                                                Args... args) {
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

void* AllocateHandle() {
  void* handle = malloc(sizeof(VK_LOADER_DATA));
  set_loader_magic_value(handle);
  return handle;
}

}  // namespace

VKAPI_ATTR VkResult VKAPI_CALL CreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo,
                                                  const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain) {
  spdlog::trace("CreateSwapchainKHR");

  VkResult result =
      CallDownDeviceFunc<PFN_vkCreateSwapchainKHR>("vkCreateSwapchainKHR", device, pCreateInfo, pAllocator, pSwapchain);
  if (result != VK_SUCCESS) {
    return result;
  }

  uint32_t swapchain_image_count = 0;
  std::vector<VkImage> client_swapchain_images;
  result = CallDownDeviceFunc<PFN_vkGetSwapchainImagesKHR>("vkGetSwapchainImagesKHR", device, *pSwapchain,
                                                           &swapchain_image_count, nullptr);
  if (result != VK_SUCCESS) {
    CallDownDeviceFunc<PFN_vkDestroySwapchainKHR>("vkDestroySwapchainKHR", device, *pSwapchain, pAllocator);
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  client_swapchain_images.resize(swapchain_image_count);
  result = CallDownDeviceFunc<PFN_vkGetSwapchainImagesKHR>("vkGetSwapchainImagesKHR", device, *pSwapchain,
                                                           &swapchain_image_count, client_swapchain_images.data());
  if (result != VK_SUCCESS) {
    CallDownDeviceFunc<PFN_vkDestroySwapchainKHR>("vkDestroySwapchainKHR", device, *pSwapchain, pAllocator);
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  DeviceInfo& device_info = GetDeviceInfo(device);
  InstanceInfo& instance_info = device_info.instance_info;
  auto reader_writer = instance_info.command_stream();

  if (pCreateInfo->oldSwapchain) {
    RemoveSwapchainInfo(pCreateInfo->oldSwapchain);
  }

  SwapchainInfo& swapchain_info = SetSwapchainInfo(*pSwapchain, device, device_info.allocator_);

  VkImageCreateInfo image_create_info = {
      .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .imageType = VK_IMAGE_TYPE_2D,
      .format = pCreateInfo->imageFormat,
      .extent = {pCreateInfo->imageExtent.width, pCreateInfo->imageExtent.height, 1},
      .mipLevels = 1,
      .arrayLayers = pCreateInfo->imageArrayLayers,
      .samples = VK_SAMPLE_COUNT_1_BIT,
      .tiling = VK_IMAGE_TILING_OPTIMAL,
      .usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | pCreateInfo->imageUsage,
      .sharingMode = pCreateInfo->imageSharingMode,
      .queueFamilyIndexCount = pCreateInfo->queueFamilyIndexCount,
      .pQueueFamilyIndices = pCreateInfo->pQueueFamilyIndices,
      .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
  };

  VmaAllocationCreateInfo alloc_create_info = {
      .flags = 0,
      .usage = VMA_MEMORY_USAGE_GPU_ONLY,
      .requiredFlags = 0,
      .preferredFlags = 0,
      .memoryTypeBits = 0,
      .pool = VK_NULL_HANDLE,
      .pUserData = nullptr,
      .priority = 0.0f,
  };

  VkDevice remote_device = instance_info.GetRemoteHandle(device);
  for (VkImage client_image : client_swapchain_images) {
    VkImage server_image;
    server_image = swapchain_info.CreateImage(image_create_info, alloc_create_info);
    if (result != VK_SUCCESS) {
      CallDownDeviceFunc<PFN_vkDestroySwapchainKHR>("vkDestroySwapchainKHR", device, *pSwapchain, pAllocator);
      RemoveSwapchainInfo(*pSwapchain);
      return VK_ERROR_INITIALIZATION_FAILED;
    }
    device_info.SetRemoteHandle(client_image, server_image);
  }

  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain,
                                               const VkAllocationCallbacks* pAllocator) {
  uint32_t swapchain_image_count = 0;
  std::vector<VkImage> client_swapchain_images;
  VkResult result = CallDownDeviceFunc<PFN_vkGetSwapchainImagesKHR>("vkGetSwapchainImagesKHR", device, swapchain,
                                                                    &swapchain_image_count, nullptr);
  if (result != VK_SUCCESS) {
    spdlog::critical("Failed to get swapchain images to destroy");
    return;
  }

  client_swapchain_images.resize(swapchain_image_count);
  result = CallDownDeviceFunc<PFN_vkGetSwapchainImagesKHR>("vkGetSwapchainImagesKHR", device, swapchain,
                                                           &swapchain_image_count, client_swapchain_images.data());
  if (result != VK_SUCCESS) {
    spdlog::critical("Failed to get swapchain images to destroy");
    return;
  }

  DeviceInfo& device_info = GetDeviceInfo(device);
  InstanceInfo& instance_info = device_info.instance_info;
  auto reader_writer = instance_info.command_stream();

  for (VkImage client_image : client_swapchain_images) {
    VkImage server_image = device_info.GetRemoteHandle(client_image);
    PackAndCallVkDestroyImage(reader_writer, instance_info.GetRemoteHandle(device), server_image, nullptr);
  }

  CallDownDeviceFunc<PFN_vkDestroySwapchainKHR>("vkDestroySwapchainKHR", device, swapchain, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL GetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain,
                                                     uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages) {
  if (pSwapchainImages == nullptr) {
    return CallDownDeviceFunc<PFN_vkGetSwapchainImagesKHR>("vkGetSwapchainImagesKHR", device, swapchain,
                                                           pSwapchainImageCount, nullptr);
  }
  VkResult result = CallDownDeviceFunc<PFN_vkGetSwapchainImagesKHR>("vkGetSwapchainImagesKHR", device, swapchain,
                                                                    pSwapchainImageCount, pSwapchainImages);
  if (result != VK_SUCCESS) {
    return result;
  }

  DeviceInfo& device_info = GetDeviceInfo(device);
  for (uint32_t i = 0; i < *pSwapchainImageCount; i++) {
    pSwapchainImages[i] = device_info.GetRemoteHandle(pSwapchainImages[i]);
  }

  return VK_SUCCESS;
}

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

    auto reader_writer = instance_info.command_stream();

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
  CallDownInstanceFunc<PFN_vkDestroyInstance>("vkDestroyInstance", instance, pAllocator);

  auto reader_writer = instance_info.command_stream();
  PackAndCallVkDestroyInstance(reader_writer, instance_info.GetRemoteHandle(instance), pAllocator);

  RemoveInstanceInfo(instance);
}

VKAPI_ATTR VkResult VKAPI_CALL EnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount,
                                                        VkPhysicalDevice* pPhysicalDevices) {
  spdlog::trace("EnumeratePhysicalDevices");

  VkResult result = CallDownInstanceFunc<PFN_vkEnumeratePhysicalDevices>("vkEnumeratePhysicalDevices", instance,
                                                                         pPhysicalDeviceCount, pPhysicalDevices);
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
  PackAndCallVkGetPhysicalDeviceProperties(GetInstanceInfo(physicalDevice).command_stream(), physicalDevice,
                                           pProperties);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format,
                                                             VkFormatProperties* pFormatProperties) {
  PackAndCallVkGetPhysicalDeviceFormatProperties(GetInstanceInfo(physicalDevice).command_stream(), physicalDevice,
                                                 format, pFormatProperties);
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

  VmaVulkanFunctions vma_vulkan_funcs = {
      .vkGetInstanceProcAddr = nullptr,
      .vkGetDeviceProcAddr = nullptr,
      .vkGetPhysicalDeviceProperties = GetPhysicalDeviceProperties,
      .vkGetPhysicalDeviceMemoryProperties = GetPhysicalDeviceMemoryProperties,
      .vkAllocateMemory = AllocateMemory,
      .vkFreeMemory = FreeMemory,
      .vkMapMemory = reinterpret_cast<PFN_vkMapMemory>(0xDEADBEEF),
      .vkUnmapMemory = reinterpret_cast<PFN_vkUnmapMemory>(0xDEADBEEF),
      .vkFlushMappedMemoryRanges = reinterpret_cast<PFN_vkFlushMappedMemoryRanges>(0xDEADBEEF),
      .vkInvalidateMappedMemoryRanges = reinterpret_cast<PFN_vkInvalidateMappedMemoryRanges>(0xDEADBEEF),
      .vkBindBufferMemory = reinterpret_cast<PFN_vkBindBufferMemory>(0xDEADBEEF),
      .vkBindImageMemory = BindImageMemory,
      .vkGetBufferMemoryRequirements = reinterpret_cast<PFN_vkGetBufferMemoryRequirements>(0xDEADBEEF),
      .vkGetImageMemoryRequirements = GetImageMemoryRequirements,
      .vkCreateBuffer = reinterpret_cast<PFN_vkCreateBuffer>(0xDEADBEEF),
      .vkDestroyBuffer = reinterpret_cast<PFN_vkDestroyBuffer>(0xDEADBEEF),
      .vkCreateImage = CreateImage,
      .vkDestroyImage = DestroyImage,
      .vkCmdCopyBuffer = reinterpret_cast<PFN_vkCmdCopyBuffer>(0xDEADBEEF),
      .vkGetBufferMemoryRequirements2KHR = reinterpret_cast<PFN_vkGetBufferMemoryRequirements2KHR>(0xDEADBEEF),
      .vkGetImageMemoryRequirements2KHR = GetImageMemoryRequirements2,
      .vkBindBufferMemory2KHR = reinterpret_cast<PFN_vkBindBufferMemory2KHR>(0xDEADBEEF),
      .vkBindImageMemory2KHR = BindImageMemory2,
      .vkGetPhysicalDeviceMemoryProperties2KHR =
          reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties2KHR>(0xDEADBEEF),
      .vkGetDeviceBufferMemoryRequirements = reinterpret_cast<PFN_vkGetDeviceBufferMemoryRequirements>(0xDEADBEEF),
      .vkGetDeviceImageMemoryRequirements = reinterpret_cast<PFN_vkGetDeviceImageMemoryRequirements>(0xDEADBEEF),
  };

  VmaAllocatorCreateInfo allocator_create_info = {
      .flags = 0,
      .physicalDevice = physicalDevice,
      .device = *pDevice,
      .preferredLargeHeapBlockSize = 0,
      .pAllocationCallbacks = nullptr,
      .pDeviceMemoryCallbacks = nullptr,
      .pHeapSizeLimit = nullptr,
      .pVulkanFunctions = &vma_vulkan_funcs,
      .instance = GetInstanceForPhysicalDevice(physicalDevice),
      // We are using Vulkan 1.0 for VMA, because the application may only use Vulkan 1.0
      .vulkanApiVersion = VK_API_VERSION_1_0,
      .pTypeExternalMemoryHandleTypes = nullptr,
  };

  SetDeviceInfo(*pDevice, nxt_gdpa, physicalDevice, allocator_create_info);

  {
    VkDeviceCreateInfo remote_create_info = *pCreateInfo;
    RemoveStructsFromChain(reinterpret_cast<VkBaseInStructure*>(&remote_create_info),
                           VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO);
    VkDevice remote_device = *pDevice;

    PackAndCallVkCreateDevice(instance_info.command_stream(), physicalDevice, &remote_create_info, pAllocator,
                              &remote_device);
    instance_info.SetRemoteHandle(*pDevice, remote_device);
  }

  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) {
  CallDownDeviceFunc<PFN_vkDestroyDevice>("vkDestroyDevice", device, pAllocator);

  InstanceInfo& instance_info = GetInstanceInfo(device);

  auto reader_writer = instance_info.command_stream();
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

  auto command_stream = GetInstanceInfo(physicalDevice).command_stream();

  return PackAndCallVkEnumerateDeviceExtensionProperties(command_stream, physicalDevice, pLayerName, pPropertyCount,
                                                         pProperties);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice,
                                                             VkPhysicalDeviceMemoryProperties* pMemoryProperties) {
  // TODO: investigate additional steps needed for this function
  auto command_stream = GetInstanceInfo(physicalDevice).command_stream();
  return PackAndCallVkGetPhysicalDeviceMemoryProperties(command_stream, physicalDevice, pMemoryProperties);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice,
                                                     VkPhysicalDeviceFeatures* pFeatures) {
  auto command_stream = GetInstanceInfo(physicalDevice).command_stream();
  return PackAndCallVkGetPhysicalDeviceFeatures(command_stream, physicalDevice, pFeatures);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice,
                                                                  uint32_t* pQueueFamilyPropertyCount,
                                                                  VkQueueFamilyProperties* pQueueFamilyProperties) {
  auto command_stream = GetInstanceInfo(physicalDevice).command_stream();
  return PackAndCallVkGetPhysicalDeviceQueueFamilyProperties(command_stream, physicalDevice, pQueueFamilyPropertyCount,
                                                             pQueueFamilyProperties);
}

VKAPI_ATTR void VKAPI_CALL GetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex,
                                          VkQueue* pQueue) {
  DeviceInfo& device_info = GetDeviceInfo(device);

  CallDownDeviceFunc<PFN_vkGetDeviceQueue>("vkGetDeviceQueue", device, queueFamilyIndex, queueIndex, pQueue);
  VkQueue remote_queue = VK_NULL_HANDLE;
  PackAndCallVkGetDeviceQueue(device_info.instance_info.command_stream(),
                              device_info.instance_info.GetRemoteHandle(device), queueFamilyIndex, queueIndex,
                              &remote_queue);
  device_info.SetRemoteHandle(*pQueue, remote_queue);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo,
                                           const VkAllocationCallbacks* pAllocator, VkFence* pFence) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  VkResult result = CallDownDeviceFunc<PFN_vkCreateFence>("vkCreateFence", device, pCreateInfo, pAllocator, pFence);
  if (result != VK_SUCCESS) {
    return result;
  }
  VkFence remote_fence = VK_NULL_HANDLE;
  result = PackAndCallVkCreateFence(device_info.instance_info.command_stream(),
                                    device_info.instance_info.GetRemoteHandle(device), pCreateInfo, pAllocator,
                                    &remote_fence);
  if (result != VK_SUCCESS) {
    CallDownDeviceFunc<PFN_vkDestroyFence>("vkDestroyFence", device, *pFence, pAllocator);
    return result;
  }
  device_info.SetRemoteHandle(*pFence, remote_fence);
  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  CallDownDeviceFunc<PFN_vkDestroyFence>("vkDestroyFence", device, fence, pAllocator);
  PackAndCallVkDestroyFence(device_info.instance_info.command_stream(),
                            device_info.instance_info.GetRemoteHandle(device), device_info.GetRemoteHandle(fence),
                            pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo,
                                               const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  VkResult result =
      CallDownDeviceFunc<PFN_vkCreateSemaphore>("vkCreateSemaphore", device, pCreateInfo, pAllocator, pSemaphore);
  if (result != VK_SUCCESS) {
    return result;
  }
  VkSemaphore remote_semaphore = VK_NULL_HANDLE;
  result = PackAndCallVkCreateSemaphore(device_info.instance_info.command_stream(),
                                        device_info.instance_info.GetRemoteHandle(device), pCreateInfo, pAllocator,
                                        &remote_semaphore);
  if (result != VK_SUCCESS) {
    CallDownDeviceFunc<PFN_vkDestroySemaphore>("vkDestroySemaphore", device, *pSemaphore, pAllocator);
    return result;
  }
  device_info.SetRemoteHandle(*pSemaphore, remote_semaphore);
  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroySemaphore(VkDevice device, VkSemaphore semaphore,
                                            const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  CallDownDeviceFunc<PFN_vkDestroySemaphore>("vkDestroySemaphore", device, semaphore, pAllocator);
  PackAndCallVkDestroySemaphore(device_info.instance_info.command_stream(),
                                device_info.instance_info.GetRemoteHandle(device),
                                device_info.GetRemoteHandle(semaphore), pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL AllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo,
                                              const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkAllocateMemory(device_info.instance_info.command_stream(),
                                     device_info.instance_info.GetRemoteHandle(device), pAllocateInfo, pAllocator,
                                     pMemory);
}

VKAPI_ATTR void VKAPI_CALL FreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkFreeMemory(device_info.instance_info.command_stream(), device_info.instance_info.GetRemoteHandle(device),
                          memory, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo,
                                           const VkAllocationCallbacks* pAllocator, VkImage* pImage) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateImage(device_info.instance_info.command_stream(),
                                  device_info.instance_info.GetRemoteHandle(device), pCreateInfo, pAllocator, pImage);
}

VKAPI_ATTR void VKAPI_CALL DestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyImage(device_info.instance_info.command_stream(),
                            device_info.instance_info.GetRemoteHandle(device), image, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL BindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory,
                                               VkDeviceSize memoryOffset) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkBindImageMemory(device_info.instance_info.command_stream(),
                                      device_info.instance_info.GetRemoteHandle(device), image, memory, memoryOffset);
}

VKAPI_ATTR VkResult VKAPI_CALL BindImageMemory2(VkDevice device, uint32_t bindInfoCount,
                                                const VkBindImageMemoryInfo* pBindInfos) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkBindImageMemory2(device_info.instance_info.command_stream(),
                                       device_info.instance_info.GetRemoteHandle(device), bindInfoCount, pBindInfos);
}

VKAPI_ATTR void VKAPI_CALL GetImageMemoryRequirements(VkDevice device, VkImage image,
                                                      VkMemoryRequirements* pMemoryRequirements) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkGetImageMemoryRequirements(device_info.instance_info.command_stream(),
                                          device_info.instance_info.GetRemoteHandle(device), image,
                                          pMemoryRequirements);
}

VKAPI_ATTR void VKAPI_CALL GetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo,
                                                       VkMemoryRequirements2* pMemoryRequirements) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkGetImageMemoryRequirements2(device_info.instance_info.command_stream(),
                                           device_info.instance_info.GetRemoteHandle(device), pInfo,
                                           pMemoryRequirements);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo,
                                               const VkAllocationCallbacks* pAllocator, VkImageView* pView) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateImageView(device_info.instance_info.command_stream(),
                                      device_info.instance_info.GetRemoteHandle(device), pCreateInfo, pAllocator,
                                      pView);
}
VKAPI_ATTR void VKAPI_CALL DestroyImageView(VkDevice device, VkImageView imageView,
                                            const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyImageView(device_info.instance_info.command_stream(),
                                device_info.instance_info.GetRemoteHandle(device), imageView, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo,
                                                 const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateCommandPool(device_info.instance_info.command_stream(),
                                        device_info.instance_info.GetRemoteHandle(device), pCreateInfo, pAllocator,
                                        pCommandPool);
}
VKAPI_ATTR void VKAPI_CALL DestroyCommandPool(VkDevice device, VkCommandPool commandPool,
                                              const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyCommandPool(device_info.instance_info.command_stream(),
                                  device_info.instance_info.GetRemoteHandle(device), commandPool, pAllocator);
}
VKAPI_ATTR VkResult VKAPI_CALL AllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo,
                                                      VkCommandBuffer* pCommandBuffers) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  VkResult result = PackAndCallVkAllocateCommandBuffers(device_info.instance_info.command_stream(),
                                                        device_info.instance_info.GetRemoteHandle(device),
                                                        pAllocateInfo, pCommandBuffers);
  if (result != VK_SUCCESS) {
    return result;
  }

  // Command buffers are dispatchable handles so we must allow the loader to insert the dispatch table
  // For more details, see:
  // https://github.com/KhronosGroup/Vulkan-Loader/blob/main/docs/LoaderDriverInterface.md#driver-dispatchable-object-creation

  for (uint32_t i = 0; i < pAllocateInfo->commandBufferCount; i++) {
    VkCommandBuffer remote_command_buffer = pCommandBuffers[i];
    pCommandBuffers[i] = reinterpret_cast<VkCommandBuffer>(AllocateHandle());
    device_info.SetRemoteHandle(pCommandBuffers[i], remote_command_buffer);
    AssociateCommandBufferWithDevice(pCommandBuffers[i], device);
  }

  return result;
}
VKAPI_ATTR void VKAPI_CALL FreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount,
                                              const VkCommandBuffer* pCommandBuffers) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  for (uint32_t i = 0; i < commandBufferCount; i++) {
    free(const_cast<VkCommandBuffer>(pCommandBuffers[i]));
  }
  std::vector<VkCommandBuffer> remote_command_buffers;
  remote_command_buffers.reserve(commandBufferCount);
  for (uint32_t i = 0; i < commandBufferCount; i++) {
    RemoveCommandBuffer(pCommandBuffers[i]);
    remote_command_buffers.push_back(device_info.GetRemoteHandle(pCommandBuffers[i]));
  }
  PackAndCallVkFreeCommandBuffers(device_info.instance_info.command_stream(),
                                  device_info.instance_info.GetRemoteHandle(device), commandPool, commandBufferCount,
                                  remote_command_buffers.data());
}

VKAPI_ATTR VkResult VKAPI_CALL BeginCommandBuffer(VkCommandBuffer commandBuffer,
                                                  const VkCommandBufferBeginInfo* pBeginInfo) {
  DeviceInfo& device_info = GetDeviceInfo(commandBuffer);
  return PackAndCallVkBeginCommandBuffer(device_info.instance_info.command_stream(),
                                         device_info.GetRemoteHandle(commandBuffer), pBeginInfo);
}
VKAPI_ATTR VkResult VKAPI_CALL EndCommandBuffer(VkCommandBuffer commandBuffer) {
  DeviceInfo& device_info = GetDeviceInfo(commandBuffer);
  return PackAndCallVkEndCommandBuffer(device_info.instance_info.command_stream(),
                                       device_info.GetRemoteHandle(commandBuffer));
}

VKAPI_ATTR void VKAPI_CALL GetImageSubresourceLayout(VkDevice device, VkImage image,
                                                     const VkImageSubresource* pSubresource,
                                                     VkSubresourceLayout* pLayout) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  VkImage image_to_check = image;
  if (device_info.HasRemoteHandle(image)) {
    image_to_check = device_info.GetRemoteHandle(image);
  }
  PackAndCallVkGetImageSubresourceLayout(device_info.instance_info.command_stream(),
                                         device_info.instance_info.GetRemoteHandle(device), image_to_check,
                                         pSubresource, pLayout);
}
}  // namespace vvk