#include "commons/remote_call.h"
#include "layer/context/device.h"
#include "layer/functions.h"
#include "layer/sempahore_handle.h"

namespace vvk {
VKAPI_ATTR VkResult VKAPI_CALL CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo,
                                               const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore) {
  *pSemaphore = new VkSemaphore_T;
  Device& device_info = GetDeviceInfo(device);
  InstanceInfo& instance_info = device_info.instance_info();
  VkResult result =
      device_info.dispatch_table().CreateSemaphore(device, pCreateInfo, pAllocator, &(*pSemaphore)->local_handle);
  if (result != VK_SUCCESS) {
    return result;
  }
  VkSemaphore remote_semaphore = VK_NULL_HANDLE;
  result = PackAndCallVkCreateSemaphore(device_info.instance_info().command_stream(),
                                        device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator,
                                        &remote_semaphore);
  if (result != VK_SUCCESS) {
    device_info.dispatch_table().DestroySemaphore(device, (*pSemaphore)->local_handle, pAllocator);
    return result;
  }

  (*pSemaphore)->remote_handle = remote_semaphore;
  (*pSemaphore)->state = SemaphoreState::kUnsignaled;
  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroySemaphore(VkDevice device, VkSemaphore semaphore,
                                            const VkAllocationCallbacks* pAllocator) {
  Device& device_info = GetDeviceInfo(device);
  InstanceInfo& instance_info = device_info.instance_info();
  device_info.dispatch_table().DestroySemaphore(device, semaphore->local_handle, pAllocator);
  PackAndCallVkDestroySemaphore(instance_info.command_stream(), instance_info.GetRemoteHandle(device),
                                semaphore->remote_handle, pAllocator);
  delete semaphore;
}

VKAPI_ATTR VkResult VKAPI_CALL SignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) {
  Device& device_info = GetDeviceInfo(device);
  VkSemaphoreSignalInfo signal_info = *pSignalInfo;
  signal_info.semaphore = signal_info.semaphore->remote_handle;
  return PackAndCallVkSignalSemaphore(device_info.instance_info().command_stream(),
                                      device_info.instance_info().GetRemoteHandle(device), &signal_info);
}

}  // namespace vvk
