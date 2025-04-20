#ifndef VVK_LAYER_FUNCTION_LOADING_H
#define VVK_LAYER_FUNCTION_LOADING_H

// clang-format off
#include "layer/wsi_support.h"
// clang-format on

#include <vulkan/vk_layer.h>

namespace vvk {
PFN_vkVoidFunction GetInstanceProcAddr(VkInstance instance, const char* pName);
PFN_vkVoidFunction GetDeviceProcAddr(VkDevice device, const char* pName);
PFN_vkVoidFunction GetPhysicalDeviceProcAddr(VkInstance instance, const char* pName);
}  // namespace vvk

#endif  // VVK_LAYER_FUNCTION_LOADING_H