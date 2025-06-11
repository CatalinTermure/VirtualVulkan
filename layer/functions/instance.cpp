// clang-format off
#include "layer/wsi_support.h"
// clang-format on

#include "layer/context/instance.h"

#include <spdlog/spdlog.h>
#include <vulkan/vk_layer.h>

#include "commons/remote_call.h"
#include "layer/functions.h"
#include "layer/utils.h"

namespace vvk {

namespace {
const std::unordered_set<std::string> kAllowedInstanceExtensions = {};
const std::unordered_set<std::string> kAllowedLayers = {
    "VK_LAYER_KHRONOS_validation",
};
}  // namespace

VKAPI_ATTR VkResult VKAPI_CALL CreateInstance(const VkInstanceCreateInfo* pCreateInfo,
                                              const VkAllocationCallbacks* pAllocator, VkInstance* pInstance) {
  spdlog::trace("CreateInstance");

  // TODO: what from the pNext chain do we need to pass to remote server?

  // find the next layer's GetInstanceProcAddr(GIPA) function
  const void* p_next_chain = pCreateInfo->pNext;
  const VkLayerInstanceCreateInfo* layer_instance_info =
      FindLayerLinkInfo<VkLayerInstanceCreateInfo, VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO>(p_next_chain);
  PFN_vkGetInstanceProcAddr nxt_gipa = layer_instance_info->u.pLayerInfo->pfnNextGetInstanceProcAddr;
  assert(nxt_gipa);

  // advance the linked list for the next layer
  {
    VkLayerInstanceCreateInfo* layer_instance_info_mut = const_cast<VkLayerInstanceCreateInfo*>(layer_instance_info);
    layer_instance_info_mut->u.pLayerInfo = layer_instance_info->u.pLayerInfo->pNext;
  }

  PFN_vkCreateInstance nxtCreateInstance =
      reinterpret_cast<PFN_vkCreateInstance>(nxt_gipa(nullptr, "vkCreateInstance"));
  if (!nxtCreateInstance) {
    spdlog::error("Failed to fetch vkCreateInstance from next layer");
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  VkResult result = nxtCreateInstance(pCreateInfo, pAllocator, pInstance);

  std::string server_address = std::getenv("VVK_TARGET_SERVER");
  if (server_address.empty()) {
    spdlog::error("VVK_TARGET_SERVER environment variable not set");
    return VK_ERROR_INITIALIZATION_FAILED;
  }
  spdlog::info("Connecting to server at {}", server_address);
  InstanceInfo& instance_info =
      SetInstanceInfo(*pInstance, nxt_gipa, grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));

  // call remote create instance
  {
    // remove loader instance create info from the pNext chain
    // the loader seems to insert these structs at the beginning of the pNext chain
    // so we can remove it by copying the instance create info and skipping the loader instance create info structs
    VkInstanceCreateInfo remote_create_info = *pCreateInfo;
    RemoveStructsFromChain(reinterpret_cast<VkBaseOutStructure*>(&remote_create_info),
                           VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO);
    VkApplicationInfo remote_app_info = *pCreateInfo->pApplicationInfo;
    remote_app_info.apiVersion = std::max(remote_app_info.apiVersion, VK_API_VERSION_1_3);
    remote_create_info.pApplicationInfo = &remote_app_info;

    std::vector<const char*> enabled_extensions;
    for (uint32_t i = 0; i < remote_create_info.enabledExtensionCount; i++) {
      if (kAllowedInstanceExtensions.contains(remote_create_info.ppEnabledExtensionNames[i])) {
        enabled_extensions.push_back(remote_create_info.ppEnabledExtensionNames[i]);
      }
    }
    remote_create_info.enabledExtensionCount = enabled_extensions.size();
    remote_create_info.ppEnabledExtensionNames = enabled_extensions.data();

    std::vector<const char*> enabled_layers;
    for (uint32_t i = 0; i < remote_create_info.enabledLayerCount; i++) {
      if (kAllowedLayers.contains(remote_create_info.ppEnabledLayerNames[i])) {
        enabled_layers.push_back(remote_create_info.ppEnabledLayerNames[i]);
      }
    }
    remote_create_info.enabledLayerCount = enabled_layers.size();
    remote_create_info.ppEnabledLayerNames = enabled_layers.data();

    auto& reader_writer = instance_info.command_stream();

    // We don't want to overwrite the local instance handle with the remote one
    VkInstance remote_instance = *pInstance;
    PackAndCallVkCreateInstance(reader_writer, &remote_create_info, pAllocator, &remote_instance);
    instance_info.SetRemoteHandle(*pInstance, remote_instance);
  }

  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator) {
  spdlog::trace("DestroyInstance");

  InstanceInfo& instance_info = GetInstanceInfo(instance);
  instance_info.dispatch_table().DestroyInstance(instance, pAllocator);

  auto& reader_writer = instance_info.command_stream();
  PackAndCallVkDestroyInstance(reader_writer, instance_info.GetRemoteHandle(instance), pAllocator);

  RemoveInstanceInfo(instance);
}

VKAPI_ATTR VkResult VKAPI_CALL EnumerateInstanceExtensionProperties(const char* pLayerName, uint32_t* pPropertyCount,
                                                                    VkExtensionProperties* pProperties) {
  if (!pLayerName || strcmp(pLayerName, "VK_LAYER_VVK_virtual_vulkan") != 0) {
    return VK_ERROR_LAYER_NOT_PRESENT;
  }

  // TODO: implement this
  assert(false);

  return VK_SUCCESS;
}
}  // namespace vvk
