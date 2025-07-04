// GENERATED FILE - DO NOT EDIT
// clang-format off
#ifndef VVK_COMMONS_REMOTE_CALL_H
#define VVK_COMMONS_REMOTE_CALL_H
#include "synchronized_bidi_stream.h"

#include "vulkan/vulkan_core.h"

#include <grpcpp/grpcpp.h>
#include "vvk_server.pb.h"

namespace vvk {
VkResult PackAndCallVkAllocateCommandBuffers(VvkCommandClientBidiStream& stream, VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers);
VkResult PackAndCallVkAllocateDescriptorSets(VvkCommandClientBidiStream& stream, VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets);
VkResult PackAndCallVkAllocateMemory(VvkCommandClientBidiStream& stream, VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory);
VkResult PackAndCallVkBeginCommandBuffer(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo);
VkResult PackAndCallVkBindBufferMemory(VvkCommandClientBidiStream& stream, VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset);
VkResult PackAndCallVkBindImageMemory(VvkCommandClientBidiStream& stream, VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset);
VkResult PackAndCallVkBindImageMemory2(VvkCommandClientBidiStream& stream, VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos);
void PackAndCallVkCmdBeginRenderPass(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents);
void PackAndCallVkCmdBindDescriptorSets(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets);
void PackAndCallVkCmdBindIndexBuffer(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType);
void PackAndCallVkCmdBindPipeline(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline);
void PackAndCallVkCmdBindVertexBuffers(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets);
void PackAndCallVkCmdCopyBuffer(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions);
void PackAndCallVkCmdCopyBufferToImage(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions);
void PackAndCallVkCmdCopyImage(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions);
void PackAndCallVkCmdCopyImageToBuffer(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions);
void PackAndCallVkCmdDispatch(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ);
void PackAndCallVkCmdDraw(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
void PackAndCallVkCmdDrawIndexed(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance);
void PackAndCallVkCmdEndRenderPass(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer);
void PackAndCallVkCmdPipelineBarrier(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers);
void PackAndCallVkCmdPushConstants(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues);
void PackAndCallVkCmdSetScissor(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors);
void PackAndCallVkCmdSetViewport(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports);
VkResult PackAndCallVkCreateBuffer(VvkCommandClientBidiStream& stream, VkDevice device, const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer);
VkResult PackAndCallVkCreateCommandPool(VvkCommandClientBidiStream& stream, VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool);
VkResult PackAndCallVkCreateComputePipelines(VvkCommandClientBidiStream& stream, VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines);
VkResult PackAndCallVkCreateDescriptorPool(VvkCommandClientBidiStream& stream, VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool);
VkResult PackAndCallVkCreateDescriptorSetLayout(VvkCommandClientBidiStream& stream, VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* pSetLayout);
VkResult PackAndCallVkCreateDevice(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice);
VkResult PackAndCallVkCreateFence(VvkCommandClientBidiStream& stream, VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence);
VkResult PackAndCallVkCreateFramebuffer(VvkCommandClientBidiStream& stream, VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer);
VkResult PackAndCallVkCreateGraphicsPipelines(VvkCommandClientBidiStream& stream, VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines);
VkResult PackAndCallVkCreateImage(VvkCommandClientBidiStream& stream, VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage);
VkResult PackAndCallVkCreateImageView(VvkCommandClientBidiStream& stream, VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView);
VkResult PackAndCallVkCreateInstance(VvkCommandClientBidiStream& stream, const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance);
VkResult PackAndCallVkCreatePipelineCache(VvkCommandClientBidiStream& stream, VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache);
VkResult PackAndCallVkCreatePipelineLayout(VvkCommandClientBidiStream& stream, VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout);
VkResult PackAndCallVkCreateRenderPass(VvkCommandClientBidiStream& stream, VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass);
VkResult PackAndCallVkCreateSampler(VvkCommandClientBidiStream& stream, VkDevice device, const VkSamplerCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler);
VkResult PackAndCallVkCreateSemaphore(VvkCommandClientBidiStream& stream, VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore);
VkResult PackAndCallVkCreateShaderModule(VvkCommandClientBidiStream& stream, VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule);
void PackAndCallVkDestroyBuffer(VvkCommandClientBidiStream& stream, VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator);
void PackAndCallVkDestroyCommandPool(VvkCommandClientBidiStream& stream, VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator);
void PackAndCallVkDestroyDescriptorPool(VvkCommandClientBidiStream& stream, VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator);
void PackAndCallVkDestroyDescriptorSetLayout(VvkCommandClientBidiStream& stream, VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks* pAllocator);
void PackAndCallVkDestroyDevice(VvkCommandClientBidiStream& stream, VkDevice device, const VkAllocationCallbacks* pAllocator);
void PackAndCallVkDestroyFence(VvkCommandClientBidiStream& stream, VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator);
void PackAndCallVkDestroyFramebuffer(VvkCommandClientBidiStream& stream, VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator);
void PackAndCallVkDestroyImage(VvkCommandClientBidiStream& stream, VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator);
void PackAndCallVkDestroyImageView(VvkCommandClientBidiStream& stream, VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator);
void PackAndCallVkDestroyInstance(VvkCommandClientBidiStream& stream, VkInstance instance, const VkAllocationCallbacks* pAllocator);
void PackAndCallVkDestroyPipeline(VvkCommandClientBidiStream& stream, VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* pAllocator);
void PackAndCallVkDestroyPipelineCache(VvkCommandClientBidiStream& stream, VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks* pAllocator);
void PackAndCallVkDestroyPipelineLayout(VvkCommandClientBidiStream& stream, VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator);
void PackAndCallVkDestroyRenderPass(VvkCommandClientBidiStream& stream, VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator);
void PackAndCallVkDestroySampler(VvkCommandClientBidiStream& stream, VkDevice device, VkSampler sampler, const VkAllocationCallbacks* pAllocator);
void PackAndCallVkDestroySemaphore(VvkCommandClientBidiStream& stream, VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator);
void PackAndCallVkDestroyShaderModule(VvkCommandClientBidiStream& stream, VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkDeviceWaitIdle(VvkCommandClientBidiStream& stream, VkDevice device);
VkResult PackAndCallVkEndCommandBuffer(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer);
VkResult PackAndCallVkEnumerateDeviceExtensionProperties(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties);
VkResult PackAndCallVkEnumerateInstanceExtensionProperties(VvkCommandClientBidiStream& stream, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties);
VkResult PackAndCallVkEnumeratePhysicalDevices(VvkCommandClientBidiStream& stream, VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices);
VkResult PackAndCallVkFlushMappedMemoryRanges(VvkCommandClientBidiStream& stream, VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges);
void PackAndCallVkFreeCommandBuffers(VvkCommandClientBidiStream& stream, VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers);
VkResult PackAndCallVkFreeDescriptorSets(VvkCommandClientBidiStream& stream, VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets);
void PackAndCallVkFreeMemory(VvkCommandClientBidiStream& stream, VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator);
void PackAndCallVkGetBufferMemoryRequirements(VvkCommandClientBidiStream& stream, VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements);
void PackAndCallVkGetBufferMemoryRequirements2(VvkCommandClientBidiStream& stream, VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements);
void PackAndCallVkGetBufferMemoryRequirements2KHR(VvkCommandClientBidiStream& stream, VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements);
void PackAndCallVkGetDeviceQueue(VvkCommandClientBidiStream& stream, VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue);
void PackAndCallVkGetImageMemoryRequirements(VvkCommandClientBidiStream& stream, VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements);
void PackAndCallVkGetImageMemoryRequirements2(VvkCommandClientBidiStream& stream, VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements);
void PackAndCallVkGetImageMemoryRequirements2KHR(VvkCommandClientBidiStream& stream, VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements);
void PackAndCallVkGetImageSubresourceLayout(VvkCommandClientBidiStream& stream, VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout);
void PackAndCallVkGetPhysicalDeviceFeatures(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures);
void PackAndCallVkGetPhysicalDeviceFeatures2(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2* pFeatures);
void PackAndCallVkGetPhysicalDeviceFormatProperties(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties* pFormatProperties);
void PackAndCallVkGetPhysicalDeviceMemoryProperties(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* pMemoryProperties);
void PackAndCallVkGetPhysicalDeviceProperties(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties);
void PackAndCallVkGetPhysicalDeviceProperties2(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2* pProperties);
void PackAndCallVkGetPhysicalDeviceQueueFamilyProperties(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties);
VkResult PackAndCallVkInvalidateMappedMemoryRanges(VvkCommandClientBidiStream& stream, VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges);
VkResult PackAndCallVkMapMemory(VvkCommandClientBidiStream& stream, VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData);
VkResult PackAndCallVkQueueSubmit(VvkCommandClientBidiStream& stream, VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence);
VkResult PackAndCallVkQueueWaitIdle(VvkCommandClientBidiStream& stream, VkQueue queue);
VkResult PackAndCallVkResetCommandBuffer(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags);
VkResult PackAndCallVkResetCommandPool(VvkCommandClientBidiStream& stream, VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags);
VkResult PackAndCallVkResetFences(VvkCommandClientBidiStream& stream, VkDevice device, uint32_t fenceCount, const VkFence* pFences);
VkResult PackAndCallVkSignalSemaphore(VvkCommandClientBidiStream& stream, VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo);
void PackAndCallVkUnmapMemory(VvkCommandClientBidiStream& stream, VkDevice device, VkDeviceMemory memory);
void PackAndCallVkUpdateDescriptorSets(VvkCommandClientBidiStream& stream, VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies);
VkResult PackAndCallVkWaitForFences(VvkCommandClientBidiStream& stream, VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout);
}  // namespace vvk

#endif  // VVK_COMMONS_REMOTE_CALL_H
