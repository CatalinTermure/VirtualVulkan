#include "layer/functions.h"

#include <spdlog/spdlog.h>
#include <vulkan/vk_layer.h>
#include <vvk_server.grpc.pb.h>
#include <vvk_server.pb.h>
#include <vvk_types.pb.h>

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
  const void* p_next_chain = pCreateInfo->pNext;
  const VkLayerInstanceCreateInfo* layer_instance_info = nullptr;
  while (p_next_chain) {
    layer_instance_info = reinterpret_cast<const VkLayerInstanceCreateInfo*>(p_next_chain);
    p_next_chain = layer_instance_info->pNext;
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

  // call remote create instance
  {
    // remove loader instance create info from the pNext chain
    // the loader seems to insert these structs at the beginning of the pNext chain
    // so we can remove it by copying the instance create info and skipping the loader instance create info structs
    VkInstanceCreateInfo remote_create_info = *pCreateInfo;
    VkBaseInStructure* next_struct = reinterpret_cast<VkBaseInStructure*>(const_cast<void*>(remote_create_info.pNext));
    VkBaseInStructure* curr_struct = reinterpret_cast<VkBaseInStructure*>(&remote_create_info);
    while (next_struct) {
      spdlog::debug("next_struct->sType: {}", (int)next_struct->sType);
      if (next_struct->sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO) {
        curr_struct->pNext = next_struct->pNext;
        next_struct = const_cast<VkBaseInStructure*>(next_struct->pNext);
      } else {
        curr_struct = reinterpret_cast<VkBaseInStructure*>(next_struct);
        next_struct = const_cast<VkBaseInStructure*>(next_struct->pNext);
      }
    }
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