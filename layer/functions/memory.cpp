// clang-format off
#include "layer/wsi_support.h"
// clang-format on

#include "commons/remote_call.h"
#include "layer/context/device.h"
#include "layer/functions.h"

namespace vvk {

VKAPI_ATTR VkResult VKAPI_CALL AllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo,
                                              const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  VkResult result = PackAndCallVkAllocateMemory(device_info.instance_info().command_stream(),
                                                device_info.instance_info().GetRemoteHandle(device), pAllocateInfo,
                                                pAllocator, pMemory);
  if (result != VK_SUCCESS) {
    return result;
  }

  device_info.RegisterMemorySize(*pMemory, pAllocateInfo->allocationSize);
  return result;
}

VKAPI_ATTR void VKAPI_CALL FreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkFreeMemory(device_info.instance_info().command_stream(),
                          device_info.instance_info().GetRemoteHandle(device), memory, pAllocator);
  device_info.UnregisterMemorySize(memory);
}

VKAPI_ATTR VkResult VKAPI_CALL MapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size,
                                         VkMemoryMapFlags flags, void** ppData) {
  DeviceInfo& device_info = GetDeviceInfo(device);

  if (size == VK_WHOLE_SIZE) {
    size = device_info.GetMemorySize(memory) - offset;
  }

  *ppData = malloc(size);
  if (ppData == nullptr) {
    return VK_ERROR_OUT_OF_HOST_MEMORY;
  }
  void* remote_address = nullptr;
  VkResult result = PackAndCallVkMapMemory(device_info.instance_info().command_stream(),
                                           device_info.instance_info().GetRemoteHandle(device), memory, offset, size,
                                           flags, &remote_address);
  if (result != VK_SUCCESS) {
    free(*ppData);
    return result;
  }

  device_info.AddMappedMemory(*ppData, remote_address, memory, size);

  return result;
}

VKAPI_ATTR void VKAPI_CALL UnmapMemory(VkDevice device, VkDeviceMemory memory) {
  DeviceInfo& device_info = GetDeviceInfo(device);

  device_info.UploadMappedMemory(memory);

  PackAndCallVkUnmapMemory(device_info.instance_info().command_stream(),
                           device_info.instance_info().GetRemoteHandle(device), memory);

  device_info.RemoveMappedMemory(memory);
}

VKAPI_ATTR VkResult VKAPI_CALL FlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount,
                                                       const VkMappedMemoryRange* pMemoryRanges) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  for (uint32_t i = 0; i < memoryRangeCount; i++) {
    device_info.UploadMappedMemory(pMemoryRanges[i].memory);
  }
  return PackAndCallVkFlushMappedMemoryRanges(device_info.instance_info().command_stream(),
                                              device_info.instance_info().GetRemoteHandle(device), memoryRangeCount,
                                              pMemoryRanges);
}

VKAPI_ATTR VkResult VKAPI_CALL InvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount,
                                                            const VkMappedMemoryRange* pMemoryRanges) {
  throw std::runtime_error("InvalidateMappedMemoryRanges is not supported in VirtualVulkan.");
}

VKAPI_ATTR void VKAPI_CALL GetBufferMemoryRequirements2KHR(VkDevice device,
                                                           const VkBufferMemoryRequirementsInfo2* pInfo,
                                                           VkMemoryRequirements2* pMemoryRequirements) {
  GetBufferMemoryRequirements2(device, pInfo, pMemoryRequirements);
}

VKAPI_ATTR void VKAPI_CALL GetImageMemoryRequirements2KHR(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo,
                                                          VkMemoryRequirements2* pMemoryRequirements) {
  GetImageMemoryRequirements2(device, pInfo, pMemoryRequirements);
}

VKAPI_ATTR void VKAPI_CALL GetBufferMemoryRequirements2(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo,
                                                        VkMemoryRequirements2* pMemoryRequirements) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkGetBufferMemoryRequirements2(device_info.instance_info().command_stream(),
                                            device_info.instance_info().GetRemoteHandle(device), pInfo,
                                            pMemoryRequirements);
}

VKAPI_ATTR void VKAPI_CALL GetBufferMemoryRequirements(VkDevice device, VkBuffer buffer,
                                                       VkMemoryRequirements* pMemoryRequirements) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkGetBufferMemoryRequirements(device_info.instance_info().command_stream(),
                                           device_info.instance_info().GetRemoteHandle(device), buffer,
                                           pMemoryRequirements);
}

VKAPI_ATTR VkResult VKAPI_CALL BindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory,
                                                VkDeviceSize memoryOffset) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkBindBufferMemory(device_info.instance_info().command_stream(),
                                       device_info.instance_info().GetRemoteHandle(device), buffer, memory,
                                       memoryOffset);
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

}  // namespace vvk
