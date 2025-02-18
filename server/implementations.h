// GENERATED FILE - DO NOT EDIT
// clang-format off
#ifndef VVK_SERVER_IMPLEMENTATIONS_H
#define VVK_SERVER_IMPLEMENTATIONS_H
#include <vulkan/vulkan_core.h>

#include "execution_context.h"
#include "vvk_server.pb.h"

void UnpackAndExecuteVkCreateInstance(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkDestroyInstance(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkEnumeratePhysicalDevices(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);
void UnpackAndExecuteVkGetPhysicalDeviceProperties(vvk::ExecutionContext& context,
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
#endif  // VVK_SERVER_IMPLEMENTATIONS_H
