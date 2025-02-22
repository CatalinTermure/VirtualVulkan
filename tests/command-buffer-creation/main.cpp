#include <spdlog/spdlog.h>
#include <vulkan/vulkan_core.h>

#include <cassert>
#include <cstdint>
#include <limits>
#include <print>
#include <vector>

int main() {
  VkResult err;

  // Create a vulkan instance
  const VkApplicationInfo application_info = {
      .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .pApplicationName = "device-creation",
      .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
      .pEngineName = "Test Engine",
      .engineVersion = VK_MAKE_VERSION(1, 0, 0),
      .apiVersion = VK_API_VERSION_1_3,
  };

  VkInstanceCreateInfo instance_create_info = {};
  instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instance_create_info.pApplicationInfo = &application_info;
  VkInstance instance = VK_NULL_HANDLE;
  vkCreateInstance(&instance_create_info, nullptr, &instance);
  assert(instance != VK_NULL_HANDLE);
  spdlog::info("Vulkan instance created");

  VkPhysicalDevice chosen_device = VK_NULL_HANDLE;
  std::vector<VkPhysicalDevice> physical_devices;
  uint32_t physical_device_count = 0;
  vkEnumeratePhysicalDevices(instance, &physical_device_count, nullptr);
  physical_devices.resize(physical_device_count);
  assert(physical_device_count > 0);
  spdlog::info("Physical device count: {}", physical_device_count);
  vkEnumeratePhysicalDevices(instance, &physical_device_count, physical_devices.data());
  for (const auto& physical_device : physical_devices) {
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(physical_device, &properties);
    spdlog::info("Physical device: {}", properties.deviceName);
    if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
      chosen_device = physical_device;
    }
  }

  if (chosen_device == VK_NULL_HANDLE) {
    chosen_device = physical_devices[0];
  }

  VkDevice device = VK_NULL_HANDLE;
  VkDeviceQueueCreateInfo queue_create_info = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .queueFamilyIndex = 0,
      .queueCount = 1,
      .pQueuePriorities = new float[1]{1.0f},
  };
  const VkDeviceCreateInfo device_create_info = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .queueCreateInfoCount = 1,
      .pQueueCreateInfos = &queue_create_info,
      .enabledLayerCount = 0,
      .ppEnabledLayerNames = nullptr,
      .enabledExtensionCount = 0,
      .ppEnabledExtensionNames = nullptr,
      .pEnabledFeatures = nullptr,
  };
  vkCreateDevice(chosen_device, &device_create_info, nullptr, &device);

  uint32_t graphics_queue_family_index = std::numeric_limits<uint32_t>::max();
  uint32_t queue_family_count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(chosen_device, &queue_family_count, nullptr);
  std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
  vkGetPhysicalDeviceQueueFamilyProperties(chosen_device, &queue_family_count, queue_families.data());
  for (uint32_t i = 0; i < queue_family_count; i++) {
    if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      graphics_queue_family_index = i;
      break;
    }
  }

  if (graphics_queue_family_index == std::numeric_limits<uint32_t>::max()) {
    spdlog::critical("No graphics queue family found");
    return 1;
  }

  VkCommandPoolCreateInfo command_pool_create_info = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .queueFamilyIndex = graphics_queue_family_index,
  };
  VkCommandPool command_pool = VK_NULL_HANDLE;
  vkCreateCommandPool(device, &command_pool_create_info, nullptr, &command_pool);

  const VkCommandBufferAllocateInfo command_buffer_allocate_info = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
      .pNext = NULL,
      .commandPool = command_pool,
      .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
      .commandBufferCount = 2,
  };
  std::vector<VkCommandBuffer> command_buffers(2);
  err = vkAllocateCommandBuffers(device, &command_buffer_allocate_info, command_buffers.data());

  vkFreeCommandBuffers(device, command_pool, 1, &command_buffers[0]);
  vkFreeCommandBuffers(device, command_pool, 1, &command_buffers[1]);
  vkDestroyCommandPool(device, command_pool, nullptr);
  vkDestroyDevice(device, nullptr);
  vkDestroyInstance(instance, nullptr);
  spdlog::info("Vulkan instance destroyed");
  return 0;
}