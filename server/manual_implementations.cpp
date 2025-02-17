#include "manual_implementations.h"

#include <spdlog/spdlog.h>
#include <vulkan/vulkan.h>

#include <vector>

#include "implementations.h"

void UnpackAndExecuteVkCreateInstanceManual(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request,
                                            vvk::server::VvkResponse* response) {
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