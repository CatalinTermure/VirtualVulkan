// GENERATED FILE - DO NOT EDIT
// clang-format off
#ifndef VVK_SERVER_IMPLEMENTATIONS_H
#define VVK_SERVER_IMPLEMENTATIONS_H
#include <vulkan/vulkan_core.h>

#include "server/execution_context.h"
#include "vvk_server.pb.h"

void UnpackAndExecuteVkCreateInstance(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkDestroyInstance(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkEnumeratePhysicalDevices(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkGetPhysicalDeviceProperties(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkGetPhysicalDeviceFormatProperties(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCreateDevice(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkDestroyDevice(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkEnumerateInstanceExtensionProperties(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkEnumerateDeviceExtensionProperties(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkGetPhysicalDeviceMemoryProperties(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkGetPhysicalDeviceFeatures(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkGetPhysicalDeviceQueueFamilyProperties(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkGetDeviceQueue(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCreateFence(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkDestroyFence(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCreateSemaphore(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkDestroySemaphore(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkAllocateMemory(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkFreeMemory(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCreateImage(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkDestroyImage(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkBindImageMemory(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkBindImageMemory2(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkGetImageMemoryRequirements(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkGetImageMemoryRequirements2(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCreateImageView(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkDestroyImageView(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCreateCommandPool(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkDestroyCommandPool(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkAllocateCommandBuffers(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkFreeCommandBuffers(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkBeginCommandBuffer(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkEndCommandBuffer(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkGetImageSubresourceLayout(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCreateRenderPass(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkDestroyRenderPass(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCreatePipelineLayout(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkDestroyPipelineLayout(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCreateShaderModule(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkDestroyShaderModule(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCreateGraphicsPipelines(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkDestroyPipeline(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCreateFramebuffer(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkDestroyFramebuffer(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkWaitForFences(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkResetFences(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkResetCommandPool(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCmdBeginRenderPass(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCmdEndRenderPass(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCmdBindPipeline(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCmdSetViewport(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCmdSetScissor(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCmdDraw(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkQueueSubmit(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkDeviceWaitIdle(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkQueueWaitIdle(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCmdPipelineBarrier(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCmdCopyImageToBuffer(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkGetPhysicalDeviceProperties2(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkGetPhysicalDeviceFeatures2(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkSignalSemaphore(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCreateBuffer(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkDestroyBuffer(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkGetBufferMemoryRequirements(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkBindBufferMemory(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkMapMemory(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkUnmapMemory(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCmdBindVertexBuffers(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCreateSampler(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkDestroySampler(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCreateDescriptorSetLayout(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkDestroyDescriptorSetLayout(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCreatePipelineCache(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkDestroyPipelineCache(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCreateDescriptorPool(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkDestroyDescriptorPool(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkAllocateDescriptorSets(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkFreeDescriptorSets(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkUpdateDescriptorSets(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkResetCommandBuffer(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCmdBindDescriptorSets(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkFlushMappedMemoryRanges(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkInvalidateMappedMemoryRanges(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCmdCopyBuffer(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkGetBufferMemoryRequirements2KHR(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkGetImageMemoryRequirements2KHR(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkGetBufferMemoryRequirements2(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkCmdCopyBufferToImage(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
#endif  // VVK_SERVER_IMPLEMENTATIONS_H
