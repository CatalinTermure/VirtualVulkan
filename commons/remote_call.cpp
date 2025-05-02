// GENERATED FILE - DO NOT EDIT
// clang-format off
#include "remote_call.h"

#include "synchronized_bidi_stream.h"

#include <vulkan/vulkan.h>
#include <spdlog/spdlog.h>
#include "vvk_server.grpc.pb.h"
#include <cstring>

namespace vvk {
namespace {
}
VkResult PackAndCallVkCreateInstance(VvkCommandClientBidiStream& stream, const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance) {
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
  const size_t pCreateInfo_proto_ppEnabledLayerNames_length = pCreateInfo->enabledLayerCount;
  for (int ppEnabledLayerNames_indx = 0; ppEnabledLayerNames_indx < pCreateInfo_proto_ppEnabledLayerNames_length; ppEnabledLayerNames_indx++) {
    pCreateInfo_proto->add_ppenabledlayernames(pCreateInfo->ppEnabledLayerNames[ppEnabledLayerNames_indx]);
  }
  if (pCreateInfo->enabledExtensionCount) {
    pCreateInfo_proto->set_enabledextensioncount(pCreateInfo->enabledExtensionCount);
  }
  const size_t pCreateInfo_proto_ppEnabledExtensionNames_length = pCreateInfo->enabledExtensionCount;
  for (int ppEnabledExtensionNames_indx = 0; ppEnabledExtensionNames_indx < pCreateInfo_proto_ppEnabledExtensionNames_length; ppEnabledExtensionNames_indx++) {
    pCreateInfo_proto->add_ppenabledextensionnames(pCreateInfo->ppEnabledExtensionNames[ppEnabledExtensionNames_indx]);
  }
  request.mutable_vkcreateinstance()->set_pinstance(reinterpret_cast<uint64_t>(*pInstance));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pInstance = reinterpret_cast<VkInstance>(response.vkcreateinstance().pinstance());
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkDestroyInstance(VvkCommandClientBidiStream& stream, VkInstance instance, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkDestroyInstance");
  if (instance) {
    request.mutable_vkdestroyinstance()->set_instance(reinterpret_cast<uint64_t>(instance));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
VkResult PackAndCallVkEnumeratePhysicalDevices(VvkCommandClientBidiStream& stream, VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices) {
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

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pPhysicalDeviceCount = response.vkenumeratephysicaldevices().pphysicaldevicecount();
  if (pPhysicalDevices) {
    assert(*pPhysicalDeviceCount == response.vkenumeratephysicaldevices().pphysicaldevicecount());
    for (int pPhysicalDevices_indx = 0; pPhysicalDevices_indx < *pPhysicalDeviceCount; pPhysicalDevices_indx++) {
      pPhysicalDevices[pPhysicalDevices_indx] = reinterpret_cast<VkPhysicalDevice>(response.vkenumeratephysicaldevices().pphysicaldevices(pPhysicalDevices_indx));
    }
  }
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkGetPhysicalDeviceProperties(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetPhysicalDeviceProperties");
  request.mutable_vkgetphysicaldeviceproperties()->set_physicaldevice(reinterpret_cast<uint64_t>(physicalDevice));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  VkPhysicalDeviceProperties& pProperties_ref = *pProperties;
  pProperties_ref.apiVersion = response.vkgetphysicaldeviceproperties().pproperties().apiversion();
  pProperties_ref.driverVersion = response.vkgetphysicaldeviceproperties().pproperties().driverversion();
  pProperties_ref.vendorID = response.vkgetphysicaldeviceproperties().pproperties().vendorid();
  pProperties_ref.deviceID = response.vkgetphysicaldeviceproperties().pproperties().deviceid();
  pProperties_ref.deviceType = static_cast<VkPhysicalDeviceType>(response.vkgetphysicaldeviceproperties().pproperties().devicetype());
  strncpy(pProperties_ref.deviceName, response.vkgetphysicaldeviceproperties().pproperties().devicename().c_str(), VK_MAX_PHYSICAL_DEVICE_NAME_SIZE);
  for (int pipelineCacheUUID_indx = 0; pipelineCacheUUID_indx < VK_UUID_SIZE; pipelineCacheUUID_indx++) {
    pProperties_ref.pipelineCacheUUID[pipelineCacheUUID_indx] = static_cast<uint8_t>(response.vkgetphysicaldeviceproperties().pproperties().pipelinecacheuuid(pipelineCacheUUID_indx));
  }
  VkPhysicalDeviceLimits &pProperties_ref_limits = pProperties_ref.limits;
  pProperties_ref_limits.maxImageDimension1D = response.vkgetphysicaldeviceproperties().pproperties().limits().maximagedimension1d();
  pProperties_ref_limits.maxImageDimension2D = response.vkgetphysicaldeviceproperties().pproperties().limits().maximagedimension2d();
  pProperties_ref_limits.maxImageDimension3D = response.vkgetphysicaldeviceproperties().pproperties().limits().maximagedimension3d();
  pProperties_ref_limits.maxImageDimensionCube = response.vkgetphysicaldeviceproperties().pproperties().limits().maximagedimensioncube();
  pProperties_ref_limits.maxImageArrayLayers = response.vkgetphysicaldeviceproperties().pproperties().limits().maximagearraylayers();
  pProperties_ref_limits.maxTexelBufferElements = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtexelbufferelements();
  pProperties_ref_limits.maxUniformBufferRange = response.vkgetphysicaldeviceproperties().pproperties().limits().maxuniformbufferrange();
  pProperties_ref_limits.maxStorageBufferRange = response.vkgetphysicaldeviceproperties().pproperties().limits().maxstoragebufferrange();
  pProperties_ref_limits.maxPushConstantsSize = response.vkgetphysicaldeviceproperties().pproperties().limits().maxpushconstantssize();
  pProperties_ref_limits.maxMemoryAllocationCount = response.vkgetphysicaldeviceproperties().pproperties().limits().maxmemoryallocationcount();
  pProperties_ref_limits.maxSamplerAllocationCount = response.vkgetphysicaldeviceproperties().pproperties().limits().maxsamplerallocationcount();
  pProperties_ref_limits.bufferImageGranularity = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties().pproperties().limits().bufferimagegranularity());
  pProperties_ref_limits.sparseAddressSpaceSize = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties().pproperties().limits().sparseaddressspacesize());
  pProperties_ref_limits.maxBoundDescriptorSets = response.vkgetphysicaldeviceproperties().pproperties().limits().maxbounddescriptorsets();
  pProperties_ref_limits.maxPerStageDescriptorSamplers = response.vkgetphysicaldeviceproperties().pproperties().limits().maxperstagedescriptorsamplers();
  pProperties_ref_limits.maxPerStageDescriptorUniformBuffers = response.vkgetphysicaldeviceproperties().pproperties().limits().maxperstagedescriptoruniformbuffers();
  pProperties_ref_limits.maxPerStageDescriptorStorageBuffers = response.vkgetphysicaldeviceproperties().pproperties().limits().maxperstagedescriptorstoragebuffers();
  pProperties_ref_limits.maxPerStageDescriptorSampledImages = response.vkgetphysicaldeviceproperties().pproperties().limits().maxperstagedescriptorsampledimages();
  pProperties_ref_limits.maxPerStageDescriptorStorageImages = response.vkgetphysicaldeviceproperties().pproperties().limits().maxperstagedescriptorstorageimages();
  pProperties_ref_limits.maxPerStageDescriptorInputAttachments = response.vkgetphysicaldeviceproperties().pproperties().limits().maxperstagedescriptorinputattachments();
  pProperties_ref_limits.maxPerStageResources = response.vkgetphysicaldeviceproperties().pproperties().limits().maxperstageresources();
  pProperties_ref_limits.maxDescriptorSetSamplers = response.vkgetphysicaldeviceproperties().pproperties().limits().maxdescriptorsetsamplers();
  pProperties_ref_limits.maxDescriptorSetUniformBuffers = response.vkgetphysicaldeviceproperties().pproperties().limits().maxdescriptorsetuniformbuffers();
  pProperties_ref_limits.maxDescriptorSetUniformBuffersDynamic = response.vkgetphysicaldeviceproperties().pproperties().limits().maxdescriptorsetuniformbuffersdynamic();
  pProperties_ref_limits.maxDescriptorSetStorageBuffers = response.vkgetphysicaldeviceproperties().pproperties().limits().maxdescriptorsetstoragebuffers();
  pProperties_ref_limits.maxDescriptorSetStorageBuffersDynamic = response.vkgetphysicaldeviceproperties().pproperties().limits().maxdescriptorsetstoragebuffersdynamic();
  pProperties_ref_limits.maxDescriptorSetSampledImages = response.vkgetphysicaldeviceproperties().pproperties().limits().maxdescriptorsetsampledimages();
  pProperties_ref_limits.maxDescriptorSetStorageImages = response.vkgetphysicaldeviceproperties().pproperties().limits().maxdescriptorsetstorageimages();
  pProperties_ref_limits.maxDescriptorSetInputAttachments = response.vkgetphysicaldeviceproperties().pproperties().limits().maxdescriptorsetinputattachments();
  pProperties_ref_limits.maxVertexInputAttributes = response.vkgetphysicaldeviceproperties().pproperties().limits().maxvertexinputattributes();
  pProperties_ref_limits.maxVertexInputBindings = response.vkgetphysicaldeviceproperties().pproperties().limits().maxvertexinputbindings();
  pProperties_ref_limits.maxVertexInputAttributeOffset = response.vkgetphysicaldeviceproperties().pproperties().limits().maxvertexinputattributeoffset();
  pProperties_ref_limits.maxVertexInputBindingStride = response.vkgetphysicaldeviceproperties().pproperties().limits().maxvertexinputbindingstride();
  pProperties_ref_limits.maxVertexOutputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxvertexoutputcomponents();
  pProperties_ref_limits.maxTessellationGenerationLevel = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtessellationgenerationlevel();
  pProperties_ref_limits.maxTessellationPatchSize = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtessellationpatchsize();
  pProperties_ref_limits.maxTessellationControlPerVertexInputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtessellationcontrolpervertexinputcomponents();
  pProperties_ref_limits.maxTessellationControlPerVertexOutputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtessellationcontrolpervertexoutputcomponents();
  pProperties_ref_limits.maxTessellationControlPerPatchOutputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtessellationcontrolperpatchoutputcomponents();
  pProperties_ref_limits.maxTessellationControlTotalOutputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtessellationcontroltotaloutputcomponents();
  pProperties_ref_limits.maxTessellationEvaluationInputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtessellationevaluationinputcomponents();
  pProperties_ref_limits.maxTessellationEvaluationOutputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtessellationevaluationoutputcomponents();
  pProperties_ref_limits.maxGeometryShaderInvocations = response.vkgetphysicaldeviceproperties().pproperties().limits().maxgeometryshaderinvocations();
  pProperties_ref_limits.maxGeometryInputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxgeometryinputcomponents();
  pProperties_ref_limits.maxGeometryOutputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxgeometryoutputcomponents();
  pProperties_ref_limits.maxGeometryOutputVertices = response.vkgetphysicaldeviceproperties().pproperties().limits().maxgeometryoutputvertices();
  pProperties_ref_limits.maxGeometryTotalOutputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxgeometrytotaloutputcomponents();
  pProperties_ref_limits.maxFragmentInputComponents = response.vkgetphysicaldeviceproperties().pproperties().limits().maxfragmentinputcomponents();
  pProperties_ref_limits.maxFragmentOutputAttachments = response.vkgetphysicaldeviceproperties().pproperties().limits().maxfragmentoutputattachments();
  pProperties_ref_limits.maxFragmentDualSrcAttachments = response.vkgetphysicaldeviceproperties().pproperties().limits().maxfragmentdualsrcattachments();
  pProperties_ref_limits.maxFragmentCombinedOutputResources = response.vkgetphysicaldeviceproperties().pproperties().limits().maxfragmentcombinedoutputresources();
  pProperties_ref_limits.maxComputeSharedMemorySize = response.vkgetphysicaldeviceproperties().pproperties().limits().maxcomputesharedmemorysize();
  for (int maxComputeWorkGroupCount_indx = 0; maxComputeWorkGroupCount_indx < 3; maxComputeWorkGroupCount_indx++) {
    pProperties_ref_limits.maxComputeWorkGroupCount[maxComputeWorkGroupCount_indx] = response.vkgetphysicaldeviceproperties().pproperties().limits().maxcomputeworkgroupcount(maxComputeWorkGroupCount_indx);
  }
  pProperties_ref_limits.maxComputeWorkGroupInvocations = response.vkgetphysicaldeviceproperties().pproperties().limits().maxcomputeworkgroupinvocations();
  for (int maxComputeWorkGroupSize_indx = 0; maxComputeWorkGroupSize_indx < 3; maxComputeWorkGroupSize_indx++) {
    pProperties_ref_limits.maxComputeWorkGroupSize[maxComputeWorkGroupSize_indx] = response.vkgetphysicaldeviceproperties().pproperties().limits().maxcomputeworkgroupsize(maxComputeWorkGroupSize_indx);
  }
  pProperties_ref_limits.subPixelPrecisionBits = response.vkgetphysicaldeviceproperties().pproperties().limits().subpixelprecisionbits();
  pProperties_ref_limits.subTexelPrecisionBits = response.vkgetphysicaldeviceproperties().pproperties().limits().subtexelprecisionbits();
  pProperties_ref_limits.mipmapPrecisionBits = response.vkgetphysicaldeviceproperties().pproperties().limits().mipmapprecisionbits();
  pProperties_ref_limits.maxDrawIndexedIndexValue = response.vkgetphysicaldeviceproperties().pproperties().limits().maxdrawindexedindexvalue();
  pProperties_ref_limits.maxDrawIndirectCount = response.vkgetphysicaldeviceproperties().pproperties().limits().maxdrawindirectcount();
  pProperties_ref_limits.maxSamplerLodBias = response.vkgetphysicaldeviceproperties().pproperties().limits().maxsamplerlodbias();
  pProperties_ref_limits.maxSamplerAnisotropy = response.vkgetphysicaldeviceproperties().pproperties().limits().maxsampleranisotropy();
  pProperties_ref_limits.maxViewports = response.vkgetphysicaldeviceproperties().pproperties().limits().maxviewports();
  for (int maxViewportDimensions_indx = 0; maxViewportDimensions_indx < 2; maxViewportDimensions_indx++) {
    pProperties_ref_limits.maxViewportDimensions[maxViewportDimensions_indx] = response.vkgetphysicaldeviceproperties().pproperties().limits().maxviewportdimensions(maxViewportDimensions_indx);
  }
  for (int viewportBoundsRange_indx = 0; viewportBoundsRange_indx < 2; viewportBoundsRange_indx++) {
    pProperties_ref_limits.viewportBoundsRange[viewportBoundsRange_indx] = response.vkgetphysicaldeviceproperties().pproperties().limits().viewportboundsrange(viewportBoundsRange_indx);
  }
  pProperties_ref_limits.viewportSubPixelBits = response.vkgetphysicaldeviceproperties().pproperties().limits().viewportsubpixelbits();
  pProperties_ref_limits.minMemoryMapAlignment = response.vkgetphysicaldeviceproperties().pproperties().limits().minmemorymapalignment();
  pProperties_ref_limits.minTexelBufferOffsetAlignment = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties().pproperties().limits().mintexelbufferoffsetalignment());
  pProperties_ref_limits.minUniformBufferOffsetAlignment = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties().pproperties().limits().minuniformbufferoffsetalignment());
  pProperties_ref_limits.minStorageBufferOffsetAlignment = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties().pproperties().limits().minstoragebufferoffsetalignment());
  pProperties_ref_limits.minTexelOffset = response.vkgetphysicaldeviceproperties().pproperties().limits().mintexeloffset();
  pProperties_ref_limits.maxTexelOffset = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtexeloffset();
  pProperties_ref_limits.minTexelGatherOffset = response.vkgetphysicaldeviceproperties().pproperties().limits().mintexelgatheroffset();
  pProperties_ref_limits.maxTexelGatherOffset = response.vkgetphysicaldeviceproperties().pproperties().limits().maxtexelgatheroffset();
  pProperties_ref_limits.minInterpolationOffset = response.vkgetphysicaldeviceproperties().pproperties().limits().mininterpolationoffset();
  pProperties_ref_limits.maxInterpolationOffset = response.vkgetphysicaldeviceproperties().pproperties().limits().maxinterpolationoffset();
  pProperties_ref_limits.subPixelInterpolationOffsetBits = response.vkgetphysicaldeviceproperties().pproperties().limits().subpixelinterpolationoffsetbits();
  pProperties_ref_limits.maxFramebufferWidth = response.vkgetphysicaldeviceproperties().pproperties().limits().maxframebufferwidth();
  pProperties_ref_limits.maxFramebufferHeight = response.vkgetphysicaldeviceproperties().pproperties().limits().maxframebufferheight();
  pProperties_ref_limits.maxFramebufferLayers = response.vkgetphysicaldeviceproperties().pproperties().limits().maxframebufferlayers();
  if (response.vkgetphysicaldeviceproperties().pproperties().limits().has_framebuffercolorsamplecounts()) {
    pProperties_ref_limits.framebufferColorSampleCounts = static_cast<VkSampleCountFlags>(response.vkgetphysicaldeviceproperties().pproperties().limits().framebuffercolorsamplecounts());
  } else {
    pProperties_ref_limits.framebufferColorSampleCounts = VkSampleCountFlags{};
  }
  if (response.vkgetphysicaldeviceproperties().pproperties().limits().has_framebufferdepthsamplecounts()) {
    pProperties_ref_limits.framebufferDepthSampleCounts = static_cast<VkSampleCountFlags>(response.vkgetphysicaldeviceproperties().pproperties().limits().framebufferdepthsamplecounts());
  } else {
    pProperties_ref_limits.framebufferDepthSampleCounts = VkSampleCountFlags{};
  }
  if (response.vkgetphysicaldeviceproperties().pproperties().limits().has_framebufferstencilsamplecounts()) {
    pProperties_ref_limits.framebufferStencilSampleCounts = static_cast<VkSampleCountFlags>(response.vkgetphysicaldeviceproperties().pproperties().limits().framebufferstencilsamplecounts());
  } else {
    pProperties_ref_limits.framebufferStencilSampleCounts = VkSampleCountFlags{};
  }
  if (response.vkgetphysicaldeviceproperties().pproperties().limits().has_framebuffernoattachmentssamplecounts()) {
    pProperties_ref_limits.framebufferNoAttachmentsSampleCounts = static_cast<VkSampleCountFlags>(response.vkgetphysicaldeviceproperties().pproperties().limits().framebuffernoattachmentssamplecounts());
  } else {
    pProperties_ref_limits.framebufferNoAttachmentsSampleCounts = VkSampleCountFlags{};
  }
  pProperties_ref_limits.maxColorAttachments = response.vkgetphysicaldeviceproperties().pproperties().limits().maxcolorattachments();
  if (response.vkgetphysicaldeviceproperties().pproperties().limits().has_sampledimagecolorsamplecounts()) {
    pProperties_ref_limits.sampledImageColorSampleCounts = static_cast<VkSampleCountFlags>(response.vkgetphysicaldeviceproperties().pproperties().limits().sampledimagecolorsamplecounts());
  } else {
    pProperties_ref_limits.sampledImageColorSampleCounts = VkSampleCountFlags{};
  }
  if (response.vkgetphysicaldeviceproperties().pproperties().limits().has_sampledimageintegersamplecounts()) {
    pProperties_ref_limits.sampledImageIntegerSampleCounts = static_cast<VkSampleCountFlags>(response.vkgetphysicaldeviceproperties().pproperties().limits().sampledimageintegersamplecounts());
  } else {
    pProperties_ref_limits.sampledImageIntegerSampleCounts = VkSampleCountFlags{};
  }
  if (response.vkgetphysicaldeviceproperties().pproperties().limits().has_sampledimagedepthsamplecounts()) {
    pProperties_ref_limits.sampledImageDepthSampleCounts = static_cast<VkSampleCountFlags>(response.vkgetphysicaldeviceproperties().pproperties().limits().sampledimagedepthsamplecounts());
  } else {
    pProperties_ref_limits.sampledImageDepthSampleCounts = VkSampleCountFlags{};
  }
  if (response.vkgetphysicaldeviceproperties().pproperties().limits().has_sampledimagestencilsamplecounts()) {
    pProperties_ref_limits.sampledImageStencilSampleCounts = static_cast<VkSampleCountFlags>(response.vkgetphysicaldeviceproperties().pproperties().limits().sampledimagestencilsamplecounts());
  } else {
    pProperties_ref_limits.sampledImageStencilSampleCounts = VkSampleCountFlags{};
  }
  if (response.vkgetphysicaldeviceproperties().pproperties().limits().has_storageimagesamplecounts()) {
    pProperties_ref_limits.storageImageSampleCounts = static_cast<VkSampleCountFlags>(response.vkgetphysicaldeviceproperties().pproperties().limits().storageimagesamplecounts());
  } else {
    pProperties_ref_limits.storageImageSampleCounts = VkSampleCountFlags{};
  }
  pProperties_ref_limits.maxSampleMaskWords = response.vkgetphysicaldeviceproperties().pproperties().limits().maxsamplemaskwords();
  pProperties_ref_limits.timestampComputeAndGraphics = response.vkgetphysicaldeviceproperties().pproperties().limits().timestampcomputeandgraphics();
  pProperties_ref_limits.timestampPeriod = response.vkgetphysicaldeviceproperties().pproperties().limits().timestampperiod();
  pProperties_ref_limits.maxClipDistances = response.vkgetphysicaldeviceproperties().pproperties().limits().maxclipdistances();
  pProperties_ref_limits.maxCullDistances = response.vkgetphysicaldeviceproperties().pproperties().limits().maxculldistances();
  pProperties_ref_limits.maxCombinedClipAndCullDistances = response.vkgetphysicaldeviceproperties().pproperties().limits().maxcombinedclipandculldistances();
  pProperties_ref_limits.discreteQueuePriorities = response.vkgetphysicaldeviceproperties().pproperties().limits().discretequeuepriorities();
  for (int pointSizeRange_indx = 0; pointSizeRange_indx < 2; pointSizeRange_indx++) {
    pProperties_ref_limits.pointSizeRange[pointSizeRange_indx] = response.vkgetphysicaldeviceproperties().pproperties().limits().pointsizerange(pointSizeRange_indx);
  }
  for (int lineWidthRange_indx = 0; lineWidthRange_indx < 2; lineWidthRange_indx++) {
    pProperties_ref_limits.lineWidthRange[lineWidthRange_indx] = response.vkgetphysicaldeviceproperties().pproperties().limits().linewidthrange(lineWidthRange_indx);
  }
  pProperties_ref_limits.pointSizeGranularity = response.vkgetphysicaldeviceproperties().pproperties().limits().pointsizegranularity();
  pProperties_ref_limits.lineWidthGranularity = response.vkgetphysicaldeviceproperties().pproperties().limits().linewidthgranularity();
  pProperties_ref_limits.strictLines = response.vkgetphysicaldeviceproperties().pproperties().limits().strictlines();
  pProperties_ref_limits.standardSampleLocations = response.vkgetphysicaldeviceproperties().pproperties().limits().standardsamplelocations();
  pProperties_ref_limits.optimalBufferCopyOffsetAlignment = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties().pproperties().limits().optimalbuffercopyoffsetalignment());
  pProperties_ref_limits.optimalBufferCopyRowPitchAlignment = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties().pproperties().limits().optimalbuffercopyrowpitchalignment());
  pProperties_ref_limits.nonCoherentAtomSize = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties().pproperties().limits().noncoherentatomsize());
  VkPhysicalDeviceSparseProperties &pProperties_ref_sparseProperties = pProperties_ref.sparseProperties;
  pProperties_ref_sparseProperties.residencyStandard2DBlockShape = response.vkgetphysicaldeviceproperties().pproperties().sparseproperties().residencystandard2dblockshape();
  pProperties_ref_sparseProperties.residencyStandard2DMultisampleBlockShape = response.vkgetphysicaldeviceproperties().pproperties().sparseproperties().residencystandard2dmultisampleblockshape();
  pProperties_ref_sparseProperties.residencyStandard3DBlockShape = response.vkgetphysicaldeviceproperties().pproperties().sparseproperties().residencystandard3dblockshape();
  pProperties_ref_sparseProperties.residencyAlignedMipSize = response.vkgetphysicaldeviceproperties().pproperties().sparseproperties().residencyalignedmipsize();
  pProperties_ref_sparseProperties.residencyNonResidentStrict = response.vkgetphysicaldeviceproperties().pproperties().sparseproperties().residencynonresidentstrict();
}
void PackAndCallVkGetPhysicalDeviceFormatProperties(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties* pFormatProperties) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetPhysicalDeviceFormatProperties");
  request.mutable_vkgetphysicaldeviceformatproperties()->set_physicaldevice(reinterpret_cast<uint64_t>(physicalDevice));
  request.mutable_vkgetphysicaldeviceformatproperties()->set_format(static_cast<vvk::server::VkFormat>(format));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  VkFormatProperties& pFormatProperties_ref = *pFormatProperties;
  if (response.vkgetphysicaldeviceformatproperties().pformatproperties().has_lineartilingfeatures()) {
    pFormatProperties_ref.linearTilingFeatures = static_cast<VkFormatFeatureFlags>(response.vkgetphysicaldeviceformatproperties().pformatproperties().lineartilingfeatures());
  } else {
    pFormatProperties_ref.linearTilingFeatures = VkFormatFeatureFlags{};
  }
  if (response.vkgetphysicaldeviceformatproperties().pformatproperties().has_optimaltilingfeatures()) {
    pFormatProperties_ref.optimalTilingFeatures = static_cast<VkFormatFeatureFlags>(response.vkgetphysicaldeviceformatproperties().pformatproperties().optimaltilingfeatures());
  } else {
    pFormatProperties_ref.optimalTilingFeatures = VkFormatFeatureFlags{};
  }
  if (response.vkgetphysicaldeviceformatproperties().pformatproperties().has_bufferfeatures()) {
    pFormatProperties_ref.bufferFeatures = static_cast<VkFormatFeatureFlags>(response.vkgetphysicaldeviceformatproperties().pformatproperties().bufferfeatures());
  } else {
    pFormatProperties_ref.bufferFeatures = VkFormatFeatureFlags{};
  }
}
VkResult PackAndCallVkCreateDevice(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice) {
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
  const size_t pCreateInfo_proto_pQueueCreateInfos_length = pCreateInfo->queueCreateInfoCount;
  for (int pQueueCreateInfos_indx = 0; pQueueCreateInfos_indx < pCreateInfo_proto_pQueueCreateInfos_length; pQueueCreateInfos_indx++) {
    vvk::server::VkDeviceQueueCreateInfo* pCreateInfo_proto_pQueueCreateInfos_proto = pCreateInfo_proto->add_pqueuecreateinfos();
    if ((&pCreateInfo->pQueueCreateInfos[pQueueCreateInfos_indx])->pNext) {
      // pNext chains are currently not supported
    }
    if ((&pCreateInfo->pQueueCreateInfos[pQueueCreateInfos_indx])->flags) {
      pCreateInfo_proto_pQueueCreateInfos_proto->set_flags((&pCreateInfo->pQueueCreateInfos[pQueueCreateInfos_indx])->flags);
    }
    pCreateInfo_proto_pQueueCreateInfos_proto->set_queuefamilyindex((&pCreateInfo->pQueueCreateInfos[pQueueCreateInfos_indx])->queueFamilyIndex);
    pCreateInfo_proto_pQueueCreateInfos_proto->set_queuecount((&pCreateInfo->pQueueCreateInfos[pQueueCreateInfos_indx])->queueCount);
    const size_t pCreateInfo_proto_pQueueCreateInfos_proto_pQueuePriorities_length = (&pCreateInfo->pQueueCreateInfos[pQueueCreateInfos_indx])->queueCount;
    for (int pQueuePriorities_indx = 0; pQueuePriorities_indx < pCreateInfo_proto_pQueueCreateInfos_proto_pQueuePriorities_length; pQueuePriorities_indx++) {
      pCreateInfo_proto_pQueueCreateInfos_proto->add_pqueuepriorities((&pCreateInfo->pQueueCreateInfos[pQueueCreateInfos_indx])->pQueuePriorities[pQueuePriorities_indx]);
    }
  }
  if (pCreateInfo->enabledLayerCount) {
    pCreateInfo_proto->set_enabledlayercount(pCreateInfo->enabledLayerCount);
  }
  const size_t pCreateInfo_proto_ppEnabledLayerNames_length = pCreateInfo->enabledLayerCount;
  for (int ppEnabledLayerNames_indx = 0; ppEnabledLayerNames_indx < pCreateInfo_proto_ppEnabledLayerNames_length; ppEnabledLayerNames_indx++) {
    pCreateInfo_proto->add_ppenabledlayernames(pCreateInfo->ppEnabledLayerNames[ppEnabledLayerNames_indx]);
  }
  if (pCreateInfo->enabledExtensionCount) {
    pCreateInfo_proto->set_enabledextensioncount(pCreateInfo->enabledExtensionCount);
  }
  const size_t pCreateInfo_proto_ppEnabledExtensionNames_length = pCreateInfo->enabledExtensionCount;
  for (int ppEnabledExtensionNames_indx = 0; ppEnabledExtensionNames_indx < pCreateInfo_proto_ppEnabledExtensionNames_length; ppEnabledExtensionNames_indx++) {
    pCreateInfo_proto->add_ppenabledextensionnames(pCreateInfo->ppEnabledExtensionNames[ppEnabledExtensionNames_indx]);
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

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pDevice = reinterpret_cast<VkDevice>(response.vkcreatedevice().pdevice());
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkDestroyDevice(VvkCommandClientBidiStream& stream, VkDevice device, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkDestroyDevice");
  if (device) {
    request.mutable_vkdestroydevice()->set_device(reinterpret_cast<uint64_t>(device));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
VkResult PackAndCallVkEnumerateInstanceExtensionProperties(VvkCommandClientBidiStream& stream, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties) {
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

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pPropertyCount = response.vkenumerateinstanceextensionproperties().ppropertycount();
  if (pProperties) {
    assert(*pPropertyCount == response.vkenumerateinstanceextensionproperties().ppropertycount());
    for (int pProperties_indx = 0; pProperties_indx < *pPropertyCount; pProperties_indx++) {
      VkExtensionProperties& pProperties_ref = pProperties[pProperties_indx];
      strncpy(pProperties_ref.extensionName, response.vkenumerateinstanceextensionproperties().pproperties(pProperties_indx).extensionname().c_str(), VK_MAX_EXTENSION_NAME_SIZE);
      pProperties_ref.specVersion = response.vkenumerateinstanceextensionproperties().pproperties(pProperties_indx).specversion();
    }
  }
  return static_cast<VkResult>(response.result());
}
VkResult PackAndCallVkEnumerateDeviceExtensionProperties(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties) {
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

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pPropertyCount = response.vkenumeratedeviceextensionproperties().ppropertycount();
  if (pProperties) {
    assert(*pPropertyCount == response.vkenumeratedeviceextensionproperties().ppropertycount());
    for (int pProperties_indx = 0; pProperties_indx < *pPropertyCount; pProperties_indx++) {
      VkExtensionProperties& pProperties_ref = pProperties[pProperties_indx];
      strncpy(pProperties_ref.extensionName, response.vkenumeratedeviceextensionproperties().pproperties(pProperties_indx).extensionname().c_str(), VK_MAX_EXTENSION_NAME_SIZE);
      pProperties_ref.specVersion = response.vkenumeratedeviceextensionproperties().pproperties(pProperties_indx).specversion();
    }
  }
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkGetPhysicalDeviceMemoryProperties(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* pMemoryProperties) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetPhysicalDeviceMemoryProperties");
  request.mutable_vkgetphysicaldevicememoryproperties()->set_physicaldevice(reinterpret_cast<uint64_t>(physicalDevice));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  VkPhysicalDeviceMemoryProperties& pMemoryProperties_ref = *pMemoryProperties;
  pMemoryProperties_ref.memoryTypeCount = response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memorytypecount();
  for (int memoryTypes_indx = 0; memoryTypes_indx < response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memorytypes_size(); memoryTypes_indx++) {
    VkMemoryType &pMemoryProperties_ref_memoryTypes_i = pMemoryProperties_ref.memoryTypes[memoryTypes_indx];
    if (response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memorytypes(memoryTypes_indx).has_propertyflags()) {
      pMemoryProperties_ref_memoryTypes_i.propertyFlags = static_cast<VkMemoryPropertyFlags>(response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memorytypes(memoryTypes_indx).propertyflags());
    } else {
      pMemoryProperties_ref_memoryTypes_i.propertyFlags = VkMemoryPropertyFlags{};
    }
    pMemoryProperties_ref_memoryTypes_i.heapIndex = response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memorytypes(memoryTypes_indx).heapindex();
  }
  pMemoryProperties_ref.memoryHeapCount = response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memoryheapcount();
  for (int memoryHeaps_indx = 0; memoryHeaps_indx < response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memoryheaps_size(); memoryHeaps_indx++) {
    VkMemoryHeap &pMemoryProperties_ref_memoryHeaps_i = pMemoryProperties_ref.memoryHeaps[memoryHeaps_indx];
    pMemoryProperties_ref_memoryHeaps_i.size = static_cast<VkDeviceSize>(response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memoryheaps(memoryHeaps_indx).size());
    if (response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memoryheaps(memoryHeaps_indx).has_flags()) {
      pMemoryProperties_ref_memoryHeaps_i.flags = static_cast<VkMemoryHeapFlags>(response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memoryheaps(memoryHeaps_indx).flags());
    } else {
      pMemoryProperties_ref_memoryHeaps_i.flags = VkMemoryHeapFlags{};
    }
  }
}
void PackAndCallVkGetPhysicalDeviceFeatures(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetPhysicalDeviceFeatures");
  request.mutable_vkgetphysicaldevicefeatures()->set_physicaldevice(reinterpret_cast<uint64_t>(physicalDevice));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
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
void PackAndCallVkGetPhysicalDeviceQueueFamilyProperties(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetPhysicalDeviceQueueFamilyProperties");
  request.mutable_vkgetphysicaldevicequeuefamilyproperties()->set_physicaldevice(reinterpret_cast<uint64_t>(physicalDevice));
  request.mutable_vkgetphysicaldevicequeuefamilyproperties()->set_pqueuefamilypropertycount(*pQueueFamilyPropertyCount);
  if (pQueueFamilyProperties) {
    // the value we set is just a sentinel value, only its presence should be checked
    auto* unused = request.mutable_vkgetphysicaldevicequeuefamilyproperties()->add_pqueuefamilyproperties();
  } else {
    request.mutable_vkgetphysicaldevicequeuefamilyproperties()->set_pqueuefamilypropertycount(0);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pQueueFamilyPropertyCount = response.vkgetphysicaldevicequeuefamilyproperties().pqueuefamilypropertycount();
  if (pQueueFamilyProperties) {
    assert(*pQueueFamilyPropertyCount == response.vkgetphysicaldevicequeuefamilyproperties().pqueuefamilypropertycount());
    for (int pQueueFamilyProperties_indx = 0; pQueueFamilyProperties_indx < *pQueueFamilyPropertyCount; pQueueFamilyProperties_indx++) {
      VkQueueFamilyProperties& pQueueFamilyProperties_ref = pQueueFamilyProperties[pQueueFamilyProperties_indx];
      if (response.vkgetphysicaldevicequeuefamilyproperties().pqueuefamilyproperties(pQueueFamilyProperties_indx).has_queueflags()) {
        pQueueFamilyProperties_ref.queueFlags = static_cast<VkQueueFlags>(response.vkgetphysicaldevicequeuefamilyproperties().pqueuefamilyproperties(pQueueFamilyProperties_indx).queueflags());
      } else {
        pQueueFamilyProperties_ref.queueFlags = VkQueueFlags{};
      }
      pQueueFamilyProperties_ref.queueCount = response.vkgetphysicaldevicequeuefamilyproperties().pqueuefamilyproperties(pQueueFamilyProperties_indx).queuecount();
      pQueueFamilyProperties_ref.timestampValidBits = response.vkgetphysicaldevicequeuefamilyproperties().pqueuefamilyproperties(pQueueFamilyProperties_indx).timestampvalidbits();
      VkExtent3D &pQueueFamilyProperties_ref_minImageTransferGranularity = pQueueFamilyProperties_ref.minImageTransferGranularity;
      pQueueFamilyProperties_ref_minImageTransferGranularity.width = response.vkgetphysicaldevicequeuefamilyproperties().pqueuefamilyproperties(pQueueFamilyProperties_indx).minimagetransfergranularity().width();
      pQueueFamilyProperties_ref_minImageTransferGranularity.height = response.vkgetphysicaldevicequeuefamilyproperties().pqueuefamilyproperties(pQueueFamilyProperties_indx).minimagetransfergranularity().height();
      pQueueFamilyProperties_ref_minImageTransferGranularity.depth = response.vkgetphysicaldevicequeuefamilyproperties().pqueuefamilyproperties(pQueueFamilyProperties_indx).minimagetransfergranularity().depth();
    }
  }
}
void PackAndCallVkGetDeviceQueue(VvkCommandClientBidiStream& stream, VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetDeviceQueue");
  request.mutable_vkgetdevicequeue()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkgetdevicequeue()->set_queuefamilyindex(queueFamilyIndex);
  request.mutable_vkgetdevicequeue()->set_queueindex(queueIndex);
  request.mutable_vkgetdevicequeue()->set_pqueue(reinterpret_cast<uint64_t>(*pQueue));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pQueue = reinterpret_cast<VkQueue>(response.vkgetdevicequeue().pqueue());
}
VkResult PackAndCallVkCreateFence(VvkCommandClientBidiStream& stream, VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateFence");
  request.mutable_vkcreatefence()->set_device(reinterpret_cast<uint64_t>(device));
  vvk::server::VkFenceCreateInfo* pCreateInfo_proto = request.mutable_vkcreatefence()->mutable_pcreateinfo();
  if (pCreateInfo->pNext) {
    // pNext chains are currently not supported
  }
  if (pCreateInfo->flags) {
    pCreateInfo_proto->set_flags(pCreateInfo->flags);
  }
  request.mutable_vkcreatefence()->set_pfence(reinterpret_cast<uint64_t>(*pFence));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pFence = reinterpret_cast<VkFence>(response.vkcreatefence().pfence());
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkDestroyFence(VvkCommandClientBidiStream& stream, VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkDestroyFence");
  request.mutable_vkdestroyfence()->set_device(reinterpret_cast<uint64_t>(device));
  if (fence) {
    request.mutable_vkdestroyfence()->set_fence(reinterpret_cast<uint64_t>(fence));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
VkResult PackAndCallVkCreateSemaphore(VvkCommandClientBidiStream& stream, VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateSemaphore");
  request.mutable_vkcreatesemaphore()->set_device(reinterpret_cast<uint64_t>(device));
  vvk::server::VkSemaphoreCreateInfo* pCreateInfo_proto = request.mutable_vkcreatesemaphore()->mutable_pcreateinfo();
  if (pCreateInfo->pNext) {
    // pNext chains are currently not supported
  }
  if (pCreateInfo->flags) {
    pCreateInfo_proto->set_flags(pCreateInfo->flags);
  }
  request.mutable_vkcreatesemaphore()->set_psemaphore(reinterpret_cast<uint64_t>(*pSemaphore));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pSemaphore = reinterpret_cast<VkSemaphore>(response.vkcreatesemaphore().psemaphore());
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkDestroySemaphore(VvkCommandClientBidiStream& stream, VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkDestroySemaphore");
  request.mutable_vkdestroysemaphore()->set_device(reinterpret_cast<uint64_t>(device));
  if (semaphore) {
    request.mutable_vkdestroysemaphore()->set_semaphore(reinterpret_cast<uint64_t>(semaphore));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
VkResult PackAndCallVkAllocateMemory(VvkCommandClientBidiStream& stream, VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory) {
  vvk::server::VvkRequest request;
  request.set_method("vkAllocateMemory");
  request.mutable_vkallocatememory()->set_device(reinterpret_cast<uint64_t>(device));
  vvk::server::VkMemoryAllocateInfo* pAllocateInfo_proto = request.mutable_vkallocatememory()->mutable_pallocateinfo();
  if (pAllocateInfo->pNext) {
    // pNext chains are currently not supported
  }
  pAllocateInfo_proto->set_allocationsize(static_cast<uint64_t>(pAllocateInfo->allocationSize));
  pAllocateInfo_proto->set_memorytypeindex(pAllocateInfo->memoryTypeIndex);
  request.mutable_vkallocatememory()->set_pmemory(reinterpret_cast<uint64_t>(*pMemory));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pMemory = reinterpret_cast<VkDeviceMemory>(response.vkallocatememory().pmemory());
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkFreeMemory(VvkCommandClientBidiStream& stream, VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkFreeMemory");
  request.mutable_vkfreememory()->set_device(reinterpret_cast<uint64_t>(device));
  if (memory) {
    request.mutable_vkfreememory()->set_memory(reinterpret_cast<uint64_t>(memory));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
VkResult PackAndCallVkCreateImage(VvkCommandClientBidiStream& stream, VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateImage");
  request.mutable_vkcreateimage()->set_device(reinterpret_cast<uint64_t>(device));
  vvk::server::VkImageCreateInfo* pCreateInfo_proto = request.mutable_vkcreateimage()->mutable_pcreateinfo();
  if (pCreateInfo->pNext) {
    // pNext chains are currently not supported
  }
  if (pCreateInfo->flags) {
    pCreateInfo_proto->set_flags(pCreateInfo->flags);
  }
  pCreateInfo_proto->set_imagetype(static_cast<vvk::server::VkImageType>(pCreateInfo->imageType));
  pCreateInfo_proto->set_format(static_cast<vvk::server::VkFormat>(pCreateInfo->format));
  vvk::server::VkExtent3D* pCreateInfo_proto_extent_proto = pCreateInfo_proto->mutable_extent();
  pCreateInfo_proto_extent_proto->set_width((&pCreateInfo->extent)->width);
  pCreateInfo_proto_extent_proto->set_height((&pCreateInfo->extent)->height);
  pCreateInfo_proto_extent_proto->set_depth((&pCreateInfo->extent)->depth);
  pCreateInfo_proto->set_miplevels(pCreateInfo->mipLevels);
  pCreateInfo_proto->set_arraylayers(pCreateInfo->arrayLayers);
  pCreateInfo_proto->set_samples(pCreateInfo->samples);
  pCreateInfo_proto->set_tiling(static_cast<vvk::server::VkImageTiling>(pCreateInfo->tiling));
  pCreateInfo_proto->set_usage(pCreateInfo->usage);
  pCreateInfo_proto->set_sharingmode(static_cast<vvk::server::VkSharingMode>(pCreateInfo->sharingMode));
  if (pCreateInfo->queueFamilyIndexCount) {
    pCreateInfo_proto->set_queuefamilyindexcount(pCreateInfo->queueFamilyIndexCount);
  }
  const size_t pCreateInfo_proto_pQueueFamilyIndices_length = pCreateInfo->queueFamilyIndexCount;
  for (int pQueueFamilyIndices_indx = 0; pQueueFamilyIndices_indx < pCreateInfo_proto_pQueueFamilyIndices_length; pQueueFamilyIndices_indx++) {
    pCreateInfo_proto->add_pqueuefamilyindices(pCreateInfo->pQueueFamilyIndices[pQueueFamilyIndices_indx]);
  }
  pCreateInfo_proto->set_initiallayout(static_cast<vvk::server::VkImageLayout>(pCreateInfo->initialLayout));
  request.mutable_vkcreateimage()->set_pimage(reinterpret_cast<uint64_t>(*pImage));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pImage = reinterpret_cast<VkImage>(response.vkcreateimage().pimage());
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkDestroyImage(VvkCommandClientBidiStream& stream, VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkDestroyImage");
  request.mutable_vkdestroyimage()->set_device(reinterpret_cast<uint64_t>(device));
  if (image) {
    request.mutable_vkdestroyimage()->set_image(reinterpret_cast<uint64_t>(image));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
VkResult PackAndCallVkBindImageMemory(VvkCommandClientBidiStream& stream, VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset) {
  vvk::server::VvkRequest request;
  request.set_method("vkBindImageMemory");
  request.mutable_vkbindimagememory()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkbindimagememory()->set_image(reinterpret_cast<uint64_t>(image));
  request.mutable_vkbindimagememory()->set_memory(reinterpret_cast<uint64_t>(memory));
  request.mutable_vkbindimagememory()->set_memoryoffset(static_cast<uint64_t>(memoryOffset));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.result());
}
VkResult PackAndCallVkBindImageMemory2(VvkCommandClientBidiStream& stream, VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) {
  vvk::server::VvkRequest request;
  request.set_method("vkBindImageMemory2");
  request.mutable_vkbindimagememory2()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkbindimagememory2()->set_bindinfocount(bindInfoCount);
  for (int pBindInfos_indx = 0; pBindInfos_indx < bindInfoCount; pBindInfos_indx++) {
    vvk::server::VkBindImageMemoryInfo* pBindInfos_proto = request.mutable_vkbindimagememory2()->add_pbindinfos();
    const VkBindImageMemoryInfo* pBindInfos_i = &pBindInfos[pBindInfos_indx];
    if (pBindInfos_i->pNext) {
      // pNext chains are currently not supported
    }
    pBindInfos_proto->set_image(reinterpret_cast<uint64_t>(pBindInfos_i->image));
    pBindInfos_proto->set_memory(reinterpret_cast<uint64_t>(pBindInfos_i->memory));
    pBindInfos_proto->set_memoryoffset(static_cast<uint64_t>(pBindInfos_i->memoryOffset));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkGetImageMemoryRequirements(VvkCommandClientBidiStream& stream, VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetImageMemoryRequirements");
  request.mutable_vkgetimagememoryrequirements()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkgetimagememoryrequirements()->set_image(reinterpret_cast<uint64_t>(image));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  VkMemoryRequirements& pMemoryRequirements_ref = *pMemoryRequirements;
  pMemoryRequirements_ref.size = static_cast<VkDeviceSize>(response.vkgetimagememoryrequirements().pmemoryrequirements().size());
  pMemoryRequirements_ref.alignment = static_cast<VkDeviceSize>(response.vkgetimagememoryrequirements().pmemoryrequirements().alignment());
  pMemoryRequirements_ref.memoryTypeBits = response.vkgetimagememoryrequirements().pmemoryrequirements().memorytypebits();
}
void PackAndCallVkGetImageMemoryRequirements2(VvkCommandClientBidiStream& stream, VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetImageMemoryRequirements2");
  request.mutable_vkgetimagememoryrequirements2()->set_device(reinterpret_cast<uint64_t>(device));
  vvk::server::VkImageMemoryRequirementsInfo2* pInfo_proto = request.mutable_vkgetimagememoryrequirements2()->mutable_pinfo();
  if (pInfo->pNext) {
    // pNext chains are currently not supported
  }
  pInfo_proto->set_image(reinterpret_cast<uint64_t>(pInfo->image));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  VkMemoryRequirements2& pMemoryRequirements_ref = *pMemoryRequirements;
  pMemoryRequirements_ref.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
  pMemoryRequirements_ref.pNext = nullptr; // pNext chains are currently unsupported
  VkMemoryRequirements &pMemoryRequirements_ref_memoryRequirements = pMemoryRequirements_ref.memoryRequirements;
  pMemoryRequirements_ref_memoryRequirements.size = static_cast<VkDeviceSize>(response.vkgetimagememoryrequirements2().pmemoryrequirements().memoryrequirements().size());
  pMemoryRequirements_ref_memoryRequirements.alignment = static_cast<VkDeviceSize>(response.vkgetimagememoryrequirements2().pmemoryrequirements().memoryrequirements().alignment());
  pMemoryRequirements_ref_memoryRequirements.memoryTypeBits = response.vkgetimagememoryrequirements2().pmemoryrequirements().memoryrequirements().memorytypebits();
}
VkResult PackAndCallVkCreateImageView(VvkCommandClientBidiStream& stream, VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateImageView");
  request.mutable_vkcreateimageview()->set_device(reinterpret_cast<uint64_t>(device));
  vvk::server::VkImageViewCreateInfo* pCreateInfo_proto = request.mutable_vkcreateimageview()->mutable_pcreateinfo();
  if (pCreateInfo->pNext) {
    // pNext chains are currently not supported
  }
  if (pCreateInfo->flags) {
    pCreateInfo_proto->set_flags(pCreateInfo->flags);
  }
  pCreateInfo_proto->set_image(reinterpret_cast<uint64_t>(pCreateInfo->image));
  pCreateInfo_proto->set_viewtype(static_cast<vvk::server::VkImageViewType>(pCreateInfo->viewType));
  pCreateInfo_proto->set_format(static_cast<vvk::server::VkFormat>(pCreateInfo->format));
  vvk::server::VkComponentMapping* pCreateInfo_proto_components_proto = pCreateInfo_proto->mutable_components();
  pCreateInfo_proto_components_proto->set_r(static_cast<vvk::server::VkComponentSwizzle>((&pCreateInfo->components)->r));
  pCreateInfo_proto_components_proto->set_g(static_cast<vvk::server::VkComponentSwizzle>((&pCreateInfo->components)->g));
  pCreateInfo_proto_components_proto->set_b(static_cast<vvk::server::VkComponentSwizzle>((&pCreateInfo->components)->b));
  pCreateInfo_proto_components_proto->set_a(static_cast<vvk::server::VkComponentSwizzle>((&pCreateInfo->components)->a));
  vvk::server::VkImageSubresourceRange* pCreateInfo_proto_subresourceRange_proto = pCreateInfo_proto->mutable_subresourcerange();
  pCreateInfo_proto_subresourceRange_proto->set_aspectmask((&pCreateInfo->subresourceRange)->aspectMask);
  pCreateInfo_proto_subresourceRange_proto->set_basemiplevel((&pCreateInfo->subresourceRange)->baseMipLevel);
  pCreateInfo_proto_subresourceRange_proto->set_levelcount((&pCreateInfo->subresourceRange)->levelCount);
  pCreateInfo_proto_subresourceRange_proto->set_basearraylayer((&pCreateInfo->subresourceRange)->baseArrayLayer);
  pCreateInfo_proto_subresourceRange_proto->set_layercount((&pCreateInfo->subresourceRange)->layerCount);
  request.mutable_vkcreateimageview()->set_pview(reinterpret_cast<uint64_t>(*pView));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pView = reinterpret_cast<VkImageView>(response.vkcreateimageview().pview());
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkDestroyImageView(VvkCommandClientBidiStream& stream, VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkDestroyImageView");
  request.mutable_vkdestroyimageview()->set_device(reinterpret_cast<uint64_t>(device));
  if (imageView) {
    request.mutable_vkdestroyimageview()->set_imageview(reinterpret_cast<uint64_t>(imageView));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
VkResult PackAndCallVkCreateCommandPool(VvkCommandClientBidiStream& stream, VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateCommandPool");
  request.mutable_vkcreatecommandpool()->set_device(reinterpret_cast<uint64_t>(device));
  vvk::server::VkCommandPoolCreateInfo* pCreateInfo_proto = request.mutable_vkcreatecommandpool()->mutable_pcreateinfo();
  if (pCreateInfo->pNext) {
    // pNext chains are currently not supported
  }
  if (pCreateInfo->flags) {
    pCreateInfo_proto->set_flags(pCreateInfo->flags);
  }
  pCreateInfo_proto->set_queuefamilyindex(pCreateInfo->queueFamilyIndex);
  request.mutable_vkcreatecommandpool()->set_pcommandpool(reinterpret_cast<uint64_t>(*pCommandPool));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pCommandPool = reinterpret_cast<VkCommandPool>(response.vkcreatecommandpool().pcommandpool());
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkDestroyCommandPool(VvkCommandClientBidiStream& stream, VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkDestroyCommandPool");
  request.mutable_vkdestroycommandpool()->set_device(reinterpret_cast<uint64_t>(device));
  if (commandPool) {
    request.mutable_vkdestroycommandpool()->set_commandpool(reinterpret_cast<uint64_t>(commandPool));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
VkResult PackAndCallVkAllocateCommandBuffers(VvkCommandClientBidiStream& stream, VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers) {
  vvk::server::VvkRequest request;
  request.set_method("vkAllocateCommandBuffers");
  request.mutable_vkallocatecommandbuffers()->set_device(reinterpret_cast<uint64_t>(device));
  vvk::server::VkCommandBufferAllocateInfo* pAllocateInfo_proto = request.mutable_vkallocatecommandbuffers()->mutable_pallocateinfo();
  if (pAllocateInfo->pNext) {
    // pNext chains are currently not supported
  }
  pAllocateInfo_proto->set_commandpool(reinterpret_cast<uint64_t>(pAllocateInfo->commandPool));
  pAllocateInfo_proto->set_level(static_cast<vvk::server::VkCommandBufferLevel>(pAllocateInfo->level));
  pAllocateInfo_proto->set_commandbuffercount(pAllocateInfo->commandBufferCount);
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  for (int i = 0; i < pAllocateInfo->commandBufferCount; i++) {
    pCommandBuffers[i] = reinterpret_cast<VkCommandBuffer>(response.vkallocatecommandbuffers().pcommandbuffers(i));
  }
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkFreeCommandBuffers(VvkCommandClientBidiStream& stream, VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) {
  vvk::server::VvkRequest request;
  request.set_method("vkFreeCommandBuffers");
  request.mutable_vkfreecommandbuffers()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkfreecommandbuffers()->set_commandpool(reinterpret_cast<uint64_t>(commandPool));
  request.mutable_vkfreecommandbuffers()->set_commandbuffercount(commandBufferCount);
  for (int i = 0; i < commandBufferCount; i++) {
    request.mutable_vkfreecommandbuffers()->add_pcommandbuffers(reinterpret_cast<uint64_t>(pCommandBuffers[i]));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
VkResult PackAndCallVkBeginCommandBuffer(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo) {
  vvk::server::VvkRequest request;
  request.set_method("vkBeginCommandBuffer");
  request.mutable_vkbegincommandbuffer()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  vvk::server::VkCommandBufferBeginInfo* pBeginInfo_proto = request.mutable_vkbegincommandbuffer()->mutable_pbegininfo();
  if (pBeginInfo->pNext) {
    // pNext chains are currently not supported
  }
  if (pBeginInfo->flags) {
    pBeginInfo_proto->set_flags(pBeginInfo->flags);
  }
  if (pBeginInfo->pInheritanceInfo) {
    vvk::server::VkCommandBufferInheritanceInfo* pBeginInfo_proto_pInheritanceInfo_proto = pBeginInfo_proto->mutable_pinheritanceinfo();
    if (pBeginInfo->pInheritanceInfo->pNext) {
      // pNext chains are currently not supported
    }
    if (pBeginInfo->pInheritanceInfo->renderPass) {
      pBeginInfo_proto_pInheritanceInfo_proto->set_renderpass(reinterpret_cast<uint64_t>(pBeginInfo->pInheritanceInfo->renderPass));
    }
    pBeginInfo_proto_pInheritanceInfo_proto->set_subpass(pBeginInfo->pInheritanceInfo->subpass);
    if (pBeginInfo->pInheritanceInfo->framebuffer) {
      pBeginInfo_proto_pInheritanceInfo_proto->set_framebuffer(reinterpret_cast<uint64_t>(pBeginInfo->pInheritanceInfo->framebuffer));
    }
    pBeginInfo_proto_pInheritanceInfo_proto->set_occlusionqueryenable(pBeginInfo->pInheritanceInfo->occlusionQueryEnable);
    if (pBeginInfo->pInheritanceInfo->queryFlags) {
      pBeginInfo_proto_pInheritanceInfo_proto->set_queryflags(pBeginInfo->pInheritanceInfo->queryFlags);
    }
    if (pBeginInfo->pInheritanceInfo->pipelineStatistics) {
      pBeginInfo_proto_pInheritanceInfo_proto->set_pipelinestatistics(pBeginInfo->pInheritanceInfo->pipelineStatistics);
    }
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.result());
}
VkResult PackAndCallVkEndCommandBuffer(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer) {
  vvk::server::VvkRequest request;
  request.set_method("vkEndCommandBuffer");
  request.mutable_vkendcommandbuffer()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkGetImageSubresourceLayout(VvkCommandClientBidiStream& stream, VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetImageSubresourceLayout");
  request.mutable_vkgetimagesubresourcelayout()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkgetimagesubresourcelayout()->set_image(reinterpret_cast<uint64_t>(image));
  vvk::server::VkImageSubresource* pSubresource_proto = request.mutable_vkgetimagesubresourcelayout()->mutable_psubresource();
  pSubresource_proto->set_aspectmask(pSubresource->aspectMask);
  pSubresource_proto->set_miplevel(pSubresource->mipLevel);
  pSubresource_proto->set_arraylayer(pSubresource->arrayLayer);
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  VkSubresourceLayout& pLayout_ref = *pLayout;
  pLayout_ref.offset = static_cast<VkDeviceSize>(response.vkgetimagesubresourcelayout().playout().offset());
  pLayout_ref.size = static_cast<VkDeviceSize>(response.vkgetimagesubresourcelayout().playout().size());
  pLayout_ref.rowPitch = static_cast<VkDeviceSize>(response.vkgetimagesubresourcelayout().playout().rowpitch());
  pLayout_ref.arrayPitch = static_cast<VkDeviceSize>(response.vkgetimagesubresourcelayout().playout().arraypitch());
  pLayout_ref.depthPitch = static_cast<VkDeviceSize>(response.vkgetimagesubresourcelayout().playout().depthpitch());
}
VkResult PackAndCallVkCreateRenderPass(VvkCommandClientBidiStream& stream, VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateRenderPass");
  request.mutable_vkcreaterenderpass()->set_device(reinterpret_cast<uint64_t>(device));
  vvk::server::VkRenderPassCreateInfo* pCreateInfo_proto = request.mutable_vkcreaterenderpass()->mutable_pcreateinfo();
  if (pCreateInfo->pNext) {
    // pNext chains are currently not supported
  }
  if (pCreateInfo->flags) {
    pCreateInfo_proto->set_flags(pCreateInfo->flags);
  }
  if (pCreateInfo->attachmentCount) {
    pCreateInfo_proto->set_attachmentcount(pCreateInfo->attachmentCount);
  }
  const size_t pCreateInfo_proto_pAttachments_length = pCreateInfo->attachmentCount;
  for (int pAttachments_indx = 0; pAttachments_indx < pCreateInfo_proto_pAttachments_length; pAttachments_indx++) {
    vvk::server::VkAttachmentDescription* pCreateInfo_proto_pAttachments_proto = pCreateInfo_proto->add_pattachments();
    if ((&pCreateInfo->pAttachments[pAttachments_indx])->flags) {
      pCreateInfo_proto_pAttachments_proto->set_flags((&pCreateInfo->pAttachments[pAttachments_indx])->flags);
    }
    pCreateInfo_proto_pAttachments_proto->set_format(static_cast<vvk::server::VkFormat>((&pCreateInfo->pAttachments[pAttachments_indx])->format));
    pCreateInfo_proto_pAttachments_proto->set_samples((&pCreateInfo->pAttachments[pAttachments_indx])->samples);
    pCreateInfo_proto_pAttachments_proto->set_loadop(static_cast<vvk::server::VkAttachmentLoadOp>((&pCreateInfo->pAttachments[pAttachments_indx])->loadOp));
    pCreateInfo_proto_pAttachments_proto->set_storeop(static_cast<vvk::server::VkAttachmentStoreOp>((&pCreateInfo->pAttachments[pAttachments_indx])->storeOp));
    pCreateInfo_proto_pAttachments_proto->set_stencilloadop(static_cast<vvk::server::VkAttachmentLoadOp>((&pCreateInfo->pAttachments[pAttachments_indx])->stencilLoadOp));
    pCreateInfo_proto_pAttachments_proto->set_stencilstoreop(static_cast<vvk::server::VkAttachmentStoreOp>((&pCreateInfo->pAttachments[pAttachments_indx])->stencilStoreOp));
    pCreateInfo_proto_pAttachments_proto->set_initiallayout(static_cast<vvk::server::VkImageLayout>((&pCreateInfo->pAttachments[pAttachments_indx])->initialLayout));
    pCreateInfo_proto_pAttachments_proto->set_finallayout(static_cast<vvk::server::VkImageLayout>((&pCreateInfo->pAttachments[pAttachments_indx])->finalLayout));
  }
  pCreateInfo_proto->set_subpasscount(pCreateInfo->subpassCount);
  const size_t pCreateInfo_proto_pSubpasses_length = pCreateInfo->subpassCount;
  for (int pSubpasses_indx = 0; pSubpasses_indx < pCreateInfo_proto_pSubpasses_length; pSubpasses_indx++) {
    vvk::server::VkSubpassDescription* pCreateInfo_proto_pSubpasses_proto = pCreateInfo_proto->add_psubpasses();
    if ((&pCreateInfo->pSubpasses[pSubpasses_indx])->flags) {
      pCreateInfo_proto_pSubpasses_proto->set_flags((&pCreateInfo->pSubpasses[pSubpasses_indx])->flags);
    }
    pCreateInfo_proto_pSubpasses_proto->set_pipelinebindpoint(static_cast<vvk::server::VkPipelineBindPoint>((&pCreateInfo->pSubpasses[pSubpasses_indx])->pipelineBindPoint));
    if ((&pCreateInfo->pSubpasses[pSubpasses_indx])->inputAttachmentCount) {
      pCreateInfo_proto_pSubpasses_proto->set_inputattachmentcount((&pCreateInfo->pSubpasses[pSubpasses_indx])->inputAttachmentCount);
    }
    const size_t pCreateInfo_proto_pSubpasses_proto_pInputAttachments_length = (&pCreateInfo->pSubpasses[pSubpasses_indx])->inputAttachmentCount;
    for (int pInputAttachments_indx = 0; pInputAttachments_indx < pCreateInfo_proto_pSubpasses_proto_pInputAttachments_length; pInputAttachments_indx++) {
      vvk::server::VkAttachmentReference* pCreateInfo_proto_pSubpasses_proto_pInputAttachments_proto = pCreateInfo_proto_pSubpasses_proto->add_pinputattachments();
      pCreateInfo_proto_pSubpasses_proto_pInputAttachments_proto->set_attachment((&(&pCreateInfo->pSubpasses[pSubpasses_indx])->pInputAttachments[pInputAttachments_indx])->attachment);
      pCreateInfo_proto_pSubpasses_proto_pInputAttachments_proto->set_layout(static_cast<vvk::server::VkImageLayout>((&(&pCreateInfo->pSubpasses[pSubpasses_indx])->pInputAttachments[pInputAttachments_indx])->layout));
    }
    if ((&pCreateInfo->pSubpasses[pSubpasses_indx])->colorAttachmentCount) {
      pCreateInfo_proto_pSubpasses_proto->set_colorattachmentcount((&pCreateInfo->pSubpasses[pSubpasses_indx])->colorAttachmentCount);
    }
    const size_t pCreateInfo_proto_pSubpasses_proto_pColorAttachments_length = (&pCreateInfo->pSubpasses[pSubpasses_indx])->colorAttachmentCount;
    for (int pColorAttachments_indx = 0; pColorAttachments_indx < pCreateInfo_proto_pSubpasses_proto_pColorAttachments_length; pColorAttachments_indx++) {
      vvk::server::VkAttachmentReference* pCreateInfo_proto_pSubpasses_proto_pColorAttachments_proto = pCreateInfo_proto_pSubpasses_proto->add_pcolorattachments();
      pCreateInfo_proto_pSubpasses_proto_pColorAttachments_proto->set_attachment((&(&pCreateInfo->pSubpasses[pSubpasses_indx])->pColorAttachments[pColorAttachments_indx])->attachment);
      pCreateInfo_proto_pSubpasses_proto_pColorAttachments_proto->set_layout(static_cast<vvk::server::VkImageLayout>((&(&pCreateInfo->pSubpasses[pSubpasses_indx])->pColorAttachments[pColorAttachments_indx])->layout));
    }
    if ((&pCreateInfo->pSubpasses[pSubpasses_indx])->pResolveAttachments) {
      const size_t pCreateInfo_proto_pSubpasses_proto_pResolveAttachments_length = (&pCreateInfo->pSubpasses[pSubpasses_indx])->colorAttachmentCount;
      for (int pResolveAttachments_indx = 0; pResolveAttachments_indx < pCreateInfo_proto_pSubpasses_proto_pResolveAttachments_length; pResolveAttachments_indx++) {
        vvk::server::VkAttachmentReference* pCreateInfo_proto_pSubpasses_proto_pResolveAttachments_proto = pCreateInfo_proto_pSubpasses_proto->add_presolveattachments();
        pCreateInfo_proto_pSubpasses_proto_pResolveAttachments_proto->set_attachment((&(&pCreateInfo->pSubpasses[pSubpasses_indx])->pResolveAttachments[pResolveAttachments_indx])->attachment);
        pCreateInfo_proto_pSubpasses_proto_pResolveAttachments_proto->set_layout(static_cast<vvk::server::VkImageLayout>((&(&pCreateInfo->pSubpasses[pSubpasses_indx])->pResolveAttachments[pResolveAttachments_indx])->layout));
      }
    }
    if ((&pCreateInfo->pSubpasses[pSubpasses_indx])->pDepthStencilAttachment) {
      vvk::server::VkAttachmentReference* pCreateInfo_proto_pSubpasses_proto_pDepthStencilAttachment_proto = pCreateInfo_proto_pSubpasses_proto->mutable_pdepthstencilattachment();
      pCreateInfo_proto_pSubpasses_proto_pDepthStencilAttachment_proto->set_attachment((&pCreateInfo->pSubpasses[pSubpasses_indx])->pDepthStencilAttachment->attachment);
      pCreateInfo_proto_pSubpasses_proto_pDepthStencilAttachment_proto->set_layout(static_cast<vvk::server::VkImageLayout>((&pCreateInfo->pSubpasses[pSubpasses_indx])->pDepthStencilAttachment->layout));
    }
    if ((&pCreateInfo->pSubpasses[pSubpasses_indx])->preserveAttachmentCount) {
      pCreateInfo_proto_pSubpasses_proto->set_preserveattachmentcount((&pCreateInfo->pSubpasses[pSubpasses_indx])->preserveAttachmentCount);
    }
    const size_t pCreateInfo_proto_pSubpasses_proto_pPreserveAttachments_length = (&pCreateInfo->pSubpasses[pSubpasses_indx])->preserveAttachmentCount;
    for (int pPreserveAttachments_indx = 0; pPreserveAttachments_indx < pCreateInfo_proto_pSubpasses_proto_pPreserveAttachments_length; pPreserveAttachments_indx++) {
      pCreateInfo_proto_pSubpasses_proto->add_ppreserveattachments((&pCreateInfo->pSubpasses[pSubpasses_indx])->pPreserveAttachments[pPreserveAttachments_indx]);
    }
  }
  if (pCreateInfo->dependencyCount) {
    pCreateInfo_proto->set_dependencycount(pCreateInfo->dependencyCount);
  }
  const size_t pCreateInfo_proto_pDependencies_length = pCreateInfo->dependencyCount;
  for (int pDependencies_indx = 0; pDependencies_indx < pCreateInfo_proto_pDependencies_length; pDependencies_indx++) {
    vvk::server::VkSubpassDependency* pCreateInfo_proto_pDependencies_proto = pCreateInfo_proto->add_pdependencies();
    pCreateInfo_proto_pDependencies_proto->set_srcsubpass((&pCreateInfo->pDependencies[pDependencies_indx])->srcSubpass);
    pCreateInfo_proto_pDependencies_proto->set_dstsubpass((&pCreateInfo->pDependencies[pDependencies_indx])->dstSubpass);
    if ((&pCreateInfo->pDependencies[pDependencies_indx])->srcStageMask) {
      pCreateInfo_proto_pDependencies_proto->set_srcstagemask((&pCreateInfo->pDependencies[pDependencies_indx])->srcStageMask);
    }
    if ((&pCreateInfo->pDependencies[pDependencies_indx])->dstStageMask) {
      pCreateInfo_proto_pDependencies_proto->set_dststagemask((&pCreateInfo->pDependencies[pDependencies_indx])->dstStageMask);
    }
    if ((&pCreateInfo->pDependencies[pDependencies_indx])->srcAccessMask) {
      pCreateInfo_proto_pDependencies_proto->set_srcaccessmask((&pCreateInfo->pDependencies[pDependencies_indx])->srcAccessMask);
    }
    if ((&pCreateInfo->pDependencies[pDependencies_indx])->dstAccessMask) {
      pCreateInfo_proto_pDependencies_proto->set_dstaccessmask((&pCreateInfo->pDependencies[pDependencies_indx])->dstAccessMask);
    }
    if ((&pCreateInfo->pDependencies[pDependencies_indx])->dependencyFlags) {
      pCreateInfo_proto_pDependencies_proto->set_dependencyflags((&pCreateInfo->pDependencies[pDependencies_indx])->dependencyFlags);
    }
  }
  request.mutable_vkcreaterenderpass()->set_prenderpass(reinterpret_cast<uint64_t>(*pRenderPass));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pRenderPass = reinterpret_cast<VkRenderPass>(response.vkcreaterenderpass().prenderpass());
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkDestroyRenderPass(VvkCommandClientBidiStream& stream, VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkDestroyRenderPass");
  request.mutable_vkdestroyrenderpass()->set_device(reinterpret_cast<uint64_t>(device));
  if (renderPass) {
    request.mutable_vkdestroyrenderpass()->set_renderpass(reinterpret_cast<uint64_t>(renderPass));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
VkResult PackAndCallVkCreatePipelineLayout(VvkCommandClientBidiStream& stream, VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreatePipelineLayout");
  request.mutable_vkcreatepipelinelayout()->set_device(reinterpret_cast<uint64_t>(device));
  vvk::server::VkPipelineLayoutCreateInfo* pCreateInfo_proto = request.mutable_vkcreatepipelinelayout()->mutable_pcreateinfo();
  if (pCreateInfo->pNext) {
    // pNext chains are currently not supported
  }
  if (pCreateInfo->flags) {
    pCreateInfo_proto->set_flags(pCreateInfo->flags);
  }
  if (pCreateInfo->setLayoutCount) {
    pCreateInfo_proto->set_setlayoutcount(pCreateInfo->setLayoutCount);
  }
  const size_t pCreateInfo_proto_pSetLayouts_length = pCreateInfo->setLayoutCount;
  for (int pSetLayouts_indx = 0; pSetLayouts_indx < pCreateInfo_proto_pSetLayouts_length; pSetLayouts_indx++) {
    pCreateInfo_proto->add_psetlayouts(reinterpret_cast<uint64_t>(pCreateInfo->pSetLayouts[pSetLayouts_indx]));
  }
  if (pCreateInfo->pushConstantRangeCount) {
    pCreateInfo_proto->set_pushconstantrangecount(pCreateInfo->pushConstantRangeCount);
  }
  const size_t pCreateInfo_proto_pPushConstantRanges_length = pCreateInfo->pushConstantRangeCount;
  for (int pPushConstantRanges_indx = 0; pPushConstantRanges_indx < pCreateInfo_proto_pPushConstantRanges_length; pPushConstantRanges_indx++) {
    vvk::server::VkPushConstantRange* pCreateInfo_proto_pPushConstantRanges_proto = pCreateInfo_proto->add_ppushconstantranges();
    pCreateInfo_proto_pPushConstantRanges_proto->set_stageflags((&pCreateInfo->pPushConstantRanges[pPushConstantRanges_indx])->stageFlags);
    pCreateInfo_proto_pPushConstantRanges_proto->set_offset((&pCreateInfo->pPushConstantRanges[pPushConstantRanges_indx])->offset);
    pCreateInfo_proto_pPushConstantRanges_proto->set_size((&pCreateInfo->pPushConstantRanges[pPushConstantRanges_indx])->size);
  }
  request.mutable_vkcreatepipelinelayout()->set_ppipelinelayout(reinterpret_cast<uint64_t>(*pPipelineLayout));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pPipelineLayout = reinterpret_cast<VkPipelineLayout>(response.vkcreatepipelinelayout().ppipelinelayout());
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkDestroyPipelineLayout(VvkCommandClientBidiStream& stream, VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkDestroyPipelineLayout");
  request.mutable_vkdestroypipelinelayout()->set_device(reinterpret_cast<uint64_t>(device));
  if (pipelineLayout) {
    request.mutable_vkdestroypipelinelayout()->set_pipelinelayout(reinterpret_cast<uint64_t>(pipelineLayout));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
VkResult PackAndCallVkCreateShaderModule(VvkCommandClientBidiStream& stream, VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateShaderModule");
  request.mutable_vkcreateshadermodule()->set_device(reinterpret_cast<uint64_t>(device));
  vvk::server::VkShaderModuleCreateInfo* pCreateInfo_proto = request.mutable_vkcreateshadermodule()->mutable_pcreateinfo();
  if (pCreateInfo->pNext) {
    // pNext chains are currently not supported
  }
  if (pCreateInfo->flags) {
    pCreateInfo_proto->set_flags(pCreateInfo->flags);
  }
  pCreateInfo_proto->set_codesize(pCreateInfo->codeSize);
  const size_t pCreateInfo_proto_pCode_length = pCreateInfo->codeSize / 4;
  for (int pCode_indx = 0; pCode_indx < pCreateInfo_proto_pCode_length; pCode_indx++) {
    pCreateInfo_proto->add_pcode(pCreateInfo->pCode[pCode_indx]);
  }
  request.mutable_vkcreateshadermodule()->set_pshadermodule(reinterpret_cast<uint64_t>(*pShaderModule));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pShaderModule = reinterpret_cast<VkShaderModule>(response.vkcreateshadermodule().pshadermodule());
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkDestroyShaderModule(VvkCommandClientBidiStream& stream, VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkDestroyShaderModule");
  request.mutable_vkdestroyshadermodule()->set_device(reinterpret_cast<uint64_t>(device));
  if (shaderModule) {
    request.mutable_vkdestroyshadermodule()->set_shadermodule(reinterpret_cast<uint64_t>(shaderModule));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
VkResult PackAndCallVkCreateGraphicsPipelines(VvkCommandClientBidiStream& stream, VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateGraphicsPipelines");
  request.mutable_vkcreategraphicspipelines()->set_device(reinterpret_cast<uint64_t>(device));
  if (pipelineCache) {
    request.mutable_vkcreategraphicspipelines()->set_pipelinecache(reinterpret_cast<uint64_t>(pipelineCache));
  }
  request.mutable_vkcreategraphicspipelines()->set_createinfocount(createInfoCount);
  for (int pCreateInfos_indx = 0; pCreateInfos_indx < createInfoCount; pCreateInfos_indx++) {
    vvk::server::VkGraphicsPipelineCreateInfo* pCreateInfos_proto = request.mutable_vkcreategraphicspipelines()->add_pcreateinfos();
    const VkGraphicsPipelineCreateInfo* pCreateInfos_i = &pCreateInfos[pCreateInfos_indx];
    if (pCreateInfos_i->pNext) {
      // pNext chains are currently not supported
    }
    if (pCreateInfos_i->flags) {
      pCreateInfos_proto->set_flags(pCreateInfos_i->flags);
    }
    if (pCreateInfos_i->stageCount) {
      pCreateInfos_proto->set_stagecount(pCreateInfos_i->stageCount);
    }
    if (pCreateInfos_i->pStages) {
      const size_t pCreateInfos_proto_pStages_length = pCreateInfos_i->stageCount;
      for (int pStages_indx = 0; pStages_indx < pCreateInfos_proto_pStages_length; pStages_indx++) {
        vvk::server::VkPipelineShaderStageCreateInfo* pCreateInfos_proto_pStages_proto = pCreateInfos_proto->add_pstages();
        if ((&pCreateInfos_i->pStages[pStages_indx])->pNext) {
          // pNext chains are currently not supported
        }
        if ((&pCreateInfos_i->pStages[pStages_indx])->flags) {
          pCreateInfos_proto_pStages_proto->set_flags((&pCreateInfos_i->pStages[pStages_indx])->flags);
        }
        pCreateInfos_proto_pStages_proto->set_stage((&pCreateInfos_i->pStages[pStages_indx])->stage);
        if ((&pCreateInfos_i->pStages[pStages_indx])->module) {
          pCreateInfos_proto_pStages_proto->set_module(reinterpret_cast<uint64_t>((&pCreateInfos_i->pStages[pStages_indx])->module));
        }
        pCreateInfos_proto_pStages_proto->set_pname((&pCreateInfos_i->pStages[pStages_indx])->pName);
        if ((&pCreateInfos_i->pStages[pStages_indx])->pSpecializationInfo) {
          vvk::server::VkSpecializationInfo* pCreateInfos_proto_pStages_proto_pSpecializationInfo_proto = pCreateInfos_proto_pStages_proto->mutable_pspecializationinfo();
          if ((&pCreateInfos_i->pStages[pStages_indx])->pSpecializationInfo->mapEntryCount) {
            pCreateInfos_proto_pStages_proto_pSpecializationInfo_proto->set_mapentrycount((&pCreateInfos_i->pStages[pStages_indx])->pSpecializationInfo->mapEntryCount);
          }
          const size_t pCreateInfos_proto_pStages_proto_pSpecializationInfo_proto_pMapEntries_length = (&pCreateInfos_i->pStages[pStages_indx])->pSpecializationInfo->mapEntryCount;
          for (int pMapEntries_indx = 0; pMapEntries_indx < pCreateInfos_proto_pStages_proto_pSpecializationInfo_proto_pMapEntries_length; pMapEntries_indx++) {
            vvk::server::VkSpecializationMapEntry* pCreateInfos_proto_pStages_proto_pSpecializationInfo_proto_pMapEntries_proto = pCreateInfos_proto_pStages_proto_pSpecializationInfo_proto->add_pmapentries();
            pCreateInfos_proto_pStages_proto_pSpecializationInfo_proto_pMapEntries_proto->set_constantid((&(&pCreateInfos_i->pStages[pStages_indx])->pSpecializationInfo->pMapEntries[pMapEntries_indx])->constantID);
            pCreateInfos_proto_pStages_proto_pSpecializationInfo_proto_pMapEntries_proto->set_offset((&(&pCreateInfos_i->pStages[pStages_indx])->pSpecializationInfo->pMapEntries[pMapEntries_indx])->offset);
            pCreateInfos_proto_pStages_proto_pSpecializationInfo_proto_pMapEntries_proto->set_size((&(&pCreateInfos_i->pStages[pStages_indx])->pSpecializationInfo->pMapEntries[pMapEntries_indx])->size);
          }
          if ((&pCreateInfos_i->pStages[pStages_indx])->pSpecializationInfo->dataSize) {
            pCreateInfos_proto_pStages_proto_pSpecializationInfo_proto->set_datasize((&pCreateInfos_i->pStages[pStages_indx])->pSpecializationInfo->dataSize);
          }
          const size_t pCreateInfos_proto_pStages_proto_pSpecializationInfo_proto_pData_length = (&pCreateInfos_i->pStages[pStages_indx])->pSpecializationInfo->dataSize;
          pCreateInfos_proto_pStages_proto_pSpecializationInfo_proto->set_pdata((&pCreateInfos_i->pStages[pStages_indx])->pSpecializationInfo->pData, pCreateInfos_proto_pStages_proto_pSpecializationInfo_proto_pData_length);
        }
      }
    }
    if (pCreateInfos_i->pVertexInputState) {
      vvk::server::VkPipelineVertexInputStateCreateInfo* pCreateInfos_proto_pVertexInputState_proto = pCreateInfos_proto->mutable_pvertexinputstate();
      if (pCreateInfos_i->pVertexInputState->pNext) {
        // pNext chains are currently not supported
      }
      if (pCreateInfos_i->pVertexInputState->flags) {
        pCreateInfos_proto_pVertexInputState_proto->set_flags(pCreateInfos_i->pVertexInputState->flags);
      }
      if (pCreateInfos_i->pVertexInputState->vertexBindingDescriptionCount) {
        pCreateInfos_proto_pVertexInputState_proto->set_vertexbindingdescriptioncount(pCreateInfos_i->pVertexInputState->vertexBindingDescriptionCount);
      }
      const size_t pCreateInfos_proto_pVertexInputState_proto_pVertexBindingDescriptions_length = pCreateInfos_i->pVertexInputState->vertexBindingDescriptionCount;
      for (int pVertexBindingDescriptions_indx = 0; pVertexBindingDescriptions_indx < pCreateInfos_proto_pVertexInputState_proto_pVertexBindingDescriptions_length; pVertexBindingDescriptions_indx++) {
        vvk::server::VkVertexInputBindingDescription* pCreateInfos_proto_pVertexInputState_proto_pVertexBindingDescriptions_proto = pCreateInfos_proto_pVertexInputState_proto->add_pvertexbindingdescriptions();
        pCreateInfos_proto_pVertexInputState_proto_pVertexBindingDescriptions_proto->set_binding((&pCreateInfos_i->pVertexInputState->pVertexBindingDescriptions[pVertexBindingDescriptions_indx])->binding);
        pCreateInfos_proto_pVertexInputState_proto_pVertexBindingDescriptions_proto->set_stride((&pCreateInfos_i->pVertexInputState->pVertexBindingDescriptions[pVertexBindingDescriptions_indx])->stride);
        pCreateInfos_proto_pVertexInputState_proto_pVertexBindingDescriptions_proto->set_inputrate(static_cast<vvk::server::VkVertexInputRate>((&pCreateInfos_i->pVertexInputState->pVertexBindingDescriptions[pVertexBindingDescriptions_indx])->inputRate));
      }
      if (pCreateInfos_i->pVertexInputState->vertexAttributeDescriptionCount) {
        pCreateInfos_proto_pVertexInputState_proto->set_vertexattributedescriptioncount(pCreateInfos_i->pVertexInputState->vertexAttributeDescriptionCount);
      }
      const size_t pCreateInfos_proto_pVertexInputState_proto_pVertexAttributeDescriptions_length = pCreateInfos_i->pVertexInputState->vertexAttributeDescriptionCount;
      for (int pVertexAttributeDescriptions_indx = 0; pVertexAttributeDescriptions_indx < pCreateInfos_proto_pVertexInputState_proto_pVertexAttributeDescriptions_length; pVertexAttributeDescriptions_indx++) {
        vvk::server::VkVertexInputAttributeDescription* pCreateInfos_proto_pVertexInputState_proto_pVertexAttributeDescriptions_proto = pCreateInfos_proto_pVertexInputState_proto->add_pvertexattributedescriptions();
        pCreateInfos_proto_pVertexInputState_proto_pVertexAttributeDescriptions_proto->set_location((&pCreateInfos_i->pVertexInputState->pVertexAttributeDescriptions[pVertexAttributeDescriptions_indx])->location);
        pCreateInfos_proto_pVertexInputState_proto_pVertexAttributeDescriptions_proto->set_binding((&pCreateInfos_i->pVertexInputState->pVertexAttributeDescriptions[pVertexAttributeDescriptions_indx])->binding);
        pCreateInfos_proto_pVertexInputState_proto_pVertexAttributeDescriptions_proto->set_format(static_cast<vvk::server::VkFormat>((&pCreateInfos_i->pVertexInputState->pVertexAttributeDescriptions[pVertexAttributeDescriptions_indx])->format));
        pCreateInfos_proto_pVertexInputState_proto_pVertexAttributeDescriptions_proto->set_offset((&pCreateInfos_i->pVertexInputState->pVertexAttributeDescriptions[pVertexAttributeDescriptions_indx])->offset);
      }
    }
    if (pCreateInfos_i->pInputAssemblyState) {
      vvk::server::VkPipelineInputAssemblyStateCreateInfo* pCreateInfos_proto_pInputAssemblyState_proto = pCreateInfos_proto->mutable_pinputassemblystate();
      if (pCreateInfos_i->pInputAssemblyState->pNext) {
        // pNext chains are currently not supported
      }
      if (pCreateInfos_i->pInputAssemblyState->flags) {
        pCreateInfos_proto_pInputAssemblyState_proto->set_flags(pCreateInfos_i->pInputAssemblyState->flags);
      }
      pCreateInfos_proto_pInputAssemblyState_proto->set_topology(static_cast<vvk::server::VkPrimitiveTopology>(pCreateInfos_i->pInputAssemblyState->topology));
      pCreateInfos_proto_pInputAssemblyState_proto->set_primitiverestartenable(pCreateInfos_i->pInputAssemblyState->primitiveRestartEnable);
    }
    if (pCreateInfos_i->pTessellationState) {
      vvk::server::VkPipelineTessellationStateCreateInfo* pCreateInfos_proto_pTessellationState_proto = pCreateInfos_proto->mutable_ptessellationstate();
      if (pCreateInfos_i->pTessellationState->pNext) {
        // pNext chains are currently not supported
      }
      if (pCreateInfos_i->pTessellationState->flags) {
        pCreateInfos_proto_pTessellationState_proto->set_flags(pCreateInfos_i->pTessellationState->flags);
      }
      pCreateInfos_proto_pTessellationState_proto->set_patchcontrolpoints(pCreateInfos_i->pTessellationState->patchControlPoints);
    }
    if (pCreateInfos_i->pViewportState) {
      vvk::server::VkPipelineViewportStateCreateInfo* pCreateInfos_proto_pViewportState_proto = pCreateInfos_proto->mutable_pviewportstate();
      if (pCreateInfos_i->pViewportState->pNext) {
        // pNext chains are currently not supported
      }
      if (pCreateInfos_i->pViewportState->flags) {
        pCreateInfos_proto_pViewportState_proto->set_flags(pCreateInfos_i->pViewportState->flags);
      }
      if (pCreateInfos_i->pViewportState->viewportCount) {
        pCreateInfos_proto_pViewportState_proto->set_viewportcount(pCreateInfos_i->pViewportState->viewportCount);
      }
      if (pCreateInfos_i->pViewportState->pViewports) {
        const size_t pCreateInfos_proto_pViewportState_proto_pViewports_length = pCreateInfos_i->pViewportState->viewportCount;
        for (int pViewports_indx = 0; pViewports_indx < pCreateInfos_proto_pViewportState_proto_pViewports_length; pViewports_indx++) {
          vvk::server::VkViewport* pCreateInfos_proto_pViewportState_proto_pViewports_proto = pCreateInfos_proto_pViewportState_proto->add_pviewports();
          pCreateInfos_proto_pViewportState_proto_pViewports_proto->set_x((&pCreateInfos_i->pViewportState->pViewports[pViewports_indx])->x);
          pCreateInfos_proto_pViewportState_proto_pViewports_proto->set_y((&pCreateInfos_i->pViewportState->pViewports[pViewports_indx])->y);
          pCreateInfos_proto_pViewportState_proto_pViewports_proto->set_width((&pCreateInfos_i->pViewportState->pViewports[pViewports_indx])->width);
          pCreateInfos_proto_pViewportState_proto_pViewports_proto->set_height((&pCreateInfos_i->pViewportState->pViewports[pViewports_indx])->height);
          pCreateInfos_proto_pViewportState_proto_pViewports_proto->set_mindepth((&pCreateInfos_i->pViewportState->pViewports[pViewports_indx])->minDepth);
          pCreateInfos_proto_pViewportState_proto_pViewports_proto->set_maxdepth((&pCreateInfos_i->pViewportState->pViewports[pViewports_indx])->maxDepth);
        }
      }
      if (pCreateInfos_i->pViewportState->scissorCount) {
        pCreateInfos_proto_pViewportState_proto->set_scissorcount(pCreateInfos_i->pViewportState->scissorCount);
      }
      if (pCreateInfos_i->pViewportState->pScissors) {
        const size_t pCreateInfos_proto_pViewportState_proto_pScissors_length = pCreateInfos_i->pViewportState->scissorCount;
        for (int pScissors_indx = 0; pScissors_indx < pCreateInfos_proto_pViewportState_proto_pScissors_length; pScissors_indx++) {
          vvk::server::VkRect2D* pCreateInfos_proto_pViewportState_proto_pScissors_proto = pCreateInfos_proto_pViewportState_proto->add_pscissors();
          vvk::server::VkOffset2D* pCreateInfos_proto_pViewportState_proto_pScissors_proto_offset_proto = pCreateInfos_proto_pViewportState_proto_pScissors_proto->mutable_offset();
          pCreateInfos_proto_pViewportState_proto_pScissors_proto_offset_proto->set_x((&(&pCreateInfos_i->pViewportState->pScissors[pScissors_indx])->offset)->x);
          pCreateInfos_proto_pViewportState_proto_pScissors_proto_offset_proto->set_y((&(&pCreateInfos_i->pViewportState->pScissors[pScissors_indx])->offset)->y);
          vvk::server::VkExtent2D* pCreateInfos_proto_pViewportState_proto_pScissors_proto_extent_proto = pCreateInfos_proto_pViewportState_proto_pScissors_proto->mutable_extent();
          pCreateInfos_proto_pViewportState_proto_pScissors_proto_extent_proto->set_width((&(&pCreateInfos_i->pViewportState->pScissors[pScissors_indx])->extent)->width);
          pCreateInfos_proto_pViewportState_proto_pScissors_proto_extent_proto->set_height((&(&pCreateInfos_i->pViewportState->pScissors[pScissors_indx])->extent)->height);
        }
      }
    }
    if (pCreateInfos_i->pRasterizationState) {
      vvk::server::VkPipelineRasterizationStateCreateInfo* pCreateInfos_proto_pRasterizationState_proto = pCreateInfos_proto->mutable_prasterizationstate();
      if (pCreateInfos_i->pRasterizationState->pNext) {
        // pNext chains are currently not supported
      }
      if (pCreateInfos_i->pRasterizationState->flags) {
        pCreateInfos_proto_pRasterizationState_proto->set_flags(pCreateInfos_i->pRasterizationState->flags);
      }
      pCreateInfos_proto_pRasterizationState_proto->set_depthclampenable(pCreateInfos_i->pRasterizationState->depthClampEnable);
      pCreateInfos_proto_pRasterizationState_proto->set_rasterizerdiscardenable(pCreateInfos_i->pRasterizationState->rasterizerDiscardEnable);
      pCreateInfos_proto_pRasterizationState_proto->set_polygonmode(static_cast<vvk::server::VkPolygonMode>(pCreateInfos_i->pRasterizationState->polygonMode));
      if (pCreateInfos_i->pRasterizationState->cullMode) {
        pCreateInfos_proto_pRasterizationState_proto->set_cullmode(pCreateInfos_i->pRasterizationState->cullMode);
      }
      pCreateInfos_proto_pRasterizationState_proto->set_frontface(static_cast<vvk::server::VkFrontFace>(pCreateInfos_i->pRasterizationState->frontFace));
      pCreateInfos_proto_pRasterizationState_proto->set_depthbiasenable(pCreateInfos_i->pRasterizationState->depthBiasEnable);
      pCreateInfos_proto_pRasterizationState_proto->set_depthbiasconstantfactor(pCreateInfos_i->pRasterizationState->depthBiasConstantFactor);
      pCreateInfos_proto_pRasterizationState_proto->set_depthbiasclamp(pCreateInfos_i->pRasterizationState->depthBiasClamp);
      pCreateInfos_proto_pRasterizationState_proto->set_depthbiasslopefactor(pCreateInfos_i->pRasterizationState->depthBiasSlopeFactor);
      pCreateInfos_proto_pRasterizationState_proto->set_linewidth(pCreateInfos_i->pRasterizationState->lineWidth);
    }
    if (pCreateInfos_i->pMultisampleState) {
      vvk::server::VkPipelineMultisampleStateCreateInfo* pCreateInfos_proto_pMultisampleState_proto = pCreateInfos_proto->mutable_pmultisamplestate();
      if (pCreateInfos_i->pMultisampleState->pNext) {
        // pNext chains are currently not supported
      }
      if (pCreateInfos_i->pMultisampleState->flags) {
        pCreateInfos_proto_pMultisampleState_proto->set_flags(pCreateInfos_i->pMultisampleState->flags);
      }
      pCreateInfos_proto_pMultisampleState_proto->set_rasterizationsamples(pCreateInfos_i->pMultisampleState->rasterizationSamples);
      pCreateInfos_proto_pMultisampleState_proto->set_sampleshadingenable(pCreateInfos_i->pMultisampleState->sampleShadingEnable);
      pCreateInfos_proto_pMultisampleState_proto->set_minsampleshading(pCreateInfos_i->pMultisampleState->minSampleShading);
      if (pCreateInfos_i->pMultisampleState->pSampleMask) {
        const size_t pCreateInfos_proto_pMultisampleState_proto_pSampleMask_length = (pCreateInfos_i->pMultisampleState->rasterizationSamples + 31) / 32;
        for (int pSampleMask_indx = 0; pSampleMask_indx < pCreateInfos_proto_pMultisampleState_proto_pSampleMask_length; pSampleMask_indx++) {
          pCreateInfos_proto_pMultisampleState_proto->add_psamplemask(static_cast<uint32_t>(pCreateInfos_i->pMultisampleState->pSampleMask[pSampleMask_indx]));
        }
      }
      pCreateInfos_proto_pMultisampleState_proto->set_alphatocoverageenable(pCreateInfos_i->pMultisampleState->alphaToCoverageEnable);
      pCreateInfos_proto_pMultisampleState_proto->set_alphatooneenable(pCreateInfos_i->pMultisampleState->alphaToOneEnable);
    }
    if (pCreateInfos_i->pDepthStencilState) {
      vvk::server::VkPipelineDepthStencilStateCreateInfo* pCreateInfos_proto_pDepthStencilState_proto = pCreateInfos_proto->mutable_pdepthstencilstate();
      if (pCreateInfos_i->pDepthStencilState->pNext) {
        // pNext chains are currently not supported
      }
      if (pCreateInfos_i->pDepthStencilState->flags) {
        pCreateInfos_proto_pDepthStencilState_proto->set_flags(pCreateInfos_i->pDepthStencilState->flags);
      }
      pCreateInfos_proto_pDepthStencilState_proto->set_depthtestenable(pCreateInfos_i->pDepthStencilState->depthTestEnable);
      pCreateInfos_proto_pDepthStencilState_proto->set_depthwriteenable(pCreateInfos_i->pDepthStencilState->depthWriteEnable);
      pCreateInfos_proto_pDepthStencilState_proto->set_depthcompareop(static_cast<vvk::server::VkCompareOp>(pCreateInfos_i->pDepthStencilState->depthCompareOp));
      pCreateInfos_proto_pDepthStencilState_proto->set_depthboundstestenable(pCreateInfos_i->pDepthStencilState->depthBoundsTestEnable);
      pCreateInfos_proto_pDepthStencilState_proto->set_stenciltestenable(pCreateInfos_i->pDepthStencilState->stencilTestEnable);
      vvk::server::VkStencilOpState* pCreateInfos_proto_pDepthStencilState_proto_front_proto = pCreateInfos_proto_pDepthStencilState_proto->mutable_front();
      pCreateInfos_proto_pDepthStencilState_proto_front_proto->set_failop(static_cast<vvk::server::VkStencilOp>((&pCreateInfos_i->pDepthStencilState->front)->failOp));
      pCreateInfos_proto_pDepthStencilState_proto_front_proto->set_passop(static_cast<vvk::server::VkStencilOp>((&pCreateInfos_i->pDepthStencilState->front)->passOp));
      pCreateInfos_proto_pDepthStencilState_proto_front_proto->set_depthfailop(static_cast<vvk::server::VkStencilOp>((&pCreateInfos_i->pDepthStencilState->front)->depthFailOp));
      pCreateInfos_proto_pDepthStencilState_proto_front_proto->set_compareop(static_cast<vvk::server::VkCompareOp>((&pCreateInfos_i->pDepthStencilState->front)->compareOp));
      pCreateInfos_proto_pDepthStencilState_proto_front_proto->set_comparemask((&pCreateInfos_i->pDepthStencilState->front)->compareMask);
      pCreateInfos_proto_pDepthStencilState_proto_front_proto->set_writemask((&pCreateInfos_i->pDepthStencilState->front)->writeMask);
      pCreateInfos_proto_pDepthStencilState_proto_front_proto->set_reference((&pCreateInfos_i->pDepthStencilState->front)->reference);
      vvk::server::VkStencilOpState* pCreateInfos_proto_pDepthStencilState_proto_back_proto = pCreateInfos_proto_pDepthStencilState_proto->mutable_back();
      pCreateInfos_proto_pDepthStencilState_proto_back_proto->set_failop(static_cast<vvk::server::VkStencilOp>((&pCreateInfos_i->pDepthStencilState->back)->failOp));
      pCreateInfos_proto_pDepthStencilState_proto_back_proto->set_passop(static_cast<vvk::server::VkStencilOp>((&pCreateInfos_i->pDepthStencilState->back)->passOp));
      pCreateInfos_proto_pDepthStencilState_proto_back_proto->set_depthfailop(static_cast<vvk::server::VkStencilOp>((&pCreateInfos_i->pDepthStencilState->back)->depthFailOp));
      pCreateInfos_proto_pDepthStencilState_proto_back_proto->set_compareop(static_cast<vvk::server::VkCompareOp>((&pCreateInfos_i->pDepthStencilState->back)->compareOp));
      pCreateInfos_proto_pDepthStencilState_proto_back_proto->set_comparemask((&pCreateInfos_i->pDepthStencilState->back)->compareMask);
      pCreateInfos_proto_pDepthStencilState_proto_back_proto->set_writemask((&pCreateInfos_i->pDepthStencilState->back)->writeMask);
      pCreateInfos_proto_pDepthStencilState_proto_back_proto->set_reference((&pCreateInfos_i->pDepthStencilState->back)->reference);
      pCreateInfos_proto_pDepthStencilState_proto->set_mindepthbounds(pCreateInfos_i->pDepthStencilState->minDepthBounds);
      pCreateInfos_proto_pDepthStencilState_proto->set_maxdepthbounds(pCreateInfos_i->pDepthStencilState->maxDepthBounds);
    }
    if (pCreateInfos_i->pColorBlendState) {
      vvk::server::VkPipelineColorBlendStateCreateInfo* pCreateInfos_proto_pColorBlendState_proto = pCreateInfos_proto->mutable_pcolorblendstate();
      if (pCreateInfos_i->pColorBlendState->pNext) {
        // pNext chains are currently not supported
      }
      if (pCreateInfos_i->pColorBlendState->flags) {
        pCreateInfos_proto_pColorBlendState_proto->set_flags(pCreateInfos_i->pColorBlendState->flags);
      }
      pCreateInfos_proto_pColorBlendState_proto->set_logicopenable(pCreateInfos_i->pColorBlendState->logicOpEnable);
      pCreateInfos_proto_pColorBlendState_proto->set_logicop(static_cast<vvk::server::VkLogicOp>(pCreateInfos_i->pColorBlendState->logicOp));
      if (pCreateInfos_i->pColorBlendState->attachmentCount) {
        pCreateInfos_proto_pColorBlendState_proto->set_attachmentcount(pCreateInfos_i->pColorBlendState->attachmentCount);
      }
      if (pCreateInfos_i->pColorBlendState->pAttachments) {
        const size_t pCreateInfos_proto_pColorBlendState_proto_pAttachments_length = pCreateInfos_i->pColorBlendState->attachmentCount;
        for (int pAttachments_indx = 0; pAttachments_indx < pCreateInfos_proto_pColorBlendState_proto_pAttachments_length; pAttachments_indx++) {
          vvk::server::VkPipelineColorBlendAttachmentState* pCreateInfos_proto_pColorBlendState_proto_pAttachments_proto = pCreateInfos_proto_pColorBlendState_proto->add_pattachments();
          pCreateInfos_proto_pColorBlendState_proto_pAttachments_proto->set_blendenable((&pCreateInfos_i->pColorBlendState->pAttachments[pAttachments_indx])->blendEnable);
          pCreateInfos_proto_pColorBlendState_proto_pAttachments_proto->set_srccolorblendfactor(static_cast<vvk::server::VkBlendFactor>((&pCreateInfos_i->pColorBlendState->pAttachments[pAttachments_indx])->srcColorBlendFactor));
          pCreateInfos_proto_pColorBlendState_proto_pAttachments_proto->set_dstcolorblendfactor(static_cast<vvk::server::VkBlendFactor>((&pCreateInfos_i->pColorBlendState->pAttachments[pAttachments_indx])->dstColorBlendFactor));
          pCreateInfos_proto_pColorBlendState_proto_pAttachments_proto->set_colorblendop(static_cast<vvk::server::VkBlendOp>((&pCreateInfos_i->pColorBlendState->pAttachments[pAttachments_indx])->colorBlendOp));
          pCreateInfos_proto_pColorBlendState_proto_pAttachments_proto->set_srcalphablendfactor(static_cast<vvk::server::VkBlendFactor>((&pCreateInfos_i->pColorBlendState->pAttachments[pAttachments_indx])->srcAlphaBlendFactor));
          pCreateInfos_proto_pColorBlendState_proto_pAttachments_proto->set_dstalphablendfactor(static_cast<vvk::server::VkBlendFactor>((&pCreateInfos_i->pColorBlendState->pAttachments[pAttachments_indx])->dstAlphaBlendFactor));
          pCreateInfos_proto_pColorBlendState_proto_pAttachments_proto->set_alphablendop(static_cast<vvk::server::VkBlendOp>((&pCreateInfos_i->pColorBlendState->pAttachments[pAttachments_indx])->alphaBlendOp));
          if ((&pCreateInfos_i->pColorBlendState->pAttachments[pAttachments_indx])->colorWriteMask) {
            pCreateInfos_proto_pColorBlendState_proto_pAttachments_proto->set_colorwritemask((&pCreateInfos_i->pColorBlendState->pAttachments[pAttachments_indx])->colorWriteMask);
          }
        }
      }
      const size_t pCreateInfos_proto_pColorBlendState_proto_blendConstants_length = 4;
      for (int blendConstants_indx = 0; blendConstants_indx < pCreateInfos_proto_pColorBlendState_proto_blendConstants_length; blendConstants_indx++) {
        pCreateInfos_proto_pColorBlendState_proto->add_blendconstants(pCreateInfos_i->pColorBlendState->blendConstants[blendConstants_indx]);
      }
    }
    if (pCreateInfos_i->pDynamicState) {
      vvk::server::VkPipelineDynamicStateCreateInfo* pCreateInfos_proto_pDynamicState_proto = pCreateInfos_proto->mutable_pdynamicstate();
      if (pCreateInfos_i->pDynamicState->pNext) {
        // pNext chains are currently not supported
      }
      if (pCreateInfos_i->pDynamicState->flags) {
        pCreateInfos_proto_pDynamicState_proto->set_flags(pCreateInfos_i->pDynamicState->flags);
      }
      if (pCreateInfos_i->pDynamicState->dynamicStateCount) {
        pCreateInfos_proto_pDynamicState_proto->set_dynamicstatecount(pCreateInfos_i->pDynamicState->dynamicStateCount);
      }
      const size_t pCreateInfos_proto_pDynamicState_proto_pDynamicStates_length = pCreateInfos_i->pDynamicState->dynamicStateCount;
      for (int pDynamicStates_indx = 0; pDynamicStates_indx < pCreateInfos_proto_pDynamicState_proto_pDynamicStates_length; pDynamicStates_indx++) {
        pCreateInfos_proto_pDynamicState_proto->add_pdynamicstates(static_cast<vvk::server::VkDynamicState>(pCreateInfos_i->pDynamicState->pDynamicStates[pDynamicStates_indx]));
      }
    }
    if (pCreateInfos_i->layout) {
      pCreateInfos_proto->set_layout(reinterpret_cast<uint64_t>(pCreateInfos_i->layout));
    }
    if (pCreateInfos_i->renderPass) {
      pCreateInfos_proto->set_renderpass(reinterpret_cast<uint64_t>(pCreateInfos_i->renderPass));
    }
    pCreateInfos_proto->set_subpass(pCreateInfos_i->subpass);
    if (pCreateInfos_i->basePipelineHandle) {
      pCreateInfos_proto->set_basepipelinehandle(reinterpret_cast<uint64_t>(pCreateInfos_i->basePipelineHandle));
    }
    pCreateInfos_proto->set_basepipelineindex(pCreateInfos_i->basePipelineIndex);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  for (int i = 0; i < createInfoCount; i++) {
    pPipelines[i] = reinterpret_cast<VkPipeline>(response.vkcreategraphicspipelines().ppipelines(i));
  }
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkDestroyPipeline(VvkCommandClientBidiStream& stream, VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkDestroyPipeline");
  request.mutable_vkdestroypipeline()->set_device(reinterpret_cast<uint64_t>(device));
  if (pipeline) {
    request.mutable_vkdestroypipeline()->set_pipeline(reinterpret_cast<uint64_t>(pipeline));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
VkResult PackAndCallVkCreateFramebuffer(VvkCommandClientBidiStream& stream, VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateFramebuffer");
  request.mutable_vkcreateframebuffer()->set_device(reinterpret_cast<uint64_t>(device));
  vvk::server::VkFramebufferCreateInfo* pCreateInfo_proto = request.mutable_vkcreateframebuffer()->mutable_pcreateinfo();
  if (pCreateInfo->pNext) {
    // pNext chains are currently not supported
  }
  if (pCreateInfo->flags) {
    pCreateInfo_proto->set_flags(pCreateInfo->flags);
  }
  pCreateInfo_proto->set_renderpass(reinterpret_cast<uint64_t>(pCreateInfo->renderPass));
  if (pCreateInfo->attachmentCount) {
    pCreateInfo_proto->set_attachmentcount(pCreateInfo->attachmentCount);
  }
  const size_t pCreateInfo_proto_pAttachments_length = pCreateInfo->attachmentCount;
  for (int pAttachments_indx = 0; pAttachments_indx < pCreateInfo_proto_pAttachments_length; pAttachments_indx++) {
    pCreateInfo_proto->add_pattachments(reinterpret_cast<uint64_t>(pCreateInfo->pAttachments[pAttachments_indx]));
  }
  pCreateInfo_proto->set_width(pCreateInfo->width);
  pCreateInfo_proto->set_height(pCreateInfo->height);
  pCreateInfo_proto->set_layers(pCreateInfo->layers);
  request.mutable_vkcreateframebuffer()->set_pframebuffer(reinterpret_cast<uint64_t>(*pFramebuffer));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pFramebuffer = reinterpret_cast<VkFramebuffer>(response.vkcreateframebuffer().pframebuffer());
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkDestroyFramebuffer(VvkCommandClientBidiStream& stream, VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkDestroyFramebuffer");
  request.mutable_vkdestroyframebuffer()->set_device(reinterpret_cast<uint64_t>(device));
  if (framebuffer) {
    request.mutable_vkdestroyframebuffer()->set_framebuffer(reinterpret_cast<uint64_t>(framebuffer));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
VkResult PackAndCallVkWaitForFences(VvkCommandClientBidiStream& stream, VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout) {
  vvk::server::VvkRequest request;
  request.set_method("vkWaitForFences");
  request.mutable_vkwaitforfences()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkwaitforfences()->set_fencecount(fenceCount);
  for (int i = 0; i < fenceCount; i++) {
    request.mutable_vkwaitforfences()->add_pfences(reinterpret_cast<uint64_t>(pFences[i]));
  }
  request.mutable_vkwaitforfences()->set_waitall(waitAll);
  request.mutable_vkwaitforfences()->set_timeout(timeout);
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.result());
}
VkResult PackAndCallVkResetFences(VvkCommandClientBidiStream& stream, VkDevice device, uint32_t fenceCount, const VkFence* pFences) {
  vvk::server::VvkRequest request;
  request.set_method("vkResetFences");
  request.mutable_vkresetfences()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkresetfences()->set_fencecount(fenceCount);
  for (int i = 0; i < fenceCount; i++) {
    request.mutable_vkresetfences()->add_pfences(reinterpret_cast<uint64_t>(pFences[i]));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.result());
}
VkResult PackAndCallVkResetCommandPool(VvkCommandClientBidiStream& stream, VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags) {
  vvk::server::VvkRequest request;
  request.set_method("vkResetCommandPool");
  request.mutable_vkresetcommandpool()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkresetcommandpool()->set_commandpool(reinterpret_cast<uint64_t>(commandPool));
  if (flags) {
    request.mutable_vkresetcommandpool()->set_flags(flags);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkCmdBeginRenderPass(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents) {
  vvk::server::VvkRequest request;
  request.set_method("vkCmdBeginRenderPass");
  request.mutable_vkcmdbeginrenderpass()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  vvk::server::VkRenderPassBeginInfo* pRenderPassBegin_proto = request.mutable_vkcmdbeginrenderpass()->mutable_prenderpassbegin();
  if (pRenderPassBegin->pNext) {
    // pNext chains are currently not supported
  }
  pRenderPassBegin_proto->set_renderpass(reinterpret_cast<uint64_t>(pRenderPassBegin->renderPass));
  pRenderPassBegin_proto->set_framebuffer(reinterpret_cast<uint64_t>(pRenderPassBegin->framebuffer));
  vvk::server::VkRect2D* pRenderPassBegin_proto_renderArea_proto = pRenderPassBegin_proto->mutable_renderarea();
  vvk::server::VkOffset2D* pRenderPassBegin_proto_renderArea_proto_offset_proto = pRenderPassBegin_proto_renderArea_proto->mutable_offset();
  pRenderPassBegin_proto_renderArea_proto_offset_proto->set_x((&(&pRenderPassBegin->renderArea)->offset)->x);
  pRenderPassBegin_proto_renderArea_proto_offset_proto->set_y((&(&pRenderPassBegin->renderArea)->offset)->y);
  vvk::server::VkExtent2D* pRenderPassBegin_proto_renderArea_proto_extent_proto = pRenderPassBegin_proto_renderArea_proto->mutable_extent();
  pRenderPassBegin_proto_renderArea_proto_extent_proto->set_width((&(&pRenderPassBegin->renderArea)->extent)->width);
  pRenderPassBegin_proto_renderArea_proto_extent_proto->set_height((&(&pRenderPassBegin->renderArea)->extent)->height);
  if (pRenderPassBegin->clearValueCount) {
    pRenderPassBegin_proto->set_clearvaluecount(pRenderPassBegin->clearValueCount);
  }
  const size_t pRenderPassBegin_proto_pClearValues_length = pRenderPassBegin->clearValueCount;
  for (int pClearValues_indx = 0; pClearValues_indx < pRenderPassBegin_proto_pClearValues_length; pClearValues_indx++) {
    vvk::server::VkClearValue* pRenderPassBegin_proto_pClearValues_proto = pRenderPassBegin_proto->add_pclearvalues();
    vvk::server::VkClearColorValue* pRenderPassBegin_proto_pClearValues_proto_color_proto = pRenderPassBegin_proto_pClearValues_proto->mutable_color();
    const size_t pRenderPassBegin_proto_pClearValues_proto_color_proto_float32_length = 4;
    for (int float32_indx = 0; float32_indx < pRenderPassBegin_proto_pClearValues_proto_color_proto_float32_length; float32_indx++) {
      pRenderPassBegin_proto_pClearValues_proto_color_proto->add_float32((&(&pRenderPassBegin->pClearValues[pClearValues_indx])->color)->float32[float32_indx]);
    }
    const size_t pRenderPassBegin_proto_pClearValues_proto_color_proto_int32_length = 4;
    for (int int32_indx = 0; int32_indx < pRenderPassBegin_proto_pClearValues_proto_color_proto_int32_length; int32_indx++) {
      pRenderPassBegin_proto_pClearValues_proto_color_proto->add_int32((&(&pRenderPassBegin->pClearValues[pClearValues_indx])->color)->int32[int32_indx]);
    }
    const size_t pRenderPassBegin_proto_pClearValues_proto_color_proto_uint32_length = 4;
    for (int uint32_indx = 0; uint32_indx < pRenderPassBegin_proto_pClearValues_proto_color_proto_uint32_length; uint32_indx++) {
      pRenderPassBegin_proto_pClearValues_proto_color_proto->add_uint32((&(&pRenderPassBegin->pClearValues[pClearValues_indx])->color)->uint32[uint32_indx]);
    }
    vvk::server::VkClearDepthStencilValue* pRenderPassBegin_proto_pClearValues_proto_depthStencil_proto = pRenderPassBegin_proto_pClearValues_proto->mutable_depthstencil();
    pRenderPassBegin_proto_pClearValues_proto_depthStencil_proto->set_depth((&(&pRenderPassBegin->pClearValues[pClearValues_indx])->depthStencil)->depth);
    pRenderPassBegin_proto_pClearValues_proto_depthStencil_proto->set_stencil((&(&pRenderPassBegin->pClearValues[pClearValues_indx])->depthStencil)->stencil);
  }
  request.mutable_vkcmdbeginrenderpass()->set_contents(static_cast<vvk::server::VkSubpassContents>(contents));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
void PackAndCallVkCmdEndRenderPass(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer) {
  vvk::server::VvkRequest request;
  request.set_method("vkCmdEndRenderPass");
  request.mutable_vkcmdendrenderpass()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
void PackAndCallVkCmdBindPipeline(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) {
  vvk::server::VvkRequest request;
  request.set_method("vkCmdBindPipeline");
  request.mutable_vkcmdbindpipeline()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  request.mutable_vkcmdbindpipeline()->set_pipelinebindpoint(static_cast<vvk::server::VkPipelineBindPoint>(pipelineBindPoint));
  request.mutable_vkcmdbindpipeline()->set_pipeline(reinterpret_cast<uint64_t>(pipeline));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
void PackAndCallVkCmdSetViewport(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports) {
  vvk::server::VvkRequest request;
  request.set_method("vkCmdSetViewport");
  request.mutable_vkcmdsetviewport()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  request.mutable_vkcmdsetviewport()->set_firstviewport(firstViewport);
  request.mutable_vkcmdsetviewport()->set_viewportcount(viewportCount);
  for (int pViewports_indx = 0; pViewports_indx < viewportCount; pViewports_indx++) {
    vvk::server::VkViewport* pViewports_proto = request.mutable_vkcmdsetviewport()->add_pviewports();
    const VkViewport* pViewports_i = &pViewports[pViewports_indx];
    pViewports_proto->set_x(pViewports_i->x);
    pViewports_proto->set_y(pViewports_i->y);
    pViewports_proto->set_width(pViewports_i->width);
    pViewports_proto->set_height(pViewports_i->height);
    pViewports_proto->set_mindepth(pViewports_i->minDepth);
    pViewports_proto->set_maxdepth(pViewports_i->maxDepth);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
void PackAndCallVkCmdSetScissor(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors) {
  vvk::server::VvkRequest request;
  request.set_method("vkCmdSetScissor");
  request.mutable_vkcmdsetscissor()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  request.mutable_vkcmdsetscissor()->set_firstscissor(firstScissor);
  request.mutable_vkcmdsetscissor()->set_scissorcount(scissorCount);
  for (int pScissors_indx = 0; pScissors_indx < scissorCount; pScissors_indx++) {
    vvk::server::VkRect2D* pScissors_proto = request.mutable_vkcmdsetscissor()->add_pscissors();
    const VkRect2D* pScissors_i = &pScissors[pScissors_indx];
    vvk::server::VkOffset2D* pScissors_proto_offset_proto = pScissors_proto->mutable_offset();
    pScissors_proto_offset_proto->set_x((&pScissors_i->offset)->x);
    pScissors_proto_offset_proto->set_y((&pScissors_i->offset)->y);
    vvk::server::VkExtent2D* pScissors_proto_extent_proto = pScissors_proto->mutable_extent();
    pScissors_proto_extent_proto->set_width((&pScissors_i->extent)->width);
    pScissors_proto_extent_proto->set_height((&pScissors_i->extent)->height);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
void PackAndCallVkCmdDraw(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
  vvk::server::VvkRequest request;
  request.set_method("vkCmdDraw");
  request.mutable_vkcmddraw()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  request.mutable_vkcmddraw()->set_vertexcount(vertexCount);
  request.mutable_vkcmddraw()->set_instancecount(instanceCount);
  request.mutable_vkcmddraw()->set_firstvertex(firstVertex);
  request.mutable_vkcmddraw()->set_firstinstance(firstInstance);
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
VkResult PackAndCallVkQueueSubmit(VvkCommandClientBidiStream& stream, VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence) {
  vvk::server::VvkRequest request;
  request.set_method("vkQueueSubmit");
  request.mutable_vkqueuesubmit()->set_queue(reinterpret_cast<uint64_t>(queue));
  if (submitCount) {
    request.mutable_vkqueuesubmit()->set_submitcount(submitCount);
  }
  for (int pSubmits_indx = 0; pSubmits_indx < submitCount; pSubmits_indx++) {
    vvk::server::VkSubmitInfo* pSubmits_proto = request.mutable_vkqueuesubmit()->add_psubmits();
    const VkSubmitInfo* pSubmits_i = &pSubmits[pSubmits_indx];
    if (pSubmits_i->pNext) {
      // pNext chains are currently not supported
    }
    if (pSubmits_i->waitSemaphoreCount) {
      pSubmits_proto->set_waitsemaphorecount(pSubmits_i->waitSemaphoreCount);
    }
    const size_t pSubmits_proto_pWaitSemaphores_length = pSubmits_i->waitSemaphoreCount;
    for (int pWaitSemaphores_indx = 0; pWaitSemaphores_indx < pSubmits_proto_pWaitSemaphores_length; pWaitSemaphores_indx++) {
      pSubmits_proto->add_pwaitsemaphores(reinterpret_cast<uint64_t>(pSubmits_i->pWaitSemaphores[pWaitSemaphores_indx]));
    }
    const size_t pSubmits_proto_pWaitDstStageMask_length = pSubmits_i->waitSemaphoreCount;
    for (int pWaitDstStageMask_indx = 0; pWaitDstStageMask_indx < pSubmits_proto_pWaitDstStageMask_length; pWaitDstStageMask_indx++) {
      pSubmits_proto->add_pwaitdststagemask(static_cast<VkPipelineStageFlags>(pSubmits_i->pWaitDstStageMask[pWaitDstStageMask_indx]));
    }
    if (pSubmits_i->commandBufferCount) {
      pSubmits_proto->set_commandbuffercount(pSubmits_i->commandBufferCount);
    }
    const size_t pSubmits_proto_pCommandBuffers_length = pSubmits_i->commandBufferCount;
    for (int pCommandBuffers_indx = 0; pCommandBuffers_indx < pSubmits_proto_pCommandBuffers_length; pCommandBuffers_indx++) {
      pSubmits_proto->add_pcommandbuffers(reinterpret_cast<uint64_t>(pSubmits_i->pCommandBuffers[pCommandBuffers_indx]));
    }
    if (pSubmits_i->signalSemaphoreCount) {
      pSubmits_proto->set_signalsemaphorecount(pSubmits_i->signalSemaphoreCount);
    }
    const size_t pSubmits_proto_pSignalSemaphores_length = pSubmits_i->signalSemaphoreCount;
    for (int pSignalSemaphores_indx = 0; pSignalSemaphores_indx < pSubmits_proto_pSignalSemaphores_length; pSignalSemaphores_indx++) {
      pSubmits_proto->add_psignalsemaphores(reinterpret_cast<uint64_t>(pSubmits_i->pSignalSemaphores[pSignalSemaphores_indx]));
    }
  }
  if (fence) {
    request.mutable_vkqueuesubmit()->set_fence(reinterpret_cast<uint64_t>(fence));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.result());
}
VkResult PackAndCallVkDeviceWaitIdle(VvkCommandClientBidiStream& stream, VkDevice device) {
  vvk::server::VvkRequest request;
  request.set_method("vkDeviceWaitIdle");
  request.mutable_vkdevicewaitidle()->set_device(reinterpret_cast<uint64_t>(device));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.result());
}
VkResult PackAndCallVkQueueWaitIdle(VvkCommandClientBidiStream& stream, VkQueue queue) {
  vvk::server::VvkRequest request;
  request.set_method("vkQueueWaitIdle");
  request.mutable_vkqueuewaitidle()->set_queue(reinterpret_cast<uint64_t>(queue));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.result());
}
void PackAndCallVkCmdPipelineBarrier(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) {
  vvk::server::VvkRequest request;
  request.set_method("vkCmdPipelineBarrier");
  request.mutable_vkcmdpipelinebarrier()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  if (srcStageMask) {
    request.mutable_vkcmdpipelinebarrier()->set_srcstagemask(srcStageMask);
  }
  if (dstStageMask) {
    request.mutable_vkcmdpipelinebarrier()->set_dststagemask(dstStageMask);
  }
  if (dependencyFlags) {
    request.mutable_vkcmdpipelinebarrier()->set_dependencyflags(dependencyFlags);
  }
  if (memoryBarrierCount) {
    request.mutable_vkcmdpipelinebarrier()->set_memorybarriercount(memoryBarrierCount);
  }
  for (int pMemoryBarriers_indx = 0; pMemoryBarriers_indx < memoryBarrierCount; pMemoryBarriers_indx++) {
    vvk::server::VkMemoryBarrier* pMemoryBarriers_proto = request.mutable_vkcmdpipelinebarrier()->add_pmemorybarriers();
    const VkMemoryBarrier* pMemoryBarriers_i = &pMemoryBarriers[pMemoryBarriers_indx];
    if (pMemoryBarriers_i->pNext) {
      // pNext chains are currently not supported
    }
    if (pMemoryBarriers_i->srcAccessMask) {
      pMemoryBarriers_proto->set_srcaccessmask(pMemoryBarriers_i->srcAccessMask);
    }
    if (pMemoryBarriers_i->dstAccessMask) {
      pMemoryBarriers_proto->set_dstaccessmask(pMemoryBarriers_i->dstAccessMask);
    }
  }
  if (bufferMemoryBarrierCount) {
    request.mutable_vkcmdpipelinebarrier()->set_buffermemorybarriercount(bufferMemoryBarrierCount);
  }
  for (int pBufferMemoryBarriers_indx = 0; pBufferMemoryBarriers_indx < bufferMemoryBarrierCount; pBufferMemoryBarriers_indx++) {
    vvk::server::VkBufferMemoryBarrier* pBufferMemoryBarriers_proto = request.mutable_vkcmdpipelinebarrier()->add_pbuffermemorybarriers();
    const VkBufferMemoryBarrier* pBufferMemoryBarriers_i = &pBufferMemoryBarriers[pBufferMemoryBarriers_indx];
    if (pBufferMemoryBarriers_i->pNext) {
      // pNext chains are currently not supported
    }
    pBufferMemoryBarriers_proto->set_srcaccessmask(pBufferMemoryBarriers_i->srcAccessMask);
    pBufferMemoryBarriers_proto->set_dstaccessmask(pBufferMemoryBarriers_i->dstAccessMask);
    pBufferMemoryBarriers_proto->set_srcqueuefamilyindex(pBufferMemoryBarriers_i->srcQueueFamilyIndex);
    pBufferMemoryBarriers_proto->set_dstqueuefamilyindex(pBufferMemoryBarriers_i->dstQueueFamilyIndex);
    pBufferMemoryBarriers_proto->set_buffer(reinterpret_cast<uint64_t>(pBufferMemoryBarriers_i->buffer));
    pBufferMemoryBarriers_proto->set_offset(static_cast<uint64_t>(pBufferMemoryBarriers_i->offset));
    pBufferMemoryBarriers_proto->set_size(static_cast<uint64_t>(pBufferMemoryBarriers_i->size));
  }
  if (imageMemoryBarrierCount) {
    request.mutable_vkcmdpipelinebarrier()->set_imagememorybarriercount(imageMemoryBarrierCount);
  }
  for (int pImageMemoryBarriers_indx = 0; pImageMemoryBarriers_indx < imageMemoryBarrierCount; pImageMemoryBarriers_indx++) {
    vvk::server::VkImageMemoryBarrier* pImageMemoryBarriers_proto = request.mutable_vkcmdpipelinebarrier()->add_pimagememorybarriers();
    const VkImageMemoryBarrier* pImageMemoryBarriers_i = &pImageMemoryBarriers[pImageMemoryBarriers_indx];
    if (pImageMemoryBarriers_i->pNext) {
      // pNext chains are currently not supported
    }
    pImageMemoryBarriers_proto->set_srcaccessmask(pImageMemoryBarriers_i->srcAccessMask);
    pImageMemoryBarriers_proto->set_dstaccessmask(pImageMemoryBarriers_i->dstAccessMask);
    pImageMemoryBarriers_proto->set_oldlayout(static_cast<vvk::server::VkImageLayout>(pImageMemoryBarriers_i->oldLayout));
    pImageMemoryBarriers_proto->set_newlayout(static_cast<vvk::server::VkImageLayout>(pImageMemoryBarriers_i->newLayout));
    pImageMemoryBarriers_proto->set_srcqueuefamilyindex(pImageMemoryBarriers_i->srcQueueFamilyIndex);
    pImageMemoryBarriers_proto->set_dstqueuefamilyindex(pImageMemoryBarriers_i->dstQueueFamilyIndex);
    pImageMemoryBarriers_proto->set_image(reinterpret_cast<uint64_t>(pImageMemoryBarriers_i->image));
    vvk::server::VkImageSubresourceRange* pImageMemoryBarriers_proto_subresourceRange_proto = pImageMemoryBarriers_proto->mutable_subresourcerange();
    pImageMemoryBarriers_proto_subresourceRange_proto->set_aspectmask((&pImageMemoryBarriers_i->subresourceRange)->aspectMask);
    pImageMemoryBarriers_proto_subresourceRange_proto->set_basemiplevel((&pImageMemoryBarriers_i->subresourceRange)->baseMipLevel);
    pImageMemoryBarriers_proto_subresourceRange_proto->set_levelcount((&pImageMemoryBarriers_i->subresourceRange)->levelCount);
    pImageMemoryBarriers_proto_subresourceRange_proto->set_basearraylayer((&pImageMemoryBarriers_i->subresourceRange)->baseArrayLayer);
    pImageMemoryBarriers_proto_subresourceRange_proto->set_layercount((&pImageMemoryBarriers_i->subresourceRange)->layerCount);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
void PackAndCallVkCmdCopyImageToBuffer(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions) {
  vvk::server::VvkRequest request;
  request.set_method("vkCmdCopyImageToBuffer");
  request.mutable_vkcmdcopyimagetobuffer()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  request.mutable_vkcmdcopyimagetobuffer()->set_srcimage(reinterpret_cast<uint64_t>(srcImage));
  request.mutable_vkcmdcopyimagetobuffer()->set_srcimagelayout(static_cast<vvk::server::VkImageLayout>(srcImageLayout));
  request.mutable_vkcmdcopyimagetobuffer()->set_dstbuffer(reinterpret_cast<uint64_t>(dstBuffer));
  request.mutable_vkcmdcopyimagetobuffer()->set_regioncount(regionCount);
  for (int pRegions_indx = 0; pRegions_indx < regionCount; pRegions_indx++) {
    vvk::server::VkBufferImageCopy* pRegions_proto = request.mutable_vkcmdcopyimagetobuffer()->add_pregions();
    const VkBufferImageCopy* pRegions_i = &pRegions[pRegions_indx];
    pRegions_proto->set_bufferoffset(static_cast<uint64_t>(pRegions_i->bufferOffset));
    pRegions_proto->set_bufferrowlength(pRegions_i->bufferRowLength);
    pRegions_proto->set_bufferimageheight(pRegions_i->bufferImageHeight);
    vvk::server::VkImageSubresourceLayers* pRegions_proto_imageSubresource_proto = pRegions_proto->mutable_imagesubresource();
    pRegions_proto_imageSubresource_proto->set_aspectmask((&pRegions_i->imageSubresource)->aspectMask);
    pRegions_proto_imageSubresource_proto->set_miplevel((&pRegions_i->imageSubresource)->mipLevel);
    pRegions_proto_imageSubresource_proto->set_basearraylayer((&pRegions_i->imageSubresource)->baseArrayLayer);
    pRegions_proto_imageSubresource_proto->set_layercount((&pRegions_i->imageSubresource)->layerCount);
    vvk::server::VkOffset3D* pRegions_proto_imageOffset_proto = pRegions_proto->mutable_imageoffset();
    pRegions_proto_imageOffset_proto->set_x((&pRegions_i->imageOffset)->x);
    pRegions_proto_imageOffset_proto->set_y((&pRegions_i->imageOffset)->y);
    pRegions_proto_imageOffset_proto->set_z((&pRegions_i->imageOffset)->z);
    vvk::server::VkExtent3D* pRegions_proto_imageExtent_proto = pRegions_proto->mutable_imageextent();
    pRegions_proto_imageExtent_proto->set_width((&pRegions_i->imageExtent)->width);
    pRegions_proto_imageExtent_proto->set_height((&pRegions_i->imageExtent)->height);
    pRegions_proto_imageExtent_proto->set_depth((&pRegions_i->imageExtent)->depth);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
}
void PackAndCallVkGetPhysicalDeviceProperties2(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2* pProperties) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetPhysicalDeviceProperties2");
  request.mutable_vkgetphysicaldeviceproperties2()->set_physicaldevice(reinterpret_cast<uint64_t>(physicalDevice));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  VkPhysicalDeviceProperties2& pProperties_ref = *pProperties;
  pProperties_ref.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
  pProperties_ref.pNext = nullptr; // pNext chains are currently unsupported
  VkPhysicalDeviceProperties &pProperties_ref_properties = pProperties_ref.properties;
  pProperties_ref_properties.apiVersion = response.vkgetphysicaldeviceproperties2().pproperties().properties().apiversion();
  pProperties_ref_properties.driverVersion = response.vkgetphysicaldeviceproperties2().pproperties().properties().driverversion();
  pProperties_ref_properties.vendorID = response.vkgetphysicaldeviceproperties2().pproperties().properties().vendorid();
  pProperties_ref_properties.deviceID = response.vkgetphysicaldeviceproperties2().pproperties().properties().deviceid();
  pProperties_ref_properties.deviceType = static_cast<VkPhysicalDeviceType>(response.vkgetphysicaldeviceproperties2().pproperties().properties().devicetype());
  strncpy(pProperties_ref_properties.deviceName, response.vkgetphysicaldeviceproperties2().pproperties().properties().devicename().c_str(), VK_MAX_PHYSICAL_DEVICE_NAME_SIZE);
  for (int pipelineCacheUUID_indx = 0; pipelineCacheUUID_indx < VK_UUID_SIZE; pipelineCacheUUID_indx++) {
    pProperties_ref_properties.pipelineCacheUUID[pipelineCacheUUID_indx] = static_cast<uint8_t>(response.vkgetphysicaldeviceproperties2().pproperties().properties().pipelinecacheuuid(pipelineCacheUUID_indx));
  }
  VkPhysicalDeviceLimits &pProperties_ref_properties_limits = pProperties_ref_properties.limits;
  pProperties_ref_properties_limits.maxImageDimension1D = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maximagedimension1d();
  pProperties_ref_properties_limits.maxImageDimension2D = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maximagedimension2d();
  pProperties_ref_properties_limits.maxImageDimension3D = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maximagedimension3d();
  pProperties_ref_properties_limits.maxImageDimensionCube = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maximagedimensioncube();
  pProperties_ref_properties_limits.maxImageArrayLayers = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maximagearraylayers();
  pProperties_ref_properties_limits.maxTexelBufferElements = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxtexelbufferelements();
  pProperties_ref_properties_limits.maxUniformBufferRange = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxuniformbufferrange();
  pProperties_ref_properties_limits.maxStorageBufferRange = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxstoragebufferrange();
  pProperties_ref_properties_limits.maxPushConstantsSize = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxpushconstantssize();
  pProperties_ref_properties_limits.maxMemoryAllocationCount = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxmemoryallocationcount();
  pProperties_ref_properties_limits.maxSamplerAllocationCount = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxsamplerallocationcount();
  pProperties_ref_properties_limits.bufferImageGranularity = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().bufferimagegranularity());
  pProperties_ref_properties_limits.sparseAddressSpaceSize = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().sparseaddressspacesize());
  pProperties_ref_properties_limits.maxBoundDescriptorSets = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxbounddescriptorsets();
  pProperties_ref_properties_limits.maxPerStageDescriptorSamplers = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxperstagedescriptorsamplers();
  pProperties_ref_properties_limits.maxPerStageDescriptorUniformBuffers = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxperstagedescriptoruniformbuffers();
  pProperties_ref_properties_limits.maxPerStageDescriptorStorageBuffers = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxperstagedescriptorstoragebuffers();
  pProperties_ref_properties_limits.maxPerStageDescriptorSampledImages = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxperstagedescriptorsampledimages();
  pProperties_ref_properties_limits.maxPerStageDescriptorStorageImages = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxperstagedescriptorstorageimages();
  pProperties_ref_properties_limits.maxPerStageDescriptorInputAttachments = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxperstagedescriptorinputattachments();
  pProperties_ref_properties_limits.maxPerStageResources = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxperstageresources();
  pProperties_ref_properties_limits.maxDescriptorSetSamplers = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxdescriptorsetsamplers();
  pProperties_ref_properties_limits.maxDescriptorSetUniformBuffers = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxdescriptorsetuniformbuffers();
  pProperties_ref_properties_limits.maxDescriptorSetUniformBuffersDynamic = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxdescriptorsetuniformbuffersdynamic();
  pProperties_ref_properties_limits.maxDescriptorSetStorageBuffers = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxdescriptorsetstoragebuffers();
  pProperties_ref_properties_limits.maxDescriptorSetStorageBuffersDynamic = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxdescriptorsetstoragebuffersdynamic();
  pProperties_ref_properties_limits.maxDescriptorSetSampledImages = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxdescriptorsetsampledimages();
  pProperties_ref_properties_limits.maxDescriptorSetStorageImages = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxdescriptorsetstorageimages();
  pProperties_ref_properties_limits.maxDescriptorSetInputAttachments = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxdescriptorsetinputattachments();
  pProperties_ref_properties_limits.maxVertexInputAttributes = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxvertexinputattributes();
  pProperties_ref_properties_limits.maxVertexInputBindings = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxvertexinputbindings();
  pProperties_ref_properties_limits.maxVertexInputAttributeOffset = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxvertexinputattributeoffset();
  pProperties_ref_properties_limits.maxVertexInputBindingStride = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxvertexinputbindingstride();
  pProperties_ref_properties_limits.maxVertexOutputComponents = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxvertexoutputcomponents();
  pProperties_ref_properties_limits.maxTessellationGenerationLevel = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxtessellationgenerationlevel();
  pProperties_ref_properties_limits.maxTessellationPatchSize = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxtessellationpatchsize();
  pProperties_ref_properties_limits.maxTessellationControlPerVertexInputComponents = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxtessellationcontrolpervertexinputcomponents();
  pProperties_ref_properties_limits.maxTessellationControlPerVertexOutputComponents = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxtessellationcontrolpervertexoutputcomponents();
  pProperties_ref_properties_limits.maxTessellationControlPerPatchOutputComponents = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxtessellationcontrolperpatchoutputcomponents();
  pProperties_ref_properties_limits.maxTessellationControlTotalOutputComponents = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxtessellationcontroltotaloutputcomponents();
  pProperties_ref_properties_limits.maxTessellationEvaluationInputComponents = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxtessellationevaluationinputcomponents();
  pProperties_ref_properties_limits.maxTessellationEvaluationOutputComponents = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxtessellationevaluationoutputcomponents();
  pProperties_ref_properties_limits.maxGeometryShaderInvocations = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxgeometryshaderinvocations();
  pProperties_ref_properties_limits.maxGeometryInputComponents = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxgeometryinputcomponents();
  pProperties_ref_properties_limits.maxGeometryOutputComponents = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxgeometryoutputcomponents();
  pProperties_ref_properties_limits.maxGeometryOutputVertices = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxgeometryoutputvertices();
  pProperties_ref_properties_limits.maxGeometryTotalOutputComponents = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxgeometrytotaloutputcomponents();
  pProperties_ref_properties_limits.maxFragmentInputComponents = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxfragmentinputcomponents();
  pProperties_ref_properties_limits.maxFragmentOutputAttachments = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxfragmentoutputattachments();
  pProperties_ref_properties_limits.maxFragmentDualSrcAttachments = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxfragmentdualsrcattachments();
  pProperties_ref_properties_limits.maxFragmentCombinedOutputResources = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxfragmentcombinedoutputresources();
  pProperties_ref_properties_limits.maxComputeSharedMemorySize = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxcomputesharedmemorysize();
  for (int maxComputeWorkGroupCount_indx = 0; maxComputeWorkGroupCount_indx < 3; maxComputeWorkGroupCount_indx++) {
    pProperties_ref_properties_limits.maxComputeWorkGroupCount[maxComputeWorkGroupCount_indx] = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxcomputeworkgroupcount(maxComputeWorkGroupCount_indx);
  }
  pProperties_ref_properties_limits.maxComputeWorkGroupInvocations = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxcomputeworkgroupinvocations();
  for (int maxComputeWorkGroupSize_indx = 0; maxComputeWorkGroupSize_indx < 3; maxComputeWorkGroupSize_indx++) {
    pProperties_ref_properties_limits.maxComputeWorkGroupSize[maxComputeWorkGroupSize_indx] = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxcomputeworkgroupsize(maxComputeWorkGroupSize_indx);
  }
  pProperties_ref_properties_limits.subPixelPrecisionBits = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().subpixelprecisionbits();
  pProperties_ref_properties_limits.subTexelPrecisionBits = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().subtexelprecisionbits();
  pProperties_ref_properties_limits.mipmapPrecisionBits = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().mipmapprecisionbits();
  pProperties_ref_properties_limits.maxDrawIndexedIndexValue = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxdrawindexedindexvalue();
  pProperties_ref_properties_limits.maxDrawIndirectCount = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxdrawindirectcount();
  pProperties_ref_properties_limits.maxSamplerLodBias = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxsamplerlodbias();
  pProperties_ref_properties_limits.maxSamplerAnisotropy = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxsampleranisotropy();
  pProperties_ref_properties_limits.maxViewports = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxviewports();
  for (int maxViewportDimensions_indx = 0; maxViewportDimensions_indx < 2; maxViewportDimensions_indx++) {
    pProperties_ref_properties_limits.maxViewportDimensions[maxViewportDimensions_indx] = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxviewportdimensions(maxViewportDimensions_indx);
  }
  for (int viewportBoundsRange_indx = 0; viewportBoundsRange_indx < 2; viewportBoundsRange_indx++) {
    pProperties_ref_properties_limits.viewportBoundsRange[viewportBoundsRange_indx] = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().viewportboundsrange(viewportBoundsRange_indx);
  }
  pProperties_ref_properties_limits.viewportSubPixelBits = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().viewportsubpixelbits();
  pProperties_ref_properties_limits.minMemoryMapAlignment = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().minmemorymapalignment();
  pProperties_ref_properties_limits.minTexelBufferOffsetAlignment = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().mintexelbufferoffsetalignment());
  pProperties_ref_properties_limits.minUniformBufferOffsetAlignment = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().minuniformbufferoffsetalignment());
  pProperties_ref_properties_limits.minStorageBufferOffsetAlignment = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().minstoragebufferoffsetalignment());
  pProperties_ref_properties_limits.minTexelOffset = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().mintexeloffset();
  pProperties_ref_properties_limits.maxTexelOffset = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxtexeloffset();
  pProperties_ref_properties_limits.minTexelGatherOffset = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().mintexelgatheroffset();
  pProperties_ref_properties_limits.maxTexelGatherOffset = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxtexelgatheroffset();
  pProperties_ref_properties_limits.minInterpolationOffset = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().mininterpolationoffset();
  pProperties_ref_properties_limits.maxInterpolationOffset = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxinterpolationoffset();
  pProperties_ref_properties_limits.subPixelInterpolationOffsetBits = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().subpixelinterpolationoffsetbits();
  pProperties_ref_properties_limits.maxFramebufferWidth = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxframebufferwidth();
  pProperties_ref_properties_limits.maxFramebufferHeight = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxframebufferheight();
  pProperties_ref_properties_limits.maxFramebufferLayers = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxframebufferlayers();
  if (response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().has_framebuffercolorsamplecounts()) {
    pProperties_ref_properties_limits.framebufferColorSampleCounts = static_cast<VkSampleCountFlags>(response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().framebuffercolorsamplecounts());
  } else {
    pProperties_ref_properties_limits.framebufferColorSampleCounts = VkSampleCountFlags{};
  }
  if (response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().has_framebufferdepthsamplecounts()) {
    pProperties_ref_properties_limits.framebufferDepthSampleCounts = static_cast<VkSampleCountFlags>(response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().framebufferdepthsamplecounts());
  } else {
    pProperties_ref_properties_limits.framebufferDepthSampleCounts = VkSampleCountFlags{};
  }
  if (response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().has_framebufferstencilsamplecounts()) {
    pProperties_ref_properties_limits.framebufferStencilSampleCounts = static_cast<VkSampleCountFlags>(response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().framebufferstencilsamplecounts());
  } else {
    pProperties_ref_properties_limits.framebufferStencilSampleCounts = VkSampleCountFlags{};
  }
  if (response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().has_framebuffernoattachmentssamplecounts()) {
    pProperties_ref_properties_limits.framebufferNoAttachmentsSampleCounts = static_cast<VkSampleCountFlags>(response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().framebuffernoattachmentssamplecounts());
  } else {
    pProperties_ref_properties_limits.framebufferNoAttachmentsSampleCounts = VkSampleCountFlags{};
  }
  pProperties_ref_properties_limits.maxColorAttachments = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxcolorattachments();
  if (response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().has_sampledimagecolorsamplecounts()) {
    pProperties_ref_properties_limits.sampledImageColorSampleCounts = static_cast<VkSampleCountFlags>(response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().sampledimagecolorsamplecounts());
  } else {
    pProperties_ref_properties_limits.sampledImageColorSampleCounts = VkSampleCountFlags{};
  }
  if (response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().has_sampledimageintegersamplecounts()) {
    pProperties_ref_properties_limits.sampledImageIntegerSampleCounts = static_cast<VkSampleCountFlags>(response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().sampledimageintegersamplecounts());
  } else {
    pProperties_ref_properties_limits.sampledImageIntegerSampleCounts = VkSampleCountFlags{};
  }
  if (response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().has_sampledimagedepthsamplecounts()) {
    pProperties_ref_properties_limits.sampledImageDepthSampleCounts = static_cast<VkSampleCountFlags>(response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().sampledimagedepthsamplecounts());
  } else {
    pProperties_ref_properties_limits.sampledImageDepthSampleCounts = VkSampleCountFlags{};
  }
  if (response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().has_sampledimagestencilsamplecounts()) {
    pProperties_ref_properties_limits.sampledImageStencilSampleCounts = static_cast<VkSampleCountFlags>(response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().sampledimagestencilsamplecounts());
  } else {
    pProperties_ref_properties_limits.sampledImageStencilSampleCounts = VkSampleCountFlags{};
  }
  if (response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().has_storageimagesamplecounts()) {
    pProperties_ref_properties_limits.storageImageSampleCounts = static_cast<VkSampleCountFlags>(response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().storageimagesamplecounts());
  } else {
    pProperties_ref_properties_limits.storageImageSampleCounts = VkSampleCountFlags{};
  }
  pProperties_ref_properties_limits.maxSampleMaskWords = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxsamplemaskwords();
  pProperties_ref_properties_limits.timestampComputeAndGraphics = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().timestampcomputeandgraphics();
  pProperties_ref_properties_limits.timestampPeriod = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().timestampperiod();
  pProperties_ref_properties_limits.maxClipDistances = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxclipdistances();
  pProperties_ref_properties_limits.maxCullDistances = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxculldistances();
  pProperties_ref_properties_limits.maxCombinedClipAndCullDistances = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().maxcombinedclipandculldistances();
  pProperties_ref_properties_limits.discreteQueuePriorities = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().discretequeuepriorities();
  for (int pointSizeRange_indx = 0; pointSizeRange_indx < 2; pointSizeRange_indx++) {
    pProperties_ref_properties_limits.pointSizeRange[pointSizeRange_indx] = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().pointsizerange(pointSizeRange_indx);
  }
  for (int lineWidthRange_indx = 0; lineWidthRange_indx < 2; lineWidthRange_indx++) {
    pProperties_ref_properties_limits.lineWidthRange[lineWidthRange_indx] = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().linewidthrange(lineWidthRange_indx);
  }
  pProperties_ref_properties_limits.pointSizeGranularity = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().pointsizegranularity();
  pProperties_ref_properties_limits.lineWidthGranularity = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().linewidthgranularity();
  pProperties_ref_properties_limits.strictLines = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().strictlines();
  pProperties_ref_properties_limits.standardSampleLocations = response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().standardsamplelocations();
  pProperties_ref_properties_limits.optimalBufferCopyOffsetAlignment = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().optimalbuffercopyoffsetalignment());
  pProperties_ref_properties_limits.optimalBufferCopyRowPitchAlignment = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().optimalbuffercopyrowpitchalignment());
  pProperties_ref_properties_limits.nonCoherentAtomSize = static_cast<VkDeviceSize>(response.vkgetphysicaldeviceproperties2().pproperties().properties().limits().noncoherentatomsize());
  VkPhysicalDeviceSparseProperties &pProperties_ref_properties_sparseProperties = pProperties_ref_properties.sparseProperties;
  pProperties_ref_properties_sparseProperties.residencyStandard2DBlockShape = response.vkgetphysicaldeviceproperties2().pproperties().properties().sparseproperties().residencystandard2dblockshape();
  pProperties_ref_properties_sparseProperties.residencyStandard2DMultisampleBlockShape = response.vkgetphysicaldeviceproperties2().pproperties().properties().sparseproperties().residencystandard2dmultisampleblockshape();
  pProperties_ref_properties_sparseProperties.residencyStandard3DBlockShape = response.vkgetphysicaldeviceproperties2().pproperties().properties().sparseproperties().residencystandard3dblockshape();
  pProperties_ref_properties_sparseProperties.residencyAlignedMipSize = response.vkgetphysicaldeviceproperties2().pproperties().properties().sparseproperties().residencyalignedmipsize();
  pProperties_ref_properties_sparseProperties.residencyNonResidentStrict = response.vkgetphysicaldeviceproperties2().pproperties().properties().sparseproperties().residencynonresidentstrict();
}
void PackAndCallVkGetPhysicalDeviceFeatures2(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2* pFeatures) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetPhysicalDeviceFeatures2");
  request.mutable_vkgetphysicaldevicefeatures2()->set_physicaldevice(reinterpret_cast<uint64_t>(physicalDevice));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  VkPhysicalDeviceFeatures2& pFeatures_ref = *pFeatures;
  pFeatures_ref.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
  pFeatures_ref.pNext = nullptr; // pNext chains are currently unsupported
  VkPhysicalDeviceFeatures &pFeatures_ref_features = pFeatures_ref.features;
  pFeatures_ref_features.robustBufferAccess = response.vkgetphysicaldevicefeatures2().pfeatures().features().robustbufferaccess();
  pFeatures_ref_features.fullDrawIndexUint32 = response.vkgetphysicaldevicefeatures2().pfeatures().features().fulldrawindexuint32();
  pFeatures_ref_features.imageCubeArray = response.vkgetphysicaldevicefeatures2().pfeatures().features().imagecubearray();
  pFeatures_ref_features.independentBlend = response.vkgetphysicaldevicefeatures2().pfeatures().features().independentblend();
  pFeatures_ref_features.geometryShader = response.vkgetphysicaldevicefeatures2().pfeatures().features().geometryshader();
  pFeatures_ref_features.tessellationShader = response.vkgetphysicaldevicefeatures2().pfeatures().features().tessellationshader();
  pFeatures_ref_features.sampleRateShading = response.vkgetphysicaldevicefeatures2().pfeatures().features().samplerateshading();
  pFeatures_ref_features.dualSrcBlend = response.vkgetphysicaldevicefeatures2().pfeatures().features().dualsrcblend();
  pFeatures_ref_features.logicOp = response.vkgetphysicaldevicefeatures2().pfeatures().features().logicop();
  pFeatures_ref_features.multiDrawIndirect = response.vkgetphysicaldevicefeatures2().pfeatures().features().multidrawindirect();
  pFeatures_ref_features.drawIndirectFirstInstance = response.vkgetphysicaldevicefeatures2().pfeatures().features().drawindirectfirstinstance();
  pFeatures_ref_features.depthClamp = response.vkgetphysicaldevicefeatures2().pfeatures().features().depthclamp();
  pFeatures_ref_features.depthBiasClamp = response.vkgetphysicaldevicefeatures2().pfeatures().features().depthbiasclamp();
  pFeatures_ref_features.fillModeNonSolid = response.vkgetphysicaldevicefeatures2().pfeatures().features().fillmodenonsolid();
  pFeatures_ref_features.depthBounds = response.vkgetphysicaldevicefeatures2().pfeatures().features().depthbounds();
  pFeatures_ref_features.wideLines = response.vkgetphysicaldevicefeatures2().pfeatures().features().widelines();
  pFeatures_ref_features.largePoints = response.vkgetphysicaldevicefeatures2().pfeatures().features().largepoints();
  pFeatures_ref_features.alphaToOne = response.vkgetphysicaldevicefeatures2().pfeatures().features().alphatoone();
  pFeatures_ref_features.multiViewport = response.vkgetphysicaldevicefeatures2().pfeatures().features().multiviewport();
  pFeatures_ref_features.samplerAnisotropy = response.vkgetphysicaldevicefeatures2().pfeatures().features().sampleranisotropy();
  pFeatures_ref_features.textureCompressionETC2 = response.vkgetphysicaldevicefeatures2().pfeatures().features().texturecompressionetc2();
  pFeatures_ref_features.textureCompressionASTC_LDR = response.vkgetphysicaldevicefeatures2().pfeatures().features().texturecompressionastc_ldr();
  pFeatures_ref_features.textureCompressionBC = response.vkgetphysicaldevicefeatures2().pfeatures().features().texturecompressionbc();
  pFeatures_ref_features.occlusionQueryPrecise = response.vkgetphysicaldevicefeatures2().pfeatures().features().occlusionqueryprecise();
  pFeatures_ref_features.pipelineStatisticsQuery = response.vkgetphysicaldevicefeatures2().pfeatures().features().pipelinestatisticsquery();
  pFeatures_ref_features.vertexPipelineStoresAndAtomics = response.vkgetphysicaldevicefeatures2().pfeatures().features().vertexpipelinestoresandatomics();
  pFeatures_ref_features.fragmentStoresAndAtomics = response.vkgetphysicaldevicefeatures2().pfeatures().features().fragmentstoresandatomics();
  pFeatures_ref_features.shaderTessellationAndGeometryPointSize = response.vkgetphysicaldevicefeatures2().pfeatures().features().shadertessellationandgeometrypointsize();
  pFeatures_ref_features.shaderImageGatherExtended = response.vkgetphysicaldevicefeatures2().pfeatures().features().shaderimagegatherextended();
  pFeatures_ref_features.shaderStorageImageExtendedFormats = response.vkgetphysicaldevicefeatures2().pfeatures().features().shaderstorageimageextendedformats();
  pFeatures_ref_features.shaderStorageImageMultisample = response.vkgetphysicaldevicefeatures2().pfeatures().features().shaderstorageimagemultisample();
  pFeatures_ref_features.shaderStorageImageReadWithoutFormat = response.vkgetphysicaldevicefeatures2().pfeatures().features().shaderstorageimagereadwithoutformat();
  pFeatures_ref_features.shaderStorageImageWriteWithoutFormat = response.vkgetphysicaldevicefeatures2().pfeatures().features().shaderstorageimagewritewithoutformat();
  pFeatures_ref_features.shaderUniformBufferArrayDynamicIndexing = response.vkgetphysicaldevicefeatures2().pfeatures().features().shaderuniformbufferarraydynamicindexing();
  pFeatures_ref_features.shaderSampledImageArrayDynamicIndexing = response.vkgetphysicaldevicefeatures2().pfeatures().features().shadersampledimagearraydynamicindexing();
  pFeatures_ref_features.shaderStorageBufferArrayDynamicIndexing = response.vkgetphysicaldevicefeatures2().pfeatures().features().shaderstoragebufferarraydynamicindexing();
  pFeatures_ref_features.shaderStorageImageArrayDynamicIndexing = response.vkgetphysicaldevicefeatures2().pfeatures().features().shaderstorageimagearraydynamicindexing();
  pFeatures_ref_features.shaderClipDistance = response.vkgetphysicaldevicefeatures2().pfeatures().features().shaderclipdistance();
  pFeatures_ref_features.shaderCullDistance = response.vkgetphysicaldevicefeatures2().pfeatures().features().shaderculldistance();
  pFeatures_ref_features.shaderFloat64 = response.vkgetphysicaldevicefeatures2().pfeatures().features().shaderfloat64();
  pFeatures_ref_features.shaderInt64 = response.vkgetphysicaldevicefeatures2().pfeatures().features().shaderint64();
  pFeatures_ref_features.shaderInt16 = response.vkgetphysicaldevicefeatures2().pfeatures().features().shaderint16();
  pFeatures_ref_features.shaderResourceResidency = response.vkgetphysicaldevicefeatures2().pfeatures().features().shaderresourceresidency();
  pFeatures_ref_features.shaderResourceMinLod = response.vkgetphysicaldevicefeatures2().pfeatures().features().shaderresourceminlod();
  pFeatures_ref_features.sparseBinding = response.vkgetphysicaldevicefeatures2().pfeatures().features().sparsebinding();
  pFeatures_ref_features.sparseResidencyBuffer = response.vkgetphysicaldevicefeatures2().pfeatures().features().sparseresidencybuffer();
  pFeatures_ref_features.sparseResidencyImage2D = response.vkgetphysicaldevicefeatures2().pfeatures().features().sparseresidencyimage2d();
  pFeatures_ref_features.sparseResidencyImage3D = response.vkgetphysicaldevicefeatures2().pfeatures().features().sparseresidencyimage3d();
  pFeatures_ref_features.sparseResidency2Samples = response.vkgetphysicaldevicefeatures2().pfeatures().features().sparseresidency2samples();
  pFeatures_ref_features.sparseResidency4Samples = response.vkgetphysicaldevicefeatures2().pfeatures().features().sparseresidency4samples();
  pFeatures_ref_features.sparseResidency8Samples = response.vkgetphysicaldevicefeatures2().pfeatures().features().sparseresidency8samples();
  pFeatures_ref_features.sparseResidency16Samples = response.vkgetphysicaldevicefeatures2().pfeatures().features().sparseresidency16samples();
  pFeatures_ref_features.sparseResidencyAliased = response.vkgetphysicaldevicefeatures2().pfeatures().features().sparseresidencyaliased();
  pFeatures_ref_features.variableMultisampleRate = response.vkgetphysicaldevicefeatures2().pfeatures().features().variablemultisamplerate();
  pFeatures_ref_features.inheritedQueries = response.vkgetphysicaldevicefeatures2().pfeatures().features().inheritedqueries();
}
}  // namespace vvk

