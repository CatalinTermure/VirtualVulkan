// GENERATED FILE - DO NOT EDIT
// clang-format off
#include "remote_call.h"

#include <vulkan/vulkan.h>
#include <spdlog/spdlog.h>
#include "vvk_server.grpc.pb.h"

namespace vvk {
VkResult PackAndCallVkCreateInstance(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateInstance");
  vvk::server::VkInstanceCreateInfo* pCreateInfo_proto = request.mutable_vkcreateinstance()->mutable_pcreateinfo();
  // pNext chains are currently not supported
  pCreateInfo_proto->set_flags(pCreateInfo->flags);
  vvk::server::VkApplicationInfo* pCreateInfo_proto_pApplicationInfo_proto = pCreateInfo_proto->mutable_papplicationinfo();
  // pNext chains are currently not supported
  pCreateInfo_proto_pApplicationInfo_proto->set_papplicationname(pCreateInfo->pApplicationInfo->pApplicationName);
  pCreateInfo_proto_pApplicationInfo_proto->set_applicationversion(pCreateInfo->pApplicationInfo->applicationVersion);
  pCreateInfo_proto_pApplicationInfo_proto->set_penginename(pCreateInfo->pApplicationInfo->pEngineName);
  pCreateInfo_proto_pApplicationInfo_proto->set_engineversion(pCreateInfo->pApplicationInfo->engineVersion);
  pCreateInfo_proto_pApplicationInfo_proto->set_apiversion(pCreateInfo->pApplicationInfo->apiVersion);
  pCreateInfo_proto->set_enabledlayercount(pCreateInfo->enabledLayerCount);
  for (int i = 0; i < pCreateInfo->enabledLayerCount; i++) {
    pCreateInfo_proto->add_ppenabledlayernames(pCreateInfo->ppEnabledLayerNames[i]);
  }
  pCreateInfo_proto->set_enabledextensioncount(pCreateInfo->enabledExtensionCount);
  for (int i = 0; i < pCreateInfo->enabledExtensionCount; i++) {
    pCreateInfo_proto->add_ppenabledextensionnames(pCreateInfo->ppEnabledExtensionNames[i]);
  }
  request.mutable_vkcreateinstance()->set_pinstance(reinterpret_cast<uint64_t>(*pInstance));
  vvk::server::VvkResponse response;

  if (!stream->Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream->Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkDestroyInstance(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkInstance instance, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkDestroyInstance");
  request.mutable_vkdestroyinstance()->set_instance(reinterpret_cast<uint64_t>(instance));
  vvk::server::VvkResponse response;

  if (!stream->Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream->Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
VkResult PackAndCallVkEnumeratePhysicalDevices(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices) {
  vvk::server::VvkRequest request;
  request.set_method("vkEnumeratePhysicalDevices");
  request.mutable_vkenumeratephysicaldevices()->set_instance(reinterpret_cast<uint64_t>(instance));
  request.mutable_vkenumeratephysicaldevices()->set_pphysicaldevicecount(*pPhysicalDeviceCount);
  if (pPhysicalDevices) {
    // the value we set is just a sentinel value, only its presence should be checked
    request.mutable_vkenumeratephysicaldevices()->add_pphysicaldevices(reinterpret_cast<uint64_t>(pPhysicalDevices));
  } else {
    request.mutable_vkenumeratephysicaldevices()->set_pphysicaldevicecount(0);
  }
  vvk::server::VvkResponse response;

  if (!stream->Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream->Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.result());
}
}  // namespace vvk

