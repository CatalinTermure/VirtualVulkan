#include "manual_implementations.h"

#include <spdlog/spdlog.h>
#include <vulkan/vulkan.h>

#include <vector>

#include "server/implementations.h"

using vvk::server::VvkRequest;
using vvk::server::VvkResponse;

namespace {
VmaAllocator CreateVmaAllocator(VkInstance instance, VkPhysicalDevice physical_device, VkDevice device) {
  VmaVulkanFunctions vulkanFunctions = {};
  vulkanFunctions.vkGetInstanceProcAddr = &vkGetInstanceProcAddr;
  vulkanFunctions.vkGetDeviceProcAddr = &vkGetDeviceProcAddr;

  VmaAllocatorCreateInfo allocator_info = {};
  allocator_info.vulkanApiVersion = VK_API_VERSION_1_0;
  allocator_info.physicalDevice = physical_device;
  allocator_info.device = device;
  allocator_info.instance = instance;
  allocator_info.pVulkanFunctions = &vulkanFunctions;

  VmaAllocator allocator;
  vmaCreateAllocator(&allocator_info, &allocator);
  return allocator;
}
}  // namespace

void UnpackAndExecuteVkCreateInstanceManual(vvk::ExecutionContext& context, const VvkRequest& request,
                                            VvkResponse* response) {
  UnpackAndExecuteVkCreateInstance(context, request, response);

  VkInstance instance = reinterpret_cast<VkInstance>(response->vkcreateinstance().pinstance());

  uint32_t device_count;
  vkEnumeratePhysicalDevices(instance, &device_count, nullptr);
  std::vector<VkPhysicalDevice> phys_devices(device_count);
  vkEnumeratePhysicalDevices(instance, &device_count, phys_devices.data());

  for (VkPhysicalDevice phys_device : phys_devices) {
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(phys_device, &properties);
    if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
      context.set_physical_device(phys_device);
      spdlog::info("Using discrete GPU {}", properties.deviceName);
      break;
    }
  }
}
