#include <spdlog/spdlog.h>
#include <vulkan/vulkan_core.h>

#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

#include <cassert>
#include <cstdint>
#include <print>
#include <vector>

int main() {
  // Create a vulkan instance
  const VkApplicationInfo application_info = {
      .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .pNext = nullptr,
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

  VmaAllocatorCreateInfo allocator_info = {};
  allocator_info.flags = 0;
  allocator_info.vulkanApiVersion = VK_API_VERSION_1_1;
  allocator_info.physicalDevice = chosen_device;
  allocator_info.device = device;
  allocator_info.instance = instance;

  VmaAllocator allocator;
  vmaCreateAllocator(&allocator_info, &allocator);

  VkMemoryRequirements requirements = {};
  requirements.alignment = 0;
  requirements.memoryTypeBits = 1;
  requirements.size = 1024;
  VmaAllocation allocation;
  VmaAllocationCreateInfo allocation_create_info = {};
  allocation_create_info.flags = 0;
  allocation_create_info.usage = VMA_MEMORY_USAGE_UNKNOWN;
  allocation_create_info.requiredFlags = 0;
  allocation_create_info.preferredFlags = 0;
  allocation_create_info.memoryTypeBits = 1;
  allocation_create_info.pool = VK_NULL_HANDLE;
  allocation_create_info.pUserData = nullptr;
  VmaAllocationInfo allocation_info = {};
  vmaAllocateMemory(allocator, &requirements, &allocation_create_info, &allocation, &allocation_info);

  vmaFreeMemory(allocator, allocation);
  vmaDestroyAllocator(allocator);
  vkDestroyDevice(device, nullptr);
  vkDestroyInstance(instance, nullptr);
  spdlog::info("Vulkan instance destroyed");
  return 0;
}