#include "function_execution.h"

#include <spdlog/spdlog.h>

#include "server/implementations.h"
#include "server/manual_implementations.h"

namespace vvk::server {

namespace {

const std::unordered_map<
    std::string, std::function<void(vvk::ExecutionContext&, const vvk::server::VvkRequest&, vvk::server::VvkResponse*)>>
    g_jump_table = {
        {"vkCreateInstance", UnpackAndExecuteVkCreateInstanceManual},
        {"vkDestroyInstance", UnpackAndExecuteVkDestroyInstance},
        {"vkEnumeratePhysicalDevices", UnpackAndExecuteVkEnumeratePhysicalDevices},
        {"vkGetPhysicalDeviceProperties", UnpackAndExecuteVkGetPhysicalDeviceProperties},
        {"vkGetPhysicalDeviceFormatProperties", UnpackAndExecuteVkGetPhysicalDeviceFormatProperties},
        {"vkCreateDevice", UnpackAndExecuteVkCreateDevice},
        {"vkDestroyDevice", UnpackAndExecuteVkDestroyDevice},
        {"vkEnumerateInstanceExtensionProperties", UnpackAndExecuteVkEnumerateInstanceExtensionProperties},
        {"vkEnumerateDeviceExtensionProperties", UnpackAndExecuteVkEnumerateDeviceExtensionProperties},
        {"vkGetPhysicalDeviceMemoryProperties", UnpackAndExecuteVkGetPhysicalDeviceMemoryProperties},
        {"vkGetPhysicalDeviceFeatures", UnpackAndExecuteVkGetPhysicalDeviceFeatures},
        {"vkGetPhysicalDeviceQueueFamilyProperties", UnpackAndExecuteVkGetPhysicalDeviceQueueFamilyProperties},
        {"vkGetDeviceQueue", UnpackAndExecuteVkGetDeviceQueue},
        {"vkCreateFence", UnpackAndExecuteVkCreateFence},
        {"vkDestroyFence", UnpackAndExecuteVkDestroyFence},
        {"vkCreateSemaphore", UnpackAndExecuteVkCreateSemaphore},
        {"vkDestroySemaphore", UnpackAndExecuteVkDestroySemaphore},
        {"vkAllocateMemory", UnpackAndExecuteVkAllocateMemory},
        {"vkFreeMemory", UnpackAndExecuteVkFreeMemory},
        {"vkCreateImage", UnpackAndExecuteVkCreateImage},
        {"vkDestroyImage", UnpackAndExecuteVkDestroyImage},
        {"vkBindImageMemory", UnpackAndExecuteVkBindImageMemory},
        {"vkBindImageMemory2", UnpackAndExecuteVkBindImageMemory2},
        {"vkGetImageMemoryRequirements", UnpackAndExecuteVkGetImageMemoryRequirements},
        {"vkGetImageMemoryRequirements2", UnpackAndExecuteVkGetImageMemoryRequirements2},
        {"vkCreateImageView", UnpackAndExecuteVkCreateImageView},
        {"vkDestroyImageView", UnpackAndExecuteVkDestroyImageView},
        {"vkCreateCommandPool", UnpackAndExecuteVkCreateCommandPool},
        {"vkDestroyCommandPool", UnpackAndExecuteVkDestroyCommandPool},
        {"vkAllocateCommandBuffers", UnpackAndExecuteVkAllocateCommandBuffers},
        {"vkFreeCommandBuffers", UnpackAndExecuteVkFreeCommandBuffers},
        {"vkBeginCommandBuffer", UnpackAndExecuteVkBeginCommandBuffer},
        {"vkEndCommandBuffer", UnpackAndExecuteVkEndCommandBuffer},
        {"vkGetImageSubresourceLayout", UnpackAndExecuteVkGetImageSubresourceLayout},
        {"vkCreateRenderPass", UnpackAndExecuteVkCreateRenderPass},
        {"vkDestroyRenderPass", UnpackAndExecuteVkDestroyRenderPass},
        {"vkCreatePipelineLayout", UnpackAndExecuteVkCreatePipelineLayout},
        {"vkDestroyPipelineLayout", UnpackAndExecuteVkDestroyPipelineLayout},
        {"vkCreateShaderModule", UnpackAndExecuteVkCreateShaderModule},
        {"vkDestroyShaderModule", UnpackAndExecuteVkDestroyShaderModule},
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