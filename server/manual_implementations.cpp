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

void UnpackAndExecuteVkEnumeratePhysicalDevicesManual(vvk::ExecutionContext& context,
                                                      const vvk::server::VvkRequest& request,
                                                      vvk::server::VvkResponse* response) {
  assert(request.method() == "vkEnumeratePhysicalDevices");

  uint32_t physical_device_count = request.vkenumeratephysicaldevices().pphysicaldevicecount();
  if (physical_device_count == 0) {
    response->mutable_vkenumeratephysicaldevices()->set_pphysicaldevicecount(1);
  } else {
    assert(physical_device_count == 1);
    response->mutable_vkenumeratephysicaldevices()->set_pphysicaldevicecount(physical_device_count);
    response->mutable_vkenumeratephysicaldevices()->add_pphysicaldevices(
        reinterpret_cast<uint64_t>(context.physical_device()));
  }
  response->set_result(VK_SUCCESS);
}

void UnpackAndExecuteSetupPresentation(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request,
                                       vvk::server::VvkResponse* response) {
  assert(request.method() == "setupPresentation");
  const auto& params = request.setuppresentation();

  VkInstance instance = reinterpret_cast<VkInstance>(params.instance());
  VkDevice device = reinterpret_cast<VkDevice>(params.device());
  uint32_t queue_family_index = params.uncompressed_stream_create_info().queue_family_index();

  if (context.allocator() == VK_NULL_HANDLE) {
    context.set_allocator(CreateVmaAllocator(instance, context.physical_device(), device));
  }

  VmaAllocator allocator = context.allocator();

  const auto& uncompressed_stream_info = response->mutable_setuppresentation()->mutable_uncompressed_stream_info();

  // Create a buffer to copy the image data to
  for (uint64_t image_handle : params.remote_images()) {
    VkImage image = reinterpret_cast<VkImage>(image_handle);
    VkMemoryRequirements buffer_memory_requirements;
    VkBuffer buffer;
    VmaAllocation buffer_allocation;
    {
      VmaAllocationCreateInfo allocation_create_info = {};
      allocation_create_info.usage = VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE;
      allocation_create_info.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT;

      vkGetImageMemoryRequirements(device, image, &buffer_memory_requirements);

      VkBufferCreateInfo buffer_create_info = {
          .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
          .pNext = nullptr,
          .flags = 0,
          .size = buffer_memory_requirements.size,
          .usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT,
          .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
          .queueFamilyIndexCount = 1,
          .pQueueFamilyIndices = &queue_family_index,
      };

      if (vmaCreateBuffer(allocator, &buffer_create_info, &allocation_create_info, &buffer, &buffer_allocation,
                          nullptr)) {
        spdlog::error("Failed to create buffer");
        return;
      }

      context.defer_deletion(
          [allocator, buffer_allocation, buffer]() { vmaDestroyBuffer(allocator, buffer, buffer_allocation); });

      uncompressed_stream_info->add_remote_buffers(reinterpret_cast<uint64_t>(buffer));
      uncompressed_stream_info->add_frame_keys(reinterpret_cast<uint64_t>(buffer_allocation));
    }
  }

  uncompressed_stream_info->set_session_key(reinterpret_cast<uint64_t>(context.allocator()));
}