#include "device.h"

#include <algorithm>

namespace vvk {

namespace {
std::mutex device_info_lock;
std::map<VkDevice, DeviceInfo> g_device_infos;
std::mutex command_buffer_to_device_lock;
std::map<VkCommandBuffer, VkDevice> g_command_buffer_to_device;
std::mutex queue_to_device_lock;
std::map<VkQueue, VkDevice> g_queue_to_device;
std::mutex pool_to_command_buffers_lock;
std::map<VkCommandPool, std::vector<VkCommandBuffer>> g_pool_to_command_buffers;

constexpr size_t kFencePoolSize = 16;
}  // namespace

DeviceInfo::DeviceInfo(VkDevice device, PFN_vkGetDeviceProcAddr nxt_gdpa, VkPhysicalDevice physical_device,
                       const VmaAllocatorCreateInfo& remote_allocator_create_info,
                       std::optional<uint32_t> present_queue_family_index, uint32_t remote_graphics_queue_family_index,
                       uint32_t remote_video_queue_family_index,
                       const vvk::server::StreamingCapabilities& streaming_capabilities)
    : nxt_gdpa_(nxt_gdpa),
      instance_info_(GetInstanceInfo(physical_device)),
      frame_stream_(nullptr),
      fence_pool_(device, kFencePoolSize, reinterpret_cast<PFN_vkCreateFence>(nxt_gdpa(device, "vkCreateFence"))) {
  if (vmaCreateAllocator(&remote_allocator_create_info, &remote_allocator_) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create remote VMA allocator");
  }
  vkuInitDeviceDispatchTable(device, &dispatch_table_, nxt_gdpa);

  VmaVulkanFunctions vma_vulkan_funcs = {
      .vkGetInstanceProcAddr = nullptr,
      .vkGetDeviceProcAddr = nullptr,
      .vkGetPhysicalDeviceProperties = instance_info_.dispatch_table().GetPhysicalDeviceProperties,
      .vkGetPhysicalDeviceMemoryProperties = instance_info_.dispatch_table().GetPhysicalDeviceMemoryProperties,
      .vkAllocateMemory = dispatch_table_.AllocateMemory,
      .vkFreeMemory = dispatch_table_.FreeMemory,
      .vkMapMemory = dispatch_table_.MapMemory,
      .vkUnmapMemory = dispatch_table_.UnmapMemory,
      .vkFlushMappedMemoryRanges = dispatch_table_.FlushMappedMemoryRanges,
      .vkInvalidateMappedMemoryRanges = dispatch_table_.InvalidateMappedMemoryRanges,
      .vkBindBufferMemory = dispatch_table_.BindBufferMemory,
      .vkBindImageMemory = dispatch_table_.BindImageMemory,
      .vkGetBufferMemoryRequirements = dispatch_table_.GetBufferMemoryRequirements,
      .vkGetImageMemoryRequirements = dispatch_table_.GetImageMemoryRequirements,
      .vkCreateBuffer = dispatch_table_.CreateBuffer,
      .vkDestroyBuffer = dispatch_table_.DestroyBuffer,
      .vkCreateImage = dispatch_table_.CreateImage,
      .vkDestroyImage = dispatch_table_.DestroyImage,
      .vkCmdCopyBuffer = dispatch_table_.CmdCopyBuffer,
      .vkGetBufferMemoryRequirements2KHR = dispatch_table_.GetBufferMemoryRequirements2KHR,
      .vkGetImageMemoryRequirements2KHR = dispatch_table_.GetImageMemoryRequirements2KHR,
      .vkBindBufferMemory2KHR = dispatch_table_.BindBufferMemory2KHR,
      .vkBindImageMemory2KHR = dispatch_table_.BindImageMemory2KHR,
      .vkGetPhysicalDeviceMemoryProperties2KHR = instance_info_.dispatch_table().GetPhysicalDeviceMemoryProperties2KHR,
      .vkGetDeviceBufferMemoryRequirements = dispatch_table_.GetDeviceBufferMemoryRequirements,
      .vkGetDeviceImageMemoryRequirements = dispatch_table_.GetDeviceImageMemoryRequirements,
      .vkGetMemoryWin32HandleKHR = nullptr,
  };
  VmaAllocatorCreateInfo local_allocator_create_info = {
      .flags = 0,
      .physicalDevice = physical_device,
      .device = device,
      .preferredLargeHeapBlockSize = 0,
      .pAllocationCallbacks = nullptr,
      .pDeviceMemoryCallbacks = nullptr,
      .pHeapSizeLimit = nullptr,
      .pVulkanFunctions = &vma_vulkan_funcs,
      .instance = GetInstanceForPhysicalDevice(physical_device),
      .vulkanApiVersion = VK_API_VERSION_1_0,
      .pTypeExternalMemoryHandleTypes = nullptr,
  };

  if (vmaCreateAllocator(&local_allocator_create_info, &local_allocator_) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create local VMA allocator");
  }

  if (present_queue_family_index.has_value()) {
    VkQueue present_queue;
    dispatch_table_.GetDeviceQueue(device, *present_queue_family_index, 0, &present_queue);
    // Workaround in order to work with Vulkan Validation Layers
    // The VVK layer does not call the Loader's vkGetDeviceQueue function, which sets the queue's loader data.
    // The Vulkan Validation Layers expect the loader data to be set, so we need to set it manually.
    *reinterpret_cast<VK_LOADER_DATA*>(present_queue) = *reinterpret_cast<VK_LOADER_DATA*>(device);
    present_queue_ = present_queue;
    present_queue_family_index_ = present_queue_family_index;
    frame_stream_ = FrameStream::Create(
        GetInstanceForPhysicalDevice(physical_device), device, instance_info_.GetRemoteHandle(physical_device),
        remote_graphics_queue_family_index, remote_video_queue_family_index, streaming_capabilities);
  }
}

void DeviceInfo::AddMappedMemory(void* local_address, void* remote_address, VkDeviceMemory memory_handle,
                                 std::size_t map_size) {
  auto it = mapped_memory_infos_.find(memory_handle);
  if (it != mapped_memory_infos_.end()) {
    throw std::runtime_error("Mapped memory already exists");
  }
  mapped_memory_infos_[memory_handle] = {local_address, remote_address, map_size};
}

void DeviceInfo::UploadMappedMemory(VkDeviceMemory memory) {
  grpc::ClientContext context;
  vvk::server::VvkWriteMappedMemoryRequest request;
  MappedMemoryInfo& mapped_memory_info = mapped_memory_infos_.at(memory);
  request.set_address(reinterpret_cast<uint64_t>(mapped_memory_info.remote_memory));
  request.set_data(reinterpret_cast<const char*>(mapped_memory_info.local_memory), mapped_memory_info.map_size);
  google::protobuf::Empty empty;
  instance_info_.stub().WriteMappedMemory(&context, request, &empty);
}

void DeviceInfo::UploadMappedMemories() {
  for (auto& [memory, mapped_memory_info] : mapped_memory_infos_) {
    UploadMappedMemory(memory);
  }
}

void DeviceInfo::RemoveMappedMemory(VkDeviceMemory memory_handle) {
  auto it = mapped_memory_infos_.find(memory_handle);
  if (it != mapped_memory_infos_.end()) {
    free(it->second.local_memory);
    mapped_memory_infos_.erase(it);
  } else {
    throw std::runtime_error("Mapped memory not found");
  }
}

void DeviceInfo::RegisterMemorySize(VkDeviceMemory memory_handle, std::size_t size) {
  auto it = memory_sizes_.find(memory_handle);
  if (it != memory_sizes_.end()) {
    throw std::runtime_error("Memory size already registered");
  }
  memory_sizes_[memory_handle] = size;
}

std::size_t DeviceInfo::GetMemorySize(VkDeviceMemory memory_handle) {
  auto it = memory_sizes_.find(memory_handle);
  if (it == memory_sizes_.end()) {
    throw std::runtime_error("Memory size not found");
  }
  return it->second;
}

void DeviceInfo::UnregisterMemorySize(VkDeviceMemory memory_handle) {
  auto it = memory_sizes_.find(memory_handle);
  if (it != memory_sizes_.end()) {
    memory_sizes_.erase(it);
  } else {
    throw std::runtime_error("Memory size not found");
  }
}

void DeviceInfo::CreateFakeQueueFamily(uint32_t queue_family_index, uint32_t queue_count) {
  if (fake_queue_families_.find(queue_family_index) != fake_queue_families_.end()) {
    throw std::runtime_error("Fake queue family already exists");
  }
  auto [it, inserted] = fake_queue_families_.emplace(queue_family_index, queue_count);
  if (!inserted) {
    throw std::runtime_error("Failed to create fake queue family");
  }
  auto& queue_family = it->second;
  for (uint32_t i = 0; i < queue_count; ++i) {
    queue_family.emplace_back();
  }
}

VkQueue DeviceInfo::GetFakeQueue(uint32_t queue_family_index, uint32_t queue_index) {
  auto map_iterator = fake_queue_families_.find(queue_family_index);
  if (map_iterator == fake_queue_families_.end()) {
    throw std::runtime_error("Fake queue family not found");
  }
  auto& queue_family = map_iterator->second;
  if (queue_index >= queue_family.size()) {
    throw std::runtime_error("Fake queue index out of range");
  }
  auto list_iterator = queue_family.begin();
  std::advance(list_iterator, queue_index);
  return reinterpret_cast<VkQueue>(&(*list_iterator));
}

DeviceInfo& GetDeviceInfo(VkDevice device) {
  std::lock_guard lock(device_info_lock);
  return g_device_infos.at(device);
}

DeviceInfo& GetDeviceInfo(VkCommandBuffer command_buffer) {
  return GetDeviceInfo(GetDeviceForCommandBuffer(command_buffer));
}

DeviceInfo& GetDeviceInfo(VkQueue queue) { return GetDeviceInfo(GetDeviceForQueue(queue)); }

DeviceInfo& SetDeviceInfo(VkDevice device, PFN_vkGetDeviceProcAddr nxt_gdpa, VkPhysicalDevice physical_device,
                          const VmaAllocatorCreateInfo& remote_allocator_create_info,
                          std::optional<uint32_t> present_queue_family_index,
                          uint32_t remote_graphics_queue_family_index, uint32_t remote_video_queue_family_index,
                          const vvk::server::StreamingCapabilities& streaming_capabilities) {
  std::lock_guard lock(device_info_lock);
  auto [iter, inserted] = g_device_infos.try_emplace(
      device, device, nxt_gdpa, physical_device, remote_allocator_create_info, present_queue_family_index,
      remote_graphics_queue_family_index, remote_video_queue_family_index, streaming_capabilities);
  assert(inserted);
  return iter->second;
}

void RemoveDeviceInfo(VkDevice device) {
  {
    std::lock_guard lock(command_buffer_to_device_lock);
    for (auto& [command_buffer, associated_device] : g_command_buffer_to_device) {
      if (associated_device == device) {
        throw std::runtime_error("Command buffers should be freed before the device is destroyed");
      }
    }
  }
  {
    std::lock_guard lock(queue_to_device_lock);
    std::erase_if(g_queue_to_device, [device](const auto& pair) { return pair.second == device; });
  }
  {
    std::lock_guard lock(device_info_lock);
    g_device_infos.erase(device);
  }
}

void AssociateCommandBufferWithDevice(VkCommandBuffer command_buffer, VkDevice device) {
  std::lock_guard lock(command_buffer_to_device_lock);
  g_command_buffer_to_device[command_buffer] = device;
}

VkDevice GetDeviceForCommandBuffer(VkCommandBuffer command_buffer) {
  std::lock_guard lock(command_buffer_to_device_lock);
  return g_command_buffer_to_device.at(command_buffer);
}

void AssociateCommandBufferWithPool(VkCommandBuffer command_buffer, VkCommandPool command_pool) {
  std::lock_guard lock(pool_to_command_buffers_lock);
  g_pool_to_command_buffers[command_pool].push_back(command_buffer);
}

std::vector<VkCommandBuffer> GetCommandBuffersForPool(VkCommandPool command_pool) {
  std::lock_guard lock(pool_to_command_buffers_lock);
  auto it = g_pool_to_command_buffers.find(command_pool);
  if (it != g_pool_to_command_buffers.end()) {
    return it->second;
  }
  return {};
}

void RemoveCommandBuffer(VkCommandBuffer command_buffer) {
  std::lock_guard lock(command_buffer_to_device_lock);
  g_command_buffer_to_device.erase(command_buffer);
}

void AssociateQueueWithDevice(VkQueue queue, VkDevice device) {
  std::lock_guard lock(queue_to_device_lock);
  g_queue_to_device[queue] = device;
}

VkDevice GetDeviceForQueue(VkQueue queue) {
  std::lock_guard lock(queue_to_device_lock);
  return g_queue_to_device.at(queue);
}

}  // namespace vvk
