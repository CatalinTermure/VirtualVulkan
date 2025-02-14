// GENERATED FILE - DO NOT EDIT
// clang-format off
#include "implementations.h"

#include <vulkan/vulkan.h>

#include <cassert>
#include <unordered_map>
#include <vector>

namespace {
std::unordered_map<void*, void*> client_to_server_handles;
VkPhysicalDevice physical_device_to_use;
}

void SetPhysicalDevice(VkPhysicalDevice physical_device) {
  physical_device_to_use = physical_device;
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
  assert(client_to_server_handles.count(reinterpret_cast<void*>(client_pInstance)) == 0);
  response->mutable_vkcreateinstance()->set_pinstance(reinterpret_cast<uint64_t>(server_pInstance));
  client_to_server_handles[client_pInstance] = server_pInstance;
  response->set_result(result);
}
void UnpackAndExecuteVkDestroyInstance(const vvk::server::VvkRequest &request,
                                      vvk::server::VvkResponse* response) {
  assert(request.method() == "vkDestroyInstance");

  vkDestroyInstance(reinterpret_cast<VkInstance>(client_to_server_handles.at(reinterpret_cast<void*>(request.vkdestroyinstance().instance()))), nullptr);
  response->set_result(VK_SUCCESS);
}
void UnpackAndExecuteVkEnumeratePhysicalDevices(const vvk::server::VvkRequest &request,
                                      vvk::server::VvkResponse* response) {
  assert(request.method() == "vkEnumeratePhysicalDevices");

  uint32_t pPhysicalDeviceCount = request.vkenumeratephysicaldevices().pphysicaldevicecount();
  std::vector<VkPhysicalDevice> aux_pPhysicalDevices;
  VkPhysicalDevice* pPhysicalDevices;
  if (pPhysicalDeviceCount == 0) {
    pPhysicalDevices = nullptr;
  } else {
    aux_pPhysicalDevices.resize(pPhysicalDeviceCount);
    pPhysicalDevices = aux_pPhysicalDevices.data();
  }
  VkResult result = vkEnumeratePhysicalDevices(reinterpret_cast<VkInstance>(client_to_server_handles.at(reinterpret_cast<void*>(request.vkenumeratephysicaldevices().instance()))), &pPhysicalDeviceCount, pPhysicalDevices);
  response->mutable_vkenumeratephysicaldevices()->set_pphysicaldevicecount(pPhysicalDeviceCount);
  if (request.vkenumeratephysicaldevices().pphysicaldevicecount() != 0) {
    for (int i = 0; i < pPhysicalDeviceCount; i++) {
      response->mutable_vkenumeratephysicaldevices()->add_pphysicaldevices(reinterpret_cast<uint64_t>(pPhysicalDevices[i]));
    }
  }
  response->set_result(result);
}
void UnpackAndExecuteVkGetPhysicalDeviceProperties(const vvk::server::VvkRequest &request,
                                      vvk::server::VvkResponse* response) {
  assert(request.method() == "vkGetPhysicalDeviceProperties");

  VkPhysicalDeviceProperties pProperties;
  vkGetPhysicalDeviceProperties(physical_device_to_use, &pProperties);
  vvk::server::VkPhysicalDeviceProperties* pProperties_proto = response->mutable_vkgetphysicaldeviceproperties()->mutable_pproperties();
  pProperties_proto->set_apiversion((&pProperties)->apiVersion);
  pProperties_proto->set_driverversion((&pProperties)->driverVersion);
  pProperties_proto->set_vendorid((&pProperties)->vendorID);
  pProperties_proto->set_deviceid((&pProperties)->deviceID);
  pProperties_proto->set_devicetype(static_cast<vvk::server::VkPhysicalDeviceType>((&pProperties)->deviceType));
  pProperties_proto->set_devicename((&pProperties)->deviceName);
  for (int i = 0; i < VK_UUID_SIZE; i++) {
    pProperties_proto->add_pipelinecacheuuid(static_cast<uint32_t>((&pProperties)->pipelineCacheUUID[i]));
  }
  vvk::server::VkPhysicalDeviceLimits* pProperties_proto_limits_proto = pProperties_proto->mutable_limits();
  pProperties_proto_limits_proto->set_maximagedimension1d((&(&pProperties)->limits)->maxImageDimension1D);
  pProperties_proto_limits_proto->set_maximagedimension2d((&(&pProperties)->limits)->maxImageDimension2D);
  pProperties_proto_limits_proto->set_maximagedimension3d((&(&pProperties)->limits)->maxImageDimension3D);
  pProperties_proto_limits_proto->set_maximagedimensioncube((&(&pProperties)->limits)->maxImageDimensionCube);
  pProperties_proto_limits_proto->set_maximagearraylayers((&(&pProperties)->limits)->maxImageArrayLayers);
  pProperties_proto_limits_proto->set_maxtexelbufferelements((&(&pProperties)->limits)->maxTexelBufferElements);
  pProperties_proto_limits_proto->set_maxuniformbufferrange((&(&pProperties)->limits)->maxUniformBufferRange);
  pProperties_proto_limits_proto->set_maxstoragebufferrange((&(&pProperties)->limits)->maxStorageBufferRange);
  pProperties_proto_limits_proto->set_maxpushconstantssize((&(&pProperties)->limits)->maxPushConstantsSize);
  pProperties_proto_limits_proto->set_maxmemoryallocationcount((&(&pProperties)->limits)->maxMemoryAllocationCount);
  pProperties_proto_limits_proto->set_maxsamplerallocationcount((&(&pProperties)->limits)->maxSamplerAllocationCount);
  pProperties_proto_limits_proto->set_bufferimagegranularity(static_cast<uint64_t>((&(&pProperties)->limits)->bufferImageGranularity));
  pProperties_proto_limits_proto->set_sparseaddressspacesize(static_cast<uint64_t>((&(&pProperties)->limits)->sparseAddressSpaceSize));
  pProperties_proto_limits_proto->set_maxbounddescriptorsets((&(&pProperties)->limits)->maxBoundDescriptorSets);
  pProperties_proto_limits_proto->set_maxperstagedescriptorsamplers((&(&pProperties)->limits)->maxPerStageDescriptorSamplers);
  pProperties_proto_limits_proto->set_maxperstagedescriptoruniformbuffers((&(&pProperties)->limits)->maxPerStageDescriptorUniformBuffers);
  pProperties_proto_limits_proto->set_maxperstagedescriptorstoragebuffers((&(&pProperties)->limits)->maxPerStageDescriptorStorageBuffers);
  pProperties_proto_limits_proto->set_maxperstagedescriptorsampledimages((&(&pProperties)->limits)->maxPerStageDescriptorSampledImages);
  pProperties_proto_limits_proto->set_maxperstagedescriptorstorageimages((&(&pProperties)->limits)->maxPerStageDescriptorStorageImages);
  pProperties_proto_limits_proto->set_maxperstagedescriptorinputattachments((&(&pProperties)->limits)->maxPerStageDescriptorInputAttachments);
  pProperties_proto_limits_proto->set_maxperstageresources((&(&pProperties)->limits)->maxPerStageResources);
  pProperties_proto_limits_proto->set_maxdescriptorsetsamplers((&(&pProperties)->limits)->maxDescriptorSetSamplers);
  pProperties_proto_limits_proto->set_maxdescriptorsetuniformbuffers((&(&pProperties)->limits)->maxDescriptorSetUniformBuffers);
  pProperties_proto_limits_proto->set_maxdescriptorsetuniformbuffersdynamic((&(&pProperties)->limits)->maxDescriptorSetUniformBuffersDynamic);
  pProperties_proto_limits_proto->set_maxdescriptorsetstoragebuffers((&(&pProperties)->limits)->maxDescriptorSetStorageBuffers);
  pProperties_proto_limits_proto->set_maxdescriptorsetstoragebuffersdynamic((&(&pProperties)->limits)->maxDescriptorSetStorageBuffersDynamic);
  pProperties_proto_limits_proto->set_maxdescriptorsetsampledimages((&(&pProperties)->limits)->maxDescriptorSetSampledImages);
  pProperties_proto_limits_proto->set_maxdescriptorsetstorageimages((&(&pProperties)->limits)->maxDescriptorSetStorageImages);
  pProperties_proto_limits_proto->set_maxdescriptorsetinputattachments((&(&pProperties)->limits)->maxDescriptorSetInputAttachments);
  pProperties_proto_limits_proto->set_maxvertexinputattributes((&(&pProperties)->limits)->maxVertexInputAttributes);
  pProperties_proto_limits_proto->set_maxvertexinputbindings((&(&pProperties)->limits)->maxVertexInputBindings);
  pProperties_proto_limits_proto->set_maxvertexinputattributeoffset((&(&pProperties)->limits)->maxVertexInputAttributeOffset);
  pProperties_proto_limits_proto->set_maxvertexinputbindingstride((&(&pProperties)->limits)->maxVertexInputBindingStride);
  pProperties_proto_limits_proto->set_maxvertexoutputcomponents((&(&pProperties)->limits)->maxVertexOutputComponents);
  pProperties_proto_limits_proto->set_maxtessellationgenerationlevel((&(&pProperties)->limits)->maxTessellationGenerationLevel);
  pProperties_proto_limits_proto->set_maxtessellationpatchsize((&(&pProperties)->limits)->maxTessellationPatchSize);
  pProperties_proto_limits_proto->set_maxtessellationcontrolpervertexinputcomponents((&(&pProperties)->limits)->maxTessellationControlPerVertexInputComponents);
  pProperties_proto_limits_proto->set_maxtessellationcontrolpervertexoutputcomponents((&(&pProperties)->limits)->maxTessellationControlPerVertexOutputComponents);
  pProperties_proto_limits_proto->set_maxtessellationcontrolperpatchoutputcomponents((&(&pProperties)->limits)->maxTessellationControlPerPatchOutputComponents);
  pProperties_proto_limits_proto->set_maxtessellationcontroltotaloutputcomponents((&(&pProperties)->limits)->maxTessellationControlTotalOutputComponents);
  pProperties_proto_limits_proto->set_maxtessellationevaluationinputcomponents((&(&pProperties)->limits)->maxTessellationEvaluationInputComponents);
  pProperties_proto_limits_proto->set_maxtessellationevaluationoutputcomponents((&(&pProperties)->limits)->maxTessellationEvaluationOutputComponents);
  pProperties_proto_limits_proto->set_maxgeometryshaderinvocations((&(&pProperties)->limits)->maxGeometryShaderInvocations);
  pProperties_proto_limits_proto->set_maxgeometryinputcomponents((&(&pProperties)->limits)->maxGeometryInputComponents);
  pProperties_proto_limits_proto->set_maxgeometryoutputcomponents((&(&pProperties)->limits)->maxGeometryOutputComponents);
  pProperties_proto_limits_proto->set_maxgeometryoutputvertices((&(&pProperties)->limits)->maxGeometryOutputVertices);
  pProperties_proto_limits_proto->set_maxgeometrytotaloutputcomponents((&(&pProperties)->limits)->maxGeometryTotalOutputComponents);
  pProperties_proto_limits_proto->set_maxfragmentinputcomponents((&(&pProperties)->limits)->maxFragmentInputComponents);
  pProperties_proto_limits_proto->set_maxfragmentoutputattachments((&(&pProperties)->limits)->maxFragmentOutputAttachments);
  pProperties_proto_limits_proto->set_maxfragmentdualsrcattachments((&(&pProperties)->limits)->maxFragmentDualSrcAttachments);
  pProperties_proto_limits_proto->set_maxfragmentcombinedoutputresources((&(&pProperties)->limits)->maxFragmentCombinedOutputResources);
  pProperties_proto_limits_proto->set_maxcomputesharedmemorysize((&(&pProperties)->limits)->maxComputeSharedMemorySize);
  for (int i = 0; i < 3; i++) {
    pProperties_proto_limits_proto->add_maxcomputeworkgroupcount((&(&pProperties)->limits)->maxComputeWorkGroupCount[i]);
  }
  pProperties_proto_limits_proto->set_maxcomputeworkgroupinvocations((&(&pProperties)->limits)->maxComputeWorkGroupInvocations);
  for (int i = 0; i < 3; i++) {
    pProperties_proto_limits_proto->add_maxcomputeworkgroupsize((&(&pProperties)->limits)->maxComputeWorkGroupSize[i]);
  }
  pProperties_proto_limits_proto->set_subpixelprecisionbits((&(&pProperties)->limits)->subPixelPrecisionBits);
  pProperties_proto_limits_proto->set_subtexelprecisionbits((&(&pProperties)->limits)->subTexelPrecisionBits);
  pProperties_proto_limits_proto->set_mipmapprecisionbits((&(&pProperties)->limits)->mipmapPrecisionBits);
  pProperties_proto_limits_proto->set_maxdrawindexedindexvalue((&(&pProperties)->limits)->maxDrawIndexedIndexValue);
  pProperties_proto_limits_proto->set_maxdrawindirectcount((&(&pProperties)->limits)->maxDrawIndirectCount);
  pProperties_proto_limits_proto->set_maxsamplerlodbias((&(&pProperties)->limits)->maxSamplerLodBias);
  pProperties_proto_limits_proto->set_maxsampleranisotropy((&(&pProperties)->limits)->maxSamplerAnisotropy);
  pProperties_proto_limits_proto->set_maxviewports((&(&pProperties)->limits)->maxViewports);
  for (int i = 0; i < 2; i++) {
    pProperties_proto_limits_proto->add_maxviewportdimensions((&(&pProperties)->limits)->maxViewportDimensions[i]);
  }
  for (int i = 0; i < 2; i++) {
    pProperties_proto_limits_proto->add_viewportboundsrange((&(&pProperties)->limits)->viewportBoundsRange[i]);
  }
  pProperties_proto_limits_proto->set_viewportsubpixelbits((&(&pProperties)->limits)->viewportSubPixelBits);
  pProperties_proto_limits_proto->set_minmemorymapalignment((&(&pProperties)->limits)->minMemoryMapAlignment);
  pProperties_proto_limits_proto->set_mintexelbufferoffsetalignment(static_cast<uint64_t>((&(&pProperties)->limits)->minTexelBufferOffsetAlignment));
  pProperties_proto_limits_proto->set_minuniformbufferoffsetalignment(static_cast<uint64_t>((&(&pProperties)->limits)->minUniformBufferOffsetAlignment));
  pProperties_proto_limits_proto->set_minstoragebufferoffsetalignment(static_cast<uint64_t>((&(&pProperties)->limits)->minStorageBufferOffsetAlignment));
  pProperties_proto_limits_proto->set_mintexeloffset((&(&pProperties)->limits)->minTexelOffset);
  pProperties_proto_limits_proto->set_maxtexeloffset((&(&pProperties)->limits)->maxTexelOffset);
  pProperties_proto_limits_proto->set_mintexelgatheroffset((&(&pProperties)->limits)->minTexelGatherOffset);
  pProperties_proto_limits_proto->set_maxtexelgatheroffset((&(&pProperties)->limits)->maxTexelGatherOffset);
  pProperties_proto_limits_proto->set_mininterpolationoffset((&(&pProperties)->limits)->minInterpolationOffset);
  pProperties_proto_limits_proto->set_maxinterpolationoffset((&(&pProperties)->limits)->maxInterpolationOffset);
  pProperties_proto_limits_proto->set_subpixelinterpolationoffsetbits((&(&pProperties)->limits)->subPixelInterpolationOffsetBits);
  pProperties_proto_limits_proto->set_maxframebufferwidth((&(&pProperties)->limits)->maxFramebufferWidth);
  pProperties_proto_limits_proto->set_maxframebufferheight((&(&pProperties)->limits)->maxFramebufferHeight);
  pProperties_proto_limits_proto->set_maxframebufferlayers((&(&pProperties)->limits)->maxFramebufferLayers);
  pProperties_proto_limits_proto->set_framebuffercolorsamplecounts((&(&pProperties)->limits)->framebufferColorSampleCounts);
  pProperties_proto_limits_proto->set_framebufferdepthsamplecounts((&(&pProperties)->limits)->framebufferDepthSampleCounts);
  pProperties_proto_limits_proto->set_framebufferstencilsamplecounts((&(&pProperties)->limits)->framebufferStencilSampleCounts);
  pProperties_proto_limits_proto->set_framebuffernoattachmentssamplecounts((&(&pProperties)->limits)->framebufferNoAttachmentsSampleCounts);
  pProperties_proto_limits_proto->set_maxcolorattachments((&(&pProperties)->limits)->maxColorAttachments);
  pProperties_proto_limits_proto->set_sampledimagecolorsamplecounts((&(&pProperties)->limits)->sampledImageColorSampleCounts);
  pProperties_proto_limits_proto->set_sampledimageintegersamplecounts((&(&pProperties)->limits)->sampledImageIntegerSampleCounts);
  pProperties_proto_limits_proto->set_sampledimagedepthsamplecounts((&(&pProperties)->limits)->sampledImageDepthSampleCounts);
  pProperties_proto_limits_proto->set_sampledimagestencilsamplecounts((&(&pProperties)->limits)->sampledImageStencilSampleCounts);
  pProperties_proto_limits_proto->set_storageimagesamplecounts((&(&pProperties)->limits)->storageImageSampleCounts);
  pProperties_proto_limits_proto->set_maxsamplemaskwords((&(&pProperties)->limits)->maxSampleMaskWords);
  pProperties_proto_limits_proto->set_timestampcomputeandgraphics((&(&pProperties)->limits)->timestampComputeAndGraphics);
  pProperties_proto_limits_proto->set_timestampperiod((&(&pProperties)->limits)->timestampPeriod);
  pProperties_proto_limits_proto->set_maxclipdistances((&(&pProperties)->limits)->maxClipDistances);
  pProperties_proto_limits_proto->set_maxculldistances((&(&pProperties)->limits)->maxCullDistances);
  pProperties_proto_limits_proto->set_maxcombinedclipandculldistances((&(&pProperties)->limits)->maxCombinedClipAndCullDistances);
  pProperties_proto_limits_proto->set_discretequeuepriorities((&(&pProperties)->limits)->discreteQueuePriorities);
  for (int i = 0; i < 2; i++) {
    pProperties_proto_limits_proto->add_pointsizerange((&(&pProperties)->limits)->pointSizeRange[i]);
  }
  for (int i = 0; i < 2; i++) {
    pProperties_proto_limits_proto->add_linewidthrange((&(&pProperties)->limits)->lineWidthRange[i]);
  }
  pProperties_proto_limits_proto->set_pointsizegranularity((&(&pProperties)->limits)->pointSizeGranularity);
  pProperties_proto_limits_proto->set_linewidthgranularity((&(&pProperties)->limits)->lineWidthGranularity);
  pProperties_proto_limits_proto->set_strictlines((&(&pProperties)->limits)->strictLines);
  pProperties_proto_limits_proto->set_standardsamplelocations((&(&pProperties)->limits)->standardSampleLocations);
  pProperties_proto_limits_proto->set_optimalbuffercopyoffsetalignment(static_cast<uint64_t>((&(&pProperties)->limits)->optimalBufferCopyOffsetAlignment));
  pProperties_proto_limits_proto->set_optimalbuffercopyrowpitchalignment(static_cast<uint64_t>((&(&pProperties)->limits)->optimalBufferCopyRowPitchAlignment));
  pProperties_proto_limits_proto->set_noncoherentatomsize(static_cast<uint64_t>((&(&pProperties)->limits)->nonCoherentAtomSize));
  vvk::server::VkPhysicalDeviceSparseProperties* pProperties_proto_sparseProperties_proto = pProperties_proto->mutable_sparseproperties();
  pProperties_proto_sparseProperties_proto->set_residencystandard2dblockshape((&(&pProperties)->sparseProperties)->residencyStandard2DBlockShape);
  pProperties_proto_sparseProperties_proto->set_residencystandard2dmultisampleblockshape((&(&pProperties)->sparseProperties)->residencyStandard2DMultisampleBlockShape);
  pProperties_proto_sparseProperties_proto->set_residencystandard3dblockshape((&(&pProperties)->sparseProperties)->residencyStandard3DBlockShape);
  pProperties_proto_sparseProperties_proto->set_residencyalignedmipsize((&(&pProperties)->sparseProperties)->residencyAlignedMipSize);
  pProperties_proto_sparseProperties_proto->set_residencynonresidentstrict((&(&pProperties)->sparseProperties)->residencyNonResidentStrict);
  response->set_result(VK_SUCCESS);
}

