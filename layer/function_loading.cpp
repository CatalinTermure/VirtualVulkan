#include "layer/function_loading.h"

#include <grpcpp/grpcpp.h>
#include <spdlog/spdlog.h>
#include <vulkan/vk_layer.h>

#include <cassert>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "layer/functions.h"

namespace vvk {

namespace {

VkResult VKAPI_CALL EnumerateInstanceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* pProperties) {
  if (pProperties == nullptr) {
    *pPropertyCount = 1;
    return VK_SUCCESS;
  }

  assert(*pPropertyCount == 1);

  strncpy(pProperties->layerName, "VK_LAYER_VVK_virtual_vulkan", 256);
  strncpy(pProperties->description, "Remote rendering layer", 256);
  pProperties->implementationVersion = 1;
  pProperties->specVersion = VK_API_VERSION_1_4;

  return VK_SUCCESS;
}

constexpr std::array non_intercepted_functions = {
    "vkCreateXcbSurfaceKHR",
    "vkCreateXlibSurfaceKHR",
    "vkCreateWaylandSurfaceKHR",
    "vkGetPhysicalDeviceSurfaceSupportKHR",
    // TODO: implement debug report callbacks
    "vkCreateDebugReportCallbackEXT",
    "vkDestroyDebugReportCallbackEXT",
    "vkGetPhysicalDeviceSurfaceFormatsKHR",
    "vkGetPhysicalDeviceSurfaceCapabilitiesKHR",
    "vkGetPhysicalDeviceSurfacePresentModesKHR",
};

}  // namespace

#define GET_PROC_ADDR(func_name)                            \
  if (strcmp(pName, "vk" #func_name) == 0) {                \
    return reinterpret_cast<PFN_vkVoidFunction>(func_name); \
  }

PFN_vkVoidFunction GetInstanceProcAddr(VkInstance instance, const char* pName) {
  spdlog::trace("Loading instance function: {}", pName);
  GET_PROC_ADDR(GetDeviceProcAddr);
  GET_PROC_ADDR(EnumerateInstanceLayerProperties);

  for (const auto& func : non_intercepted_functions) {
    if (strcmp(pName, func) == 0) {
      return DefaultGetInstanceProcAddr(instance, pName);
    }
  }

  auto it = g_name_to_func_ptr.find(pName);
  if (it != g_name_to_func_ptr.end()) {
    return it->second;
  }
  spdlog::warn("Instance function not found: {}", pName);
  return nullptr;
}

PFN_vkVoidFunction GetDeviceProcAddr(VkDevice device, const char* pName) {
  spdlog::trace("Loading device function: {}", pName);

  GET_PROC_ADDR(CreateSwapchainKHR);
  GET_PROC_ADDR(DestroySwapchainKHR);
  GET_PROC_ADDR(GetSwapchainImagesKHR);

  for (const auto& func : non_intercepted_functions) {
    if (strcmp(pName, func) == 0) {
      return DefaultGetDeviceProcAddr(device, pName);
    }
  }

  auto it = g_name_to_func_ptr.find(pName);
  if (it != g_name_to_func_ptr.end()) {
    return it->second;
  }

  spdlog::warn("Device function not found: {}", pName);
  return nullptr;
}

PFN_vkVoidFunction GetPhysicalDeviceProcAddr(VkInstance instance, const char* pName) {
  spdlog::trace("Loading physical device function: {}", pName);
  auto it = g_name_to_func_ptr.find(pName);
  if (it != g_name_to_func_ptr.end()) {
    return it->second;
  }

  spdlog::warn("Physical device function not found: {}", pName);
  return nullptr;
}

}  // namespace vvk
