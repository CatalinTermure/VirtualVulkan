// GENERATED FILE - DO NOT EDIT
// clang-format off
#include "remote_call.h"

#include <vulkan/vulkan.h>
#include <spdlog/spdlog.h>
#include "vvk_server.grpc.pb.h"
#include <cstring>

namespace vvk {
VkResult PackAndCallVkCreateInstance(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateInstance");
  vvk::server::VkInstanceCreateInfo* pCreateInfo_proto = request.mutable_vkcreateinstance()->mutable_pcreateinfo();
  if (pCreateInfo->pNext) {
    // pNext chains are currently not supported
  }
  if (pCreateInfo->flags) {
    pCreateInfo_proto->set_flags(pCreateInfo->flags);
  }
  if (pCreateInfo->pApplicationInfo) {
    vvk::server::VkApplicationInfo* pCreateInfo_proto_pApplicationInfo_proto = pCreateInfo_proto->mutable_papplicationinfo();
    if (pCreateInfo->pApplicationInfo->pNext) {
      // pNext chains are currently not supported
    }
    if (pCreateInfo->pApplicationInfo->pApplicationName) {
      pCreateInfo_proto_pApplicationInfo_proto->set_papplicationname(pCreateInfo->pApplicationInfo->pApplicationName);
    }
    pCreateInfo_proto_pApplicationInfo_proto->set_applicationversion(pCreateInfo->pApplicationInfo->applicationVersion);
    if (pCreateInfo->pApplicationInfo->pEngineName) {
      pCreateInfo_proto_pApplicationInfo_proto->set_penginename(pCreateInfo->pApplicationInfo->pEngineName);
    }
    pCreateInfo_proto_pApplicationInfo_proto->set_engineversion(pCreateInfo->pApplicationInfo->engineVersion);
    pCreateInfo_proto_pApplicationInfo_proto->set_apiversion(pCreateInfo->pApplicationInfo->apiVersion);
  }
  if (pCreateInfo->enabledLayerCount) {
    pCreateInfo_proto->set_enabledlayercount(pCreateInfo->enabledLayerCount);
  }
  for (int i = 0; i < pCreateInfo->enabledLayerCount; i++) {
    pCreateInfo_proto->add_ppenabledlayernames(pCreateInfo->ppEnabledLayerNames[i]);
  }
  if (pCreateInfo->enabledExtensionCount) {
    pCreateInfo_proto->set_enabledextensioncount(pCreateInfo->enabledExtensionCount);
  }
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
  *pInstance = reinterpret_cast<VkInstance>(response.vkcreateinstance().pinstance());
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkDestroyInstance(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkInstance instance, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkDestroyInstance");
  if (instance) {
    request.mutable_vkdestroyinstance()->set_instance(reinterpret_cast<uint64_t>(instance));
  }
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
  *pPhysicalDeviceCount = response.vkenumeratephysicaldevices().pphysicaldevicecount();
  if (pPhysicalDevices) {
    assert(*pPhysicalDeviceCount == response.vkenumeratephysicaldevices().pphysicaldevicecount());
    for (int i = 0; i < *pPhysicalDeviceCount; i++) {
      pPhysicalDevices[i] = reinterpret_cast<VkPhysicalDevice>(response.vkenumeratephysicaldevices().pphysicaldevices(i));
    }
  }
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkGetPhysicalDeviceProperties(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetPhysicalDeviceProperties");
  request.mutable_vkgetphysicaldeviceproperties()->set_physicaldevice(reinterpret_cast<uint64_t>(physicalDevice));
  vvk::server::VvkResponse response;

  if (!stream->Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream->Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  VkPhysicalDeviceProperties& pProperties_ref = *pProperties;
  pProperties_ref.apiVersion = response.vkgetphysicaldeviceproperties().pproperties().apiversion();
  pProperties_ref.driverVersion = response.vkgetphysicaldeviceproperties().pproperties().driverversion();
  pProperties_ref.vendorID = response.vkgetphysicaldeviceproperties().pproperties().vendorid();
  pProperties_ref.deviceID = response.vkgetphysicaldeviceproperties().pproperties().deviceid();
  pProperties_ref.deviceType = static_cast<VkPhysicalDeviceType>(response.vkgetphysicaldeviceproperties().pproperties().devicetype());
  strncpy(pProperties_ref.deviceName, response.vkgetphysicaldeviceproperties().pproperties().devicename().c_str(), VK_MAX_PHYSICAL_DEVICE_NAME_SIZE);
  for (int i = 0; i < VK_UUID_SIZE; i++) {
    pProperties_ref.pipelineCacheUUID[i] = static_cast<uint8_t>(response.vkgetphysicaldeviceproperties().pproperties().pipelinecacheuuid(i));
  }
  pProperties_ref.limits.maxImageDimension1D = response.vkgetphysicaldeviceproperties().pproperties().limits().maximagedimension1d();
  pProperties_ref.limits.maxImageDimension2D = response.vkgetphysicaldeviceproperties().pproperties().limits().maximagedimension2d();
  pProperties_ref.limits.maxImageDimension3D = response.vkgetphysicaldeviceproperties().pproperties().limits().maximagedimension3d();
  pProperties_ref.limits.maxImageDimensionCube = response.vkgetphysicaldeviceproperties().pproperties().limits().maximagedimensioncube();
  pProperties_ref.limits.maxImageArrayLayers = response.vkgetphysicaldeviceproperties().pproperties().limits().maximagearraylayers();
  pProperties_ref.limits.maxTexelBufferElements = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtexelbufferelements();
  pProperties_ref.limits.maxUniformBufferRange = response.vkgetphysicaldeviceproperties().pproperties().limits().maxuniformbufferrange();
  pProperties_ref.limits.maxStorageBufferRange = response.vkgetphysicaldeviceproperties().pproperties().limits().maxstoragebufferrange();
  pProperties_ref.limits.maxPushConstantsSize = response.vkgetphysicaldeviceproperties().pproperties().limits().maxpushconstantssize();
  pProperties_ref.limits.maxMemoryAllocationCount = response.vkgetphysicaldeviceproperties().pproperties().limits().maxmemoryallocationcount();
  pProperties_ref.limits.maxSamplerAllocationCount = response.vkgetphysicaldeviceproperties().pproperties().limits().maxsamplerallocationcount();
  pProperties_ref.limits.bufferImageGranularity = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties().pproperties().limits().bufferimagegranularity());
  pProperties_ref.limits.sparseAddressSpaceSize = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties().pproperties().limits().sparseaddressspacesize());
  pProperties_ref.limits.maxBoundDescriptorSets = response.vkgetphysicaldeviceproperties().pproperties().limits().maxbounddescriptorsets();
  pProperties_ref.limits.maxPerStageDescriptorSamplers = response.vkgetphysicaldeviceproperties().pproperties().limits().maxperstagedescriptorsamplers();
  pProperties_ref.limits.maxPerStageDescriptorUniformBuffers = response.vkgetphysicaldeviceproperties().pproperties().limits().maxperstagedescriptoruniformbuffers();
  pProperties_ref.limits.maxPerStageDescriptorStorageBuffers = response.vkgetphysicaldeviceproperties().pproperties().limits().maxperstagedescriptorstoragebuffers();
  pProperties_ref.limits.maxPerStageDescriptorSampledImages = response.vkgetphysicaldeviceproperties().pproperties().limits().maxperstagedescriptorsampledimages();
  pProperties_ref.limits.maxPerStageDescriptorStorageImages = response.vkgetphysicaldeviceproperties().pproperties().limits().maxperstagedescriptorstorageimages();
  pProperties_ref.limits.maxPerStageDescriptorInputAttachments = response.vkgetphysicaldeviceproperties().pproperties().limits().maxperstagedescriptorinputattachments();
  pProperties_ref.limits.maxPerStageResources = response.vkgetphysicaldeviceproperties().pproperties().limits().maxperstageresources();
  pProperties_ref.limits.maxDescriptorSetSamplers = response.vkgetphysicaldeviceproperties().pproperties().limits().maxdescriptorsetsamplers();
  pProperties_ref.limits.maxDescriptorSetUniformBuffers = response.vkgetphysicaldeviceproperties().pproperties().limits().maxdescriptorsetuniformbuffers();
  pProperties_ref.limits.maxDescriptorSetUniformBuffersDynamic = response.vkgetphysicaldeviceproperties().pproperties().limits().maxdescriptorsetuniformbuffersdynamic();
  pProperties_ref.limits.maxDescriptorSetStorageBuffers = response.vkgetphysicaldeviceproperties().pproperties().limits().maxdescriptorsetstoragebuffers();
  pProperties_ref.limits.maxDescriptorSetStorageBuffersDynamic = response.vkgetphysicaldeviceproperties().pproperties().limits().maxdescriptorsetstoragebuffersdynamic();
  pProperties_ref.limits.maxDescriptorSetSampledImages = response.vkgetphysicaldeviceproperties().pproperties().limits().maxdescriptorsetsampledimages();
  pProperties_ref.limits.maxDescriptorSetStorageImages = response.vkgetphysicaldeviceproperties().pproperties().limits().maxdescriptorsetstorageimages();
  pProperties_ref.limits.maxDescriptorSetInputAttachments = response.vkgetphysicaldeviceproperties().pproperties().limits().maxdescriptorsetinputattachments();
  pProperties_ref.limits.maxVertexInputAttributes = response.vkgetphysicaldeviceproperties().pproperties().limits().maxvertexinputattributes();
  pProperties_ref.limits.maxVertexInputBindings = response.vkgetphysicaldeviceproperties().pproperties().limits().maxvertexinputbindings();
  pProperties_ref.limits.maxVertexInputAttributeOffset = response.vkgetphysicaldeviceproperties().pproperties().limits().maxvertexinputattributeoffset();
  pProperties_ref.limits.maxVertexInputBindingStride = response.vkgetphysicaldeviceproperties().pproperties().limits().maxvertexinputbindingstride();
  pProperties_ref.limits.maxVertexOutputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxvertexoutputcomponents();
  pProperties_ref.limits.maxTessellationGenerationLevel = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtessellationgenerationlevel();
  pProperties_ref.limits.maxTessellationPatchSize = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtessellationpatchsize();
  pProperties_ref.limits.maxTessellationControlPerVertexInputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtessellationcontrolpervertexinputcomponents();
  pProperties_ref.limits.maxTessellationControlPerVertexOutputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtessellationcontrolpervertexoutputcomponents();
  pProperties_ref.limits.maxTessellationControlPerPatchOutputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtessellationcontrolperpatchoutputcomponents();
  pProperties_ref.limits.maxTessellationControlTotalOutputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtessellationcontroltotaloutputcomponents();
  pProperties_ref.limits.maxTessellationEvaluationInputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtessellationevaluationinputcomponents();
  pProperties_ref.limits.maxTessellationEvaluationOutputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtessellationevaluationoutputcomponents();
  pProperties_ref.limits.maxGeometryShaderInvocations = response.vkgetphysicaldeviceproperties().pproperties().limits().maxgeometryshaderinvocations();
  pProperties_ref.limits.maxGeometryInputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxgeometryinputcomponents();
  pProperties_ref.limits.maxGeometryOutputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxgeometryoutputcomponents();
  pProperties_ref.limits.maxGeometryOutputVertices = response.vkgetphysicaldeviceproperties().pproperties().limits().maxgeometryoutputvertices();
  pProperties_ref.limits.maxGeometryTotalOutputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxgeometrytotaloutputcomponents();
  pProperties_ref.limits.maxFragmentInputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxfragmentinputcomponents();
  pProperties_ref.limits.maxFragmentOutputAttachments = response.vkgetphysicaldeviceproperties().pproperties().limits().maxfragmentoutputattachments();
  pProperties_ref.limits.maxFragmentDualSrcAttachments = response.vkgetphysicaldeviceproperties().pproperties().limits().maxfragmentdualsrcattachments();
  pProperties_ref.limits.maxFragmentCombinedOutputResources = response.vkgetphysicaldeviceproperties().pproperties().limits().maxfragmentcombinedoutputresources();
  pProperties_ref.limits.maxComputeSharedMemorySize = response.vkgetphysicaldeviceproperties().pproperties().limits().maxcomputesharedmemorysize();
  for (int i = 0; i < 3; i++) {
    pProperties_ref.limits.maxComputeWorkGroupCount[i] = response.vkgetphysicaldeviceproperties().pproperties().limits().maxcomputeworkgroupcount(i);
  }
  pProperties_ref.limits.maxComputeWorkGroupInvocations = response.vkgetphysicaldeviceproperties().pproperties().limits().maxcomputeworkgroupinvocations();
  for (int i = 0; i < 3; i++) {
    pProperties_ref.limits.maxComputeWorkGroupSize[i] = response.vkgetphysicaldeviceproperties().pproperties().limits().maxcomputeworkgroupsize(i);
  }
  pProperties_ref.limits.subPixelPrecisionBits = response.vkgetphysicaldeviceproperties().pproperties().limits().subpixelprecisionbits();
  pProperties_ref.limits.subTexelPrecisionBits = response.vkgetphysicaldeviceproperties().pproperties().limits().subtexelprecisionbits();
  pProperties_ref.limits.mipmapPrecisionBits = response.vkgetphysicaldeviceproperties().pproperties().limits().mipmapprecisionbits();
  pProperties_ref.limits.maxDrawIndexedIndexValue = response.vkgetphysicaldeviceproperties().pproperties().limits().maxdrawindexedindexvalue();
  pProperties_ref.limits.maxDrawIndirectCount = response.vkgetphysicaldeviceproperties().pproperties().limits().maxdrawindirectcount();
  pProperties_ref.limits.maxSamplerLodBias = response.vkgetphysicaldeviceproperties().pproperties().limits().maxsamplerlodbias();
  pProperties_ref.limits.maxSamplerAnisotropy = response.vkgetphysicaldeviceproperties().pproperties().limits().maxsampleranisotropy();
  pProperties_ref.limits.maxViewports = response.vkgetphysicaldeviceproperties().pproperties().limits().maxviewports();
  for (int i = 0; i < 2; i++) {
    pProperties_ref.limits.maxViewportDimensions[i] = response.vkgetphysicaldeviceproperties().pproperties().limits().maxviewportdimensions(i);
  }
  for (int i = 0; i < 2; i++) {
    pProperties_ref.limits.viewportBoundsRange[i] = response.vkgetphysicaldeviceproperties().pproperties().limits().viewportboundsrange(i);
  }
  pProperties_ref.limits.viewportSubPixelBits = response.vkgetphysicaldeviceproperties().pproperties().limits().viewportsubpixelbits();
  pProperties_ref.limits.minMemoryMapAlignment = response.vkgetphysicaldeviceproperties().pproperties().limits().minmemorymapalignment();
  pProperties_ref.limits.minTexelBufferOffsetAlignment = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties().pproperties().limits().mintexelbufferoffsetalignment());
  pProperties_ref.limits.minUniformBufferOffsetAlignment = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties().pproperties().limits().minuniformbufferoffsetalignment());
  pProperties_ref.limits.minStorageBufferOffsetAlignment = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties().pproperties().limits().minstoragebufferoffsetalignment());
  pProperties_ref.limits.minTexelOffset = response.vkgetphysicaldeviceproperties().pproperties().limits().mintexeloffset();
  pProperties_ref.limits.maxTexelOffset = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtexeloffset();
  pProperties_ref.limits.minTexelGatherOffset = response.vkgetphysicaldeviceproperties().pproperties().limits().mintexelgatheroffset();
  pProperties_ref.limits.maxTexelGatherOffset = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtexelgatheroffset();
  pProperties_ref.limits.minInterpolationOffset = response.vkgetphysicaldeviceproperties().pproperties().limits().mininterpolationoffset();
  pProperties_ref.limits.maxInterpolationOffset = response.vkgetphysicaldeviceproperties().pproperties().limits().maxinterpolationoffset();
  pProperties_ref.limits.subPixelInterpolationOffsetBits = response.vkgetphysicaldeviceproperties().pproperties().limits().subpixelinterpolationoffsetbits();
  pProperties_ref.limits.maxFramebufferWidth = response.vkgetphysicaldeviceproperties().pproperties().limits().maxframebufferwidth();
  pProperties_ref.limits.maxFramebufferHeight = response.vkgetphysicaldeviceproperties().pproperties().limits().maxframebufferheight();
  pProperties_ref.limits.maxFramebufferLayers = response.vkgetphysicaldeviceproperties().pproperties().limits().maxframebufferlayers();
  if (response.vkgetphysicaldeviceproperties().pproperties().limits().has_framebuffercolorsamplecounts()) {
    pProperties_ref.limits.framebufferColorSampleCounts = response.vkgetphysicaldeviceproperties().pproperties().limits().framebuffercolorsamplecounts();
  }
  if (response.vkgetphysicaldeviceproperties().pproperties().limits().has_framebufferdepthsamplecounts()) {
    pProperties_ref.limits.framebufferDepthSampleCounts = response.vkgetphysicaldeviceproperties().pproperties().limits().framebufferdepthsamplecounts();
  }
  if (response.vkgetphysicaldeviceproperties().pproperties().limits().has_framebufferstencilsamplecounts()) {
    pProperties_ref.limits.framebufferStencilSampleCounts = response.vkgetphysicaldeviceproperties().pproperties().limits().framebufferstencilsamplecounts();
  }
  if (response.vkgetphysicaldeviceproperties().pproperties().limits().has_framebuffernoattachmentssamplecounts()) {
    pProperties_ref.limits.framebufferNoAttachmentsSampleCounts = response.vkgetphysicaldeviceproperties().pproperties().limits().framebuffernoattachmentssamplecounts();
  }
  pProperties_ref.limits.maxColorAttachments = response.vkgetphysicaldeviceproperties().pproperties().limits().maxcolorattachments();
  if (response.vkgetphysicaldeviceproperties().pproperties().limits().has_sampledimagecolorsamplecounts()) {
    pProperties_ref.limits.sampledImageColorSampleCounts = response.vkgetphysicaldeviceproperties().pproperties().limits().sampledimagecolorsamplecounts();
  }
  if (response.vkgetphysicaldeviceproperties().pproperties().limits().has_sampledimageintegersamplecounts()) {
    pProperties_ref.limits.sampledImageIntegerSampleCounts = response.vkgetphysicaldeviceproperties().pproperties().limits().sampledimageintegersamplecounts();
  }
  if (response.vkgetphysicaldeviceproperties().pproperties().limits().has_sampledimagedepthsamplecounts()) {
    pProperties_ref.limits.sampledImageDepthSampleCounts = response.vkgetphysicaldeviceproperties().pproperties().limits().sampledimagedepthsamplecounts();
  }
  if (response.vkgetphysicaldeviceproperties().pproperties().limits().has_sampledimagestencilsamplecounts()) {
    pProperties_ref.limits.sampledImageStencilSampleCounts = response.vkgetphysicaldeviceproperties().pproperties().limits().sampledimagestencilsamplecounts();
  }
  if (response.vkgetphysicaldeviceproperties().pproperties().limits().has_storageimagesamplecounts()) {
    pProperties_ref.limits.storageImageSampleCounts = response.vkgetphysicaldeviceproperties().pproperties().limits().storageimagesamplecounts();
  }
  pProperties_ref.limits.maxSampleMaskWords = response.vkgetphysicaldeviceproperties().pproperties().limits().maxsamplemaskwords();
  pProperties_ref.limits.timestampComputeAndGraphics = response.vkgetphysicaldeviceproperties().pproperties().limits().timestampcomputeandgraphics();
  pProperties_ref.limits.timestampPeriod = response.vkgetphysicaldeviceproperties().pproperties().limits().timestampperiod();
  pProperties_ref.limits.maxClipDistances = response.vkgetphysicaldeviceproperties().pproperties().limits().maxclipdistances();
  pProperties_ref.limits.maxCullDistances = response.vkgetphysicaldeviceproperties().pproperties().limits().maxculldistances();
  pProperties_ref.limits.maxCombinedClipAndCullDistances = response.vkgetphysicaldeviceproperties().pproperties().limits().maxcombinedclipandculldistances();
  pProperties_ref.limits.discreteQueuePriorities = response.vkgetphysicaldeviceproperties().pproperties().limits().discretequeuepriorities();
  for (int i = 0; i < 2; i++) {
    pProperties_ref.limits.pointSizeRange[i] = response.vkgetphysicaldeviceproperties().pproperties().limits().pointsizerange(i);
  }
  for (int i = 0; i < 2; i++) {
    pProperties_ref.limits.lineWidthRange[i] = response.vkgetphysicaldeviceproperties().pproperties().limits().linewidthrange(i);
  }
  pProperties_ref.limits.pointSizeGranularity = response.vkgetphysicaldeviceproperties().pproperties().limits().pointsizegranularity();
  pProperties_ref.limits.lineWidthGranularity = response.vkgetphysicaldeviceproperties().pproperties().limits().linewidthgranularity();
  pProperties_ref.limits.strictLines = response.vkgetphysicaldeviceproperties().pproperties().limits().strictlines();
  pProperties_ref.limits.standardSampleLocations = response.vkgetphysicaldeviceproperties().pproperties().limits().standardsamplelocations();
  pProperties_ref.limits.optimalBufferCopyOffsetAlignment = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties().pproperties().limits().optimalbuffercopyoffsetalignment());
  pProperties_ref.limits.optimalBufferCopyRowPitchAlignment = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties().pproperties().limits().optimalbuffercopyrowpitchalignment());
  pProperties_ref.limits.nonCoherentAtomSize = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties().pproperties().limits().noncoherentatomsize());
  pProperties_ref.sparseProperties.residencyStandard2DBlockShape = response.vkgetphysicaldeviceproperties().pproperties().sparseproperties().residencystandard2dblockshape();
  pProperties_ref.sparseProperties.residencyStandard2DMultisampleBlockShape = response.vkgetphysicaldeviceproperties().pproperties().sparseproperties().residencystandard2dmultisampleblockshape();
  pProperties_ref.sparseProperties.residencyStandard3DBlockShape = response.vkgetphysicaldeviceproperties().pproperties().sparseproperties().residencystandard3dblockshape();
  pProperties_ref.sparseProperties.residencyAlignedMipSize = response.vkgetphysicaldeviceproperties().pproperties().sparseproperties().residencyalignedmipsize();
  pProperties_ref.sparseProperties.residencyNonResidentStrict = response.vkgetphysicaldeviceproperties().pproperties().sparseproperties().residencynonresidentstrict();
}
VkResult PackAndCallVkCreateDevice(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateDevice");
  request.mutable_vkcreatedevice()->set_physicaldevice(reinterpret_cast<uint64_t>(physicalDevice));
  vvk::server::VkDeviceCreateInfo* pCreateInfo_proto = request.mutable_vkcreatedevice()->mutable_pcreateinfo();
  if (pCreateInfo->pNext) {
    // pNext chains are currently not supported
  }
  if (pCreateInfo->flags) {
    pCreateInfo_proto->set_flags(pCreateInfo->flags);
  }
  pCreateInfo_proto->set_queuecreateinfocount(pCreateInfo->queueCreateInfoCount);
  for (int i = 0; i < pCreateInfo->queueCreateInfoCount; i++) {
    vvk::server::VkDeviceQueueCreateInfo* pCreateInfo_proto_pQueueCreateInfos_proto = pCreateInfo_proto->add_pqueuecreateinfos();
    if ((&pCreateInfo->pQueueCreateInfos[i])->pNext) {
      // pNext chains are currently not supported
    }
    if ((&pCreateInfo->pQueueCreateInfos[i])->flags) {
      pCreateInfo_proto_pQueueCreateInfos_proto->set_flags((&pCreateInfo->pQueueCreateInfos[i])->flags);
    }
    pCreateInfo_proto_pQueueCreateInfos_proto->set_queuefamilyindex((&pCreateInfo->pQueueCreateInfos[i])->queueFamilyIndex);
    pCreateInfo_proto_pQueueCreateInfos_proto->set_queuecount((&pCreateInfo->pQueueCreateInfos[i])->queueCount);
    for (int i = 0; i < (&pCreateInfo->pQueueCreateInfos[i])->queueCount; i++) {
      pCreateInfo_proto_pQueueCreateInfos_proto->add_pqueuepriorities((&pCreateInfo->pQueueCreateInfos[i])->pQueuePriorities[i]);
    }
  }
  if (pCreateInfo->enabledLayerCount) {
    pCreateInfo_proto->set_enabledlayercount(pCreateInfo->enabledLayerCount);
  }
  for (int i = 0; i < pCreateInfo->enabledLayerCount; i++) {
    pCreateInfo_proto->add_ppenabledlayernames(pCreateInfo->ppEnabledLayerNames[i]);
  }
  if (pCreateInfo->enabledExtensionCount) {
    pCreateInfo_proto->set_enabledextensioncount(pCreateInfo->enabledExtensionCount);
  }
  for (int i = 0; i < pCreateInfo->enabledExtensionCount; i++) {
    pCreateInfo_proto->add_ppenabledextensionnames(pCreateInfo->ppEnabledExtensionNames[i]);
  }
  if (pCreateInfo->pEnabledFeatures) {
    vvk::server::VkPhysicalDeviceFeatures* pCreateInfo_proto_pEnabledFeatures_proto = pCreateInfo_proto->mutable_penabledfeatures();
    pCreateInfo_proto_pEnabledFeatures_proto->set_robustbufferaccess(pCreateInfo->pEnabledFeatures->robustBufferAccess);
    pCreateInfo_proto_pEnabledFeatures_proto->set_fulldrawindexuint32(pCreateInfo->pEnabledFeatures->fullDrawIndexUint32);
    pCreateInfo_proto_pEnabledFeatures_proto->set_imagecubearray(pCreateInfo->pEnabledFeatures->imageCubeArray);
    pCreateInfo_proto_pEnabledFeatures_proto->set_independentblend(pCreateInfo->pEnabledFeatures->independentBlend);
    pCreateInfo_proto_pEnabledFeatures_proto->set_geometryshader(pCreateInfo->pEnabledFeatures->geometryShader);
    pCreateInfo_proto_pEnabledFeatures_proto->set_tessellationshader(pCreateInfo->pEnabledFeatures->tessellationShader);
    pCreateInfo_proto_pEnabledFeatures_proto->set_samplerateshading(pCreateInfo->pEnabledFeatures->sampleRateShading);
    pCreateInfo_proto_pEnabledFeatures_proto->set_dualsrcblend(pCreateInfo->pEnabledFeatures->dualSrcBlend);
    pCreateInfo_proto_pEnabledFeatures_proto->set_logicop(pCreateInfo->pEnabledFeatures->logicOp);
    pCreateInfo_proto_pEnabledFeatures_proto->set_multidrawindirect(pCreateInfo->pEnabledFeatures->multiDrawIndirect);
    pCreateInfo_proto_pEnabledFeatures_proto->set_drawindirectfirstinstance(pCreateInfo->pEnabledFeatures->drawIndirectFirstInstance);
    pCreateInfo_proto_pEnabledFeatures_proto->set_depthclamp(pCreateInfo->pEnabledFeatures->depthClamp);
    pCreateInfo_proto_pEnabledFeatures_proto->set_depthbiasclamp(pCreateInfo->pEnabledFeatures->depthBiasClamp);
    pCreateInfo_proto_pEnabledFeatures_proto->set_fillmodenonsolid(pCreateInfo->pEnabledFeatures->fillModeNonSolid);
    pCreateInfo_proto_pEnabledFeatures_proto->set_depthbounds(pCreateInfo->pEnabledFeatures->depthBounds);
    pCreateInfo_proto_pEnabledFeatures_proto->set_widelines(pCreateInfo->pEnabledFeatures->wideLines);
    pCreateInfo_proto_pEnabledFeatures_proto->set_largepoints(pCreateInfo->pEnabledFeatures->largePoints);
    pCreateInfo_proto_pEnabledFeatures_proto->set_alphatoone(pCreateInfo->pEnabledFeatures->alphaToOne);
    pCreateInfo_proto_pEnabledFeatures_proto->set_multiviewport(pCreateInfo->pEnabledFeatures->multiViewport);
    pCreateInfo_proto_pEnabledFeatures_proto->set_sampleranisotropy(pCreateInfo->pEnabledFeatures->samplerAnisotropy);
    pCreateInfo_proto_pEnabledFeatures_proto->set_texturecompressionetc2(pCreateInfo->pEnabledFeatures->textureCompressionETC2);
    pCreateInfo_proto_pEnabledFeatures_proto->set_texturecompressionastc_ldr(pCreateInfo->pEnabledFeatures->textureCompressionASTC_LDR);
    pCreateInfo_proto_pEnabledFeatures_proto->set_texturecompressionbc(pCreateInfo->pEnabledFeatures->textureCompressionBC);
    pCreateInfo_proto_pEnabledFeatures_proto->set_occlusionqueryprecise(pCreateInfo->pEnabledFeatures->occlusionQueryPrecise);
    pCreateInfo_proto_pEnabledFeatures_proto->set_pipelinestatisticsquery(pCreateInfo->pEnabledFeatures->pipelineStatisticsQuery);
    pCreateInfo_proto_pEnabledFeatures_proto->set_vertexpipelinestoresandatomics(pCreateInfo->pEnabledFeatures->vertexPipelineStoresAndAtomics);
    pCreateInfo_proto_pEnabledFeatures_proto->set_fragmentstoresandatomics(pCreateInfo->pEnabledFeatures->fragmentStoresAndAtomics);
    pCreateInfo_proto_pEnabledFeatures_proto->set_shadertessellationandgeometrypointsize(pCreateInfo->pEnabledFeatures->shaderTessellationAndGeometryPointSize);
    pCreateInfo_proto_pEnabledFeatures_proto->set_shaderimagegatherextended(pCreateInfo->pEnabledFeatures->shaderImageGatherExtended);
    pCreateInfo_proto_pEnabledFeatures_proto->set_shaderstorageimageextendedformats(pCreateInfo->pEnabledFeatures->shaderStorageImageExtendedFormats);
    pCreateInfo_proto_pEnabledFeatures_proto->set_shaderstorageimagemultisample(pCreateInfo->pEnabledFeatures->shaderStorageImageMultisample);
    pCreateInfo_proto_pEnabledFeatures_proto->set_shaderstorageimagereadwithoutformat(pCreateInfo->pEnabledFeatures->shaderStorageImageReadWithoutFormat);
    pCreateInfo_proto_pEnabledFeatures_proto->set_shaderstorageimagewritewithoutformat(pCreateInfo->pEnabledFeatures->shaderStorageImageWriteWithoutFormat);
    pCreateInfo_proto_pEnabledFeatures_proto->set_shaderuniformbufferarraydynamicindexing(pCreateInfo->pEnabledFeatures->shaderUniformBufferArrayDynamicIndexing);
    pCreateInfo_proto_pEnabledFeatures_proto->set_shadersampledimagearraydynamicindexing(pCreateInfo->pEnabledFeatures->shaderSampledImageArrayDynamicIndexing);
    pCreateInfo_proto_pEnabledFeatures_proto->set_shaderstoragebufferarraydynamicindexing(pCreateInfo->pEnabledFeatures->shaderStorageBufferArrayDynamicIndexing);
    pCreateInfo_proto_pEnabledFeatures_proto->set_shaderstorageimagearraydynamicindexing(pCreateInfo->pEnabledFeatures->shaderStorageImageArrayDynamicIndexing);
    pCreateInfo_proto_pEnabledFeatures_proto->set_shaderclipdistance(pCreateInfo->pEnabledFeatures->shaderClipDistance);
    pCreateInfo_proto_pEnabledFeatures_proto->set_shaderculldistance(pCreateInfo->pEnabledFeatures->shaderCullDistance);
    pCreateInfo_proto_pEnabledFeatures_proto->set_shaderfloat64(pCreateInfo->pEnabledFeatures->shaderFloat64);
    pCreateInfo_proto_pEnabledFeatures_proto->set_shaderint64(pCreateInfo->pEnabledFeatures->shaderInt64);
    pCreateInfo_proto_pEnabledFeatures_proto->set_shaderint16(pCreateInfo->pEnabledFeatures->shaderInt16);
    pCreateInfo_proto_pEnabledFeatures_proto->set_shaderresourceresidency(pCreateInfo->pEnabledFeatures->shaderResourceResidency);
    pCreateInfo_proto_pEnabledFeatures_proto->set_shaderresourceminlod(pCreateInfo->pEnabledFeatures->shaderResourceMinLod);
    pCreateInfo_proto_pEnabledFeatures_proto->set_sparsebinding(pCreateInfo->pEnabledFeatures->sparseBinding);
    pCreateInfo_proto_pEnabledFeatures_proto->set_sparseresidencybuffer(pCreateInfo->pEnabledFeatures->sparseResidencyBuffer);
    pCreateInfo_proto_pEnabledFeatures_proto->set_sparseresidencyimage2d(pCreateInfo->pEnabledFeatures->sparseResidencyImage2D);
    pCreateInfo_proto_pEnabledFeatures_proto->set_sparseresidencyimage3d(pCreateInfo->pEnabledFeatures->sparseResidencyImage3D);
    pCreateInfo_proto_pEnabledFeatures_proto->set_sparseresidency2samples(pCreateInfo->pEnabledFeatures->sparseResidency2Samples);
    pCreateInfo_proto_pEnabledFeatures_proto->set_sparseresidency4samples(pCreateInfo->pEnabledFeatures->sparseResidency4Samples);
    pCreateInfo_proto_pEnabledFeatures_proto->set_sparseresidency8samples(pCreateInfo->pEnabledFeatures->sparseResidency8Samples);
    pCreateInfo_proto_pEnabledFeatures_proto->set_sparseresidency16samples(pCreateInfo->pEnabledFeatures->sparseResidency16Samples);
    pCreateInfo_proto_pEnabledFeatures_proto->set_sparseresidencyaliased(pCreateInfo->pEnabledFeatures->sparseResidencyAliased);
    pCreateInfo_proto_pEnabledFeatures_proto->set_variablemultisamplerate(pCreateInfo->pEnabledFeatures->variableMultisampleRate);
    pCreateInfo_proto_pEnabledFeatures_proto->set_inheritedqueries(pCreateInfo->pEnabledFeatures->inheritedQueries);
  }
  request.mutable_vkcreatedevice()->set_pdevice(reinterpret_cast<uint64_t>(*pDevice));
  vvk::server::VvkResponse response;

  if (!stream->Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream->Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pDevice = reinterpret_cast<VkDevice>(response.vkcreatedevice().pdevice());
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkDestroyDevice(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkDestroyDevice");
  if (device) {
    request.mutable_vkdestroydevice()->set_device(reinterpret_cast<uint64_t>(device));
  }
  vvk::server::VvkResponse response;

  if (!stream->Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream->Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
VkResult PackAndCallVkEnumerateInstanceExtensionProperties(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties) {
  vvk::server::VvkRequest request;
  request.set_method("vkEnumerateInstanceExtensionProperties");
  request.mutable_vkenumerateinstanceextensionproperties()->set_playername(pLayerName);
  request.mutable_vkenumerateinstanceextensionproperties()->set_ppropertycount(*pPropertyCount);
  if (pProperties) {
    // the value we set is just a sentinel value, only its presence should be checked
    auto* unused = request.mutable_vkenumerateinstanceextensionproperties()->add_pproperties();
  } else {
    request.mutable_vkenumerateinstanceextensionproperties()->set_ppropertycount(0);
  }
  vvk::server::VvkResponse response;

  if (!stream->Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream->Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pPropertyCount = response.vkenumerateinstanceextensionproperties().ppropertycount();
  if (pProperties) {
    assert(*pPropertyCount == response.vkenumerateinstanceextensionproperties().ppropertycount());
    for (int i = 0; i < *pPropertyCount; i++) {
      VkExtensionProperties& pProperties_ref = pProperties[i];
      strncpy(pProperties_ref.extensionName, response.vkenumerateinstanceextensionproperties().pproperties(i).extensionname().c_str(), VK_MAX_EXTENSION_NAME_SIZE);
      pProperties_ref.specVersion = response.vkenumerateinstanceextensionproperties().pproperties(i).specversion();
    }
  }
  return static_cast<VkResult>(response.result());
}
VkResult PackAndCallVkEnumerateDeviceExtensionProperties(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkPhysicalDevice physicalDevice, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties) {
  vvk::server::VvkRequest request;
  request.set_method("vkEnumerateDeviceExtensionProperties");
  request.mutable_vkenumeratedeviceextensionproperties()->set_physicaldevice(reinterpret_cast<uint64_t>(physicalDevice));
  request.mutable_vkenumeratedeviceextensionproperties()->set_playername(pLayerName);
  request.mutable_vkenumeratedeviceextensionproperties()->set_ppropertycount(*pPropertyCount);
  if (pProperties) {
    // the value we set is just a sentinel value, only its presence should be checked
    auto* unused = request.mutable_vkenumeratedeviceextensionproperties()->add_pproperties();
  } else {
    request.mutable_vkenumeratedeviceextensionproperties()->set_ppropertycount(0);
  }
  vvk::server::VvkResponse response;

  if (!stream->Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream->Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pPropertyCount = response.vkenumeratedeviceextensionproperties().ppropertycount();
  if (pProperties) {
    assert(*pPropertyCount == response.vkenumeratedeviceextensionproperties().ppropertycount());
    for (int i = 0; i < *pPropertyCount; i++) {
      VkExtensionProperties& pProperties_ref = pProperties[i];
      strncpy(pProperties_ref.extensionName, response.vkenumeratedeviceextensionproperties().pproperties(i).extensionname().c_str(), VK_MAX_EXTENSION_NAME_SIZE);
      pProperties_ref.specVersion = response.vkenumeratedeviceextensionproperties().pproperties(i).specversion();
    }
  }
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkGetPhysicalDeviceMemoryProperties(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* pMemoryProperties) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetPhysicalDeviceMemoryProperties");
  request.mutable_vkgetphysicaldevicememoryproperties()->set_physicaldevice(reinterpret_cast<uint64_t>(physicalDevice));
  vvk::server::VvkResponse response;

  if (!stream->Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream->Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  VkPhysicalDeviceMemoryProperties& pMemoryProperties_ref = *pMemoryProperties;
  pMemoryProperties_ref.memoryTypeCount = response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memorytypecount();
  for (int i = 0; i < response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memorytypecount(); i++) {
    VkMemoryType &pMemoryProperties_ref_memoryTypes_i = pMemoryProperties_ref.memoryTypes[i];
    if (response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memorytypes(i).has_propertyflags()) {
      pMemoryProperties_ref_memoryTypes_i.propertyFlags = response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memorytypes(i).propertyflags();
    }
    pMemoryProperties_ref_memoryTypes_i.heapIndex = response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memorytypes(i).heapindex();
  }
  pMemoryProperties_ref.memoryHeapCount = response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memoryheapcount();
  for (int i = 0; i < response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memoryheapcount(); i++) {
    VkMemoryHeap &pMemoryProperties_ref_memoryHeaps_i = pMemoryProperties_ref.memoryHeaps[i];
    pMemoryProperties_ref_memoryHeaps_i.size = static_cast<VkDeviceSize>(response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memoryheaps(i).size());
    if (response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memoryheaps(i).has_flags()) {
      pMemoryProperties_ref_memoryHeaps_i.flags = response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memoryheaps(i).flags();
    }
  }
}
void PackAndCallVkGetPhysicalDeviceFeatures(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetPhysicalDeviceFeatures");
  request.mutable_vkgetphysicaldevicefeatures()->set_physicaldevice(reinterpret_cast<uint64_t>(physicalDevice));
  vvk::server::VvkResponse response;

  if (!stream->Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream->Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  VkPhysicalDeviceFeatures& pFeatures_ref = *pFeatures;
  pFeatures_ref.robustBufferAccess = response.vkgetphysicaldevicefeatures().pfeatures().robustbufferaccess();
  pFeatures_ref.fullDrawIndexUint32 = response.vkgetphysicaldevicefeatures().pfeatures().fulldrawindexuint32();
  pFeatures_ref.imageCubeArray = response.vkgetphysicaldevicefeatures().pfeatures().imagecubearray();
  pFeatures_ref.independentBlend = response.vkgetphysicaldevicefeatures().pfeatures().independentblend();
  pFeatures_ref.geometryShader = response.vkgetphysicaldevicefeatures().pfeatures().geometryshader();
  pFeatures_ref.tessellationShader = response.vkgetphysicaldevicefeatures().pfeatures().tessellationshader();
  pFeatures_ref.sampleRateShading = response.vkgetphysicaldevicefeatures().pfeatures().samplerateshading();
  pFeatures_ref.dualSrcBlend = response.vkgetphysicaldevicefeatures().pfeatures().dualsrcblend();
  pFeatures_ref.logicOp = response.vkgetphysicaldevicefeatures().pfeatures().logicop();
  pFeatures_ref.multiDrawIndirect = response.vkgetphysicaldevicefeatures().pfeatures().multidrawindirect();
  pFeatures_ref.drawIndirectFirstInstance = response.vkgetphysicaldevicefeatures().pfeatures().drawindirectfirstinstance();
  pFeatures_ref.depthClamp = response.vkgetphysicaldevicefeatures().pfeatures().depthclamp();
  pFeatures_ref.depthBiasClamp = response.vkgetphysicaldevicefeatures().pfeatures().depthbiasclamp();
  pFeatures_ref.fillModeNonSolid = response.vkgetphysicaldevicefeatures().pfeatures().fillmodenonsolid();
  pFeatures_ref.depthBounds = response.vkgetphysicaldevicefeatures().pfeatures().depthbounds();
  pFeatures_ref.wideLines = response.vkgetphysicaldevicefeatures().pfeatures().widelines();
  pFeatures_ref.largePoints = response.vkgetphysicaldevicefeatures().pfeatures().largepoints();
  pFeatures_ref.alphaToOne = response.vkgetphysicaldevicefeatures().pfeatures().alphatoone();
  pFeatures_ref.multiViewport = response.vkgetphysicaldevicefeatures().pfeatures().multiviewport();
  pFeatures_ref.samplerAnisotropy = response.vkgetphysicaldevicefeatures().pfeatures().sampleranisotropy();
  pFeatures_ref.textureCompressionETC2 = response.vkgetphysicaldevicefeatures().pfeatures().texturecompressionetc2();
  pFeatures_ref.textureCompressionASTC_LDR = response.vkgetphysicaldevicefeatures().pfeatures().texturecompressionastc_ldr();
  pFeatures_ref.textureCompressionBC = response.vkgetphysicaldevicefeatures().pfeatures().texturecompressionbc();
  pFeatures_ref.occlusionQueryPrecise = response.vkgetphysicaldevicefeatures().pfeatures().occlusionqueryprecise();
  pFeatures_ref.pipelineStatisticsQuery = response.vkgetphysicaldevicefeatures().pfeatures().pipelinestatisticsquery();
  pFeatures_ref.vertexPipelineStoresAndAtomics = response.vkgetphysicaldevicefeatures().pfeatures().vertexpipelinestoresandatomics();
  pFeatures_ref.fragmentStoresAndAtomics = response.vkgetphysicaldevicefeatures().pfeatures().fragmentstoresandatomics();
  pFeatures_ref.shaderTessellationAndGeometryPointSize = response.vkgetphysicaldevicefeatures().pfeatures().shadertessellationandgeometrypointsize();
  pFeatures_ref.shaderImageGatherExtended = response.vkgetphysicaldevicefeatures().pfeatures().shaderimagegatherextended();
  pFeatures_ref.shaderStorageImageExtendedFormats = response.vkgetphysicaldevicefeatures().pfeatures().shaderstorageimageextendedformats();
  pFeatures_ref.shaderStorageImageMultisample = response.vkgetphysicaldevicefeatures().pfeatures().shaderstorageimagemultisample();
  pFeatures_ref.shaderStorageImageReadWithoutFormat = response.vkgetphysicaldevicefeatures().pfeatures().shaderstorageimagereadwithoutformat();
  pFeatures_ref.shaderStorageImageWriteWithoutFormat = response.vkgetphysicaldevicefeatures().pfeatures().shaderstorageimagewritewithoutformat();
  pFeatures_ref.shaderUniformBufferArrayDynamicIndexing = response.vkgetphysicaldevicefeatures().pfeatures().shaderuniformbufferarraydynamicindexing();
  pFeatures_ref.shaderSampledImageArrayDynamicIndexing = response.vkgetphysicaldevicefeatures().pfeatures().shadersampledimagearraydynamicindexing();
  pFeatures_ref.shaderStorageBufferArrayDynamicIndexing = response.vkgetphysicaldevicefeatures().pfeatures().shaderstoragebufferarraydynamicindexing();
  pFeatures_ref.shaderStorageImageArrayDynamicIndexing = response.vkgetphysicaldevicefeatures().pfeatures().shaderstorageimagearraydynamicindexing();
  pFeatures_ref.shaderClipDistance = response.vkgetphysicaldevicefeatures().pfeatures().shaderclipdistance();
  pFeatures_ref.shaderCullDistance = response.vkgetphysicaldevicefeatures().pfeatures().shaderculldistance();
  pFeatures_ref.shaderFloat64 = response.vkgetphysicaldevicefeatures().pfeatures().shaderfloat64();
  pFeatures_ref.shaderInt64 = response.vkgetphysicaldevicefeatures().pfeatures().shaderint64();
  pFeatures_ref.shaderInt16 = response.vkgetphysicaldevicefeatures().pfeatures().shaderint16();
  pFeatures_ref.shaderResourceResidency = response.vkgetphysicaldevicefeatures().pfeatures().shaderresourceresidency();
  pFeatures_ref.shaderResourceMinLod = response.vkgetphysicaldevicefeatures().pfeatures().shaderresourceminlod();
  pFeatures_ref.sparseBinding = response.vkgetphysicaldevicefeatures().pfeatures().sparsebinding();
  pFeatures_ref.sparseResidencyBuffer = response.vkgetphysicaldevicefeatures().pfeatures().sparseresidencybuffer();
  pFeatures_ref.sparseResidencyImage2D = response.vkgetphysicaldevicefeatures().pfeatures().sparseresidencyimage2d();
  pFeatures_ref.sparseResidencyImage3D = response.vkgetphysicaldevicefeatures().pfeatures().sparseresidencyimage3d();
  pFeatures_ref.sparseResidency2Samples = response.vkgetphysicaldevicefeatures().pfeatures().sparseresidency2samples();
  pFeatures_ref.sparseResidency4Samples = response.vkgetphysicaldevicefeatures().pfeatures().sparseresidency4samples();
  pFeatures_ref.sparseResidency8Samples = response.vkgetphysicaldevicefeatures().pfeatures().sparseresidency8samples();
  pFeatures_ref.sparseResidency16Samples = response.vkgetphysicaldevicefeatures().pfeatures().sparseresidency16samples();
  pFeatures_ref.sparseResidencyAliased = response.vkgetphysicaldevicefeatures().pfeatures().sparseresidencyaliased();
  pFeatures_ref.variableMultisampleRate = response.vkgetphysicaldevicefeatures().pfeatures().variablemultisamplerate();
  pFeatures_ref.inheritedQueries = response.vkgetphysicaldevicefeatures().pfeatures().inheritedqueries();
}
}  // namespace vvk

