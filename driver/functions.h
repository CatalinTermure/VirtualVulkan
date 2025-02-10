#include <vulkan/vulkan_core.h>

namespace vvk {

VKAPI_ATTR VkResult VKAPI_CALL CreateInstance(const VkInstanceCreateInfo* pCreateInfo,
                                              const VkAllocationCallbacks* pAllocator, VkInstance* pInstance);

VKAPI_ATTR VkResult VKAPI_CALL EnumerateInstanceExtensionProperties(const char* pLayerName, uint32_t* pPropertyCount,
                                                                    VkExtensionProperties* pProperties);

VKAPI_ATTR void VKAPI_CALL DestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator);

VKAPI_ATTR VkResult VKAPI_CALL EnumerateInstanceVersion(uint32_t* pApiVersion);

VKAPI_ATTR VkResult VKAPI_CALL EnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount,
                                                        VkPhysicalDevice* pPhysicalDevices);

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice,
                                                         VkPhysicalDeviceFeatures* pFeatures);

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceFeatures2(VkPhysicalDevice physicalDevice,
                                                          VkPhysicalDeviceFeatures2* pFeatures);

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format,
                                                                 VkFormatProperties* pFormatProperties);

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format,
                                                                      VkImageType type, VkImageTiling tiling,
                                                                      VkImageUsageFlags usage, VkImageCreateFlags flags,
                                                                      VkImageFormatProperties* pImageFormatProperties);

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice,
                                                           VkPhysicalDeviceProperties* pProperties);

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceProperties2(VkPhysicalDevice physicalDevice,
                                                            VkPhysicalDeviceProperties2* pProperties);

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice,
                                                                      uint32_t* pQueueFamilyPropertyCount,
                                                                      VkQueueFamilyProperties* pQueueFamilyProperties);

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice,
                                                                 VkPhysicalDeviceMemoryProperties* pMemoryProperties);

VKAPI_ATTR VkResult VKAPI_CALL CreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo,
                                            const VkAllocationCallbacks* pAllocator, VkDevice* pDevice);

VKAPI_ATTR void VKAPI_CALL DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator);

VKAPI_ATTR VkResult VKAPI_CALL EnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice,
                                                                  const char* pLayerName, uint32_t* pPropertyCount,
                                                                  VkExtensionProperties* pProperties);

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceSparseImageFormatProperties(VkPhysicalDevice physicalDevice,
                                                                        VkFormat format, VkImageType type,
                                                                        VkSampleCountFlagBits samples,
                                                                        VkImageUsageFlags usage, VkImageTiling tiling,
                                                                        uint32_t* pPropertyCount,
                                                                        VkSparseImageFormatProperties* pProperties);

}  // namespace vvk