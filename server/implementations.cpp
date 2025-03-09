// GENERATED FILE - DO NOT EDIT
// clang-format off
#include "implementations.h"

#include <vulkan/vulkan.h>

#include <cassert>
#include <unordered_map>
#include <vector>
#include <cstdlib>

#include "server/execution_context.h"

void UnpackAndExecuteVkCreateInstance(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateInstance");

  VkInstanceCreateInfo pCreateInfo = {};
  pCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  pCreateInfo.pNext = nullptr; // pNext chains are currently unsupported
  if (request.vkcreateinstance().pcreateinfo().has_flags()) {
    pCreateInfo.flags = static_cast<VkInstanceCreateFlags>(request.vkcreateinstance().pcreateinfo().flags());
  } else {
    pCreateInfo.flags = VkInstanceCreateFlags{};
  }
  VkApplicationInfo pCreateInfo_pApplicationInfo = {};
  if (request.vkcreateinstance().pcreateinfo().has_papplicationinfo()) {
    pCreateInfo_pApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    pCreateInfo_pApplicationInfo.pNext = nullptr; // pNext chains are currently unsupported
    if (request.vkcreateinstance().pcreateinfo().papplicationinfo().has_papplicationname()) {
      pCreateInfo_pApplicationInfo.pApplicationName = request.vkcreateinstance().pcreateinfo().papplicationinfo().papplicationname().data();
    } else {
      pCreateInfo_pApplicationInfo.pApplicationName = nullptr;
    }
    pCreateInfo_pApplicationInfo.applicationVersion = request.vkcreateinstance().pcreateinfo().papplicationinfo().applicationversion();
    if (request.vkcreateinstance().pcreateinfo().papplicationinfo().has_penginename()) {
      pCreateInfo_pApplicationInfo.pEngineName = request.vkcreateinstance().pcreateinfo().papplicationinfo().penginename().data();
    } else {
      pCreateInfo_pApplicationInfo.pEngineName = nullptr;
    }
    pCreateInfo_pApplicationInfo.engineVersion = request.vkcreateinstance().pcreateinfo().papplicationinfo().engineversion();
    pCreateInfo_pApplicationInfo.apiVersion = request.vkcreateinstance().pcreateinfo().papplicationinfo().apiversion();
    pCreateInfo.pApplicationInfo = &pCreateInfo_pApplicationInfo;
  } else {
    pCreateInfo.pApplicationInfo = nullptr;
  }
  if (request.vkcreateinstance().pcreateinfo().has_enabledlayercount()) {
    pCreateInfo.enabledLayerCount = request.vkcreateinstance().pcreateinfo().enabledlayercount();
  } else {
    pCreateInfo.enabledLayerCount = uint32_t{};
  }
  const char** pCreateInfo_ppEnabledLayerNames = new const char*[request.vkcreateinstance().pcreateinfo().ppenabledlayernames_size()]();
  pCreateInfo.ppEnabledLayerNames = pCreateInfo_ppEnabledLayerNames;
  for (int ppEnabledLayerNames_indx = 0; ppEnabledLayerNames_indx < request.vkcreateinstance().pcreateinfo().ppenabledlayernames_size(); ppEnabledLayerNames_indx++) {
    pCreateInfo_ppEnabledLayerNames[ppEnabledLayerNames_indx] = request.vkcreateinstance().pcreateinfo().ppenabledlayernames(ppEnabledLayerNames_indx).data();
  }
  if (request.vkcreateinstance().pcreateinfo().has_enabledextensioncount()) {
    pCreateInfo.enabledExtensionCount = request.vkcreateinstance().pcreateinfo().enabledextensioncount();
  } else {
    pCreateInfo.enabledExtensionCount = uint32_t{};
  }
  const char** pCreateInfo_ppEnabledExtensionNames = new const char*[request.vkcreateinstance().pcreateinfo().ppenabledextensionnames_size()]();
  pCreateInfo.ppEnabledExtensionNames = pCreateInfo_ppEnabledExtensionNames;
  for (int ppEnabledExtensionNames_indx = 0; ppEnabledExtensionNames_indx < request.vkcreateinstance().pcreateinfo().ppenabledextensionnames_size(); ppEnabledExtensionNames_indx++) {
    pCreateInfo_ppEnabledExtensionNames[ppEnabledExtensionNames_indx] = request.vkcreateinstance().pcreateinfo().ppenabledextensionnames(ppEnabledExtensionNames_indx).data();
  }
  VkInstance client_pInstance = reinterpret_cast<VkInstance>(request.vkcreateinstance().pinstance());
  VkInstance server_pInstance;
  VkResult result = vkCreateInstance(&pCreateInfo, nullptr, &server_pInstance);
  response->mutable_vkcreateinstance()->set_pinstance(reinterpret_cast<uint64_t>(server_pInstance));
  response->set_result(result);
  delete[] pCreateInfo.ppEnabledLayerNames;
  delete[] pCreateInfo.ppEnabledExtensionNames;
}
void UnpackAndExecuteVkDestroyInstance(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyInstance");

  vkDestroyInstance(reinterpret_cast<VkInstance>(request.vkdestroyinstance().instance()), nullptr);
  response->set_result(VK_SUCCESS);
}
void UnpackAndExecuteVkEnumeratePhysicalDevices(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
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
  VkResult result = vkEnumeratePhysicalDevices(reinterpret_cast<VkInstance>(request.vkenumeratephysicaldevices().instance()), &pPhysicalDeviceCount, pPhysicalDevices);
  response->mutable_vkenumeratephysicaldevices()->set_pphysicaldevicecount(pPhysicalDeviceCount);
  if (request.vkenumeratephysicaldevices().pphysicaldevicecount() != 0) {
    for (int pPhysicalDevices_index = 0; pPhysicalDevices_index < pPhysicalDeviceCount; pPhysicalDevices_index++) {
      response->mutable_vkenumeratephysicaldevices()->add_pphysicaldevices(reinterpret_cast<uint64_t>(pPhysicalDevices[pPhysicalDevices_index]));
    }
  }
  response->set_result(result);
}
void UnpackAndExecuteVkGetPhysicalDeviceProperties(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkGetPhysicalDeviceProperties");

  VkPhysicalDeviceProperties pProperties = {};
  vkGetPhysicalDeviceProperties(context.physical_device(), &pProperties);
  vvk::server::VkPhysicalDeviceProperties* pProperties_proto = response->mutable_vkgetphysicaldeviceproperties()->mutable_pproperties();
  pProperties_proto->set_apiversion((&pProperties)->apiVersion);
  pProperties_proto->set_driverversion((&pProperties)->driverVersion);
  pProperties_proto->set_vendorid((&pProperties)->vendorID);
  pProperties_proto->set_deviceid((&pProperties)->deviceID);
  pProperties_proto->set_devicetype(static_cast<vvk::server::VkPhysicalDeviceType>((&pProperties)->deviceType));
  pProperties_proto->set_devicename((&pProperties)->deviceName);
  const size_t pProperties_proto_pipelineCacheUUID_length = VK_UUID_SIZE;
  for (int pipelineCacheUUID_indx = 0; pipelineCacheUUID_indx < pProperties_proto_pipelineCacheUUID_length; pipelineCacheUUID_indx++) {
    pProperties_proto->add_pipelinecacheuuid(static_cast<uint32_t>((&pProperties)->pipelineCacheUUID[pipelineCacheUUID_indx]));
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
  const size_t pProperties_proto_limits_proto_maxComputeWorkGroupCount_length = 3;
  for (int maxComputeWorkGroupCount_indx = 0; maxComputeWorkGroupCount_indx < pProperties_proto_limits_proto_maxComputeWorkGroupCount_length; maxComputeWorkGroupCount_indx++) {
    pProperties_proto_limits_proto->add_maxcomputeworkgroupcount((&(&pProperties)->limits)->maxComputeWorkGroupCount[maxComputeWorkGroupCount_indx]);
  }
  pProperties_proto_limits_proto->set_maxcomputeworkgroupinvocations((&(&pProperties)->limits)->maxComputeWorkGroupInvocations);
  const size_t pProperties_proto_limits_proto_maxComputeWorkGroupSize_length = 3;
  for (int maxComputeWorkGroupSize_indx = 0; maxComputeWorkGroupSize_indx < pProperties_proto_limits_proto_maxComputeWorkGroupSize_length; maxComputeWorkGroupSize_indx++) {
    pProperties_proto_limits_proto->add_maxcomputeworkgroupsize((&(&pProperties)->limits)->maxComputeWorkGroupSize[maxComputeWorkGroupSize_indx]);
  }
  pProperties_proto_limits_proto->set_subpixelprecisionbits((&(&pProperties)->limits)->subPixelPrecisionBits);
  pProperties_proto_limits_proto->set_subtexelprecisionbits((&(&pProperties)->limits)->subTexelPrecisionBits);
  pProperties_proto_limits_proto->set_mipmapprecisionbits((&(&pProperties)->limits)->mipmapPrecisionBits);
  pProperties_proto_limits_proto->set_maxdrawindexedindexvalue((&(&pProperties)->limits)->maxDrawIndexedIndexValue);
  pProperties_proto_limits_proto->set_maxdrawindirectcount((&(&pProperties)->limits)->maxDrawIndirectCount);
  pProperties_proto_limits_proto->set_maxsamplerlodbias((&(&pProperties)->limits)->maxSamplerLodBias);
  pProperties_proto_limits_proto->set_maxsampleranisotropy((&(&pProperties)->limits)->maxSamplerAnisotropy);
  pProperties_proto_limits_proto->set_maxviewports((&(&pProperties)->limits)->maxViewports);
  const size_t pProperties_proto_limits_proto_maxViewportDimensions_length = 2;
  for (int maxViewportDimensions_indx = 0; maxViewportDimensions_indx < pProperties_proto_limits_proto_maxViewportDimensions_length; maxViewportDimensions_indx++) {
    pProperties_proto_limits_proto->add_maxviewportdimensions((&(&pProperties)->limits)->maxViewportDimensions[maxViewportDimensions_indx]);
  }
  const size_t pProperties_proto_limits_proto_viewportBoundsRange_length = 2;
  for (int viewportBoundsRange_indx = 0; viewportBoundsRange_indx < pProperties_proto_limits_proto_viewportBoundsRange_length; viewportBoundsRange_indx++) {
    pProperties_proto_limits_proto->add_viewportboundsrange((&(&pProperties)->limits)->viewportBoundsRange[viewportBoundsRange_indx]);
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
  if ((&(&pProperties)->limits)->framebufferColorSampleCounts) {
    pProperties_proto_limits_proto->set_framebuffercolorsamplecounts((&(&pProperties)->limits)->framebufferColorSampleCounts);
  }
  if ((&(&pProperties)->limits)->framebufferDepthSampleCounts) {
    pProperties_proto_limits_proto->set_framebufferdepthsamplecounts((&(&pProperties)->limits)->framebufferDepthSampleCounts);
  }
  if ((&(&pProperties)->limits)->framebufferStencilSampleCounts) {
    pProperties_proto_limits_proto->set_framebufferstencilsamplecounts((&(&pProperties)->limits)->framebufferStencilSampleCounts);
  }
  if ((&(&pProperties)->limits)->framebufferNoAttachmentsSampleCounts) {
    pProperties_proto_limits_proto->set_framebuffernoattachmentssamplecounts((&(&pProperties)->limits)->framebufferNoAttachmentsSampleCounts);
  }
  pProperties_proto_limits_proto->set_maxcolorattachments((&(&pProperties)->limits)->maxColorAttachments);
  if ((&(&pProperties)->limits)->sampledImageColorSampleCounts) {
    pProperties_proto_limits_proto->set_sampledimagecolorsamplecounts((&(&pProperties)->limits)->sampledImageColorSampleCounts);
  }
  if ((&(&pProperties)->limits)->sampledImageIntegerSampleCounts) {
    pProperties_proto_limits_proto->set_sampledimageintegersamplecounts((&(&pProperties)->limits)->sampledImageIntegerSampleCounts);
  }
  if ((&(&pProperties)->limits)->sampledImageDepthSampleCounts) {
    pProperties_proto_limits_proto->set_sampledimagedepthsamplecounts((&(&pProperties)->limits)->sampledImageDepthSampleCounts);
  }
  if ((&(&pProperties)->limits)->sampledImageStencilSampleCounts) {
    pProperties_proto_limits_proto->set_sampledimagestencilsamplecounts((&(&pProperties)->limits)->sampledImageStencilSampleCounts);
  }
  if ((&(&pProperties)->limits)->storageImageSampleCounts) {
    pProperties_proto_limits_proto->set_storageimagesamplecounts((&(&pProperties)->limits)->storageImageSampleCounts);
  }
  pProperties_proto_limits_proto->set_maxsamplemaskwords((&(&pProperties)->limits)->maxSampleMaskWords);
  pProperties_proto_limits_proto->set_timestampcomputeandgraphics((&(&pProperties)->limits)->timestampComputeAndGraphics);
  pProperties_proto_limits_proto->set_timestampperiod((&(&pProperties)->limits)->timestampPeriod);
  pProperties_proto_limits_proto->set_maxclipdistances((&(&pProperties)->limits)->maxClipDistances);
  pProperties_proto_limits_proto->set_maxculldistances((&(&pProperties)->limits)->maxCullDistances);
  pProperties_proto_limits_proto->set_maxcombinedclipandculldistances((&(&pProperties)->limits)->maxCombinedClipAndCullDistances);
  pProperties_proto_limits_proto->set_discretequeuepriorities((&(&pProperties)->limits)->discreteQueuePriorities);
  const size_t pProperties_proto_limits_proto_pointSizeRange_length = 2;
  for (int pointSizeRange_indx = 0; pointSizeRange_indx < pProperties_proto_limits_proto_pointSizeRange_length; pointSizeRange_indx++) {
    pProperties_proto_limits_proto->add_pointsizerange((&(&pProperties)->limits)->pointSizeRange[pointSizeRange_indx]);
  }
  const size_t pProperties_proto_limits_proto_lineWidthRange_length = 2;
  for (int lineWidthRange_indx = 0; lineWidthRange_indx < pProperties_proto_limits_proto_lineWidthRange_length; lineWidthRange_indx++) {
    pProperties_proto_limits_proto->add_linewidthrange((&(&pProperties)->limits)->lineWidthRange[lineWidthRange_indx]);
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
void UnpackAndExecuteVkGetPhysicalDeviceFormatProperties(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkGetPhysicalDeviceFormatProperties");

  VkFormatProperties pFormatProperties = {};
  vkGetPhysicalDeviceFormatProperties(context.physical_device(), static_cast<VkFormat>(request.vkgetphysicaldeviceformatproperties().format()), &pFormatProperties);
  vvk::server::VkFormatProperties* pFormatProperties_proto = response->mutable_vkgetphysicaldeviceformatproperties()->mutable_pformatproperties();
  if ((&pFormatProperties)->linearTilingFeatures) {
    pFormatProperties_proto->set_lineartilingfeatures((&pFormatProperties)->linearTilingFeatures);
  }
  if ((&pFormatProperties)->optimalTilingFeatures) {
    pFormatProperties_proto->set_optimaltilingfeatures((&pFormatProperties)->optimalTilingFeatures);
  }
  if ((&pFormatProperties)->bufferFeatures) {
    pFormatProperties_proto->set_bufferfeatures((&pFormatProperties)->bufferFeatures);
  }
  response->set_result(VK_SUCCESS);
}
void UnpackAndExecuteVkCreateDevice(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateDevice");

  VkDeviceCreateInfo pCreateInfo = {};
  pCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  pCreateInfo.pNext = nullptr; // pNext chains are currently unsupported
  if (request.vkcreatedevice().pcreateinfo().has_flags()) {
    pCreateInfo.flags = static_cast<VkDeviceCreateFlags>(request.vkcreatedevice().pcreateinfo().flags());
  } else {
    pCreateInfo.flags = VkDeviceCreateFlags{};
  }
  pCreateInfo.queueCreateInfoCount = request.vkcreatedevice().pcreateinfo().queuecreateinfocount();
  VkDeviceQueueCreateInfo* pCreateInfo_pQueueCreateInfos = new VkDeviceQueueCreateInfo[request.vkcreatedevice().pcreateinfo().pqueuecreateinfos_size()]();
  pCreateInfo.pQueueCreateInfos = pCreateInfo_pQueueCreateInfos;
  for (int pQueueCreateInfos_indx = 0; pQueueCreateInfos_indx < request.vkcreatedevice().pcreateinfo().pqueuecreateinfos_size(); pQueueCreateInfos_indx++) {
    VkDeviceQueueCreateInfo &pCreateInfo_pQueueCreateInfos_i = pCreateInfo_pQueueCreateInfos[pQueueCreateInfos_indx];
    pCreateInfo_pQueueCreateInfos_i.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    pCreateInfo_pQueueCreateInfos_i.pNext = nullptr; // pNext chains are currently unsupported
    if (request.vkcreatedevice().pcreateinfo().pqueuecreateinfos(pQueueCreateInfos_indx).has_flags()) {
      pCreateInfo_pQueueCreateInfos_i.flags = static_cast<VkDeviceQueueCreateFlags>(request.vkcreatedevice().pcreateinfo().pqueuecreateinfos(pQueueCreateInfos_indx).flags());
    } else {
      pCreateInfo_pQueueCreateInfos_i.flags = VkDeviceQueueCreateFlags{};
    }
    pCreateInfo_pQueueCreateInfos_i.queueFamilyIndex = request.vkcreatedevice().pcreateinfo().pqueuecreateinfos(pQueueCreateInfos_indx).queuefamilyindex();
    pCreateInfo_pQueueCreateInfos_i.queueCount = request.vkcreatedevice().pcreateinfo().pqueuecreateinfos(pQueueCreateInfos_indx).queuecount();
    float* pCreateInfo_pQueueCreateInfos_i_pQueuePriorities = new float[request.vkcreatedevice().pcreateinfo().pqueuecreateinfos(pQueueCreateInfos_indx).pqueuepriorities_size()]();
    pCreateInfo_pQueueCreateInfos_i.pQueuePriorities = pCreateInfo_pQueueCreateInfos_i_pQueuePriorities;
    for (int pQueuePriorities_indx = 0; pQueuePriorities_indx < request.vkcreatedevice().pcreateinfo().pqueuecreateinfos(pQueueCreateInfos_indx).pqueuepriorities_size(); pQueuePriorities_indx++) {
      pCreateInfo_pQueueCreateInfos_i_pQueuePriorities[pQueuePriorities_indx] = request.vkcreatedevice().pcreateinfo().pqueuecreateinfos(pQueueCreateInfos_indx).pqueuepriorities(pQueuePriorities_indx);
    }
  }
  if (request.vkcreatedevice().pcreateinfo().has_enabledlayercount()) {
    pCreateInfo.enabledLayerCount = request.vkcreatedevice().pcreateinfo().enabledlayercount();
  } else {
    pCreateInfo.enabledLayerCount = uint32_t{};
  }
  const char** pCreateInfo_ppEnabledLayerNames = new const char*[request.vkcreatedevice().pcreateinfo().ppenabledlayernames_size()]();
  pCreateInfo.ppEnabledLayerNames = pCreateInfo_ppEnabledLayerNames;
  for (int ppEnabledLayerNames_indx = 0; ppEnabledLayerNames_indx < request.vkcreatedevice().pcreateinfo().ppenabledlayernames_size(); ppEnabledLayerNames_indx++) {
    pCreateInfo_ppEnabledLayerNames[ppEnabledLayerNames_indx] = request.vkcreatedevice().pcreateinfo().ppenabledlayernames(ppEnabledLayerNames_indx).data();
  }
  if (request.vkcreatedevice().pcreateinfo().has_enabledextensioncount()) {
    pCreateInfo.enabledExtensionCount = request.vkcreatedevice().pcreateinfo().enabledextensioncount();
  } else {
    pCreateInfo.enabledExtensionCount = uint32_t{};
  }
  const char** pCreateInfo_ppEnabledExtensionNames = new const char*[request.vkcreatedevice().pcreateinfo().ppenabledextensionnames_size()]();
  pCreateInfo.ppEnabledExtensionNames = pCreateInfo_ppEnabledExtensionNames;
  for (int ppEnabledExtensionNames_indx = 0; ppEnabledExtensionNames_indx < request.vkcreatedevice().pcreateinfo().ppenabledextensionnames_size(); ppEnabledExtensionNames_indx++) {
    pCreateInfo_ppEnabledExtensionNames[ppEnabledExtensionNames_indx] = request.vkcreatedevice().pcreateinfo().ppenabledextensionnames(ppEnabledExtensionNames_indx).data();
  }
  VkPhysicalDeviceFeatures pCreateInfo_pEnabledFeatures = {};
  if (request.vkcreatedevice().pcreateinfo().has_penabledfeatures()) {
    pCreateInfo_pEnabledFeatures.robustBufferAccess = request.vkcreatedevice().pcreateinfo().penabledfeatures().robustbufferaccess();
    pCreateInfo_pEnabledFeatures.fullDrawIndexUint32 = request.vkcreatedevice().pcreateinfo().penabledfeatures().fulldrawindexuint32();
    pCreateInfo_pEnabledFeatures.imageCubeArray = request.vkcreatedevice().pcreateinfo().penabledfeatures().imagecubearray();
    pCreateInfo_pEnabledFeatures.independentBlend = request.vkcreatedevice().pcreateinfo().penabledfeatures().independentblend();
    pCreateInfo_pEnabledFeatures.geometryShader = request.vkcreatedevice().pcreateinfo().penabledfeatures().geometryshader();
    pCreateInfo_pEnabledFeatures.tessellationShader = request.vkcreatedevice().pcreateinfo().penabledfeatures().tessellationshader();
    pCreateInfo_pEnabledFeatures.sampleRateShading = request.vkcreatedevice().pcreateinfo().penabledfeatures().samplerateshading();
    pCreateInfo_pEnabledFeatures.dualSrcBlend = request.vkcreatedevice().pcreateinfo().penabledfeatures().dualsrcblend();
    pCreateInfo_pEnabledFeatures.logicOp = request.vkcreatedevice().pcreateinfo().penabledfeatures().logicop();
    pCreateInfo_pEnabledFeatures.multiDrawIndirect = request.vkcreatedevice().pcreateinfo().penabledfeatures().multidrawindirect();
    pCreateInfo_pEnabledFeatures.drawIndirectFirstInstance = request.vkcreatedevice().pcreateinfo().penabledfeatures().drawindirectfirstinstance();
    pCreateInfo_pEnabledFeatures.depthClamp = request.vkcreatedevice().pcreateinfo().penabledfeatures().depthclamp();
    pCreateInfo_pEnabledFeatures.depthBiasClamp = request.vkcreatedevice().pcreateinfo().penabledfeatures().depthbiasclamp();
    pCreateInfo_pEnabledFeatures.fillModeNonSolid = request.vkcreatedevice().pcreateinfo().penabledfeatures().fillmodenonsolid();
    pCreateInfo_pEnabledFeatures.depthBounds = request.vkcreatedevice().pcreateinfo().penabledfeatures().depthbounds();
    pCreateInfo_pEnabledFeatures.wideLines = request.vkcreatedevice().pcreateinfo().penabledfeatures().widelines();
    pCreateInfo_pEnabledFeatures.largePoints = request.vkcreatedevice().pcreateinfo().penabledfeatures().largepoints();
    pCreateInfo_pEnabledFeatures.alphaToOne = request.vkcreatedevice().pcreateinfo().penabledfeatures().alphatoone();
    pCreateInfo_pEnabledFeatures.multiViewport = request.vkcreatedevice().pcreateinfo().penabledfeatures().multiviewport();
    pCreateInfo_pEnabledFeatures.samplerAnisotropy = request.vkcreatedevice().pcreateinfo().penabledfeatures().sampleranisotropy();
    pCreateInfo_pEnabledFeatures.textureCompressionETC2 = request.vkcreatedevice().pcreateinfo().penabledfeatures().texturecompressionetc2();
    pCreateInfo_pEnabledFeatures.textureCompressionASTC_LDR = request.vkcreatedevice().pcreateinfo().penabledfeatures().texturecompressionastc_ldr();
    pCreateInfo_pEnabledFeatures.textureCompressionBC = request.vkcreatedevice().pcreateinfo().penabledfeatures().texturecompressionbc();
    pCreateInfo_pEnabledFeatures.occlusionQueryPrecise = request.vkcreatedevice().pcreateinfo().penabledfeatures().occlusionqueryprecise();
    pCreateInfo_pEnabledFeatures.pipelineStatisticsQuery = request.vkcreatedevice().pcreateinfo().penabledfeatures().pipelinestatisticsquery();
    pCreateInfo_pEnabledFeatures.vertexPipelineStoresAndAtomics = request.vkcreatedevice().pcreateinfo().penabledfeatures().vertexpipelinestoresandatomics();
    pCreateInfo_pEnabledFeatures.fragmentStoresAndAtomics = request.vkcreatedevice().pcreateinfo().penabledfeatures().fragmentstoresandatomics();
    pCreateInfo_pEnabledFeatures.shaderTessellationAndGeometryPointSize = request.vkcreatedevice().pcreateinfo().penabledfeatures().shadertessellationandgeometrypointsize();
    pCreateInfo_pEnabledFeatures.shaderImageGatherExtended = request.vkcreatedevice().pcreateinfo().penabledfeatures().shaderimagegatherextended();
    pCreateInfo_pEnabledFeatures.shaderStorageImageExtendedFormats = request.vkcreatedevice().pcreateinfo().penabledfeatures().shaderstorageimageextendedformats();
    pCreateInfo_pEnabledFeatures.shaderStorageImageMultisample = request.vkcreatedevice().pcreateinfo().penabledfeatures().shaderstorageimagemultisample();
    pCreateInfo_pEnabledFeatures.shaderStorageImageReadWithoutFormat = request.vkcreatedevice().pcreateinfo().penabledfeatures().shaderstorageimagereadwithoutformat();
    pCreateInfo_pEnabledFeatures.shaderStorageImageWriteWithoutFormat = request.vkcreatedevice().pcreateinfo().penabledfeatures().shaderstorageimagewritewithoutformat();
    pCreateInfo_pEnabledFeatures.shaderUniformBufferArrayDynamicIndexing = request.vkcreatedevice().pcreateinfo().penabledfeatures().shaderuniformbufferarraydynamicindexing();
    pCreateInfo_pEnabledFeatures.shaderSampledImageArrayDynamicIndexing = request.vkcreatedevice().pcreateinfo().penabledfeatures().shadersampledimagearraydynamicindexing();
    pCreateInfo_pEnabledFeatures.shaderStorageBufferArrayDynamicIndexing = request.vkcreatedevice().pcreateinfo().penabledfeatures().shaderstoragebufferarraydynamicindexing();
    pCreateInfo_pEnabledFeatures.shaderStorageImageArrayDynamicIndexing = request.vkcreatedevice().pcreateinfo().penabledfeatures().shaderstorageimagearraydynamicindexing();
    pCreateInfo_pEnabledFeatures.shaderClipDistance = request.vkcreatedevice().pcreateinfo().penabledfeatures().shaderclipdistance();
    pCreateInfo_pEnabledFeatures.shaderCullDistance = request.vkcreatedevice().pcreateinfo().penabledfeatures().shaderculldistance();
    pCreateInfo_pEnabledFeatures.shaderFloat64 = request.vkcreatedevice().pcreateinfo().penabledfeatures().shaderfloat64();
    pCreateInfo_pEnabledFeatures.shaderInt64 = request.vkcreatedevice().pcreateinfo().penabledfeatures().shaderint64();
    pCreateInfo_pEnabledFeatures.shaderInt16 = request.vkcreatedevice().pcreateinfo().penabledfeatures().shaderint16();
    pCreateInfo_pEnabledFeatures.shaderResourceResidency = request.vkcreatedevice().pcreateinfo().penabledfeatures().shaderresourceresidency();
    pCreateInfo_pEnabledFeatures.shaderResourceMinLod = request.vkcreatedevice().pcreateinfo().penabledfeatures().shaderresourceminlod();
    pCreateInfo_pEnabledFeatures.sparseBinding = request.vkcreatedevice().pcreateinfo().penabledfeatures().sparsebinding();
    pCreateInfo_pEnabledFeatures.sparseResidencyBuffer = request.vkcreatedevice().pcreateinfo().penabledfeatures().sparseresidencybuffer();
    pCreateInfo_pEnabledFeatures.sparseResidencyImage2D = request.vkcreatedevice().pcreateinfo().penabledfeatures().sparseresidencyimage2d();
    pCreateInfo_pEnabledFeatures.sparseResidencyImage3D = request.vkcreatedevice().pcreateinfo().penabledfeatures().sparseresidencyimage3d();
    pCreateInfo_pEnabledFeatures.sparseResidency2Samples = request.vkcreatedevice().pcreateinfo().penabledfeatures().sparseresidency2samples();
    pCreateInfo_pEnabledFeatures.sparseResidency4Samples = request.vkcreatedevice().pcreateinfo().penabledfeatures().sparseresidency4samples();
    pCreateInfo_pEnabledFeatures.sparseResidency8Samples = request.vkcreatedevice().pcreateinfo().penabledfeatures().sparseresidency8samples();
    pCreateInfo_pEnabledFeatures.sparseResidency16Samples = request.vkcreatedevice().pcreateinfo().penabledfeatures().sparseresidency16samples();
    pCreateInfo_pEnabledFeatures.sparseResidencyAliased = request.vkcreatedevice().pcreateinfo().penabledfeatures().sparseresidencyaliased();
    pCreateInfo_pEnabledFeatures.variableMultisampleRate = request.vkcreatedevice().pcreateinfo().penabledfeatures().variablemultisamplerate();
    pCreateInfo_pEnabledFeatures.inheritedQueries = request.vkcreatedevice().pcreateinfo().penabledfeatures().inheritedqueries();
    pCreateInfo.pEnabledFeatures = &pCreateInfo_pEnabledFeatures;
  } else {
    pCreateInfo.pEnabledFeatures = nullptr;
  }
  VkDevice client_pDevice = reinterpret_cast<VkDevice>(request.vkcreatedevice().pdevice());
  VkDevice server_pDevice;
  VkResult result = vkCreateDevice(context.physical_device(), &pCreateInfo, nullptr, &server_pDevice);
  response->mutable_vkcreatedevice()->set_pdevice(reinterpret_cast<uint64_t>(server_pDevice));
  response->set_result(result);
  for (int pQueueCreateInfos_indx = 0; pQueueCreateInfos_indx < request.vkcreatedevice().pcreateinfo().pqueuecreateinfos_size(); pQueueCreateInfos_indx++)  {
    const VkDeviceQueueCreateInfo &pCreateInfo_pQueueCreateInfos_i = pCreateInfo.pQueueCreateInfos[pQueueCreateInfos_indx];
    delete[] pCreateInfo_pQueueCreateInfos_i.pQueuePriorities;
  }
  delete[] pCreateInfo.pQueueCreateInfos;
  delete[] pCreateInfo.ppEnabledLayerNames;
  delete[] pCreateInfo.ppEnabledExtensionNames;
}
void UnpackAndExecuteVkDestroyDevice(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyDevice");

  vkDestroyDevice(reinterpret_cast<VkDevice>(request.vkdestroydevice().device()), nullptr);
  response->set_result(VK_SUCCESS);
}
void UnpackAndExecuteVkEnumerateInstanceExtensionProperties(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkEnumerateInstanceExtensionProperties");

  uint32_t pPropertyCount = request.vkenumerateinstanceextensionproperties().ppropertycount();
  std::vector<VkExtensionProperties> aux_pProperties;
  VkExtensionProperties* pProperties;
  if (pPropertyCount == 0) {
    pProperties = nullptr;
  } else {
    aux_pProperties.resize(pPropertyCount);
    pProperties = aux_pProperties.data();
  }
  VkResult result = vkEnumerateInstanceExtensionProperties(request.vkenumerateinstanceextensionproperties().playername().data(), &pPropertyCount, pProperties);
  response->mutable_vkenumerateinstanceextensionproperties()->set_ppropertycount(pPropertyCount);
  if (request.vkenumerateinstanceextensionproperties().ppropertycount() != 0) {
    for (int pProperties_index = 0; pProperties_index < pPropertyCount; pProperties_index++) {
      vvk::server::VkExtensionProperties* pProperties_proto = response->mutable_vkenumerateinstanceextensionproperties()->add_pproperties();
      pProperties_proto->set_extensionname((&pProperties[pProperties_index])->extensionName);
      pProperties_proto->set_specversion((&pProperties[pProperties_index])->specVersion);
    }
  }
  response->set_result(result);
}
void UnpackAndExecuteVkEnumerateDeviceExtensionProperties(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkEnumerateDeviceExtensionProperties");

  uint32_t pPropertyCount = request.vkenumeratedeviceextensionproperties().ppropertycount();
  std::vector<VkExtensionProperties> aux_pProperties;
  VkExtensionProperties* pProperties;
  if (pPropertyCount == 0) {
    pProperties = nullptr;
  } else {
    aux_pProperties.resize(pPropertyCount);
    pProperties = aux_pProperties.data();
  }
  VkResult result = vkEnumerateDeviceExtensionProperties(context.physical_device(), request.vkenumeratedeviceextensionproperties().playername().data(), &pPropertyCount, pProperties);
  response->mutable_vkenumeratedeviceextensionproperties()->set_ppropertycount(pPropertyCount);
  if (request.vkenumeratedeviceextensionproperties().ppropertycount() != 0) {
    for (int pProperties_index = 0; pProperties_index < pPropertyCount; pProperties_index++) {
      vvk::server::VkExtensionProperties* pProperties_proto = response->mutable_vkenumeratedeviceextensionproperties()->add_pproperties();
      pProperties_proto->set_extensionname((&pProperties[pProperties_index])->extensionName);
      pProperties_proto->set_specversion((&pProperties[pProperties_index])->specVersion);
    }
  }
  response->set_result(result);
}
void UnpackAndExecuteVkGetPhysicalDeviceMemoryProperties(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkGetPhysicalDeviceMemoryProperties");

  VkPhysicalDeviceMemoryProperties pMemoryProperties = {};
  vkGetPhysicalDeviceMemoryProperties(context.physical_device(), &pMemoryProperties);
  vvk::server::VkPhysicalDeviceMemoryProperties* pMemoryProperties_proto = response->mutable_vkgetphysicaldevicememoryproperties()->mutable_pmemoryproperties();
  pMemoryProperties_proto->set_memorytypecount((&pMemoryProperties)->memoryTypeCount);
  const size_t pMemoryProperties_proto_memoryTypes_length = (&pMemoryProperties)->memoryTypeCount;
  for (int memoryTypes_indx = 0; memoryTypes_indx < pMemoryProperties_proto_memoryTypes_length; memoryTypes_indx++) {
    vvk::server::VkMemoryType* pMemoryProperties_proto_memoryTypes_proto = pMemoryProperties_proto->add_memorytypes();
    if ((&(&pMemoryProperties)->memoryTypes[memoryTypes_indx])->propertyFlags) {
      pMemoryProperties_proto_memoryTypes_proto->set_propertyflags((&(&pMemoryProperties)->memoryTypes[memoryTypes_indx])->propertyFlags);
    }
    pMemoryProperties_proto_memoryTypes_proto->set_heapindex((&(&pMemoryProperties)->memoryTypes[memoryTypes_indx])->heapIndex);
  }
  pMemoryProperties_proto->set_memoryheapcount((&pMemoryProperties)->memoryHeapCount);
  const size_t pMemoryProperties_proto_memoryHeaps_length = (&pMemoryProperties)->memoryHeapCount;
  for (int memoryHeaps_indx = 0; memoryHeaps_indx < pMemoryProperties_proto_memoryHeaps_length; memoryHeaps_indx++) {
    vvk::server::VkMemoryHeap* pMemoryProperties_proto_memoryHeaps_proto = pMemoryProperties_proto->add_memoryheaps();
    pMemoryProperties_proto_memoryHeaps_proto->set_size(static_cast<uint64_t>((&(&pMemoryProperties)->memoryHeaps[memoryHeaps_indx])->size));
    if ((&(&pMemoryProperties)->memoryHeaps[memoryHeaps_indx])->flags) {
      pMemoryProperties_proto_memoryHeaps_proto->set_flags((&(&pMemoryProperties)->memoryHeaps[memoryHeaps_indx])->flags);
    }
  }
  response->set_result(VK_SUCCESS);
}
void UnpackAndExecuteVkGetPhysicalDeviceFeatures(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkGetPhysicalDeviceFeatures");

  VkPhysicalDeviceFeatures pFeatures = {};
  vkGetPhysicalDeviceFeatures(context.physical_device(), &pFeatures);
  vvk::server::VkPhysicalDeviceFeatures* pFeatures_proto = response->mutable_vkgetphysicaldevicefeatures()->mutable_pfeatures();
  pFeatures_proto->set_robustbufferaccess((&pFeatures)->robustBufferAccess);
  pFeatures_proto->set_fulldrawindexuint32((&pFeatures)->fullDrawIndexUint32);
  pFeatures_proto->set_imagecubearray((&pFeatures)->imageCubeArray);
  pFeatures_proto->set_independentblend((&pFeatures)->independentBlend);
  pFeatures_proto->set_geometryshader((&pFeatures)->geometryShader);
  pFeatures_proto->set_tessellationshader((&pFeatures)->tessellationShader);
  pFeatures_proto->set_samplerateshading((&pFeatures)->sampleRateShading);
  pFeatures_proto->set_dualsrcblend((&pFeatures)->dualSrcBlend);
  pFeatures_proto->set_logicop((&pFeatures)->logicOp);
  pFeatures_proto->set_multidrawindirect((&pFeatures)->multiDrawIndirect);
  pFeatures_proto->set_drawindirectfirstinstance((&pFeatures)->drawIndirectFirstInstance);
  pFeatures_proto->set_depthclamp((&pFeatures)->depthClamp);
  pFeatures_proto->set_depthbiasclamp((&pFeatures)->depthBiasClamp);
  pFeatures_proto->set_fillmodenonsolid((&pFeatures)->fillModeNonSolid);
  pFeatures_proto->set_depthbounds((&pFeatures)->depthBounds);
  pFeatures_proto->set_widelines((&pFeatures)->wideLines);
  pFeatures_proto->set_largepoints((&pFeatures)->largePoints);
  pFeatures_proto->set_alphatoone((&pFeatures)->alphaToOne);
  pFeatures_proto->set_multiviewport((&pFeatures)->multiViewport);
  pFeatures_proto->set_sampleranisotropy((&pFeatures)->samplerAnisotropy);
  pFeatures_proto->set_texturecompressionetc2((&pFeatures)->textureCompressionETC2);
  pFeatures_proto->set_texturecompressionastc_ldr((&pFeatures)->textureCompressionASTC_LDR);
  pFeatures_proto->set_texturecompressionbc((&pFeatures)->textureCompressionBC);
  pFeatures_proto->set_occlusionqueryprecise((&pFeatures)->occlusionQueryPrecise);
  pFeatures_proto->set_pipelinestatisticsquery((&pFeatures)->pipelineStatisticsQuery);
  pFeatures_proto->set_vertexpipelinestoresandatomics((&pFeatures)->vertexPipelineStoresAndAtomics);
  pFeatures_proto->set_fragmentstoresandatomics((&pFeatures)->fragmentStoresAndAtomics);
  pFeatures_proto->set_shadertessellationandgeometrypointsize((&pFeatures)->shaderTessellationAndGeometryPointSize);
  pFeatures_proto->set_shaderimagegatherextended((&pFeatures)->shaderImageGatherExtended);
  pFeatures_proto->set_shaderstorageimageextendedformats((&pFeatures)->shaderStorageImageExtendedFormats);
  pFeatures_proto->set_shaderstorageimagemultisample((&pFeatures)->shaderStorageImageMultisample);
  pFeatures_proto->set_shaderstorageimagereadwithoutformat((&pFeatures)->shaderStorageImageReadWithoutFormat);
  pFeatures_proto->set_shaderstorageimagewritewithoutformat((&pFeatures)->shaderStorageImageWriteWithoutFormat);
  pFeatures_proto->set_shaderuniformbufferarraydynamicindexing((&pFeatures)->shaderUniformBufferArrayDynamicIndexing);
  pFeatures_proto->set_shadersampledimagearraydynamicindexing((&pFeatures)->shaderSampledImageArrayDynamicIndexing);
  pFeatures_proto->set_shaderstoragebufferarraydynamicindexing((&pFeatures)->shaderStorageBufferArrayDynamicIndexing);
  pFeatures_proto->set_shaderstorageimagearraydynamicindexing((&pFeatures)->shaderStorageImageArrayDynamicIndexing);
  pFeatures_proto->set_shaderclipdistance((&pFeatures)->shaderClipDistance);
  pFeatures_proto->set_shaderculldistance((&pFeatures)->shaderCullDistance);
  pFeatures_proto->set_shaderfloat64((&pFeatures)->shaderFloat64);
  pFeatures_proto->set_shaderint64((&pFeatures)->shaderInt64);
  pFeatures_proto->set_shaderint16((&pFeatures)->shaderInt16);
  pFeatures_proto->set_shaderresourceresidency((&pFeatures)->shaderResourceResidency);
  pFeatures_proto->set_shaderresourceminlod((&pFeatures)->shaderResourceMinLod);
  pFeatures_proto->set_sparsebinding((&pFeatures)->sparseBinding);
  pFeatures_proto->set_sparseresidencybuffer((&pFeatures)->sparseResidencyBuffer);
  pFeatures_proto->set_sparseresidencyimage2d((&pFeatures)->sparseResidencyImage2D);
  pFeatures_proto->set_sparseresidencyimage3d((&pFeatures)->sparseResidencyImage3D);
  pFeatures_proto->set_sparseresidency2samples((&pFeatures)->sparseResidency2Samples);
  pFeatures_proto->set_sparseresidency4samples((&pFeatures)->sparseResidency4Samples);
  pFeatures_proto->set_sparseresidency8samples((&pFeatures)->sparseResidency8Samples);
  pFeatures_proto->set_sparseresidency16samples((&pFeatures)->sparseResidency16Samples);
  pFeatures_proto->set_sparseresidencyaliased((&pFeatures)->sparseResidencyAliased);
  pFeatures_proto->set_variablemultisamplerate((&pFeatures)->variableMultisampleRate);
  pFeatures_proto->set_inheritedqueries((&pFeatures)->inheritedQueries);
  response->set_result(VK_SUCCESS);
}
void UnpackAndExecuteVkGetPhysicalDeviceQueueFamilyProperties(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkGetPhysicalDeviceQueueFamilyProperties");

  uint32_t pQueueFamilyPropertyCount = request.vkgetphysicaldevicequeuefamilyproperties().pqueuefamilypropertycount();
  std::vector<VkQueueFamilyProperties> aux_pQueueFamilyProperties;
  VkQueueFamilyProperties* pQueueFamilyProperties;
  if (pQueueFamilyPropertyCount == 0) {
    pQueueFamilyProperties = nullptr;
  } else {
    aux_pQueueFamilyProperties.resize(pQueueFamilyPropertyCount);
    pQueueFamilyProperties = aux_pQueueFamilyProperties.data();
  }
  vkGetPhysicalDeviceQueueFamilyProperties(context.physical_device(), &pQueueFamilyPropertyCount, pQueueFamilyProperties);
  response->mutable_vkgetphysicaldevicequeuefamilyproperties()->set_pqueuefamilypropertycount(pQueueFamilyPropertyCount);
  if (request.vkgetphysicaldevicequeuefamilyproperties().pqueuefamilypropertycount() != 0) {
    for (int pQueueFamilyProperties_index = 0; pQueueFamilyProperties_index < pQueueFamilyPropertyCount; pQueueFamilyProperties_index++) {
      vvk::server::VkQueueFamilyProperties* pQueueFamilyProperties_proto = response->mutable_vkgetphysicaldevicequeuefamilyproperties()->add_pqueuefamilyproperties();
      if ((&pQueueFamilyProperties[pQueueFamilyProperties_index])->queueFlags) {
        pQueueFamilyProperties_proto->set_queueflags((&pQueueFamilyProperties[pQueueFamilyProperties_index])->queueFlags);
      }
      pQueueFamilyProperties_proto->set_queuecount((&pQueueFamilyProperties[pQueueFamilyProperties_index])->queueCount);
      pQueueFamilyProperties_proto->set_timestampvalidbits((&pQueueFamilyProperties[pQueueFamilyProperties_index])->timestampValidBits);
      vvk::server::VkExtent3D* pQueueFamilyProperties_proto_minImageTransferGranularity_proto = pQueueFamilyProperties_proto->mutable_minimagetransfergranularity();
      pQueueFamilyProperties_proto_minImageTransferGranularity_proto->set_width((&(&pQueueFamilyProperties[pQueueFamilyProperties_index])->minImageTransferGranularity)->width);
      pQueueFamilyProperties_proto_minImageTransferGranularity_proto->set_height((&(&pQueueFamilyProperties[pQueueFamilyProperties_index])->minImageTransferGranularity)->height);
      pQueueFamilyProperties_proto_minImageTransferGranularity_proto->set_depth((&(&pQueueFamilyProperties[pQueueFamilyProperties_index])->minImageTransferGranularity)->depth);
    }
  }
  response->set_result(VK_SUCCESS);
}
void UnpackAndExecuteVkGetDeviceQueue(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkGetDeviceQueue");

  VkQueue client_pQueue = reinterpret_cast<VkQueue>(request.vkgetdevicequeue().pqueue());
  VkQueue server_pQueue;
  vkGetDeviceQueue(reinterpret_cast<VkDevice>(request.vkgetdevicequeue().device()), request.vkgetdevicequeue().queuefamilyindex(), request.vkgetdevicequeue().queueindex(), &server_pQueue);
  response->mutable_vkgetdevicequeue()->set_pqueue(reinterpret_cast<uint64_t>(server_pQueue));
  response->set_result(VK_SUCCESS);
}
void UnpackAndExecuteVkCreateFence(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateFence");

  VkFenceCreateInfo pCreateInfo = {};
  pCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  pCreateInfo.pNext = nullptr; // pNext chains are currently unsupported
  if (request.vkcreatefence().pcreateinfo().has_flags()) {
    pCreateInfo.flags = static_cast<VkFenceCreateFlags>(request.vkcreatefence().pcreateinfo().flags());
  } else {
    pCreateInfo.flags = VkFenceCreateFlags{};
  }
  VkFence client_pFence = reinterpret_cast<VkFence>(request.vkcreatefence().pfence());
  VkFence server_pFence;
  VkResult result = vkCreateFence(reinterpret_cast<VkDevice>(request.vkcreatefence().device()), &pCreateInfo, nullptr, &server_pFence);
  response->mutable_vkcreatefence()->set_pfence(reinterpret_cast<uint64_t>(server_pFence));
  response->set_result(result);
}
void UnpackAndExecuteVkDestroyFence(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyFence");

  vkDestroyFence(reinterpret_cast<VkDevice>(request.vkdestroyfence().device()), reinterpret_cast<VkFence>(request.vkdestroyfence().fence()), nullptr);
  response->set_result(VK_SUCCESS);
}
void UnpackAndExecuteVkCreateSemaphore(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateSemaphore");

  VkSemaphoreCreateInfo pCreateInfo = {};
  pCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
  pCreateInfo.pNext = nullptr; // pNext chains are currently unsupported
  if (request.vkcreatesemaphore().pcreateinfo().has_flags()) {
    pCreateInfo.flags = static_cast<VkSemaphoreCreateFlags>(request.vkcreatesemaphore().pcreateinfo().flags());
  } else {
    pCreateInfo.flags = VkSemaphoreCreateFlags{};
  }
  VkSemaphore client_pSemaphore = reinterpret_cast<VkSemaphore>(request.vkcreatesemaphore().psemaphore());
  VkSemaphore server_pSemaphore;
  VkResult result = vkCreateSemaphore(reinterpret_cast<VkDevice>(request.vkcreatesemaphore().device()), &pCreateInfo, nullptr, &server_pSemaphore);
  response->mutable_vkcreatesemaphore()->set_psemaphore(reinterpret_cast<uint64_t>(server_pSemaphore));
  response->set_result(result);
}
void UnpackAndExecuteVkDestroySemaphore(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroySemaphore");

  vkDestroySemaphore(reinterpret_cast<VkDevice>(request.vkdestroysemaphore().device()), reinterpret_cast<VkSemaphore>(request.vkdestroysemaphore().semaphore()), nullptr);
  response->set_result(VK_SUCCESS);
}
void UnpackAndExecuteVkAllocateMemory(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkAllocateMemory");

  VkMemoryAllocateInfo pAllocateInfo = {};
  pAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  pAllocateInfo.pNext = nullptr; // pNext chains are currently unsupported
  pAllocateInfo.allocationSize = static_cast<VkDeviceSize>(request.vkallocatememory().pallocateinfo().allocationsize());
  pAllocateInfo.memoryTypeIndex = request.vkallocatememory().pallocateinfo().memorytypeindex();
  VkDeviceMemory client_pMemory = reinterpret_cast<VkDeviceMemory>(request.vkallocatememory().pmemory());
  VkDeviceMemory server_pMemory;
  VkResult result = vkAllocateMemory(reinterpret_cast<VkDevice>(request.vkallocatememory().device()), &pAllocateInfo, nullptr, &server_pMemory);
  response->mutable_vkallocatememory()->set_pmemory(reinterpret_cast<uint64_t>(server_pMemory));
  response->set_result(result);
}
void UnpackAndExecuteVkFreeMemory(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkFreeMemory");

  vkFreeMemory(reinterpret_cast<VkDevice>(request.vkfreememory().device()), reinterpret_cast<VkDeviceMemory>(request.vkfreememory().memory()), nullptr);
  response->set_result(VK_SUCCESS);
}
void UnpackAndExecuteVkCreateImage(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateImage");

  VkImageCreateInfo pCreateInfo = {};
  pCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  pCreateInfo.pNext = nullptr; // pNext chains are currently unsupported
  if (request.vkcreateimage().pcreateinfo().has_flags()) {
    pCreateInfo.flags = static_cast<VkImageCreateFlags>(request.vkcreateimage().pcreateinfo().flags());
  } else {
    pCreateInfo.flags = VkImageCreateFlags{};
  }
  pCreateInfo.imageType = static_cast<VkImageType>(request.vkcreateimage().pcreateinfo().imagetype());
  pCreateInfo.format = static_cast<VkFormat>(request.vkcreateimage().pcreateinfo().format());
  VkExtent3D &pCreateInfo_extent = pCreateInfo.extent;
  pCreateInfo_extent.width = request.vkcreateimage().pcreateinfo().extent().width();
  pCreateInfo_extent.height = request.vkcreateimage().pcreateinfo().extent().height();
  pCreateInfo_extent.depth = request.vkcreateimage().pcreateinfo().extent().depth();
  pCreateInfo.mipLevels = request.vkcreateimage().pcreateinfo().miplevels();
  pCreateInfo.arrayLayers = request.vkcreateimage().pcreateinfo().arraylayers();
  pCreateInfo.samples = static_cast<VkSampleCountFlagBits>(request.vkcreateimage().pcreateinfo().samples());
  pCreateInfo.tiling = static_cast<VkImageTiling>(request.vkcreateimage().pcreateinfo().tiling());
  pCreateInfo.usage = static_cast<VkImageUsageFlags>(request.vkcreateimage().pcreateinfo().usage());
  pCreateInfo.sharingMode = static_cast<VkSharingMode>(request.vkcreateimage().pcreateinfo().sharingmode());
  if (request.vkcreateimage().pcreateinfo().has_queuefamilyindexcount()) {
    pCreateInfo.queueFamilyIndexCount = request.vkcreateimage().pcreateinfo().queuefamilyindexcount();
  } else {
    pCreateInfo.queueFamilyIndexCount = uint32_t{};
  }
  uint32_t* pCreateInfo_pQueueFamilyIndices = new uint32_t[request.vkcreateimage().pcreateinfo().pqueuefamilyindices_size()]();
  pCreateInfo.pQueueFamilyIndices = pCreateInfo_pQueueFamilyIndices;
  for (int pQueueFamilyIndices_indx = 0; pQueueFamilyIndices_indx < request.vkcreateimage().pcreateinfo().pqueuefamilyindices_size(); pQueueFamilyIndices_indx++) {
    pCreateInfo_pQueueFamilyIndices[pQueueFamilyIndices_indx] = request.vkcreateimage().pcreateinfo().pqueuefamilyindices(pQueueFamilyIndices_indx);
  }
  pCreateInfo.initialLayout = static_cast<VkImageLayout>(request.vkcreateimage().pcreateinfo().initiallayout());
  VkImage client_pImage = reinterpret_cast<VkImage>(request.vkcreateimage().pimage());
  VkImage server_pImage;
  VkResult result = vkCreateImage(reinterpret_cast<VkDevice>(request.vkcreateimage().device()), &pCreateInfo, nullptr, &server_pImage);
  response->mutable_vkcreateimage()->set_pimage(reinterpret_cast<uint64_t>(server_pImage));
  response->set_result(result);
  delete[] pCreateInfo.pQueueFamilyIndices;
}
void UnpackAndExecuteVkDestroyImage(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyImage");

  vkDestroyImage(reinterpret_cast<VkDevice>(request.vkdestroyimage().device()), reinterpret_cast<VkImage>(request.vkdestroyimage().image()), nullptr);
  response->set_result(VK_SUCCESS);
}
void UnpackAndExecuteVkBindImageMemory(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkBindImageMemory");

  VkResult result = vkBindImageMemory(reinterpret_cast<VkDevice>(request.vkbindimagememory().device()), reinterpret_cast<VkImage>(request.vkbindimagememory().image()), reinterpret_cast<VkDeviceMemory>(request.vkbindimagememory().memory()), static_cast<VkDeviceSize>(request.vkbindimagememory().memoryoffset()));
  response->set_result(result);
}
void UnpackAndExecuteVkBindImageMemory2(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkBindImageMemory2");

  std::vector<VkBindImageMemoryInfo> pBindInfos(request.vkbindimagememory2().bindinfocount());
  for (int i = 0; i < pBindInfos.size(); i++) {
    VkBindImageMemoryInfo& pBindInfos_ref = pBindInfos[i];
    pBindInfos_ref.sType = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO;
    pBindInfos_ref.pNext = nullptr; // pNext chains are currently unsupported
    pBindInfos_ref.image = reinterpret_cast<VkImage>(request.vkbindimagememory2().pbindinfos(i).image());
    pBindInfos_ref.memory = reinterpret_cast<VkDeviceMemory>(request.vkbindimagememory2().pbindinfos(i).memory());
    pBindInfos_ref.memoryOffset = static_cast<VkDeviceSize>(request.vkbindimagememory2().pbindinfos(i).memoryoffset());
  }
  VkResult result = vkBindImageMemory2(reinterpret_cast<VkDevice>(request.vkbindimagememory2().device()), request.vkbindimagememory2().bindinfocount(), pBindInfos.data());
  response->set_result(result);
}
void UnpackAndExecuteVkGetImageMemoryRequirements(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkGetImageMemoryRequirements");

  VkMemoryRequirements pMemoryRequirements = {};
  vkGetImageMemoryRequirements(reinterpret_cast<VkDevice>(request.vkgetimagememoryrequirements().device()), reinterpret_cast<VkImage>(request.vkgetimagememoryrequirements().image()), &pMemoryRequirements);
  vvk::server::VkMemoryRequirements* pMemoryRequirements_proto = response->mutable_vkgetimagememoryrequirements()->mutable_pmemoryrequirements();
  pMemoryRequirements_proto->set_size(static_cast<uint64_t>((&pMemoryRequirements)->size));
  pMemoryRequirements_proto->set_alignment(static_cast<uint64_t>((&pMemoryRequirements)->alignment));
  pMemoryRequirements_proto->set_memorytypebits((&pMemoryRequirements)->memoryTypeBits);
  response->set_result(VK_SUCCESS);
}
void UnpackAndExecuteVkGetImageMemoryRequirements2(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkGetImageMemoryRequirements2");

  VkImageMemoryRequirementsInfo2 pInfo = {};
  pInfo.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2;
  pInfo.pNext = nullptr; // pNext chains are currently unsupported
  pInfo.image = reinterpret_cast<VkImage>(request.vkgetimagememoryrequirements2().pinfo().image());
  VkMemoryRequirements2 pMemoryRequirements = {};
  pMemoryRequirements.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
  vkGetImageMemoryRequirements2(reinterpret_cast<VkDevice>(request.vkgetimagememoryrequirements2().device()), &pInfo, &pMemoryRequirements);
  vvk::server::VkMemoryRequirements2* pMemoryRequirements_proto = response->mutable_vkgetimagememoryrequirements2()->mutable_pmemoryrequirements();
  if ((&pMemoryRequirements)->pNext) {
    // pNext chains are currently not supported
  }
  vvk::server::VkMemoryRequirements* pMemoryRequirements_proto_memoryRequirements_proto = pMemoryRequirements_proto->mutable_memoryrequirements();
  pMemoryRequirements_proto_memoryRequirements_proto->set_size(static_cast<uint64_t>((&(&pMemoryRequirements)->memoryRequirements)->size));
  pMemoryRequirements_proto_memoryRequirements_proto->set_alignment(static_cast<uint64_t>((&(&pMemoryRequirements)->memoryRequirements)->alignment));
  pMemoryRequirements_proto_memoryRequirements_proto->set_memorytypebits((&(&pMemoryRequirements)->memoryRequirements)->memoryTypeBits);
  response->set_result(VK_SUCCESS);
}
void UnpackAndExecuteVkCreateImageView(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateImageView");

  VkImageViewCreateInfo pCreateInfo = {};
  pCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  pCreateInfo.pNext = nullptr; // pNext chains are currently unsupported
  if (request.vkcreateimageview().pcreateinfo().has_flags()) {
    pCreateInfo.flags = static_cast<VkImageViewCreateFlags>(request.vkcreateimageview().pcreateinfo().flags());
  } else {
    pCreateInfo.flags = VkImageViewCreateFlags{};
  }
  pCreateInfo.image = reinterpret_cast<VkImage>(request.vkcreateimageview().pcreateinfo().image());
  pCreateInfo.viewType = static_cast<VkImageViewType>(request.vkcreateimageview().pcreateinfo().viewtype());
  pCreateInfo.format = static_cast<VkFormat>(request.vkcreateimageview().pcreateinfo().format());
  VkComponentMapping &pCreateInfo_components = pCreateInfo.components;
  pCreateInfo_components.r = static_cast<VkComponentSwizzle>(request.vkcreateimageview().pcreateinfo().components().r());
  pCreateInfo_components.g = static_cast<VkComponentSwizzle>(request.vkcreateimageview().pcreateinfo().components().g());
  pCreateInfo_components.b = static_cast<VkComponentSwizzle>(request.vkcreateimageview().pcreateinfo().components().b());
  pCreateInfo_components.a = static_cast<VkComponentSwizzle>(request.vkcreateimageview().pcreateinfo().components().a());
  VkImageSubresourceRange &pCreateInfo_subresourceRange = pCreateInfo.subresourceRange;
  pCreateInfo_subresourceRange.aspectMask = static_cast<VkImageAspectFlags>(request.vkcreateimageview().pcreateinfo().subresourcerange().aspectmask());
  pCreateInfo_subresourceRange.baseMipLevel = request.vkcreateimageview().pcreateinfo().subresourcerange().basemiplevel();
  pCreateInfo_subresourceRange.levelCount = request.vkcreateimageview().pcreateinfo().subresourcerange().levelcount();
  pCreateInfo_subresourceRange.baseArrayLayer = request.vkcreateimageview().pcreateinfo().subresourcerange().basearraylayer();
  pCreateInfo_subresourceRange.layerCount = request.vkcreateimageview().pcreateinfo().subresourcerange().layercount();
  VkImageView client_pView = reinterpret_cast<VkImageView>(request.vkcreateimageview().pview());
  VkImageView server_pView;
  VkResult result = vkCreateImageView(reinterpret_cast<VkDevice>(request.vkcreateimageview().device()), &pCreateInfo, nullptr, &server_pView);
  response->mutable_vkcreateimageview()->set_pview(reinterpret_cast<uint64_t>(server_pView));
  response->set_result(result);
}
void UnpackAndExecuteVkDestroyImageView(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyImageView");

  vkDestroyImageView(reinterpret_cast<VkDevice>(request.vkdestroyimageview().device()), reinterpret_cast<VkImageView>(request.vkdestroyimageview().imageview()), nullptr);
  response->set_result(VK_SUCCESS);
}
void UnpackAndExecuteVkCreateCommandPool(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateCommandPool");

  VkCommandPoolCreateInfo pCreateInfo = {};
  pCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  pCreateInfo.pNext = nullptr; // pNext chains are currently unsupported
  if (request.vkcreatecommandpool().pcreateinfo().has_flags()) {
    pCreateInfo.flags = static_cast<VkCommandPoolCreateFlags>(request.vkcreatecommandpool().pcreateinfo().flags());
  } else {
    pCreateInfo.flags = VkCommandPoolCreateFlags{};
  }
  pCreateInfo.queueFamilyIndex = request.vkcreatecommandpool().pcreateinfo().queuefamilyindex();
  VkCommandPool client_pCommandPool = reinterpret_cast<VkCommandPool>(request.vkcreatecommandpool().pcommandpool());
  VkCommandPool server_pCommandPool;
  VkResult result = vkCreateCommandPool(reinterpret_cast<VkDevice>(request.vkcreatecommandpool().device()), &pCreateInfo, nullptr, &server_pCommandPool);
  response->mutable_vkcreatecommandpool()->set_pcommandpool(reinterpret_cast<uint64_t>(server_pCommandPool));
  response->set_result(result);
}
void UnpackAndExecuteVkDestroyCommandPool(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyCommandPool");

  vkDestroyCommandPool(reinterpret_cast<VkDevice>(request.vkdestroycommandpool().device()), reinterpret_cast<VkCommandPool>(request.vkdestroycommandpool().commandpool()), nullptr);
  response->set_result(VK_SUCCESS);
}
void UnpackAndExecuteVkAllocateCommandBuffers(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkAllocateCommandBuffers");

  VkCommandBufferAllocateInfo pAllocateInfo = {};
  pAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  pAllocateInfo.pNext = nullptr; // pNext chains are currently unsupported
  pAllocateInfo.commandPool = reinterpret_cast<VkCommandPool>(request.vkallocatecommandbuffers().pallocateinfo().commandpool());
  pAllocateInfo.level = static_cast<VkCommandBufferLevel>(request.vkallocatecommandbuffers().pallocateinfo().level());
  pAllocateInfo.commandBufferCount = request.vkallocatecommandbuffers().pallocateinfo().commandbuffercount();
  std::vector<VkCommandBuffer> pCommandBuffers(request.vkallocatecommandbuffers().pallocateinfo().commandbuffercount());
  VkResult result = vkAllocateCommandBuffers(reinterpret_cast<VkDevice>(request.vkallocatecommandbuffers().device()), &pAllocateInfo, pCommandBuffers.data());
  for (VkCommandBuffer pCommandBuffers_elem : pCommandBuffers) {
    response->mutable_vkallocatecommandbuffers()->add_pcommandbuffers(reinterpret_cast<uint64_t>(pCommandBuffers_elem));
  }
  response->set_result(result);
}
void UnpackAndExecuteVkFreeCommandBuffers(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkFreeCommandBuffers");

  vkFreeCommandBuffers(reinterpret_cast<VkDevice>(request.vkfreecommandbuffers().device()), reinterpret_cast<VkCommandPool>(request.vkfreecommandbuffers().commandpool()), request.vkfreecommandbuffers().commandbuffercount(), reinterpret_cast<const VkCommandBuffer*>(request.vkfreecommandbuffers().pcommandbuffers().data()));
  response->set_result(VK_SUCCESS);
}
void UnpackAndExecuteVkBeginCommandBuffer(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkBeginCommandBuffer");

  VkCommandBufferBeginInfo pBeginInfo = {};
  pBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  pBeginInfo.pNext = nullptr; // pNext chains are currently unsupported
  if (request.vkbegincommandbuffer().pbegininfo().has_flags()) {
    pBeginInfo.flags = static_cast<VkCommandBufferUsageFlags>(request.vkbegincommandbuffer().pbegininfo().flags());
  } else {
    pBeginInfo.flags = VkCommandBufferUsageFlags{};
  }
  VkCommandBufferInheritanceInfo pBeginInfo_pInheritanceInfo = {};
  if (request.vkbegincommandbuffer().pbegininfo().has_pinheritanceinfo()) {
    pBeginInfo_pInheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
    pBeginInfo_pInheritanceInfo.pNext = nullptr; // pNext chains are currently unsupported
    if (request.vkbegincommandbuffer().pbegininfo().pinheritanceinfo().has_renderpass()) {
      pBeginInfo_pInheritanceInfo.renderPass = reinterpret_cast<VkRenderPass>(request.vkbegincommandbuffer().pbegininfo().pinheritanceinfo().renderpass());
    } else {
      pBeginInfo_pInheritanceInfo.renderPass = VkRenderPass{};
    }
    pBeginInfo_pInheritanceInfo.subpass = request.vkbegincommandbuffer().pbegininfo().pinheritanceinfo().subpass();
    if (request.vkbegincommandbuffer().pbegininfo().pinheritanceinfo().has_framebuffer()) {
      pBeginInfo_pInheritanceInfo.framebuffer = reinterpret_cast<VkFramebuffer>(request.vkbegincommandbuffer().pbegininfo().pinheritanceinfo().framebuffer());
    } else {
      pBeginInfo_pInheritanceInfo.framebuffer = VkFramebuffer{};
    }
    pBeginInfo_pInheritanceInfo.occlusionQueryEnable = request.vkbegincommandbuffer().pbegininfo().pinheritanceinfo().occlusionqueryenable();
    if (request.vkbegincommandbuffer().pbegininfo().pinheritanceinfo().has_queryflags()) {
      pBeginInfo_pInheritanceInfo.queryFlags = static_cast<VkQueryControlFlags>(request.vkbegincommandbuffer().pbegininfo().pinheritanceinfo().queryflags());
    } else {
      pBeginInfo_pInheritanceInfo.queryFlags = VkQueryControlFlags{};
    }
    if (request.vkbegincommandbuffer().pbegininfo().pinheritanceinfo().has_pipelinestatistics()) {
      pBeginInfo_pInheritanceInfo.pipelineStatistics = static_cast<VkQueryPipelineStatisticFlags>(request.vkbegincommandbuffer().pbegininfo().pinheritanceinfo().pipelinestatistics());
    } else {
      pBeginInfo_pInheritanceInfo.pipelineStatistics = VkQueryPipelineStatisticFlags{};
    }
    pBeginInfo.pInheritanceInfo = &pBeginInfo_pInheritanceInfo;
  } else {
    pBeginInfo.pInheritanceInfo = nullptr;
  }
  VkResult result = vkBeginCommandBuffer(reinterpret_cast<VkCommandBuffer>(request.vkbegincommandbuffer().commandbuffer()), &pBeginInfo);
  response->set_result(result);
}
void UnpackAndExecuteVkEndCommandBuffer(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkEndCommandBuffer");

  VkResult result = vkEndCommandBuffer(reinterpret_cast<VkCommandBuffer>(request.vkendcommandbuffer().commandbuffer()));
  response->set_result(result);
}
void UnpackAndExecuteVkGetImageSubresourceLayout(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkGetImageSubresourceLayout");

  VkImageSubresource pSubresource = {};
  pSubresource.aspectMask = static_cast<VkImageAspectFlags>(request.vkgetimagesubresourcelayout().psubresource().aspectmask());
  pSubresource.mipLevel = request.vkgetimagesubresourcelayout().psubresource().miplevel();
  pSubresource.arrayLayer = request.vkgetimagesubresourcelayout().psubresource().arraylayer();
  VkSubresourceLayout pLayout = {};
  vkGetImageSubresourceLayout(reinterpret_cast<VkDevice>(request.vkgetimagesubresourcelayout().device()), reinterpret_cast<VkImage>(request.vkgetimagesubresourcelayout().image()), &pSubresource, &pLayout);
  vvk::server::VkSubresourceLayout* pLayout_proto = response->mutable_vkgetimagesubresourcelayout()->mutable_playout();
  pLayout_proto->set_offset(static_cast<uint64_t>((&pLayout)->offset));
  pLayout_proto->set_size(static_cast<uint64_t>((&pLayout)->size));
  pLayout_proto->set_rowpitch(static_cast<uint64_t>((&pLayout)->rowPitch));
  pLayout_proto->set_arraypitch(static_cast<uint64_t>((&pLayout)->arrayPitch));
  pLayout_proto->set_depthpitch(static_cast<uint64_t>((&pLayout)->depthPitch));
  response->set_result(VK_SUCCESS);
}
void UnpackAndExecuteVkCreateRenderPass(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateRenderPass");

  VkRenderPassCreateInfo pCreateInfo = {};
  pCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  pCreateInfo.pNext = nullptr; // pNext chains are currently unsupported
  if (request.vkcreaterenderpass().pcreateinfo().has_flags()) {
    pCreateInfo.flags = static_cast<VkRenderPassCreateFlags>(request.vkcreaterenderpass().pcreateinfo().flags());
  } else {
    pCreateInfo.flags = VkRenderPassCreateFlags{};
  }
  if (request.vkcreaterenderpass().pcreateinfo().has_attachmentcount()) {
    pCreateInfo.attachmentCount = request.vkcreaterenderpass().pcreateinfo().attachmentcount();
  } else {
    pCreateInfo.attachmentCount = uint32_t{};
  }
  VkAttachmentDescription* pCreateInfo_pAttachments = new VkAttachmentDescription[request.vkcreaterenderpass().pcreateinfo().pattachments_size()]();
  pCreateInfo.pAttachments = pCreateInfo_pAttachments;
  for (int pAttachments_indx = 0; pAttachments_indx < request.vkcreaterenderpass().pcreateinfo().pattachments_size(); pAttachments_indx++) {
    VkAttachmentDescription &pCreateInfo_pAttachments_i = pCreateInfo_pAttachments[pAttachments_indx];
    if (request.vkcreaterenderpass().pcreateinfo().pattachments(pAttachments_indx).has_flags()) {
      pCreateInfo_pAttachments_i.flags = static_cast<VkAttachmentDescriptionFlags>(request.vkcreaterenderpass().pcreateinfo().pattachments(pAttachments_indx).flags());
    } else {
      pCreateInfo_pAttachments_i.flags = VkAttachmentDescriptionFlags{};
    }
    pCreateInfo_pAttachments_i.format = static_cast<VkFormat>(request.vkcreaterenderpass().pcreateinfo().pattachments(pAttachments_indx).format());
    pCreateInfo_pAttachments_i.samples = static_cast<VkSampleCountFlagBits>(request.vkcreaterenderpass().pcreateinfo().pattachments(pAttachments_indx).samples());
    pCreateInfo_pAttachments_i.loadOp = static_cast<VkAttachmentLoadOp>(request.vkcreaterenderpass().pcreateinfo().pattachments(pAttachments_indx).loadop());
    pCreateInfo_pAttachments_i.storeOp = static_cast<VkAttachmentStoreOp>(request.vkcreaterenderpass().pcreateinfo().pattachments(pAttachments_indx).storeop());
    pCreateInfo_pAttachments_i.stencilLoadOp = static_cast<VkAttachmentLoadOp>(request.vkcreaterenderpass().pcreateinfo().pattachments(pAttachments_indx).stencilloadop());
    pCreateInfo_pAttachments_i.stencilStoreOp = static_cast<VkAttachmentStoreOp>(request.vkcreaterenderpass().pcreateinfo().pattachments(pAttachments_indx).stencilstoreop());
    pCreateInfo_pAttachments_i.initialLayout = static_cast<VkImageLayout>(request.vkcreaterenderpass().pcreateinfo().pattachments(pAttachments_indx).initiallayout());
    pCreateInfo_pAttachments_i.finalLayout = static_cast<VkImageLayout>(request.vkcreaterenderpass().pcreateinfo().pattachments(pAttachments_indx).finallayout());
  }
  pCreateInfo.subpassCount = request.vkcreaterenderpass().pcreateinfo().subpasscount();
  VkSubpassDescription* pCreateInfo_pSubpasses = new VkSubpassDescription[request.vkcreaterenderpass().pcreateinfo().psubpasses_size()]();
  pCreateInfo.pSubpasses = pCreateInfo_pSubpasses;
  for (int pSubpasses_indx = 0; pSubpasses_indx < request.vkcreaterenderpass().pcreateinfo().psubpasses_size(); pSubpasses_indx++) {
    VkSubpassDescription &pCreateInfo_pSubpasses_i = pCreateInfo_pSubpasses[pSubpasses_indx];
    if (request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).has_flags()) {
      pCreateInfo_pSubpasses_i.flags = static_cast<VkSubpassDescriptionFlags>(request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).flags());
    } else {
      pCreateInfo_pSubpasses_i.flags = VkSubpassDescriptionFlags{};
    }
    pCreateInfo_pSubpasses_i.pipelineBindPoint = static_cast<VkPipelineBindPoint>(request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).pipelinebindpoint());
    if (request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).has_inputattachmentcount()) {
      pCreateInfo_pSubpasses_i.inputAttachmentCount = request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).inputattachmentcount();
    } else {
      pCreateInfo_pSubpasses_i.inputAttachmentCount = uint32_t{};
    }
    VkAttachmentReference* pCreateInfo_pSubpasses_i_pInputAttachments = new VkAttachmentReference[request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).pinputattachments_size()]();
    pCreateInfo_pSubpasses_i.pInputAttachments = pCreateInfo_pSubpasses_i_pInputAttachments;
    for (int pInputAttachments_indx = 0; pInputAttachments_indx < request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).pinputattachments_size(); pInputAttachments_indx++) {
      VkAttachmentReference &pCreateInfo_pSubpasses_i_pInputAttachments_i = pCreateInfo_pSubpasses_i_pInputAttachments[pInputAttachments_indx];
      pCreateInfo_pSubpasses_i_pInputAttachments_i.attachment = request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).pinputattachments(pInputAttachments_indx).attachment();
      pCreateInfo_pSubpasses_i_pInputAttachments_i.layout = static_cast<VkImageLayout>(request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).pinputattachments(pInputAttachments_indx).layout());
    }
    if (request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).has_colorattachmentcount()) {
      pCreateInfo_pSubpasses_i.colorAttachmentCount = request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).colorattachmentcount();
    } else {
      pCreateInfo_pSubpasses_i.colorAttachmentCount = uint32_t{};
    }
    VkAttachmentReference* pCreateInfo_pSubpasses_i_pColorAttachments = new VkAttachmentReference[request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).pcolorattachments_size()]();
    pCreateInfo_pSubpasses_i.pColorAttachments = pCreateInfo_pSubpasses_i_pColorAttachments;
    for (int pColorAttachments_indx = 0; pColorAttachments_indx < request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).pcolorattachments_size(); pColorAttachments_indx++) {
      VkAttachmentReference &pCreateInfo_pSubpasses_i_pColorAttachments_i = pCreateInfo_pSubpasses_i_pColorAttachments[pColorAttachments_indx];
      pCreateInfo_pSubpasses_i_pColorAttachments_i.attachment = request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).pcolorattachments(pColorAttachments_indx).attachment();
      pCreateInfo_pSubpasses_i_pColorAttachments_i.layout = static_cast<VkImageLayout>(request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).pcolorattachments(pColorAttachments_indx).layout());
    }
    VkAttachmentReference* pCreateInfo_pSubpasses_i_pResolveAttachments = new VkAttachmentReference[request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).presolveattachments_size()]();
    pCreateInfo_pSubpasses_i.pResolveAttachments = pCreateInfo_pSubpasses_i_pResolveAttachments;
    if (request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).presolveattachments_size()) {
      for (int pResolveAttachments_indx = 0; pResolveAttachments_indx < request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).presolveattachments_size(); pResolveAttachments_indx++) {
        VkAttachmentReference &pCreateInfo_pSubpasses_i_pResolveAttachments_i = pCreateInfo_pSubpasses_i_pResolveAttachments[pResolveAttachments_indx];
        pCreateInfo_pSubpasses_i_pResolveAttachments_i.attachment = request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).presolveattachments(pResolveAttachments_indx).attachment();
        pCreateInfo_pSubpasses_i_pResolveAttachments_i.layout = static_cast<VkImageLayout>(request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).presolveattachments(pResolveAttachments_indx).layout());
      }
    } else {
      pCreateInfo_pSubpasses_i.pResolveAttachments = nullptr;
    }
    VkAttachmentReference pCreateInfo_pSubpasses_i_pDepthStencilAttachment = {};
    if (request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).has_pdepthstencilattachment()) {
      pCreateInfo_pSubpasses_i_pDepthStencilAttachment.attachment = request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).pdepthstencilattachment().attachment();
      pCreateInfo_pSubpasses_i_pDepthStencilAttachment.layout = static_cast<VkImageLayout>(request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).pdepthstencilattachment().layout());
      pCreateInfo_pSubpasses_i.pDepthStencilAttachment = &pCreateInfo_pSubpasses_i_pDepthStencilAttachment;
    } else {
      pCreateInfo_pSubpasses_i.pDepthStencilAttachment = nullptr;
    }
    if (request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).has_preserveattachmentcount()) {
      pCreateInfo_pSubpasses_i.preserveAttachmentCount = request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).preserveattachmentcount();
    } else {
      pCreateInfo_pSubpasses_i.preserveAttachmentCount = uint32_t{};
    }
    uint32_t* pCreateInfo_pSubpasses_i_pPreserveAttachments = new uint32_t[request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).ppreserveattachments_size()]();
    pCreateInfo_pSubpasses_i.pPreserveAttachments = pCreateInfo_pSubpasses_i_pPreserveAttachments;
    for (int pPreserveAttachments_indx = 0; pPreserveAttachments_indx < request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).ppreserveattachments_size(); pPreserveAttachments_indx++) {
      pCreateInfo_pSubpasses_i_pPreserveAttachments[pPreserveAttachments_indx] = request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).ppreserveattachments(pPreserveAttachments_indx);
    }
  }
  if (request.vkcreaterenderpass().pcreateinfo().has_dependencycount()) {
    pCreateInfo.dependencyCount = request.vkcreaterenderpass().pcreateinfo().dependencycount();
  } else {
    pCreateInfo.dependencyCount = uint32_t{};
  }
  VkSubpassDependency* pCreateInfo_pDependencies = new VkSubpassDependency[request.vkcreaterenderpass().pcreateinfo().pdependencies_size()]();
  pCreateInfo.pDependencies = pCreateInfo_pDependencies;
  for (int pDependencies_indx = 0; pDependencies_indx < request.vkcreaterenderpass().pcreateinfo().pdependencies_size(); pDependencies_indx++) {
    VkSubpassDependency &pCreateInfo_pDependencies_i = pCreateInfo_pDependencies[pDependencies_indx];
    pCreateInfo_pDependencies_i.srcSubpass = request.vkcreaterenderpass().pcreateinfo().pdependencies(pDependencies_indx).srcsubpass();
    pCreateInfo_pDependencies_i.dstSubpass = request.vkcreaterenderpass().pcreateinfo().pdependencies(pDependencies_indx).dstsubpass();
    if (request.vkcreaterenderpass().pcreateinfo().pdependencies(pDependencies_indx).has_srcstagemask()) {
      pCreateInfo_pDependencies_i.srcStageMask = static_cast<VkPipelineStageFlags>(request.vkcreaterenderpass().pcreateinfo().pdependencies(pDependencies_indx).srcstagemask());
    } else {
      pCreateInfo_pDependencies_i.srcStageMask = VkPipelineStageFlags{};
    }
    if (request.vkcreaterenderpass().pcreateinfo().pdependencies(pDependencies_indx).has_dststagemask()) {
      pCreateInfo_pDependencies_i.dstStageMask = static_cast<VkPipelineStageFlags>(request.vkcreaterenderpass().pcreateinfo().pdependencies(pDependencies_indx).dststagemask());
    } else {
      pCreateInfo_pDependencies_i.dstStageMask = VkPipelineStageFlags{};
    }
    if (request.vkcreaterenderpass().pcreateinfo().pdependencies(pDependencies_indx).has_srcaccessmask()) {
      pCreateInfo_pDependencies_i.srcAccessMask = static_cast<VkAccessFlags>(request.vkcreaterenderpass().pcreateinfo().pdependencies(pDependencies_indx).srcaccessmask());
    } else {
      pCreateInfo_pDependencies_i.srcAccessMask = VkAccessFlags{};
    }
    if (request.vkcreaterenderpass().pcreateinfo().pdependencies(pDependencies_indx).has_dstaccessmask()) {
      pCreateInfo_pDependencies_i.dstAccessMask = static_cast<VkAccessFlags>(request.vkcreaterenderpass().pcreateinfo().pdependencies(pDependencies_indx).dstaccessmask());
    } else {
      pCreateInfo_pDependencies_i.dstAccessMask = VkAccessFlags{};
    }
    if (request.vkcreaterenderpass().pcreateinfo().pdependencies(pDependencies_indx).has_dependencyflags()) {
      pCreateInfo_pDependencies_i.dependencyFlags = static_cast<VkDependencyFlags>(request.vkcreaterenderpass().pcreateinfo().pdependencies(pDependencies_indx).dependencyflags());
    } else {
      pCreateInfo_pDependencies_i.dependencyFlags = VkDependencyFlags{};
    }
  }
  VkRenderPass client_pRenderPass = reinterpret_cast<VkRenderPass>(request.vkcreaterenderpass().prenderpass());
  VkRenderPass server_pRenderPass;
  VkResult result = vkCreateRenderPass(reinterpret_cast<VkDevice>(request.vkcreaterenderpass().device()), &pCreateInfo, nullptr, &server_pRenderPass);
  response->mutable_vkcreaterenderpass()->set_prenderpass(reinterpret_cast<uint64_t>(server_pRenderPass));
  response->set_result(result);
  delete[] pCreateInfo.pAttachments;
  for (int pSubpasses_indx = 0; pSubpasses_indx < request.vkcreaterenderpass().pcreateinfo().psubpasses_size(); pSubpasses_indx++)  {
    const VkSubpassDescription &pCreateInfo_pSubpasses_i = pCreateInfo.pSubpasses[pSubpasses_indx];
    delete[] pCreateInfo_pSubpasses_i.pInputAttachments;
    delete[] pCreateInfo_pSubpasses_i.pColorAttachments;
    delete[] pCreateInfo_pSubpasses_i.pResolveAttachments;
    delete[] pCreateInfo_pSubpasses_i.pPreserveAttachments;
  }
  delete[] pCreateInfo.pSubpasses;
  delete[] pCreateInfo.pDependencies;
}
void UnpackAndExecuteVkDestroyRenderPass(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyRenderPass");

  vkDestroyRenderPass(reinterpret_cast<VkDevice>(request.vkdestroyrenderpass().device()), reinterpret_cast<VkRenderPass>(request.vkdestroyrenderpass().renderpass()), nullptr);
  response->set_result(VK_SUCCESS);
}
void UnpackAndExecuteVkCreatePipelineLayout(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreatePipelineLayout");

  VkPipelineLayoutCreateInfo pCreateInfo = {};
  pCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pCreateInfo.pNext = nullptr; // pNext chains are currently unsupported
  if (request.vkcreatepipelinelayout().pcreateinfo().has_flags()) {
    pCreateInfo.flags = static_cast<VkPipelineLayoutCreateFlags>(request.vkcreatepipelinelayout().pcreateinfo().flags());
  } else {
    pCreateInfo.flags = VkPipelineLayoutCreateFlags{};
  }
  if (request.vkcreatepipelinelayout().pcreateinfo().has_setlayoutcount()) {
    pCreateInfo.setLayoutCount = request.vkcreatepipelinelayout().pcreateinfo().setlayoutcount();
  } else {
    pCreateInfo.setLayoutCount = uint32_t{};
  }
  pCreateInfo.pSetLayouts = reinterpret_cast<const VkDescriptorSetLayout*>(request.vkcreatepipelinelayout().pcreateinfo().psetlayouts().data());
  if (request.vkcreatepipelinelayout().pcreateinfo().has_pushconstantrangecount()) {
    pCreateInfo.pushConstantRangeCount = request.vkcreatepipelinelayout().pcreateinfo().pushconstantrangecount();
  } else {
    pCreateInfo.pushConstantRangeCount = uint32_t{};
  }
  VkPushConstantRange* pCreateInfo_pPushConstantRanges = new VkPushConstantRange[request.vkcreatepipelinelayout().pcreateinfo().ppushconstantranges_size()]();
  pCreateInfo.pPushConstantRanges = pCreateInfo_pPushConstantRanges;
  for (int pPushConstantRanges_indx = 0; pPushConstantRanges_indx < request.vkcreatepipelinelayout().pcreateinfo().ppushconstantranges_size(); pPushConstantRanges_indx++) {
    VkPushConstantRange &pCreateInfo_pPushConstantRanges_i = pCreateInfo_pPushConstantRanges[pPushConstantRanges_indx];
    pCreateInfo_pPushConstantRanges_i.stageFlags = static_cast<VkShaderStageFlags>(request.vkcreatepipelinelayout().pcreateinfo().ppushconstantranges(pPushConstantRanges_indx).stageflags());
    pCreateInfo_pPushConstantRanges_i.offset = request.vkcreatepipelinelayout().pcreateinfo().ppushconstantranges(pPushConstantRanges_indx).offset();
    pCreateInfo_pPushConstantRanges_i.size = request.vkcreatepipelinelayout().pcreateinfo().ppushconstantranges(pPushConstantRanges_indx).size();
  }
  VkPipelineLayout client_pPipelineLayout = reinterpret_cast<VkPipelineLayout>(request.vkcreatepipelinelayout().ppipelinelayout());
  VkPipelineLayout server_pPipelineLayout;
  VkResult result = vkCreatePipelineLayout(reinterpret_cast<VkDevice>(request.vkcreatepipelinelayout().device()), &pCreateInfo, nullptr, &server_pPipelineLayout);
  response->mutable_vkcreatepipelinelayout()->set_ppipelinelayout(reinterpret_cast<uint64_t>(server_pPipelineLayout));
  response->set_result(result);
  delete[] pCreateInfo.pPushConstantRanges;
}
void UnpackAndExecuteVkDestroyPipelineLayout(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyPipelineLayout");

  vkDestroyPipelineLayout(reinterpret_cast<VkDevice>(request.vkdestroypipelinelayout().device()), reinterpret_cast<VkPipelineLayout>(request.vkdestroypipelinelayout().pipelinelayout()), nullptr);
  response->set_result(VK_SUCCESS);
}
void UnpackAndExecuteVkCreateShaderModule(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateShaderModule");

  VkShaderModuleCreateInfo pCreateInfo = {};
  pCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  pCreateInfo.pNext = nullptr; // pNext chains are currently unsupported
  if (request.vkcreateshadermodule().pcreateinfo().has_flags()) {
    pCreateInfo.flags = static_cast<VkShaderModuleCreateFlags>(request.vkcreateshadermodule().pcreateinfo().flags());
  } else {
    pCreateInfo.flags = VkShaderModuleCreateFlags{};
  }
  pCreateInfo.codeSize = request.vkcreateshadermodule().pcreateinfo().codesize();
  uint32_t* pCreateInfo_pCode = new uint32_t[request.vkcreateshadermodule().pcreateinfo().pcode_size()]();
  pCreateInfo.pCode = pCreateInfo_pCode;
  for (int pCode_indx = 0; pCode_indx < request.vkcreateshadermodule().pcreateinfo().pcode_size(); pCode_indx++) {
    pCreateInfo_pCode[pCode_indx] = request.vkcreateshadermodule().pcreateinfo().pcode(pCode_indx);
  }
  VkShaderModule client_pShaderModule = reinterpret_cast<VkShaderModule>(request.vkcreateshadermodule().pshadermodule());
  VkShaderModule server_pShaderModule;
  VkResult result = vkCreateShaderModule(reinterpret_cast<VkDevice>(request.vkcreateshadermodule().device()), &pCreateInfo, nullptr, &server_pShaderModule);
  response->mutable_vkcreateshadermodule()->set_pshadermodule(reinterpret_cast<uint64_t>(server_pShaderModule));
  response->set_result(result);
  delete[] pCreateInfo.pCode;
}
void UnpackAndExecuteVkDestroyShaderModule(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyShaderModule");

  vkDestroyShaderModule(reinterpret_cast<VkDevice>(request.vkdestroyshadermodule().device()), reinterpret_cast<VkShaderModule>(request.vkdestroyshadermodule().shadermodule()), nullptr);
  response->set_result(VK_SUCCESS);
}

