#include "commons/remote_call.h"
#include "layer/context/instance.h"
#include "layer/functions.h"

namespace vvk {

VKAPI_ATTR VkResult VKAPI_CALL EnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount,
                                                        VkPhysicalDevice* pPhysicalDevices) {
  Instance& instance_info = GetInstanceInfo(instance);

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

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice,
                                                             VkPhysicalDeviceMemoryProperties* pMemoryProperties) {
  // TODO: investigate additional steps needed for this function
  auto& command_stream = GetInstanceInfo(physicalDevice).command_stream();
  PackAndCallVkGetPhysicalDeviceMemoryProperties(command_stream, physicalDevice, pMemoryProperties);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice,
                                                     VkPhysicalDeviceFeatures* pFeatures) {
  auto& command_stream = GetInstanceInfo(physicalDevice).command_stream();
  PackAndCallVkGetPhysicalDeviceFeatures(command_stream, physicalDevice, pFeatures);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice,
                                                                  uint32_t* pQueueFamilyPropertyCount,
                                                                  VkQueueFamilyProperties* pQueueFamilyProperties) {
  auto& command_stream = GetInstanceInfo(physicalDevice).command_stream();
  PackAndCallVkGetPhysicalDeviceQueueFamilyProperties(command_stream, physicalDevice, pQueueFamilyPropertyCount,
                                                      pQueueFamilyProperties);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceProperties2(VkPhysicalDevice physicalDevice,
                                                        VkPhysicalDeviceProperties2* pProperties) {
  Instance& instance_info = GetInstanceInfo(physicalDevice);
  PackAndCallVkGetPhysicalDeviceProperties2(instance_info.command_stream(), physicalDevice, pProperties);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceFeatures2(VkPhysicalDevice physicalDevice,
                                                      VkPhysicalDeviceFeatures2* pFeatures) {
  Instance& instance_info = GetInstanceInfo(physicalDevice);
  PackAndCallVkGetPhysicalDeviceFeatures2(instance_info.command_stream(), physicalDevice, pFeatures);
}

}  // namespace vvk
