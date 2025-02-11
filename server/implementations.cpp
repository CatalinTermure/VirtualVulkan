#include "implementations.h"

#include <vulkan/vulkan.h>

#include <cassert>
#include <unordered_map>
#include <vector>

namespace {
std::unordered_map<VkInstance, VkInstance> g_instance_map;
}

void UnpackAndExecuteVkCreateInstance(const vvk::server::VvkRequest& request) {
  assert(request.method() == "vkCreateInstance");

  assert(request.vkcreateinstance().pcreateinfo_size() == 1);
  VkInstanceCreateInfo create_info = {};
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.flags = request.vkcreateinstance().pcreateinfo(0).flags();

  create_info.enabledLayerCount = request.vkcreateinstance().pcreateinfo(0).enabledlayercount();
  std::vector<const char*> enabled_layer_names;
  enabled_layer_names.reserve(create_info.enabledLayerCount);
  for (int i = 0; i < create_info.enabledLayerCount; ++i) {
    enabled_layer_names.push_back(request.vkcreateinstance().pcreateinfo(0).ppenabledlayernames(i).data());
  }
  create_info.ppEnabledLayerNames = enabled_layer_names.data();

  create_info.enabledExtensionCount = request.vkcreateinstance().pcreateinfo(0).enabledextensioncount();
  std::vector<const char*> enabled_extension_names;
  enabled_extension_names.reserve(create_info.enabledExtensionCount);
  for (int i = 0; i < create_info.enabledExtensionCount; ++i) {
    enabled_extension_names.push_back(request.vkcreateinstance().pcreateinfo(0).ppenabledextensionnames(i).data());
  }
  create_info.ppEnabledExtensionNames = enabled_extension_names.data();

  VkApplicationInfo application_info = {};
  application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;

  assert(request.vkcreateinstance().pcreateinfo(0).papplicationinfo_size() == 1);
  application_info.pApplicationName =
      request.vkcreateinstance().pcreateinfo(0).papplicationinfo(0).papplicationname().data();
  application_info.applicationVersion =
      request.vkcreateinstance().pcreateinfo(0).papplicationinfo(0).applicationversion();
  application_info.pEngineName = request.vkcreateinstance().pcreateinfo(0).papplicationinfo(0).penginename().data();
  application_info.engineVersion = request.vkcreateinstance().pcreateinfo(0).papplicationinfo(0).engineversion();
  application_info.apiVersion = request.vkcreateinstance().pcreateinfo(0).papplicationinfo(0).apiversion();
  create_info.pApplicationInfo = &application_info;

  VkInstance old_instance;
  assert(request.vkcreateinstance().pinstance_size() == 1);
  old_instance = reinterpret_cast<VkInstance>(request.vkcreateinstance().pinstance(0));

  VkInstance new_instance;
  vkCreateInstance(&create_info, nullptr, &new_instance);

  g_instance_map[old_instance] = new_instance;
}