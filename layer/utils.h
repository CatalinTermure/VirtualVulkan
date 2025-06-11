#ifndef VVK_LAYER_UTILS_H
#define VVK_LAYER_UTILS_H

#include <vulkan/vk_layer.h>
#include <vulkan/vulkan_core.h>

namespace vvk {

template <typename T, VkStructureType sType>
T* FindStructInChain(const void* p_next_chain) {
  const T* struct_info = nullptr;
  while (p_next_chain) {
    struct_info = reinterpret_cast<const T*>(p_next_chain);
    p_next_chain = struct_info->pNext;
    if (struct_info->sType == sType) {
      return const_cast<T*>(struct_info);
    }
  }
  return nullptr;
}

template <typename T, VkStructureType sType>
T* FindLayerLinkInfo(const void* p_next_chain) {
  const T* layer_info = nullptr;
  while (p_next_chain) {
    layer_info = reinterpret_cast<const T*>(p_next_chain);
    p_next_chain = layer_info->pNext;
    if (layer_info->sType != sType) {
      continue;
    }
    if (layer_info->function == VK_LAYER_LINK_INFO) {
      break;
    }
  }
  return const_cast<T*>(layer_info);
}

void RemoveStructsFromChain(VkBaseOutStructure* base_struct, VkStructureType sType);

void AddStructToChain(VkBaseOutStructure* base_struct, VkBaseOutStructure* new_struct);

}  // namespace vvk

#endif  // VVK_LAYER_UTILS_H
