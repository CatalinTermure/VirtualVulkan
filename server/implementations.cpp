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

  VkInstanceCreateInfo pCreateInfo;
  pCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  pCreateInfo.pNext = nullptr; // pNext chains are currently unsupported
  pCreateInfo.flags = request.vkcreateinstance().pcreateinfo().flags();
  VkApplicationInfo pCreateInfo_pApplicationInfo;
  pCreateInfo_pApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  pCreateInfo_pApplicationInfo.pNext = nullptr; // pNext chains are currently unsupported
  pCreateInfo_pApplicationInfo.pApplicationName = request.vkcreateinstance().pcreateinfo().papplicationinfo().papplicationname().data();
  pCreateInfo_pApplicationInfo.applicationVersion = request.vkcreateinstance().pcreateinfo().papplicationinfo().applicationversion();
  pCreateInfo_pApplicationInfo.pEngineName = request.vkcreateinstance().pcreateinfo().papplicationinfo().penginename().data();
  pCreateInfo_pApplicationInfo.engineVersion = request.vkcreateinstance().pcreateinfo().papplicationinfo().engineversion();
  pCreateInfo_pApplicationInfo.apiVersion = request.vkcreateinstance().pcreateinfo().papplicationinfo().apiversion();
  pCreateInfo.pApplicationInfo = &pCreateInfo_pApplicationInfo;
  pCreateInfo.enabledLayerCount = request.vkcreateinstance().pcreateinfo().enabledlayercount();
  std::vector<const char*> pCreateInfo_ppEnabledLayerNames;
  for (int i = 0; i < request.vkcreateinstance().pcreateinfo().ppenabledlayernames_size(); i++) {
    pCreateInfo_ppEnabledLayerNames.push_back(request.vkcreateinstance().pcreateinfo().ppenabledlayernames(i).data());
  }
  pCreateInfo.ppEnabledLayerNames = pCreateInfo_ppEnabledLayerNames.data();
  pCreateInfo.enabledExtensionCount = request.vkcreateinstance().pcreateinfo().enabledextensioncount();
  std::vector<const char*> pCreateInfo_ppEnabledExtensionNames;
  for (int i = 0; i < request.vkcreateinstance().pcreateinfo().ppenabledextensionnames_size(); i++) {
    pCreateInfo_ppEnabledExtensionNames.push_back(request.vkcreateinstance().pcreateinfo().ppenabledextensionnames(i).data());
  }
  pCreateInfo.ppEnabledExtensionNames = pCreateInfo_ppEnabledExtensionNames.data();

  VkInstance client_pInstance = reinterpret_cast<VkInstance>(request.vkcreateinstance().pinstance());
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

