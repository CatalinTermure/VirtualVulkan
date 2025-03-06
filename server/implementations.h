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
#endif  // VVK_SERVER_IMPLEMENTATIONS_H
