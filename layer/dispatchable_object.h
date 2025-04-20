#ifndef VVK_LAYER_DISPATCHABLE_OBJECT_H
#define VVK_LAYER_DISPATCHABLE_OBJECT_H

// clang-format off
#include "layer/wsi_support.h"
// clang-format on

#include <vulkan/vk_icd.h>

struct DispatchableObject {
  VK_LOADER_DATA loader_data;

  DispatchableObject() { set_loader_magic_value(this); }
};

#endif  // VVK_LAYER_DISPATCHABLE_OBJECT_H
