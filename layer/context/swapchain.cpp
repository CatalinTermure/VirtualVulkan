#include "swapchain.h"

#include <map>
#include <mutex>

#include "commons/remote_call.h"
#include "layer/context/device.h"

namespace vvk {

namespace {
std::mutex swapchain_info_lock;
std::map<VkSwapchainKHR, SwapchainInfo> g_swapchain_infos;
}  // namespace

SwapchainInfo::SwapchainInfo(VkSwapchainKHR swapchain, VkDevice device, VmaAllocator remote_allocator,
                             const std::vector<VkImage>& swapchain_images, const VkExtent2D& swapchain_image_extent)
    : swapchain_handle_(swapchain),
      device_(device),
      instance_info_(GetInstanceInfo(device)),
      remote_allocator_(remote_allocator),
      remote_images_(),
      acquired_images_(swapchain_images.size() - 1) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  uint32_t queue_family_index = *device_info.present_queue_family_index();
  VkCommandPoolCreateInfo command_pool_create_info = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .queueFamilyIndex = queue_family_index,
  };
  device_info.dispatch_table().CreateCommandPool(device, &command_pool_create_info, nullptr, &command_pool_);
  command_buffers_.resize(swapchain_images.size());
  staging_buffers_.resize(swapchain_images.size());
  buffer_allocations_.resize(swapchain_images.size());
  VkCommandBufferAllocateInfo command_buffer_allocate_info = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
      .pNext = nullptr,
      .commandPool = command_pool_,
      .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
      .commandBufferCount = static_cast<uint32_t>(swapchain_images.size()),
  };
  device_info.dispatch_table().AllocateCommandBuffers(device, &command_buffer_allocate_info, command_buffers_.data());

  VkBufferCreateInfo buffer_create_info = {.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
                                           .pNext = nullptr,
                                           .flags = 0,
                                           .size = swapchain_image_extent.width * swapchain_image_extent.height * 4,
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

  local_swapchain_images_ = swapchain_images;

  for (uint32_t i = 0; i < swapchain_images.size(); ++i) {
    vmaCreateBuffer(device_info.local_allocator(), &buffer_create_info, &allocation_create_info, &staging_buffers_[i],
                    &buffer_allocations_[i], nullptr);
    // Workaround in order to work with Vulkan Validation Layers, see device.cpp for reasoning
    *reinterpret_cast<VK_LOADER_DATA*>(command_buffers_[i]) = *reinterpret_cast<VK_LOADER_DATA*>(device);
    device_info.dispatch_table().BeginCommandBuffer(command_buffers_[i], &command_buffer_begin_info);
    VkBufferImageCopy full_screen_region = {
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
        .imageExtent = {swapchain_image_extent.width, swapchain_image_extent.height, 1},
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
        .image = swapchain_images[i],
        .subresourceRange =
            {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .baseMipLevel = 0,
                .levelCount = 1,
                .baseArrayLayer = 0,
                .layerCount = 1,
            },
    };
    device_info.dispatch_table().CmdPipelineBarrier(command_buffers_[i], VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                                                    VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1,
                                                    &to_transfer_dst_barrier);
    device_info.dispatch_table().CmdCopyBufferToImage(command_buffers_[i], staging_buffers_[i], swapchain_images[i],
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
        .image = swapchain_images[i],
        .subresourceRange =
            {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .baseMipLevel = 0,
                .levelCount = 1,
                .baseArrayLayer = 0,
                .layerCount = 1,
            },
    };
    device_info.dispatch_table().CmdPipelineBarrier(command_buffers_[i], VK_PIPELINE_STAGE_TRANSFER_BIT,
                                                    VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0, nullptr, 0, nullptr, 1,
                                                    &to_present_barrier);
    device_info.dispatch_table().EndCommandBuffer(command_buffers_[i]);
  }
}  // namespace vvk

VkResult SwapchainInfo::CopyMemoryToImage(uint32_t image_index, std::string_view data,
                                          std::span<VkSemaphore> semaphores_to_wait,
                                          std::span<VkPipelineStageFlags> wait_stages,
                                          std::span<VkSemaphore> semaphores_to_signal, VkFence fence_to_signal) {
  if (wait_stages.size() != semaphores_to_wait.size()) {
    throw std::runtime_error("wait_stages and semaphores_to_wait must have the same size");
  }

  if (image_index >= command_buffers_.size()) {
    throw std::runtime_error("image_index is out of bounds");
  }

  DeviceInfo& device_info = GetDeviceInfo(device_);
  VkResult result = vmaCopyMemoryToAllocation(device_info.local_allocator(), data.data(),
                                              buffer_allocations_[image_index], 0, data.size());
  if (result != VK_SUCCESS) {
    return result;
  }
  VkSubmitInfo submit_info = {
      .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
      .pNext = nullptr,
      .waitSemaphoreCount = static_cast<uint32_t>(semaphores_to_wait.size()),
      .pWaitSemaphores = semaphores_to_wait.data(),
      .pWaitDstStageMask = wait_stages.data(),
      .commandBufferCount = 1,
      .pCommandBuffers = &command_buffers_[image_index],
      .signalSemaphoreCount = static_cast<uint32_t>(semaphores_to_signal.size()),
      .pSignalSemaphores = semaphores_to_signal.data(),
  };
  return device_info.dispatch_table().QueueSubmit(*device_info.present_queue(), 1, &submit_info, fence_to_signal);
}

SwapchainInfo::~SwapchainInfo() {
  std::lock_guard g(lock_);
  DeviceInfo& device_info = GetDeviceInfo(device_);
  for (auto [remote_image, remote_allocation] : remote_images_) {
    vmaDestroyImage(remote_allocator_, remote_image, remote_allocation);
    device_info.swapchain_images.erase(remote_image);
  }
  device_info.dispatch_table().FreeCommandBuffers(
      device_, command_pool_, static_cast<uint32_t>(command_buffers_.size()), command_buffers_.data());
  for (uint32_t i = 0; i < staging_buffers_.size(); ++i) {
    vmaDestroyBuffer(device_info.local_allocator(), staging_buffers_[i], buffer_allocations_[i]);
  }
  device_info.dispatch_table().DestroyCommandPool(device_, command_pool_, nullptr);
}

VkImage SwapchainInfo::CreateImageRemote(const VkImageCreateInfo& create_info,
                                         const VmaAllocationCreateInfo& alloc_info) {
  VkImage remote_image;
  VmaAllocation remote_allocation;
  VkResult result =
      vmaCreateImage(remote_allocator_, &create_info, &alloc_info, &remote_image, &remote_allocation, nullptr);
  if (result != VK_SUCCESS) {
    return VK_NULL_HANDLE;
  }
  remote_images_.emplace_back(remote_image, remote_allocation);
  return remote_image;
}

SwapchainInfo& GetSwapchainInfo(VkSwapchainKHR swapchain) {
  std::lock_guard lock(swapchain_info_lock);
  return g_swapchain_infos.at(swapchain);
}

SwapchainInfo& SetSwapchainInfo(VkSwapchainKHR swapchain, VkDevice device, VmaAllocator remote_allocator,
                                const std::vector<VkImage>& swapchain_images,
                                const VkExtent2D& swapchain_image_extent) {
  std::lock_guard lock(swapchain_info_lock);
  auto [iter, inserted] = g_swapchain_infos.try_emplace(swapchain, swapchain, device, remote_allocator,
                                                        swapchain_images, swapchain_image_extent);
  assert(inserted);
  return iter->second;
}

void RemoveSwapchainInfo(VkSwapchainKHR swapchain) {
  std::lock_guard lock(swapchain_info_lock);
  g_swapchain_infos.erase(swapchain);
}

}  // namespace vvk