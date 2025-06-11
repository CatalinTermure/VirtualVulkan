#include "commons/remote_call.h"
#include "layer/context/device.h"
#include "layer/functions.h"

namespace vvk {

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
  for (VkCommandBuffer command_buffer : GetCommandBuffersForPool(commandPool)) {
    RemoveCommandBuffer(command_buffer);
  }
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
    pCommandBuffers[i] = reinterpret_cast<VkCommandBuffer>(new DispatchableObject);
    device_info.SetRemoteHandle(pCommandBuffers[i], remote_command_buffer);
    AssociateCommandBufferWithDevice(pCommandBuffers[i], device);
    AssociateCommandBufferWithPool(pCommandBuffers[i], pAllocateInfo->commandPool);
  }

  return result;
}
VKAPI_ATTR void VKAPI_CALL FreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount,
                                              const VkCommandBuffer* pCommandBuffers) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  for (uint32_t i = 0; i < commandBufferCount; i++) {
    delete reinterpret_cast<DispatchableObject*>(const_cast<VkCommandBuffer>(pCommandBuffers[i]));
  }
  std::vector<VkCommandBuffer> remote_command_buffers;
  remote_command_buffers.reserve(commandBufferCount);
  for (uint32_t i = 0; i < commandBufferCount; i++) {
    RemoveCommandBuffer(pCommandBuffers[i]);
    device_info.swapchain_render_command_buffers.erase(pCommandBuffers[i]);
    remote_command_buffers.push_back(device_info.GetRemoteHandle(pCommandBuffers[i]));
    device_info.RemoveRemoteHandle(pCommandBuffers[i]);
  }
  PackAndCallVkFreeCommandBuffers(device_info.instance_info().command_stream(),
                                  device_info.instance_info().GetRemoteHandle(device), commandPool, commandBufferCount,
                                  remote_command_buffers.data());
}

VKAPI_ATTR VkResult VKAPI_CALL ResetCommandPool(VkDevice device, VkCommandPool commandPool,
                                                VkCommandPoolResetFlags flags) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  for (VkCommandBuffer command_buffer : GetCommandBuffersForPool(commandPool)) {
    device_info.swapchain_render_command_buffers.erase(command_buffer);
  }
  return PackAndCallVkResetCommandPool(device_info.instance_info().command_stream(),
                                       device_info.instance_info().GetRemoteHandle(device), commandPool, flags);
}

}  // namespace vvk
