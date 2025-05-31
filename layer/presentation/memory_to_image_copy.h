#ifndef VVK_LAYER_PRESENTATION_MEMORY_TO_IMAGE_COPY_H
#define VVK_LAYER_PRESENTATION_MEMORY_TO_IMAGE_COPY_H

// clang-format off
#include "layer/wsi_support.h"
// clang-format on

#include <vk_mem_alloc.h>
#include <vulkan/vulkan.h>

#include <optional>
#include <span>
#include <string_view>
#include <vector>

namespace vvk {

struct BufferLayout {
  uint32_t offset;
  uint32_t row_length;
  uint32_t image_height;
};

class MemoryToImageCopyContext {
 public:
  MemoryToImageCopyContext(VkDevice device, std::span<VkImage> images, VkExtent2D image_extent,
                           BufferLayout buffer_layout, bool use_fence, bool use_semaphore);

  MemoryToImageCopyContext(const MemoryToImageCopyContext&) = delete;
  MemoryToImageCopyContext& operator=(const MemoryToImageCopyContext&) = delete;
  MemoryToImageCopyContext(MemoryToImageCopyContext&& other) noexcept;
  MemoryToImageCopyContext& operator=(MemoryToImageCopyContext&& other) noexcept;

  ~MemoryToImageCopyContext();

  VkResult CopyMemoryToImage(uint32_t image_index, std::string_view data);

  std::optional<VkSemaphore> GetSemaphoreToSignal() const { return semaphore_to_signal_; }
  std::optional<VkFence> GetFenceToSignal() const { return fence_to_signal_; }

 private:
  std::optional<VkSemaphore> semaphore_to_signal_;
  std::optional<VkFence> fence_to_signal_;

  struct ImageInfo {
    VkImage image;
    VkCommandBuffer command_buffer;
    VmaAllocation buffer_allocation;
    VkBuffer staging_buffer;
  };
  std::vector<ImageInfo> images_;

  VkCommandPool command_pool_ = VK_NULL_HANDLE;
  VkDevice device_ = VK_NULL_HANDLE;
};
}  // namespace vvk

#endif  // VVK_LAYER_PRESENTATION_MEMORY_TO_IMAGE_COPY_H
