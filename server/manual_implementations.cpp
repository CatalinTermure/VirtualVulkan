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

void UnpackAndExecuteVvkGetFrame(vvk::ExecutionContext& context, const VvkRequest& request, VvkResponse* response) {
  assert(request.method() == "VvkGetFrame");
  assert(request.has_vvkgetframe());

  const auto& params = request.vvkgetframe();
  VkImage image = reinterpret_cast<VkImage>(params.image());
  VkInstance instance = reinterpret_cast<VkInstance>(params.instance());
  VkDevice device = reinterpret_cast<VkDevice>(params.device());
  VkCommandBuffer command_buffer = reinterpret_cast<VkCommandBuffer>(params.commandbuffer());
  VkQueue queue = reinterpret_cast<VkQueue>(params.queue());
  uint32_t queue_family_index = params.queuefamilyindex();

  if (context.allocator() == VK_NULL_HANDLE) {
    context.set_allocator(CreateVmaAllocator(instance, context.physical_device(), device));
    return;
  }

  VmaAllocator allocator = context.allocator();

  // Create a buffer to copy the image data to
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

    vmaCreateBuffer(allocator, &buffer_create_info, &allocation_create_info, &buffer, &buffer_allocation, nullptr);

    context.defer_deletion(
        [allocator, buffer_allocation, buffer]() { vmaDestroyBuffer(allocator, buffer, buffer_allocation); });
  }

  // Transition the image layout
  {
    VkImageMemoryBarrier2 image_memory_barrier = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
        .pNext = nullptr,
        .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .srcAccessMask = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT,
        .dstStageMask = VK_PIPELINE_STAGE_2_TRANSFER_BIT,
        .dstAccessMask = VK_ACCESS_2_TRANSFER_READ_BIT,
        .oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        .newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
        .srcQueueFamilyIndex = queue_family_index,
        .dstQueueFamilyIndex = queue_family_index,
        .image = image,
        .subresourceRange =
            {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .baseMipLevel = 0,
                .levelCount = 1,
                .baseArrayLayer = 0,
                .layerCount = 1,
            },
    };

    VkDependencyInfoKHR dependency_info = {
        .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO_KHR,
        .pNext = nullptr,
        .dependencyFlags = 0,
        .memoryBarrierCount = 0,
        .pMemoryBarriers = nullptr,
        .bufferMemoryBarrierCount = 0,
        .pBufferMemoryBarriers = nullptr,
        .imageMemoryBarrierCount = 1,
        .pImageMemoryBarriers = &image_memory_barrier,
    };

    vkCmdPipelineBarrier2(command_buffer, &dependency_info);
  }

  // Copy the image to the buffer
  {
    VkBufferImageCopy2 region = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_IMAGE_COPY_2,
        .pNext = nullptr,
        .bufferOffset = 0,
        .bufferRowLength = 0,
        .bufferImageHeight = 0,
        .imageSubresource =
            {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .mipLevel = 0,
                .baseArrayLayer = 0,
                .layerCount = 1,
            },
        .imageOffset = {0, 0, 0},
        .imageExtent =
            {
                .width = params.width(),
                .height = params.height(),
                .depth = 1,
            },
    };

    VkCopyImageToBufferInfo2 copy_image_to_buffer_info = {
        .sType = VK_STRUCTURE_TYPE_COPY_IMAGE_TO_BUFFER_INFO_2,
        .pNext = nullptr,
        .srcImage = image,
        .srcImageLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
        .dstBuffer = buffer,
        .regionCount = 1,
        .pRegions = &region,
    };
    vkCmdCopyImageToBuffer2(command_buffer, &copy_image_to_buffer_info);
  }

  // Map the buffer memory and copy the data to the response
  {
    void* data;
    vmaMapMemory(allocator, buffer_allocation, &data);

    response->mutable_vvkgetframe()->set_encodeddata(reinterpret_cast<char*>(data), buffer_memory_requirements.size);

    vmaUnmapMemory(allocator, buffer_allocation);
  }
}