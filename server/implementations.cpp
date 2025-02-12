// GENERATED FILE - DO NOT EDIT
// clang-format off
#include "implementations.h"

#include <vulkan/vulkan.h>

#include <cassert>
#include <unordered_map>
#include <vector>

namespace {
std::unordered_map<void*, void*> client_to_server_handles;
}

void UnpackAndExecuteVkCreateInstance(const vvk::server::VvkRequest &request,
                                      vvk::server::VvkResponse* response) {
  assert(request.method() == "vkCreateInstance");

  assert(request.vkcreateinstance().pcreateinfo_size() == 1);
  VkInstanceCreateInfo pCreateInfo;
  pCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  pCreateInfo.pNext = nullptr; // pNext chains are currently unsupported
  pCreateInfo.flags = request.vkcreateinstance().pcreateinfo(0).flags();
  assert(request.vkcreateinstance().pcreateinfo(0).papplicationinfo_size() == 1);
  VkApplicationInfo pCreateInfo_pApplicationInfo;
  pCreateInfo_pApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  pCreateInfo_pApplicationInfo.pNext = nullptr; // pNext chains are currently unsupported
  pCreateInfo_pApplicationInfo.pApplicationName = request.vkcreateinstance().pcreateinfo(0).papplicationinfo(0).papplicationname().data();
  pCreateInfo_pApplicationInfo.applicationVersion = request.vkcreateinstance().pcreateinfo(0).papplicationinfo(0).applicationversion();
  pCreateInfo_pApplicationInfo.pEngineName = request.vkcreateinstance().pcreateinfo(0).papplicationinfo(0).penginename().data();
  pCreateInfo_pApplicationInfo.engineVersion = request.vkcreateinstance().pcreateinfo(0).papplicationinfo(0).engineversion();
  pCreateInfo_pApplicationInfo.apiVersion = request.vkcreateinstance().pcreateinfo(0).papplicationinfo(0).apiversion();
  pCreateInfo.pApplicationInfo = &pCreateInfo_pApplicationInfo;
  pCreateInfo.enabledLayerCount = request.vkcreateinstance().pcreateinfo(0).enabledlayercount();
  std::vector<const char*> pCreateInfo_ppEnabledLayerNames;
  for (int i = 0; i < request.vkcreateinstance().pcreateinfo(0).ppenabledlayernames_size(); i++) {
    pCreateInfo_ppEnabledLayerNames.push_back(request.vkcreateinstance().pcreateinfo(0).ppenabledlayernames(i).data());
  }
  pCreateInfo.ppEnabledLayerNames = pCreateInfo_ppEnabledLayerNames.data();
  pCreateInfo.enabledExtensionCount = request.vkcreateinstance().pcreateinfo(0).enabledextensioncount();
  std::vector<const char*> pCreateInfo_ppEnabledExtensionNames;
  for (int i = 0; i < request.vkcreateinstance().pcreateinfo(0).ppenabledextensionnames_size(); i++) {
    pCreateInfo_ppEnabledExtensionNames.push_back(request.vkcreateinstance().pcreateinfo(0).ppenabledextensionnames(i).data());
  }
  pCreateInfo.ppEnabledExtensionNames = pCreateInfo_ppEnabledExtensionNames.data();

  assert(request.vkcreateinstance().pinstance_size() == 1);
  VkInstance client_pInstance = reinterpret_cast<VkInstance>(request.vkcreateinstance().pinstance(0));
  VkInstance server_pInstance;

  VkResult result = vkCreateInstance(&pCreateInfo, nullptr, &server_pInstance);
  response->set_result(result);
  client_to_server_handles[client_pInstance] = server_pInstance;
}
void UnpackAndExecuteVkDestroyInstance(const vvk::server::VvkRequest &request,
                                      vvk::server::VvkResponse* response) {
  assert(request.method() == "vkDestroyInstance");


  vkDestroyInstance(reinterpret_cast<VkInstance>(client_to_server_handles.at(reinterpret_cast<void*>(request.vkdestroyinstance().instance()))), nullptr);
  response->set_result(VK_SUCCESS);
}

