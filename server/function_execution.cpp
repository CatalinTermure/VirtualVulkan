#include "function_execution.h"

#include <spdlog/spdlog.h>

#include "implementations.h"
#include "manual_implementations.h"

namespace vvk::server {

namespace {

const std::unordered_map<
    std::string, std::function<void(vvk::ExecutionContext&, const vvk::server::VvkRequest&, vvk::server::VvkResponse*)>>
    g_jump_table = {
        {"vkCreateInstance", UnpackAndExecuteVkCreateInstanceManual},
        {"vkDestroyInstance", UnpackAndExecuteVkDestroyInstance},
        {"vkEnumeratePhysicalDevices", UnpackAndExecuteVkEnumeratePhysicalDevices},
        {"vkGetPhysicalDeviceProperties", UnpackAndExecuteVkGetPhysicalDeviceProperties},
        {"vkCreateDevice", UnpackAndExecuteVkCreateDevice},
        {"vkDestroyDevice", UnpackAndExecuteVkDestroyDevice},
        {"vkEnumerateInstanceExtensionProperties", UnpackAndExecuteVkEnumerateInstanceExtensionProperties},
        {"vkEnumerateDeviceExtensionProperties", UnpackAndExecuteVkEnumerateDeviceExtensionProperties},
        {"vkGetPhysicalDeviceMemoryProperties", UnpackAndExecuteVkGetPhysicalDeviceMemoryProperties},
        {"vkGetPhysicalDeviceFeatures", UnpackAndExecuteVkGetPhysicalDeviceFeatures},
        {"vkGetPhysicalDeviceQueueFamilyProperties", UnpackAndExecuteVkGetPhysicalDeviceQueueFamilyProperties},
        {"vkGetDeviceQueue", UnpackAndExecuteVkGetDeviceQueue},
};

}  // namespace

void UnpackAndExecuteFunction(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request,
                              vvk::server::VvkResponse* response) {
  auto it = g_jump_table.find(request.method());
  if (it != g_jump_table.end()) {
    it->second(context, request, response);
  } else {
    spdlog::error("Unknown method: {}", request.method());
  }
}
}  // namespace vvk::server