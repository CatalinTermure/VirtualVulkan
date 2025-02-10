#include "function_loading.h"

#include <grpcpp/grpcpp.h>
#include <spdlog/spdlog.h>
#include <vulkan/vk_icd.h>

#include <cassert>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "functions.h"
#include "vvk_server.grpc.pb.h"

namespace vvk {

namespace {

PFN_vkVoidFunction GetDeviceProcAddr(VkDevice device, const char* pName);

std::unordered_map<std::string, PFN_vkVoidFunction> g_name_to_func_ptr = {
    {"vkCreateInstance", reinterpret_cast<PFN_vkVoidFunction>(CreateInstance)},
    {"vkDestroyInstance", reinterpret_cast<PFN_vkVoidFunction>(DestroyInstance)},
    {"vkEnumerateInstanceExtensionProperties",
     reinterpret_cast<PFN_vkVoidFunction>(EnumerateInstanceExtensionProperties)},
    {"vkEnumerateInstanceVersion", reinterpret_cast<PFN_vkVoidFunction>(EnumerateInstanceVersion)},
    {"vkEnumeratePhysicalDevices", reinterpret_cast<PFN_vkVoidFunction>(EnumeratePhysicalDevices)},
    {"vkGetPhysicalDeviceFeatures", reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceFeatures)},
    {"vkGetPhysicalDeviceFeatures2", reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceFeatures2)},
    {"vkGetPhysicalDeviceFormatProperties", reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceFormatProperties)},
    {"vkGetPhysicalDeviceImageFormatProperties",
     reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceImageFormatProperties)},
    {"vkGetPhysicalDeviceProperties", reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceProperties)},
    {"vkGetPhysicalDeviceProperties2", reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceProperties2)},
    {"vkGetPhysicalDeviceQueueFamilyProperties",
     reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceQueueFamilyProperties)},
    {"vkGetPhysicalDeviceMemoryProperties", reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceMemoryProperties)},
    {"vkGetDeviceProcAddr", reinterpret_cast<PFN_vkVoidFunction>(GetDeviceProcAddr)},
    {"vkCreateDevice", reinterpret_cast<PFN_vkVoidFunction>(CreateDevice)},
    {"vkDestroyDevice", reinterpret_cast<PFN_vkVoidFunction>(DestroyDevice)},
    {"vkEnumerateDeviceExtensionProperties", reinterpret_cast<PFN_vkVoidFunction>(EnumerateDeviceExtensionProperties)},
    {"vkGetPhysicalDeviceSparseImageFormatProperties",
     reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceSparseImageFormatProperties)},
};

PFN_vkVoidFunction GetDeviceProcAddr(VkDevice device, const char* pName) {
  spdlog::trace("Loading device function: {}", pName);
  auto it = g_name_to_func_ptr.find(pName);
  if (it != g_name_to_func_ptr.end()) {
    return it->second;
  }

  return nullptr;
}

}  // namespace

PFN_vkVoidFunction GetInstanceProcAddr(VkInstance instance, const char* pName) {
  spdlog::trace("Loading instance function: {}", pName);
  auto it = g_name_to_func_ptr.find(pName);
  if (it != g_name_to_func_ptr.end()) {
    return it->second;
  }

  return nullptr;
}

}  // namespace vvk
