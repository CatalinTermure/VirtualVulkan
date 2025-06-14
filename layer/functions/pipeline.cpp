#include "commons/remote_call.h"
#include "layer/context/device.h"
#include "layer/functions.h"

namespace vvk {

VKAPI_ATTR VkResult VKAPI_CALL CreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo,
                                                   const VkAllocationCallbacks* pAllocator,
                                                   VkPipelineCache* pPipelineCache) {
  Device& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreatePipelineCache(device_info.instance_info().command_stream(),
                                          device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator,
                                          pPipelineCache);
}
VKAPI_ATTR void VKAPI_CALL DestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache,
                                                const VkAllocationCallbacks* pAllocator) {
  Device& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyPipelineCache(device_info.instance_info().command_stream(),
                                    device_info.instance_info().GetRemoteHandle(device), pipelineCache, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo,
                                                  const VkAllocationCallbacks* pAllocator,
                                                  VkShaderModule* pShaderModule) {
  Device& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateShaderModule(device_info.instance_info().command_stream(),
                                         device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator,
                                         pShaderModule);
}
VKAPI_ATTR void VKAPI_CALL DestroyShaderModule(VkDevice device, VkShaderModule shaderModule,
                                               const VkAllocationCallbacks* pAllocator) {
  Device& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyShaderModule(device_info.instance_info().command_stream(),
                                   device_info.instance_info().GetRemoteHandle(device), shaderModule, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo,
                                                    const VkAllocationCallbacks* pAllocator,
                                                    VkPipelineLayout* pPipelineLayout) {
  Device& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreatePipelineLayout(device_info.instance_info().command_stream(),
                                           device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator,
                                           pPipelineLayout);
}
VKAPI_ATTR void VKAPI_CALL DestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout,
                                                 const VkAllocationCallbacks* pAllocator) {
  Device& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyPipelineLayout(device_info.instance_info().command_stream(),
                                     device_info.instance_info().GetRemoteHandle(device), pipelineLayout, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache,
                                                      uint32_t createInfoCount,
                                                      const VkComputePipelineCreateInfo* pCreateInfos,
                                                      const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) {
  Device& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateComputePipelines(device_info.instance_info().command_stream(),
                                             device_info.instance_info().GetRemoteHandle(device), pipelineCache,
                                             createInfoCount, pCreateInfos, pAllocator, pPipelines);
}
VKAPI_ATTR VkResult VKAPI_CALL CreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache,
                                                       uint32_t createInfoCount,
                                                       const VkGraphicsPipelineCreateInfo* pCreateInfos,
                                                       const VkAllocationCallbacks* pAllocator,
                                                       VkPipeline* pPipelines) {
  Device& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateGraphicsPipelines(device_info.instance_info().command_stream(),
                                              device_info.instance_info().GetRemoteHandle(device), pipelineCache,
                                              createInfoCount, pCreateInfos, pAllocator, pPipelines);
}
VKAPI_ATTR void VKAPI_CALL DestroyPipeline(VkDevice device, VkPipeline pipeline,
                                           const VkAllocationCallbacks* pAllocator) {
  Device& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyPipeline(device_info.instance_info().command_stream(),
                               device_info.instance_info().GetRemoteHandle(device), pipeline, pAllocator);
}

}  // namespace vvk
