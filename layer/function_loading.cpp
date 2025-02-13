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

#define GET_PROC_ADDR(func_name)                            \
  if (strcmp(pName, "vk" #func_name) == 0) {                \
    return reinterpret_cast<PFN_vkVoidFunction>(func_name); \
  }

PFN_vkVoidFunction GetInstanceProcAddr(VkInstance instance, const char* pName) {
  spdlog::trace("Loading instance function: {}", pName);
  GET_PROC_ADDR("GetDeviceProcAddr");
  auto it = g_name_to_func_ptr.find(pName);
  if (it != g_name_to_func_ptr.end()) {
    return it->second;
  }

  return nullptr;
}

PFN_vkVoidFunction GetDeviceProcAddr(VkDevice device, const char* pName) {
  spdlog::trace("Loading device function: {}", pName);
  auto it = g_name_to_func_ptr.find(pName);
  if (it != g_name_to_func_ptr.end()) {
    return it->second;
  }

  return nullptr;
}

PFN_vkVoidFunction GetPhysicalDeviceProcAddr(VkInstance instance, const char* pName) {
  spdlog::trace("Loading physical device function: {}", pName);
  auto it = g_name_to_func_ptr.find(pName);
  if (it != g_name_to_func_ptr.end()) {
    return it->second;
  }

  return nullptr;
}

}  // namespace vvk
