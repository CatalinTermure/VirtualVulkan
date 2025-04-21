#ifndef VVK_SERVER_PRESENTATION_CONTEXT_H
#define VVK_SERVER_PRESENTATION_CONTEXT_H

#include <vk_mem_alloc.h>
#include <vulkan/vulkan_core.h>

#include <vector>

struct PresentationContext {
  VkInstance instance;
  VkDevice device;
  VmaAllocator allocator;
  std::vector<VkImage> presentable_images;
  std::vector<VkFence> presentation_fences;
  std::vector<VkBuffer> cpu_buffers;
  std::vector<VmaAllocation> buffer_allocations;

  ~PresentationContext() {
    for (uint32_t i = 0; i < cpu_buffers.size(); ++i) {
      vmaDestroyBuffer(allocator, cpu_buffers[i], buffer_allocations[i]);
    }
  }
};

#endif  // VVK_SERVER_PRESENTATION_CONTEXT_H
