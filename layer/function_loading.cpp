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

std::unordered_map<std::string, PFN_vkVoidFunction> g_name_to_func_ptr = {
    {"vkGetDeviceProcAddr", reinterpret_cast<PFN_vkVoidFunction>(GetDeviceProcAddr)},
    {"vkCreateInstance", reinterpret_cast<PFN_vkVoidFunction>(CreateInstance)},
};

}  // namespace

PFN_vkVoidFunction GetInstanceProcAddr(VkInstance instance, const char* pName) {
  spdlog::trace("Loading instance function: {}", pName);
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
