#include "device.h"

#include <algorithm>

#include "3rdparty/ctpl_stl.h"
#include "spdlog/spdlog.h"

namespace vvk {

namespace {
std::mutex device_info_lock;
std::map<VkDevice, Device> g_device_infos;
std::mutex command_buffer_to_device_lock;
std::map<VkCommandBuffer, VkDevice> g_command_buffer_to_device;
std::mutex queue_to_device_lock;
std::map<VkQueue, VkDevice> g_queue_to_device;
std::mutex pool_to_command_buffers_lock;
std::map<VkCommandPool, std::vector<VkCommandBuffer>> g_pool_to_command_buffers;

constexpr size_t kFencePoolSize = 16;
constexpr size_t kChunkSize = 128 * 1024;

ctpl::thread_pool g_thread_pool(32);
}  // namespace

Device::Device(VkDevice device, PFN_vkGetDeviceProcAddr nxt_gdpa, VkPhysicalDevice physical_device,
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

  fence_pool_.ForAllFences([this](VkFence& fence) { RegisterFence(fence); });

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
    spdlog::info("Device: Present queue set to {}", (void*)present_queue);
    present_queue_family_index_ = present_queue_family_index;
    frame_stream_ = FrameStream::Create(
        GetInstanceForPhysicalDevice(physical_device), device, instance_info_.GetRemoteHandle(physical_device),
        remote_graphics_queue_family_index, remote_video_queue_family_index, streaming_capabilities);
  }
}

void Device::AddMappedMemory(void* local_address, void* remote_address, VkDeviceMemory memory_handle,
                             std::size_t map_size) {
  auto it = mapped_memory_infos_.find(memory_handle);
  if (it != mapped_memory_infos_.end()) {
    throw std::runtime_error("Mapped memory already exists");
  }
  mapped_memory_infos_[memory_handle] = MappedMemoryInfo{
      .local_memory = local_address,
      .remote_memory = remote_address,
      .map_size = map_size,
      .hashes = std::vector<std::size_t>((map_size + kChunkSize - 1) / kChunkSize, 0),
  };
  MappedMemoryInfo& mapped_memory_info = mapped_memory_infos_.at(memory_handle);
  for (size_t offset = 0; offset < mapped_memory_info.map_size; offset += kChunkSize) {
    size_t chunk_size = std::min(kChunkSize, mapped_memory_info.map_size - offset);
    std::size_t hash = std::hash<std::string_view>()(
        std::string_view(reinterpret_cast<const char*>(mapped_memory_info.local_memory) + offset, chunk_size));
    mapped_memory_info.hashes[offset / kChunkSize] = hash;
  }
}

void Device::UploadMappedMemory(VkDeviceMemory memory) {
  std::vector<std::future<void>> futures;

  for (size_t offset = 0; offset < mapped_memory_infos_.at(memory).map_size; offset += kChunkSize) {
    MappedMemoryInfo& mapped_memory_info = mapped_memory_infos_.at(memory);
    size_t chunk_size = std::min(kChunkSize, mapped_memory_info.map_size - offset);
    std::size_t hash = std::hash<std::string_view>()(
        std::string_view(reinterpret_cast<const char*>(mapped_memory_info.local_memory) + offset, chunk_size));
    if (mapped_memory_info.hashes[offset / kChunkSize] == hash) {
      spdlog::debug("Skipping upload for memory {} at offset {}: data unchanged", (void*)memory, offset);
      continue;
    }
    mapped_memory_info.hashes[offset / kChunkSize] = hash;
    futures.push_back(g_thread_pool.push([offset, this, &mapped_memory_info, chunk_size](int unused) {
      grpc::ClientContext context;
      vvk::server::VvkWriteMappedMemoryRequest request;
      request.set_address(reinterpret_cast<uint64_t>(mapped_memory_info.remote_memory) + offset);
      request.set_data(reinterpret_cast<const char*>(mapped_memory_info.local_memory) + offset, chunk_size);
      google::protobuf::Empty empty;
      auto status = instance_info_.stub().WriteMappedMemory(&context, request, &empty);
      if (!status.ok()) {
        throw std::runtime_error("Failed to upload mapped memory: " + status.error_message());
      }
    }));
  }
  for (auto& future : futures) {
    try {
      future.get();
    } catch (const std::exception& e) {
      throw std::runtime_error(std::string("Error uploading mapped memory: ") + e.what());
    }
  }
}

void Device::UploadMappedMemories() {
  for (auto& [memory, mapped_memory_info] : mapped_memory_infos_) {
    UploadMappedMemory(memory);
  }
}

void Device::RemoveMappedMemory(VkDeviceMemory memory_handle) {
  auto it = mapped_memory_infos_.find(memory_handle);
  if (it != mapped_memory_infos_.end()) {
    free(it->second.local_memory);
    mapped_memory_infos_.erase(it);
  } else {
    throw std::runtime_error("Mapped memory not found");
  }
}

void Device::RegisterMemorySize(VkDeviceMemory memory_handle, std::size_t size) {
  auto it = memory_sizes_.find(memory_handle);
  if (it != memory_sizes_.end()) {
    throw std::runtime_error("Memory size already registered");
  }
  memory_sizes_[memory_handle] = size;
}

std::size_t Device::GetMemorySize(VkDeviceMemory memory_handle) {
  auto it = memory_sizes_.find(memory_handle);
  if (it == memory_sizes_.end()) {
    throw std::runtime_error("Memory size not found");
  }
  return it->second;
}

void Device::UnregisterMemorySize(VkDeviceMemory memory_handle) {
  auto it = memory_sizes_.find(memory_handle);
  if (it != memory_sizes_.end()) {
    memory_sizes_.erase(it);
  } else {
    throw std::runtime_error("Memory size not found");
  }
}

void Device::CreateFakeQueueFamily(uint32_t queue_family_index, uint32_t queue_count) {
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

VkQueue Device::GetFakeQueue(uint32_t queue_family_index, uint32_t queue_index) {
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

Device& GetDeviceInfo(VkDevice device) {
  std::lock_guard lock(device_info_lock);
  return g_device_infos.at(device);
}

Device& GetDeviceInfo(VkCommandBuffer command_buffer) {
  return GetDeviceInfo(GetDeviceForCommandBuffer(command_buffer));
}

Device& GetDeviceInfo(VkQueue queue) { return GetDeviceInfo(GetDeviceForQueue(queue)); }

Device& SetDeviceInfo(VkDevice device, PFN_vkGetDeviceProcAddr nxt_gdpa, VkPhysicalDevice physical_device,
                      const VmaAllocatorCreateInfo& remote_allocator_create_info,
                      std::optional<uint32_t> present_queue_family_index, uint32_t remote_graphics_queue_family_index,
                      uint32_t remote_video_queue_family_index,
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
