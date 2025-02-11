#include "layer/functions.h"

#include <spdlog/spdlog.h>
#include <vulkan/vk_layer.h>

#include <cassert>
#include <unordered_map>

namespace vvk {

namespace {

struct InstanceInfo {
  PFN_vkGetInstanceProcAddr nxtGipa;
};

std::unordered_map<VkInstance, InstanceInfo> g_instance_infos;

}  // namespace

VKAPI_ATTR VkResult VKAPI_CALL CreateInstance(const VkInstanceCreateInfo* pCreateInfo,
                                              const VkAllocationCallbacks* pAllocator, VkInstance* pInstance) {
  spdlog::trace("CreateInstance");

  // TODO: what from the pNext chain do we need to pass to remote server?

  // find the next layer's GetInstanceProcAddr(GIPA) function
  const void* pNextChain = pCreateInfo->pNext;
  const VkLayerInstanceCreateInfo* layer_instance_info = nullptr;
  while (pNextChain) {
    layer_instance_info = reinterpret_cast<const VkLayerInstanceCreateInfo*>(pNextChain);
    pNextChain = layer_instance_info->pNext;
    if (layer_instance_info->sType != VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO) {
      continue;
    }
    spdlog::trace("layer_instance_info->function: {}", (int)layer_instance_info->function);
    if (layer_instance_info->function == VK_LAYER_LINK_INFO) {
      break;
    }
  }
  PFN_vkGetInstanceProcAddr nxtGipa = layer_instance_info->u.pLayerInfo->pfnNextGetInstanceProcAddr;
  assert(nxtGipa);

  // advance the linked list for the next layer
  {
    VkLayerInstanceCreateInfo* layer_instance_info_mut = const_cast<VkLayerInstanceCreateInfo*>(layer_instance_info);
    layer_instance_info_mut->u.pLayerInfo = layer_instance_info->u.pLayerInfo->pNext;
  }

  PFN_vkCreateInstance nxtCreateInstance = reinterpret_cast<PFN_vkCreateInstance>(nxtGipa(nullptr, "vkCreateInstance"));
  if (!nxtCreateInstance) {
    spdlog::error("Failed to fetch vkCreateInstance from next layer");
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  VkResult result = nxtCreateInstance(pCreateInfo, pAllocator, pInstance);

  g_instance_infos[*pInstance].nxtGipa = nxtGipa;

  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator) {
  spdlog::trace("DestroyInstance");

  // find the next layer's GetInstanceProcAddr(GIPA) function
  PFN_vkGetInstanceProcAddr nxtGipa = g_instance_infos[instance].nxtGipa;

  PFN_vkDestroyInstance nxtDestroyInstance =
      reinterpret_cast<PFN_vkDestroyInstance>(nxtGipa(instance, "vkDestroyInstance"));
  if (!nxtDestroyInstance) {
    spdlog::error("Failed to fetch vkDestroyInstance from next layer");
    return;
  }

  nxtDestroyInstance(instance, pAllocator);

  g_instance_infos.erase(instance);
}

}  // namespace vvk