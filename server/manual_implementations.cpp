#include "manual_implementations.h"

#include <spdlog/spdlog.h>
#include <vulkan/vulkan.h>

#include <vector>

#include "server/h264_encoder.h"
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

void SetupPresentationUncompressedStream(vvk::ExecutionContext& context,
                                         const vvk::server::VvkSetupPresentationRequest& params,
                                         vvk::server::VvkResponse* response) {
  VkInstance instance = reinterpret_cast<VkInstance>(params.instance());
  VkDevice device = reinterpret_cast<VkDevice>(params.device());
  uint32_t queue_family_index = params.uncompressed_stream_create_info().queue_family_index();

  VmaAllocator allocator = context.allocator();

  auto* setup_presentation_response = response->mutable_setuppresentation();
  auto* uncompressed_stream_info = response->mutable_setuppresentation()->mutable_uncompressed_stream_info();

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
      setup_presentation_response->add_frame_keys(reinterpret_cast<uint64_t>(buffer_allocation));
    }
  }

  setup_presentation_response->set_session_key(reinterpret_cast<uint64_t>(context.allocator()));
}

void SetupPresentationH264Stream(vvk::ExecutionContext& context, const vvk::server::VvkSetupPresentationRequest& params,
                                 vvk::server::VvkResponse* response) {
  std::vector<VkImage> remote_images;
  for (uint64_t image_handle : params.remote_images()) {
    remote_images.push_back(reinterpret_cast<VkImage>(image_handle));
  }
  auto encoder = std::make_unique<vvk::H264Encoder>(
      context, reinterpret_cast<VkDevice>(params.device()), params.h264_stream_create_info().video_queue_family_index(),
      params.h264_stream_create_info().compute_queue_family_index(), vk::Extent2D{params.width(), params.height()},
      std::move(remote_images), static_cast<VkFormat>(params.h264_stream_create_info().remote_images_format()),
      reinterpret_cast<VkSemaphore>(params.h264_stream_create_info().encode_wait_semaphore()));
  auto& h264_stream_info = *response->mutable_setuppresentation()->mutable_h264_stream_info();
  h264_stream_info.set_header(encoder->GetEncodedHeader());

  context.set_encoder(std::move(encoder));
  auto* setup_presentation_response = response->mutable_setuppresentation();
  setup_presentation_response->set_session_key(reinterpret_cast<uint64_t>(context.encoder()));
  for (uint64_t image : params.remote_images()) {
    setup_presentation_response->add_frame_keys(image);
  }
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

  context.InitInstanceDispatchTable(instance);
}

void UnpackAndExecuteVkCreateDeviceManual(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request,
                                          vvk::server::VvkResponse* response) {
  UnpackAndExecuteVkCreateDevice(context, request, response);

  context.InitDeviceDispatchTable(reinterpret_cast<VkDevice>(response->vkcreatedevice().pdevice()));
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
  response->mutable_vkenumeratephysicaldevices()->set_result(vvk::server::VkResult::VK_SUCCESS);
}

void UnpackAndExecuteSetupPresentation(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request,
                                       vvk::server::VvkResponse* response) {
  assert(request.method() == "setupPresentation");
  const auto& params = request.setuppresentation();
  if (context.allocator() == VK_NULL_HANDLE) {
    context.set_allocator(CreateVmaAllocator(reinterpret_cast<VkInstance>(params.instance()), context.physical_device(),
                                             reinterpret_cast<VkDevice>(params.device())));
  }

  if (params.has_uncompressed_stream_create_info()) {
    SetupPresentationUncompressedStream(context, params, response);
  } else if (params.has_h264_stream_create_info()) {
    SetupPresentationH264Stream(context, params, response);
  } else {
    spdlog::error("Unsupported presentation stream type");
  }
}

void UnpackAndExecuteSetupFrame(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request,
                                vvk::server::VvkResponse* response) {
  vvk::Encoder* encoder = reinterpret_cast<vvk::Encoder*>(request.setupframe().session_key());
  VkImage image = reinterpret_cast<VkImage>(request.setupframe().frame_key());
  VkCommandBuffer command_buffer = reinterpret_cast<VkCommandBuffer>(request.setupframe().command_buffer());
  encoder->WriteEncodeCommands(command_buffer, image);
}