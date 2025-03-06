// GENERATED FILE - DO NOT EDIT
// clang-format off
#ifndef VVK_COMMONS_REMOTE_CALL_H
#define VVK_COMMONS_REMOTE_CALL_H
#include "vulkan/vulkan_core.h"

#include <grpcpp/grpcpp.h>
#include "vvk_server.pb.h"

namespace vvk {
VkResult PackAndCallVkCreateInstance(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance);
void PackAndCallVkDestroyInstance(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkInstance instance, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkEnumeratePhysicalDevices(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices);
void PackAndCallVkGetPhysicalDeviceProperties(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties);
void PackAndCallVkGetPhysicalDeviceFormatProperties(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties* pFormatProperties);
VkResult PackAndCallVkCreateDevice(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice);
void PackAndCallVkDestroyDevice(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkEnumerateInstanceExtensionProperties(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties);
VkResult PackAndCallVkEnumerateDeviceExtensionProperties(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkPhysicalDevice physicalDevice, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties);
void PackAndCallVkGetPhysicalDeviceMemoryProperties(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* pMemoryProperties);
void PackAndCallVkGetPhysicalDeviceFeatures(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures);
void PackAndCallVkGetPhysicalDeviceQueueFamilyProperties(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties);
void PackAndCallVkGetDeviceQueue(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue);
VkResult PackAndCallVkCreateFence(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence);
void PackAndCallVkDestroyFence(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkCreateSemaphore(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore);
void PackAndCallVkDestroySemaphore(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkAllocateMemory(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory);
void PackAndCallVkFreeMemory(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkCreateImage(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage);
void PackAndCallVkDestroyImage(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkBindImageMemory(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset);
VkResult PackAndCallVkBindImageMemory2(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos);
void PackAndCallVkGetImageMemoryRequirements(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements);
void PackAndCallVkGetImageMemoryRequirements2(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements);
VkResult PackAndCallVkCreateImageView(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView);
void PackAndCallVkDestroyImageView(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkCreateCommandPool(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool);
void PackAndCallVkDestroyCommandPool(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkAllocateCommandBuffers(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers);
void PackAndCallVkFreeCommandBuffers(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers);
VkResult PackAndCallVkBeginCommandBuffer(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo);
VkResult PackAndCallVkEndCommandBuffer(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkCommandBuffer commandBuffer);
void PackAndCallVkGetImageSubresourceLayout(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout);
VkResult PackAndCallVkCreateRenderPass(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass);
void PackAndCallVkDestroyRenderPass(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator);
}  // namespace vvk

#endif  // VVK_COMMONS_REMOTE_CALL_H
