// GENERATED FILE - DO NOT EDIT
// clang-format off
#include "vvk_server.pb.h"
#include <vulkan/vulkan_core.h>

void SetPhysicalDevice(VkPhysicalDevice physical_device);
void UnpackAndExecuteVkCreateInstance(const vvk::server::VvkRequest &request,
                                      vvk::server::VvkResponse* response);
void UnpackAndExecuteVkDestroyInstance(const vvk::server::VvkRequest &request,
                                      vvk::server::VvkResponse* response);
void UnpackAndExecuteVkEnumeratePhysicalDevices(const vvk::server::VvkRequest &request,
                                      vvk::server::VvkResponse* response);
void UnpackAndExecuteVkGetPhysicalDeviceProperties(const vvk::server::VvkRequest &request,
                                      vvk::server::VvkResponse* response);
