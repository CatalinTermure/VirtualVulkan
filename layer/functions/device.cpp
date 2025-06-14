// clang-format off
#include "layer/wsi_support.h"
// clang-format on

#include "layer/context/device.h"

#include <spdlog/spdlog.h>
#include <vulkan/vk_layer.h>

#include "commons/remote_call.h"
#include "layer/functions.h"
#include "layer/utils.h"

namespace vvk {

namespace {
const std::unordered_set<std::string> kAllowedDeviceExtensions = {VK_KHR_TIMELINE_SEMAPHORE_EXTENSION_NAME};
}  // namespace

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
  VkResult result;

  VkInstance instance = GetInstanceForPhysicalDevice(physicalDevice);
  uint32_t remote_physical_device_count = 0;
  PackAndCallVkEnumeratePhysicalDevices(instance_info.command_stream(), instance_info.GetRemoteHandle(instance),
                                        &remote_physical_device_count, nullptr);
  if (remote_physical_device_count != 1) {
    spdlog::error("Remote physical device count is not 1");
    return VK_ERROR_INITIALIZATION_FAILED;
  }
  VkPhysicalDevice remote_physical_device;
  result =
      PackAndCallVkEnumeratePhysicalDevices(instance_info.command_stream(), instance_info.GetRemoteHandle(instance),
                                            &remote_physical_device_count, &remote_physical_device);
  if (result != VK_SUCCESS) {
    return result;
  }
  instance_info.SetRemoteHandle(physicalDevice, remote_physical_device);

  grpc::ClientContext context;
  vvk::server::StreamingCapabilities streaming_capabilities;
  streaming_capabilities.set_supports_uncompressed_stream(true);
  vvk::server::StreamingCapabilities frame_streaming_capabilities;
  {
    vvk::server::VvkGetFrameStreamingCapabilitiesRequest request;
    request.set_physical_device(reinterpret_cast<uint64_t>(instance_info.GetRemoteHandle(physicalDevice)));
    instance_info.stub().GetFrameStreamingCapabilities(&context, request, &frame_streaming_capabilities);
  }

  std::optional<uint32_t> present_queue_family_index = std::nullopt;
  {
    float queue_priorities[1] = {1.0f};
    VkDeviceCreateInfo local_create_info = *pCreateInfo;
    VkDeviceQueueCreateInfo queue_create_info = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        // Even if we don't need any queue, we must still create a queue on the device as per
        // VUID-VkDeviceCreateInfo-queueCreateInfoCount-arraylength
        .queueFamilyIndex = 0,
        .queueCount = 1,
        .pQueuePriorities = queue_priorities,
    };
    local_create_info.queueCreateInfoCount = 1;
    local_create_info.pQueueCreateInfos = &queue_create_info;
    {
      uint32_t local_device_extension_count = 0;
      std::vector<VkExtensionProperties> local_device_extensions_properties;
      instance_info.dispatch_table().EnumerateDeviceExtensionProperties(physicalDevice, nullptr,
                                                                        &local_device_extension_count, nullptr);
      local_device_extensions_properties.resize(local_device_extension_count);
      instance_info.dispatch_table().EnumerateDeviceExtensionProperties(
          physicalDevice, nullptr, &local_device_extension_count, local_device_extensions_properties.data());

      bool local_device_supports_h264_decode =
          std::find_if(local_device_extensions_properties.begin(), local_device_extensions_properties.end(),
                       [](const VkExtensionProperties& extension) {
                         return strcmp(extension.extensionName, VK_KHR_VIDEO_DECODE_H264_EXTENSION_NAME) == 0;
                       }) != local_device_extensions_properties.end();

      if (frame_streaming_capabilities.supports_h264_stream() && local_device_supports_h264_decode) {
        streaming_capabilities.set_supports_h264_stream(true);
      }
    }

    auto surface = instance_info.surface();
    if (surface.has_value()) {
      uint32_t queue_family_count = 0;
      std::vector<VkQueueFamilyProperties> queue_family_properties;
      instance_info.dispatch_table().GetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queue_family_count,
                                                                            nullptr);
      queue_family_properties.resize(queue_family_count);
      instance_info.dispatch_table().GetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queue_family_count,
                                                                            queue_family_properties.data());
      for (uint32_t i = 0; i < queue_family_count; i++) {
        VkBool32 supports_present = VK_FALSE;
        instance_info.dispatch_table().GetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, *surface,
                                                                          &supports_present);
        if (supports_present) {
          queue_create_info.queueFamilyIndex = i;
          present_queue_family_index = i;
          break;
        }
      }
    }

    result = instance_info.dispatch_table().CreateDevice(physicalDevice, &local_create_info, pAllocator, pDevice);
  }

  if (result != VK_SUCCESS) {
    return result;
  }

  VmaVulkanFunctions vma_vulkan_funcs = {
      .vkGetInstanceProcAddr = nullptr,
      .vkGetDeviceProcAddr = nullptr,
      .vkGetPhysicalDeviceProperties = GetPhysicalDeviceProperties,
      .vkGetPhysicalDeviceMemoryProperties = GetPhysicalDeviceMemoryProperties,
      .vkAllocateMemory = AllocateMemory,
      .vkFreeMemory = FreeMemory,
      .vkMapMemory = MapMemory,
      .vkUnmapMemory = UnmapMemory,
      .vkFlushMappedMemoryRanges = FlushMappedMemoryRanges,
      .vkInvalidateMappedMemoryRanges = InvalidateMappedMemoryRanges,
      .vkBindBufferMemory = BindBufferMemory,
      .vkBindImageMemory = BindImageMemory,
      .vkGetBufferMemoryRequirements = GetBufferMemoryRequirements,
      .vkGetImageMemoryRequirements = GetImageMemoryRequirements,
      .vkCreateBuffer = CreateBuffer,
      .vkDestroyBuffer = DestroyBuffer,
      .vkCreateImage = CreateImage,
      .vkDestroyImage = DestroyImage,
      .vkCmdCopyBuffer = CmdCopyBuffer,
      .vkGetBufferMemoryRequirements2KHR = GetBufferMemoryRequirements2,
      .vkGetImageMemoryRequirements2KHR = GetImageMemoryRequirements2,
      .vkBindBufferMemory2KHR = reinterpret_cast<PFN_vkBindBufferMemory2KHR>(0xDEADBEEF),
      .vkBindImageMemory2KHR = BindImageMemory2,
      .vkGetPhysicalDeviceMemoryProperties2KHR =
          reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties2KHR>(0xDEADBEEF),
      .vkGetDeviceBufferMemoryRequirements = reinterpret_cast<PFN_vkGetDeviceBufferMemoryRequirements>(0xDEADBEEF),
      .vkGetDeviceImageMemoryRequirements = reinterpret_cast<PFN_vkGetDeviceImageMemoryRequirements>(0xDEADBEEF),
      .vkGetMemoryWin32HandleKHR = nullptr,
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
      .instance = instance,
      // We are using Vulkan 1.0 for VMA, because the application may only use Vulkan 1.0
      .vulkanApiVersion = VK_API_VERSION_1_0,
      .pTypeExternalMemoryHandleTypes = nullptr,
  };

  auto remote_queue_family_properties = [&]() {
    uint32_t queue_family_count;
    PackAndCallVkGetPhysicalDeviceQueueFamilyProperties(instance_info.command_stream(), physicalDevice,
                                                        &queue_family_count, nullptr);
    std::vector<VkQueueFamilyProperties> queue_family_properties(queue_family_count);
    PackAndCallVkGetPhysicalDeviceQueueFamilyProperties(instance_info.command_stream(), physicalDevice,
                                                        &queue_family_count, queue_family_properties.data());
    return queue_family_properties;
  }();

  auto remote_graphics_queue_family_index = [&]() -> std::optional<uint32_t> {
    for (uint32_t i = 0; i < pCreateInfo->queueCreateInfoCount; i++) {
      const VkDeviceQueueCreateInfo& queue_create_info = pCreateInfo->pQueueCreateInfos[i];
      if (remote_queue_family_properties[queue_create_info.queueFamilyIndex].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
        return queue_create_info.queueFamilyIndex;
      }
    }
    return std::nullopt;
  }();

  if (!remote_graphics_queue_family_index.has_value()) {
    spdlog::error("No graphics queue family found");
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  auto remote_video_queue_family_index = [&]() -> std::optional<uint32_t> {
    for (uint32_t i = 0; i < remote_queue_family_properties.size(); i++) {
      if (remote_queue_family_properties[i].queueFlags & VK_QUEUE_VIDEO_ENCODE_BIT_KHR) {
        return i;
      }
    }
    return std::nullopt;
  }();

  if (frame_streaming_capabilities.supports_h264_stream() && !remote_video_queue_family_index.has_value()) {
    spdlog::error("No video queue family found");
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  VkDevice remote_device = *pDevice;
  {
    VkDeviceCreateInfo remote_create_info = *pCreateInfo;
    RemoveStructsFromChain(reinterpret_cast<VkBaseOutStructure*>(&remote_create_info),
                           VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO);

    // Add timeline semaphore feature
    VkPhysicalDeviceVulkan12Features required_vulkan_1_2_features = {};
    required_vulkan_1_2_features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
    required_vulkan_1_2_features.timelineSemaphore = 1;
    VkPhysicalDeviceVulkan12Features* vulkan_1_2_features =
        FindStructInChain<VkPhysicalDeviceVulkan12Features, VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES>(
            remote_create_info.pNext);
    if (!vulkan_1_2_features) {
      AddStructToChain(reinterpret_cast<VkBaseOutStructure*>(&remote_create_info),
                       reinterpret_cast<VkBaseOutStructure*>(&required_vulkan_1_2_features));
    } else {
      vulkan_1_2_features->timelineSemaphore = VK_TRUE;
    }

    // Add synchronization2 feature
    VkPhysicalDeviceVulkan13Features required_vulkan_1_3_features = {};
    required_vulkan_1_3_features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
    required_vulkan_1_3_features.synchronization2 = 1;
    VkPhysicalDeviceVulkan13Features* vulkan_1_3_features =
        FindStructInChain<VkPhysicalDeviceVulkan13Features, VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES>(
            remote_create_info.pNext);
    if (!vulkan_1_3_features) {
      AddStructToChain(reinterpret_cast<VkBaseOutStructure*>(&remote_create_info),
                       reinterpret_cast<VkBaseOutStructure*>(&required_vulkan_1_3_features));
    } else {
      vulkan_1_3_features->synchronization2 = VK_TRUE;
    }

    // Add extensions
    std::vector<const char*> enabled_extensions;
    for (uint32_t i = 0; i < remote_create_info.enabledExtensionCount; i++) {
      if (kAllowedDeviceExtensions.contains(remote_create_info.ppEnabledExtensionNames[i])) {
        enabled_extensions.push_back(remote_create_info.ppEnabledExtensionNames[i]);
      }
    }

    if (frame_streaming_capabilities.supports_h264_stream()) {
      enabled_extensions.push_back(VK_KHR_VIDEO_QUEUE_EXTENSION_NAME);
      enabled_extensions.push_back(VK_KHR_VIDEO_ENCODE_QUEUE_EXTENSION_NAME);
      enabled_extensions.push_back(VK_KHR_VIDEO_ENCODE_H264_EXTENSION_NAME);
    }

    remote_create_info.enabledExtensionCount = enabled_extensions.size();
    remote_create_info.ppEnabledExtensionNames = enabled_extensions.data();

    std::vector<VkDeviceQueueCreateInfo> remote_queue_create_infos;
    remote_queue_create_infos.reserve(remote_create_info.queueCreateInfoCount);
    for (uint32_t i = 0; i < remote_create_info.queueCreateInfoCount; i++) {
      remote_queue_create_infos.push_back(remote_create_info.pQueueCreateInfos[i]);
    }

    if (frame_streaming_capabilities.supports_h264_stream()) {
      bool already_added_video_queue = false;
      for (const auto& queue_create_info : remote_queue_create_infos) {
        if (queue_create_info.queueFamilyIndex == *remote_video_queue_family_index) {
          already_added_video_queue = true;
          break;
        }
      }
      if (!already_added_video_queue) {
        VkDeviceQueueCreateInfo video_queue_create_info = {
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .queueFamilyIndex = *remote_video_queue_family_index,
            .queueCount = 1,
            .pQueuePriorities =
                remote_queue_create_infos[0].pQueuePriorities,  // Use the same priority as graphics queue
        };
        remote_queue_create_infos.push_back(video_queue_create_info);
      }
    }

    remote_create_info.queueCreateInfoCount = remote_queue_create_infos.size();
    remote_create_info.pQueueCreateInfos = remote_queue_create_infos.data();

    PackAndCallVkCreateDevice(instance_info.command_stream(), physicalDevice, &remote_create_info, pAllocator,
                              &remote_device);
    instance_info.SetRemoteHandle(*pDevice, remote_device);
  }

  Device& device_info =
      SetDeviceInfo(*pDevice, nxt_gdpa, physicalDevice, allocator_create_info, present_queue_family_index,
                    *remote_graphics_queue_family_index, *remote_video_queue_family_index, streaming_capabilities);

  for (uint32_t i = 0; i < pCreateInfo->queueCreateInfoCount; i++) {
    const VkDeviceQueueCreateInfo& queue_create_info = pCreateInfo->pQueueCreateInfos[i];
    device_info.CreateFakeQueueFamily(queue_create_info.queueFamilyIndex, queue_create_info.queueCount);
  }

  if (device_info.present_queue().has_value()) {
    AssociateQueueWithDevice(device_info.present_queue().value(), *pDevice);
  }

  device_info.fence_pool().ForAllFences([&](VkFence& fence) {
    VkFenceCreateInfo fence_create_info = {
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
    };
    VkFence remote_fence = VK_NULL_HANDLE;
    VkResult result = PackAndCallVkCreateFence(instance_info.command_stream(), remote_device, &fence_create_info,
                                               pAllocator, &remote_fence);
    if (result != VK_SUCCESS) {
      spdlog::error("Failed to create remote fence for local fence in fence pool {}: {}", (void*)fence, (int)result);
      return;
    }
    device_info.SetRemoteHandle(fence, remote_fence);
  });

  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) {
  Device& device_info = GetDeviceInfo(device);
  InstanceInfo& instance_info = device_info.instance_info();

  device_info.fence_pool().ForAllFences([&](VkFence& fence) {
    PackAndCallVkDestroyFence(instance_info.command_stream(), instance_info.GetRemoteHandle(device),
                              device_info.GetRemoteHandle(fence), pAllocator);
    device_info.RemoveRemoteHandle(fence);
    device_info.dispatch_table().DestroyFence(device, fence, pAllocator);
  });

  device_info.dispatch_table().DestroyDevice(device, pAllocator);

  PackAndCallVkDestroyDevice(instance_info.command_stream(), device_info.instance_info().GetRemoteHandle(device),
                             pAllocator);

  instance_info.RemoveRemoteHandle(device);

  RemoveDeviceInfo(device);
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

VKAPI_ATTR void VKAPI_CALL GetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex,
                                          VkQueue* pQueue) {
  Device& device_info = GetDeviceInfo(device);

  *pQueue = device_info.GetFakeQueue(queueFamilyIndex, queueIndex);

  VkQueue remote_queue = VK_NULL_HANDLE;
  PackAndCallVkGetDeviceQueue(device_info.instance_info().command_stream(),
                              device_info.instance_info().GetRemoteHandle(device), queueFamilyIndex, queueIndex,
                              &remote_queue);
  device_info.SetRemoteHandle(*pQueue, remote_queue);
  AssociateQueueWithDevice(*pQueue, device);
}

VKAPI_ATTR VkResult VKAPI_CALL DeviceWaitIdle(VkDevice device) {
  InstanceInfo& instance_info = GetInstanceInfo(device);
  return PackAndCallVkDeviceWaitIdle(instance_info.command_stream(), instance_info.GetRemoteHandle(device));
}

}  // namespace vvk
