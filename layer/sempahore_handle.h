#ifndef VVK_LAYER_SEMPAHORE_HANDLE_H
#define VVK_LAYER_SEMPAHORE_HANDLE_H

#include <vulkan/vulkan_core.h>

#include <semaphore>

enum class SemaphoreState {
  kUnsignaled,
  kToBeSignaledLocal,
  kToBeSignaledRemote,
};

struct VkSemaphore_T {
  VkSemaphore local_handle = VK_NULL_HANDLE;
  VkSemaphore remote_handle = VK_NULL_HANDLE;
  std::binary_semaphore remote_to_local_semaphore{0};
  SemaphoreState state = SemaphoreState::kUnsignaled;
};

#endif  // VVK_LAYER_SEMPAHORE_HANDLE_H
