#include "functions.h"

#include <grpcpp/grpcpp.h>
#include <spdlog/spdlog.h>
#include <vk_mem_alloc.h>
#include <vulkan/vk_icd.h>
#include <vulkan/vk_layer.h>

#include <cassert>
#include <optional>
#include <vector>

#include "commons/remote_call.h"
#include "layer/context/device.h"
#include "layer/context/instance.h"
#include "layer/context/swapchain.h"

enum class SemaphoreState {
  kUnsignaled,
  kToBeSignaledLocal,
  kToBeSignaledRemote,
};

struct VkSemaphore_T {
  VkSemaphore_T()
      : local_handle(VK_NULL_HANDLE),
        remote_handle(VK_NULL_HANDLE),
        local_to_remote_fence(VK_NULL_HANDLE),
        remote_to_local_semaphore(0),
        state(SemaphoreState::kUnsignaled) {}

  VkSemaphore local_handle;
  VkSemaphore remote_handle;
  VkFence local_to_remote_fence;
  std::binary_semaphore remote_to_local_semaphore;
  SemaphoreState state;
};

namespace vvk {

namespace {

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

std::optional<std::vector<VkImage>> GetLocalImagesForSwapchain(VkDevice device, VkSwapchainKHR swapchain) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  uint32_t swapchain_image_count = 0;
  std::vector<VkImage> client_swapchain_images;
  VkResult result =
      device_info.dispatch_table().GetSwapchainImagesKHR(device, swapchain, &swapchain_image_count, nullptr);
  if (result != VK_SUCCESS) {
    return std::nullopt;
  }

  client_swapchain_images.resize(swapchain_image_count);
  result = device_info.dispatch_table().GetSwapchainImagesKHR(device, swapchain, &swapchain_image_count,
                                                              client_swapchain_images.data());
  if (result != VK_SUCCESS) {
    return std::nullopt;
  }

  return client_swapchain_images;
}

}  // namespace

VKAPI_ATTR VkResult VKAPI_CALL CreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo,
                                                  const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain) {
  spdlog::trace("CreateSwapchainKHR");

  DeviceInfo& device_info = GetDeviceInfo(device);
  VkResult result = device_info.dispatch_table().CreateSwapchainKHR(device, pCreateInfo, pAllocator, pSwapchain);
  if (result != VK_SUCCESS) {
    return result;
  }

  std::optional<std::vector<VkImage>> client_swapchain_images = GetLocalImagesForSwapchain(device, *pSwapchain);
  if (!client_swapchain_images) {
    device_info.dispatch_table().DestroySwapchainKHR(device, *pSwapchain, pAllocator);
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  InstanceInfo& instance_info = device_info.instance_info();
  auto& reader_writer = instance_info.command_stream();

  if (pCreateInfo->oldSwapchain) {
    RemoveSwapchainInfo(pCreateInfo->oldSwapchain);
  }

  SwapchainInfo& swapchain_info = SetSwapchainInfo(*pSwapchain, device, device_info.remote_allocator());

  // Create remote images for the swapchain
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
  for (VkImage client_image : *client_swapchain_images) {
    VkImage server_image;
    server_image = swapchain_info.CreateImageRemote(image_create_info, alloc_create_info);
    if (result != VK_SUCCESS) {
      device_info.dispatch_table().DestroySwapchainKHR(device, *pSwapchain, pAllocator);
      RemoveSwapchainInfo(*pSwapchain);
      return VK_ERROR_INITIALIZATION_FAILED;
    }
    device_info.SetRemoteHandle(client_image, server_image);
  }

  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain,
                                               const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);

  uint32_t swapchain_image_count = 0;
  std::optional<std::vector<VkImage>> client_swapchain_images = GetLocalImagesForSwapchain(device, swapchain);
  if (!client_swapchain_images) {
    spdlog::critical("Failed to get swapchain images to destroy");
    return;
  }

  InstanceInfo& instance_info = device_info.instance_info();
  auto& reader_writer = instance_info.command_stream();

  for (VkImage client_image : *client_swapchain_images) {
    VkImage server_image = device_info.GetRemoteHandle(client_image);
    PackAndCallVkDestroyImage(reader_writer, instance_info.GetRemoteHandle(device), server_image, nullptr);
  }

  device_info.dispatch_table().DestroySwapchainKHR(device, swapchain, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL GetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain,
                                                     uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages) {
  DeviceInfo& device_info = GetDeviceInfo(device);

  if (pSwapchainImages == nullptr) {
    return device_info.dispatch_table().GetSwapchainImagesKHR(device, swapchain, pSwapchainImageCount, nullptr);
  }
  VkResult result =
      device_info.dispatch_table().GetSwapchainImagesKHR(device, swapchain, pSwapchainImageCount, pSwapchainImages);
  if (result != VK_SUCCESS) {
    return result;
  }

  for (uint32_t i = 0; i < *pSwapchainImageCount; i++) {
    pSwapchainImages[i] = device_info.GetRemoteHandle(pSwapchainImages[i]);
  }

  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL AcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout,
                                                   VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  if (semaphore != VK_NULL_HANDLE) {
    if (fence != VK_NULL_HANDLE) {
      throw std::runtime_error("Cannot use both semaphore and fence in AcquireNextImageKHR");
    }
    semaphore->state = SemaphoreState::kToBeSignaledLocal;
    fence = semaphore->local_to_remote_fence;
  }
  if (fence != VK_NULL_HANDLE) {
    device_info.SetFenceLocal(fence);
  }
  VkResult result = device_info.dispatch_table().AcquireNextImageKHR(device, swapchain, timeout,
                                                                     semaphore->local_handle, fence, pImageIndex);
  if (result != VK_SUCCESS) {
    semaphore->state = SemaphoreState::kUnsignaled;
    device_info.ResetFenceLocal(fence);
  }
  return result;
}

VKAPI_ATTR VkResult VKAPI_CALL QueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo) {
  std::vector<VkSemaphore> semaphores_to_wait_device;
  std::vector<VkSemaphore> semaphores_to_wait_cpu;
  std::vector<VkSwapchainKHR> swapchains;
  std::vector<uint32_t> image_indices;

  // TODO: send image data from remote server

  VkPresentInfoKHR present_info = *pPresentInfo;
  for (uint32_t i = 0; i < pPresentInfo->waitSemaphoreCount; i++) {
    VkSemaphore semaphore = pPresentInfo->pWaitSemaphores[i];
    if (semaphore->state == SemaphoreState::kToBeSignaledRemote) {
      semaphores_to_wait_cpu.push_back(semaphore);
    } else if (semaphore->state == SemaphoreState::kToBeSignaledLocal) {
      semaphores_to_wait_device.push_back(semaphore->local_handle);
      semaphore->state = SemaphoreState::kUnsignaled;
    } else {
      throw std::runtime_error("Invalid semaphore state in QueuePresentKHR");
    }
  }
  present_info.waitSemaphoreCount = semaphores_to_wait_device.size();
  present_info.pWaitSemaphores = semaphores_to_wait_device.data();

  for (uint32_t i = 0; i < pPresentInfo->swapchainCount; i++) {
    swapchains.push_back(pPresentInfo->pSwapchains[i]);
    image_indices.push_back(pPresentInfo->pImageIndices[i]);
  }
  present_info.pSwapchains = swapchains.data();
  present_info.pImageIndices = image_indices.data();

  DeviceInfo& device_info = GetDeviceInfo(queue);
  std::thread caller_thread([queue_present_fn = device_info.dispatch_table().QueuePresentKHR, queue,
                             present_info = std::move(present_info),
                             semaphores_to_wait = std::move(semaphores_to_wait_cpu),
                             // these vectors are moved to the lambda so present_info is valid
                             unused1 = std::move(semaphores_to_wait_device), unused2 = std::move(swapchains),
                             unused3 = std::move(image_indices)]() {
    for (VkSemaphore semaphore : semaphores_to_wait) {
      if (semaphore->state != SemaphoreState::kToBeSignaledRemote) {
        throw std::runtime_error("Invalid semaphore state in QueuePresentKHR");
      }
      semaphore->remote_to_local_semaphore.acquire();
      semaphore->state = SemaphoreState::kUnsignaled;
    }

    queue_present_fn(queue, &present_info);
  });
  caller_thread.detach();
  return VK_SUCCESS;
}

PFN_vkVoidFunction DefaultGetInstanceProcAddr(VkInstance instance, const char* pName) {
  return GetInstanceInfo(instance).dispatch_table().GetInstanceProcAddr(instance, pName);
}
PFN_vkVoidFunction DefaultGetDeviceProcAddr(VkDevice device, const char* pName) {
  return GetDeviceInfo(device).dispatch_table().GetDeviceProcAddr(device, pName);
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

    auto& reader_writer = instance_info.command_stream();

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
  instance_info.dispatch_table().DestroyInstance(instance, pAllocator);

  auto& reader_writer = instance_info.command_stream();
  PackAndCallVkDestroyInstance(reader_writer, instance_info.GetRemoteHandle(instance), pAllocator);

  RemoveInstanceInfo(instance);
}

VKAPI_ATTR VkResult VKAPI_CALL EnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount,
                                                        VkPhysicalDevice* pPhysicalDevices) {
  spdlog::trace("EnumeratePhysicalDevices");

  InstanceInfo& instance_info = GetInstanceInfo(instance);

  VkResult result =
      instance_info.dispatch_table().EnumeratePhysicalDevices(instance, pPhysicalDeviceCount, pPhysicalDevices);
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

  VkResult result = instance_info.dispatch_table().CreateDevice(physicalDevice, pCreateInfo, pAllocator, pDevice);

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
  DeviceInfo& device_info = GetDeviceInfo(device);
  device_info.dispatch_table().DestroyDevice(device, pAllocator);

  InstanceInfo& instance_info = GetInstanceInfo(device);

  auto& reader_writer = device_info.instance_info().command_stream();
  PackAndCallVkDestroyDevice(reader_writer, device_info.instance_info().GetRemoteHandle(device), pAllocator);

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
    InstanceInfo& instance_info = GetInstanceInfo(physicalDevice);
    return instance_info.dispatch_table().EnumerateDeviceExtensionProperties(physicalDevice, pLayerName, pPropertyCount,
                                                                             pProperties);
  }

  auto& command_stream = GetInstanceInfo(physicalDevice).command_stream();

  return PackAndCallVkEnumerateDeviceExtensionProperties(command_stream, physicalDevice, pLayerName, pPropertyCount,
                                                         pProperties);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice,
                                                             VkPhysicalDeviceMemoryProperties* pMemoryProperties) {
  // TODO: investigate additional steps needed for this function
  auto& command_stream = GetInstanceInfo(physicalDevice).command_stream();
  return PackAndCallVkGetPhysicalDeviceMemoryProperties(command_stream, physicalDevice, pMemoryProperties);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice,
                                                     VkPhysicalDeviceFeatures* pFeatures) {
  auto& command_stream = GetInstanceInfo(physicalDevice).command_stream();
  return PackAndCallVkGetPhysicalDeviceFeatures(command_stream, physicalDevice, pFeatures);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice,
                                                                  uint32_t* pQueueFamilyPropertyCount,
                                                                  VkQueueFamilyProperties* pQueueFamilyProperties) {
  auto& command_stream = GetInstanceInfo(physicalDevice).command_stream();
  return PackAndCallVkGetPhysicalDeviceQueueFamilyProperties(command_stream, physicalDevice, pQueueFamilyPropertyCount,
                                                             pQueueFamilyProperties);
}

VKAPI_ATTR void VKAPI_CALL GetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex,
                                          VkQueue* pQueue) {
  DeviceInfo& device_info = GetDeviceInfo(device);

  device_info.dispatch_table().GetDeviceQueue(device, queueFamilyIndex, queueIndex, pQueue);
  VkQueue remote_queue = VK_NULL_HANDLE;
  PackAndCallVkGetDeviceQueue(device_info.instance_info().command_stream(),
                              device_info.instance_info().GetRemoteHandle(device), queueFamilyIndex, queueIndex,
                              &remote_queue);
  device_info.SetRemoteHandle(*pQueue, remote_queue);
  AssociateQueueWithDevice(*pQueue, device);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo,
                                           const VkAllocationCallbacks* pAllocator, VkFence* pFence) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  VkResult result = device_info.dispatch_table().CreateFence(device, pCreateInfo, pAllocator, pFence);
  if (result != VK_SUCCESS) {
    return result;
  }
  VkFence remote_fence = VK_NULL_HANDLE;
  result = PackAndCallVkCreateFence(device_info.instance_info().command_stream(),
                                    device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator,
                                    &remote_fence);
  if (result != VK_SUCCESS) {
    device_info.dispatch_table().DestroyFence(device, *pFence, pAllocator);
    return result;
  }
  device_info.SetRemoteHandle(*pFence, remote_fence);
  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  device_info.dispatch_table().DestroyFence(device, fence, pAllocator);
  PackAndCallVkDestroyFence(device_info.instance_info().command_stream(),
                            device_info.instance_info().GetRemoteHandle(device), device_info.GetRemoteHandle(fence),
                            pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo,
                                               const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore) {
  *pSemaphore = new VkSemaphore_T;
  DeviceInfo& device_info = GetDeviceInfo(device);
  VkResult result =
      device_info.dispatch_table().CreateSemaphore(device, pCreateInfo, pAllocator, &(*pSemaphore)->local_handle);
  if (result != VK_SUCCESS) {
    return result;
  }
  VkFenceCreateInfo fence_create_info = {
      .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
  };
  result = device_info.dispatch_table().CreateFence(device, &fence_create_info, pAllocator,
                                                    &(*pSemaphore)->local_to_remote_fence);
  if (result != VK_SUCCESS) {
    device_info.dispatch_table().DestroySemaphore(device, (*pSemaphore)->local_handle, pAllocator);
    return result;
  }
  VkSemaphore remote_semaphore = VK_NULL_HANDLE;
  result = PackAndCallVkCreateSemaphore(device_info.instance_info().command_stream(),
                                        device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator,
                                        &remote_semaphore);
  if (result != VK_SUCCESS) {
    device_info.dispatch_table().DestroySemaphore(device, (*pSemaphore)->local_handle, pAllocator);
    device_info.dispatch_table().DestroyFence(device, (*pSemaphore)->local_to_remote_fence, pAllocator);
    return result;
  }
  (*pSemaphore)->remote_handle = remote_semaphore;
  (*pSemaphore)->state = SemaphoreState::kUnsignaled;
  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroySemaphore(VkDevice device, VkSemaphore semaphore,
                                            const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  device_info.dispatch_table().DestroySemaphore(device, semaphore->local_handle, pAllocator);
  device_info.dispatch_table().DestroyFence(device, semaphore->local_to_remote_fence, pAllocator);
  PackAndCallVkDestroySemaphore(device_info.instance_info().command_stream(),
                                device_info.instance_info().GetRemoteHandle(device),
                                device_info.GetRemoteHandle(semaphore->remote_handle), pAllocator);
  delete semaphore;
}

VKAPI_ATTR VkResult VKAPI_CALL AllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo,
                                              const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkAllocateMemory(device_info.instance_info().command_stream(),
                                     device_info.instance_info().GetRemoteHandle(device), pAllocateInfo, pAllocator,
                                     pMemory);
}

VKAPI_ATTR void VKAPI_CALL FreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkFreeMemory(device_info.instance_info().command_stream(),
                          device_info.instance_info().GetRemoteHandle(device), memory, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo,
                                           const VkAllocationCallbacks* pAllocator, VkImage* pImage) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateImage(device_info.instance_info().command_stream(),
                                  device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator, pImage);
}

VKAPI_ATTR void VKAPI_CALL DestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyImage(device_info.instance_info().command_stream(),
                            device_info.instance_info().GetRemoteHandle(device), image, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL BindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory,
                                               VkDeviceSize memoryOffset) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkBindImageMemory(device_info.instance_info().command_stream(),
                                      device_info.instance_info().GetRemoteHandle(device), image, memory, memoryOffset);
}

VKAPI_ATTR VkResult VKAPI_CALL BindImageMemory2(VkDevice device, uint32_t bindInfoCount,
                                                const VkBindImageMemoryInfo* pBindInfos) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkBindImageMemory2(device_info.instance_info().command_stream(),
                                       device_info.instance_info().GetRemoteHandle(device), bindInfoCount, pBindInfos);
}

VKAPI_ATTR void VKAPI_CALL GetImageMemoryRequirements(VkDevice device, VkImage image,
                                                      VkMemoryRequirements* pMemoryRequirements) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkGetImageMemoryRequirements(device_info.instance_info().command_stream(),
                                          device_info.instance_info().GetRemoteHandle(device), image,
                                          pMemoryRequirements);
}

VKAPI_ATTR void VKAPI_CALL GetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo,
                                                       VkMemoryRequirements2* pMemoryRequirements) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkGetImageMemoryRequirements2(device_info.instance_info().command_stream(),
                                           device_info.instance_info().GetRemoteHandle(device), pInfo,
                                           pMemoryRequirements);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo,
                                               const VkAllocationCallbacks* pAllocator, VkImageView* pView) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateImageView(device_info.instance_info().command_stream(),
                                      device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator,
                                      pView);
}
VKAPI_ATTR void VKAPI_CALL DestroyImageView(VkDevice device, VkImageView imageView,
                                            const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyImageView(device_info.instance_info().command_stream(),
                                device_info.instance_info().GetRemoteHandle(device), imageView, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo,
                                                 const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateCommandPool(device_info.instance_info().command_stream(),
                                        device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator,
                                        pCommandPool);
}
VKAPI_ATTR void VKAPI_CALL DestroyCommandPool(VkDevice device, VkCommandPool commandPool,
                                              const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyCommandPool(device_info.instance_info().command_stream(),
                                  device_info.instance_info().GetRemoteHandle(device), commandPool, pAllocator);
}
VKAPI_ATTR VkResult VKAPI_CALL AllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo,
                                                      VkCommandBuffer* pCommandBuffers) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  VkResult result = PackAndCallVkAllocateCommandBuffers(device_info.instance_info().command_stream(),
                                                        device_info.instance_info().GetRemoteHandle(device),
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
  PackAndCallVkFreeCommandBuffers(device_info.instance_info().command_stream(),
                                  device_info.instance_info().GetRemoteHandle(device), commandPool, commandBufferCount,
                                  remote_command_buffers.data());
}

VKAPI_ATTR VkResult VKAPI_CALL BeginCommandBuffer(VkCommandBuffer commandBuffer,
                                                  const VkCommandBufferBeginInfo* pBeginInfo) {
  DeviceInfo& device_info = GetDeviceInfo(commandBuffer);
  return PackAndCallVkBeginCommandBuffer(device_info.instance_info().command_stream(),
                                         device_info.GetRemoteHandle(commandBuffer), pBeginInfo);
}
VKAPI_ATTR VkResult VKAPI_CALL EndCommandBuffer(VkCommandBuffer commandBuffer) {
  DeviceInfo& device_info = GetDeviceInfo(commandBuffer);
  return PackAndCallVkEndCommandBuffer(device_info.instance_info().command_stream(),
                                       device_info.GetRemoteHandle(commandBuffer));
}

VKAPI_ATTR void VKAPI_CALL GetImageSubresourceLayout(VkDevice device, VkImage image,
                                                     const VkImageSubresource* pSubresource,
                                                     VkSubresourceLayout* pLayout) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkGetImageSubresourceLayout(device_info.instance_info().command_stream(),
                                         device_info.instance_info().GetRemoteHandle(device), image, pSubresource,
                                         pLayout);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo,
                                                const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) {
  DeviceInfo device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateRenderPass(device_info.instance_info().command_stream(),
                                       device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator,
                                       pRenderPass);
}
VKAPI_ATTR void VKAPI_CALL DestroyRenderPass(VkDevice device, VkRenderPass renderPass,
                                             const VkAllocationCallbacks* pAllocator) {
  DeviceInfo device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyRenderPass(device_info.instance_info().command_stream(),
                                 device_info.instance_info().GetRemoteHandle(device), renderPass, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo,
                                                    const VkAllocationCallbacks* pAllocator,
                                                    VkPipelineLayout* pPipelineLayout) {
  DeviceInfo device_info = GetDeviceInfo(device);
  return PackAndCallVkCreatePipelineLayout(device_info.instance_info().command_stream(),
                                           device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator,
                                           pPipelineLayout);
}
VKAPI_ATTR void VKAPI_CALL DestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout,
                                                 const VkAllocationCallbacks* pAllocator) {
  DeviceInfo device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyPipelineLayout(device_info.instance_info().command_stream(),
                                     device_info.instance_info().GetRemoteHandle(device), pipelineLayout, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo,
                                                  const VkAllocationCallbacks* pAllocator,
                                                  VkShaderModule* pShaderModule) {
  DeviceInfo device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateShaderModule(device_info.instance_info().command_stream(),
                                         device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator,
                                         pShaderModule);
}
VKAPI_ATTR void VKAPI_CALL DestroyShaderModule(VkDevice device, VkShaderModule shaderModule,
                                               const VkAllocationCallbacks* pAllocator) {
  DeviceInfo device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyShaderModule(device_info.instance_info().command_stream(),
                                   device_info.instance_info().GetRemoteHandle(device), shaderModule, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache,
                                                       uint32_t createInfoCount,
                                                       const VkGraphicsPipelineCreateInfo* pCreateInfos,
                                                       const VkAllocationCallbacks* pAllocator,
                                                       VkPipeline* pPipelines) {
  DeviceInfo device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateGraphicsPipelines(device_info.instance_info().command_stream(),
                                              device_info.instance_info().GetRemoteHandle(device), pipelineCache,
                                              createInfoCount, pCreateInfos, pAllocator, pPipelines);
}
VKAPI_ATTR void VKAPI_CALL DestroyPipeline(VkDevice device, VkPipeline pipeline,
                                           const VkAllocationCallbacks* pAllocator) {
  DeviceInfo device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyPipeline(device_info.instance_info().command_stream(),
                               device_info.instance_info().GetRemoteHandle(device), pipeline, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo,
                                                 const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer) {
  DeviceInfo device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateFramebuffer(device_info.instance_info().command_stream(),
                                        device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator,
                                        pFramebuffer);
}
VKAPI_ATTR void VKAPI_CALL DestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer,
                                              const VkAllocationCallbacks* pAllocator) {
  DeviceInfo device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyFramebuffer(device_info.instance_info().command_stream(),
                                  device_info.instance_info().GetRemoteHandle(device), framebuffer, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL WaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences,
                                             VkBool32 waitAll, uint64_t timeout) {
  if (!waitAll) {
    throw std::runtime_error("WaitForFences with waitAll=false is not supported");
  }
  DeviceInfo& device_info = GetDeviceInfo(device);

  std::vector<VkFence> local_fences;
  local_fences.reserve(fenceCount);
  std::vector<VkFence> remote_fences;
  remote_fences.reserve(fenceCount);

  for (uint32_t i = 0; i < fenceCount; i++) {
    if (device_info.IsLocalFence(pFences[i])) {
      local_fences.push_back(pFences[i]);
    } else {
      remote_fences.push_back(device_info.GetRemoteHandle(pFences[i]));
    }
  }

  VkResult local_result = VK_SUCCESS;
  VkResult remote_result = VK_SUCCESS;
  std::thread local_wait_thread;
  std::thread remote_wait_thread;

  if (!local_fences.empty()) {
    local_wait_thread =
        std::thread([&device_info, &local_fences, &local_result, device, fenceCount, waitAll, timeout]() {
          local_result = device_info.dispatch_table().WaitForFences(device, local_fences.size(), local_fences.data(),
                                                                    waitAll, timeout);
        });
  }
  if (!remote_fences.empty()) {
    remote_wait_thread =
        std::thread([&device_info, &remote_fences, &remote_result, device, fenceCount, waitAll, timeout]() {
          remote_result = PackAndCallVkWaitForFences(device_info.instance_info().command_stream(),
                                                     device_info.instance_info().GetRemoteHandle(device), fenceCount,
                                                     remote_fences.data(), waitAll, timeout);
        });
  }

  if (local_wait_thread.joinable()) {
    local_wait_thread.join();
  }
  if (remote_wait_thread.joinable()) {
    remote_wait_thread.join();
  }

  if (local_result != VK_SUCCESS) {
    return local_result;
  }
  return remote_result;
}

VKAPI_ATTR VkResult VKAPI_CALL ResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences) {
  DeviceInfo& device_info = GetDeviceInfo(device);

  std::vector<VkFence> local_fences;
  local_fences.reserve(fenceCount);
  std::vector<VkFence> remote_fences;
  remote_fences.reserve(fenceCount);

  for (uint32_t i = 0; i < fenceCount; i++) {
    if (device_info.IsLocalFence(pFences[i])) {
      local_fences.push_back(pFences[i]);
    } else {
      remote_fences.push_back(device_info.GetRemoteHandle(pFences[i]));
    }
  }

  if (!local_fences.empty()) {
    VkResult result = device_info.dispatch_table().ResetFences(device, local_fences.size(), local_fences.data());
    if (result != VK_SUCCESS) {
      return result;
    }
    for (VkFence fence : local_fences) {
      device_info.ResetFenceLocal(fence);
    }
  }

  if (!remote_fences.empty()) {
    VkResult result = PackAndCallVkResetFences(device_info.instance_info().command_stream(),
                                               device_info.instance_info().GetRemoteHandle(device),
                                               remote_fences.size(), remote_fences.data());
    if (result != VK_SUCCESS) {
      return result;
    }
  }

  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL ResetCommandPool(VkDevice device, VkCommandPool commandPool,
                                                VkCommandPoolResetFlags flags) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkResetCommandPool(device_info.instance_info().command_stream(),
                                       device_info.instance_info().GetRemoteHandle(device), commandPool, flags);
}

VKAPI_ATTR void VKAPI_CALL CmdBeginRenderPass(VkCommandBuffer commandBuffer,
                                              const VkRenderPassBeginInfo* pRenderPassBegin,
                                              VkSubpassContents contents) {
  DeviceInfo& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdBeginRenderPass(device_info.instance_info().command_stream(),
                                  device_info.GetRemoteHandle(commandBuffer), pRenderPassBegin, contents);
}
VKAPI_ATTR void VKAPI_CALL CmdEndRenderPass(VkCommandBuffer commandBuffer) {
  DeviceInfo& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdEndRenderPass(device_info.instance_info().command_stream(),
                                device_info.GetRemoteHandle(commandBuffer));
}

VKAPI_ATTR void VKAPI_CALL CmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint,
                                           VkPipeline pipeline) {
  DeviceInfo& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdBindPipeline(device_info.instance_info().command_stream(), device_info.GetRemoteHandle(commandBuffer),
                               pipelineBindPoint, pipeline);
}

VKAPI_ATTR void VKAPI_CALL CmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount,
                                          const VkViewport* pViewports) {
  DeviceInfo& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdSetViewport(device_info.instance_info().command_stream(), device_info.GetRemoteHandle(commandBuffer),
                              firstViewport, viewportCount, pViewports);
}
VKAPI_ATTR void VKAPI_CALL CmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount,
                                         const VkRect2D* pScissors) {
  DeviceInfo& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdSetScissor(device_info.instance_info().command_stream(), device_info.GetRemoteHandle(commandBuffer),
                             firstScissor, scissorCount, pScissors);
}

VKAPI_ATTR void VKAPI_CALL CmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount,
                                   uint32_t firstVertex, uint32_t firstInstance) {
  DeviceInfo& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdDraw(device_info.instance_info().command_stream(), device_info.GetRemoteHandle(commandBuffer),
                       vertexCount, instanceCount, firstVertex, firstInstance);
}

VKAPI_ATTR VkResult VKAPI_CALL QueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits,
                                           VkFence fence) {
  VkDevice device = GetDeviceForQueue(queue);
  DeviceInfo& device_info = GetDeviceInfo(device);

  if (fence == VK_NULL_HANDLE) {
    throw std::runtime_error("QueueSubmit with fence == VK_NULL_HANDLE is not supported");
  }

  std::vector<VkSemaphore> semaphores_to_wait_local;
  semaphores_to_wait_local.reserve(submitCount);  // not the exact size but it's a good guess
  std::vector<VkSemaphore> semaphores_to_signal_from_remote;
  semaphores_to_signal_from_remote.reserve(submitCount);  // not the exact size but it's a good guess
  std::vector<VkSubmitInfo> submit_infos;
  submit_infos.reserve(submitCount);
  std::vector<std::vector<VkSemaphore>> semaphores_to_wait_remote;
  semaphores_to_wait_remote.resize(submitCount);
  std::vector<std::vector<VkSemaphore>> semaphores_to_signal_remote;
  semaphores_to_signal_remote.resize(submitCount);
  std::vector<std::vector<VkCommandBuffer>> command_buffers_remote;
  command_buffers_remote.resize(submitCount);

  // We look for local semaphores and remove them from the list
  // then we send the queue submit command to the server only once the semaphores are signaled
  // we check for the semaphores to be signaled using the local_to_remote_fence of the semaphore
  // TODO: use timeline semaphores
  for (uint32_t submit_info_indx = 0; submit_info_indx < submitCount; submit_info_indx++) {
    VkSubmitInfo submit_info = pSubmits[submit_info_indx];

    if (submit_info.waitSemaphoreCount > 0) {
      for (uint32_t j = 0; j < submit_info.waitSemaphoreCount; j++) {
        if (submit_info.pWaitSemaphores[j]->state == SemaphoreState::kToBeSignaledLocal) {
          semaphores_to_wait_local.push_back(submit_info.pWaitSemaphores[j]);
          submit_info.pWaitSemaphores[j]->state = SemaphoreState::kUnsignaled;
        } else {
          semaphores_to_wait_remote[submit_info_indx].push_back(submit_info.pWaitSemaphores[j]->remote_handle);
        }
      }
      submit_info.waitSemaphoreCount = semaphores_to_wait_remote[submit_info_indx].size();
      submit_info.pWaitSemaphores = semaphores_to_wait_remote[submit_info_indx].data();
    }

    for (uint32_t j = 0; j < submit_info.signalSemaphoreCount; j++) {
      semaphores_to_signal_remote[submit_info_indx].push_back(submit_info.pSignalSemaphores[j]->remote_handle);
      submit_info.pSignalSemaphores[j]->state = SemaphoreState::kToBeSignaledRemote;
      semaphores_to_signal_from_remote.push_back(submit_info.pSignalSemaphores[j]);
    }
    submit_info.signalSemaphoreCount = semaphores_to_signal_remote[submit_info_indx].size();
    submit_info.pSignalSemaphores = semaphores_to_signal_remote[submit_info_indx].data();

    for (uint32_t j = 0; j < submit_info.commandBufferCount; j++) {
      command_buffers_remote[submit_info_indx].push_back(device_info.GetRemoteHandle(submit_info.pCommandBuffers[j]));
    }
    submit_info.commandBufferCount = command_buffers_remote[submit_info_indx].size();
    submit_info.pCommandBuffers = command_buffers_remote[submit_info_indx].data();

    submit_infos.emplace_back(std::move(submit_info));
  }

  {
    std::vector<VkFence> fences_to_wait;
    for (VkSemaphore semaphore : semaphores_to_wait_local) {
      fences_to_wait.push_back(semaphore->local_to_remote_fence);
    }
    std::thread remote_caller(
        [&dispatch_table = device_info.dispatch_table(), &command_stream = device_info.instance_info().command_stream(),
         remote_queue = device_info.GetRemoteHandle(queue), remote_fence = device_info.GetRemoteHandle(fence), device,
         remote_device = device_info.instance_info().GetRemoteHandle(device), submitCount,
         submits = std::move(submit_infos), fences = std::move(fences_to_wait),
         to_signal = std::move(semaphores_to_signal_from_remote),
         // we need to move the vectors into this thread so they don't get deleted
         unused1 = std::move(semaphores_to_wait_remote), unused2 = std::move(semaphores_to_signal_remote),
         unused3 = std::move(command_buffers_remote)]() {
          spdlog::info("VkQueueSubmit: Waiting for local semaphores");
          VkResult result = dispatch_table.WaitForFences(device, fences.size(), fences.data(), VK_TRUE, UINT64_MAX);
          if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to wait for local semaphores");
          }
          spdlog::info("VkQueueSubmit: Finished waiting for local semaphores");
          result = PackAndCallVkQueueSubmit(command_stream, remote_queue, submitCount, submits.data(), remote_fence);
          if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to submit to remote queue");
          }
          spdlog::info("VkQueueSubmit: Finished submitting to remote queue");
          result = PackAndCallVkWaitForFences(command_stream, remote_device, 1, &remote_fence, VK_TRUE, UINT64_MAX);
          if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to wait for remote fence");
          }
          spdlog::info("VkQueueSubmit: Finished waiting for remote fence");
          for (VkSemaphore semaphore : to_signal) {
            if (semaphore->state != SemaphoreState::kToBeSignaledRemote) {
              throw std::runtime_error("Semaphore was not in the correct state");
            }
            semaphore->remote_to_local_semaphore.release();
          }
          spdlog::info("VkQueueSubmit: Finished signaling semaphores");
        });
    remote_caller.detach();
  }

  return VK_SUCCESS;
}
VKAPI_ATTR VkResult VKAPI_CALL DeviceWaitIdle(VkDevice device) {
  InstanceInfo& instance_info = GetInstanceInfo(device);
  return PackAndCallVkDeviceWaitIdle(instance_info.command_stream(), instance_info.GetRemoteHandle(device));
}
}  // namespace vvk