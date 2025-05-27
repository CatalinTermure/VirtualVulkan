// GENERATED FILE - DO NOT EDIT
// clang-format off
#include "implementations.h"

#include <vulkan/vulkan.h>

#include <cassert>
#include <unordered_map>
#include <vector>
#include <cstdlib>

#include "server/execution_context.h"

namespace {
void FillProtoFromStruct(vvk::server::VkConformanceVersion* proto, const VkConformanceVersion* original_struct);
void FillProtoFromStruct(vvk::server::VkExtensionProperties* proto, const VkExtensionProperties* original_struct);
void FillProtoFromStruct(vvk::server::VkExtent3D* proto, const VkExtent3D* original_struct);
void FillProtoFromStruct(vvk::server::VkFormatProperties* proto, const VkFormatProperties* original_struct);
void FillProtoFromStruct(vvk::server::VkMemoryHeap* proto, const VkMemoryHeap* original_struct);
void FillProtoFromStruct(vvk::server::VkMemoryRequirements* proto, const VkMemoryRequirements* original_struct);
void FillProtoFromStruct(vvk::server::VkMemoryRequirements2* proto, const VkMemoryRequirements2* original_struct);
void FillProtoFromStruct(vvk::server::VkMemoryType* proto, const VkMemoryType* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceFeatures* proto, const VkPhysicalDeviceFeatures* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceFeatures2* proto, const VkPhysicalDeviceFeatures2* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceLimits* proto, const VkPhysicalDeviceLimits* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceMemoryProperties* proto, const VkPhysicalDeviceMemoryProperties* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceProperties* proto, const VkPhysicalDeviceProperties* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceProperties2* proto, const VkPhysicalDeviceProperties2* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceProtectedMemoryFeatures* proto, const VkPhysicalDeviceProtectedMemoryFeatures* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceProtectedMemoryProperties* proto, const VkPhysicalDeviceProtectedMemoryProperties* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceShaderDrawParametersFeatures* proto, const VkPhysicalDeviceShaderDrawParametersFeatures* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceSparseProperties* proto, const VkPhysicalDeviceSparseProperties* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceSubgroupProperties* proto, const VkPhysicalDeviceSubgroupProperties* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceTimelineSemaphoreFeatures* proto, const VkPhysicalDeviceTimelineSemaphoreFeatures* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceTimelineSemaphoreProperties* proto, const VkPhysicalDeviceTimelineSemaphoreProperties* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceVulkan11Features* proto, const VkPhysicalDeviceVulkan11Features* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceVulkan11Properties* proto, const VkPhysicalDeviceVulkan11Properties* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceVulkan12Features* proto, const VkPhysicalDeviceVulkan12Features* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceVulkan12Properties* proto, const VkPhysicalDeviceVulkan12Properties* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceVulkan13Features* proto, const VkPhysicalDeviceVulkan13Features* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceVulkan13Properties* proto, const VkPhysicalDeviceVulkan13Properties* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceVulkan14Features* proto, const VkPhysicalDeviceVulkan14Features* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceVulkan14Properties* proto, const VkPhysicalDeviceVulkan14Properties* original_struct);
void FillProtoFromStruct(vvk::server::VkQueueFamilyProperties* proto, const VkQueueFamilyProperties* original_struct);
void FillProtoFromStruct(vvk::server::VkSubresourceLayout* proto, const VkSubresourceLayout* original_struct);
void FillStructFromProto(VkApplicationInfo& original_struct, const vvk::server::VkApplicationInfo& proto);
void FillStructFromProto(VkAttachmentDescription& original_struct, const vvk::server::VkAttachmentDescription& proto);
void FillStructFromProto(VkAttachmentReference& original_struct, const vvk::server::VkAttachmentReference& proto);
void FillStructFromProto(VkBindImageMemoryInfo& original_struct, const vvk::server::VkBindImageMemoryInfo& proto);
void FillStructFromProto(VkBufferCreateInfo& original_struct, const vvk::server::VkBufferCreateInfo& proto);
void FillStructFromProto(VkBufferImageCopy& original_struct, const vvk::server::VkBufferImageCopy& proto);
void FillStructFromProto(VkBufferMemoryBarrier& original_struct, const vvk::server::VkBufferMemoryBarrier& proto);
void FillStructFromProto(VkClearColorValue& original_struct, const vvk::server::VkClearColorValue& proto);
void FillStructFromProto(VkClearDepthStencilValue& original_struct, const vvk::server::VkClearDepthStencilValue& proto);
void FillStructFromProto(VkClearValue& original_struct, const vvk::server::VkClearValue& proto);
void FillStructFromProto(VkCommandBufferAllocateInfo& original_struct, const vvk::server::VkCommandBufferAllocateInfo& proto);
void FillStructFromProto(VkCommandBufferBeginInfo& original_struct, const vvk::server::VkCommandBufferBeginInfo& proto);
void FillStructFromProto(VkCommandBufferInheritanceInfo& original_struct, const vvk::server::VkCommandBufferInheritanceInfo& proto);
void FillStructFromProto(VkCommandPoolCreateInfo& original_struct, const vvk::server::VkCommandPoolCreateInfo& proto);
void FillStructFromProto(VkComponentMapping& original_struct, const vvk::server::VkComponentMapping& proto);
void FillStructFromProto(VkConformanceVersion& original_struct, const vvk::server::VkConformanceVersion& proto);
void FillStructFromProto(VkCopyDescriptorSet& original_struct, const vvk::server::VkCopyDescriptorSet& proto);
void FillStructFromProto(VkDescriptorBufferInfo& original_struct, const vvk::server::VkDescriptorBufferInfo& proto);
void FillStructFromProto(VkDescriptorImageInfo& original_struct, const vvk::server::VkDescriptorImageInfo& proto);
void FillStructFromProto(VkDescriptorPoolCreateInfo& original_struct, const vvk::server::VkDescriptorPoolCreateInfo& proto);
void FillStructFromProto(VkDescriptorPoolSize& original_struct, const vvk::server::VkDescriptorPoolSize& proto);
void FillStructFromProto(VkDescriptorSetAllocateInfo& original_struct, const vvk::server::VkDescriptorSetAllocateInfo& proto);
void FillStructFromProto(VkDescriptorSetLayoutBinding& original_struct, const vvk::server::VkDescriptorSetLayoutBinding& proto);
void FillStructFromProto(VkDescriptorSetLayoutCreateInfo& original_struct, const vvk::server::VkDescriptorSetLayoutCreateInfo& proto);
void FillStructFromProto(VkDeviceCreateInfo& original_struct, const vvk::server::VkDeviceCreateInfo& proto);
void FillStructFromProto(VkDeviceQueueCreateInfo& original_struct, const vvk::server::VkDeviceQueueCreateInfo& proto);
void FillStructFromProto(VkExtent2D& original_struct, const vvk::server::VkExtent2D& proto);
void FillStructFromProto(VkExtent3D& original_struct, const vvk::server::VkExtent3D& proto);
void FillStructFromProto(VkFenceCreateInfo& original_struct, const vvk::server::VkFenceCreateInfo& proto);
void FillStructFromProto(VkFormatProperties& original_struct, const vvk::server::VkFormatProperties& proto);
void FillStructFromProto(VkFramebufferCreateInfo& original_struct, const vvk::server::VkFramebufferCreateInfo& proto);
void FillStructFromProto(VkGraphicsPipelineCreateInfo& original_struct, const vvk::server::VkGraphicsPipelineCreateInfo& proto);
void FillStructFromProto(VkImageCreateInfo& original_struct, const vvk::server::VkImageCreateInfo& proto);
void FillStructFromProto(VkImageMemoryBarrier& original_struct, const vvk::server::VkImageMemoryBarrier& proto);
void FillStructFromProto(VkImageMemoryRequirementsInfo2& original_struct, const vvk::server::VkImageMemoryRequirementsInfo2& proto);
void FillStructFromProto(VkImageSubresource& original_struct, const vvk::server::VkImageSubresource& proto);
void FillStructFromProto(VkImageSubresourceLayers& original_struct, const vvk::server::VkImageSubresourceLayers& proto);
void FillStructFromProto(VkImageSubresourceRange& original_struct, const vvk::server::VkImageSubresourceRange& proto);
void FillStructFromProto(VkImageViewCreateInfo& original_struct, const vvk::server::VkImageViewCreateInfo& proto);
void FillStructFromProto(VkInstanceCreateInfo& original_struct, const vvk::server::VkInstanceCreateInfo& proto);
void FillStructFromProto(VkMappedMemoryRange& original_struct, const vvk::server::VkMappedMemoryRange& proto);
void FillStructFromProto(VkMemoryAllocateInfo& original_struct, const vvk::server::VkMemoryAllocateInfo& proto);
void FillStructFromProto(VkMemoryBarrier& original_struct, const vvk::server::VkMemoryBarrier& proto);
void FillStructFromProto(VkMemoryHeap& original_struct, const vvk::server::VkMemoryHeap& proto);
void FillStructFromProto(VkMemoryRequirements& original_struct, const vvk::server::VkMemoryRequirements& proto);
void FillStructFromProto(VkMemoryRequirements2& original_struct, const vvk::server::VkMemoryRequirements2& proto);
void FillStructFromProto(VkMemoryType& original_struct, const vvk::server::VkMemoryType& proto);
void FillStructFromProto(VkOffset2D& original_struct, const vvk::server::VkOffset2D& proto);
void FillStructFromProto(VkOffset3D& original_struct, const vvk::server::VkOffset3D& proto);
void FillStructFromProto(VkPhysicalDeviceFeatures& original_struct, const vvk::server::VkPhysicalDeviceFeatures& proto);
void FillStructFromProto(VkPhysicalDeviceFeatures2& original_struct, const vvk::server::VkPhysicalDeviceFeatures2& proto);
void FillStructFromProto(VkPhysicalDeviceLimits& original_struct, const vvk::server::VkPhysicalDeviceLimits& proto);
void FillStructFromProto(VkPhysicalDeviceMemoryProperties& original_struct, const vvk::server::VkPhysicalDeviceMemoryProperties& proto);
void FillStructFromProto(VkPhysicalDeviceProperties& original_struct, const vvk::server::VkPhysicalDeviceProperties& proto);
void FillStructFromProto(VkPhysicalDeviceProperties2& original_struct, const vvk::server::VkPhysicalDeviceProperties2& proto);
void FillStructFromProto(VkPhysicalDeviceSparseProperties& original_struct, const vvk::server::VkPhysicalDeviceSparseProperties& proto);
void FillStructFromProto(VkPipelineCacheCreateInfo& original_struct, const vvk::server::VkPipelineCacheCreateInfo& proto);
void FillStructFromProto(VkPipelineColorBlendAttachmentState& original_struct, const vvk::server::VkPipelineColorBlendAttachmentState& proto);
void FillStructFromProto(VkPipelineColorBlendStateCreateInfo& original_struct, const vvk::server::VkPipelineColorBlendStateCreateInfo& proto);
void FillStructFromProto(VkPipelineDepthStencilStateCreateInfo& original_struct, const vvk::server::VkPipelineDepthStencilStateCreateInfo& proto);
void FillStructFromProto(VkPipelineDynamicStateCreateInfo& original_struct, const vvk::server::VkPipelineDynamicStateCreateInfo& proto);
void FillStructFromProto(VkPipelineInputAssemblyStateCreateInfo& original_struct, const vvk::server::VkPipelineInputAssemblyStateCreateInfo& proto);
void FillStructFromProto(VkPipelineLayoutCreateInfo& original_struct, const vvk::server::VkPipelineLayoutCreateInfo& proto);
void FillStructFromProto(VkPipelineMultisampleStateCreateInfo& original_struct, const vvk::server::VkPipelineMultisampleStateCreateInfo& proto);
void FillStructFromProto(VkPipelineRasterizationStateCreateInfo& original_struct, const vvk::server::VkPipelineRasterizationStateCreateInfo& proto);
void FillStructFromProto(VkPipelineShaderStageCreateInfo& original_struct, const vvk::server::VkPipelineShaderStageCreateInfo& proto);
void FillStructFromProto(VkPipelineTessellationStateCreateInfo& original_struct, const vvk::server::VkPipelineTessellationStateCreateInfo& proto);
void FillStructFromProto(VkPipelineVertexInputStateCreateInfo& original_struct, const vvk::server::VkPipelineVertexInputStateCreateInfo& proto);
void FillStructFromProto(VkPipelineViewportStateCreateInfo& original_struct, const vvk::server::VkPipelineViewportStateCreateInfo& proto);
void FillStructFromProto(VkPushConstantRange& original_struct, const vvk::server::VkPushConstantRange& proto);
void FillStructFromProto(VkRect2D& original_struct, const vvk::server::VkRect2D& proto);
void FillStructFromProto(VkRenderPassBeginInfo& original_struct, const vvk::server::VkRenderPassBeginInfo& proto);
void FillStructFromProto(VkRenderPassCreateInfo& original_struct, const vvk::server::VkRenderPassCreateInfo& proto);
void FillStructFromProto(VkSamplerCreateInfo& original_struct, const vvk::server::VkSamplerCreateInfo& proto);
void FillStructFromProto(VkSemaphoreCreateInfo& original_struct, const vvk::server::VkSemaphoreCreateInfo& proto);
void FillStructFromProto(VkSemaphoreSignalInfo& original_struct, const vvk::server::VkSemaphoreSignalInfo& proto);
void FillStructFromProto(VkShaderModuleCreateInfo& original_struct, const vvk::server::VkShaderModuleCreateInfo& proto);
void FillStructFromProto(VkSpecializationInfo& original_struct, const vvk::server::VkSpecializationInfo& proto);
void FillStructFromProto(VkSpecializationMapEntry& original_struct, const vvk::server::VkSpecializationMapEntry& proto);
void FillStructFromProto(VkStencilOpState& original_struct, const vvk::server::VkStencilOpState& proto);
void FillStructFromProto(VkSubmitInfo& original_struct, const vvk::server::VkSubmitInfo& proto);
void FillStructFromProto(VkSubpassDependency& original_struct, const vvk::server::VkSubpassDependency& proto);
void FillStructFromProto(VkSubpassDescription& original_struct, const vvk::server::VkSubpassDescription& proto);
void FillStructFromProto(VkSubresourceLayout& original_struct, const vvk::server::VkSubresourceLayout& proto);
void FillStructFromProto(VkVertexInputAttributeDescription& original_struct, const vvk::server::VkVertexInputAttributeDescription& proto);
void FillStructFromProto(VkVertexInputBindingDescription& original_struct, const vvk::server::VkVertexInputBindingDescription& proto);
void FillStructFromProto(VkViewport& original_struct, const vvk::server::VkViewport& proto);
void FillStructFromProto(VkWriteDescriptorSet& original_struct, const vvk::server::VkWriteDescriptorSet& proto);
void FillStructFromProtoNoPNext(VkPhysicalDeviceProtectedMemoryFeatures& original_struct, const vvk::server::VkPhysicalDeviceProtectedMemoryFeatures& proto);
void FillStructFromProtoNoPNext(VkPhysicalDeviceProtectedMemoryProperties& original_struct, const vvk::server::VkPhysicalDeviceProtectedMemoryProperties& proto);
void FillStructFromProtoNoPNext(VkPhysicalDeviceShaderDrawParametersFeatures& original_struct, const vvk::server::VkPhysicalDeviceShaderDrawParametersFeatures& proto);
void FillStructFromProtoNoPNext(VkPhysicalDeviceSubgroupProperties& original_struct, const vvk::server::VkPhysicalDeviceSubgroupProperties& proto);
void FillStructFromProtoNoPNext(VkPhysicalDeviceTimelineSemaphoreFeatures& original_struct, const vvk::server::VkPhysicalDeviceTimelineSemaphoreFeatures& proto);
void FillStructFromProtoNoPNext(VkPhysicalDeviceTimelineSemaphoreProperties& original_struct, const vvk::server::VkPhysicalDeviceTimelineSemaphoreProperties& proto);
void FillStructFromProtoNoPNext(VkPhysicalDeviceVulkan11Features& original_struct, const vvk::server::VkPhysicalDeviceVulkan11Features& proto);
void FillStructFromProtoNoPNext(VkPhysicalDeviceVulkan11Properties& original_struct, const vvk::server::VkPhysicalDeviceVulkan11Properties& proto);
void FillStructFromProtoNoPNext(VkPhysicalDeviceVulkan12Features& original_struct, const vvk::server::VkPhysicalDeviceVulkan12Features& proto);
void FillStructFromProtoNoPNext(VkPhysicalDeviceVulkan12Properties& original_struct, const vvk::server::VkPhysicalDeviceVulkan12Properties& proto);
void FillStructFromProtoNoPNext(VkPhysicalDeviceVulkan13Features& original_struct, const vvk::server::VkPhysicalDeviceVulkan13Features& proto);
void FillStructFromProtoNoPNext(VkPhysicalDeviceVulkan13Properties& original_struct, const vvk::server::VkPhysicalDeviceVulkan13Properties& proto);
void FillStructFromProtoNoPNext(VkPhysicalDeviceVulkan14Features& original_struct, const vvk::server::VkPhysicalDeviceVulkan14Features& proto);
void FillStructFromProtoNoPNext(VkPhysicalDeviceVulkan14Properties& original_struct, const vvk::server::VkPhysicalDeviceVulkan14Properties& proto);
void FillStructFromProtoNoPNext(VkProtectedSubmitInfo& original_struct, const vvk::server::VkProtectedSubmitInfo& proto);
void FillStructFromProtoNoPNext(VkSemaphoreTypeCreateInfo& original_struct, const vvk::server::VkSemaphoreTypeCreateInfo& proto);
void FillStructFromProtoNoPNext(VkShaderModuleCreateInfo& original_struct, const vvk::server::VkShaderModuleCreateInfo& proto);
void FillStructFromProtoNoPNext(VkTimelineSemaphoreSubmitInfo& original_struct, const vvk::server::VkTimelineSemaphoreSubmitInfo& proto);
void FillProtoFromStruct(vvk::server::VkConformanceVersion* proto, const VkConformanceVersion* original_struct) {
  proto->set_major(static_cast<uint32_t>(original_struct->major));
  proto->set_minor(static_cast<uint32_t>(original_struct->minor));
  proto->set_subminor(static_cast<uint32_t>(original_struct->subminor));
  proto->set_patch(static_cast<uint32_t>(original_struct->patch));
}
void FillProtoFromStruct(vvk::server::VkExtensionProperties* proto, const VkExtensionProperties* original_struct) {
  proto->set_extensionname(original_struct->extensionName);
  proto->set_specversion(original_struct->specVersion);
}
void FillProtoFromStruct(vvk::server::VkExtent3D* proto, const VkExtent3D* original_struct) {
  proto->set_width(original_struct->width);
  proto->set_height(original_struct->height);
  proto->set_depth(original_struct->depth);
}
void FillProtoFromStruct(vvk::server::VkFormatProperties* proto, const VkFormatProperties* original_struct) {
  if (original_struct->linearTilingFeatures) {
    proto->set_lineartilingfeatures(original_struct->linearTilingFeatures);
  }
  if (original_struct->optimalTilingFeatures) {
    proto->set_optimaltilingfeatures(original_struct->optimalTilingFeatures);
  }
  if (original_struct->bufferFeatures) {
    proto->set_bufferfeatures(original_struct->bufferFeatures);
  }
}
void FillProtoFromStruct(vvk::server::VkMemoryHeap* proto, const VkMemoryHeap* original_struct) {
  proto->set_size(static_cast<uint64_t>(original_struct->size));
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
}
void FillProtoFromStruct(vvk::server::VkMemoryRequirements* proto, const VkMemoryRequirements* original_struct) {
  proto->set_size(static_cast<uint64_t>(original_struct->size));
  proto->set_alignment(static_cast<uint64_t>(original_struct->alignment));
  proto->set_memorytypebits(original_struct->memoryTypeBits);
}
void FillProtoFromStruct(vvk::server::VkMemoryRequirements2* proto, const VkMemoryRequirements2* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  FillProtoFromStruct(proto->mutable_memoryrequirements(), &original_struct->memoryRequirements);
}
void FillProtoFromStruct(vvk::server::VkMemoryType* proto, const VkMemoryType* original_struct) {
  if (original_struct->propertyFlags) {
    proto->set_propertyflags(original_struct->propertyFlags);
  }
  proto->set_heapindex(original_struct->heapIndex);
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceFeatures* proto, const VkPhysicalDeviceFeatures* original_struct) {
  proto->set_robustbufferaccess(original_struct->robustBufferAccess);
  proto->set_fulldrawindexuint32(original_struct->fullDrawIndexUint32);
  proto->set_imagecubearray(original_struct->imageCubeArray);
  proto->set_independentblend(original_struct->independentBlend);
  proto->set_geometryshader(original_struct->geometryShader);
  proto->set_tessellationshader(original_struct->tessellationShader);
  proto->set_samplerateshading(original_struct->sampleRateShading);
  proto->set_dualsrcblend(original_struct->dualSrcBlend);
  proto->set_logicop(original_struct->logicOp);
  proto->set_multidrawindirect(original_struct->multiDrawIndirect);
  proto->set_drawindirectfirstinstance(original_struct->drawIndirectFirstInstance);
  proto->set_depthclamp(original_struct->depthClamp);
  proto->set_depthbiasclamp(original_struct->depthBiasClamp);
  proto->set_fillmodenonsolid(original_struct->fillModeNonSolid);
  proto->set_depthbounds(original_struct->depthBounds);
  proto->set_widelines(original_struct->wideLines);
  proto->set_largepoints(original_struct->largePoints);
  proto->set_alphatoone(original_struct->alphaToOne);
  proto->set_multiviewport(original_struct->multiViewport);
  proto->set_sampleranisotropy(original_struct->samplerAnisotropy);
  proto->set_texturecompressionetc2(original_struct->textureCompressionETC2);
  proto->set_texturecompressionastc_ldr(original_struct->textureCompressionASTC_LDR);
  proto->set_texturecompressionbc(original_struct->textureCompressionBC);
  proto->set_occlusionqueryprecise(original_struct->occlusionQueryPrecise);
  proto->set_pipelinestatisticsquery(original_struct->pipelineStatisticsQuery);
  proto->set_vertexpipelinestoresandatomics(original_struct->vertexPipelineStoresAndAtomics);
  proto->set_fragmentstoresandatomics(original_struct->fragmentStoresAndAtomics);
  proto->set_shadertessellationandgeometrypointsize(original_struct->shaderTessellationAndGeometryPointSize);
  proto->set_shaderimagegatherextended(original_struct->shaderImageGatherExtended);
  proto->set_shaderstorageimageextendedformats(original_struct->shaderStorageImageExtendedFormats);
  proto->set_shaderstorageimagemultisample(original_struct->shaderStorageImageMultisample);
  proto->set_shaderstorageimagereadwithoutformat(original_struct->shaderStorageImageReadWithoutFormat);
  proto->set_shaderstorageimagewritewithoutformat(original_struct->shaderStorageImageWriteWithoutFormat);
  proto->set_shaderuniformbufferarraydynamicindexing(original_struct->shaderUniformBufferArrayDynamicIndexing);
  proto->set_shadersampledimagearraydynamicindexing(original_struct->shaderSampledImageArrayDynamicIndexing);
  proto->set_shaderstoragebufferarraydynamicindexing(original_struct->shaderStorageBufferArrayDynamicIndexing);
  proto->set_shaderstorageimagearraydynamicindexing(original_struct->shaderStorageImageArrayDynamicIndexing);
  proto->set_shaderclipdistance(original_struct->shaderClipDistance);
  proto->set_shaderculldistance(original_struct->shaderCullDistance);
  proto->set_shaderfloat64(original_struct->shaderFloat64);
  proto->set_shaderint64(original_struct->shaderInt64);
  proto->set_shaderint16(original_struct->shaderInt16);
  proto->set_shaderresourceresidency(original_struct->shaderResourceResidency);
  proto->set_shaderresourceminlod(original_struct->shaderResourceMinLod);
  proto->set_sparsebinding(original_struct->sparseBinding);
  proto->set_sparseresidencybuffer(original_struct->sparseResidencyBuffer);
  proto->set_sparseresidencyimage2d(original_struct->sparseResidencyImage2D);
  proto->set_sparseresidencyimage3d(original_struct->sparseResidencyImage3D);
  proto->set_sparseresidency2samples(original_struct->sparseResidency2Samples);
  proto->set_sparseresidency4samples(original_struct->sparseResidency4Samples);
  proto->set_sparseresidency8samples(original_struct->sparseResidency8Samples);
  proto->set_sparseresidency16samples(original_struct->sparseResidency16Samples);
  proto->set_sparseresidencyaliased(original_struct->sparseResidencyAliased);
  proto->set_variablemultisamplerate(original_struct->variableMultisampleRate);
  proto->set_inheritedqueries(original_struct->inheritedQueries);
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceFeatures2* proto, const VkPhysicalDeviceFeatures2* original_struct) {
  if (original_struct->pNext) {
    const void* pNext = original_struct->pNext;
    while (pNext) {
      const VkBaseInStructure* base = reinterpret_cast<const VkBaseInStructure*>(pNext);
      if (base->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_FEATURES) {
        FillProtoFromStruct(proto->add_pnext()->mutable_vkphysicaldeviceprotectedmemoryfeatures_chain_elem(), reinterpret_cast<const VkPhysicalDeviceProtectedMemoryFeatures*>(pNext));
      }
      if (base->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETERS_FEATURES) {
        FillProtoFromStruct(proto->add_pnext()->mutable_vkphysicaldeviceshaderdrawparametersfeatures_chain_elem(), reinterpret_cast<const VkPhysicalDeviceShaderDrawParametersFeatures*>(pNext));
      }
      if (base->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES) {
        FillProtoFromStruct(proto->add_pnext()->mutable_vkphysicaldevicetimelinesemaphorefeatures_chain_elem(), reinterpret_cast<const VkPhysicalDeviceTimelineSemaphoreFeatures*>(pNext));
      }
      if (base->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES) {
        FillProtoFromStruct(proto->add_pnext()->mutable_vkphysicaldevicevulkan11features_chain_elem(), reinterpret_cast<const VkPhysicalDeviceVulkan11Features*>(pNext));
      }
      if (base->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES) {
        FillProtoFromStruct(proto->add_pnext()->mutable_vkphysicaldevicevulkan12features_chain_elem(), reinterpret_cast<const VkPhysicalDeviceVulkan12Features*>(pNext));
      }
      if (base->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES) {
        FillProtoFromStruct(proto->add_pnext()->mutable_vkphysicaldevicevulkan13features_chain_elem(), reinterpret_cast<const VkPhysicalDeviceVulkan13Features*>(pNext));
      }
      if (base->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES) {
        FillProtoFromStruct(proto->add_pnext()->mutable_vkphysicaldevicevulkan14features_chain_elem(), reinterpret_cast<const VkPhysicalDeviceVulkan14Features*>(pNext));
      }
      pNext = reinterpret_cast<const void*>(base->pNext);
    }
  }
  FillProtoFromStruct(proto->mutable_features(), &original_struct->features);
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceLimits* proto, const VkPhysicalDeviceLimits* original_struct) {
  proto->set_maximagedimension1d(original_struct->maxImageDimension1D);
  proto->set_maximagedimension2d(original_struct->maxImageDimension2D);
  proto->set_maximagedimension3d(original_struct->maxImageDimension3D);
  proto->set_maximagedimensioncube(original_struct->maxImageDimensionCube);
  proto->set_maximagearraylayers(original_struct->maxImageArrayLayers);
  proto->set_maxtexelbufferelements(original_struct->maxTexelBufferElements);
  proto->set_maxuniformbufferrange(original_struct->maxUniformBufferRange);
  proto->set_maxstoragebufferrange(original_struct->maxStorageBufferRange);
  proto->set_maxpushconstantssize(original_struct->maxPushConstantsSize);
  proto->set_maxmemoryallocationcount(original_struct->maxMemoryAllocationCount);
  proto->set_maxsamplerallocationcount(original_struct->maxSamplerAllocationCount);
  proto->set_bufferimagegranularity(static_cast<uint64_t>(original_struct->bufferImageGranularity));
  proto->set_sparseaddressspacesize(static_cast<uint64_t>(original_struct->sparseAddressSpaceSize));
  proto->set_maxbounddescriptorsets(original_struct->maxBoundDescriptorSets);
  proto->set_maxperstagedescriptorsamplers(original_struct->maxPerStageDescriptorSamplers);
  proto->set_maxperstagedescriptoruniformbuffers(original_struct->maxPerStageDescriptorUniformBuffers);
  proto->set_maxperstagedescriptorstoragebuffers(original_struct->maxPerStageDescriptorStorageBuffers);
  proto->set_maxperstagedescriptorsampledimages(original_struct->maxPerStageDescriptorSampledImages);
  proto->set_maxperstagedescriptorstorageimages(original_struct->maxPerStageDescriptorStorageImages);
  proto->set_maxperstagedescriptorinputattachments(original_struct->maxPerStageDescriptorInputAttachments);
  proto->set_maxperstageresources(original_struct->maxPerStageResources);
  proto->set_maxdescriptorsetsamplers(original_struct->maxDescriptorSetSamplers);
  proto->set_maxdescriptorsetuniformbuffers(original_struct->maxDescriptorSetUniformBuffers);
  proto->set_maxdescriptorsetuniformbuffersdynamic(original_struct->maxDescriptorSetUniformBuffersDynamic);
  proto->set_maxdescriptorsetstoragebuffers(original_struct->maxDescriptorSetStorageBuffers);
  proto->set_maxdescriptorsetstoragebuffersdynamic(original_struct->maxDescriptorSetStorageBuffersDynamic);
  proto->set_maxdescriptorsetsampledimages(original_struct->maxDescriptorSetSampledImages);
  proto->set_maxdescriptorsetstorageimages(original_struct->maxDescriptorSetStorageImages);
  proto->set_maxdescriptorsetinputattachments(original_struct->maxDescriptorSetInputAttachments);
  proto->set_maxvertexinputattributes(original_struct->maxVertexInputAttributes);
  proto->set_maxvertexinputbindings(original_struct->maxVertexInputBindings);
  proto->set_maxvertexinputattributeoffset(original_struct->maxVertexInputAttributeOffset);
  proto->set_maxvertexinputbindingstride(original_struct->maxVertexInputBindingStride);
  proto->set_maxvertexoutputcomponents(original_struct->maxVertexOutputComponents);
  proto->set_maxtessellationgenerationlevel(original_struct->maxTessellationGenerationLevel);
  proto->set_maxtessellationpatchsize(original_struct->maxTessellationPatchSize);
  proto->set_maxtessellationcontrolpervertexinputcomponents(original_struct->maxTessellationControlPerVertexInputComponents);
  proto->set_maxtessellationcontrolpervertexoutputcomponents(original_struct->maxTessellationControlPerVertexOutputComponents);
  proto->set_maxtessellationcontrolperpatchoutputcomponents(original_struct->maxTessellationControlPerPatchOutputComponents);
  proto->set_maxtessellationcontroltotaloutputcomponents(original_struct->maxTessellationControlTotalOutputComponents);
  proto->set_maxtessellationevaluationinputcomponents(original_struct->maxTessellationEvaluationInputComponents);
  proto->set_maxtessellationevaluationoutputcomponents(original_struct->maxTessellationEvaluationOutputComponents);
  proto->set_maxgeometryshaderinvocations(original_struct->maxGeometryShaderInvocations);
  proto->set_maxgeometryinputcomponents(original_struct->maxGeometryInputComponents);
  proto->set_maxgeometryoutputcomponents(original_struct->maxGeometryOutputComponents);
  proto->set_maxgeometryoutputvertices(original_struct->maxGeometryOutputVertices);
  proto->set_maxgeometrytotaloutputcomponents(original_struct->maxGeometryTotalOutputComponents);
  proto->set_maxfragmentinputcomponents(original_struct->maxFragmentInputComponents);
  proto->set_maxfragmentoutputattachments(original_struct->maxFragmentOutputAttachments);
  proto->set_maxfragmentdualsrcattachments(original_struct->maxFragmentDualSrcAttachments);
  proto->set_maxfragmentcombinedoutputresources(original_struct->maxFragmentCombinedOutputResources);
  proto->set_maxcomputesharedmemorysize(original_struct->maxComputeSharedMemorySize);
  const size_t proto_maxComputeWorkGroupCount_length = std::min(3, 3);
  for (uint32_t maxComputeWorkGroupCount_indx = 0; maxComputeWorkGroupCount_indx < proto_maxComputeWorkGroupCount_length; maxComputeWorkGroupCount_indx++) {
    proto->add_maxcomputeworkgroupcount(original_struct->maxComputeWorkGroupCount[maxComputeWorkGroupCount_indx]);
  }
  proto->set_maxcomputeworkgroupinvocations(original_struct->maxComputeWorkGroupInvocations);
  const size_t proto_maxComputeWorkGroupSize_length = std::min(3, 3);
  for (uint32_t maxComputeWorkGroupSize_indx = 0; maxComputeWorkGroupSize_indx < proto_maxComputeWorkGroupSize_length; maxComputeWorkGroupSize_indx++) {
    proto->add_maxcomputeworkgroupsize(original_struct->maxComputeWorkGroupSize[maxComputeWorkGroupSize_indx]);
  }
  proto->set_subpixelprecisionbits(original_struct->subPixelPrecisionBits);
  proto->set_subtexelprecisionbits(original_struct->subTexelPrecisionBits);
  proto->set_mipmapprecisionbits(original_struct->mipmapPrecisionBits);
  proto->set_maxdrawindexedindexvalue(original_struct->maxDrawIndexedIndexValue);
  proto->set_maxdrawindirectcount(original_struct->maxDrawIndirectCount);
  proto->set_maxsamplerlodbias(original_struct->maxSamplerLodBias);
  proto->set_maxsampleranisotropy(original_struct->maxSamplerAnisotropy);
  proto->set_maxviewports(original_struct->maxViewports);
  const size_t proto_maxViewportDimensions_length = std::min(2, 2);
  for (uint32_t maxViewportDimensions_indx = 0; maxViewportDimensions_indx < proto_maxViewportDimensions_length; maxViewportDimensions_indx++) {
    proto->add_maxviewportdimensions(original_struct->maxViewportDimensions[maxViewportDimensions_indx]);
  }
  const size_t proto_viewportBoundsRange_length = std::min(2, 2);
  for (uint32_t viewportBoundsRange_indx = 0; viewportBoundsRange_indx < proto_viewportBoundsRange_length; viewportBoundsRange_indx++) {
    proto->add_viewportboundsrange(original_struct->viewportBoundsRange[viewportBoundsRange_indx]);
  }
  proto->set_viewportsubpixelbits(original_struct->viewportSubPixelBits);
  proto->set_minmemorymapalignment(original_struct->minMemoryMapAlignment);
  proto->set_mintexelbufferoffsetalignment(static_cast<uint64_t>(original_struct->minTexelBufferOffsetAlignment));
  proto->set_minuniformbufferoffsetalignment(static_cast<uint64_t>(original_struct->minUniformBufferOffsetAlignment));
  proto->set_minstoragebufferoffsetalignment(static_cast<uint64_t>(original_struct->minStorageBufferOffsetAlignment));
  proto->set_mintexeloffset(original_struct->minTexelOffset);
  proto->set_maxtexeloffset(original_struct->maxTexelOffset);
  proto->set_mintexelgatheroffset(original_struct->minTexelGatherOffset);
  proto->set_maxtexelgatheroffset(original_struct->maxTexelGatherOffset);
  proto->set_mininterpolationoffset(original_struct->minInterpolationOffset);
  proto->set_maxinterpolationoffset(original_struct->maxInterpolationOffset);
  proto->set_subpixelinterpolationoffsetbits(original_struct->subPixelInterpolationOffsetBits);
  proto->set_maxframebufferwidth(original_struct->maxFramebufferWidth);
  proto->set_maxframebufferheight(original_struct->maxFramebufferHeight);
  proto->set_maxframebufferlayers(original_struct->maxFramebufferLayers);
  if (original_struct->framebufferColorSampleCounts) {
    proto->set_framebuffercolorsamplecounts(original_struct->framebufferColorSampleCounts);
  }
  if (original_struct->framebufferDepthSampleCounts) {
    proto->set_framebufferdepthsamplecounts(original_struct->framebufferDepthSampleCounts);
  }
  if (original_struct->framebufferStencilSampleCounts) {
    proto->set_framebufferstencilsamplecounts(original_struct->framebufferStencilSampleCounts);
  }
  if (original_struct->framebufferNoAttachmentsSampleCounts) {
    proto->set_framebuffernoattachmentssamplecounts(original_struct->framebufferNoAttachmentsSampleCounts);
  }
  proto->set_maxcolorattachments(original_struct->maxColorAttachments);
  if (original_struct->sampledImageColorSampleCounts) {
    proto->set_sampledimagecolorsamplecounts(original_struct->sampledImageColorSampleCounts);
  }
  if (original_struct->sampledImageIntegerSampleCounts) {
    proto->set_sampledimageintegersamplecounts(original_struct->sampledImageIntegerSampleCounts);
  }
  if (original_struct->sampledImageDepthSampleCounts) {
    proto->set_sampledimagedepthsamplecounts(original_struct->sampledImageDepthSampleCounts);
  }
  if (original_struct->sampledImageStencilSampleCounts) {
    proto->set_sampledimagestencilsamplecounts(original_struct->sampledImageStencilSampleCounts);
  }
  if (original_struct->storageImageSampleCounts) {
    proto->set_storageimagesamplecounts(original_struct->storageImageSampleCounts);
  }
  proto->set_maxsamplemaskwords(original_struct->maxSampleMaskWords);
  proto->set_timestampcomputeandgraphics(original_struct->timestampComputeAndGraphics);
  proto->set_timestampperiod(original_struct->timestampPeriod);
  proto->set_maxclipdistances(original_struct->maxClipDistances);
  proto->set_maxculldistances(original_struct->maxCullDistances);
  proto->set_maxcombinedclipandculldistances(original_struct->maxCombinedClipAndCullDistances);
  proto->set_discretequeuepriorities(original_struct->discreteQueuePriorities);
  const size_t proto_pointSizeRange_length = std::min(2, 2);
  for (uint32_t pointSizeRange_indx = 0; pointSizeRange_indx < proto_pointSizeRange_length; pointSizeRange_indx++) {
    proto->add_pointsizerange(original_struct->pointSizeRange[pointSizeRange_indx]);
  }
  const size_t proto_lineWidthRange_length = std::min(2, 2);
  for (uint32_t lineWidthRange_indx = 0; lineWidthRange_indx < proto_lineWidthRange_length; lineWidthRange_indx++) {
    proto->add_linewidthrange(original_struct->lineWidthRange[lineWidthRange_indx]);
  }
  proto->set_pointsizegranularity(original_struct->pointSizeGranularity);
  proto->set_linewidthgranularity(original_struct->lineWidthGranularity);
  proto->set_strictlines(original_struct->strictLines);
  proto->set_standardsamplelocations(original_struct->standardSampleLocations);
  proto->set_optimalbuffercopyoffsetalignment(static_cast<uint64_t>(original_struct->optimalBufferCopyOffsetAlignment));
  proto->set_optimalbuffercopyrowpitchalignment(static_cast<uint64_t>(original_struct->optimalBufferCopyRowPitchAlignment));
  proto->set_noncoherentatomsize(static_cast<uint64_t>(original_struct->nonCoherentAtomSize));
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceMemoryProperties* proto, const VkPhysicalDeviceMemoryProperties* original_struct) {
  proto->set_memorytypecount(original_struct->memoryTypeCount);
  const size_t proto_memoryTypes_length = std::min(original_struct->memoryTypeCount, VK_MAX_MEMORY_TYPES);
  for (uint32_t memoryTypes_indx = 0; memoryTypes_indx < proto_memoryTypes_length; memoryTypes_indx++) {
    FillProtoFromStruct(proto->add_memorytypes(), &original_struct->memoryTypes[memoryTypes_indx]);
  }
  proto->set_memoryheapcount(original_struct->memoryHeapCount);
  const size_t proto_memoryHeaps_length = std::min(original_struct->memoryHeapCount, VK_MAX_MEMORY_HEAPS);
  for (uint32_t memoryHeaps_indx = 0; memoryHeaps_indx < proto_memoryHeaps_length; memoryHeaps_indx++) {
    FillProtoFromStruct(proto->add_memoryheaps(), &original_struct->memoryHeaps[memoryHeaps_indx]);
  }
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceProperties* proto, const VkPhysicalDeviceProperties* original_struct) {
  proto->set_apiversion(original_struct->apiVersion);
  proto->set_driverversion(original_struct->driverVersion);
  proto->set_vendorid(original_struct->vendorID);
  proto->set_deviceid(original_struct->deviceID);
  proto->set_devicetype(static_cast<vvk::server::VkPhysicalDeviceType>(original_struct->deviceType));
  proto->set_devicename(original_struct->deviceName);
  const size_t proto_pipelineCacheUUID_length = std::min(VK_UUID_SIZE, VK_UUID_SIZE);
  for (uint32_t pipelineCacheUUID_indx = 0; pipelineCacheUUID_indx < proto_pipelineCacheUUID_length; pipelineCacheUUID_indx++) {
    proto->add_pipelinecacheuuid(static_cast<uint32_t>(original_struct->pipelineCacheUUID[pipelineCacheUUID_indx]));
  }
  FillProtoFromStruct(proto->mutable_limits(), &original_struct->limits);
  FillProtoFromStruct(proto->mutable_sparseproperties(), &original_struct->sparseProperties);
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceProperties2* proto, const VkPhysicalDeviceProperties2* original_struct) {
  if (original_struct->pNext) {
    const void* pNext = original_struct->pNext;
    while (pNext) {
      const VkBaseInStructure* base = reinterpret_cast<const VkBaseInStructure*>(pNext);
      if (base->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_PROPERTIES) {
        FillProtoFromStruct(proto->add_pnext()->mutable_vkphysicaldeviceprotectedmemoryproperties_chain_elem(), reinterpret_cast<const VkPhysicalDeviceProtectedMemoryProperties*>(pNext));
      }
      if (base->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES) {
        FillProtoFromStruct(proto->add_pnext()->mutable_vkphysicaldevicesubgroupproperties_chain_elem(), reinterpret_cast<const VkPhysicalDeviceSubgroupProperties*>(pNext));
      }
      if (base->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_PROPERTIES) {
        FillProtoFromStruct(proto->add_pnext()->mutable_vkphysicaldevicetimelinesemaphoreproperties_chain_elem(), reinterpret_cast<const VkPhysicalDeviceTimelineSemaphoreProperties*>(pNext));
      }
      if (base->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES) {
        FillProtoFromStruct(proto->add_pnext()->mutable_vkphysicaldevicevulkan11properties_chain_elem(), reinterpret_cast<const VkPhysicalDeviceVulkan11Properties*>(pNext));
      }
      if (base->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES) {
        FillProtoFromStruct(proto->add_pnext()->mutable_vkphysicaldevicevulkan12properties_chain_elem(), reinterpret_cast<const VkPhysicalDeviceVulkan12Properties*>(pNext));
      }
      if (base->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_PROPERTIES) {
        FillProtoFromStruct(proto->add_pnext()->mutable_vkphysicaldevicevulkan13properties_chain_elem(), reinterpret_cast<const VkPhysicalDeviceVulkan13Properties*>(pNext));
      }
      if (base->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_PROPERTIES) {
        FillProtoFromStruct(proto->add_pnext()->mutable_vkphysicaldevicevulkan14properties_chain_elem(), reinterpret_cast<const VkPhysicalDeviceVulkan14Properties*>(pNext));
      }
      pNext = reinterpret_cast<const void*>(base->pNext);
    }
  }
  FillProtoFromStruct(proto->mutable_properties(), &original_struct->properties);
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceProtectedMemoryFeatures* proto, const VkPhysicalDeviceProtectedMemoryFeatures* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_protectedmemory(original_struct->protectedMemory);
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceProtectedMemoryProperties* proto, const VkPhysicalDeviceProtectedMemoryProperties* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_protectednofault(original_struct->protectedNoFault);
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceShaderDrawParametersFeatures* proto, const VkPhysicalDeviceShaderDrawParametersFeatures* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_shaderdrawparameters(original_struct->shaderDrawParameters);
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceSparseProperties* proto, const VkPhysicalDeviceSparseProperties* original_struct) {
  proto->set_residencystandard2dblockshape(original_struct->residencyStandard2DBlockShape);
  proto->set_residencystandard2dmultisampleblockshape(original_struct->residencyStandard2DMultisampleBlockShape);
  proto->set_residencystandard3dblockshape(original_struct->residencyStandard3DBlockShape);
  proto->set_residencyalignedmipsize(original_struct->residencyAlignedMipSize);
  proto->set_residencynonresidentstrict(original_struct->residencyNonResidentStrict);
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceSubgroupProperties* proto, const VkPhysicalDeviceSubgroupProperties* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_subgroupsize(original_struct->subgroupSize);
  proto->set_supportedstages(original_struct->supportedStages);
  proto->set_supportedoperations(original_struct->supportedOperations);
  proto->set_quadoperationsinallstages(original_struct->quadOperationsInAllStages);
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceTimelineSemaphoreFeatures* proto, const VkPhysicalDeviceTimelineSemaphoreFeatures* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_timelinesemaphore(original_struct->timelineSemaphore);
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceTimelineSemaphoreProperties* proto, const VkPhysicalDeviceTimelineSemaphoreProperties* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_maxtimelinesemaphorevaluedifference(original_struct->maxTimelineSemaphoreValueDifference);
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceVulkan11Features* proto, const VkPhysicalDeviceVulkan11Features* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_storagebuffer16bitaccess(original_struct->storageBuffer16BitAccess);
  proto->set_uniformandstoragebuffer16bitaccess(original_struct->uniformAndStorageBuffer16BitAccess);
  proto->set_storagepushconstant16(original_struct->storagePushConstant16);
  proto->set_storageinputoutput16(original_struct->storageInputOutput16);
  proto->set_multiview(original_struct->multiview);
  proto->set_multiviewgeometryshader(original_struct->multiviewGeometryShader);
  proto->set_multiviewtessellationshader(original_struct->multiviewTessellationShader);
  proto->set_variablepointersstoragebuffer(original_struct->variablePointersStorageBuffer);
  proto->set_variablepointers(original_struct->variablePointers);
  proto->set_protectedmemory(original_struct->protectedMemory);
  proto->set_samplerycbcrconversion(original_struct->samplerYcbcrConversion);
  proto->set_shaderdrawparameters(original_struct->shaderDrawParameters);
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceVulkan11Properties* proto, const VkPhysicalDeviceVulkan11Properties* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  const size_t proto_deviceUUID_length = std::min(VK_UUID_SIZE, VK_UUID_SIZE);
  for (uint32_t deviceUUID_indx = 0; deviceUUID_indx < proto_deviceUUID_length; deviceUUID_indx++) {
    proto->add_deviceuuid(static_cast<uint32_t>(original_struct->deviceUUID[deviceUUID_indx]));
  }
  const size_t proto_driverUUID_length = std::min(VK_UUID_SIZE, VK_UUID_SIZE);
  for (uint32_t driverUUID_indx = 0; driverUUID_indx < proto_driverUUID_length; driverUUID_indx++) {
    proto->add_driveruuid(static_cast<uint32_t>(original_struct->driverUUID[driverUUID_indx]));
  }
  const size_t proto_deviceLUID_length = std::min(VK_LUID_SIZE, VK_LUID_SIZE);
  for (uint32_t deviceLUID_indx = 0; deviceLUID_indx < proto_deviceLUID_length; deviceLUID_indx++) {
    proto->add_deviceluid(static_cast<uint32_t>(original_struct->deviceLUID[deviceLUID_indx]));
  }
  proto->set_devicenodemask(original_struct->deviceNodeMask);
  proto->set_deviceluidvalid(original_struct->deviceLUIDValid);
  proto->set_subgroupsize(original_struct->subgroupSize);
  proto->set_subgroupsupportedstages(original_struct->subgroupSupportedStages);
  proto->set_subgroupsupportedoperations(original_struct->subgroupSupportedOperations);
  proto->set_subgroupquadoperationsinallstages(original_struct->subgroupQuadOperationsInAllStages);
  proto->set_pointclippingbehavior(static_cast<vvk::server::VkPointClippingBehavior>(original_struct->pointClippingBehavior));
  proto->set_maxmultiviewviewcount(original_struct->maxMultiviewViewCount);
  proto->set_maxmultiviewinstanceindex(original_struct->maxMultiviewInstanceIndex);
  proto->set_protectednofault(original_struct->protectedNoFault);
  proto->set_maxpersetdescriptors(original_struct->maxPerSetDescriptors);
  proto->set_maxmemoryallocationsize(static_cast<uint64_t>(original_struct->maxMemoryAllocationSize));
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceVulkan12Features* proto, const VkPhysicalDeviceVulkan12Features* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_samplermirrorclamptoedge(original_struct->samplerMirrorClampToEdge);
  proto->set_drawindirectcount(original_struct->drawIndirectCount);
  proto->set_storagebuffer8bitaccess(original_struct->storageBuffer8BitAccess);
  proto->set_uniformandstoragebuffer8bitaccess(original_struct->uniformAndStorageBuffer8BitAccess);
  proto->set_storagepushconstant8(original_struct->storagePushConstant8);
  proto->set_shaderbufferint64atomics(original_struct->shaderBufferInt64Atomics);
  proto->set_shadersharedint64atomics(original_struct->shaderSharedInt64Atomics);
  proto->set_shaderfloat16(original_struct->shaderFloat16);
  proto->set_shaderint8(original_struct->shaderInt8);
  proto->set_descriptorindexing(original_struct->descriptorIndexing);
  proto->set_shaderinputattachmentarraydynamicindexing(original_struct->shaderInputAttachmentArrayDynamicIndexing);
  proto->set_shaderuniformtexelbufferarraydynamicindexing(original_struct->shaderUniformTexelBufferArrayDynamicIndexing);
  proto->set_shaderstoragetexelbufferarraydynamicindexing(original_struct->shaderStorageTexelBufferArrayDynamicIndexing);
  proto->set_shaderuniformbufferarraynonuniformindexing(original_struct->shaderUniformBufferArrayNonUniformIndexing);
  proto->set_shadersampledimagearraynonuniformindexing(original_struct->shaderSampledImageArrayNonUniformIndexing);
  proto->set_shaderstoragebufferarraynonuniformindexing(original_struct->shaderStorageBufferArrayNonUniformIndexing);
  proto->set_shaderstorageimagearraynonuniformindexing(original_struct->shaderStorageImageArrayNonUniformIndexing);
  proto->set_shaderinputattachmentarraynonuniformindexing(original_struct->shaderInputAttachmentArrayNonUniformIndexing);
  proto->set_shaderuniformtexelbufferarraynonuniformindexing(original_struct->shaderUniformTexelBufferArrayNonUniformIndexing);
  proto->set_shaderstoragetexelbufferarraynonuniformindexing(original_struct->shaderStorageTexelBufferArrayNonUniformIndexing);
  proto->set_descriptorbindinguniformbufferupdateafterbind(original_struct->descriptorBindingUniformBufferUpdateAfterBind);
  proto->set_descriptorbindingsampledimageupdateafterbind(original_struct->descriptorBindingSampledImageUpdateAfterBind);
  proto->set_descriptorbindingstorageimageupdateafterbind(original_struct->descriptorBindingStorageImageUpdateAfterBind);
  proto->set_descriptorbindingstoragebufferupdateafterbind(original_struct->descriptorBindingStorageBufferUpdateAfterBind);
  proto->set_descriptorbindinguniformtexelbufferupdateafterbind(original_struct->descriptorBindingUniformTexelBufferUpdateAfterBind);
  proto->set_descriptorbindingstoragetexelbufferupdateafterbind(original_struct->descriptorBindingStorageTexelBufferUpdateAfterBind);
  proto->set_descriptorbindingupdateunusedwhilepending(original_struct->descriptorBindingUpdateUnusedWhilePending);
  proto->set_descriptorbindingpartiallybound(original_struct->descriptorBindingPartiallyBound);
  proto->set_descriptorbindingvariabledescriptorcount(original_struct->descriptorBindingVariableDescriptorCount);
  proto->set_runtimedescriptorarray(original_struct->runtimeDescriptorArray);
  proto->set_samplerfilterminmax(original_struct->samplerFilterMinmax);
  proto->set_scalarblocklayout(original_struct->scalarBlockLayout);
  proto->set_imagelessframebuffer(original_struct->imagelessFramebuffer);
  proto->set_uniformbufferstandardlayout(original_struct->uniformBufferStandardLayout);
  proto->set_shadersubgroupextendedtypes(original_struct->shaderSubgroupExtendedTypes);
  proto->set_separatedepthstencillayouts(original_struct->separateDepthStencilLayouts);
  proto->set_hostqueryreset(original_struct->hostQueryReset);
  proto->set_timelinesemaphore(original_struct->timelineSemaphore);
  proto->set_bufferdeviceaddress(original_struct->bufferDeviceAddress);
  proto->set_bufferdeviceaddresscapturereplay(original_struct->bufferDeviceAddressCaptureReplay);
  proto->set_bufferdeviceaddressmultidevice(original_struct->bufferDeviceAddressMultiDevice);
  proto->set_vulkanmemorymodel(original_struct->vulkanMemoryModel);
  proto->set_vulkanmemorymodeldevicescope(original_struct->vulkanMemoryModelDeviceScope);
  proto->set_vulkanmemorymodelavailabilityvisibilitychains(original_struct->vulkanMemoryModelAvailabilityVisibilityChains);
  proto->set_shaderoutputviewportindex(original_struct->shaderOutputViewportIndex);
  proto->set_shaderoutputlayer(original_struct->shaderOutputLayer);
  proto->set_subgroupbroadcastdynamicid(original_struct->subgroupBroadcastDynamicId);
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceVulkan12Properties* proto, const VkPhysicalDeviceVulkan12Properties* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_driverid(static_cast<vvk::server::VkDriverId>(original_struct->driverID));
  proto->set_drivername(original_struct->driverName);
  proto->set_driverinfo(original_struct->driverInfo);
  FillProtoFromStruct(proto->mutable_conformanceversion(), &original_struct->conformanceVersion);
  proto->set_denormbehaviorindependence(static_cast<vvk::server::VkShaderFloatControlsIndependence>(original_struct->denormBehaviorIndependence));
  proto->set_roundingmodeindependence(static_cast<vvk::server::VkShaderFloatControlsIndependence>(original_struct->roundingModeIndependence));
  proto->set_shadersignedzeroinfnanpreservefloat16(original_struct->shaderSignedZeroInfNanPreserveFloat16);
  proto->set_shadersignedzeroinfnanpreservefloat32(original_struct->shaderSignedZeroInfNanPreserveFloat32);
  proto->set_shadersignedzeroinfnanpreservefloat64(original_struct->shaderSignedZeroInfNanPreserveFloat64);
  proto->set_shaderdenormpreservefloat16(original_struct->shaderDenormPreserveFloat16);
  proto->set_shaderdenormpreservefloat32(original_struct->shaderDenormPreserveFloat32);
  proto->set_shaderdenormpreservefloat64(original_struct->shaderDenormPreserveFloat64);
  proto->set_shaderdenormflushtozerofloat16(original_struct->shaderDenormFlushToZeroFloat16);
  proto->set_shaderdenormflushtozerofloat32(original_struct->shaderDenormFlushToZeroFloat32);
  proto->set_shaderdenormflushtozerofloat64(original_struct->shaderDenormFlushToZeroFloat64);
  proto->set_shaderroundingmodertefloat16(original_struct->shaderRoundingModeRTEFloat16);
  proto->set_shaderroundingmodertefloat32(original_struct->shaderRoundingModeRTEFloat32);
  proto->set_shaderroundingmodertefloat64(original_struct->shaderRoundingModeRTEFloat64);
  proto->set_shaderroundingmodertzfloat16(original_struct->shaderRoundingModeRTZFloat16);
  proto->set_shaderroundingmodertzfloat32(original_struct->shaderRoundingModeRTZFloat32);
  proto->set_shaderroundingmodertzfloat64(original_struct->shaderRoundingModeRTZFloat64);
  proto->set_maxupdateafterbinddescriptorsinallpools(original_struct->maxUpdateAfterBindDescriptorsInAllPools);
  proto->set_shaderuniformbufferarraynonuniformindexingnative(original_struct->shaderUniformBufferArrayNonUniformIndexingNative);
  proto->set_shadersampledimagearraynonuniformindexingnative(original_struct->shaderSampledImageArrayNonUniformIndexingNative);
  proto->set_shaderstoragebufferarraynonuniformindexingnative(original_struct->shaderStorageBufferArrayNonUniformIndexingNative);
  proto->set_shaderstorageimagearraynonuniformindexingnative(original_struct->shaderStorageImageArrayNonUniformIndexingNative);
  proto->set_shaderinputattachmentarraynonuniformindexingnative(original_struct->shaderInputAttachmentArrayNonUniformIndexingNative);
  proto->set_robustbufferaccessupdateafterbind(original_struct->robustBufferAccessUpdateAfterBind);
  proto->set_quaddivergentimplicitlod(original_struct->quadDivergentImplicitLod);
  proto->set_maxperstagedescriptorupdateafterbindsamplers(original_struct->maxPerStageDescriptorUpdateAfterBindSamplers);
  proto->set_maxperstagedescriptorupdateafterbinduniformbuffers(original_struct->maxPerStageDescriptorUpdateAfterBindUniformBuffers);
  proto->set_maxperstagedescriptorupdateafterbindstoragebuffers(original_struct->maxPerStageDescriptorUpdateAfterBindStorageBuffers);
  proto->set_maxperstagedescriptorupdateafterbindsampledimages(original_struct->maxPerStageDescriptorUpdateAfterBindSampledImages);
  proto->set_maxperstagedescriptorupdateafterbindstorageimages(original_struct->maxPerStageDescriptorUpdateAfterBindStorageImages);
  proto->set_maxperstagedescriptorupdateafterbindinputattachments(original_struct->maxPerStageDescriptorUpdateAfterBindInputAttachments);
  proto->set_maxperstageupdateafterbindresources(original_struct->maxPerStageUpdateAfterBindResources);
  proto->set_maxdescriptorsetupdateafterbindsamplers(original_struct->maxDescriptorSetUpdateAfterBindSamplers);
  proto->set_maxdescriptorsetupdateafterbinduniformbuffers(original_struct->maxDescriptorSetUpdateAfterBindUniformBuffers);
  proto->set_maxdescriptorsetupdateafterbinduniformbuffersdynamic(original_struct->maxDescriptorSetUpdateAfterBindUniformBuffersDynamic);
  proto->set_maxdescriptorsetupdateafterbindstoragebuffers(original_struct->maxDescriptorSetUpdateAfterBindStorageBuffers);
  proto->set_maxdescriptorsetupdateafterbindstoragebuffersdynamic(original_struct->maxDescriptorSetUpdateAfterBindStorageBuffersDynamic);
  proto->set_maxdescriptorsetupdateafterbindsampledimages(original_struct->maxDescriptorSetUpdateAfterBindSampledImages);
  proto->set_maxdescriptorsetupdateafterbindstorageimages(original_struct->maxDescriptorSetUpdateAfterBindStorageImages);
  proto->set_maxdescriptorsetupdateafterbindinputattachments(original_struct->maxDescriptorSetUpdateAfterBindInputAttachments);
  proto->set_supporteddepthresolvemodes(original_struct->supportedDepthResolveModes);
  proto->set_supportedstencilresolvemodes(original_struct->supportedStencilResolveModes);
  proto->set_independentresolvenone(original_struct->independentResolveNone);
  proto->set_independentresolve(original_struct->independentResolve);
  proto->set_filterminmaxsinglecomponentformats(original_struct->filterMinmaxSingleComponentFormats);
  proto->set_filterminmaximagecomponentmapping(original_struct->filterMinmaxImageComponentMapping);
  proto->set_maxtimelinesemaphorevaluedifference(original_struct->maxTimelineSemaphoreValueDifference);
  if (original_struct->framebufferIntegerColorSampleCounts) {
    proto->set_framebufferintegercolorsamplecounts(original_struct->framebufferIntegerColorSampleCounts);
  }
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceVulkan13Features* proto, const VkPhysicalDeviceVulkan13Features* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_robustimageaccess(original_struct->robustImageAccess);
  proto->set_inlineuniformblock(original_struct->inlineUniformBlock);
  proto->set_descriptorbindinginlineuniformblockupdateafterbind(original_struct->descriptorBindingInlineUniformBlockUpdateAfterBind);
  proto->set_pipelinecreationcachecontrol(original_struct->pipelineCreationCacheControl);
  proto->set_privatedata(original_struct->privateData);
  proto->set_shaderdemotetohelperinvocation(original_struct->shaderDemoteToHelperInvocation);
  proto->set_shaderterminateinvocation(original_struct->shaderTerminateInvocation);
  proto->set_subgroupsizecontrol(original_struct->subgroupSizeControl);
  proto->set_computefullsubgroups(original_struct->computeFullSubgroups);
  proto->set_synchronization2(original_struct->synchronization2);
  proto->set_texturecompressionastc_hdr(original_struct->textureCompressionASTC_HDR);
  proto->set_shaderzeroinitializeworkgroupmemory(original_struct->shaderZeroInitializeWorkgroupMemory);
  proto->set_dynamicrendering(original_struct->dynamicRendering);
  proto->set_shaderintegerdotproduct(original_struct->shaderIntegerDotProduct);
  proto->set_maintenance4(original_struct->maintenance4);
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceVulkan13Properties* proto, const VkPhysicalDeviceVulkan13Properties* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_minsubgroupsize(original_struct->minSubgroupSize);
  proto->set_maxsubgroupsize(original_struct->maxSubgroupSize);
  proto->set_maxcomputeworkgroupsubgroups(original_struct->maxComputeWorkgroupSubgroups);
  proto->set_requiredsubgroupsizestages(original_struct->requiredSubgroupSizeStages);
  proto->set_maxinlineuniformblocksize(original_struct->maxInlineUniformBlockSize);
  proto->set_maxperstagedescriptorinlineuniformblocks(original_struct->maxPerStageDescriptorInlineUniformBlocks);
  proto->set_maxperstagedescriptorupdateafterbindinlineuniformblocks(original_struct->maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks);
  proto->set_maxdescriptorsetinlineuniformblocks(original_struct->maxDescriptorSetInlineUniformBlocks);
  proto->set_maxdescriptorsetupdateafterbindinlineuniformblocks(original_struct->maxDescriptorSetUpdateAfterBindInlineUniformBlocks);
  proto->set_maxinlineuniformtotalsize(original_struct->maxInlineUniformTotalSize);
  proto->set_integerdotproduct8bitunsignedaccelerated(original_struct->integerDotProduct8BitUnsignedAccelerated);
  proto->set_integerdotproduct8bitsignedaccelerated(original_struct->integerDotProduct8BitSignedAccelerated);
  proto->set_integerdotproduct8bitmixedsignednessaccelerated(original_struct->integerDotProduct8BitMixedSignednessAccelerated);
  proto->set_integerdotproduct4x8bitpackedunsignedaccelerated(original_struct->integerDotProduct4x8BitPackedUnsignedAccelerated);
  proto->set_integerdotproduct4x8bitpackedsignedaccelerated(original_struct->integerDotProduct4x8BitPackedSignedAccelerated);
  proto->set_integerdotproduct4x8bitpackedmixedsignednessaccelerated(original_struct->integerDotProduct4x8BitPackedMixedSignednessAccelerated);
  proto->set_integerdotproduct16bitunsignedaccelerated(original_struct->integerDotProduct16BitUnsignedAccelerated);
  proto->set_integerdotproduct16bitsignedaccelerated(original_struct->integerDotProduct16BitSignedAccelerated);
  proto->set_integerdotproduct16bitmixedsignednessaccelerated(original_struct->integerDotProduct16BitMixedSignednessAccelerated);
  proto->set_integerdotproduct32bitunsignedaccelerated(original_struct->integerDotProduct32BitUnsignedAccelerated);
  proto->set_integerdotproduct32bitsignedaccelerated(original_struct->integerDotProduct32BitSignedAccelerated);
  proto->set_integerdotproduct32bitmixedsignednessaccelerated(original_struct->integerDotProduct32BitMixedSignednessAccelerated);
  proto->set_integerdotproduct64bitunsignedaccelerated(original_struct->integerDotProduct64BitUnsignedAccelerated);
  proto->set_integerdotproduct64bitsignedaccelerated(original_struct->integerDotProduct64BitSignedAccelerated);
  proto->set_integerdotproduct64bitmixedsignednessaccelerated(original_struct->integerDotProduct64BitMixedSignednessAccelerated);
  proto->set_integerdotproductaccumulatingsaturating8bitunsignedaccelerated(original_struct->integerDotProductAccumulatingSaturating8BitUnsignedAccelerated);
  proto->set_integerdotproductaccumulatingsaturating8bitsignedaccelerated(original_struct->integerDotProductAccumulatingSaturating8BitSignedAccelerated);
  proto->set_integerdotproductaccumulatingsaturating8bitmixedsignednessaccelerated(original_struct->integerDotProductAccumulatingSaturating8BitMixedSignednessAccelerated);
  proto->set_integerdotproductaccumulatingsaturating4x8bitpackedunsignedaccelerated(original_struct->integerDotProductAccumulatingSaturating4x8BitPackedUnsignedAccelerated);
  proto->set_integerdotproductaccumulatingsaturating4x8bitpackedsignedaccelerated(original_struct->integerDotProductAccumulatingSaturating4x8BitPackedSignedAccelerated);
  proto->set_integerdotproductaccumulatingsaturating4x8bitpackedmixedsignednessaccelerated(original_struct->integerDotProductAccumulatingSaturating4x8BitPackedMixedSignednessAccelerated);
  proto->set_integerdotproductaccumulatingsaturating16bitunsignedaccelerated(original_struct->integerDotProductAccumulatingSaturating16BitUnsignedAccelerated);
  proto->set_integerdotproductaccumulatingsaturating16bitsignedaccelerated(original_struct->integerDotProductAccumulatingSaturating16BitSignedAccelerated);
  proto->set_integerdotproductaccumulatingsaturating16bitmixedsignednessaccelerated(original_struct->integerDotProductAccumulatingSaturating16BitMixedSignednessAccelerated);
  proto->set_integerdotproductaccumulatingsaturating32bitunsignedaccelerated(original_struct->integerDotProductAccumulatingSaturating32BitUnsignedAccelerated);
  proto->set_integerdotproductaccumulatingsaturating32bitsignedaccelerated(original_struct->integerDotProductAccumulatingSaturating32BitSignedAccelerated);
  proto->set_integerdotproductaccumulatingsaturating32bitmixedsignednessaccelerated(original_struct->integerDotProductAccumulatingSaturating32BitMixedSignednessAccelerated);
  proto->set_integerdotproductaccumulatingsaturating64bitunsignedaccelerated(original_struct->integerDotProductAccumulatingSaturating64BitUnsignedAccelerated);
  proto->set_integerdotproductaccumulatingsaturating64bitsignedaccelerated(original_struct->integerDotProductAccumulatingSaturating64BitSignedAccelerated);
  proto->set_integerdotproductaccumulatingsaturating64bitmixedsignednessaccelerated(original_struct->integerDotProductAccumulatingSaturating64BitMixedSignednessAccelerated);
  proto->set_storagetexelbufferoffsetalignmentbytes(static_cast<uint64_t>(original_struct->storageTexelBufferOffsetAlignmentBytes));
  proto->set_storagetexelbufferoffsetsingletexelalignment(original_struct->storageTexelBufferOffsetSingleTexelAlignment);
  proto->set_uniformtexelbufferoffsetalignmentbytes(static_cast<uint64_t>(original_struct->uniformTexelBufferOffsetAlignmentBytes));
  proto->set_uniformtexelbufferoffsetsingletexelalignment(original_struct->uniformTexelBufferOffsetSingleTexelAlignment);
  proto->set_maxbuffersize(static_cast<uint64_t>(original_struct->maxBufferSize));
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceVulkan14Features* proto, const VkPhysicalDeviceVulkan14Features* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_globalpriorityquery(original_struct->globalPriorityQuery);
  proto->set_shadersubgrouprotate(original_struct->shaderSubgroupRotate);
  proto->set_shadersubgrouprotateclustered(original_struct->shaderSubgroupRotateClustered);
  proto->set_shaderfloatcontrols2(original_struct->shaderFloatControls2);
  proto->set_shaderexpectassume(original_struct->shaderExpectAssume);
  proto->set_rectangularlines(original_struct->rectangularLines);
  proto->set_bresenhamlines(original_struct->bresenhamLines);
  proto->set_smoothlines(original_struct->smoothLines);
  proto->set_stippledrectangularlines(original_struct->stippledRectangularLines);
  proto->set_stippledbresenhamlines(original_struct->stippledBresenhamLines);
  proto->set_stippledsmoothlines(original_struct->stippledSmoothLines);
  proto->set_vertexattributeinstanceratedivisor(original_struct->vertexAttributeInstanceRateDivisor);
  proto->set_vertexattributeinstanceratezerodivisor(original_struct->vertexAttributeInstanceRateZeroDivisor);
  proto->set_indextypeuint8(original_struct->indexTypeUint8);
  proto->set_dynamicrenderinglocalread(original_struct->dynamicRenderingLocalRead);
  proto->set_maintenance5(original_struct->maintenance5);
  proto->set_maintenance6(original_struct->maintenance6);
  proto->set_pipelineprotectedaccess(original_struct->pipelineProtectedAccess);
  proto->set_pipelinerobustness(original_struct->pipelineRobustness);
  proto->set_hostimagecopy(original_struct->hostImageCopy);
  proto->set_pushdescriptor(original_struct->pushDescriptor);
}
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceVulkan14Properties* proto, const VkPhysicalDeviceVulkan14Properties* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_linesubpixelprecisionbits(original_struct->lineSubPixelPrecisionBits);
  proto->set_maxvertexattribdivisor(original_struct->maxVertexAttribDivisor);
  proto->set_supportsnonzerofirstinstance(original_struct->supportsNonZeroFirstInstance);
  proto->set_maxpushdescriptors(original_struct->maxPushDescriptors);
  proto->set_dynamicrenderinglocalreaddepthstencilattachments(original_struct->dynamicRenderingLocalReadDepthStencilAttachments);
  proto->set_dynamicrenderinglocalreadmultisampledattachments(original_struct->dynamicRenderingLocalReadMultisampledAttachments);
  proto->set_earlyfragmentmultisamplecoverageaftersamplecounting(original_struct->earlyFragmentMultisampleCoverageAfterSampleCounting);
  proto->set_earlyfragmentsamplemasktestbeforesamplecounting(original_struct->earlyFragmentSampleMaskTestBeforeSampleCounting);
  proto->set_depthstencilswizzleonesupport(original_struct->depthStencilSwizzleOneSupport);
  proto->set_polygonmodepointsize(original_struct->polygonModePointSize);
  proto->set_nonstrictsinglepixelwidelinesuseparallelogram(original_struct->nonStrictSinglePixelWideLinesUseParallelogram);
  proto->set_nonstrictwidelinesuseparallelogram(original_struct->nonStrictWideLinesUseParallelogram);
  proto->set_blocktexelviewcompatiblemultiplelayers(original_struct->blockTexelViewCompatibleMultipleLayers);
  proto->set_maxcombinedimagesamplerdescriptorcount(original_struct->maxCombinedImageSamplerDescriptorCount);
  proto->set_fragmentshadingrateclampcombinerinputs(original_struct->fragmentShadingRateClampCombinerInputs);
  proto->set_defaultrobustnessstoragebuffers(static_cast<vvk::server::VkPipelineRobustnessBufferBehavior>(original_struct->defaultRobustnessStorageBuffers));
  proto->set_defaultrobustnessuniformbuffers(static_cast<vvk::server::VkPipelineRobustnessBufferBehavior>(original_struct->defaultRobustnessUniformBuffers));
  proto->set_defaultrobustnessvertexinputs(static_cast<vvk::server::VkPipelineRobustnessBufferBehavior>(original_struct->defaultRobustnessVertexInputs));
  proto->set_defaultrobustnessimages(static_cast<vvk::server::VkPipelineRobustnessImageBehavior>(original_struct->defaultRobustnessImages));
  if (original_struct->copySrcLayoutCount) {
    proto->set_copysrclayoutcount(original_struct->copySrcLayoutCount);
  }
  if (original_struct->pCopySrcLayouts) {
    const size_t proto_pCopySrcLayouts_length = original_struct->copySrcLayoutCount;
    for (uint32_t pCopySrcLayouts_indx = 0; pCopySrcLayouts_indx < proto_pCopySrcLayouts_length; pCopySrcLayouts_indx++) {
      proto->add_pcopysrclayouts(static_cast<vvk::server::VkImageLayout>(original_struct->pCopySrcLayouts[pCopySrcLayouts_indx]));
    }
  }
  if (original_struct->copyDstLayoutCount) {
    proto->set_copydstlayoutcount(original_struct->copyDstLayoutCount);
  }
  if (original_struct->pCopyDstLayouts) {
    const size_t proto_pCopyDstLayouts_length = original_struct->copyDstLayoutCount;
    for (uint32_t pCopyDstLayouts_indx = 0; pCopyDstLayouts_indx < proto_pCopyDstLayouts_length; pCopyDstLayouts_indx++) {
      proto->add_pcopydstlayouts(static_cast<vvk::server::VkImageLayout>(original_struct->pCopyDstLayouts[pCopyDstLayouts_indx]));
    }
  }
  if (original_struct->optimalTilingLayoutUUID) {
    const size_t proto_optimalTilingLayoutUUID_length = std::min(VK_UUID_SIZE, VK_UUID_SIZE);
    for (uint32_t optimalTilingLayoutUUID_indx = 0; optimalTilingLayoutUUID_indx < proto_optimalTilingLayoutUUID_length; optimalTilingLayoutUUID_indx++) {
      proto->add_optimaltilinglayoutuuid(static_cast<uint32_t>(original_struct->optimalTilingLayoutUUID[optimalTilingLayoutUUID_indx]));
    }
  }
  proto->set_identicalmemorytyperequirements(original_struct->identicalMemoryTypeRequirements);
}
void FillProtoFromStruct(vvk::server::VkQueueFamilyProperties* proto, const VkQueueFamilyProperties* original_struct) {
  if (original_struct->queueFlags) {
    proto->set_queueflags(original_struct->queueFlags);
  }
  proto->set_queuecount(original_struct->queueCount);
  proto->set_timestampvalidbits(original_struct->timestampValidBits);
  FillProtoFromStruct(proto->mutable_minimagetransfergranularity(), &original_struct->minImageTransferGranularity);
}
void FillProtoFromStruct(vvk::server::VkSubresourceLayout* proto, const VkSubresourceLayout* original_struct) {
  proto->set_offset(static_cast<uint64_t>(original_struct->offset));
  proto->set_size(static_cast<uint64_t>(original_struct->size));
  proto->set_rowpitch(static_cast<uint64_t>(original_struct->rowPitch));
  proto->set_arraypitch(static_cast<uint64_t>(original_struct->arrayPitch));
  proto->set_depthpitch(static_cast<uint64_t>(original_struct->depthPitch));
}
void FillStructFromProto(VkApplicationInfo& original_struct, const vvk::server::VkApplicationInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_papplicationname()) {
    original_struct.pApplicationName = proto.papplicationname().data();
  } else {
    original_struct.pApplicationName = nullptr;
  }
  original_struct.applicationVersion = proto.applicationversion();
  if (proto.has_penginename()) {
    original_struct.pEngineName = proto.penginename().data();
  } else {
    original_struct.pEngineName = nullptr;
  }
  original_struct.engineVersion = proto.engineversion();
  original_struct.apiVersion = proto.apiversion();
}
void FillStructFromProto(VkAttachmentDescription& original_struct, const vvk::server::VkAttachmentDescription& proto) {
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkAttachmentDescriptionFlags>(proto.flags());
  } else {
    original_struct.flags = VkAttachmentDescriptionFlags{};
  }
  original_struct.format = static_cast<VkFormat>(proto.format());
  original_struct.samples = static_cast<VkSampleCountFlagBits>(proto.samples());
  original_struct.loadOp = static_cast<VkAttachmentLoadOp>(proto.loadop());
  original_struct.storeOp = static_cast<VkAttachmentStoreOp>(proto.storeop());
  original_struct.stencilLoadOp = static_cast<VkAttachmentLoadOp>(proto.stencilloadop());
  original_struct.stencilStoreOp = static_cast<VkAttachmentStoreOp>(proto.stencilstoreop());
  original_struct.initialLayout = static_cast<VkImageLayout>(proto.initiallayout());
  original_struct.finalLayout = static_cast<VkImageLayout>(proto.finallayout());
}
void FillStructFromProto(VkAttachmentReference& original_struct, const vvk::server::VkAttachmentReference& proto) {
  original_struct.attachment = proto.attachment();
  original_struct.layout = static_cast<VkImageLayout>(proto.layout());
}
void FillStructFromProto(VkBindImageMemoryInfo& original_struct, const vvk::server::VkBindImageMemoryInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  original_struct.image = reinterpret_cast<VkImage>(proto.image());
  original_struct.memory = reinterpret_cast<VkDeviceMemory>(proto.memory());
  original_struct.memoryOffset = static_cast<VkDeviceSize>(proto.memoryoffset());
}
void FillStructFromProto(VkBufferCreateInfo& original_struct, const vvk::server::VkBufferCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkBufferCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkBufferCreateFlags{};
  }
  original_struct.size = static_cast<VkDeviceSize>(proto.size());
  original_struct.usage = static_cast<VkBufferUsageFlags>(proto.usage());
  original_struct.sharingMode = static_cast<VkSharingMode>(proto.sharingmode());
  if (proto.has_queuefamilyindexcount()) {
    original_struct.queueFamilyIndexCount = proto.queuefamilyindexcount();
  } else {
    original_struct.queueFamilyIndexCount = uint32_t{};
  }
  uint32_t* original_struct_pQueueFamilyIndices = new uint32_t[proto.pqueuefamilyindices_size()]();
  original_struct.pQueueFamilyIndices = original_struct_pQueueFamilyIndices;
  for (int pQueueFamilyIndices_indx = 0; pQueueFamilyIndices_indx < proto.pqueuefamilyindices_size(); pQueueFamilyIndices_indx++) {
    original_struct_pQueueFamilyIndices[pQueueFamilyIndices_indx] = proto.pqueuefamilyindices(pQueueFamilyIndices_indx);
  }
}
void FillStructFromProto(VkBufferImageCopy& original_struct, const vvk::server::VkBufferImageCopy& proto) {
  original_struct.bufferOffset = static_cast<VkDeviceSize>(proto.bufferoffset());
  original_struct.bufferRowLength = proto.bufferrowlength();
  original_struct.bufferImageHeight = proto.bufferimageheight();
  VkImageSubresourceLayers &original_struct_imageSubresource = original_struct.imageSubresource;
  FillStructFromProto(original_struct_imageSubresource, proto.imagesubresource());
  VkOffset3D &original_struct_imageOffset = original_struct.imageOffset;
  FillStructFromProto(original_struct_imageOffset, proto.imageoffset());
  VkExtent3D &original_struct_imageExtent = original_struct.imageExtent;
  FillStructFromProto(original_struct_imageExtent, proto.imageextent());
}
void FillStructFromProto(VkBufferMemoryBarrier& original_struct, const vvk::server::VkBufferMemoryBarrier& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
  original_struct.pNext = nullptr;  // Empty pNext chain
  original_struct.srcAccessMask = static_cast<VkAccessFlags>(proto.srcaccessmask());
  original_struct.dstAccessMask = static_cast<VkAccessFlags>(proto.dstaccessmask());
  original_struct.srcQueueFamilyIndex = proto.srcqueuefamilyindex();
  original_struct.dstQueueFamilyIndex = proto.dstqueuefamilyindex();
  original_struct.buffer = reinterpret_cast<VkBuffer>(proto.buffer());
  original_struct.offset = static_cast<VkDeviceSize>(proto.offset());
  original_struct.size = static_cast<VkDeviceSize>(proto.size());
}
void FillStructFromProto(VkClearColorValue& original_struct, const vvk::server::VkClearColorValue& proto) {
  const size_t original_struct_float32_length = std::min(4, 4);
  for (uint32_t float32_indx = 0; float32_indx < original_struct_float32_length; float32_indx++) {
    original_struct.float32[float32_indx] = proto.float32(float32_indx);
  }
  const size_t original_struct_int32_length = std::min(4, 4);
  for (uint32_t int32_indx = 0; int32_indx < original_struct_int32_length; int32_indx++) {
    original_struct.int32[int32_indx] = proto.int32(int32_indx);
  }
  const size_t original_struct_uint32_length = std::min(4, 4);
  for (uint32_t uint32_indx = 0; uint32_indx < original_struct_uint32_length; uint32_indx++) {
    original_struct.uint32[uint32_indx] = proto.uint32(uint32_indx);
  }
}
void FillStructFromProto(VkClearDepthStencilValue& original_struct, const vvk::server::VkClearDepthStencilValue& proto) {
  original_struct.depth = proto.depth();
  original_struct.stencil = proto.stencil();
}
void FillStructFromProto(VkClearValue& original_struct, const vvk::server::VkClearValue& proto) {
  VkClearColorValue &original_struct_color = original_struct.color;
  FillStructFromProto(original_struct_color, proto.color());
  VkClearDepthStencilValue &original_struct_depthStencil = original_struct.depthStencil;
  FillStructFromProto(original_struct_depthStencil, proto.depthstencil());
}
void FillStructFromProto(VkCommandBufferAllocateInfo& original_struct, const vvk::server::VkCommandBufferAllocateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  original_struct.commandPool = reinterpret_cast<VkCommandPool>(proto.commandpool());
  original_struct.level = static_cast<VkCommandBufferLevel>(proto.level());
  original_struct.commandBufferCount = proto.commandbuffercount();
}
void FillStructFromProto(VkCommandBufferBeginInfo& original_struct, const vvk::server::VkCommandBufferBeginInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkCommandBufferUsageFlags>(proto.flags());
  } else {
    original_struct.flags = VkCommandBufferUsageFlags{};
  }
  if (proto.has_pinheritanceinfo()) {
    VkCommandBufferInheritanceInfo* original_struct_pInheritanceInfo = new VkCommandBufferInheritanceInfo;
    FillStructFromProto(*original_struct_pInheritanceInfo, proto.pinheritanceinfo());
    original_struct.pInheritanceInfo = original_struct_pInheritanceInfo;
  } else {
    original_struct.pInheritanceInfo = nullptr;
  }
}
void FillStructFromProto(VkCommandBufferInheritanceInfo& original_struct, const vvk::server::VkCommandBufferInheritanceInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_renderpass()) {
    original_struct.renderPass = reinterpret_cast<VkRenderPass>(proto.renderpass());
  } else {
    original_struct.renderPass = VkRenderPass{};
  }
  original_struct.subpass = proto.subpass();
  if (proto.has_framebuffer()) {
    original_struct.framebuffer = reinterpret_cast<VkFramebuffer>(proto.framebuffer());
  } else {
    original_struct.framebuffer = VkFramebuffer{};
  }
  original_struct.occlusionQueryEnable = proto.occlusionqueryenable();
  if (proto.has_queryflags()) {
    original_struct.queryFlags = static_cast<VkQueryControlFlags>(proto.queryflags());
  } else {
    original_struct.queryFlags = VkQueryControlFlags{};
  }
  if (proto.has_pipelinestatistics()) {
    original_struct.pipelineStatistics = static_cast<VkQueryPipelineStatisticFlags>(proto.pipelinestatistics());
  } else {
    original_struct.pipelineStatistics = VkQueryPipelineStatisticFlags{};
  }
}
void FillStructFromProto(VkCommandPoolCreateInfo& original_struct, const vvk::server::VkCommandPoolCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkCommandPoolCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkCommandPoolCreateFlags{};
  }
  original_struct.queueFamilyIndex = proto.queuefamilyindex();
}
void FillStructFromProto(VkComponentMapping& original_struct, const vvk::server::VkComponentMapping& proto) {
  original_struct.r = static_cast<VkComponentSwizzle>(proto.r());
  original_struct.g = static_cast<VkComponentSwizzle>(proto.g());
  original_struct.b = static_cast<VkComponentSwizzle>(proto.b());
  original_struct.a = static_cast<VkComponentSwizzle>(proto.a());
}
void FillStructFromProto(VkConformanceVersion& original_struct, const vvk::server::VkConformanceVersion& proto) {
  original_struct.major = static_cast<uint8_t>(proto.major());
  original_struct.minor = static_cast<uint8_t>(proto.minor());
  original_struct.subminor = static_cast<uint8_t>(proto.subminor());
  original_struct.patch = static_cast<uint8_t>(proto.patch());
}
void FillStructFromProto(VkCopyDescriptorSet& original_struct, const vvk::server::VkCopyDescriptorSet& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET;
  original_struct.pNext = nullptr;  // Empty pNext chain
  original_struct.srcSet = reinterpret_cast<VkDescriptorSet>(proto.srcset());
  original_struct.srcBinding = proto.srcbinding();
  original_struct.srcArrayElement = proto.srcarrayelement();
  original_struct.dstSet = reinterpret_cast<VkDescriptorSet>(proto.dstset());
  original_struct.dstBinding = proto.dstbinding();
  original_struct.dstArrayElement = proto.dstarrayelement();
  original_struct.descriptorCount = proto.descriptorcount();
}
void FillStructFromProto(VkDescriptorBufferInfo& original_struct, const vvk::server::VkDescriptorBufferInfo& proto) {
  if (proto.has_buffer()) {
    original_struct.buffer = reinterpret_cast<VkBuffer>(proto.buffer());
  } else {
    original_struct.buffer = VkBuffer{};
  }
  original_struct.offset = static_cast<VkDeviceSize>(proto.offset());
  original_struct.range = static_cast<VkDeviceSize>(proto.range());
}
void FillStructFromProto(VkDescriptorImageInfo& original_struct, const vvk::server::VkDescriptorImageInfo& proto) {
  original_struct.sampler = reinterpret_cast<VkSampler>(proto.sampler());
  original_struct.imageView = reinterpret_cast<VkImageView>(proto.imageview());
  original_struct.imageLayout = static_cast<VkImageLayout>(proto.imagelayout());
}
void FillStructFromProto(VkDescriptorPoolCreateInfo& original_struct, const vvk::server::VkDescriptorPoolCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkDescriptorPoolCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkDescriptorPoolCreateFlags{};
  }
  original_struct.maxSets = proto.maxsets();
  if (proto.has_poolsizecount()) {
    original_struct.poolSizeCount = proto.poolsizecount();
  } else {
    original_struct.poolSizeCount = uint32_t{};
  }
  VkDescriptorPoolSize* original_struct_pPoolSizes = new VkDescriptorPoolSize[proto.ppoolsizes_size()]();
  original_struct.pPoolSizes = original_struct_pPoolSizes;
  for (int pPoolSizes_indx = 0; pPoolSizes_indx < proto.ppoolsizes_size(); pPoolSizes_indx++) {
    VkDescriptorPoolSize &original_struct_pPoolSizes_i = original_struct_pPoolSizes[pPoolSizes_indx];
    FillStructFromProto(original_struct_pPoolSizes_i, proto.ppoolsizes(pPoolSizes_indx));
  }
}
void FillStructFromProto(VkDescriptorPoolSize& original_struct, const vvk::server::VkDescriptorPoolSize& proto) {
  original_struct.type = static_cast<VkDescriptorType>(proto.type());
  original_struct.descriptorCount = proto.descriptorcount();
}
void FillStructFromProto(VkDescriptorSetAllocateInfo& original_struct, const vvk::server::VkDescriptorSetAllocateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  original_struct.descriptorPool = reinterpret_cast<VkDescriptorPool>(proto.descriptorpool());
  original_struct.descriptorSetCount = proto.descriptorsetcount();
  original_struct.pSetLayouts = reinterpret_cast<const VkDescriptorSetLayout*>(proto.psetlayouts().data());
}
void FillStructFromProto(VkDescriptorSetLayoutBinding& original_struct, const vvk::server::VkDescriptorSetLayoutBinding& proto) {
  original_struct.binding = proto.binding();
  original_struct.descriptorType = static_cast<VkDescriptorType>(proto.descriptortype());
  if (proto.has_descriptorcount()) {
    original_struct.descriptorCount = proto.descriptorcount();
  } else {
    original_struct.descriptorCount = uint32_t{};
  }
  original_struct.stageFlags = static_cast<VkShaderStageFlags>(proto.stageflags());
  if (proto.pimmutablesamplers_size()) {
    original_struct.pImmutableSamplers = reinterpret_cast<const VkSampler*>(proto.pimmutablesamplers().data());
  } else {
    original_struct.pImmutableSamplers = nullptr;
  }
}
void FillStructFromProto(VkDescriptorSetLayoutCreateInfo& original_struct, const vvk::server::VkDescriptorSetLayoutCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkDescriptorSetLayoutCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkDescriptorSetLayoutCreateFlags{};
  }
  if (proto.has_bindingcount()) {
    original_struct.bindingCount = proto.bindingcount();
  } else {
    original_struct.bindingCount = uint32_t{};
  }
  VkDescriptorSetLayoutBinding* original_struct_pBindings = new VkDescriptorSetLayoutBinding[proto.pbindings_size()]();
  original_struct.pBindings = original_struct_pBindings;
  for (int pBindings_indx = 0; pBindings_indx < proto.pbindings_size(); pBindings_indx++) {
    VkDescriptorSetLayoutBinding &original_struct_pBindings_i = original_struct_pBindings[pBindings_indx];
    FillStructFromProto(original_struct_pBindings_i, proto.pbindings(pBindings_indx));
  }
}
void FillStructFromProto(VkDeviceCreateInfo& original_struct, const vvk::server::VkDeviceCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  VkBaseOutStructure* base = reinterpret_cast<VkBaseOutStructure*>(&original_struct);
  for (const auto& pnext : proto.pnext()) {
    if (pnext.has_vkphysicaldeviceprotectedmemoryfeatures_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceProtectedMemoryFeatures);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceProtectedMemoryFeatures*>(base->pNext), pnext.vkphysicaldeviceprotectedmemoryfeatures_chain_elem());
    }
    if (pnext.has_vkphysicaldeviceshaderdrawparametersfeatures_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceShaderDrawParametersFeatures);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceShaderDrawParametersFeatures*>(base->pNext), pnext.vkphysicaldeviceshaderdrawparametersfeatures_chain_elem());
    }
    if (pnext.has_vkphysicaldevicetimelinesemaphorefeatures_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceTimelineSemaphoreFeatures);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceTimelineSemaphoreFeatures*>(base->pNext), pnext.vkphysicaldevicetimelinesemaphorefeatures_chain_elem());
    }
    if (pnext.has_vkphysicaldevicevulkan11features_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceVulkan11Features);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceVulkan11Features*>(base->pNext), pnext.vkphysicaldevicevulkan11features_chain_elem());
    }
    if (pnext.has_vkphysicaldevicevulkan12features_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceVulkan12Features);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceVulkan12Features*>(base->pNext), pnext.vkphysicaldevicevulkan12features_chain_elem());
    }
    if (pnext.has_vkphysicaldevicevulkan13features_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceVulkan13Features);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceVulkan13Features*>(base->pNext), pnext.vkphysicaldevicevulkan13features_chain_elem());
    }
    if (pnext.has_vkphysicaldevicevulkan14features_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceVulkan14Features);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceVulkan14Features*>(base->pNext), pnext.vkphysicaldevicevulkan14features_chain_elem());
    }
    base = base->pNext;
  }
  base->pNext = nullptr;
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkDeviceCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkDeviceCreateFlags{};
  }
  original_struct.queueCreateInfoCount = proto.queuecreateinfocount();
  VkDeviceQueueCreateInfo* original_struct_pQueueCreateInfos = new VkDeviceQueueCreateInfo[proto.pqueuecreateinfos_size()]();
  original_struct.pQueueCreateInfos = original_struct_pQueueCreateInfos;
  for (int pQueueCreateInfos_indx = 0; pQueueCreateInfos_indx < proto.pqueuecreateinfos_size(); pQueueCreateInfos_indx++) {
    VkDeviceQueueCreateInfo &original_struct_pQueueCreateInfos_i = original_struct_pQueueCreateInfos[pQueueCreateInfos_indx];
    FillStructFromProto(original_struct_pQueueCreateInfos_i, proto.pqueuecreateinfos(pQueueCreateInfos_indx));
  }
  if (proto.has_enabledlayercount()) {
    original_struct.enabledLayerCount = proto.enabledlayercount();
  } else {
    original_struct.enabledLayerCount = uint32_t{};
  }
  const char** original_struct_ppEnabledLayerNames = new const char*[proto.ppenabledlayernames_size()]();
  original_struct.ppEnabledLayerNames = original_struct_ppEnabledLayerNames;
  for (int ppEnabledLayerNames_indx = 0; ppEnabledLayerNames_indx < proto.ppenabledlayernames_size(); ppEnabledLayerNames_indx++) {
    original_struct_ppEnabledLayerNames[ppEnabledLayerNames_indx] = proto.ppenabledlayernames(ppEnabledLayerNames_indx).data();
  }
  if (proto.has_enabledextensioncount()) {
    original_struct.enabledExtensionCount = proto.enabledextensioncount();
  } else {
    original_struct.enabledExtensionCount = uint32_t{};
  }
  const char** original_struct_ppEnabledExtensionNames = new const char*[proto.ppenabledextensionnames_size()]();
  original_struct.ppEnabledExtensionNames = original_struct_ppEnabledExtensionNames;
  for (int ppEnabledExtensionNames_indx = 0; ppEnabledExtensionNames_indx < proto.ppenabledextensionnames_size(); ppEnabledExtensionNames_indx++) {
    original_struct_ppEnabledExtensionNames[ppEnabledExtensionNames_indx] = proto.ppenabledextensionnames(ppEnabledExtensionNames_indx).data();
  }
  if (proto.has_penabledfeatures()) {
    VkPhysicalDeviceFeatures* original_struct_pEnabledFeatures = new VkPhysicalDeviceFeatures;
    FillStructFromProto(*original_struct_pEnabledFeatures, proto.penabledfeatures());
    original_struct.pEnabledFeatures = original_struct_pEnabledFeatures;
  } else {
    original_struct.pEnabledFeatures = nullptr;
  }
}
void FillStructFromProto(VkDeviceQueueCreateInfo& original_struct, const vvk::server::VkDeviceQueueCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkDeviceQueueCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkDeviceQueueCreateFlags{};
  }
  original_struct.queueFamilyIndex = proto.queuefamilyindex();
  original_struct.queueCount = proto.queuecount();
  float* original_struct_pQueuePriorities = new float[proto.pqueuepriorities_size()]();
  original_struct.pQueuePriorities = original_struct_pQueuePriorities;
  for (int pQueuePriorities_indx = 0; pQueuePriorities_indx < proto.pqueuepriorities_size(); pQueuePriorities_indx++) {
    original_struct_pQueuePriorities[pQueuePriorities_indx] = proto.pqueuepriorities(pQueuePriorities_indx);
  }
}
void FillStructFromProto(VkExtent2D& original_struct, const vvk::server::VkExtent2D& proto) {
  original_struct.width = proto.width();
  original_struct.height = proto.height();
}
void FillStructFromProto(VkExtent3D& original_struct, const vvk::server::VkExtent3D& proto) {
  original_struct.width = proto.width();
  original_struct.height = proto.height();
  original_struct.depth = proto.depth();
}
void FillStructFromProto(VkFenceCreateInfo& original_struct, const vvk::server::VkFenceCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkFenceCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkFenceCreateFlags{};
  }
}
void FillStructFromProto(VkFormatProperties& original_struct, const vvk::server::VkFormatProperties& proto) {
  if (proto.has_lineartilingfeatures()) {
    original_struct.linearTilingFeatures = static_cast<VkFormatFeatureFlags>(proto.lineartilingfeatures());
  } else {
    original_struct.linearTilingFeatures = VkFormatFeatureFlags{};
  }
  if (proto.has_optimaltilingfeatures()) {
    original_struct.optimalTilingFeatures = static_cast<VkFormatFeatureFlags>(proto.optimaltilingfeatures());
  } else {
    original_struct.optimalTilingFeatures = VkFormatFeatureFlags{};
  }
  if (proto.has_bufferfeatures()) {
    original_struct.bufferFeatures = static_cast<VkFormatFeatureFlags>(proto.bufferfeatures());
  } else {
    original_struct.bufferFeatures = VkFormatFeatureFlags{};
  }
}
void FillStructFromProto(VkFramebufferCreateInfo& original_struct, const vvk::server::VkFramebufferCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkFramebufferCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkFramebufferCreateFlags{};
  }
  original_struct.renderPass = reinterpret_cast<VkRenderPass>(proto.renderpass());
  if (proto.has_attachmentcount()) {
    original_struct.attachmentCount = proto.attachmentcount();
  } else {
    original_struct.attachmentCount = uint32_t{};
  }
  original_struct.pAttachments = reinterpret_cast<const VkImageView*>(proto.pattachments().data());
  original_struct.width = proto.width();
  original_struct.height = proto.height();
  original_struct.layers = proto.layers();
}
void FillStructFromProto(VkGraphicsPipelineCreateInfo& original_struct, const vvk::server::VkGraphicsPipelineCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkPipelineCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkPipelineCreateFlags{};
  }
  if (proto.has_stagecount()) {
    original_struct.stageCount = proto.stagecount();
  } else {
    original_struct.stageCount = uint32_t{};
  }
  VkPipelineShaderStageCreateInfo* original_struct_pStages = new VkPipelineShaderStageCreateInfo[proto.pstages_size()]();
  original_struct.pStages = original_struct_pStages;
  if (proto.pstages_size()) {
    for (int pStages_indx = 0; pStages_indx < proto.pstages_size(); pStages_indx++) {
      VkPipelineShaderStageCreateInfo &original_struct_pStages_i = original_struct_pStages[pStages_indx];
      FillStructFromProto(original_struct_pStages_i, proto.pstages(pStages_indx));
    }
  } else {
    original_struct.pStages = nullptr;
  }
  if (proto.has_pvertexinputstate()) {
    VkPipelineVertexInputStateCreateInfo* original_struct_pVertexInputState = new VkPipelineVertexInputStateCreateInfo;
    FillStructFromProto(*original_struct_pVertexInputState, proto.pvertexinputstate());
    original_struct.pVertexInputState = original_struct_pVertexInputState;
  } else {
    original_struct.pVertexInputState = nullptr;
  }
  if (proto.has_pinputassemblystate()) {
    VkPipelineInputAssemblyStateCreateInfo* original_struct_pInputAssemblyState = new VkPipelineInputAssemblyStateCreateInfo;
    FillStructFromProto(*original_struct_pInputAssemblyState, proto.pinputassemblystate());
    original_struct.pInputAssemblyState = original_struct_pInputAssemblyState;
  } else {
    original_struct.pInputAssemblyState = nullptr;
  }
  if (proto.has_ptessellationstate()) {
    VkPipelineTessellationStateCreateInfo* original_struct_pTessellationState = new VkPipelineTessellationStateCreateInfo;
    FillStructFromProto(*original_struct_pTessellationState, proto.ptessellationstate());
    original_struct.pTessellationState = original_struct_pTessellationState;
  } else {
    original_struct.pTessellationState = nullptr;
  }
  if (proto.has_pviewportstate()) {
    VkPipelineViewportStateCreateInfo* original_struct_pViewportState = new VkPipelineViewportStateCreateInfo;
    FillStructFromProto(*original_struct_pViewportState, proto.pviewportstate());
    original_struct.pViewportState = original_struct_pViewportState;
  } else {
    original_struct.pViewportState = nullptr;
  }
  if (proto.has_prasterizationstate()) {
    VkPipelineRasterizationStateCreateInfo* original_struct_pRasterizationState = new VkPipelineRasterizationStateCreateInfo;
    FillStructFromProto(*original_struct_pRasterizationState, proto.prasterizationstate());
    original_struct.pRasterizationState = original_struct_pRasterizationState;
  } else {
    original_struct.pRasterizationState = nullptr;
  }
  if (proto.has_pmultisamplestate()) {
    VkPipelineMultisampleStateCreateInfo* original_struct_pMultisampleState = new VkPipelineMultisampleStateCreateInfo;
    FillStructFromProto(*original_struct_pMultisampleState, proto.pmultisamplestate());
    original_struct.pMultisampleState = original_struct_pMultisampleState;
  } else {
    original_struct.pMultisampleState = nullptr;
  }
  if (proto.has_pdepthstencilstate()) {
    VkPipelineDepthStencilStateCreateInfo* original_struct_pDepthStencilState = new VkPipelineDepthStencilStateCreateInfo;
    FillStructFromProto(*original_struct_pDepthStencilState, proto.pdepthstencilstate());
    original_struct.pDepthStencilState = original_struct_pDepthStencilState;
  } else {
    original_struct.pDepthStencilState = nullptr;
  }
  if (proto.has_pcolorblendstate()) {
    VkPipelineColorBlendStateCreateInfo* original_struct_pColorBlendState = new VkPipelineColorBlendStateCreateInfo;
    FillStructFromProto(*original_struct_pColorBlendState, proto.pcolorblendstate());
    original_struct.pColorBlendState = original_struct_pColorBlendState;
  } else {
    original_struct.pColorBlendState = nullptr;
  }
  if (proto.has_pdynamicstate()) {
    VkPipelineDynamicStateCreateInfo* original_struct_pDynamicState = new VkPipelineDynamicStateCreateInfo;
    FillStructFromProto(*original_struct_pDynamicState, proto.pdynamicstate());
    original_struct.pDynamicState = original_struct_pDynamicState;
  } else {
    original_struct.pDynamicState = nullptr;
  }
  if (proto.has_layout()) {
    original_struct.layout = reinterpret_cast<VkPipelineLayout>(proto.layout());
  } else {
    original_struct.layout = VkPipelineLayout{};
  }
  if (proto.has_renderpass()) {
    original_struct.renderPass = reinterpret_cast<VkRenderPass>(proto.renderpass());
  } else {
    original_struct.renderPass = VkRenderPass{};
  }
  original_struct.subpass = proto.subpass();
  if (proto.has_basepipelinehandle()) {
    original_struct.basePipelineHandle = reinterpret_cast<VkPipeline>(proto.basepipelinehandle());
  } else {
    original_struct.basePipelineHandle = VkPipeline{};
  }
  original_struct.basePipelineIndex = proto.basepipelineindex();
}
void FillStructFromProto(VkImageCreateInfo& original_struct, const vvk::server::VkImageCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkImageCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkImageCreateFlags{};
  }
  original_struct.imageType = static_cast<VkImageType>(proto.imagetype());
  original_struct.format = static_cast<VkFormat>(proto.format());
  VkExtent3D &original_struct_extent = original_struct.extent;
  FillStructFromProto(original_struct_extent, proto.extent());
  original_struct.mipLevels = proto.miplevels();
  original_struct.arrayLayers = proto.arraylayers();
  original_struct.samples = static_cast<VkSampleCountFlagBits>(proto.samples());
  original_struct.tiling = static_cast<VkImageTiling>(proto.tiling());
  original_struct.usage = static_cast<VkImageUsageFlags>(proto.usage());
  original_struct.sharingMode = static_cast<VkSharingMode>(proto.sharingmode());
  if (proto.has_queuefamilyindexcount()) {
    original_struct.queueFamilyIndexCount = proto.queuefamilyindexcount();
  } else {
    original_struct.queueFamilyIndexCount = uint32_t{};
  }
  uint32_t* original_struct_pQueueFamilyIndices = new uint32_t[proto.pqueuefamilyindices_size()]();
  original_struct.pQueueFamilyIndices = original_struct_pQueueFamilyIndices;
  for (int pQueueFamilyIndices_indx = 0; pQueueFamilyIndices_indx < proto.pqueuefamilyindices_size(); pQueueFamilyIndices_indx++) {
    original_struct_pQueueFamilyIndices[pQueueFamilyIndices_indx] = proto.pqueuefamilyindices(pQueueFamilyIndices_indx);
  }
  original_struct.initialLayout = static_cast<VkImageLayout>(proto.initiallayout());
}
void FillStructFromProto(VkImageMemoryBarrier& original_struct, const vvk::server::VkImageMemoryBarrier& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  original_struct.pNext = nullptr;  // Empty pNext chain
  original_struct.srcAccessMask = static_cast<VkAccessFlags>(proto.srcaccessmask());
  original_struct.dstAccessMask = static_cast<VkAccessFlags>(proto.dstaccessmask());
  original_struct.oldLayout = static_cast<VkImageLayout>(proto.oldlayout());
  original_struct.newLayout = static_cast<VkImageLayout>(proto.newlayout());
  original_struct.srcQueueFamilyIndex = proto.srcqueuefamilyindex();
  original_struct.dstQueueFamilyIndex = proto.dstqueuefamilyindex();
  original_struct.image = reinterpret_cast<VkImage>(proto.image());
  VkImageSubresourceRange &original_struct_subresourceRange = original_struct.subresourceRange;
  FillStructFromProto(original_struct_subresourceRange, proto.subresourcerange());
}
void FillStructFromProto(VkImageMemoryRequirementsInfo2& original_struct, const vvk::server::VkImageMemoryRequirementsInfo2& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2;
  original_struct.pNext = nullptr;  // Empty pNext chain
  original_struct.image = reinterpret_cast<VkImage>(proto.image());
}
void FillStructFromProto(VkImageSubresource& original_struct, const vvk::server::VkImageSubresource& proto) {
  original_struct.aspectMask = static_cast<VkImageAspectFlags>(proto.aspectmask());
  original_struct.mipLevel = proto.miplevel();
  original_struct.arrayLayer = proto.arraylayer();
}
void FillStructFromProto(VkImageSubresourceLayers& original_struct, const vvk::server::VkImageSubresourceLayers& proto) {
  original_struct.aspectMask = static_cast<VkImageAspectFlags>(proto.aspectmask());
  original_struct.mipLevel = proto.miplevel();
  original_struct.baseArrayLayer = proto.basearraylayer();
  original_struct.layerCount = proto.layercount();
}
void FillStructFromProto(VkImageSubresourceRange& original_struct, const vvk::server::VkImageSubresourceRange& proto) {
  original_struct.aspectMask = static_cast<VkImageAspectFlags>(proto.aspectmask());
  original_struct.baseMipLevel = proto.basemiplevel();
  original_struct.levelCount = proto.levelcount();
  original_struct.baseArrayLayer = proto.basearraylayer();
  original_struct.layerCount = proto.layercount();
}
void FillStructFromProto(VkImageViewCreateInfo& original_struct, const vvk::server::VkImageViewCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkImageViewCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkImageViewCreateFlags{};
  }
  original_struct.image = reinterpret_cast<VkImage>(proto.image());
  original_struct.viewType = static_cast<VkImageViewType>(proto.viewtype());
  original_struct.format = static_cast<VkFormat>(proto.format());
  VkComponentMapping &original_struct_components = original_struct.components;
  FillStructFromProto(original_struct_components, proto.components());
  VkImageSubresourceRange &original_struct_subresourceRange = original_struct.subresourceRange;
  FillStructFromProto(original_struct_subresourceRange, proto.subresourcerange());
}
void FillStructFromProto(VkInstanceCreateInfo& original_struct, const vvk::server::VkInstanceCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkInstanceCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkInstanceCreateFlags{};
  }
  if (proto.has_papplicationinfo()) {
    VkApplicationInfo* original_struct_pApplicationInfo = new VkApplicationInfo;
    FillStructFromProto(*original_struct_pApplicationInfo, proto.papplicationinfo());
    original_struct.pApplicationInfo = original_struct_pApplicationInfo;
  } else {
    original_struct.pApplicationInfo = nullptr;
  }
  if (proto.has_enabledlayercount()) {
    original_struct.enabledLayerCount = proto.enabledlayercount();
  } else {
    original_struct.enabledLayerCount = uint32_t{};
  }
  const char** original_struct_ppEnabledLayerNames = new const char*[proto.ppenabledlayernames_size()]();
  original_struct.ppEnabledLayerNames = original_struct_ppEnabledLayerNames;
  for (int ppEnabledLayerNames_indx = 0; ppEnabledLayerNames_indx < proto.ppenabledlayernames_size(); ppEnabledLayerNames_indx++) {
    original_struct_ppEnabledLayerNames[ppEnabledLayerNames_indx] = proto.ppenabledlayernames(ppEnabledLayerNames_indx).data();
  }
  if (proto.has_enabledextensioncount()) {
    original_struct.enabledExtensionCount = proto.enabledextensioncount();
  } else {
    original_struct.enabledExtensionCount = uint32_t{};
  }
  const char** original_struct_ppEnabledExtensionNames = new const char*[proto.ppenabledextensionnames_size()]();
  original_struct.ppEnabledExtensionNames = original_struct_ppEnabledExtensionNames;
  for (int ppEnabledExtensionNames_indx = 0; ppEnabledExtensionNames_indx < proto.ppenabledextensionnames_size(); ppEnabledExtensionNames_indx++) {
    original_struct_ppEnabledExtensionNames[ppEnabledExtensionNames_indx] = proto.ppenabledextensionnames(ppEnabledExtensionNames_indx).data();
  }
}
void FillStructFromProto(VkMappedMemoryRange& original_struct, const vvk::server::VkMappedMemoryRange& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
  original_struct.pNext = nullptr;  // Empty pNext chain
  original_struct.memory = reinterpret_cast<VkDeviceMemory>(proto.memory());
  original_struct.offset = static_cast<VkDeviceSize>(proto.offset());
  original_struct.size = static_cast<VkDeviceSize>(proto.size());
}
void FillStructFromProto(VkMemoryAllocateInfo& original_struct, const vvk::server::VkMemoryAllocateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  original_struct.allocationSize = static_cast<VkDeviceSize>(proto.allocationsize());
  original_struct.memoryTypeIndex = proto.memorytypeindex();
}
void FillStructFromProto(VkMemoryBarrier& original_struct, const vvk::server::VkMemoryBarrier& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_srcaccessmask()) {
    original_struct.srcAccessMask = static_cast<VkAccessFlags>(proto.srcaccessmask());
  } else {
    original_struct.srcAccessMask = VkAccessFlags{};
  }
  if (proto.has_dstaccessmask()) {
    original_struct.dstAccessMask = static_cast<VkAccessFlags>(proto.dstaccessmask());
  } else {
    original_struct.dstAccessMask = VkAccessFlags{};
  }
}
void FillStructFromProto(VkMemoryHeap& original_struct, const vvk::server::VkMemoryHeap& proto) {
  original_struct.size = static_cast<VkDeviceSize>(proto.size());
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkMemoryHeapFlags>(proto.flags());
  } else {
    original_struct.flags = VkMemoryHeapFlags{};
  }
}
void FillStructFromProto(VkMemoryRequirements& original_struct, const vvk::server::VkMemoryRequirements& proto) {
  original_struct.size = static_cast<VkDeviceSize>(proto.size());
  original_struct.alignment = static_cast<VkDeviceSize>(proto.alignment());
  original_struct.memoryTypeBits = proto.memorytypebits();
}
void FillStructFromProto(VkMemoryRequirements2& original_struct, const vvk::server::VkMemoryRequirements2& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
  original_struct.pNext = nullptr;  // Empty pNext chain
  VkMemoryRequirements &original_struct_memoryRequirements = original_struct.memoryRequirements;
  FillStructFromProto(original_struct_memoryRequirements, proto.memoryrequirements());
}
void FillStructFromProto(VkMemoryType& original_struct, const vvk::server::VkMemoryType& proto) {
  if (proto.has_propertyflags()) {
    original_struct.propertyFlags = static_cast<VkMemoryPropertyFlags>(proto.propertyflags());
  } else {
    original_struct.propertyFlags = VkMemoryPropertyFlags{};
  }
  original_struct.heapIndex = proto.heapindex();
}
void FillStructFromProto(VkOffset2D& original_struct, const vvk::server::VkOffset2D& proto) {
  original_struct.x = proto.x();
  original_struct.y = proto.y();
}
void FillStructFromProto(VkOffset3D& original_struct, const vvk::server::VkOffset3D& proto) {
  original_struct.x = proto.x();
  original_struct.y = proto.y();
  original_struct.z = proto.z();
}
void FillStructFromProto(VkPhysicalDeviceFeatures& original_struct, const vvk::server::VkPhysicalDeviceFeatures& proto) {
  original_struct.robustBufferAccess = proto.robustbufferaccess();
  original_struct.fullDrawIndexUint32 = proto.fulldrawindexuint32();
  original_struct.imageCubeArray = proto.imagecubearray();
  original_struct.independentBlend = proto.independentblend();
  original_struct.geometryShader = proto.geometryshader();
  original_struct.tessellationShader = proto.tessellationshader();
  original_struct.sampleRateShading = proto.samplerateshading();
  original_struct.dualSrcBlend = proto.dualsrcblend();
  original_struct.logicOp = proto.logicop();
  original_struct.multiDrawIndirect = proto.multidrawindirect();
  original_struct.drawIndirectFirstInstance = proto.drawindirectfirstinstance();
  original_struct.depthClamp = proto.depthclamp();
  original_struct.depthBiasClamp = proto.depthbiasclamp();
  original_struct.fillModeNonSolid = proto.fillmodenonsolid();
  original_struct.depthBounds = proto.depthbounds();
  original_struct.wideLines = proto.widelines();
  original_struct.largePoints = proto.largepoints();
  original_struct.alphaToOne = proto.alphatoone();
  original_struct.multiViewport = proto.multiviewport();
  original_struct.samplerAnisotropy = proto.sampleranisotropy();
  original_struct.textureCompressionETC2 = proto.texturecompressionetc2();
  original_struct.textureCompressionASTC_LDR = proto.texturecompressionastc_ldr();
  original_struct.textureCompressionBC = proto.texturecompressionbc();
  original_struct.occlusionQueryPrecise = proto.occlusionqueryprecise();
  original_struct.pipelineStatisticsQuery = proto.pipelinestatisticsquery();
  original_struct.vertexPipelineStoresAndAtomics = proto.vertexpipelinestoresandatomics();
  original_struct.fragmentStoresAndAtomics = proto.fragmentstoresandatomics();
  original_struct.shaderTessellationAndGeometryPointSize = proto.shadertessellationandgeometrypointsize();
  original_struct.shaderImageGatherExtended = proto.shaderimagegatherextended();
  original_struct.shaderStorageImageExtendedFormats = proto.shaderstorageimageextendedformats();
  original_struct.shaderStorageImageMultisample = proto.shaderstorageimagemultisample();
  original_struct.shaderStorageImageReadWithoutFormat = proto.shaderstorageimagereadwithoutformat();
  original_struct.shaderStorageImageWriteWithoutFormat = proto.shaderstorageimagewritewithoutformat();
  original_struct.shaderUniformBufferArrayDynamicIndexing = proto.shaderuniformbufferarraydynamicindexing();
  original_struct.shaderSampledImageArrayDynamicIndexing = proto.shadersampledimagearraydynamicindexing();
  original_struct.shaderStorageBufferArrayDynamicIndexing = proto.shaderstoragebufferarraydynamicindexing();
  original_struct.shaderStorageImageArrayDynamicIndexing = proto.shaderstorageimagearraydynamicindexing();
  original_struct.shaderClipDistance = proto.shaderclipdistance();
  original_struct.shaderCullDistance = proto.shaderculldistance();
  original_struct.shaderFloat64 = proto.shaderfloat64();
  original_struct.shaderInt64 = proto.shaderint64();
  original_struct.shaderInt16 = proto.shaderint16();
  original_struct.shaderResourceResidency = proto.shaderresourceresidency();
  original_struct.shaderResourceMinLod = proto.shaderresourceminlod();
  original_struct.sparseBinding = proto.sparsebinding();
  original_struct.sparseResidencyBuffer = proto.sparseresidencybuffer();
  original_struct.sparseResidencyImage2D = proto.sparseresidencyimage2d();
  original_struct.sparseResidencyImage3D = proto.sparseresidencyimage3d();
  original_struct.sparseResidency2Samples = proto.sparseresidency2samples();
  original_struct.sparseResidency4Samples = proto.sparseresidency4samples();
  original_struct.sparseResidency8Samples = proto.sparseresidency8samples();
  original_struct.sparseResidency16Samples = proto.sparseresidency16samples();
  original_struct.sparseResidencyAliased = proto.sparseresidencyaliased();
  original_struct.variableMultisampleRate = proto.variablemultisamplerate();
  original_struct.inheritedQueries = proto.inheritedqueries();
}
void FillStructFromProto(VkPhysicalDeviceFeatures2& original_struct, const vvk::server::VkPhysicalDeviceFeatures2& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
  VkBaseOutStructure* base = reinterpret_cast<VkBaseOutStructure*>(&original_struct);
  for (const auto& pnext : proto.pnext()) {
    if (pnext.has_vkphysicaldeviceprotectedmemoryfeatures_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceProtectedMemoryFeatures);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceProtectedMemoryFeatures*>(base->pNext), pnext.vkphysicaldeviceprotectedmemoryfeatures_chain_elem());
    }
    if (pnext.has_vkphysicaldeviceshaderdrawparametersfeatures_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceShaderDrawParametersFeatures);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceShaderDrawParametersFeatures*>(base->pNext), pnext.vkphysicaldeviceshaderdrawparametersfeatures_chain_elem());
    }
    if (pnext.has_vkphysicaldevicetimelinesemaphorefeatures_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceTimelineSemaphoreFeatures);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceTimelineSemaphoreFeatures*>(base->pNext), pnext.vkphysicaldevicetimelinesemaphorefeatures_chain_elem());
    }
    if (pnext.has_vkphysicaldevicevulkan11features_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceVulkan11Features);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceVulkan11Features*>(base->pNext), pnext.vkphysicaldevicevulkan11features_chain_elem());
    }
    if (pnext.has_vkphysicaldevicevulkan12features_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceVulkan12Features);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceVulkan12Features*>(base->pNext), pnext.vkphysicaldevicevulkan12features_chain_elem());
    }
    if (pnext.has_vkphysicaldevicevulkan13features_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceVulkan13Features);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceVulkan13Features*>(base->pNext), pnext.vkphysicaldevicevulkan13features_chain_elem());
    }
    if (pnext.has_vkphysicaldevicevulkan14features_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceVulkan14Features);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceVulkan14Features*>(base->pNext), pnext.vkphysicaldevicevulkan14features_chain_elem());
    }
    base = base->pNext;
  }
  base->pNext = nullptr;
  VkPhysicalDeviceFeatures &original_struct_features = original_struct.features;
  FillStructFromProto(original_struct_features, proto.features());
}
void FillStructFromProto(VkPhysicalDeviceLimits& original_struct, const vvk::server::VkPhysicalDeviceLimits& proto) {
  original_struct.maxImageDimension1D = proto.maximagedimension1d();
  original_struct.maxImageDimension2D = proto.maximagedimension2d();
  original_struct.maxImageDimension3D = proto.maximagedimension3d();
  original_struct.maxImageDimensionCube = proto.maximagedimensioncube();
  original_struct.maxImageArrayLayers = proto.maximagearraylayers();
  original_struct.maxTexelBufferElements = proto.maxtexelbufferelements();
  original_struct.maxUniformBufferRange = proto.maxuniformbufferrange();
  original_struct.maxStorageBufferRange = proto.maxstoragebufferrange();
  original_struct.maxPushConstantsSize = proto.maxpushconstantssize();
  original_struct.maxMemoryAllocationCount = proto.maxmemoryallocationcount();
  original_struct.maxSamplerAllocationCount = proto.maxsamplerallocationcount();
  original_struct.bufferImageGranularity = static_cast<VkDeviceSize>(proto.bufferimagegranularity());
  original_struct.sparseAddressSpaceSize = static_cast<VkDeviceSize>(proto.sparseaddressspacesize());
  original_struct.maxBoundDescriptorSets = proto.maxbounddescriptorsets();
  original_struct.maxPerStageDescriptorSamplers = proto.maxperstagedescriptorsamplers();
  original_struct.maxPerStageDescriptorUniformBuffers = proto.maxperstagedescriptoruniformbuffers();
  original_struct.maxPerStageDescriptorStorageBuffers = proto.maxperstagedescriptorstoragebuffers();
  original_struct.maxPerStageDescriptorSampledImages = proto.maxperstagedescriptorsampledimages();
  original_struct.maxPerStageDescriptorStorageImages = proto.maxperstagedescriptorstorageimages();
  original_struct.maxPerStageDescriptorInputAttachments = proto.maxperstagedescriptorinputattachments();
  original_struct.maxPerStageResources = proto.maxperstageresources();
  original_struct.maxDescriptorSetSamplers = proto.maxdescriptorsetsamplers();
  original_struct.maxDescriptorSetUniformBuffers = proto.maxdescriptorsetuniformbuffers();
  original_struct.maxDescriptorSetUniformBuffersDynamic = proto.maxdescriptorsetuniformbuffersdynamic();
  original_struct.maxDescriptorSetStorageBuffers = proto.maxdescriptorsetstoragebuffers();
  original_struct.maxDescriptorSetStorageBuffersDynamic = proto.maxdescriptorsetstoragebuffersdynamic();
  original_struct.maxDescriptorSetSampledImages = proto.maxdescriptorsetsampledimages();
  original_struct.maxDescriptorSetStorageImages = proto.maxdescriptorsetstorageimages();
  original_struct.maxDescriptorSetInputAttachments = proto.maxdescriptorsetinputattachments();
  original_struct.maxVertexInputAttributes = proto.maxvertexinputattributes();
  original_struct.maxVertexInputBindings = proto.maxvertexinputbindings();
  original_struct.maxVertexInputAttributeOffset = proto.maxvertexinputattributeoffset();
  original_struct.maxVertexInputBindingStride = proto.maxvertexinputbindingstride();
  original_struct.maxVertexOutputComponents = proto.maxvertexoutputcomponents();
  original_struct.maxTessellationGenerationLevel = proto.maxtessellationgenerationlevel();
  original_struct.maxTessellationPatchSize = proto.maxtessellationpatchsize();
  original_struct.maxTessellationControlPerVertexInputComponents = proto.maxtessellationcontrolpervertexinputcomponents();
  original_struct.maxTessellationControlPerVertexOutputComponents = proto.maxtessellationcontrolpervertexoutputcomponents();
  original_struct.maxTessellationControlPerPatchOutputComponents = proto.maxtessellationcontrolperpatchoutputcomponents();
  original_struct.maxTessellationControlTotalOutputComponents = proto.maxtessellationcontroltotaloutputcomponents();
  original_struct.maxTessellationEvaluationInputComponents = proto.maxtessellationevaluationinputcomponents();
  original_struct.maxTessellationEvaluationOutputComponents = proto.maxtessellationevaluationoutputcomponents();
  original_struct.maxGeometryShaderInvocations = proto.maxgeometryshaderinvocations();
  original_struct.maxGeometryInputComponents = proto.maxgeometryinputcomponents();
  original_struct.maxGeometryOutputComponents = proto.maxgeometryoutputcomponents();
  original_struct.maxGeometryOutputVertices = proto.maxgeometryoutputvertices();
  original_struct.maxGeometryTotalOutputComponents = proto.maxgeometrytotaloutputcomponents();
  original_struct.maxFragmentInputComponents = proto.maxfragmentinputcomponents();
  original_struct.maxFragmentOutputAttachments = proto.maxfragmentoutputattachments();
  original_struct.maxFragmentDualSrcAttachments = proto.maxfragmentdualsrcattachments();
  original_struct.maxFragmentCombinedOutputResources = proto.maxfragmentcombinedoutputresources();
  original_struct.maxComputeSharedMemorySize = proto.maxcomputesharedmemorysize();
  const size_t original_struct_maxComputeWorkGroupCount_length = std::min(3, 3);
  for (uint32_t maxComputeWorkGroupCount_indx = 0; maxComputeWorkGroupCount_indx < original_struct_maxComputeWorkGroupCount_length; maxComputeWorkGroupCount_indx++) {
    original_struct.maxComputeWorkGroupCount[maxComputeWorkGroupCount_indx] = proto.maxcomputeworkgroupcount(maxComputeWorkGroupCount_indx);
  }
  original_struct.maxComputeWorkGroupInvocations = proto.maxcomputeworkgroupinvocations();
  const size_t original_struct_maxComputeWorkGroupSize_length = std::min(3, 3);
  for (uint32_t maxComputeWorkGroupSize_indx = 0; maxComputeWorkGroupSize_indx < original_struct_maxComputeWorkGroupSize_length; maxComputeWorkGroupSize_indx++) {
    original_struct.maxComputeWorkGroupSize[maxComputeWorkGroupSize_indx] = proto.maxcomputeworkgroupsize(maxComputeWorkGroupSize_indx);
  }
  original_struct.subPixelPrecisionBits = proto.subpixelprecisionbits();
  original_struct.subTexelPrecisionBits = proto.subtexelprecisionbits();
  original_struct.mipmapPrecisionBits = proto.mipmapprecisionbits();
  original_struct.maxDrawIndexedIndexValue = proto.maxdrawindexedindexvalue();
  original_struct.maxDrawIndirectCount = proto.maxdrawindirectcount();
  original_struct.maxSamplerLodBias = proto.maxsamplerlodbias();
  original_struct.maxSamplerAnisotropy = proto.maxsampleranisotropy();
  original_struct.maxViewports = proto.maxviewports();
  const size_t original_struct_maxViewportDimensions_length = std::min(2, 2);
  for (uint32_t maxViewportDimensions_indx = 0; maxViewportDimensions_indx < original_struct_maxViewportDimensions_length; maxViewportDimensions_indx++) {
    original_struct.maxViewportDimensions[maxViewportDimensions_indx] = proto.maxviewportdimensions(maxViewportDimensions_indx);
  }
  const size_t original_struct_viewportBoundsRange_length = std::min(2, 2);
  for (uint32_t viewportBoundsRange_indx = 0; viewportBoundsRange_indx < original_struct_viewportBoundsRange_length; viewportBoundsRange_indx++) {
    original_struct.viewportBoundsRange[viewportBoundsRange_indx] = proto.viewportboundsrange(viewportBoundsRange_indx);
  }
  original_struct.viewportSubPixelBits = proto.viewportsubpixelbits();
  original_struct.minMemoryMapAlignment = proto.minmemorymapalignment();
  original_struct.minTexelBufferOffsetAlignment = static_cast<VkDeviceSize>(proto.mintexelbufferoffsetalignment());
  original_struct.minUniformBufferOffsetAlignment = static_cast<VkDeviceSize>(proto.minuniformbufferoffsetalignment());
  original_struct.minStorageBufferOffsetAlignment = static_cast<VkDeviceSize>(proto.minstoragebufferoffsetalignment());
  original_struct.minTexelOffset = proto.mintexeloffset();
  original_struct.maxTexelOffset = proto.maxtexeloffset();
  original_struct.minTexelGatherOffset = proto.mintexelgatheroffset();
  original_struct.maxTexelGatherOffset = proto.maxtexelgatheroffset();
  original_struct.minInterpolationOffset = proto.mininterpolationoffset();
  original_struct.maxInterpolationOffset = proto.maxinterpolationoffset();
  original_struct.subPixelInterpolationOffsetBits = proto.subpixelinterpolationoffsetbits();
  original_struct.maxFramebufferWidth = proto.maxframebufferwidth();
  original_struct.maxFramebufferHeight = proto.maxframebufferheight();
  original_struct.maxFramebufferLayers = proto.maxframebufferlayers();
  if (proto.has_framebuffercolorsamplecounts()) {
    original_struct.framebufferColorSampleCounts = static_cast<VkSampleCountFlags>(proto.framebuffercolorsamplecounts());
  } else {
    original_struct.framebufferColorSampleCounts = VkSampleCountFlags{};
  }
  if (proto.has_framebufferdepthsamplecounts()) {
    original_struct.framebufferDepthSampleCounts = static_cast<VkSampleCountFlags>(proto.framebufferdepthsamplecounts());
  } else {
    original_struct.framebufferDepthSampleCounts = VkSampleCountFlags{};
  }
  if (proto.has_framebufferstencilsamplecounts()) {
    original_struct.framebufferStencilSampleCounts = static_cast<VkSampleCountFlags>(proto.framebufferstencilsamplecounts());
  } else {
    original_struct.framebufferStencilSampleCounts = VkSampleCountFlags{};
  }
  if (proto.has_framebuffernoattachmentssamplecounts()) {
    original_struct.framebufferNoAttachmentsSampleCounts = static_cast<VkSampleCountFlags>(proto.framebuffernoattachmentssamplecounts());
  } else {
    original_struct.framebufferNoAttachmentsSampleCounts = VkSampleCountFlags{};
  }
  original_struct.maxColorAttachments = proto.maxcolorattachments();
  if (proto.has_sampledimagecolorsamplecounts()) {
    original_struct.sampledImageColorSampleCounts = static_cast<VkSampleCountFlags>(proto.sampledimagecolorsamplecounts());
  } else {
    original_struct.sampledImageColorSampleCounts = VkSampleCountFlags{};
  }
  if (proto.has_sampledimageintegersamplecounts()) {
    original_struct.sampledImageIntegerSampleCounts = static_cast<VkSampleCountFlags>(proto.sampledimageintegersamplecounts());
  } else {
    original_struct.sampledImageIntegerSampleCounts = VkSampleCountFlags{};
  }
  if (proto.has_sampledimagedepthsamplecounts()) {
    original_struct.sampledImageDepthSampleCounts = static_cast<VkSampleCountFlags>(proto.sampledimagedepthsamplecounts());
  } else {
    original_struct.sampledImageDepthSampleCounts = VkSampleCountFlags{};
  }
  if (proto.has_sampledimagestencilsamplecounts()) {
    original_struct.sampledImageStencilSampleCounts = static_cast<VkSampleCountFlags>(proto.sampledimagestencilsamplecounts());
  } else {
    original_struct.sampledImageStencilSampleCounts = VkSampleCountFlags{};
  }
  if (proto.has_storageimagesamplecounts()) {
    original_struct.storageImageSampleCounts = static_cast<VkSampleCountFlags>(proto.storageimagesamplecounts());
  } else {
    original_struct.storageImageSampleCounts = VkSampleCountFlags{};
  }
  original_struct.maxSampleMaskWords = proto.maxsamplemaskwords();
  original_struct.timestampComputeAndGraphics = proto.timestampcomputeandgraphics();
  original_struct.timestampPeriod = proto.timestampperiod();
  original_struct.maxClipDistances = proto.maxclipdistances();
  original_struct.maxCullDistances = proto.maxculldistances();
  original_struct.maxCombinedClipAndCullDistances = proto.maxcombinedclipandculldistances();
  original_struct.discreteQueuePriorities = proto.discretequeuepriorities();
  const size_t original_struct_pointSizeRange_length = std::min(2, 2);
  for (uint32_t pointSizeRange_indx = 0; pointSizeRange_indx < original_struct_pointSizeRange_length; pointSizeRange_indx++) {
    original_struct.pointSizeRange[pointSizeRange_indx] = proto.pointsizerange(pointSizeRange_indx);
  }
  const size_t original_struct_lineWidthRange_length = std::min(2, 2);
  for (uint32_t lineWidthRange_indx = 0; lineWidthRange_indx < original_struct_lineWidthRange_length; lineWidthRange_indx++) {
    original_struct.lineWidthRange[lineWidthRange_indx] = proto.linewidthrange(lineWidthRange_indx);
  }
  original_struct.pointSizeGranularity = proto.pointsizegranularity();
  original_struct.lineWidthGranularity = proto.linewidthgranularity();
  original_struct.strictLines = proto.strictlines();
  original_struct.standardSampleLocations = proto.standardsamplelocations();
  original_struct.optimalBufferCopyOffsetAlignment = static_cast<VkDeviceSize>(proto.optimalbuffercopyoffsetalignment());
  original_struct.optimalBufferCopyRowPitchAlignment = static_cast<VkDeviceSize>(proto.optimalbuffercopyrowpitchalignment());
  original_struct.nonCoherentAtomSize = static_cast<VkDeviceSize>(proto.noncoherentatomsize());
}
void FillStructFromProto(VkPhysicalDeviceMemoryProperties& original_struct, const vvk::server::VkPhysicalDeviceMemoryProperties& proto) {
  original_struct.memoryTypeCount = proto.memorytypecount();
  for (int memoryTypes_indx = 0; memoryTypes_indx < proto.memorytypes_size(); memoryTypes_indx++) {
    FillStructFromProto(original_struct.memoryTypes[memoryTypes_indx], proto.memorytypes(memoryTypes_indx));
  }
  original_struct.memoryHeapCount = proto.memoryheapcount();
  for (int memoryHeaps_indx = 0; memoryHeaps_indx < proto.memoryheaps_size(); memoryHeaps_indx++) {
    FillStructFromProto(original_struct.memoryHeaps[memoryHeaps_indx], proto.memoryheaps(memoryHeaps_indx));
  }
}
void FillStructFromProto(VkPhysicalDeviceProperties& original_struct, const vvk::server::VkPhysicalDeviceProperties& proto) {
  original_struct.apiVersion = proto.apiversion();
  original_struct.driverVersion = proto.driverversion();
  original_struct.vendorID = proto.vendorid();
  original_struct.deviceID = proto.deviceid();
  original_struct.deviceType = static_cast<VkPhysicalDeviceType>(proto.devicetype());
  strncpy(original_struct.deviceName, proto.devicename().c_str(), VK_MAX_PHYSICAL_DEVICE_NAME_SIZE);
  const size_t original_struct_pipelineCacheUUID_length = std::min(VK_UUID_SIZE, VK_UUID_SIZE);
  for (uint32_t pipelineCacheUUID_indx = 0; pipelineCacheUUID_indx < original_struct_pipelineCacheUUID_length; pipelineCacheUUID_indx++) {
    original_struct.pipelineCacheUUID[pipelineCacheUUID_indx] = static_cast<uint8_t>(proto.pipelinecacheuuid(pipelineCacheUUID_indx));
  }
  VkPhysicalDeviceLimits &original_struct_limits = original_struct.limits;
  FillStructFromProto(original_struct_limits, proto.limits());
  VkPhysicalDeviceSparseProperties &original_struct_sparseProperties = original_struct.sparseProperties;
  FillStructFromProto(original_struct_sparseProperties, proto.sparseproperties());
}
void FillStructFromProto(VkPhysicalDeviceProperties2& original_struct, const vvk::server::VkPhysicalDeviceProperties2& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
  VkBaseOutStructure* base = reinterpret_cast<VkBaseOutStructure*>(&original_struct);
  for (const auto& pnext : proto.pnext()) {
    if (pnext.has_vkphysicaldeviceprotectedmemoryproperties_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceProtectedMemoryProperties);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceProtectedMemoryProperties*>(base->pNext), pnext.vkphysicaldeviceprotectedmemoryproperties_chain_elem());
    }
    if (pnext.has_vkphysicaldevicesubgroupproperties_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceSubgroupProperties);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceSubgroupProperties*>(base->pNext), pnext.vkphysicaldevicesubgroupproperties_chain_elem());
    }
    if (pnext.has_vkphysicaldevicetimelinesemaphoreproperties_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceTimelineSemaphoreProperties);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceTimelineSemaphoreProperties*>(base->pNext), pnext.vkphysicaldevicetimelinesemaphoreproperties_chain_elem());
    }
    if (pnext.has_vkphysicaldevicevulkan11properties_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceVulkan11Properties);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceVulkan11Properties*>(base->pNext), pnext.vkphysicaldevicevulkan11properties_chain_elem());
    }
    if (pnext.has_vkphysicaldevicevulkan12properties_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceVulkan12Properties);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceVulkan12Properties*>(base->pNext), pnext.vkphysicaldevicevulkan12properties_chain_elem());
    }
    if (pnext.has_vkphysicaldevicevulkan13properties_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceVulkan13Properties);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceVulkan13Properties*>(base->pNext), pnext.vkphysicaldevicevulkan13properties_chain_elem());
    }
    if (pnext.has_vkphysicaldevicevulkan14properties_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkPhysicalDeviceVulkan14Properties);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceVulkan14Properties*>(base->pNext), pnext.vkphysicaldevicevulkan14properties_chain_elem());
    }
    base = base->pNext;
  }
  base->pNext = nullptr;
  VkPhysicalDeviceProperties &original_struct_properties = original_struct.properties;
  FillStructFromProto(original_struct_properties, proto.properties());
}
void FillStructFromProto(VkPhysicalDeviceSparseProperties& original_struct, const vvk::server::VkPhysicalDeviceSparseProperties& proto) {
  original_struct.residencyStandard2DBlockShape = proto.residencystandard2dblockshape();
  original_struct.residencyStandard2DMultisampleBlockShape = proto.residencystandard2dmultisampleblockshape();
  original_struct.residencyStandard3DBlockShape = proto.residencystandard3dblockshape();
  original_struct.residencyAlignedMipSize = proto.residencyalignedmipsize();
  original_struct.residencyNonResidentStrict = proto.residencynonresidentstrict();
}
void FillStructFromProto(VkPipelineCacheCreateInfo& original_struct, const vvk::server::VkPipelineCacheCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkPipelineCacheCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkPipelineCacheCreateFlags{};
  }
  if (proto.has_initialdatasize()) {
    original_struct.initialDataSize = proto.initialdatasize();
  } else {
    original_struct.initialDataSize = size_t{};
  }
  original_struct.pInitialData = proto.pinitialdata().data();
}
void FillStructFromProto(VkPipelineColorBlendAttachmentState& original_struct, const vvk::server::VkPipelineColorBlendAttachmentState& proto) {
  original_struct.blendEnable = proto.blendenable();
  original_struct.srcColorBlendFactor = static_cast<VkBlendFactor>(proto.srccolorblendfactor());
  original_struct.dstColorBlendFactor = static_cast<VkBlendFactor>(proto.dstcolorblendfactor());
  original_struct.colorBlendOp = static_cast<VkBlendOp>(proto.colorblendop());
  original_struct.srcAlphaBlendFactor = static_cast<VkBlendFactor>(proto.srcalphablendfactor());
  original_struct.dstAlphaBlendFactor = static_cast<VkBlendFactor>(proto.dstalphablendfactor());
  original_struct.alphaBlendOp = static_cast<VkBlendOp>(proto.alphablendop());
  if (proto.has_colorwritemask()) {
    original_struct.colorWriteMask = static_cast<VkColorComponentFlags>(proto.colorwritemask());
  } else {
    original_struct.colorWriteMask = VkColorComponentFlags{};
  }
}
void FillStructFromProto(VkPipelineColorBlendStateCreateInfo& original_struct, const vvk::server::VkPipelineColorBlendStateCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkPipelineColorBlendStateCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkPipelineColorBlendStateCreateFlags{};
  }
  original_struct.logicOpEnable = proto.logicopenable();
  original_struct.logicOp = static_cast<VkLogicOp>(proto.logicop());
  if (proto.has_attachmentcount()) {
    original_struct.attachmentCount = proto.attachmentcount();
  } else {
    original_struct.attachmentCount = uint32_t{};
  }
  VkPipelineColorBlendAttachmentState* original_struct_pAttachments = new VkPipelineColorBlendAttachmentState[proto.pattachments_size()]();
  original_struct.pAttachments = original_struct_pAttachments;
  if (proto.pattachments_size()) {
    for (int pAttachments_indx = 0; pAttachments_indx < proto.pattachments_size(); pAttachments_indx++) {
      VkPipelineColorBlendAttachmentState &original_struct_pAttachments_i = original_struct_pAttachments[pAttachments_indx];
      FillStructFromProto(original_struct_pAttachments_i, proto.pattachments(pAttachments_indx));
    }
  } else {
    original_struct.pAttachments = nullptr;
  }
  const size_t original_struct_blendConstants_length = std::min(4, 4);
  for (uint32_t blendConstants_indx = 0; blendConstants_indx < original_struct_blendConstants_length; blendConstants_indx++) {
    original_struct.blendConstants[blendConstants_indx] = proto.blendconstants(blendConstants_indx);
  }
}
void FillStructFromProto(VkPipelineDepthStencilStateCreateInfo& original_struct, const vvk::server::VkPipelineDepthStencilStateCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkPipelineDepthStencilStateCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkPipelineDepthStencilStateCreateFlags{};
  }
  original_struct.depthTestEnable = proto.depthtestenable();
  original_struct.depthWriteEnable = proto.depthwriteenable();
  original_struct.depthCompareOp = static_cast<VkCompareOp>(proto.depthcompareop());
  original_struct.depthBoundsTestEnable = proto.depthboundstestenable();
  original_struct.stencilTestEnable = proto.stenciltestenable();
  VkStencilOpState &original_struct_front = original_struct.front;
  FillStructFromProto(original_struct_front, proto.front());
  VkStencilOpState &original_struct_back = original_struct.back;
  FillStructFromProto(original_struct_back, proto.back());
  original_struct.minDepthBounds = proto.mindepthbounds();
  original_struct.maxDepthBounds = proto.maxdepthbounds();
}
void FillStructFromProto(VkPipelineDynamicStateCreateInfo& original_struct, const vvk::server::VkPipelineDynamicStateCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkPipelineDynamicStateCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkPipelineDynamicStateCreateFlags{};
  }
  if (proto.has_dynamicstatecount()) {
    original_struct.dynamicStateCount = proto.dynamicstatecount();
  } else {
    original_struct.dynamicStateCount = uint32_t{};
  }
  original_struct.pDynamicStates = reinterpret_cast<VkDynamicState*>(const_cast<vvk::server::VkPipelineDynamicStateCreateInfo&>(proto).mutable_pdynamicstates()->mutable_data());
}
void FillStructFromProto(VkPipelineInputAssemblyStateCreateInfo& original_struct, const vvk::server::VkPipelineInputAssemblyStateCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkPipelineInputAssemblyStateCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkPipelineInputAssemblyStateCreateFlags{};
  }
  original_struct.topology = static_cast<VkPrimitiveTopology>(proto.topology());
  original_struct.primitiveRestartEnable = proto.primitiverestartenable();
}
void FillStructFromProto(VkPipelineLayoutCreateInfo& original_struct, const vvk::server::VkPipelineLayoutCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkPipelineLayoutCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkPipelineLayoutCreateFlags{};
  }
  if (proto.has_setlayoutcount()) {
    original_struct.setLayoutCount = proto.setlayoutcount();
  } else {
    original_struct.setLayoutCount = uint32_t{};
  }
  original_struct.pSetLayouts = reinterpret_cast<const VkDescriptorSetLayout*>(proto.psetlayouts().data());
  if (proto.has_pushconstantrangecount()) {
    original_struct.pushConstantRangeCount = proto.pushconstantrangecount();
  } else {
    original_struct.pushConstantRangeCount = uint32_t{};
  }
  VkPushConstantRange* original_struct_pPushConstantRanges = new VkPushConstantRange[proto.ppushconstantranges_size()]();
  original_struct.pPushConstantRanges = original_struct_pPushConstantRanges;
  for (int pPushConstantRanges_indx = 0; pPushConstantRanges_indx < proto.ppushconstantranges_size(); pPushConstantRanges_indx++) {
    VkPushConstantRange &original_struct_pPushConstantRanges_i = original_struct_pPushConstantRanges[pPushConstantRanges_indx];
    FillStructFromProto(original_struct_pPushConstantRanges_i, proto.ppushconstantranges(pPushConstantRanges_indx));
  }
}
void FillStructFromProto(VkPipelineMultisampleStateCreateInfo& original_struct, const vvk::server::VkPipelineMultisampleStateCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkPipelineMultisampleStateCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkPipelineMultisampleStateCreateFlags{};
  }
  original_struct.rasterizationSamples = static_cast<VkSampleCountFlagBits>(proto.rasterizationsamples());
  original_struct.sampleShadingEnable = proto.sampleshadingenable();
  original_struct.minSampleShading = proto.minsampleshading();
  VkSampleMask* original_struct_pSampleMask = new VkSampleMask[proto.psamplemask_size()]();
  original_struct.pSampleMask = original_struct_pSampleMask;
  if (proto.psamplemask_size()) {
    for (int pSampleMask_indx = 0; pSampleMask_indx < proto.psamplemask_size(); pSampleMask_indx++) {
      original_struct_pSampleMask[pSampleMask_indx] = proto.psamplemask(pSampleMask_indx);
    }
  } else {
    original_struct.pSampleMask = nullptr;
  }
  original_struct.alphaToCoverageEnable = proto.alphatocoverageenable();
  original_struct.alphaToOneEnable = proto.alphatooneenable();
}
void FillStructFromProto(VkPipelineRasterizationStateCreateInfo& original_struct, const vvk::server::VkPipelineRasterizationStateCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkPipelineRasterizationStateCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkPipelineRasterizationStateCreateFlags{};
  }
  original_struct.depthClampEnable = proto.depthclampenable();
  original_struct.rasterizerDiscardEnable = proto.rasterizerdiscardenable();
  original_struct.polygonMode = static_cast<VkPolygonMode>(proto.polygonmode());
  if (proto.has_cullmode()) {
    original_struct.cullMode = static_cast<VkCullModeFlags>(proto.cullmode());
  } else {
    original_struct.cullMode = VkCullModeFlags{};
  }
  original_struct.frontFace = static_cast<VkFrontFace>(proto.frontface());
  original_struct.depthBiasEnable = proto.depthbiasenable();
  original_struct.depthBiasConstantFactor = proto.depthbiasconstantfactor();
  original_struct.depthBiasClamp = proto.depthbiasclamp();
  original_struct.depthBiasSlopeFactor = proto.depthbiasslopefactor();
  original_struct.lineWidth = proto.linewidth();
}
void FillStructFromProto(VkPipelineShaderStageCreateInfo& original_struct, const vvk::server::VkPipelineShaderStageCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  VkBaseOutStructure* base = reinterpret_cast<VkBaseOutStructure*>(&original_struct);
  for (const auto& pnext : proto.pnext()) {
    if (pnext.has_vkshadermodulecreateinfo_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkShaderModuleCreateInfo);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkShaderModuleCreateInfo*>(base->pNext), pnext.vkshadermodulecreateinfo_chain_elem());
    }
    base = base->pNext;
  }
  base->pNext = nullptr;
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkPipelineShaderStageCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkPipelineShaderStageCreateFlags{};
  }
  original_struct.stage = static_cast<VkShaderStageFlagBits>(proto.stage());
  if (proto.has_module()) {
    original_struct.module = reinterpret_cast<VkShaderModule>(proto.module());
  } else {
    original_struct.module = VkShaderModule{};
  }
  original_struct.pName = proto.pname().data();
  if (proto.has_pspecializationinfo()) {
    VkSpecializationInfo* original_struct_pSpecializationInfo = new VkSpecializationInfo;
    FillStructFromProto(*original_struct_pSpecializationInfo, proto.pspecializationinfo());
    original_struct.pSpecializationInfo = original_struct_pSpecializationInfo;
  } else {
    original_struct.pSpecializationInfo = nullptr;
  }
}
void FillStructFromProto(VkPipelineTessellationStateCreateInfo& original_struct, const vvk::server::VkPipelineTessellationStateCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkPipelineTessellationStateCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkPipelineTessellationStateCreateFlags{};
  }
  original_struct.patchControlPoints = proto.patchcontrolpoints();
}
void FillStructFromProto(VkPipelineVertexInputStateCreateInfo& original_struct, const vvk::server::VkPipelineVertexInputStateCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkPipelineVertexInputStateCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkPipelineVertexInputStateCreateFlags{};
  }
  if (proto.has_vertexbindingdescriptioncount()) {
    original_struct.vertexBindingDescriptionCount = proto.vertexbindingdescriptioncount();
  } else {
    original_struct.vertexBindingDescriptionCount = uint32_t{};
  }
  VkVertexInputBindingDescription* original_struct_pVertexBindingDescriptions = new VkVertexInputBindingDescription[proto.pvertexbindingdescriptions_size()]();
  original_struct.pVertexBindingDescriptions = original_struct_pVertexBindingDescriptions;
  for (int pVertexBindingDescriptions_indx = 0; pVertexBindingDescriptions_indx < proto.pvertexbindingdescriptions_size(); pVertexBindingDescriptions_indx++) {
    VkVertexInputBindingDescription &original_struct_pVertexBindingDescriptions_i = original_struct_pVertexBindingDescriptions[pVertexBindingDescriptions_indx];
    FillStructFromProto(original_struct_pVertexBindingDescriptions_i, proto.pvertexbindingdescriptions(pVertexBindingDescriptions_indx));
  }
  if (proto.has_vertexattributedescriptioncount()) {
    original_struct.vertexAttributeDescriptionCount = proto.vertexattributedescriptioncount();
  } else {
    original_struct.vertexAttributeDescriptionCount = uint32_t{};
  }
  VkVertexInputAttributeDescription* original_struct_pVertexAttributeDescriptions = new VkVertexInputAttributeDescription[proto.pvertexattributedescriptions_size()]();
  original_struct.pVertexAttributeDescriptions = original_struct_pVertexAttributeDescriptions;
  for (int pVertexAttributeDescriptions_indx = 0; pVertexAttributeDescriptions_indx < proto.pvertexattributedescriptions_size(); pVertexAttributeDescriptions_indx++) {
    VkVertexInputAttributeDescription &original_struct_pVertexAttributeDescriptions_i = original_struct_pVertexAttributeDescriptions[pVertexAttributeDescriptions_indx];
    FillStructFromProto(original_struct_pVertexAttributeDescriptions_i, proto.pvertexattributedescriptions(pVertexAttributeDescriptions_indx));
  }
}
void FillStructFromProto(VkPipelineViewportStateCreateInfo& original_struct, const vvk::server::VkPipelineViewportStateCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkPipelineViewportStateCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkPipelineViewportStateCreateFlags{};
  }
  if (proto.has_viewportcount()) {
    original_struct.viewportCount = proto.viewportcount();
  } else {
    original_struct.viewportCount = uint32_t{};
  }
  VkViewport* original_struct_pViewports = new VkViewport[proto.pviewports_size()]();
  original_struct.pViewports = original_struct_pViewports;
  if (proto.pviewports_size()) {
    for (int pViewports_indx = 0; pViewports_indx < proto.pviewports_size(); pViewports_indx++) {
      VkViewport &original_struct_pViewports_i = original_struct_pViewports[pViewports_indx];
      FillStructFromProto(original_struct_pViewports_i, proto.pviewports(pViewports_indx));
    }
  } else {
    original_struct.pViewports = nullptr;
  }
  if (proto.has_scissorcount()) {
    original_struct.scissorCount = proto.scissorcount();
  } else {
    original_struct.scissorCount = uint32_t{};
  }
  VkRect2D* original_struct_pScissors = new VkRect2D[proto.pscissors_size()]();
  original_struct.pScissors = original_struct_pScissors;
  if (proto.pscissors_size()) {
    for (int pScissors_indx = 0; pScissors_indx < proto.pscissors_size(); pScissors_indx++) {
      VkRect2D &original_struct_pScissors_i = original_struct_pScissors[pScissors_indx];
      FillStructFromProto(original_struct_pScissors_i, proto.pscissors(pScissors_indx));
    }
  } else {
    original_struct.pScissors = nullptr;
  }
}
void FillStructFromProto(VkPushConstantRange& original_struct, const vvk::server::VkPushConstantRange& proto) {
  original_struct.stageFlags = static_cast<VkShaderStageFlags>(proto.stageflags());
  original_struct.offset = proto.offset();
  original_struct.size = proto.size();
}
void FillStructFromProto(VkRect2D& original_struct, const vvk::server::VkRect2D& proto) {
  VkOffset2D &original_struct_offset = original_struct.offset;
  FillStructFromProto(original_struct_offset, proto.offset());
  VkExtent2D &original_struct_extent = original_struct.extent;
  FillStructFromProto(original_struct_extent, proto.extent());
}
void FillStructFromProto(VkRenderPassBeginInfo& original_struct, const vvk::server::VkRenderPassBeginInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  original_struct.renderPass = reinterpret_cast<VkRenderPass>(proto.renderpass());
  original_struct.framebuffer = reinterpret_cast<VkFramebuffer>(proto.framebuffer());
  VkRect2D &original_struct_renderArea = original_struct.renderArea;
  FillStructFromProto(original_struct_renderArea, proto.renderarea());
  if (proto.has_clearvaluecount()) {
    original_struct.clearValueCount = proto.clearvaluecount();
  } else {
    original_struct.clearValueCount = uint32_t{};
  }
  VkClearValue* original_struct_pClearValues = new VkClearValue[proto.pclearvalues_size()]();
  original_struct.pClearValues = original_struct_pClearValues;
  for (int pClearValues_indx = 0; pClearValues_indx < proto.pclearvalues_size(); pClearValues_indx++) {
    VkClearValue &original_struct_pClearValues_i = original_struct_pClearValues[pClearValues_indx];
    FillStructFromProto(original_struct_pClearValues_i, proto.pclearvalues(pClearValues_indx));
  }
}
void FillStructFromProto(VkRenderPassCreateInfo& original_struct, const vvk::server::VkRenderPassCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkRenderPassCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkRenderPassCreateFlags{};
  }
  if (proto.has_attachmentcount()) {
    original_struct.attachmentCount = proto.attachmentcount();
  } else {
    original_struct.attachmentCount = uint32_t{};
  }
  VkAttachmentDescription* original_struct_pAttachments = new VkAttachmentDescription[proto.pattachments_size()]();
  original_struct.pAttachments = original_struct_pAttachments;
  for (int pAttachments_indx = 0; pAttachments_indx < proto.pattachments_size(); pAttachments_indx++) {
    VkAttachmentDescription &original_struct_pAttachments_i = original_struct_pAttachments[pAttachments_indx];
    FillStructFromProto(original_struct_pAttachments_i, proto.pattachments(pAttachments_indx));
  }
  original_struct.subpassCount = proto.subpasscount();
  VkSubpassDescription* original_struct_pSubpasses = new VkSubpassDescription[proto.psubpasses_size()]();
  original_struct.pSubpasses = original_struct_pSubpasses;
  for (int pSubpasses_indx = 0; pSubpasses_indx < proto.psubpasses_size(); pSubpasses_indx++) {
    VkSubpassDescription &original_struct_pSubpasses_i = original_struct_pSubpasses[pSubpasses_indx];
    FillStructFromProto(original_struct_pSubpasses_i, proto.psubpasses(pSubpasses_indx));
  }
  if (proto.has_dependencycount()) {
    original_struct.dependencyCount = proto.dependencycount();
  } else {
    original_struct.dependencyCount = uint32_t{};
  }
  VkSubpassDependency* original_struct_pDependencies = new VkSubpassDependency[proto.pdependencies_size()]();
  original_struct.pDependencies = original_struct_pDependencies;
  for (int pDependencies_indx = 0; pDependencies_indx < proto.pdependencies_size(); pDependencies_indx++) {
    VkSubpassDependency &original_struct_pDependencies_i = original_struct_pDependencies[pDependencies_indx];
    FillStructFromProto(original_struct_pDependencies_i, proto.pdependencies(pDependencies_indx));
  }
}
void FillStructFromProto(VkSamplerCreateInfo& original_struct, const vvk::server::VkSamplerCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkSamplerCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkSamplerCreateFlags{};
  }
  original_struct.magFilter = static_cast<VkFilter>(proto.magfilter());
  original_struct.minFilter = static_cast<VkFilter>(proto.minfilter());
  original_struct.mipmapMode = static_cast<VkSamplerMipmapMode>(proto.mipmapmode());
  original_struct.addressModeU = static_cast<VkSamplerAddressMode>(proto.addressmodeu());
  original_struct.addressModeV = static_cast<VkSamplerAddressMode>(proto.addressmodev());
  original_struct.addressModeW = static_cast<VkSamplerAddressMode>(proto.addressmodew());
  original_struct.mipLodBias = proto.miplodbias();
  original_struct.anisotropyEnable = proto.anisotropyenable();
  original_struct.maxAnisotropy = proto.maxanisotropy();
  original_struct.compareEnable = proto.compareenable();
  original_struct.compareOp = static_cast<VkCompareOp>(proto.compareop());
  original_struct.minLod = proto.minlod();
  original_struct.maxLod = proto.maxlod();
  original_struct.borderColor = static_cast<VkBorderColor>(proto.bordercolor());
  original_struct.unnormalizedCoordinates = proto.unnormalizedcoordinates();
}
void FillStructFromProto(VkSemaphoreCreateInfo& original_struct, const vvk::server::VkSemaphoreCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
  VkBaseOutStructure* base = reinterpret_cast<VkBaseOutStructure*>(&original_struct);
  for (const auto& pnext : proto.pnext()) {
    if (pnext.has_vksemaphoretypecreateinfo_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkSemaphoreTypeCreateInfo);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkSemaphoreTypeCreateInfo*>(base->pNext), pnext.vksemaphoretypecreateinfo_chain_elem());
    }
    base = base->pNext;
  }
  base->pNext = nullptr;
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkSemaphoreCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkSemaphoreCreateFlags{};
  }
}
void FillStructFromProto(VkSemaphoreSignalInfo& original_struct, const vvk::server::VkSemaphoreSignalInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  original_struct.semaphore = reinterpret_cast<VkSemaphore>(proto.semaphore());
  original_struct.value = proto.value();
}
void FillStructFromProto(VkShaderModuleCreateInfo& original_struct, const vvk::server::VkShaderModuleCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  original_struct.pNext = nullptr;  // Empty pNext chain
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkShaderModuleCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkShaderModuleCreateFlags{};
  }
  original_struct.codeSize = proto.codesize();
  uint32_t* original_struct_pCode = new uint32_t[proto.pcode_size()]();
  original_struct.pCode = original_struct_pCode;
  for (int pCode_indx = 0; pCode_indx < proto.pcode_size(); pCode_indx++) {
    original_struct_pCode[pCode_indx] = proto.pcode(pCode_indx);
  }
}
void FillStructFromProto(VkSpecializationInfo& original_struct, const vvk::server::VkSpecializationInfo& proto) {
  if (proto.has_mapentrycount()) {
    original_struct.mapEntryCount = proto.mapentrycount();
  } else {
    original_struct.mapEntryCount = uint32_t{};
  }
  VkSpecializationMapEntry* original_struct_pMapEntries = new VkSpecializationMapEntry[proto.pmapentries_size()]();
  original_struct.pMapEntries = original_struct_pMapEntries;
  for (int pMapEntries_indx = 0; pMapEntries_indx < proto.pmapentries_size(); pMapEntries_indx++) {
    VkSpecializationMapEntry &original_struct_pMapEntries_i = original_struct_pMapEntries[pMapEntries_indx];
    FillStructFromProto(original_struct_pMapEntries_i, proto.pmapentries(pMapEntries_indx));
  }
  if (proto.has_datasize()) {
    original_struct.dataSize = proto.datasize();
  } else {
    original_struct.dataSize = size_t{};
  }
  original_struct.pData = proto.pdata().data();
}
void FillStructFromProto(VkSpecializationMapEntry& original_struct, const vvk::server::VkSpecializationMapEntry& proto) {
  original_struct.constantID = proto.constantid();
  original_struct.offset = proto.offset();
  original_struct.size = proto.size();
}
void FillStructFromProto(VkStencilOpState& original_struct, const vvk::server::VkStencilOpState& proto) {
  original_struct.failOp = static_cast<VkStencilOp>(proto.failop());
  original_struct.passOp = static_cast<VkStencilOp>(proto.passop());
  original_struct.depthFailOp = static_cast<VkStencilOp>(proto.depthfailop());
  original_struct.compareOp = static_cast<VkCompareOp>(proto.compareop());
  original_struct.compareMask = proto.comparemask();
  original_struct.writeMask = proto.writemask();
  original_struct.reference = proto.reference();
}
void FillStructFromProto(VkSubmitInfo& original_struct, const vvk::server::VkSubmitInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  VkBaseOutStructure* base = reinterpret_cast<VkBaseOutStructure*>(&original_struct);
  for (const auto& pnext : proto.pnext()) {
    if (pnext.has_vkprotectedsubmitinfo_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkProtectedSubmitInfo);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkProtectedSubmitInfo*>(base->pNext), pnext.vkprotectedsubmitinfo_chain_elem());
    }
    if (pnext.has_vktimelinesemaphoresubmitinfo_chain_elem()) {
      base->pNext = reinterpret_cast<VkBaseOutStructure*>(new VkTimelineSemaphoreSubmitInfo);
      FillStructFromProtoNoPNext(*reinterpret_cast<VkTimelineSemaphoreSubmitInfo*>(base->pNext), pnext.vktimelinesemaphoresubmitinfo_chain_elem());
    }
    base = base->pNext;
  }
  base->pNext = nullptr;
  if (proto.has_waitsemaphorecount()) {
    original_struct.waitSemaphoreCount = proto.waitsemaphorecount();
  } else {
    original_struct.waitSemaphoreCount = uint32_t{};
  }
  original_struct.pWaitSemaphores = reinterpret_cast<const VkSemaphore*>(proto.pwaitsemaphores().data());
  VkPipelineStageFlags* original_struct_pWaitDstStageMask = new VkPipelineStageFlags[proto.pwaitdststagemask_size()]();
  original_struct.pWaitDstStageMask = original_struct_pWaitDstStageMask;
  for (int pWaitDstStageMask_indx = 0; pWaitDstStageMask_indx < proto.pwaitdststagemask_size(); pWaitDstStageMask_indx++) {
    original_struct_pWaitDstStageMask[pWaitDstStageMask_indx] = static_cast<VkPipelineStageFlags>(proto.pwaitdststagemask(pWaitDstStageMask_indx));
  }
  if (proto.has_commandbuffercount()) {
    original_struct.commandBufferCount = proto.commandbuffercount();
  } else {
    original_struct.commandBufferCount = uint32_t{};
  }
  original_struct.pCommandBuffers = reinterpret_cast<const VkCommandBuffer*>(proto.pcommandbuffers().data());
  if (proto.has_signalsemaphorecount()) {
    original_struct.signalSemaphoreCount = proto.signalsemaphorecount();
  } else {
    original_struct.signalSemaphoreCount = uint32_t{};
  }
  original_struct.pSignalSemaphores = reinterpret_cast<const VkSemaphore*>(proto.psignalsemaphores().data());
}
void FillStructFromProto(VkSubpassDependency& original_struct, const vvk::server::VkSubpassDependency& proto) {
  original_struct.srcSubpass = proto.srcsubpass();
  original_struct.dstSubpass = proto.dstsubpass();
  if (proto.has_srcstagemask()) {
    original_struct.srcStageMask = static_cast<VkPipelineStageFlags>(proto.srcstagemask());
  } else {
    original_struct.srcStageMask = VkPipelineStageFlags{};
  }
  if (proto.has_dststagemask()) {
    original_struct.dstStageMask = static_cast<VkPipelineStageFlags>(proto.dststagemask());
  } else {
    original_struct.dstStageMask = VkPipelineStageFlags{};
  }
  if (proto.has_srcaccessmask()) {
    original_struct.srcAccessMask = static_cast<VkAccessFlags>(proto.srcaccessmask());
  } else {
    original_struct.srcAccessMask = VkAccessFlags{};
  }
  if (proto.has_dstaccessmask()) {
    original_struct.dstAccessMask = static_cast<VkAccessFlags>(proto.dstaccessmask());
  } else {
    original_struct.dstAccessMask = VkAccessFlags{};
  }
  if (proto.has_dependencyflags()) {
    original_struct.dependencyFlags = static_cast<VkDependencyFlags>(proto.dependencyflags());
  } else {
    original_struct.dependencyFlags = VkDependencyFlags{};
  }
}
void FillStructFromProto(VkSubpassDescription& original_struct, const vvk::server::VkSubpassDescription& proto) {
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkSubpassDescriptionFlags>(proto.flags());
  } else {
    original_struct.flags = VkSubpassDescriptionFlags{};
  }
  original_struct.pipelineBindPoint = static_cast<VkPipelineBindPoint>(proto.pipelinebindpoint());
  if (proto.has_inputattachmentcount()) {
    original_struct.inputAttachmentCount = proto.inputattachmentcount();
  } else {
    original_struct.inputAttachmentCount = uint32_t{};
  }
  VkAttachmentReference* original_struct_pInputAttachments = new VkAttachmentReference[proto.pinputattachments_size()]();
  original_struct.pInputAttachments = original_struct_pInputAttachments;
  for (int pInputAttachments_indx = 0; pInputAttachments_indx < proto.pinputattachments_size(); pInputAttachments_indx++) {
    VkAttachmentReference &original_struct_pInputAttachments_i = original_struct_pInputAttachments[pInputAttachments_indx];
    FillStructFromProto(original_struct_pInputAttachments_i, proto.pinputattachments(pInputAttachments_indx));
  }
  if (proto.has_colorattachmentcount()) {
    original_struct.colorAttachmentCount = proto.colorattachmentcount();
  } else {
    original_struct.colorAttachmentCount = uint32_t{};
  }
  VkAttachmentReference* original_struct_pColorAttachments = new VkAttachmentReference[proto.pcolorattachments_size()]();
  original_struct.pColorAttachments = original_struct_pColorAttachments;
  for (int pColorAttachments_indx = 0; pColorAttachments_indx < proto.pcolorattachments_size(); pColorAttachments_indx++) {
    VkAttachmentReference &original_struct_pColorAttachments_i = original_struct_pColorAttachments[pColorAttachments_indx];
    FillStructFromProto(original_struct_pColorAttachments_i, proto.pcolorattachments(pColorAttachments_indx));
  }
  VkAttachmentReference* original_struct_pResolveAttachments = new VkAttachmentReference[proto.presolveattachments_size()]();
  original_struct.pResolveAttachments = original_struct_pResolveAttachments;
  if (proto.presolveattachments_size()) {
    for (int pResolveAttachments_indx = 0; pResolveAttachments_indx < proto.presolveattachments_size(); pResolveAttachments_indx++) {
      VkAttachmentReference &original_struct_pResolveAttachments_i = original_struct_pResolveAttachments[pResolveAttachments_indx];
      FillStructFromProto(original_struct_pResolveAttachments_i, proto.presolveattachments(pResolveAttachments_indx));
    }
  } else {
    original_struct.pResolveAttachments = nullptr;
  }
  if (proto.has_pdepthstencilattachment()) {
    VkAttachmentReference* original_struct_pDepthStencilAttachment = new VkAttachmentReference;
    FillStructFromProto(*original_struct_pDepthStencilAttachment, proto.pdepthstencilattachment());
    original_struct.pDepthStencilAttachment = original_struct_pDepthStencilAttachment;
  } else {
    original_struct.pDepthStencilAttachment = nullptr;
  }
  if (proto.has_preserveattachmentcount()) {
    original_struct.preserveAttachmentCount = proto.preserveattachmentcount();
  } else {
    original_struct.preserveAttachmentCount = uint32_t{};
  }
  uint32_t* original_struct_pPreserveAttachments = new uint32_t[proto.ppreserveattachments_size()]();
  original_struct.pPreserveAttachments = original_struct_pPreserveAttachments;
  for (int pPreserveAttachments_indx = 0; pPreserveAttachments_indx < proto.ppreserveattachments_size(); pPreserveAttachments_indx++) {
    original_struct_pPreserveAttachments[pPreserveAttachments_indx] = proto.ppreserveattachments(pPreserveAttachments_indx);
  }
}
void FillStructFromProto(VkSubresourceLayout& original_struct, const vvk::server::VkSubresourceLayout& proto) {
  original_struct.offset = static_cast<VkDeviceSize>(proto.offset());
  original_struct.size = static_cast<VkDeviceSize>(proto.size());
  original_struct.rowPitch = static_cast<VkDeviceSize>(proto.rowpitch());
  original_struct.arrayPitch = static_cast<VkDeviceSize>(proto.arraypitch());
  original_struct.depthPitch = static_cast<VkDeviceSize>(proto.depthpitch());
}
void FillStructFromProto(VkVertexInputAttributeDescription& original_struct, const vvk::server::VkVertexInputAttributeDescription& proto) {
  original_struct.location = proto.location();
  original_struct.binding = proto.binding();
  original_struct.format = static_cast<VkFormat>(proto.format());
  original_struct.offset = proto.offset();
}
void FillStructFromProto(VkVertexInputBindingDescription& original_struct, const vvk::server::VkVertexInputBindingDescription& proto) {
  original_struct.binding = proto.binding();
  original_struct.stride = proto.stride();
  original_struct.inputRate = static_cast<VkVertexInputRate>(proto.inputrate());
}
void FillStructFromProto(VkViewport& original_struct, const vvk::server::VkViewport& proto) {
  original_struct.x = proto.x();
  original_struct.y = proto.y();
  original_struct.width = proto.width();
  original_struct.height = proto.height();
  original_struct.minDepth = proto.mindepth();
  original_struct.maxDepth = proto.maxdepth();
}
void FillStructFromProto(VkWriteDescriptorSet& original_struct, const vvk::server::VkWriteDescriptorSet& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  original_struct.pNext = nullptr;  // Empty pNext chain
  original_struct.dstSet = reinterpret_cast<VkDescriptorSet>(proto.dstset());
  original_struct.dstBinding = proto.dstbinding();
  original_struct.dstArrayElement = proto.dstarrayelement();
  original_struct.descriptorCount = proto.descriptorcount();
  original_struct.descriptorType = static_cast<VkDescriptorType>(proto.descriptortype());
  VkDescriptorImageInfo* original_struct_pImageInfo = new VkDescriptorImageInfo[proto.pimageinfo_size()]();
  original_struct.pImageInfo = original_struct_pImageInfo;
  for (int pImageInfo_indx = 0; pImageInfo_indx < proto.pimageinfo_size(); pImageInfo_indx++) {
    VkDescriptorImageInfo &original_struct_pImageInfo_i = original_struct_pImageInfo[pImageInfo_indx];
    FillStructFromProto(original_struct_pImageInfo_i, proto.pimageinfo(pImageInfo_indx));
  }
  VkDescriptorBufferInfo* original_struct_pBufferInfo = new VkDescriptorBufferInfo[proto.pbufferinfo_size()]();
  original_struct.pBufferInfo = original_struct_pBufferInfo;
  for (int pBufferInfo_indx = 0; pBufferInfo_indx < proto.pbufferinfo_size(); pBufferInfo_indx++) {
    VkDescriptorBufferInfo &original_struct_pBufferInfo_i = original_struct_pBufferInfo[pBufferInfo_indx];
    FillStructFromProto(original_struct_pBufferInfo_i, proto.pbufferinfo(pBufferInfo_indx));
  }
  original_struct.pTexelBufferView = reinterpret_cast<const VkBufferView*>(proto.ptexelbufferview().data());
}
void FillStructFromProtoNoPNext(VkPhysicalDeviceProtectedMemoryFeatures& original_struct, const vvk::server::VkPhysicalDeviceProtectedMemoryFeatures& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_FEATURES;
  original_struct.protectedMemory = proto.protectedmemory();
}
void FillStructFromProtoNoPNext(VkPhysicalDeviceProtectedMemoryProperties& original_struct, const vvk::server::VkPhysicalDeviceProtectedMemoryProperties& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_PROPERTIES;
  original_struct.protectedNoFault = proto.protectednofault();
}
void FillStructFromProtoNoPNext(VkPhysicalDeviceShaderDrawParametersFeatures& original_struct, const vvk::server::VkPhysicalDeviceShaderDrawParametersFeatures& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETERS_FEATURES;
  original_struct.shaderDrawParameters = proto.shaderdrawparameters();
}
void FillStructFromProtoNoPNext(VkPhysicalDeviceSubgroupProperties& original_struct, const vvk::server::VkPhysicalDeviceSubgroupProperties& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES;
  original_struct.subgroupSize = proto.subgroupsize();
  original_struct.supportedStages = static_cast<VkShaderStageFlags>(proto.supportedstages());
  original_struct.supportedOperations = static_cast<VkSubgroupFeatureFlags>(proto.supportedoperations());
  original_struct.quadOperationsInAllStages = proto.quadoperationsinallstages();
}
void FillStructFromProtoNoPNext(VkPhysicalDeviceTimelineSemaphoreFeatures& original_struct, const vvk::server::VkPhysicalDeviceTimelineSemaphoreFeatures& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES;
  original_struct.timelineSemaphore = proto.timelinesemaphore();
}
void FillStructFromProtoNoPNext(VkPhysicalDeviceTimelineSemaphoreProperties& original_struct, const vvk::server::VkPhysicalDeviceTimelineSemaphoreProperties& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_PROPERTIES;
  original_struct.maxTimelineSemaphoreValueDifference = proto.maxtimelinesemaphorevaluedifference();
}
void FillStructFromProtoNoPNext(VkPhysicalDeviceVulkan11Features& original_struct, const vvk::server::VkPhysicalDeviceVulkan11Features& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
  original_struct.storageBuffer16BitAccess = proto.storagebuffer16bitaccess();
  original_struct.uniformAndStorageBuffer16BitAccess = proto.uniformandstoragebuffer16bitaccess();
  original_struct.storagePushConstant16 = proto.storagepushconstant16();
  original_struct.storageInputOutput16 = proto.storageinputoutput16();
  original_struct.multiview = proto.multiview();
  original_struct.multiviewGeometryShader = proto.multiviewgeometryshader();
  original_struct.multiviewTessellationShader = proto.multiviewtessellationshader();
  original_struct.variablePointersStorageBuffer = proto.variablepointersstoragebuffer();
  original_struct.variablePointers = proto.variablepointers();
  original_struct.protectedMemory = proto.protectedmemory();
  original_struct.samplerYcbcrConversion = proto.samplerycbcrconversion();
  original_struct.shaderDrawParameters = proto.shaderdrawparameters();
}
void FillStructFromProtoNoPNext(VkPhysicalDeviceVulkan11Properties& original_struct, const vvk::server::VkPhysicalDeviceVulkan11Properties& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES;
  const size_t original_struct_deviceUUID_length = std::min(VK_UUID_SIZE, VK_UUID_SIZE);
  for (uint32_t deviceUUID_indx = 0; deviceUUID_indx < original_struct_deviceUUID_length; deviceUUID_indx++) {
    original_struct.deviceUUID[deviceUUID_indx] = static_cast<uint8_t>(proto.deviceuuid(deviceUUID_indx));
  }
  const size_t original_struct_driverUUID_length = std::min(VK_UUID_SIZE, VK_UUID_SIZE);
  for (uint32_t driverUUID_indx = 0; driverUUID_indx < original_struct_driverUUID_length; driverUUID_indx++) {
    original_struct.driverUUID[driverUUID_indx] = static_cast<uint8_t>(proto.driveruuid(driverUUID_indx));
  }
  const size_t original_struct_deviceLUID_length = std::min(VK_LUID_SIZE, VK_LUID_SIZE);
  for (uint32_t deviceLUID_indx = 0; deviceLUID_indx < original_struct_deviceLUID_length; deviceLUID_indx++) {
    original_struct.deviceLUID[deviceLUID_indx] = static_cast<uint8_t>(proto.deviceluid(deviceLUID_indx));
  }
  original_struct.deviceNodeMask = proto.devicenodemask();
  original_struct.deviceLUIDValid = proto.deviceluidvalid();
  original_struct.subgroupSize = proto.subgroupsize();
  original_struct.subgroupSupportedStages = static_cast<VkShaderStageFlags>(proto.subgroupsupportedstages());
  original_struct.subgroupSupportedOperations = static_cast<VkSubgroupFeatureFlags>(proto.subgroupsupportedoperations());
  original_struct.subgroupQuadOperationsInAllStages = proto.subgroupquadoperationsinallstages();
  original_struct.pointClippingBehavior = static_cast<VkPointClippingBehavior>(proto.pointclippingbehavior());
  original_struct.maxMultiviewViewCount = proto.maxmultiviewviewcount();
  original_struct.maxMultiviewInstanceIndex = proto.maxmultiviewinstanceindex();
  original_struct.protectedNoFault = proto.protectednofault();
  original_struct.maxPerSetDescriptors = proto.maxpersetdescriptors();
  original_struct.maxMemoryAllocationSize = static_cast<VkDeviceSize>(proto.maxmemoryallocationsize());
}
void FillStructFromProtoNoPNext(VkPhysicalDeviceVulkan12Features& original_struct, const vvk::server::VkPhysicalDeviceVulkan12Features& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
  original_struct.samplerMirrorClampToEdge = proto.samplermirrorclamptoedge();
  original_struct.drawIndirectCount = proto.drawindirectcount();
  original_struct.storageBuffer8BitAccess = proto.storagebuffer8bitaccess();
  original_struct.uniformAndStorageBuffer8BitAccess = proto.uniformandstoragebuffer8bitaccess();
  original_struct.storagePushConstant8 = proto.storagepushconstant8();
  original_struct.shaderBufferInt64Atomics = proto.shaderbufferint64atomics();
  original_struct.shaderSharedInt64Atomics = proto.shadersharedint64atomics();
  original_struct.shaderFloat16 = proto.shaderfloat16();
  original_struct.shaderInt8 = proto.shaderint8();
  original_struct.descriptorIndexing = proto.descriptorindexing();
  original_struct.shaderInputAttachmentArrayDynamicIndexing = proto.shaderinputattachmentarraydynamicindexing();
  original_struct.shaderUniformTexelBufferArrayDynamicIndexing = proto.shaderuniformtexelbufferarraydynamicindexing();
  original_struct.shaderStorageTexelBufferArrayDynamicIndexing = proto.shaderstoragetexelbufferarraydynamicindexing();
  original_struct.shaderUniformBufferArrayNonUniformIndexing = proto.shaderuniformbufferarraynonuniformindexing();
  original_struct.shaderSampledImageArrayNonUniformIndexing = proto.shadersampledimagearraynonuniformindexing();
  original_struct.shaderStorageBufferArrayNonUniformIndexing = proto.shaderstoragebufferarraynonuniformindexing();
  original_struct.shaderStorageImageArrayNonUniformIndexing = proto.shaderstorageimagearraynonuniformindexing();
  original_struct.shaderInputAttachmentArrayNonUniformIndexing = proto.shaderinputattachmentarraynonuniformindexing();
  original_struct.shaderUniformTexelBufferArrayNonUniformIndexing = proto.shaderuniformtexelbufferarraynonuniformindexing();
  original_struct.shaderStorageTexelBufferArrayNonUniformIndexing = proto.shaderstoragetexelbufferarraynonuniformindexing();
  original_struct.descriptorBindingUniformBufferUpdateAfterBind = proto.descriptorbindinguniformbufferupdateafterbind();
  original_struct.descriptorBindingSampledImageUpdateAfterBind = proto.descriptorbindingsampledimageupdateafterbind();
  original_struct.descriptorBindingStorageImageUpdateAfterBind = proto.descriptorbindingstorageimageupdateafterbind();
  original_struct.descriptorBindingStorageBufferUpdateAfterBind = proto.descriptorbindingstoragebufferupdateafterbind();
  original_struct.descriptorBindingUniformTexelBufferUpdateAfterBind = proto.descriptorbindinguniformtexelbufferupdateafterbind();
  original_struct.descriptorBindingStorageTexelBufferUpdateAfterBind = proto.descriptorbindingstoragetexelbufferupdateafterbind();
  original_struct.descriptorBindingUpdateUnusedWhilePending = proto.descriptorbindingupdateunusedwhilepending();
  original_struct.descriptorBindingPartiallyBound = proto.descriptorbindingpartiallybound();
  original_struct.descriptorBindingVariableDescriptorCount = proto.descriptorbindingvariabledescriptorcount();
  original_struct.runtimeDescriptorArray = proto.runtimedescriptorarray();
  original_struct.samplerFilterMinmax = proto.samplerfilterminmax();
  original_struct.scalarBlockLayout = proto.scalarblocklayout();
  original_struct.imagelessFramebuffer = proto.imagelessframebuffer();
  original_struct.uniformBufferStandardLayout = proto.uniformbufferstandardlayout();
  original_struct.shaderSubgroupExtendedTypes = proto.shadersubgroupextendedtypes();
  original_struct.separateDepthStencilLayouts = proto.separatedepthstencillayouts();
  original_struct.hostQueryReset = proto.hostqueryreset();
  original_struct.timelineSemaphore = proto.timelinesemaphore();
  original_struct.bufferDeviceAddress = proto.bufferdeviceaddress();
  original_struct.bufferDeviceAddressCaptureReplay = proto.bufferdeviceaddresscapturereplay();
  original_struct.bufferDeviceAddressMultiDevice = proto.bufferdeviceaddressmultidevice();
  original_struct.vulkanMemoryModel = proto.vulkanmemorymodel();
  original_struct.vulkanMemoryModelDeviceScope = proto.vulkanmemorymodeldevicescope();
  original_struct.vulkanMemoryModelAvailabilityVisibilityChains = proto.vulkanmemorymodelavailabilityvisibilitychains();
  original_struct.shaderOutputViewportIndex = proto.shaderoutputviewportindex();
  original_struct.shaderOutputLayer = proto.shaderoutputlayer();
  original_struct.subgroupBroadcastDynamicId = proto.subgroupbroadcastdynamicid();
}
void FillStructFromProtoNoPNext(VkPhysicalDeviceVulkan12Properties& original_struct, const vvk::server::VkPhysicalDeviceVulkan12Properties& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES;
  original_struct.driverID = static_cast<VkDriverId>(proto.driverid());
  strncpy(original_struct.driverName, proto.drivername().c_str(), VK_MAX_DRIVER_NAME_SIZE);
  strncpy(original_struct.driverInfo, proto.driverinfo().c_str(), VK_MAX_DRIVER_INFO_SIZE);
  VkConformanceVersion &original_struct_conformanceVersion = original_struct.conformanceVersion;
  FillStructFromProto(original_struct_conformanceVersion, proto.conformanceversion());
  original_struct.denormBehaviorIndependence = static_cast<VkShaderFloatControlsIndependence>(proto.denormbehaviorindependence());
  original_struct.roundingModeIndependence = static_cast<VkShaderFloatControlsIndependence>(proto.roundingmodeindependence());
  original_struct.shaderSignedZeroInfNanPreserveFloat16 = proto.shadersignedzeroinfnanpreservefloat16();
  original_struct.shaderSignedZeroInfNanPreserveFloat32 = proto.shadersignedzeroinfnanpreservefloat32();
  original_struct.shaderSignedZeroInfNanPreserveFloat64 = proto.shadersignedzeroinfnanpreservefloat64();
  original_struct.shaderDenormPreserveFloat16 = proto.shaderdenormpreservefloat16();
  original_struct.shaderDenormPreserveFloat32 = proto.shaderdenormpreservefloat32();
  original_struct.shaderDenormPreserveFloat64 = proto.shaderdenormpreservefloat64();
  original_struct.shaderDenormFlushToZeroFloat16 = proto.shaderdenormflushtozerofloat16();
  original_struct.shaderDenormFlushToZeroFloat32 = proto.shaderdenormflushtozerofloat32();
  original_struct.shaderDenormFlushToZeroFloat64 = proto.shaderdenormflushtozerofloat64();
  original_struct.shaderRoundingModeRTEFloat16 = proto.shaderroundingmodertefloat16();
  original_struct.shaderRoundingModeRTEFloat32 = proto.shaderroundingmodertefloat32();
  original_struct.shaderRoundingModeRTEFloat64 = proto.shaderroundingmodertefloat64();
  original_struct.shaderRoundingModeRTZFloat16 = proto.shaderroundingmodertzfloat16();
  original_struct.shaderRoundingModeRTZFloat32 = proto.shaderroundingmodertzfloat32();
  original_struct.shaderRoundingModeRTZFloat64 = proto.shaderroundingmodertzfloat64();
  original_struct.maxUpdateAfterBindDescriptorsInAllPools = proto.maxupdateafterbinddescriptorsinallpools();
  original_struct.shaderUniformBufferArrayNonUniformIndexingNative = proto.shaderuniformbufferarraynonuniformindexingnative();
  original_struct.shaderSampledImageArrayNonUniformIndexingNative = proto.shadersampledimagearraynonuniformindexingnative();
  original_struct.shaderStorageBufferArrayNonUniformIndexingNative = proto.shaderstoragebufferarraynonuniformindexingnative();
  original_struct.shaderStorageImageArrayNonUniformIndexingNative = proto.shaderstorageimagearraynonuniformindexingnative();
  original_struct.shaderInputAttachmentArrayNonUniformIndexingNative = proto.shaderinputattachmentarraynonuniformindexingnative();
  original_struct.robustBufferAccessUpdateAfterBind = proto.robustbufferaccessupdateafterbind();
  original_struct.quadDivergentImplicitLod = proto.quaddivergentimplicitlod();
  original_struct.maxPerStageDescriptorUpdateAfterBindSamplers = proto.maxperstagedescriptorupdateafterbindsamplers();
  original_struct.maxPerStageDescriptorUpdateAfterBindUniformBuffers = proto.maxperstagedescriptorupdateafterbinduniformbuffers();
  original_struct.maxPerStageDescriptorUpdateAfterBindStorageBuffers = proto.maxperstagedescriptorupdateafterbindstoragebuffers();
  original_struct.maxPerStageDescriptorUpdateAfterBindSampledImages = proto.maxperstagedescriptorupdateafterbindsampledimages();
  original_struct.maxPerStageDescriptorUpdateAfterBindStorageImages = proto.maxperstagedescriptorupdateafterbindstorageimages();
  original_struct.maxPerStageDescriptorUpdateAfterBindInputAttachments = proto.maxperstagedescriptorupdateafterbindinputattachments();
  original_struct.maxPerStageUpdateAfterBindResources = proto.maxperstageupdateafterbindresources();
  original_struct.maxDescriptorSetUpdateAfterBindSamplers = proto.maxdescriptorsetupdateafterbindsamplers();
  original_struct.maxDescriptorSetUpdateAfterBindUniformBuffers = proto.maxdescriptorsetupdateafterbinduniformbuffers();
  original_struct.maxDescriptorSetUpdateAfterBindUniformBuffersDynamic = proto.maxdescriptorsetupdateafterbinduniformbuffersdynamic();
  original_struct.maxDescriptorSetUpdateAfterBindStorageBuffers = proto.maxdescriptorsetupdateafterbindstoragebuffers();
  original_struct.maxDescriptorSetUpdateAfterBindStorageBuffersDynamic = proto.maxdescriptorsetupdateafterbindstoragebuffersdynamic();
  original_struct.maxDescriptorSetUpdateAfterBindSampledImages = proto.maxdescriptorsetupdateafterbindsampledimages();
  original_struct.maxDescriptorSetUpdateAfterBindStorageImages = proto.maxdescriptorsetupdateafterbindstorageimages();
  original_struct.maxDescriptorSetUpdateAfterBindInputAttachments = proto.maxdescriptorsetupdateafterbindinputattachments();
  original_struct.supportedDepthResolveModes = static_cast<VkResolveModeFlags>(proto.supporteddepthresolvemodes());
  original_struct.supportedStencilResolveModes = static_cast<VkResolveModeFlags>(proto.supportedstencilresolvemodes());
  original_struct.independentResolveNone = proto.independentresolvenone();
  original_struct.independentResolve = proto.independentresolve();
  original_struct.filterMinmaxSingleComponentFormats = proto.filterminmaxsinglecomponentformats();
  original_struct.filterMinmaxImageComponentMapping = proto.filterminmaximagecomponentmapping();
  original_struct.maxTimelineSemaphoreValueDifference = proto.maxtimelinesemaphorevaluedifference();
  if (proto.has_framebufferintegercolorsamplecounts()) {
    original_struct.framebufferIntegerColorSampleCounts = static_cast<VkSampleCountFlags>(proto.framebufferintegercolorsamplecounts());
  } else {
    original_struct.framebufferIntegerColorSampleCounts = VkSampleCountFlags{};
  }
}
void FillStructFromProtoNoPNext(VkPhysicalDeviceVulkan13Features& original_struct, const vvk::server::VkPhysicalDeviceVulkan13Features& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
  original_struct.robustImageAccess = proto.robustimageaccess();
  original_struct.inlineUniformBlock = proto.inlineuniformblock();
  original_struct.descriptorBindingInlineUniformBlockUpdateAfterBind = proto.descriptorbindinginlineuniformblockupdateafterbind();
  original_struct.pipelineCreationCacheControl = proto.pipelinecreationcachecontrol();
  original_struct.privateData = proto.privatedata();
  original_struct.shaderDemoteToHelperInvocation = proto.shaderdemotetohelperinvocation();
  original_struct.shaderTerminateInvocation = proto.shaderterminateinvocation();
  original_struct.subgroupSizeControl = proto.subgroupsizecontrol();
  original_struct.computeFullSubgroups = proto.computefullsubgroups();
  original_struct.synchronization2 = proto.synchronization2();
  original_struct.textureCompressionASTC_HDR = proto.texturecompressionastc_hdr();
  original_struct.shaderZeroInitializeWorkgroupMemory = proto.shaderzeroinitializeworkgroupmemory();
  original_struct.dynamicRendering = proto.dynamicrendering();
  original_struct.shaderIntegerDotProduct = proto.shaderintegerdotproduct();
  original_struct.maintenance4 = proto.maintenance4();
}
void FillStructFromProtoNoPNext(VkPhysicalDeviceVulkan13Properties& original_struct, const vvk::server::VkPhysicalDeviceVulkan13Properties& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_PROPERTIES;
  original_struct.minSubgroupSize = proto.minsubgroupsize();
  original_struct.maxSubgroupSize = proto.maxsubgroupsize();
  original_struct.maxComputeWorkgroupSubgroups = proto.maxcomputeworkgroupsubgroups();
  original_struct.requiredSubgroupSizeStages = static_cast<VkShaderStageFlags>(proto.requiredsubgroupsizestages());
  original_struct.maxInlineUniformBlockSize = proto.maxinlineuniformblocksize();
  original_struct.maxPerStageDescriptorInlineUniformBlocks = proto.maxperstagedescriptorinlineuniformblocks();
  original_struct.maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks = proto.maxperstagedescriptorupdateafterbindinlineuniformblocks();
  original_struct.maxDescriptorSetInlineUniformBlocks = proto.maxdescriptorsetinlineuniformblocks();
  original_struct.maxDescriptorSetUpdateAfterBindInlineUniformBlocks = proto.maxdescriptorsetupdateafterbindinlineuniformblocks();
  original_struct.maxInlineUniformTotalSize = proto.maxinlineuniformtotalsize();
  original_struct.integerDotProduct8BitUnsignedAccelerated = proto.integerdotproduct8bitunsignedaccelerated();
  original_struct.integerDotProduct8BitSignedAccelerated = proto.integerdotproduct8bitsignedaccelerated();
  original_struct.integerDotProduct8BitMixedSignednessAccelerated = proto.integerdotproduct8bitmixedsignednessaccelerated();
  original_struct.integerDotProduct4x8BitPackedUnsignedAccelerated = proto.integerdotproduct4x8bitpackedunsignedaccelerated();
  original_struct.integerDotProduct4x8BitPackedSignedAccelerated = proto.integerdotproduct4x8bitpackedsignedaccelerated();
  original_struct.integerDotProduct4x8BitPackedMixedSignednessAccelerated = proto.integerdotproduct4x8bitpackedmixedsignednessaccelerated();
  original_struct.integerDotProduct16BitUnsignedAccelerated = proto.integerdotproduct16bitunsignedaccelerated();
  original_struct.integerDotProduct16BitSignedAccelerated = proto.integerdotproduct16bitsignedaccelerated();
  original_struct.integerDotProduct16BitMixedSignednessAccelerated = proto.integerdotproduct16bitmixedsignednessaccelerated();
  original_struct.integerDotProduct32BitUnsignedAccelerated = proto.integerdotproduct32bitunsignedaccelerated();
  original_struct.integerDotProduct32BitSignedAccelerated = proto.integerdotproduct32bitsignedaccelerated();
  original_struct.integerDotProduct32BitMixedSignednessAccelerated = proto.integerdotproduct32bitmixedsignednessaccelerated();
  original_struct.integerDotProduct64BitUnsignedAccelerated = proto.integerdotproduct64bitunsignedaccelerated();
  original_struct.integerDotProduct64BitSignedAccelerated = proto.integerdotproduct64bitsignedaccelerated();
  original_struct.integerDotProduct64BitMixedSignednessAccelerated = proto.integerdotproduct64bitmixedsignednessaccelerated();
  original_struct.integerDotProductAccumulatingSaturating8BitUnsignedAccelerated = proto.integerdotproductaccumulatingsaturating8bitunsignedaccelerated();
  original_struct.integerDotProductAccumulatingSaturating8BitSignedAccelerated = proto.integerdotproductaccumulatingsaturating8bitsignedaccelerated();
  original_struct.integerDotProductAccumulatingSaturating8BitMixedSignednessAccelerated = proto.integerdotproductaccumulatingsaturating8bitmixedsignednessaccelerated();
  original_struct.integerDotProductAccumulatingSaturating4x8BitPackedUnsignedAccelerated = proto.integerdotproductaccumulatingsaturating4x8bitpackedunsignedaccelerated();
  original_struct.integerDotProductAccumulatingSaturating4x8BitPackedSignedAccelerated = proto.integerdotproductaccumulatingsaturating4x8bitpackedsignedaccelerated();
  original_struct.integerDotProductAccumulatingSaturating4x8BitPackedMixedSignednessAccelerated = proto.integerdotproductaccumulatingsaturating4x8bitpackedmixedsignednessaccelerated();
  original_struct.integerDotProductAccumulatingSaturating16BitUnsignedAccelerated = proto.integerdotproductaccumulatingsaturating16bitunsignedaccelerated();
  original_struct.integerDotProductAccumulatingSaturating16BitSignedAccelerated = proto.integerdotproductaccumulatingsaturating16bitsignedaccelerated();
  original_struct.integerDotProductAccumulatingSaturating16BitMixedSignednessAccelerated = proto.integerdotproductaccumulatingsaturating16bitmixedsignednessaccelerated();
  original_struct.integerDotProductAccumulatingSaturating32BitUnsignedAccelerated = proto.integerdotproductaccumulatingsaturating32bitunsignedaccelerated();
  original_struct.integerDotProductAccumulatingSaturating32BitSignedAccelerated = proto.integerdotproductaccumulatingsaturating32bitsignedaccelerated();
  original_struct.integerDotProductAccumulatingSaturating32BitMixedSignednessAccelerated = proto.integerdotproductaccumulatingsaturating32bitmixedsignednessaccelerated();
  original_struct.integerDotProductAccumulatingSaturating64BitUnsignedAccelerated = proto.integerdotproductaccumulatingsaturating64bitunsignedaccelerated();
  original_struct.integerDotProductAccumulatingSaturating64BitSignedAccelerated = proto.integerdotproductaccumulatingsaturating64bitsignedaccelerated();
  original_struct.integerDotProductAccumulatingSaturating64BitMixedSignednessAccelerated = proto.integerdotproductaccumulatingsaturating64bitmixedsignednessaccelerated();
  original_struct.storageTexelBufferOffsetAlignmentBytes = static_cast<VkDeviceSize>(proto.storagetexelbufferoffsetalignmentbytes());
  original_struct.storageTexelBufferOffsetSingleTexelAlignment = proto.storagetexelbufferoffsetsingletexelalignment();
  original_struct.uniformTexelBufferOffsetAlignmentBytes = static_cast<VkDeviceSize>(proto.uniformtexelbufferoffsetalignmentbytes());
  original_struct.uniformTexelBufferOffsetSingleTexelAlignment = proto.uniformtexelbufferoffsetsingletexelalignment();
  original_struct.maxBufferSize = static_cast<VkDeviceSize>(proto.maxbuffersize());
}
void FillStructFromProtoNoPNext(VkPhysicalDeviceVulkan14Features& original_struct, const vvk::server::VkPhysicalDeviceVulkan14Features& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES;
  original_struct.globalPriorityQuery = proto.globalpriorityquery();
  original_struct.shaderSubgroupRotate = proto.shadersubgrouprotate();
  original_struct.shaderSubgroupRotateClustered = proto.shadersubgrouprotateclustered();
  original_struct.shaderFloatControls2 = proto.shaderfloatcontrols2();
  original_struct.shaderExpectAssume = proto.shaderexpectassume();
  original_struct.rectangularLines = proto.rectangularlines();
  original_struct.bresenhamLines = proto.bresenhamlines();
  original_struct.smoothLines = proto.smoothlines();
  original_struct.stippledRectangularLines = proto.stippledrectangularlines();
  original_struct.stippledBresenhamLines = proto.stippledbresenhamlines();
  original_struct.stippledSmoothLines = proto.stippledsmoothlines();
  original_struct.vertexAttributeInstanceRateDivisor = proto.vertexattributeinstanceratedivisor();
  original_struct.vertexAttributeInstanceRateZeroDivisor = proto.vertexattributeinstanceratezerodivisor();
  original_struct.indexTypeUint8 = proto.indextypeuint8();
  original_struct.dynamicRenderingLocalRead = proto.dynamicrenderinglocalread();
  original_struct.maintenance5 = proto.maintenance5();
  original_struct.maintenance6 = proto.maintenance6();
  original_struct.pipelineProtectedAccess = proto.pipelineprotectedaccess();
  original_struct.pipelineRobustness = proto.pipelinerobustness();
  original_struct.hostImageCopy = proto.hostimagecopy();
  original_struct.pushDescriptor = proto.pushdescriptor();
}
void FillStructFromProtoNoPNext(VkPhysicalDeviceVulkan14Properties& original_struct, const vvk::server::VkPhysicalDeviceVulkan14Properties& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_PROPERTIES;
  original_struct.lineSubPixelPrecisionBits = proto.linesubpixelprecisionbits();
  original_struct.maxVertexAttribDivisor = proto.maxvertexattribdivisor();
  original_struct.supportsNonZeroFirstInstance = proto.supportsnonzerofirstinstance();
  original_struct.maxPushDescriptors = proto.maxpushdescriptors();
  original_struct.dynamicRenderingLocalReadDepthStencilAttachments = proto.dynamicrenderinglocalreaddepthstencilattachments();
  original_struct.dynamicRenderingLocalReadMultisampledAttachments = proto.dynamicrenderinglocalreadmultisampledattachments();
  original_struct.earlyFragmentMultisampleCoverageAfterSampleCounting = proto.earlyfragmentmultisamplecoverageaftersamplecounting();
  original_struct.earlyFragmentSampleMaskTestBeforeSampleCounting = proto.earlyfragmentsamplemasktestbeforesamplecounting();
  original_struct.depthStencilSwizzleOneSupport = proto.depthstencilswizzleonesupport();
  original_struct.polygonModePointSize = proto.polygonmodepointsize();
  original_struct.nonStrictSinglePixelWideLinesUseParallelogram = proto.nonstrictsinglepixelwidelinesuseparallelogram();
  original_struct.nonStrictWideLinesUseParallelogram = proto.nonstrictwidelinesuseparallelogram();
  original_struct.blockTexelViewCompatibleMultipleLayers = proto.blocktexelviewcompatiblemultiplelayers();
  original_struct.maxCombinedImageSamplerDescriptorCount = proto.maxcombinedimagesamplerdescriptorcount();
  original_struct.fragmentShadingRateClampCombinerInputs = proto.fragmentshadingrateclampcombinerinputs();
  original_struct.defaultRobustnessStorageBuffers = static_cast<VkPipelineRobustnessBufferBehavior>(proto.defaultrobustnessstoragebuffers());
  original_struct.defaultRobustnessUniformBuffers = static_cast<VkPipelineRobustnessBufferBehavior>(proto.defaultrobustnessuniformbuffers());
  original_struct.defaultRobustnessVertexInputs = static_cast<VkPipelineRobustnessBufferBehavior>(proto.defaultrobustnessvertexinputs());
  original_struct.defaultRobustnessImages = static_cast<VkPipelineRobustnessImageBehavior>(proto.defaultrobustnessimages());
  if (proto.has_copysrclayoutcount()) {
    original_struct.copySrcLayoutCount = proto.copysrclayoutcount();
  } else {
    original_struct.copySrcLayoutCount = uint32_t{};
  }
  if (proto.pcopysrclayouts_size()) {
    original_struct.pCopySrcLayouts = reinterpret_cast<VkImageLayout*>(const_cast<vvk::server::VkPhysicalDeviceVulkan14Properties&>(proto).mutable_pcopysrclayouts()->mutable_data());
  } else {
    original_struct.pCopySrcLayouts = nullptr;
  }
  if (proto.has_copydstlayoutcount()) {
    original_struct.copyDstLayoutCount = proto.copydstlayoutcount();
  } else {
    original_struct.copyDstLayoutCount = uint32_t{};
  }
  if (proto.pcopydstlayouts_size()) {
    original_struct.pCopyDstLayouts = reinterpret_cast<VkImageLayout*>(const_cast<vvk::server::VkPhysicalDeviceVulkan14Properties&>(proto).mutable_pcopydstlayouts()->mutable_data());
  } else {
    original_struct.pCopyDstLayouts = nullptr;
  }
  if (proto.optimaltilinglayoutuuid_size()) {
    const size_t original_struct_optimalTilingLayoutUUID_length = std::min(VK_UUID_SIZE, VK_UUID_SIZE);
    for (uint32_t optimalTilingLayoutUUID_indx = 0; optimalTilingLayoutUUID_indx < original_struct_optimalTilingLayoutUUID_length; optimalTilingLayoutUUID_indx++) {
      original_struct.optimalTilingLayoutUUID[optimalTilingLayoutUUID_indx] = static_cast<uint8_t>(proto.optimaltilinglayoutuuid(optimalTilingLayoutUUID_indx));
    }
  } else {
    // this should not be reached
    std::exit(EXIT_FAILURE);
  }
  original_struct.identicalMemoryTypeRequirements = proto.identicalmemorytyperequirements();
}
void FillStructFromProtoNoPNext(VkProtectedSubmitInfo& original_struct, const vvk::server::VkProtectedSubmitInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO;
  original_struct.protectedSubmit = proto.protectedsubmit();
}
void FillStructFromProtoNoPNext(VkSemaphoreTypeCreateInfo& original_struct, const vvk::server::VkSemaphoreTypeCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO;
  original_struct.semaphoreType = static_cast<VkSemaphoreType>(proto.semaphoretype());
  original_struct.initialValue = proto.initialvalue();
}
void FillStructFromProtoNoPNext(VkShaderModuleCreateInfo& original_struct, const vvk::server::VkShaderModuleCreateInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  if (proto.has_flags()) {
    original_struct.flags = static_cast<VkShaderModuleCreateFlags>(proto.flags());
  } else {
    original_struct.flags = VkShaderModuleCreateFlags{};
  }
  original_struct.codeSize = proto.codesize();
  uint32_t* original_struct_pCode = new uint32_t[proto.pcode_size()]();
  original_struct.pCode = original_struct_pCode;
  for (int pCode_indx = 0; pCode_indx < proto.pcode_size(); pCode_indx++) {
    original_struct_pCode[pCode_indx] = proto.pcode(pCode_indx);
  }
}
void FillStructFromProtoNoPNext(VkTimelineSemaphoreSubmitInfo& original_struct, const vvk::server::VkTimelineSemaphoreSubmitInfo& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO;
  if (proto.has_waitsemaphorevaluecount()) {
    original_struct.waitSemaphoreValueCount = proto.waitsemaphorevaluecount();
  } else {
    original_struct.waitSemaphoreValueCount = uint32_t{};
  }
  uint64_t* original_struct_pWaitSemaphoreValues = new uint64_t[proto.pwaitsemaphorevalues_size()]();
  original_struct.pWaitSemaphoreValues = original_struct_pWaitSemaphoreValues;
  if (proto.pwaitsemaphorevalues_size()) {
    for (int pWaitSemaphoreValues_indx = 0; pWaitSemaphoreValues_indx < proto.pwaitsemaphorevalues_size(); pWaitSemaphoreValues_indx++) {
      original_struct_pWaitSemaphoreValues[pWaitSemaphoreValues_indx] = proto.pwaitsemaphorevalues(pWaitSemaphoreValues_indx);
    }
  } else {
    original_struct.pWaitSemaphoreValues = nullptr;
  }
  if (proto.has_signalsemaphorevaluecount()) {
    original_struct.signalSemaphoreValueCount = proto.signalsemaphorevaluecount();
  } else {
    original_struct.signalSemaphoreValueCount = uint32_t{};
  }
  uint64_t* original_struct_pSignalSemaphoreValues = new uint64_t[proto.psignalsemaphorevalues_size()]();
  original_struct.pSignalSemaphoreValues = original_struct_pSignalSemaphoreValues;
  if (proto.psignalsemaphorevalues_size()) {
    for (int pSignalSemaphoreValues_indx = 0; pSignalSemaphoreValues_indx < proto.psignalsemaphorevalues_size(); pSignalSemaphoreValues_indx++) {
      original_struct_pSignalSemaphoreValues[pSignalSemaphoreValues_indx] = proto.psignalsemaphorevalues(pSignalSemaphoreValues_indx);
    }
  } else {
    original_struct.pSignalSemaphoreValues = nullptr;
  }
}
}
void UnpackAndExecuteVkCreateInstance(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateInstance");

  VkInstanceCreateInfo pCreateInfo = {};
  FillStructFromProto(pCreateInfo, request.vkcreateinstance().pcreateinfo());
  VkInstance server_pInstance;
  VkResult result = vkCreateInstance(&pCreateInfo, nullptr, &server_pInstance);
  response->mutable_vkcreateinstance()->set_pinstance(reinterpret_cast<uint64_t>(server_pInstance));
  response->mutable_vkcreateinstance()->set_result(static_cast<vvk::server::VkResult>(result));
  if (request.vkcreateinstance().pcreateinfo().has_papplicationinfo()) {
    const VkApplicationInfo &pCreateInfo_pApplicationInfo = *pCreateInfo.pApplicationInfo;
    delete pCreateInfo.pApplicationInfo;
  }
  delete[] pCreateInfo.ppEnabledLayerNames;
  delete[] pCreateInfo.ppEnabledExtensionNames;
}
void UnpackAndExecuteVkDestroyInstance(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyInstance");

  context.instance_dispatch_table().DestroyInstance(reinterpret_cast<VkInstance>(request.vkdestroyinstance().instance()), nullptr);
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
  VkResult result = context.instance_dispatch_table().EnumeratePhysicalDevices(reinterpret_cast<VkInstance>(request.vkenumeratephysicaldevices().instance()), &pPhysicalDeviceCount, pPhysicalDevices);
  response->mutable_vkenumeratephysicaldevices()->set_pphysicaldevicecount(pPhysicalDeviceCount);
  if (request.vkenumeratephysicaldevices().pphysicaldevicecount() != 0) {
    for (uint32_t pPhysicalDevices_index = 0; pPhysicalDevices_index < pPhysicalDeviceCount; pPhysicalDevices_index++) {
      response->mutable_vkenumeratephysicaldevices()->add_pphysicaldevices(reinterpret_cast<uint64_t>(pPhysicalDevices[pPhysicalDevices_index]));
    }
  }
  response->mutable_vkenumeratephysicaldevices()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkGetPhysicalDeviceProperties(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkGetPhysicalDeviceProperties");

  VkPhysicalDeviceProperties pProperties = {};
  FillStructFromProto(pProperties, request.vkgetphysicaldeviceproperties().pproperties());
  context.instance_dispatch_table().GetPhysicalDeviceProperties(context.physical_device(), &pProperties);
  FillProtoFromStruct(response->mutable_vkgetphysicaldeviceproperties()->mutable_pproperties(), &pProperties);
}
void UnpackAndExecuteVkGetPhysicalDeviceFormatProperties(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkGetPhysicalDeviceFormatProperties");

  VkFormatProperties pFormatProperties = {};
  FillStructFromProto(pFormatProperties, request.vkgetphysicaldeviceformatproperties().pformatproperties());
  context.instance_dispatch_table().GetPhysicalDeviceFormatProperties(context.physical_device(), static_cast<VkFormat>(request.vkgetphysicaldeviceformatproperties().format()), &pFormatProperties);
  FillProtoFromStruct(response->mutable_vkgetphysicaldeviceformatproperties()->mutable_pformatproperties(), &pFormatProperties);
}
void UnpackAndExecuteVkCreateDevice(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateDevice");

  VkDeviceCreateInfo pCreateInfo = {};
  FillStructFromProto(pCreateInfo, request.vkcreatedevice().pcreateinfo());
  VkDevice server_pDevice;
  VkResult result = context.instance_dispatch_table().CreateDevice(context.physical_device(), &pCreateInfo, nullptr, &server_pDevice);
  response->mutable_vkcreatedevice()->set_pdevice(reinterpret_cast<uint64_t>(server_pDevice));
  response->mutable_vkcreatedevice()->set_result(static_cast<vvk::server::VkResult>(result));
  for (int pQueueCreateInfos_indx = 0; pQueueCreateInfos_indx < request.vkcreatedevice().pcreateinfo().pqueuecreateinfos_size(); pQueueCreateInfos_indx++)  {
    const VkDeviceQueueCreateInfo &pCreateInfo_pQueueCreateInfos_i = pCreateInfo.pQueueCreateInfos[pQueueCreateInfos_indx];
    delete[] pCreateInfo_pQueueCreateInfos_i.pQueuePriorities;
  }
  delete[] pCreateInfo.pQueueCreateInfos;
  delete[] pCreateInfo.ppEnabledLayerNames;
  delete[] pCreateInfo.ppEnabledExtensionNames;
  if (request.vkcreatedevice().pcreateinfo().has_penabledfeatures()) {
    const VkPhysicalDeviceFeatures &pCreateInfo_pEnabledFeatures = *pCreateInfo.pEnabledFeatures;
    delete pCreateInfo.pEnabledFeatures;
  }
}
void UnpackAndExecuteVkDestroyDevice(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyDevice");

  context.device_dispatch_table().DestroyDevice(reinterpret_cast<VkDevice>(request.vkdestroydevice().device()), nullptr);
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
    for (uint32_t pProperties_index = 0; pProperties_index < pPropertyCount; pProperties_index++) {
      FillProtoFromStruct(response->mutable_vkenumerateinstanceextensionproperties()->add_pproperties(), &pProperties[pProperties_index]);
    }
  }
  response->mutable_vkenumerateinstanceextensionproperties()->set_result(static_cast<vvk::server::VkResult>(result));
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
  VkResult result = context.instance_dispatch_table().EnumerateDeviceExtensionProperties(context.physical_device(), request.vkenumeratedeviceextensionproperties().playername().data(), &pPropertyCount, pProperties);
  response->mutable_vkenumeratedeviceextensionproperties()->set_ppropertycount(pPropertyCount);
  if (request.vkenumeratedeviceextensionproperties().ppropertycount() != 0) {
    for (uint32_t pProperties_index = 0; pProperties_index < pPropertyCount; pProperties_index++) {
      FillProtoFromStruct(response->mutable_vkenumeratedeviceextensionproperties()->add_pproperties(), &pProperties[pProperties_index]);
    }
  }
  response->mutable_vkenumeratedeviceextensionproperties()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkGetPhysicalDeviceMemoryProperties(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkGetPhysicalDeviceMemoryProperties");

  VkPhysicalDeviceMemoryProperties pMemoryProperties = {};
  FillStructFromProto(pMemoryProperties, request.vkgetphysicaldevicememoryproperties().pmemoryproperties());
  context.instance_dispatch_table().GetPhysicalDeviceMemoryProperties(context.physical_device(), &pMemoryProperties);
  FillProtoFromStruct(response->mutable_vkgetphysicaldevicememoryproperties()->mutable_pmemoryproperties(), &pMemoryProperties);
}
void UnpackAndExecuteVkGetPhysicalDeviceFeatures(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkGetPhysicalDeviceFeatures");

  VkPhysicalDeviceFeatures pFeatures = {};
  FillStructFromProto(pFeatures, request.vkgetphysicaldevicefeatures().pfeatures());
  context.instance_dispatch_table().GetPhysicalDeviceFeatures(context.physical_device(), &pFeatures);
  FillProtoFromStruct(response->mutable_vkgetphysicaldevicefeatures()->mutable_pfeatures(), &pFeatures);
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
  context.instance_dispatch_table().GetPhysicalDeviceQueueFamilyProperties(context.physical_device(), &pQueueFamilyPropertyCount, pQueueFamilyProperties);
  response->mutable_vkgetphysicaldevicequeuefamilyproperties()->set_pqueuefamilypropertycount(pQueueFamilyPropertyCount);
  if (request.vkgetphysicaldevicequeuefamilyproperties().pqueuefamilypropertycount() != 0) {
    for (uint32_t pQueueFamilyProperties_index = 0; pQueueFamilyProperties_index < pQueueFamilyPropertyCount; pQueueFamilyProperties_index++) {
      FillProtoFromStruct(response->mutable_vkgetphysicaldevicequeuefamilyproperties()->add_pqueuefamilyproperties(), &pQueueFamilyProperties[pQueueFamilyProperties_index]);
    }
  }
}
void UnpackAndExecuteVkGetDeviceQueue(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkGetDeviceQueue");

  VkQueue server_pQueue;
  context.device_dispatch_table().GetDeviceQueue(reinterpret_cast<VkDevice>(request.vkgetdevicequeue().device()), request.vkgetdevicequeue().queuefamilyindex(), request.vkgetdevicequeue().queueindex(), &server_pQueue);
  response->mutable_vkgetdevicequeue()->set_pqueue(reinterpret_cast<uint64_t>(server_pQueue));
}
void UnpackAndExecuteVkCreateFence(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateFence");

  VkFenceCreateInfo pCreateInfo = {};
  FillStructFromProto(pCreateInfo, request.vkcreatefence().pcreateinfo());
  VkFence server_pFence;
  VkResult result = context.device_dispatch_table().CreateFence(reinterpret_cast<VkDevice>(request.vkcreatefence().device()), &pCreateInfo, nullptr, &server_pFence);
  response->mutable_vkcreatefence()->set_pfence(reinterpret_cast<uint64_t>(server_pFence));
  response->mutable_vkcreatefence()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkDestroyFence(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyFence");

  context.device_dispatch_table().DestroyFence(reinterpret_cast<VkDevice>(request.vkdestroyfence().device()), reinterpret_cast<VkFence>(request.vkdestroyfence().fence()), nullptr);
}
void UnpackAndExecuteVkCreateSemaphore(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateSemaphore");

  VkSemaphoreCreateInfo pCreateInfo = {};
  FillStructFromProto(pCreateInfo, request.vkcreatesemaphore().pcreateinfo());
  VkSemaphore server_pSemaphore;
  VkResult result = context.device_dispatch_table().CreateSemaphore(reinterpret_cast<VkDevice>(request.vkcreatesemaphore().device()), &pCreateInfo, nullptr, &server_pSemaphore);
  response->mutable_vkcreatesemaphore()->set_psemaphore(reinterpret_cast<uint64_t>(server_pSemaphore));
  response->mutable_vkcreatesemaphore()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkDestroySemaphore(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroySemaphore");

  context.device_dispatch_table().DestroySemaphore(reinterpret_cast<VkDevice>(request.vkdestroysemaphore().device()), reinterpret_cast<VkSemaphore>(request.vkdestroysemaphore().semaphore()), nullptr);
}
void UnpackAndExecuteVkAllocateMemory(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkAllocateMemory");

  VkMemoryAllocateInfo pAllocateInfo = {};
  FillStructFromProto(pAllocateInfo, request.vkallocatememory().pallocateinfo());
  VkDeviceMemory server_pMemory;
  VkResult result = context.device_dispatch_table().AllocateMemory(reinterpret_cast<VkDevice>(request.vkallocatememory().device()), &pAllocateInfo, nullptr, &server_pMemory);
  response->mutable_vkallocatememory()->set_pmemory(reinterpret_cast<uint64_t>(server_pMemory));
  response->mutable_vkallocatememory()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkFreeMemory(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkFreeMemory");

  context.device_dispatch_table().FreeMemory(reinterpret_cast<VkDevice>(request.vkfreememory().device()), reinterpret_cast<VkDeviceMemory>(request.vkfreememory().memory()), nullptr);
}
void UnpackAndExecuteVkCreateImage(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateImage");

  VkImageCreateInfo pCreateInfo = {};
  FillStructFromProto(pCreateInfo, request.vkcreateimage().pcreateinfo());
  VkImage server_pImage;
  VkResult result = context.device_dispatch_table().CreateImage(reinterpret_cast<VkDevice>(request.vkcreateimage().device()), &pCreateInfo, nullptr, &server_pImage);
  response->mutable_vkcreateimage()->set_pimage(reinterpret_cast<uint64_t>(server_pImage));
  response->mutable_vkcreateimage()->set_result(static_cast<vvk::server::VkResult>(result));
  delete[] pCreateInfo.pQueueFamilyIndices;
}
void UnpackAndExecuteVkDestroyImage(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyImage");

  context.device_dispatch_table().DestroyImage(reinterpret_cast<VkDevice>(request.vkdestroyimage().device()), reinterpret_cast<VkImage>(request.vkdestroyimage().image()), nullptr);
}
void UnpackAndExecuteVkBindImageMemory(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkBindImageMemory");

  VkResult result = context.device_dispatch_table().BindImageMemory(reinterpret_cast<VkDevice>(request.vkbindimagememory().device()), reinterpret_cast<VkImage>(request.vkbindimagememory().image()), reinterpret_cast<VkDeviceMemory>(request.vkbindimagememory().memory()), static_cast<VkDeviceSize>(request.vkbindimagememory().memoryoffset()));
  response->mutable_vkbindimagememory()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkBindImageMemory2(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkBindImageMemory2");

  std::vector<VkBindImageMemoryInfo> pBindInfos(request.vkbindimagememory2().bindinfocount());
  for (uint32_t i = 0; i < pBindInfos.size(); i++) {
    FillStructFromProto(pBindInfos[i], request.vkbindimagememory2().pbindinfos(i));
  }
  VkResult result = context.device_dispatch_table().BindImageMemory2(reinterpret_cast<VkDevice>(request.vkbindimagememory2().device()), request.vkbindimagememory2().bindinfocount(), pBindInfos.data());
  response->mutable_vkbindimagememory2()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkGetImageMemoryRequirements(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkGetImageMemoryRequirements");

  VkMemoryRequirements pMemoryRequirements = {};
  FillStructFromProto(pMemoryRequirements, request.vkgetimagememoryrequirements().pmemoryrequirements());
  context.device_dispatch_table().GetImageMemoryRequirements(reinterpret_cast<VkDevice>(request.vkgetimagememoryrequirements().device()), reinterpret_cast<VkImage>(request.vkgetimagememoryrequirements().image()), &pMemoryRequirements);
  FillProtoFromStruct(response->mutable_vkgetimagememoryrequirements()->mutable_pmemoryrequirements(), &pMemoryRequirements);
}
void UnpackAndExecuteVkGetImageMemoryRequirements2(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkGetImageMemoryRequirements2");

  VkImageMemoryRequirementsInfo2 pInfo = {};
  FillStructFromProto(pInfo, request.vkgetimagememoryrequirements2().pinfo());
  VkMemoryRequirements2 pMemoryRequirements = {};
  FillStructFromProto(pMemoryRequirements, request.vkgetimagememoryrequirements2().pmemoryrequirements());
  context.device_dispatch_table().GetImageMemoryRequirements2(reinterpret_cast<VkDevice>(request.vkgetimagememoryrequirements2().device()), &pInfo, &pMemoryRequirements);
  FillProtoFromStruct(response->mutable_vkgetimagememoryrequirements2()->mutable_pmemoryrequirements(), &pMemoryRequirements);
}
void UnpackAndExecuteVkCreateImageView(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateImageView");

  VkImageViewCreateInfo pCreateInfo = {};
  FillStructFromProto(pCreateInfo, request.vkcreateimageview().pcreateinfo());
  VkImageView server_pView;
  VkResult result = context.device_dispatch_table().CreateImageView(reinterpret_cast<VkDevice>(request.vkcreateimageview().device()), &pCreateInfo, nullptr, &server_pView);
  response->mutable_vkcreateimageview()->set_pview(reinterpret_cast<uint64_t>(server_pView));
  response->mutable_vkcreateimageview()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkDestroyImageView(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyImageView");

  context.device_dispatch_table().DestroyImageView(reinterpret_cast<VkDevice>(request.vkdestroyimageview().device()), reinterpret_cast<VkImageView>(request.vkdestroyimageview().imageview()), nullptr);
}
void UnpackAndExecuteVkCreateCommandPool(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateCommandPool");

  VkCommandPoolCreateInfo pCreateInfo = {};
  FillStructFromProto(pCreateInfo, request.vkcreatecommandpool().pcreateinfo());
  VkCommandPool server_pCommandPool;
  VkResult result = context.device_dispatch_table().CreateCommandPool(reinterpret_cast<VkDevice>(request.vkcreatecommandpool().device()), &pCreateInfo, nullptr, &server_pCommandPool);
  response->mutable_vkcreatecommandpool()->set_pcommandpool(reinterpret_cast<uint64_t>(server_pCommandPool));
  response->mutable_vkcreatecommandpool()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkDestroyCommandPool(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyCommandPool");

  context.device_dispatch_table().DestroyCommandPool(reinterpret_cast<VkDevice>(request.vkdestroycommandpool().device()), reinterpret_cast<VkCommandPool>(request.vkdestroycommandpool().commandpool()), nullptr);
}
void UnpackAndExecuteVkAllocateCommandBuffers(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkAllocateCommandBuffers");

  VkCommandBufferAllocateInfo pAllocateInfo = {};
  FillStructFromProto(pAllocateInfo, request.vkallocatecommandbuffers().pallocateinfo());
  std::vector<VkCommandBuffer> pCommandBuffers(request.vkallocatecommandbuffers().pallocateinfo().commandbuffercount());
  VkResult result = context.device_dispatch_table().AllocateCommandBuffers(reinterpret_cast<VkDevice>(request.vkallocatecommandbuffers().device()), &pAllocateInfo, pCommandBuffers.data());
  for (VkCommandBuffer pCommandBuffers_elem : pCommandBuffers) {
    response->mutable_vkallocatecommandbuffers()->add_pcommandbuffers(reinterpret_cast<uint64_t>(pCommandBuffers_elem));
  }
  response->mutable_vkallocatecommandbuffers()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkFreeCommandBuffers(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkFreeCommandBuffers");

  context.device_dispatch_table().FreeCommandBuffers(reinterpret_cast<VkDevice>(request.vkfreecommandbuffers().device()), reinterpret_cast<VkCommandPool>(request.vkfreecommandbuffers().commandpool()), request.vkfreecommandbuffers().commandbuffercount(), reinterpret_cast<const VkCommandBuffer*>(request.vkfreecommandbuffers().pcommandbuffers().data()));
}
void UnpackAndExecuteVkBeginCommandBuffer(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkBeginCommandBuffer");

  VkCommandBufferBeginInfo pBeginInfo = {};
  FillStructFromProto(pBeginInfo, request.vkbegincommandbuffer().pbegininfo());
  VkResult result = context.device_dispatch_table().BeginCommandBuffer(reinterpret_cast<VkCommandBuffer>(request.vkbegincommandbuffer().commandbuffer()), &pBeginInfo);
  response->mutable_vkbegincommandbuffer()->set_result(static_cast<vvk::server::VkResult>(result));
  if (request.vkbegincommandbuffer().pbegininfo().has_pinheritanceinfo()) {
    const VkCommandBufferInheritanceInfo &pBeginInfo_pInheritanceInfo = *pBeginInfo.pInheritanceInfo;
    delete pBeginInfo.pInheritanceInfo;
  }
}
void UnpackAndExecuteVkEndCommandBuffer(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkEndCommandBuffer");

  VkResult result = context.device_dispatch_table().EndCommandBuffer(reinterpret_cast<VkCommandBuffer>(request.vkendcommandbuffer().commandbuffer()));
  response->mutable_vkendcommandbuffer()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkGetImageSubresourceLayout(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkGetImageSubresourceLayout");

  VkImageSubresource pSubresource = {};
  FillStructFromProto(pSubresource, request.vkgetimagesubresourcelayout().psubresource());
  VkSubresourceLayout pLayout = {};
  FillStructFromProto(pLayout, request.vkgetimagesubresourcelayout().playout());
  context.device_dispatch_table().GetImageSubresourceLayout(reinterpret_cast<VkDevice>(request.vkgetimagesubresourcelayout().device()), reinterpret_cast<VkImage>(request.vkgetimagesubresourcelayout().image()), &pSubresource, &pLayout);
  FillProtoFromStruct(response->mutable_vkgetimagesubresourcelayout()->mutable_playout(), &pLayout);
}
void UnpackAndExecuteVkCreateRenderPass(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateRenderPass");

  VkRenderPassCreateInfo pCreateInfo = {};
  FillStructFromProto(pCreateInfo, request.vkcreaterenderpass().pcreateinfo());
  VkRenderPass server_pRenderPass;
  VkResult result = context.device_dispatch_table().CreateRenderPass(reinterpret_cast<VkDevice>(request.vkcreaterenderpass().device()), &pCreateInfo, nullptr, &server_pRenderPass);
  response->mutable_vkcreaterenderpass()->set_prenderpass(reinterpret_cast<uint64_t>(server_pRenderPass));
  response->mutable_vkcreaterenderpass()->set_result(static_cast<vvk::server::VkResult>(result));
  delete[] pCreateInfo.pAttachments;
  for (int pSubpasses_indx = 0; pSubpasses_indx < request.vkcreaterenderpass().pcreateinfo().psubpasses_size(); pSubpasses_indx++)  {
    const VkSubpassDescription &pCreateInfo_pSubpasses_i = pCreateInfo.pSubpasses[pSubpasses_indx];
    delete[] pCreateInfo_pSubpasses_i.pInputAttachments;
    delete[] pCreateInfo_pSubpasses_i.pColorAttachments;
    delete[] pCreateInfo_pSubpasses_i.pResolveAttachments;
    if (request.vkcreaterenderpass().pcreateinfo().psubpasses(pSubpasses_indx).has_pdepthstencilattachment()) {
      const VkAttachmentReference &pCreateInfo_pSubpasses_i_pDepthStencilAttachment = *pCreateInfo_pSubpasses_i.pDepthStencilAttachment;
      delete pCreateInfo_pSubpasses_i.pDepthStencilAttachment;
    }
    delete[] pCreateInfo_pSubpasses_i.pPreserveAttachments;
  }
  delete[] pCreateInfo.pSubpasses;
  delete[] pCreateInfo.pDependencies;
}
void UnpackAndExecuteVkDestroyRenderPass(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyRenderPass");

  context.device_dispatch_table().DestroyRenderPass(reinterpret_cast<VkDevice>(request.vkdestroyrenderpass().device()), reinterpret_cast<VkRenderPass>(request.vkdestroyrenderpass().renderpass()), nullptr);
}
void UnpackAndExecuteVkCreatePipelineLayout(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreatePipelineLayout");

  VkPipelineLayoutCreateInfo pCreateInfo = {};
  FillStructFromProto(pCreateInfo, request.vkcreatepipelinelayout().pcreateinfo());
  VkPipelineLayout server_pPipelineLayout;
  VkResult result = context.device_dispatch_table().CreatePipelineLayout(reinterpret_cast<VkDevice>(request.vkcreatepipelinelayout().device()), &pCreateInfo, nullptr, &server_pPipelineLayout);
  response->mutable_vkcreatepipelinelayout()->set_ppipelinelayout(reinterpret_cast<uint64_t>(server_pPipelineLayout));
  response->mutable_vkcreatepipelinelayout()->set_result(static_cast<vvk::server::VkResult>(result));
  delete[] pCreateInfo.pPushConstantRanges;
}
void UnpackAndExecuteVkDestroyPipelineLayout(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyPipelineLayout");

  context.device_dispatch_table().DestroyPipelineLayout(reinterpret_cast<VkDevice>(request.vkdestroypipelinelayout().device()), reinterpret_cast<VkPipelineLayout>(request.vkdestroypipelinelayout().pipelinelayout()), nullptr);
}
void UnpackAndExecuteVkCreateShaderModule(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateShaderModule");

  VkShaderModuleCreateInfo pCreateInfo = {};
  FillStructFromProto(pCreateInfo, request.vkcreateshadermodule().pcreateinfo());
  VkShaderModule server_pShaderModule;
  VkResult result = context.device_dispatch_table().CreateShaderModule(reinterpret_cast<VkDevice>(request.vkcreateshadermodule().device()), &pCreateInfo, nullptr, &server_pShaderModule);
  response->mutable_vkcreateshadermodule()->set_pshadermodule(reinterpret_cast<uint64_t>(server_pShaderModule));
  response->mutable_vkcreateshadermodule()->set_result(static_cast<vvk::server::VkResult>(result));
  delete[] pCreateInfo.pCode;
}
void UnpackAndExecuteVkDestroyShaderModule(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyShaderModule");

  context.device_dispatch_table().DestroyShaderModule(reinterpret_cast<VkDevice>(request.vkdestroyshadermodule().device()), reinterpret_cast<VkShaderModule>(request.vkdestroyshadermodule().shadermodule()), nullptr);
}
void UnpackAndExecuteVkCreateGraphicsPipelines(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateGraphicsPipelines");

  std::vector<VkGraphicsPipelineCreateInfo> pCreateInfos(request.vkcreategraphicspipelines().createinfocount());
  for (uint32_t i = 0; i < pCreateInfos.size(); i++) {
    FillStructFromProto(pCreateInfos[i], request.vkcreategraphicspipelines().pcreateinfos(i));
  }
  std::vector<VkPipeline> pPipelines(request.vkcreategraphicspipelines().createinfocount());
  VkResult result = context.device_dispatch_table().CreateGraphicsPipelines(reinterpret_cast<VkDevice>(request.vkcreategraphicspipelines().device()), reinterpret_cast<VkPipelineCache>(request.vkcreategraphicspipelines().pipelinecache()), request.vkcreategraphicspipelines().createinfocount(), pCreateInfos.data(), nullptr, pPipelines.data());
  for (VkPipeline pPipelines_elem : pPipelines) {
    response->mutable_vkcreategraphicspipelines()->add_ppipelines(reinterpret_cast<uint64_t>(pPipelines_elem));
  }
  response->mutable_vkcreategraphicspipelines()->set_result(static_cast<vvk::server::VkResult>(result));
  for (uint32_t i = 0; i < pCreateInfos.size(); i++) {
    VkGraphicsPipelineCreateInfo& pCreateInfos_ref = pCreateInfos[i];
    for (int pStages_indx = 0; pStages_indx < request.vkcreategraphicspipelines().pcreateinfos(i).pstages_size(); pStages_indx++)  {
      const VkPipelineShaderStageCreateInfo &pCreateInfos_ref_pStages_i = pCreateInfos_ref.pStages[pStages_indx];
      if (request.vkcreategraphicspipelines().pcreateinfos(i).pstages(pStages_indx).has_pspecializationinfo()) {
        const VkSpecializationInfo &pCreateInfos_ref_pStages_i_pSpecializationInfo = *pCreateInfos_ref_pStages_i.pSpecializationInfo;
        delete[] pCreateInfos_ref_pStages_i_pSpecializationInfo.pMapEntries;
        delete pCreateInfos_ref_pStages_i.pSpecializationInfo;
      }
    }
    delete[] pCreateInfos_ref.pStages;
    if (request.vkcreategraphicspipelines().pcreateinfos(i).has_pvertexinputstate()) {
      const VkPipelineVertexInputStateCreateInfo &pCreateInfos_ref_pVertexInputState = *pCreateInfos_ref.pVertexInputState;
      delete[] pCreateInfos_ref_pVertexInputState.pVertexBindingDescriptions;
      delete[] pCreateInfos_ref_pVertexInputState.pVertexAttributeDescriptions;
      delete pCreateInfos_ref.pVertexInputState;
    }
    if (request.vkcreategraphicspipelines().pcreateinfos(i).has_pinputassemblystate()) {
      const VkPipelineInputAssemblyStateCreateInfo &pCreateInfos_ref_pInputAssemblyState = *pCreateInfos_ref.pInputAssemblyState;
      delete pCreateInfos_ref.pInputAssemblyState;
    }
    if (request.vkcreategraphicspipelines().pcreateinfos(i).has_ptessellationstate()) {
      const VkPipelineTessellationStateCreateInfo &pCreateInfos_ref_pTessellationState = *pCreateInfos_ref.pTessellationState;
      delete pCreateInfos_ref.pTessellationState;
    }
    if (request.vkcreategraphicspipelines().pcreateinfos(i).has_pviewportstate()) {
      const VkPipelineViewportStateCreateInfo &pCreateInfos_ref_pViewportState = *pCreateInfos_ref.pViewportState;
      delete[] pCreateInfos_ref_pViewportState.pViewports;
      delete[] pCreateInfos_ref_pViewportState.pScissors;
      delete pCreateInfos_ref.pViewportState;
    }
    if (request.vkcreategraphicspipelines().pcreateinfos(i).has_prasterizationstate()) {
      const VkPipelineRasterizationStateCreateInfo &pCreateInfos_ref_pRasterizationState = *pCreateInfos_ref.pRasterizationState;
      delete pCreateInfos_ref.pRasterizationState;
    }
    if (request.vkcreategraphicspipelines().pcreateinfos(i).has_pmultisamplestate()) {
      const VkPipelineMultisampleStateCreateInfo &pCreateInfos_ref_pMultisampleState = *pCreateInfos_ref.pMultisampleState;
      delete[] pCreateInfos_ref_pMultisampleState.pSampleMask;
      delete pCreateInfos_ref.pMultisampleState;
    }
    if (request.vkcreategraphicspipelines().pcreateinfos(i).has_pdepthstencilstate()) {
      const VkPipelineDepthStencilStateCreateInfo &pCreateInfos_ref_pDepthStencilState = *pCreateInfos_ref.pDepthStencilState;
      delete pCreateInfos_ref.pDepthStencilState;
    }
    if (request.vkcreategraphicspipelines().pcreateinfos(i).has_pcolorblendstate()) {
      const VkPipelineColorBlendStateCreateInfo &pCreateInfos_ref_pColorBlendState = *pCreateInfos_ref.pColorBlendState;
      delete[] pCreateInfos_ref_pColorBlendState.pAttachments;
      delete pCreateInfos_ref.pColorBlendState;
    }
    if (request.vkcreategraphicspipelines().pcreateinfos(i).has_pdynamicstate()) {
      const VkPipelineDynamicStateCreateInfo &pCreateInfos_ref_pDynamicState = *pCreateInfos_ref.pDynamicState;
      delete pCreateInfos_ref.pDynamicState;
    }
  }
}
void UnpackAndExecuteVkDestroyPipeline(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyPipeline");

  context.device_dispatch_table().DestroyPipeline(reinterpret_cast<VkDevice>(request.vkdestroypipeline().device()), reinterpret_cast<VkPipeline>(request.vkdestroypipeline().pipeline()), nullptr);
}
void UnpackAndExecuteVkCreateFramebuffer(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateFramebuffer");

  VkFramebufferCreateInfo pCreateInfo = {};
  FillStructFromProto(pCreateInfo, request.vkcreateframebuffer().pcreateinfo());
  VkFramebuffer server_pFramebuffer;
  VkResult result = context.device_dispatch_table().CreateFramebuffer(reinterpret_cast<VkDevice>(request.vkcreateframebuffer().device()), &pCreateInfo, nullptr, &server_pFramebuffer);
  response->mutable_vkcreateframebuffer()->set_pframebuffer(reinterpret_cast<uint64_t>(server_pFramebuffer));
  response->mutable_vkcreateframebuffer()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkDestroyFramebuffer(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyFramebuffer");

  context.device_dispatch_table().DestroyFramebuffer(reinterpret_cast<VkDevice>(request.vkdestroyframebuffer().device()), reinterpret_cast<VkFramebuffer>(request.vkdestroyframebuffer().framebuffer()), nullptr);
}
void UnpackAndExecuteVkWaitForFences(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkWaitForFences");

  VkResult result = context.device_dispatch_table().WaitForFences(reinterpret_cast<VkDevice>(request.vkwaitforfences().device()), request.vkwaitforfences().fencecount(), reinterpret_cast<const VkFence*>(request.vkwaitforfences().pfences().data()), request.vkwaitforfences().waitall(), request.vkwaitforfences().timeout());
  response->mutable_vkwaitforfences()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkResetFences(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkResetFences");

  VkResult result = context.device_dispatch_table().ResetFences(reinterpret_cast<VkDevice>(request.vkresetfences().device()), request.vkresetfences().fencecount(), reinterpret_cast<const VkFence*>(request.vkresetfences().pfences().data()));
  response->mutable_vkresetfences()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkResetCommandPool(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkResetCommandPool");

  VkResult result = context.device_dispatch_table().ResetCommandPool(reinterpret_cast<VkDevice>(request.vkresetcommandpool().device()), reinterpret_cast<VkCommandPool>(request.vkresetcommandpool().commandpool()), static_cast<VkCommandPoolResetFlags>(request.vkresetcommandpool().flags()));
  response->mutable_vkresetcommandpool()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkCmdBeginRenderPass(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCmdBeginRenderPass");

  VkRenderPassBeginInfo pRenderPassBegin = {};
  FillStructFromProto(pRenderPassBegin, request.vkcmdbeginrenderpass().prenderpassbegin());
  context.device_dispatch_table().CmdBeginRenderPass(reinterpret_cast<VkCommandBuffer>(request.vkcmdbeginrenderpass().commandbuffer()), &pRenderPassBegin, static_cast<VkSubpassContents>(request.vkcmdbeginrenderpass().contents()));
  delete[] pRenderPassBegin.pClearValues;
}
void UnpackAndExecuteVkCmdEndRenderPass(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCmdEndRenderPass");

  context.device_dispatch_table().CmdEndRenderPass(reinterpret_cast<VkCommandBuffer>(request.vkcmdendrenderpass().commandbuffer()));
}
void UnpackAndExecuteVkCmdBindPipeline(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCmdBindPipeline");

  context.device_dispatch_table().CmdBindPipeline(reinterpret_cast<VkCommandBuffer>(request.vkcmdbindpipeline().commandbuffer()), static_cast<VkPipelineBindPoint>(request.vkcmdbindpipeline().pipelinebindpoint()), reinterpret_cast<VkPipeline>(request.vkcmdbindpipeline().pipeline()));
}
void UnpackAndExecuteVkCmdSetViewport(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCmdSetViewport");

  std::vector<VkViewport> pViewports(request.vkcmdsetviewport().viewportcount());
  for (uint32_t i = 0; i < pViewports.size(); i++) {
    FillStructFromProto(pViewports[i], request.vkcmdsetviewport().pviewports(i));
  }
  context.device_dispatch_table().CmdSetViewport(reinterpret_cast<VkCommandBuffer>(request.vkcmdsetviewport().commandbuffer()), request.vkcmdsetviewport().firstviewport(), request.vkcmdsetviewport().viewportcount(), pViewports.data());
}
void UnpackAndExecuteVkCmdSetScissor(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCmdSetScissor");

  std::vector<VkRect2D> pScissors(request.vkcmdsetscissor().scissorcount());
  for (uint32_t i = 0; i < pScissors.size(); i++) {
    FillStructFromProto(pScissors[i], request.vkcmdsetscissor().pscissors(i));
  }
  context.device_dispatch_table().CmdSetScissor(reinterpret_cast<VkCommandBuffer>(request.vkcmdsetscissor().commandbuffer()), request.vkcmdsetscissor().firstscissor(), request.vkcmdsetscissor().scissorcount(), pScissors.data());
}
void UnpackAndExecuteVkCmdDraw(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCmdDraw");

  context.device_dispatch_table().CmdDraw(reinterpret_cast<VkCommandBuffer>(request.vkcmddraw().commandbuffer()), request.vkcmddraw().vertexcount(), request.vkcmddraw().instancecount(), request.vkcmddraw().firstvertex(), request.vkcmddraw().firstinstance());
}
void UnpackAndExecuteVkQueueSubmit(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkQueueSubmit");

  std::vector<VkSubmitInfo> pSubmits(request.vkqueuesubmit().submitcount());
  for (uint32_t i = 0; i < pSubmits.size(); i++) {
    FillStructFromProto(pSubmits[i], request.vkqueuesubmit().psubmits(i));
  }
  VkResult result = context.device_dispatch_table().QueueSubmit(reinterpret_cast<VkQueue>(request.vkqueuesubmit().queue()), request.vkqueuesubmit().submitcount(), pSubmits.data(), reinterpret_cast<VkFence>(request.vkqueuesubmit().fence()));
  response->mutable_vkqueuesubmit()->set_result(static_cast<vvk::server::VkResult>(result));
  for (uint32_t i = 0; i < pSubmits.size(); i++) {
    VkSubmitInfo& pSubmits_ref = pSubmits[i];
    delete[] pSubmits_ref.pWaitDstStageMask;
  }
}
void UnpackAndExecuteVkDeviceWaitIdle(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDeviceWaitIdle");

  VkResult result = context.device_dispatch_table().DeviceWaitIdle(reinterpret_cast<VkDevice>(request.vkdevicewaitidle().device()));
  response->mutable_vkdevicewaitidle()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkQueueWaitIdle(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkQueueWaitIdle");

  VkResult result = context.device_dispatch_table().QueueWaitIdle(reinterpret_cast<VkQueue>(request.vkqueuewaitidle().queue()));
  response->mutable_vkqueuewaitidle()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkCmdPipelineBarrier(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCmdPipelineBarrier");

  std::vector<VkMemoryBarrier> pMemoryBarriers(request.vkcmdpipelinebarrier().memorybarriercount());
  for (uint32_t i = 0; i < pMemoryBarriers.size(); i++) {
    FillStructFromProto(pMemoryBarriers[i], request.vkcmdpipelinebarrier().pmemorybarriers(i));
  }
  std::vector<VkBufferMemoryBarrier> pBufferMemoryBarriers(request.vkcmdpipelinebarrier().buffermemorybarriercount());
  for (uint32_t i = 0; i < pBufferMemoryBarriers.size(); i++) {
    FillStructFromProto(pBufferMemoryBarriers[i], request.vkcmdpipelinebarrier().pbuffermemorybarriers(i));
  }
  std::vector<VkImageMemoryBarrier> pImageMemoryBarriers(request.vkcmdpipelinebarrier().imagememorybarriercount());
  for (uint32_t i = 0; i < pImageMemoryBarriers.size(); i++) {
    FillStructFromProto(pImageMemoryBarriers[i], request.vkcmdpipelinebarrier().pimagememorybarriers(i));
  }
  context.device_dispatch_table().CmdPipelineBarrier(reinterpret_cast<VkCommandBuffer>(request.vkcmdpipelinebarrier().commandbuffer()), static_cast<VkPipelineStageFlags>(request.vkcmdpipelinebarrier().srcstagemask()), static_cast<VkPipelineStageFlags>(request.vkcmdpipelinebarrier().dststagemask()), static_cast<VkDependencyFlags>(request.vkcmdpipelinebarrier().dependencyflags()), request.vkcmdpipelinebarrier().memorybarriercount(), pMemoryBarriers.data(), request.vkcmdpipelinebarrier().buffermemorybarriercount(), pBufferMemoryBarriers.data(), request.vkcmdpipelinebarrier().imagememorybarriercount(), pImageMemoryBarriers.data());
}
void UnpackAndExecuteVkCmdCopyImageToBuffer(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCmdCopyImageToBuffer");

  std::vector<VkBufferImageCopy> pRegions(request.vkcmdcopyimagetobuffer().regioncount());
  for (uint32_t i = 0; i < pRegions.size(); i++) {
    FillStructFromProto(pRegions[i], request.vkcmdcopyimagetobuffer().pregions(i));
  }
  context.device_dispatch_table().CmdCopyImageToBuffer(reinterpret_cast<VkCommandBuffer>(request.vkcmdcopyimagetobuffer().commandbuffer()), reinterpret_cast<VkImage>(request.vkcmdcopyimagetobuffer().srcimage()), static_cast<VkImageLayout>(request.vkcmdcopyimagetobuffer().srcimagelayout()), reinterpret_cast<VkBuffer>(request.vkcmdcopyimagetobuffer().dstbuffer()), request.vkcmdcopyimagetobuffer().regioncount(), pRegions.data());
}
void UnpackAndExecuteVkGetPhysicalDeviceProperties2(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkGetPhysicalDeviceProperties2");

  VkPhysicalDeviceProperties2 pProperties = {};
  FillStructFromProto(pProperties, request.vkgetphysicaldeviceproperties2().pproperties());
  context.instance_dispatch_table().GetPhysicalDeviceProperties2(context.physical_device(), &pProperties);
  FillProtoFromStruct(response->mutable_vkgetphysicaldeviceproperties2()->mutable_pproperties(), &pProperties);
}
void UnpackAndExecuteVkGetPhysicalDeviceFeatures2(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkGetPhysicalDeviceFeatures2");

  VkPhysicalDeviceFeatures2 pFeatures = {};
  FillStructFromProto(pFeatures, request.vkgetphysicaldevicefeatures2().pfeatures());
  context.instance_dispatch_table().GetPhysicalDeviceFeatures2(context.physical_device(), &pFeatures);
  FillProtoFromStruct(response->mutable_vkgetphysicaldevicefeatures2()->mutable_pfeatures(), &pFeatures);
}
void UnpackAndExecuteVkSignalSemaphore(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkSignalSemaphore");

  VkSemaphoreSignalInfo pSignalInfo = {};
  FillStructFromProto(pSignalInfo, request.vksignalsemaphore().psignalinfo());
  VkResult result = context.device_dispatch_table().SignalSemaphore(reinterpret_cast<VkDevice>(request.vksignalsemaphore().device()), &pSignalInfo);
  response->mutable_vksignalsemaphore()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkCreateBuffer(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateBuffer");

  VkBufferCreateInfo pCreateInfo = {};
  FillStructFromProto(pCreateInfo, request.vkcreatebuffer().pcreateinfo());
  VkBuffer server_pBuffer;
  VkResult result = context.device_dispatch_table().CreateBuffer(reinterpret_cast<VkDevice>(request.vkcreatebuffer().device()), &pCreateInfo, nullptr, &server_pBuffer);
  response->mutable_vkcreatebuffer()->set_pbuffer(reinterpret_cast<uint64_t>(server_pBuffer));
  response->mutable_vkcreatebuffer()->set_result(static_cast<vvk::server::VkResult>(result));
  delete[] pCreateInfo.pQueueFamilyIndices;
}
void UnpackAndExecuteVkDestroyBuffer(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyBuffer");

  context.device_dispatch_table().DestroyBuffer(reinterpret_cast<VkDevice>(request.vkdestroybuffer().device()), reinterpret_cast<VkBuffer>(request.vkdestroybuffer().buffer()), nullptr);
}
void UnpackAndExecuteVkGetBufferMemoryRequirements(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkGetBufferMemoryRequirements");

  VkMemoryRequirements pMemoryRequirements = {};
  FillStructFromProto(pMemoryRequirements, request.vkgetbuffermemoryrequirements().pmemoryrequirements());
  context.device_dispatch_table().GetBufferMemoryRequirements(reinterpret_cast<VkDevice>(request.vkgetbuffermemoryrequirements().device()), reinterpret_cast<VkBuffer>(request.vkgetbuffermemoryrequirements().buffer()), &pMemoryRequirements);
  FillProtoFromStruct(response->mutable_vkgetbuffermemoryrequirements()->mutable_pmemoryrequirements(), &pMemoryRequirements);
}
void UnpackAndExecuteVkBindBufferMemory(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkBindBufferMemory");

  VkResult result = context.device_dispatch_table().BindBufferMemory(reinterpret_cast<VkDevice>(request.vkbindbuffermemory().device()), reinterpret_cast<VkBuffer>(request.vkbindbuffermemory().buffer()), reinterpret_cast<VkDeviceMemory>(request.vkbindbuffermemory().memory()), static_cast<VkDeviceSize>(request.vkbindbuffermemory().memoryoffset()));
  response->mutable_vkbindbuffermemory()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkMapMemory(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkMapMemory");

  void* ppData = reinterpret_cast<void*>(request.vkmapmemory().ppdata());
  VkResult result = context.device_dispatch_table().MapMemory(reinterpret_cast<VkDevice>(request.vkmapmemory().device()), reinterpret_cast<VkDeviceMemory>(request.vkmapmemory().memory()), static_cast<VkDeviceSize>(request.vkmapmemory().offset()), static_cast<VkDeviceSize>(request.vkmapmemory().size()), static_cast<VkMemoryMapFlags>(request.vkmapmemory().flags()), &ppData);
  response->mutable_vkmapmemory()->set_ppdata(reinterpret_cast<uint64_t>(ppData));
  response->mutable_vkmapmemory()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkUnmapMemory(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkUnmapMemory");

  context.device_dispatch_table().UnmapMemory(reinterpret_cast<VkDevice>(request.vkunmapmemory().device()), reinterpret_cast<VkDeviceMemory>(request.vkunmapmemory().memory()));
}
void UnpackAndExecuteVkCmdBindVertexBuffers(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCmdBindVertexBuffers");

  context.device_dispatch_table().CmdBindVertexBuffers(reinterpret_cast<VkCommandBuffer>(request.vkcmdbindvertexbuffers().commandbuffer()), request.vkcmdbindvertexbuffers().firstbinding(), request.vkcmdbindvertexbuffers().bindingcount(), reinterpret_cast<const VkBuffer*>(request.vkcmdbindvertexbuffers().pbuffers().data()), reinterpret_cast<const VkDeviceSize*>(request.vkcmdbindvertexbuffers().poffsets().data()));
}
void UnpackAndExecuteVkCreateSampler(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateSampler");

  VkSamplerCreateInfo pCreateInfo = {};
  FillStructFromProto(pCreateInfo, request.vkcreatesampler().pcreateinfo());
  VkSampler server_pSampler;
  VkResult result = context.device_dispatch_table().CreateSampler(reinterpret_cast<VkDevice>(request.vkcreatesampler().device()), &pCreateInfo, nullptr, &server_pSampler);
  response->mutable_vkcreatesampler()->set_psampler(reinterpret_cast<uint64_t>(server_pSampler));
  response->mutable_vkcreatesampler()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkDestroySampler(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroySampler");

  context.device_dispatch_table().DestroySampler(reinterpret_cast<VkDevice>(request.vkdestroysampler().device()), reinterpret_cast<VkSampler>(request.vkdestroysampler().sampler()), nullptr);
}
void UnpackAndExecuteVkCreateDescriptorSetLayout(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateDescriptorSetLayout");

  VkDescriptorSetLayoutCreateInfo pCreateInfo = {};
  FillStructFromProto(pCreateInfo, request.vkcreatedescriptorsetlayout().pcreateinfo());
  VkDescriptorSetLayout server_pSetLayout;
  VkResult result = context.device_dispatch_table().CreateDescriptorSetLayout(reinterpret_cast<VkDevice>(request.vkcreatedescriptorsetlayout().device()), &pCreateInfo, nullptr, &server_pSetLayout);
  response->mutable_vkcreatedescriptorsetlayout()->set_psetlayout(reinterpret_cast<uint64_t>(server_pSetLayout));
  response->mutable_vkcreatedescriptorsetlayout()->set_result(static_cast<vvk::server::VkResult>(result));
  delete[] pCreateInfo.pBindings;
}
void UnpackAndExecuteVkDestroyDescriptorSetLayout(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyDescriptorSetLayout");

  context.device_dispatch_table().DestroyDescriptorSetLayout(reinterpret_cast<VkDevice>(request.vkdestroydescriptorsetlayout().device()), reinterpret_cast<VkDescriptorSetLayout>(request.vkdestroydescriptorsetlayout().descriptorsetlayout()), nullptr);
}
void UnpackAndExecuteVkCreatePipelineCache(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreatePipelineCache");

  VkPipelineCacheCreateInfo pCreateInfo = {};
  FillStructFromProto(pCreateInfo, request.vkcreatepipelinecache().pcreateinfo());
  VkPipelineCache server_pPipelineCache;
  VkResult result = context.device_dispatch_table().CreatePipelineCache(reinterpret_cast<VkDevice>(request.vkcreatepipelinecache().device()), &pCreateInfo, nullptr, &server_pPipelineCache);
  response->mutable_vkcreatepipelinecache()->set_ppipelinecache(reinterpret_cast<uint64_t>(server_pPipelineCache));
  response->mutable_vkcreatepipelinecache()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkDestroyPipelineCache(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyPipelineCache");

  context.device_dispatch_table().DestroyPipelineCache(reinterpret_cast<VkDevice>(request.vkdestroypipelinecache().device()), reinterpret_cast<VkPipelineCache>(request.vkdestroypipelinecache().pipelinecache()), nullptr);
}
void UnpackAndExecuteVkCreateDescriptorPool(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCreateDescriptorPool");

  VkDescriptorPoolCreateInfo pCreateInfo = {};
  FillStructFromProto(pCreateInfo, request.vkcreatedescriptorpool().pcreateinfo());
  VkDescriptorPool server_pDescriptorPool;
  VkResult result = context.device_dispatch_table().CreateDescriptorPool(reinterpret_cast<VkDevice>(request.vkcreatedescriptorpool().device()), &pCreateInfo, nullptr, &server_pDescriptorPool);
  response->mutable_vkcreatedescriptorpool()->set_pdescriptorpool(reinterpret_cast<uint64_t>(server_pDescriptorPool));
  response->mutable_vkcreatedescriptorpool()->set_result(static_cast<vvk::server::VkResult>(result));
  delete[] pCreateInfo.pPoolSizes;
}
void UnpackAndExecuteVkDestroyDescriptorPool(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkDestroyDescriptorPool");

  context.device_dispatch_table().DestroyDescriptorPool(reinterpret_cast<VkDevice>(request.vkdestroydescriptorpool().device()), reinterpret_cast<VkDescriptorPool>(request.vkdestroydescriptorpool().descriptorpool()), nullptr);
}
void UnpackAndExecuteVkAllocateDescriptorSets(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkAllocateDescriptorSets");

  VkDescriptorSetAllocateInfo pAllocateInfo = {};
  FillStructFromProto(pAllocateInfo, request.vkallocatedescriptorsets().pallocateinfo());
  std::vector<VkDescriptorSet> pDescriptorSets(request.vkallocatedescriptorsets().pallocateinfo().descriptorsetcount());
  VkResult result = context.device_dispatch_table().AllocateDescriptorSets(reinterpret_cast<VkDevice>(request.vkallocatedescriptorsets().device()), &pAllocateInfo, pDescriptorSets.data());
  for (VkDescriptorSet pDescriptorSets_elem : pDescriptorSets) {
    response->mutable_vkallocatedescriptorsets()->add_pdescriptorsets(reinterpret_cast<uint64_t>(pDescriptorSets_elem));
  }
  response->mutable_vkallocatedescriptorsets()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkFreeDescriptorSets(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkFreeDescriptorSets");

  VkResult result = context.device_dispatch_table().FreeDescriptorSets(reinterpret_cast<VkDevice>(request.vkfreedescriptorsets().device()), reinterpret_cast<VkDescriptorPool>(request.vkfreedescriptorsets().descriptorpool()), request.vkfreedescriptorsets().descriptorsetcount(), reinterpret_cast<const VkDescriptorSet*>(request.vkfreedescriptorsets().pdescriptorsets().data()));
  response->mutable_vkfreedescriptorsets()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkUpdateDescriptorSets(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkUpdateDescriptorSets");

  std::vector<VkWriteDescriptorSet> pDescriptorWrites(request.vkupdatedescriptorsets().descriptorwritecount());
  for (uint32_t i = 0; i < pDescriptorWrites.size(); i++) {
    FillStructFromProto(pDescriptorWrites[i], request.vkupdatedescriptorsets().pdescriptorwrites(i));
  }
  std::vector<VkCopyDescriptorSet> pDescriptorCopies(request.vkupdatedescriptorsets().descriptorcopycount());
  for (uint32_t i = 0; i < pDescriptorCopies.size(); i++) {
    FillStructFromProto(pDescriptorCopies[i], request.vkupdatedescriptorsets().pdescriptorcopies(i));
  }
  context.device_dispatch_table().UpdateDescriptorSets(reinterpret_cast<VkDevice>(request.vkupdatedescriptorsets().device()), request.vkupdatedescriptorsets().descriptorwritecount(), pDescriptorWrites.data(), request.vkupdatedescriptorsets().descriptorcopycount(), pDescriptorCopies.data());
  for (uint32_t i = 0; i < pDescriptorWrites.size(); i++) {
    VkWriteDescriptorSet& pDescriptorWrites_ref = pDescriptorWrites[i];
    delete[] pDescriptorWrites_ref.pImageInfo;
    delete[] pDescriptorWrites_ref.pBufferInfo;
  }
}
void UnpackAndExecuteVkResetCommandBuffer(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkResetCommandBuffer");

  VkResult result = context.device_dispatch_table().ResetCommandBuffer(reinterpret_cast<VkCommandBuffer>(request.vkresetcommandbuffer().commandbuffer()), static_cast<VkCommandBufferResetFlags>(request.vkresetcommandbuffer().flags()));
  response->mutable_vkresetcommandbuffer()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkCmdBindDescriptorSets(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkCmdBindDescriptorSets");

  context.device_dispatch_table().CmdBindDescriptorSets(reinterpret_cast<VkCommandBuffer>(request.vkcmdbinddescriptorsets().commandbuffer()), static_cast<VkPipelineBindPoint>(request.vkcmdbinddescriptorsets().pipelinebindpoint()), reinterpret_cast<VkPipelineLayout>(request.vkcmdbinddescriptorsets().layout()), request.vkcmdbinddescriptorsets().firstset(), request.vkcmdbinddescriptorsets().descriptorsetcount(), reinterpret_cast<const VkDescriptorSet*>(request.vkcmdbinddescriptorsets().pdescriptorsets().data()), request.vkcmdbinddescriptorsets().dynamicoffsetcount(), reinterpret_cast<const uint32_t*>(request.vkcmdbinddescriptorsets().pdynamicoffsets().data()));
}
void UnpackAndExecuteVkFlushMappedMemoryRanges(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkFlushMappedMemoryRanges");

  std::vector<VkMappedMemoryRange> pMemoryRanges(request.vkflushmappedmemoryranges().memoryrangecount());
  for (uint32_t i = 0; i < pMemoryRanges.size(); i++) {
    FillStructFromProto(pMemoryRanges[i], request.vkflushmappedmemoryranges().pmemoryranges(i));
  }
  VkResult result = context.device_dispatch_table().FlushMappedMemoryRanges(reinterpret_cast<VkDevice>(request.vkflushmappedmemoryranges().device()), request.vkflushmappedmemoryranges().memoryrangecount(), pMemoryRanges.data());
  response->mutable_vkflushmappedmemoryranges()->set_result(static_cast<vvk::server::VkResult>(result));
}
void UnpackAndExecuteVkInvalidateMappedMemoryRanges(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response){
  assert(request.method() == "vkInvalidateMappedMemoryRanges");

  std::vector<VkMappedMemoryRange> pMemoryRanges(request.vkinvalidatemappedmemoryranges().memoryrangecount());
  for (uint32_t i = 0; i < pMemoryRanges.size(); i++) {
    FillStructFromProto(pMemoryRanges[i], request.vkinvalidatemappedmemoryranges().pmemoryranges(i));
  }
  VkResult result = context.device_dispatch_table().InvalidateMappedMemoryRanges(reinterpret_cast<VkDevice>(request.vkinvalidatemappedmemoryranges().device()), request.vkinvalidatemappedmemoryranges().memoryrangecount(), pMemoryRanges.data());
  response->mutable_vkinvalidatemappedmemoryranges()->set_result(static_cast<vvk::server::VkResult>(result));
}

