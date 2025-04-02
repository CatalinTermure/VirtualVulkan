// GENERATED FILE - DO NOT EDIT
// clang-format off
#ifndef VVK_COMMONS_REMOTE_CALL_H
#define VVK_COMMONS_REMOTE_CALL_H
#include "bidi_stream.h"

#include "vulkan/vulkan_core.h"

#include <grpcpp/grpcpp.h>
#include "vvk_server.pb.h"

namespace vvk {
VkResult PackAndCallVkCreateInstance(ClientBidiStream& stream, const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance);
void PackAndCallVkDestroyInstance(ClientBidiStream& stream, VkInstance instance, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkEnumeratePhysicalDevices(ClientBidiStream& stream, VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices);
void PackAndCallVkGetPhysicalDeviceProperties(ClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties);
void PackAndCallVkGetPhysicalDeviceFormatProperties(ClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties* pFormatProperties);
VkResult PackAndCallVkCreateDevice(ClientBidiStream& stream, VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice);
void PackAndCallVkDestroyDevice(ClientBidiStream& stream, VkDevice device, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkEnumerateInstanceExtensionProperties(ClientBidiStream& stream, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties);
VkResult PackAndCallVkEnumerateDeviceExtensionProperties(ClientBidiStream& stream, VkPhysicalDevice physicalDevice, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties);
void PackAndCallVkGetPhysicalDeviceMemoryProperties(ClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* pMemoryProperties);
void PackAndCallVkGetPhysicalDeviceFeatures(ClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures);
void PackAndCallVkGetPhysicalDeviceQueueFamilyProperties(ClientBidiStream& stream, VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties);
void PackAndCallVkGetDeviceQueue(ClientBidiStream& stream, VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue);
VkResult PackAndCallVkCreateFence(ClientBidiStream& stream, VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence);
void PackAndCallVkDestroyFence(ClientBidiStream& stream, VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkCreateSemaphore(ClientBidiStream& stream, VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore);
void PackAndCallVkDestroySemaphore(ClientBidiStream& stream, VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkAllocateMemory(ClientBidiStream& stream, VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory);
void PackAndCallVkFreeMemory(ClientBidiStream& stream, VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkCreateImage(ClientBidiStream& stream, VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage);
void PackAndCallVkDestroyImage(ClientBidiStream& stream, VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkBindImageMemory(ClientBidiStream& stream, VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset);
VkResult PackAndCallVkBindImageMemory2(ClientBidiStream& stream, VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos);
void PackAndCallVkGetImageMemoryRequirements(ClientBidiStream& stream, VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements);
void PackAndCallVkGetImageMemoryRequirements2(ClientBidiStream& stream, VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements);
VkResult PackAndCallVkCreateImageView(ClientBidiStream& stream, VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView);
void PackAndCallVkDestroyImageView(ClientBidiStream& stream, VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkCreateCommandPool(ClientBidiStream& stream, VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool);
void PackAndCallVkDestroyCommandPool(ClientBidiStream& stream, VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkAllocateCommandBuffers(ClientBidiStream& stream, VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers);
void PackAndCallVkFreeCommandBuffers(ClientBidiStream& stream, VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers);
VkResult PackAndCallVkBeginCommandBuffer(ClientBidiStream& stream, VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo);
VkResult PackAndCallVkEndCommandBuffer(ClientBidiStream& stream, VkCommandBuffer commandBuffer);
void PackAndCallVkGetImageSubresourceLayout(ClientBidiStream& stream, VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout);
VkResult PackAndCallVkCreateRenderPass(ClientBidiStream& stream, VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass);
void PackAndCallVkDestroyRenderPass(ClientBidiStream& stream, VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkCreatePipelineLayout(ClientBidiStream& stream, VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout);
void PackAndCallVkDestroyPipelineLayout(ClientBidiStream& stream, VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkCreateShaderModule(ClientBidiStream& stream, VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule);
void PackAndCallVkDestroyShaderModule(ClientBidiStream& stream, VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkCreateGraphicsPipelines(ClientBidiStream& stream, VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines);
void PackAndCallVkDestroyPipeline(ClientBidiStream& stream, VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkCreateFramebuffer(ClientBidiStream& stream, VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer);
void PackAndCallVkDestroyFramebuffer(ClientBidiStream& stream, VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkWaitForFences(ClientBidiStream& stream, VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout);
VkResult PackAndCallVkResetFences(ClientBidiStream& stream, VkDevice device, uint32_t fenceCount, const VkFence* pFences);
VkResult PackAndCallVkResetCommandPool(ClientBidiStream& stream, VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags);
void PackAndCallVkCmdBeginRenderPass(ClientBidiStream& stream, VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents);
void PackAndCallVkCmdEndRenderPass(ClientBidiStream& stream, VkCommandBuffer commandBuffer);
void PackAndCallVkCmdBindPipeline(ClientBidiStream& stream, VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline);
void PackAndCallVkCmdSetViewport(ClientBidiStream& stream, VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports);
void PackAndCallVkCmdSetScissor(ClientBidiStream& stream, VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors);
void PackAndCallVkCmdDraw(ClientBidiStream& stream, VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
VkResult PackAndCallVkQueueSubmit(ClientBidiStream& stream, VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence);
VkResult PackAndCallVkDeviceWaitIdle(ClientBidiStream& stream, VkDevice device);
}  // namespace vvk

#endif  // VVK_COMMONS_REMOTE_CALL_H
