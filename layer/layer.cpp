#include <spdlog/cfg/env.h>
#include <spdlog/spdlog.h>
#include <vulkan/vk_layer.h>

#undef VK_LAYER_EXPORT
#if defined(_WIN32)
#define VK_LAYER_EXPORT extern "C" __declspec(dllexport)
#else
#define VK_LAYER_EXPORT extern "C" __attribute__((visibility("default")))
#endif

#define VVK_MIN_SUPPORTED_LOADER_LAYER_INTERFACE_VERSION 2

#include "layer/function_loading.h"

VK_LAYER_EXPORT VkResult VKAPI_CALL
VVK_NegotiateLoaderLayerInterfaceVersion(VkNegotiateLayerInterface* pVersionStruct) {
  if (pVersionStruct->loaderLayerInterfaceVersion < VVK_MIN_SUPPORTED_LOADER_LAYER_INTERFACE_VERSION) {
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [VvkLayer] [%^%l%$] %v");
  spdlog::cfg::load_env_levels("VVK_LAYER_LOG_LEVEL");

  pVersionStruct->sType = LAYER_NEGOTIATE_INTERFACE_STRUCT;
  pVersionStruct->pNext = nullptr;
  pVersionStruct->loaderLayerInterfaceVersion = CURRENT_LOADER_LAYER_INTERFACE_VERSION;
  pVersionStruct->pfnGetInstanceProcAddr = vvk::GetInstanceProcAddr;
  pVersionStruct->pfnGetDeviceProcAddr = vvk::GetDeviceProcAddr;
  pVersionStruct->pfnGetPhysicalDeviceProcAddr = vvk::GetPhysicalDeviceProcAddr;

  return VK_SUCCESS;
}