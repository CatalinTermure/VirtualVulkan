#include "commons/remote_call.h"
#include "layer/context/device.h"
#include "layer/functions.h"

namespace vvk {

VKAPI_ATTR VkResult VKAPI_CALL CreateDescriptorSetLayout(VkDevice device,
                                                         const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
                                                         const VkAllocationCallbacks* pAllocator,
                                                         VkDescriptorSetLayout* pSetLayout) {
  Device& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateDescriptorSetLayout(device_info.instance_info().command_stream(),
                                                device_info.instance_info().GetRemoteHandle(device), pCreateInfo,
                                                pAllocator, pSetLayout);
}
VKAPI_ATTR void VKAPI_CALL DestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout,
                                                      const VkAllocationCallbacks* pAllocator) {
  Device& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyDescriptorSetLayout(device_info.instance_info().command_stream(),
                                          device_info.instance_info().GetRemoteHandle(device), descriptorSetLayout,
                                          pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo,
                                                    const VkAllocationCallbacks* pAllocator,
                                                    VkDescriptorPool* pDescriptorPool) {
  Device& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateDescriptorPool(device_info.instance_info().command_stream(),
                                           device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator,
                                           pDescriptorPool);
}
VKAPI_ATTR void VKAPI_CALL DestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool,
                                                 const VkAllocationCallbacks* pAllocator) {
  Device& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyDescriptorPool(device_info.instance_info().command_stream(),
                                     device_info.instance_info().GetRemoteHandle(device), descriptorPool, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL AllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo,
                                                      VkDescriptorSet* pDescriptorSets) {
  Device& device_info = GetDeviceInfo(device);
  return PackAndCallVkAllocateDescriptorSets(device_info.instance_info().command_stream(),
                                             device_info.instance_info().GetRemoteHandle(device), pAllocateInfo,
                                             pDescriptorSets);
}
VKAPI_ATTR VkResult VKAPI_CALL FreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool,
                                                  uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets) {
  Device& device_info = GetDeviceInfo(device);
  return PackAndCallVkFreeDescriptorSets(device_info.instance_info().command_stream(),
                                         device_info.instance_info().GetRemoteHandle(device), descriptorPool,
                                         descriptorSetCount, pDescriptorSets);
}

VKAPI_ATTR void VKAPI_CALL UpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount,
                                                const VkWriteDescriptorSet* pDescriptorWrites,
                                                uint32_t descriptorCopyCount,
                                                const VkCopyDescriptorSet* pDescriptorCopies) {
  Device& device_info = GetDeviceInfo(device);
  PackAndCallVkUpdateDescriptorSets(device_info.instance_info().command_stream(),
                                    device_info.instance_info().GetRemoteHandle(device), descriptorWriteCount,
                                    pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
}
}  // namespace vvk
