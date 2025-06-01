#include "memory_to_image_copy.h"

#include <algorithm>

#include "layer/context/device.h"

namespace vvk {
MemoryToImageCopyContext::MemoryToImageCopyContext(VkDevice device, std::span<VkImage> images, VkExtent2D image_extent,
                                                   BufferLayout buffer_layout, bool use_fence, bool use_semaphore) {
  device_ = device;
  DeviceInfo& device_info = GetDeviceInfo(device);
  uint32_t queue_family_index = *device_info.present_queue_family_index();
  VkCommandPoolCreateInfo command_pool_create_info = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .queueFamilyIndex = queue_family_index,
  };
  device_info.dispatch_table().CreateCommandPool(device, &command_pool_create_info, nullptr, &command_pool_);
  std::vector<VkCommandBuffer> command_buffers;
  command_buffers.resize(images.size());
  VkCommandBufferAllocateInfo command_buffer_allocate_info = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
      .pNext = nullptr,
      .commandPool = command_pool_,
      .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
      .commandBufferCount = static_cast<uint32_t>(command_buffers.size()),
  };
  device_info.dispatch_table().AllocateCommandBuffers(device, &command_buffer_allocate_info, command_buffers.data());

  VkBufferCreateInfo buffer_create_info = {.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
                                           .pNext = nullptr,
                                           .flags = 0,
                                           .size = std::max(buffer_layout.row_length, image_extent.width) *
                                                   std::max(buffer_layout.image_height, image_extent.height) * 4,
                                           .usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                                           .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
                                           .queueFamilyIndexCount = 1,
                                           .pQueueFamilyIndices = &queue_family_index};

  VmaAllocationCreateInfo allocation_create_info = {};
  allocation_create_info.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT;
  allocation_create_info.usage = VMA_MEMORY_USAGE_AUTO_PREFER_HOST;

  VkCommandBufferBeginInfo command_buffer_begin_info = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
      .pNext = nullptr,
      .flags = 0,
      .pInheritanceInfo = nullptr,
  };

  images_.reserve(images.size());
  for (uint32_t i = 0; i < images.size(); ++i) {
    VmaAllocation buffer_allocation;
    VkBuffer staging_buffer;
    vmaCreateBuffer(device_info.local_allocator(), &buffer_create_info, &allocation_create_info, &staging_buffer,
                    &buffer_allocation, nullptr);
    // Workaround in order to work with Vulkan Validation Layers, see device.cpp for reasoning
    *reinterpret_cast<VK_LOADER_DATA*>(command_buffers[i]) = *reinterpret_cast<VK_LOADER_DATA*>(device);
    device_info.dispatch_table().BeginCommandBuffer(command_buffers[i], &command_buffer_begin_info);
    VkBufferImageCopy full_screen_region = {
        .bufferOffset = buffer_layout.offset,
        .bufferRowLength = buffer_layout.row_length,
        .bufferImageHeight = buffer_layout.image_height,
        .imageSubresource =
            {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .mipLevel = 0,
                .baseArrayLayer = 0,
                .layerCount = 1,
            },
        .imageOffset = {0, 0, 0},
        .imageExtent = {image_extent.width, image_extent.height, 1},
    };
    VkImageMemoryBarrier to_transfer_dst_barrier = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
        .pNext = nullptr,
        .srcAccessMask = 0,
        .dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT,
        // maybe use VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, but must transition once when creating the swapchain
        .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        .srcQueueFamilyIndex = queue_family_index,
        .dstQueueFamilyIndex = queue_family_index,
        .image = images[i],
        .subresourceRange =
            {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .baseMipLevel = 0,
                .levelCount = 1,
                .baseArrayLayer = 0,
                .layerCount = 1,
            },
    };
    device_info.dispatch_table().CmdPipelineBarrier(command_buffers[i], VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                                                    VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1,
                                                    &to_transfer_dst_barrier);
    device_info.dispatch_table().CmdCopyBufferToImage(command_buffers[i], staging_buffer, images[i],
                                                      VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &full_screen_region);
    VkImageMemoryBarrier to_present_barrier = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
        .pNext = nullptr,
        .srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT,
        .dstAccessMask = 0,
        .oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        .newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
        .srcQueueFamilyIndex = queue_family_index,
        .dstQueueFamilyIndex = queue_family_index,
        .image = images[i],
        .subresourceRange =
            {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .baseMipLevel = 0,
                .levelCount = 1,
                .baseArrayLayer = 0,
                .layerCount = 1,
            },
    };
    device_info.dispatch_table().CmdPipelineBarrier(command_buffers[i], VK_PIPELINE_STAGE_TRANSFER_BIT,
                                                    VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0, nullptr, 0, nullptr, 1,
                                                    &to_present_barrier);
    device_info.dispatch_table().EndCommandBuffer(command_buffers[i]);
    images_.push_back({
        .image = images[i],
        .command_buffer = command_buffers[i],
        .buffer_allocation = buffer_allocation,
        .staging_buffer = staging_buffer,
    });
  }

  if (use_fence) {
    VkFence fence;
    VkFenceCreateInfo fence_create_info = {};
    fence_create_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    device_info.dispatch_table().CreateFence(device_, &fence_create_info, nullptr, &fence);
    fence_to_signal_ = fence;
  }
  if (use_semaphore) {
    VkSemaphore semaphore;
    VkSemaphoreCreateInfo semaphore_create_info = {};
    semaphore_create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    device_info.dispatch_table().CreateSemaphore(device_, &semaphore_create_info, nullptr, &semaphore);
    semaphore_to_signal_ = semaphore;
  }
}

MemoryToImageCopyContext::MemoryToImageCopyContext(MemoryToImageCopyContext&& other) noexcept {
  device_ = other.device_;
  command_pool_ = other.command_pool_;
  images_ = std::move(other.images_);
  semaphore_to_signal_ = std::move(other.semaphore_to_signal_);
  fence_to_signal_ = std::move(other.fence_to_signal_);
  other.command_pool_ = VK_NULL_HANDLE;
  other.device_ = VK_NULL_HANDLE;
}

MemoryToImageCopyContext& MemoryToImageCopyContext::operator=(MemoryToImageCopyContext&& other) noexcept {
  if (this != &other) {
    DeviceInfo& device_info = GetDeviceInfo(device_);
    for (auto& image_info : images_) {
      vmaDestroyBuffer(device_info.local_allocator(), image_info.staging_buffer, image_info.buffer_allocation);
      device_info.dispatch_table().FreeCommandBuffers(device_, command_pool_, 1, &image_info.command_buffer);
    }
    if (command_pool_ != VK_NULL_HANDLE) {
      device_info.dispatch_table().DestroyCommandPool(device_, command_pool_, nullptr);
    }
    if (fence_to_signal_.has_value()) {
      device_info.dispatch_table().DestroyFence(device_, *fence_to_signal_, nullptr);
    }
    if (semaphore_to_signal_.has_value()) {
      device_info.dispatch_table().DestroySemaphore(device_, *semaphore_to_signal_, nullptr);
    }

    device_ = other.device_;
    command_pool_ = other.command_pool_;
    images_ = std::move(other.images_);
    semaphore_to_signal_ = std::move(other.semaphore_to_signal_);
    fence_to_signal_ = std::move(other.fence_to_signal_);
    other.command_pool_ = VK_NULL_HANDLE;
    other.device_ = VK_NULL_HANDLE;
  }
  return *this;
}

MemoryToImageCopyContext::~MemoryToImageCopyContext() {
  if (device_ == VK_NULL_HANDLE) {
    return;  // Already cleaned up
  }
  DeviceInfo& device_info = GetDeviceInfo(device_);
  for (auto& image_info : images_) {
    vmaDestroyBuffer(device_info.local_allocator(), image_info.staging_buffer, image_info.buffer_allocation);
    device_info.dispatch_table().FreeCommandBuffers(device_, command_pool_, 1, &image_info.command_buffer);
  }
  if (command_pool_ != VK_NULL_HANDLE) {
    device_info.dispatch_table().DestroyCommandPool(device_, command_pool_, nullptr);
  }
  if (fence_to_signal_.has_value()) {
    device_info.dispatch_table().DestroyFence(device_, *fence_to_signal_, nullptr);
  }
  if (semaphore_to_signal_.has_value()) {
    device_info.dispatch_table().DestroySemaphore(device_, *semaphore_to_signal_, nullptr);
  }
}

VkResult MemoryToImageCopyContext::CopyMemoryToImage(uint32_t image_index, std::string_view data) {
  if (image_index >= images_.size()) {
    throw std::runtime_error("image_index is out of bounds");
  }

  DeviceInfo& device_info = GetDeviceInfo(device_);
  VkResult result = vmaCopyMemoryToAllocation(device_info.local_allocator(), data.data(),
                                              images_[image_index].buffer_allocation, 0, data.size());
  if (result != VK_SUCCESS) {
    return result;
  }
  VkSubmitInfo submit_info = {
      .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
      .pNext = nullptr,
      .waitSemaphoreCount = 0,
      .pWaitSemaphores = nullptr,
      .pWaitDstStageMask = nullptr,
      .commandBufferCount = 1,
      .pCommandBuffers = &images_[image_index].command_buffer,
      .signalSemaphoreCount = semaphore_to_signal_.has_value() ? 1u : 0u,
      .pSignalSemaphores = semaphore_to_signal_.has_value() ? &*semaphore_to_signal_ : nullptr,
  };
  return device_info.dispatch_table().QueueSubmit(*device_info.present_queue(), 1, &submit_info,
                                                  fence_to_signal_.has_value() ? *fence_to_signal_ : VK_NULL_HANDLE);
}

}  // namespace vvk
