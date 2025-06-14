#include "commons/remote_call.h"
#include "layer/context/device.h"
#include "layer/functions.h"

namespace vvk {

VKAPI_ATTR VkResult VKAPI_CALL CreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo,
                                            const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer) {
  Device& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateBuffer(device_info.instance_info().command_stream(),
                                   device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator,
                                   pBuffer);
}
VKAPI_ATTR void VKAPI_CALL DestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator) {
  Device& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyBuffer(device_info.instance_info().command_stream(),
                             device_info.instance_info().GetRemoteHandle(device), buffer, pAllocator);
}

}  // namespace vvk
