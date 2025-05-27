#include <spdlog/spdlog.h>
#include <vulkan/vulkan_core.h>

#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

#include <cassert>
#include <cstdint>
#include <limits>
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

  const std::array<uint32_t, 1> queue_family_indices = {0};
  VkImage image;
  VmaAllocation allocation;
  VmaAllocationInfo allocation_info = {};
  VmaAllocationCreateInfo allocation_create_info = {};
  allocation_create_info.flags = 0;
  allocation_create_info.usage = VMA_MEMORY_USAGE_AUTO;
  allocation_create_info.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
  allocation_create_info.preferredFlags = 0;
  allocation_create_info.memoryTypeBits = std::numeric_limits<uint32_t>::max();
  allocation_create_info.pool = VK_NULL_HANDLE;
  allocation_create_info.pUserData = nullptr;
  VkImageCreateInfo image_create_info = {};
  image_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  image_create_info.pNext = nullptr;
  image_create_info.flags = 0;
  image_create_info.imageType = VK_IMAGE_TYPE_2D;
  image_create_info.format = VK_FORMAT_R8G8B8A8_UNORM;
  image_create_info.extent = {1024, 1024, 1};
  image_create_info.mipLevels = 1;
  image_create_info.arrayLayers = 1;
  image_create_info.samples = VK_SAMPLE_COUNT_1_BIT;
  image_create_info.tiling = VK_IMAGE_TILING_OPTIMAL;
  image_create_info.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  image_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  image_create_info.queueFamilyIndexCount = 1;
  image_create_info.pQueueFamilyIndices = queue_family_indices.data();
  image_create_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  vmaCreateImage(allocator, &image_create_info, &allocation_create_info, &image, &allocation, &allocation_info);

  vmaDestroyImage(allocator, image, allocation);
  vmaDestroyAllocator(allocator);
  vkDestroyDevice(device, nullptr);
  vkDestroyInstance(instance, nullptr);
  spdlog::info("Vulkan instance destroyed");
  return 0;
}