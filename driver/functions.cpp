#include "functions.h"

#include <spdlog/spdlog.h>
#include <vulkan/vk_icd.h>

#include <unordered_map>

#include "mem_management.h"

struct VkInstance_T {
  VK_LOADER_DATA loader_data;
  VkInstanceCreateInfo create_info;
  std::vector<VkPhysicalDevice> physical_devices;
};

struct VkPhysicalDevice_T {
  VK_LOADER_DATA loader_data;
  VkInstance instance;
};

struct VkDevice_T {
  VK_LOADER_DATA loader_data;
  VkInstance instance;
  VkPhysicalDevice physical_device;
};

namespace vvk {

VKAPI_ATTR VkResult VKAPI_CALL CreateInstance(const VkInstanceCreateInfo* pCreateInfo,
                                              const VkAllocationCallbacks* pAllocator, VkInstance* pInstance) {
  spdlog::info("CreateInstance");
  VkInstance instance = AllocateVkHandle<VkInstance_T>();
  instance->create_info = *pCreateInfo;
  *pInstance = instance;
  spdlog::info("Instance created: {:p}", (void*)instance);
  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL EnumerateInstanceExtensionProperties(const char* pLayerName, uint32_t* pPropertyCount,
                                                                    VkExtensionProperties* pProperties) {
  // TODO: Implement
  return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL DestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator) {
  if (instance == VK_NULL_HANDLE) {
    return;
  }
  delete instance;
}

VKAPI_ATTR VkResult VKAPI_CALL EnumerateInstanceVersion(uint32_t* pApiVersion) {
  *pApiVersion = VK_API_VERSION_1_4;
  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL EnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount,
                                                        VkPhysicalDevice* pPhysicalDevices) {
  if (pPhysicalDevices) {
    if (instance->physical_devices.empty()) {
      VkPhysicalDevice vvk_device = AllocateVkHandle<VkPhysicalDevice_T>();
      vvk_device->instance = instance;
      instance->physical_devices.push_back(vvk_device);
      *pPhysicalDevices = vvk_device;
    }
    *pPhysicalDevices = instance->physical_devices[0];
    spdlog::info("Physical device handle: {:p}; Instance handle: {:p}", (void*)instance->physical_devices[0],
                 (void*)instance);
  } else {
    *pPhysicalDeviceCount = 1;
  }
  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice,
                                                         VkPhysicalDeviceFeatures* pFeatures) {
  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceFeatures2(VkPhysicalDevice physicalDevice,
                                                          VkPhysicalDeviceFeatures2* pFeatures) {
  pFeatures->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
  pFeatures->pNext = nullptr;
  return GetPhysicalDeviceFeatures(physicalDevice, &pFeatures->features);
}

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format,
                                                                 VkFormatProperties* pFormatProperties) {
  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format,
                                                                      VkImageType type, VkImageTiling tiling,
                                                                      VkImageUsageFlags usage, VkImageCreateFlags flags,
                                                                      VkImageFormatProperties* pImageFormatProperties) {
  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice,
                                                           VkPhysicalDeviceProperties* pProperties) {
  pProperties->apiVersion = VK_API_VERSION_1_4;
  pProperties->driverVersion = 1;
  pProperties->vendorID = 0xDEAD;
  pProperties->deviceID = 0xDEADBEEF;
  pProperties->deviceType = VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU;
  strcpy(pProperties->deviceName, "VirtualVulkan Device");
  memset(pProperties->pipelineCacheUUID, 0x42, VK_UUID_SIZE);
  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceProperties2(VkPhysicalDevice physicalDevice,
                                                            VkPhysicalDeviceProperties2* pProperties) {
  return GetPhysicalDeviceProperties(physicalDevice, &pProperties->properties);
}

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice,
                                                                      uint32_t* pQueueFamilyPropertyCount,
                                                                      VkQueueFamilyProperties* pQueueFamilyProperties) {
  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice,
                                                                 VkPhysicalDeviceMemoryProperties* pMemoryProperties) {
  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL CreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo,
                                            const VkAllocationCallbacks* pAllocator, VkDevice* pDevice) {
  VkDevice device = AllocateVkHandle<VkDevice_T>();
  device->physical_device = physicalDevice;
  device->instance = physicalDevice->instance;
  *pDevice = device;
  spdlog::info("Device handle: {:p}; Physical device handle: {:p}; Instance handle: {:p}", (void*)device,
               (void*)physicalDevice, (void*)device->instance);

  return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) {
  if (device) {
    delete device;
  }
}

VKAPI_ATTR VkResult VKAPI_CALL EnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice,
                                                                  const char* pLayerName, uint32_t* pPropertyCount,
                                                                  VkExtensionProperties* pProperties) {
  return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceSparseImageFormatProperties(VkPhysicalDevice physicalDevice,
                                                                        VkFormat format, VkImageType type,
                                                                        VkSampleCountFlagBits samples,
                                                                        VkImageUsageFlags usage, VkImageTiling tiling,
                                                                        uint32_t* pPropertyCount,
                                                                        VkSparseImageFormatProperties* pProperties) {}

}  // namespace vvk