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
  *pInstance = reinterpret_cast<VkInstance>(response.vkcreateinstance().pinstance());
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
  pProperties_ref.limits.framebufferColorSampleCounts = response.vkgetphysicaldeviceproperties().pproperties().limits().framebuffercolorsamplecounts();
  pProperties_ref.limits.framebufferDepthSampleCounts = response.vkgetphysicaldeviceproperties().pproperties().limits().framebufferdepthsamplecounts();
  pProperties_ref.limits.framebufferStencilSampleCounts = response.vkgetphysicaldeviceproperties().pproperties().limits().framebufferstencilsamplecounts();
  pProperties_ref.limits.framebufferNoAttachmentsSampleCounts = response.vkgetphysicaldeviceproperties().pproperties().limits().framebuffernoattachmentssamplecounts();
  pProperties_ref.limits.maxColorAttachments = response.vkgetphysicaldeviceproperties().pproperties().limits().maxcolorattachments();
  pProperties_ref.limits.sampledImageColorSampleCounts = response.vkgetphysicaldeviceproperties().pproperties().limits().sampledimagecolorsamplecounts();
  pProperties_ref.limits.sampledImageIntegerSampleCounts = response.vkgetphysicaldeviceproperties().pproperties().limits().sampledimageintegersamplecounts();
  pProperties_ref.limits.sampledImageDepthSampleCounts = response.vkgetphysicaldeviceproperties().pproperties().limits().sampledimagedepthsamplecounts();
  pProperties_ref.limits.sampledImageStencilSampleCounts = response.vkgetphysicaldeviceproperties().pproperties().limits().sampledimagestencilsamplecounts();
  pProperties_ref.limits.storageImageSampleCounts = response.vkgetphysicaldeviceproperties().pproperties().limits().storageimagesamplecounts();
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
}  // namespace vvk

