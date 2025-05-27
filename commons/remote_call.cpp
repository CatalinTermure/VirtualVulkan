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
void FillProtoFromStruct(vvk::server::VkApplicationInfo* proto, const VkApplicationInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkAttachmentDescription* proto, const VkAttachmentDescription* original_struct);
void FillProtoFromStruct(vvk::server::VkAttachmentReference* proto, const VkAttachmentReference* original_struct);
void FillProtoFromStruct(vvk::server::VkBindImageMemoryInfo* proto, const VkBindImageMemoryInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkBufferCopy* proto, const VkBufferCopy* original_struct);
void FillProtoFromStruct(vvk::server::VkBufferCreateInfo* proto, const VkBufferCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkBufferImageCopy* proto, const VkBufferImageCopy* original_struct);
void FillProtoFromStruct(vvk::server::VkBufferMemoryBarrier* proto, const VkBufferMemoryBarrier* original_struct);
void FillProtoFromStruct(vvk::server::VkBufferMemoryRequirementsInfo2* proto, const VkBufferMemoryRequirementsInfo2* original_struct);
void FillProtoFromStruct(vvk::server::VkClearColorValue* proto, const VkClearColorValue* original_struct);
void FillProtoFromStruct(vvk::server::VkClearDepthStencilValue* proto, const VkClearDepthStencilValue* original_struct);
void FillProtoFromStruct(vvk::server::VkClearValue* proto, const VkClearValue* original_struct);
void FillProtoFromStruct(vvk::server::VkCommandBufferAllocateInfo* proto, const VkCommandBufferAllocateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkCommandBufferBeginInfo* proto, const VkCommandBufferBeginInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkCommandBufferInheritanceInfo* proto, const VkCommandBufferInheritanceInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkCommandPoolCreateInfo* proto, const VkCommandPoolCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkComponentMapping* proto, const VkComponentMapping* original_struct);
void FillProtoFromStruct(vvk::server::VkComputePipelineCreateInfo* proto, const VkComputePipelineCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkConformanceVersion* proto, const VkConformanceVersion* original_struct);
void FillProtoFromStruct(vvk::server::VkCopyDescriptorSet* proto, const VkCopyDescriptorSet* original_struct);
void FillProtoFromStruct(vvk::server::VkDescriptorBufferInfo* proto, const VkDescriptorBufferInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkDescriptorImageInfo* proto, const VkDescriptorImageInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkDescriptorPoolCreateInfo* proto, const VkDescriptorPoolCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkDescriptorPoolSize* proto, const VkDescriptorPoolSize* original_struct);
void FillProtoFromStruct(vvk::server::VkDescriptorSetAllocateInfo* proto, const VkDescriptorSetAllocateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkDescriptorSetLayoutBinding* proto, const VkDescriptorSetLayoutBinding* original_struct);
void FillProtoFromStruct(vvk::server::VkDescriptorSetLayoutCreateInfo* proto, const VkDescriptorSetLayoutCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkDeviceCreateInfo* proto, const VkDeviceCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkDeviceQueueCreateInfo* proto, const VkDeviceQueueCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkExtent2D* proto, const VkExtent2D* original_struct);
void FillProtoFromStruct(vvk::server::VkExtent3D* proto, const VkExtent3D* original_struct);
void FillProtoFromStruct(vvk::server::VkFenceCreateInfo* proto, const VkFenceCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkFormatProperties* proto, const VkFormatProperties* original_struct);
void FillProtoFromStruct(vvk::server::VkFramebufferCreateInfo* proto, const VkFramebufferCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkGraphicsPipelineCreateInfo* proto, const VkGraphicsPipelineCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkImageCreateInfo* proto, const VkImageCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkImageMemoryBarrier* proto, const VkImageMemoryBarrier* original_struct);
void FillProtoFromStruct(vvk::server::VkImageMemoryRequirementsInfo2* proto, const VkImageMemoryRequirementsInfo2* original_struct);
void FillProtoFromStruct(vvk::server::VkImageSubresource* proto, const VkImageSubresource* original_struct);
void FillProtoFromStruct(vvk::server::VkImageSubresourceLayers* proto, const VkImageSubresourceLayers* original_struct);
void FillProtoFromStruct(vvk::server::VkImageSubresourceRange* proto, const VkImageSubresourceRange* original_struct);
void FillProtoFromStruct(vvk::server::VkImageViewCreateInfo* proto, const VkImageViewCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkInstanceCreateInfo* proto, const VkInstanceCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkMappedMemoryRange* proto, const VkMappedMemoryRange* original_struct);
void FillProtoFromStruct(vvk::server::VkMemoryAllocateInfo* proto, const VkMemoryAllocateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkMemoryBarrier* proto, const VkMemoryBarrier* original_struct);
void FillProtoFromStruct(vvk::server::VkMemoryDedicatedAllocateInfo* proto, const VkMemoryDedicatedAllocateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkMemoryDedicatedRequirements* proto, const VkMemoryDedicatedRequirements* original_struct);
void FillProtoFromStruct(vvk::server::VkMemoryHeap* proto, const VkMemoryHeap* original_struct);
void FillProtoFromStruct(vvk::server::VkMemoryRequirements* proto, const VkMemoryRequirements* original_struct);
void FillProtoFromStruct(vvk::server::VkMemoryRequirements2* proto, const VkMemoryRequirements2* original_struct);
void FillProtoFromStruct(vvk::server::VkMemoryType* proto, const VkMemoryType* original_struct);
void FillProtoFromStruct(vvk::server::VkOffset2D* proto, const VkOffset2D* original_struct);
void FillProtoFromStruct(vvk::server::VkOffset3D* proto, const VkOffset3D* original_struct);
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
void FillProtoFromStruct(vvk::server::VkPipelineCacheCreateInfo* proto, const VkPipelineCacheCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkPipelineColorBlendAttachmentState* proto, const VkPipelineColorBlendAttachmentState* original_struct);
void FillProtoFromStruct(vvk::server::VkPipelineColorBlendStateCreateInfo* proto, const VkPipelineColorBlendStateCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkPipelineDepthStencilStateCreateInfo* proto, const VkPipelineDepthStencilStateCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkPipelineDynamicStateCreateInfo* proto, const VkPipelineDynamicStateCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkPipelineInputAssemblyStateCreateInfo* proto, const VkPipelineInputAssemblyStateCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkPipelineLayoutCreateInfo* proto, const VkPipelineLayoutCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkPipelineMultisampleStateCreateInfo* proto, const VkPipelineMultisampleStateCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkPipelineRasterizationStateCreateInfo* proto, const VkPipelineRasterizationStateCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkPipelineShaderStageCreateInfo* proto, const VkPipelineShaderStageCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkPipelineTessellationStateCreateInfo* proto, const VkPipelineTessellationStateCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkPipelineVertexInputStateCreateInfo* proto, const VkPipelineVertexInputStateCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkPipelineViewportStateCreateInfo* proto, const VkPipelineViewportStateCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkProtectedSubmitInfo* proto, const VkProtectedSubmitInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkPushConstantRange* proto, const VkPushConstantRange* original_struct);
void FillProtoFromStruct(vvk::server::VkRect2D* proto, const VkRect2D* original_struct);
void FillProtoFromStruct(vvk::server::VkRenderPassBeginInfo* proto, const VkRenderPassBeginInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkRenderPassCreateInfo* proto, const VkRenderPassCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkSamplerCreateInfo* proto, const VkSamplerCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkSemaphoreCreateInfo* proto, const VkSemaphoreCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkSemaphoreSignalInfo* proto, const VkSemaphoreSignalInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkSemaphoreTypeCreateInfo* proto, const VkSemaphoreTypeCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkShaderModuleCreateInfo* proto, const VkShaderModuleCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkSpecializationInfo* proto, const VkSpecializationInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkSpecializationMapEntry* proto, const VkSpecializationMapEntry* original_struct);
void FillProtoFromStruct(vvk::server::VkStencilOpState* proto, const VkStencilOpState* original_struct);
void FillProtoFromStruct(vvk::server::VkSubmitInfo* proto, const VkSubmitInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkSubpassDependency* proto, const VkSubpassDependency* original_struct);
void FillProtoFromStruct(vvk::server::VkSubpassDescription* proto, const VkSubpassDescription* original_struct);
void FillProtoFromStruct(vvk::server::VkSubresourceLayout* proto, const VkSubresourceLayout* original_struct);
void FillProtoFromStruct(vvk::server::VkTimelineSemaphoreSubmitInfo* proto, const VkTimelineSemaphoreSubmitInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkVertexInputAttributeDescription* proto, const VkVertexInputAttributeDescription* original_struct);
void FillProtoFromStruct(vvk::server::VkVertexInputBindingDescription* proto, const VkVertexInputBindingDescription* original_struct);
void FillProtoFromStruct(vvk::server::VkViewport* proto, const VkViewport* original_struct);
void FillProtoFromStruct(vvk::server::VkWriteDescriptorSet* proto, const VkWriteDescriptorSet* original_struct);
void FillStructFromProto(VkConformanceVersion& original_struct, const vvk::server::VkConformanceVersion& proto);
void FillStructFromProto(VkExtent3D& original_struct, const vvk::server::VkExtent3D& proto);
void FillStructFromProto(VkMemoryHeap& original_struct, const vvk::server::VkMemoryHeap& proto);
void FillStructFromProto(VkMemoryRequirements& original_struct, const vvk::server::VkMemoryRequirements& proto);
void FillStructFromProto(VkMemoryType& original_struct, const vvk::server::VkMemoryType& proto);
void FillStructFromProto(VkPhysicalDeviceFeatures& original_struct, const vvk::server::VkPhysicalDeviceFeatures& proto);
void FillStructFromProto(VkPhysicalDeviceLimits& original_struct, const vvk::server::VkPhysicalDeviceLimits& proto);
void FillStructFromProto(VkPhysicalDeviceProperties& original_struct, const vvk::server::VkPhysicalDeviceProperties& proto);
void FillStructFromProto(VkPhysicalDeviceSparseProperties& original_struct, const vvk::server::VkPhysicalDeviceSparseProperties& proto);
void FillStructFromProtoNoPNext(VkMemoryDedicatedRequirements& original_struct, const vvk::server::VkMemoryDedicatedRequirements& proto);
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
void FillProtoFromStruct(vvk::server::VkApplicationInfo* proto, const VkApplicationInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->pApplicationName) {
    proto->set_papplicationname(original_struct->pApplicationName);
  }
  proto->set_applicationversion(original_struct->applicationVersion);
  if (original_struct->pEngineName) {
    proto->set_penginename(original_struct->pEngineName);
  }
  proto->set_engineversion(original_struct->engineVersion);
  proto->set_apiversion(original_struct->apiVersion);
}
void FillProtoFromStruct(vvk::server::VkAttachmentDescription* proto, const VkAttachmentDescription* original_struct) {
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  proto->set_format(static_cast<vvk::server::VkFormat>(original_struct->format));
  proto->set_samples(original_struct->samples);
  proto->set_loadop(static_cast<vvk::server::VkAttachmentLoadOp>(original_struct->loadOp));
  proto->set_storeop(static_cast<vvk::server::VkAttachmentStoreOp>(original_struct->storeOp));
  proto->set_stencilloadop(static_cast<vvk::server::VkAttachmentLoadOp>(original_struct->stencilLoadOp));
  proto->set_stencilstoreop(static_cast<vvk::server::VkAttachmentStoreOp>(original_struct->stencilStoreOp));
  proto->set_initiallayout(static_cast<vvk::server::VkImageLayout>(original_struct->initialLayout));
  proto->set_finallayout(static_cast<vvk::server::VkImageLayout>(original_struct->finalLayout));
}
void FillProtoFromStruct(vvk::server::VkAttachmentReference* proto, const VkAttachmentReference* original_struct) {
  proto->set_attachment(original_struct->attachment);
  proto->set_layout(static_cast<vvk::server::VkImageLayout>(original_struct->layout));
}
void FillProtoFromStruct(vvk::server::VkBindImageMemoryInfo* proto, const VkBindImageMemoryInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_image(reinterpret_cast<uint64_t>(original_struct->image));
  proto->set_memory(reinterpret_cast<uint64_t>(original_struct->memory));
  proto->set_memoryoffset(static_cast<uint64_t>(original_struct->memoryOffset));
}
void FillProtoFromStruct(vvk::server::VkBufferCopy* proto, const VkBufferCopy* original_struct) {
  proto->set_srcoffset(static_cast<uint64_t>(original_struct->srcOffset));
  proto->set_dstoffset(static_cast<uint64_t>(original_struct->dstOffset));
  proto->set_size(static_cast<uint64_t>(original_struct->size));
}
void FillProtoFromStruct(vvk::server::VkBufferCreateInfo* proto, const VkBufferCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  proto->set_size(static_cast<uint64_t>(original_struct->size));
  proto->set_usage(original_struct->usage);
  proto->set_sharingmode(static_cast<vvk::server::VkSharingMode>(original_struct->sharingMode));
  if (original_struct->queueFamilyIndexCount) {
    proto->set_queuefamilyindexcount(original_struct->queueFamilyIndexCount);
  }
  const size_t proto_pQueueFamilyIndices_length = original_struct->queueFamilyIndexCount;
  for (uint32_t pQueueFamilyIndices_indx = 0; pQueueFamilyIndices_indx < proto_pQueueFamilyIndices_length; pQueueFamilyIndices_indx++) {
    proto->add_pqueuefamilyindices(original_struct->pQueueFamilyIndices[pQueueFamilyIndices_indx]);
  }
}
void FillProtoFromStruct(vvk::server::VkBufferImageCopy* proto, const VkBufferImageCopy* original_struct) {
  proto->set_bufferoffset(static_cast<uint64_t>(original_struct->bufferOffset));
  proto->set_bufferrowlength(original_struct->bufferRowLength);
  proto->set_bufferimageheight(original_struct->bufferImageHeight);
  FillProtoFromStruct(proto->mutable_imagesubresource(), &original_struct->imageSubresource);
  FillProtoFromStruct(proto->mutable_imageoffset(), &original_struct->imageOffset);
  FillProtoFromStruct(proto->mutable_imageextent(), &original_struct->imageExtent);
}
void FillProtoFromStruct(vvk::server::VkBufferMemoryBarrier* proto, const VkBufferMemoryBarrier* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_srcaccessmask(original_struct->srcAccessMask);
  proto->set_dstaccessmask(original_struct->dstAccessMask);
  proto->set_srcqueuefamilyindex(original_struct->srcQueueFamilyIndex);
  proto->set_dstqueuefamilyindex(original_struct->dstQueueFamilyIndex);
  proto->set_buffer(reinterpret_cast<uint64_t>(original_struct->buffer));
  proto->set_offset(static_cast<uint64_t>(original_struct->offset));
  proto->set_size(static_cast<uint64_t>(original_struct->size));
}
void FillProtoFromStruct(vvk::server::VkBufferMemoryRequirementsInfo2* proto, const VkBufferMemoryRequirementsInfo2* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_buffer(reinterpret_cast<uint64_t>(original_struct->buffer));
}
void FillProtoFromStruct(vvk::server::VkClearColorValue* proto, const VkClearColorValue* original_struct) {
  const size_t proto_float32_length = std::min(4, 4);
  for (uint32_t float32_indx = 0; float32_indx < proto_float32_length; float32_indx++) {
    proto->add_float32(original_struct->float32[float32_indx]);
  }
  const size_t proto_int32_length = std::min(4, 4);
  for (uint32_t int32_indx = 0; int32_indx < proto_int32_length; int32_indx++) {
    proto->add_int32(original_struct->int32[int32_indx]);
  }
  const size_t proto_uint32_length = std::min(4, 4);
  for (uint32_t uint32_indx = 0; uint32_indx < proto_uint32_length; uint32_indx++) {
    proto->add_uint32(original_struct->uint32[uint32_indx]);
  }
}
void FillProtoFromStruct(vvk::server::VkClearDepthStencilValue* proto, const VkClearDepthStencilValue* original_struct) {
  proto->set_depth(original_struct->depth);
  proto->set_stencil(original_struct->stencil);
}
void FillProtoFromStruct(vvk::server::VkClearValue* proto, const VkClearValue* original_struct) {
  FillProtoFromStruct(proto->mutable_color(), &original_struct->color);
  FillProtoFromStruct(proto->mutable_depthstencil(), &original_struct->depthStencil);
}
void FillProtoFromStruct(vvk::server::VkCommandBufferAllocateInfo* proto, const VkCommandBufferAllocateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_commandpool(reinterpret_cast<uint64_t>(original_struct->commandPool));
  proto->set_level(static_cast<vvk::server::VkCommandBufferLevel>(original_struct->level));
  proto->set_commandbuffercount(original_struct->commandBufferCount);
}
void FillProtoFromStruct(vvk::server::VkCommandBufferBeginInfo* proto, const VkCommandBufferBeginInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  if (original_struct->pInheritanceInfo) {
    FillProtoFromStruct(proto->mutable_pinheritanceinfo(), original_struct->pInheritanceInfo);
  }
}
void FillProtoFromStruct(vvk::server::VkCommandBufferInheritanceInfo* proto, const VkCommandBufferInheritanceInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->renderPass) {
    proto->set_renderpass(reinterpret_cast<uint64_t>(original_struct->renderPass));
  }
  proto->set_subpass(original_struct->subpass);
  if (original_struct->framebuffer) {
    proto->set_framebuffer(reinterpret_cast<uint64_t>(original_struct->framebuffer));
  }
  proto->set_occlusionqueryenable(original_struct->occlusionQueryEnable);
  if (original_struct->queryFlags) {
    proto->set_queryflags(original_struct->queryFlags);
  }
  if (original_struct->pipelineStatistics) {
    proto->set_pipelinestatistics(original_struct->pipelineStatistics);
  }
}
void FillProtoFromStruct(vvk::server::VkCommandPoolCreateInfo* proto, const VkCommandPoolCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  proto->set_queuefamilyindex(original_struct->queueFamilyIndex);
}
void FillProtoFromStruct(vvk::server::VkComponentMapping* proto, const VkComponentMapping* original_struct) {
  proto->set_r(static_cast<vvk::server::VkComponentSwizzle>(original_struct->r));
  proto->set_g(static_cast<vvk::server::VkComponentSwizzle>(original_struct->g));
  proto->set_b(static_cast<vvk::server::VkComponentSwizzle>(original_struct->b));
  proto->set_a(static_cast<vvk::server::VkComponentSwizzle>(original_struct->a));
}
void FillProtoFromStruct(vvk::server::VkComputePipelineCreateInfo* proto, const VkComputePipelineCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  FillProtoFromStruct(proto->mutable_stage(), &original_struct->stage);
  proto->set_layout(reinterpret_cast<uint64_t>(original_struct->layout));
  if (original_struct->basePipelineHandle) {
    proto->set_basepipelinehandle(reinterpret_cast<uint64_t>(original_struct->basePipelineHandle));
  }
  proto->set_basepipelineindex(original_struct->basePipelineIndex);
}
void FillProtoFromStruct(vvk::server::VkConformanceVersion* proto, const VkConformanceVersion* original_struct) {
  proto->set_major(static_cast<uint32_t>(original_struct->major));
  proto->set_minor(static_cast<uint32_t>(original_struct->minor));
  proto->set_subminor(static_cast<uint32_t>(original_struct->subminor));
  proto->set_patch(static_cast<uint32_t>(original_struct->patch));
}
void FillProtoFromStruct(vvk::server::VkCopyDescriptorSet* proto, const VkCopyDescriptorSet* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_srcset(reinterpret_cast<uint64_t>(original_struct->srcSet));
  proto->set_srcbinding(original_struct->srcBinding);
  proto->set_srcarrayelement(original_struct->srcArrayElement);
  proto->set_dstset(reinterpret_cast<uint64_t>(original_struct->dstSet));
  proto->set_dstbinding(original_struct->dstBinding);
  proto->set_dstarrayelement(original_struct->dstArrayElement);
  proto->set_descriptorcount(original_struct->descriptorCount);
}
void FillProtoFromStruct(vvk::server::VkDescriptorBufferInfo* proto, const VkDescriptorBufferInfo* original_struct) {
  if (original_struct->buffer) {
    proto->set_buffer(reinterpret_cast<uint64_t>(original_struct->buffer));
  }
  proto->set_offset(static_cast<uint64_t>(original_struct->offset));
  proto->set_range(static_cast<uint64_t>(original_struct->range));
}
void FillProtoFromStruct(vvk::server::VkDescriptorImageInfo* proto, const VkDescriptorImageInfo* original_struct) {
  proto->set_sampler(reinterpret_cast<uint64_t>(original_struct->sampler));
  proto->set_imageview(reinterpret_cast<uint64_t>(original_struct->imageView));
  proto->set_imagelayout(static_cast<vvk::server::VkImageLayout>(original_struct->imageLayout));
}
void FillProtoFromStruct(vvk::server::VkDescriptorPoolCreateInfo* proto, const VkDescriptorPoolCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  proto->set_maxsets(original_struct->maxSets);
  if (original_struct->poolSizeCount) {
    proto->set_poolsizecount(original_struct->poolSizeCount);
  }
  const size_t proto_pPoolSizes_length = original_struct->poolSizeCount;
  for (uint32_t pPoolSizes_indx = 0; pPoolSizes_indx < proto_pPoolSizes_length; pPoolSizes_indx++) {
    FillProtoFromStruct(proto->add_ppoolsizes(), (&original_struct->pPoolSizes[pPoolSizes_indx]));
  }
}
void FillProtoFromStruct(vvk::server::VkDescriptorPoolSize* proto, const VkDescriptorPoolSize* original_struct) {
  proto->set_type(static_cast<vvk::server::VkDescriptorType>(original_struct->type));
  proto->set_descriptorcount(original_struct->descriptorCount);
}
void FillProtoFromStruct(vvk::server::VkDescriptorSetAllocateInfo* proto, const VkDescriptorSetAllocateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_descriptorpool(reinterpret_cast<uint64_t>(original_struct->descriptorPool));
  proto->set_descriptorsetcount(original_struct->descriptorSetCount);
  const size_t proto_pSetLayouts_length = original_struct->descriptorSetCount;
  for (uint32_t pSetLayouts_indx = 0; pSetLayouts_indx < proto_pSetLayouts_length; pSetLayouts_indx++) {
    proto->add_psetlayouts(reinterpret_cast<uint64_t>(original_struct->pSetLayouts[pSetLayouts_indx]));
  }
}
void FillProtoFromStruct(vvk::server::VkDescriptorSetLayoutBinding* proto, const VkDescriptorSetLayoutBinding* original_struct) {
  proto->set_binding(original_struct->binding);
  proto->set_descriptortype(static_cast<vvk::server::VkDescriptorType>(original_struct->descriptorType));
  if (original_struct->descriptorCount) {
    proto->set_descriptorcount(original_struct->descriptorCount);
  }
  proto->set_stageflags(original_struct->stageFlags);
  if (original_struct->pImmutableSamplers) {
    const size_t proto_pImmutableSamplers_length = original_struct->descriptorCount;
    for (uint32_t pImmutableSamplers_indx = 0; pImmutableSamplers_indx < proto_pImmutableSamplers_length; pImmutableSamplers_indx++) {
      proto->add_pimmutablesamplers(reinterpret_cast<uint64_t>(original_struct->pImmutableSamplers[pImmutableSamplers_indx]));
    }
  }
}
void FillProtoFromStruct(vvk::server::VkDescriptorSetLayoutCreateInfo* proto, const VkDescriptorSetLayoutCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  if (original_struct->bindingCount) {
    proto->set_bindingcount(original_struct->bindingCount);
  }
  const size_t proto_pBindings_length = original_struct->bindingCount;
  for (uint32_t pBindings_indx = 0; pBindings_indx < proto_pBindings_length; pBindings_indx++) {
    FillProtoFromStruct(proto->add_pbindings(), (&original_struct->pBindings[pBindings_indx]));
  }
}
void FillProtoFromStruct(vvk::server::VkDeviceCreateInfo* proto, const VkDeviceCreateInfo* original_struct) {
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
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  proto->set_queuecreateinfocount(original_struct->queueCreateInfoCount);
  const size_t proto_pQueueCreateInfos_length = original_struct->queueCreateInfoCount;
  for (uint32_t pQueueCreateInfos_indx = 0; pQueueCreateInfos_indx < proto_pQueueCreateInfos_length; pQueueCreateInfos_indx++) {
    FillProtoFromStruct(proto->add_pqueuecreateinfos(), (&original_struct->pQueueCreateInfos[pQueueCreateInfos_indx]));
  }
  if (original_struct->enabledLayerCount) {
    proto->set_enabledlayercount(original_struct->enabledLayerCount);
  }
  const size_t proto_ppEnabledLayerNames_length = original_struct->enabledLayerCount;
  for (uint32_t ppEnabledLayerNames_indx = 0; ppEnabledLayerNames_indx < proto_ppEnabledLayerNames_length; ppEnabledLayerNames_indx++) {
    proto->add_ppenabledlayernames(original_struct->ppEnabledLayerNames[ppEnabledLayerNames_indx]);
  }
  if (original_struct->enabledExtensionCount) {
    proto->set_enabledextensioncount(original_struct->enabledExtensionCount);
  }
  const size_t proto_ppEnabledExtensionNames_length = original_struct->enabledExtensionCount;
  for (uint32_t ppEnabledExtensionNames_indx = 0; ppEnabledExtensionNames_indx < proto_ppEnabledExtensionNames_length; ppEnabledExtensionNames_indx++) {
    proto->add_ppenabledextensionnames(original_struct->ppEnabledExtensionNames[ppEnabledExtensionNames_indx]);
  }
  if (original_struct->pEnabledFeatures) {
    FillProtoFromStruct(proto->mutable_penabledfeatures(), original_struct->pEnabledFeatures);
  }
}
void FillProtoFromStruct(vvk::server::VkDeviceQueueCreateInfo* proto, const VkDeviceQueueCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  proto->set_queuefamilyindex(original_struct->queueFamilyIndex);
  proto->set_queuecount(original_struct->queueCount);
  const size_t proto_pQueuePriorities_length = original_struct->queueCount;
  for (uint32_t pQueuePriorities_indx = 0; pQueuePriorities_indx < proto_pQueuePriorities_length; pQueuePriorities_indx++) {
    proto->add_pqueuepriorities(original_struct->pQueuePriorities[pQueuePriorities_indx]);
  }
}
void FillProtoFromStruct(vvk::server::VkExtent2D* proto, const VkExtent2D* original_struct) {
  proto->set_width(original_struct->width);
  proto->set_height(original_struct->height);
}
void FillProtoFromStruct(vvk::server::VkExtent3D* proto, const VkExtent3D* original_struct) {
  proto->set_width(original_struct->width);
  proto->set_height(original_struct->height);
  proto->set_depth(original_struct->depth);
}
void FillProtoFromStruct(vvk::server::VkFenceCreateInfo* proto, const VkFenceCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
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
void FillProtoFromStruct(vvk::server::VkFramebufferCreateInfo* proto, const VkFramebufferCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  proto->set_renderpass(reinterpret_cast<uint64_t>(original_struct->renderPass));
  if (original_struct->attachmentCount) {
    proto->set_attachmentcount(original_struct->attachmentCount);
  }
  const size_t proto_pAttachments_length = original_struct->attachmentCount;
  for (uint32_t pAttachments_indx = 0; pAttachments_indx < proto_pAttachments_length; pAttachments_indx++) {
    proto->add_pattachments(reinterpret_cast<uint64_t>(original_struct->pAttachments[pAttachments_indx]));
  }
  proto->set_width(original_struct->width);
  proto->set_height(original_struct->height);
  proto->set_layers(original_struct->layers);
}
void FillProtoFromStruct(vvk::server::VkGraphicsPipelineCreateInfo* proto, const VkGraphicsPipelineCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  if (original_struct->stageCount) {
    proto->set_stagecount(original_struct->stageCount);
  }
  if (original_struct->pStages) {
    const size_t proto_pStages_length = original_struct->stageCount;
    for (uint32_t pStages_indx = 0; pStages_indx < proto_pStages_length; pStages_indx++) {
      FillProtoFromStruct(proto->add_pstages(), (&original_struct->pStages[pStages_indx]));
    }
  }
  if (original_struct->pVertexInputState) {
    FillProtoFromStruct(proto->mutable_pvertexinputstate(), original_struct->pVertexInputState);
  }
  if (original_struct->pInputAssemblyState) {
    FillProtoFromStruct(proto->mutable_pinputassemblystate(), original_struct->pInputAssemblyState);
  }
  if (original_struct->pTessellationState) {
    FillProtoFromStruct(proto->mutable_ptessellationstate(), original_struct->pTessellationState);
  }
  if (original_struct->pViewportState) {
    FillProtoFromStruct(proto->mutable_pviewportstate(), original_struct->pViewportState);
  }
  if (original_struct->pRasterizationState) {
    FillProtoFromStruct(proto->mutable_prasterizationstate(), original_struct->pRasterizationState);
  }
  if (original_struct->pMultisampleState) {
    FillProtoFromStruct(proto->mutable_pmultisamplestate(), original_struct->pMultisampleState);
  }
  if (original_struct->pDepthStencilState) {
    FillProtoFromStruct(proto->mutable_pdepthstencilstate(), original_struct->pDepthStencilState);
  }
  if (original_struct->pColorBlendState) {
    FillProtoFromStruct(proto->mutable_pcolorblendstate(), original_struct->pColorBlendState);
  }
  if (original_struct->pDynamicState) {
    FillProtoFromStruct(proto->mutable_pdynamicstate(), original_struct->pDynamicState);
  }
  if (original_struct->layout) {
    proto->set_layout(reinterpret_cast<uint64_t>(original_struct->layout));
  }
  if (original_struct->renderPass) {
    proto->set_renderpass(reinterpret_cast<uint64_t>(original_struct->renderPass));
  }
  proto->set_subpass(original_struct->subpass);
  if (original_struct->basePipelineHandle) {
    proto->set_basepipelinehandle(reinterpret_cast<uint64_t>(original_struct->basePipelineHandle));
  }
  proto->set_basepipelineindex(original_struct->basePipelineIndex);
}
void FillProtoFromStruct(vvk::server::VkImageCreateInfo* proto, const VkImageCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  proto->set_imagetype(static_cast<vvk::server::VkImageType>(original_struct->imageType));
  proto->set_format(static_cast<vvk::server::VkFormat>(original_struct->format));
  FillProtoFromStruct(proto->mutable_extent(), &original_struct->extent);
  proto->set_miplevels(original_struct->mipLevels);
  proto->set_arraylayers(original_struct->arrayLayers);
  proto->set_samples(original_struct->samples);
  proto->set_tiling(static_cast<vvk::server::VkImageTiling>(original_struct->tiling));
  proto->set_usage(original_struct->usage);
  proto->set_sharingmode(static_cast<vvk::server::VkSharingMode>(original_struct->sharingMode));
  if (original_struct->queueFamilyIndexCount) {
    proto->set_queuefamilyindexcount(original_struct->queueFamilyIndexCount);
  }
  const size_t proto_pQueueFamilyIndices_length = original_struct->queueFamilyIndexCount;
  for (uint32_t pQueueFamilyIndices_indx = 0; pQueueFamilyIndices_indx < proto_pQueueFamilyIndices_length; pQueueFamilyIndices_indx++) {
    proto->add_pqueuefamilyindices(original_struct->pQueueFamilyIndices[pQueueFamilyIndices_indx]);
  }
  proto->set_initiallayout(static_cast<vvk::server::VkImageLayout>(original_struct->initialLayout));
}
void FillProtoFromStruct(vvk::server::VkImageMemoryBarrier* proto, const VkImageMemoryBarrier* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_srcaccessmask(original_struct->srcAccessMask);
  proto->set_dstaccessmask(original_struct->dstAccessMask);
  proto->set_oldlayout(static_cast<vvk::server::VkImageLayout>(original_struct->oldLayout));
  proto->set_newlayout(static_cast<vvk::server::VkImageLayout>(original_struct->newLayout));
  proto->set_srcqueuefamilyindex(original_struct->srcQueueFamilyIndex);
  proto->set_dstqueuefamilyindex(original_struct->dstQueueFamilyIndex);
  proto->set_image(reinterpret_cast<uint64_t>(original_struct->image));
  FillProtoFromStruct(proto->mutable_subresourcerange(), &original_struct->subresourceRange);
}
void FillProtoFromStruct(vvk::server::VkImageMemoryRequirementsInfo2* proto, const VkImageMemoryRequirementsInfo2* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_image(reinterpret_cast<uint64_t>(original_struct->image));
}
void FillProtoFromStruct(vvk::server::VkImageSubresource* proto, const VkImageSubresource* original_struct) {
  proto->set_aspectmask(original_struct->aspectMask);
  proto->set_miplevel(original_struct->mipLevel);
  proto->set_arraylayer(original_struct->arrayLayer);
}
void FillProtoFromStruct(vvk::server::VkImageSubresourceLayers* proto, const VkImageSubresourceLayers* original_struct) {
  proto->set_aspectmask(original_struct->aspectMask);
  proto->set_miplevel(original_struct->mipLevel);
  proto->set_basearraylayer(original_struct->baseArrayLayer);
  proto->set_layercount(original_struct->layerCount);
}
void FillProtoFromStruct(vvk::server::VkImageSubresourceRange* proto, const VkImageSubresourceRange* original_struct) {
  proto->set_aspectmask(original_struct->aspectMask);
  proto->set_basemiplevel(original_struct->baseMipLevel);
  proto->set_levelcount(original_struct->levelCount);
  proto->set_basearraylayer(original_struct->baseArrayLayer);
  proto->set_layercount(original_struct->layerCount);
}
void FillProtoFromStruct(vvk::server::VkImageViewCreateInfo* proto, const VkImageViewCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  proto->set_image(reinterpret_cast<uint64_t>(original_struct->image));
  proto->set_viewtype(static_cast<vvk::server::VkImageViewType>(original_struct->viewType));
  proto->set_format(static_cast<vvk::server::VkFormat>(original_struct->format));
  FillProtoFromStruct(proto->mutable_components(), &original_struct->components);
  FillProtoFromStruct(proto->mutable_subresourcerange(), &original_struct->subresourceRange);
}
void FillProtoFromStruct(vvk::server::VkInstanceCreateInfo* proto, const VkInstanceCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  if (original_struct->pApplicationInfo) {
    FillProtoFromStruct(proto->mutable_papplicationinfo(), original_struct->pApplicationInfo);
  }
  if (original_struct->enabledLayerCount) {
    proto->set_enabledlayercount(original_struct->enabledLayerCount);
  }
  const size_t proto_ppEnabledLayerNames_length = original_struct->enabledLayerCount;
  for (uint32_t ppEnabledLayerNames_indx = 0; ppEnabledLayerNames_indx < proto_ppEnabledLayerNames_length; ppEnabledLayerNames_indx++) {
    proto->add_ppenabledlayernames(original_struct->ppEnabledLayerNames[ppEnabledLayerNames_indx]);
  }
  if (original_struct->enabledExtensionCount) {
    proto->set_enabledextensioncount(original_struct->enabledExtensionCount);
  }
  const size_t proto_ppEnabledExtensionNames_length = original_struct->enabledExtensionCount;
  for (uint32_t ppEnabledExtensionNames_indx = 0; ppEnabledExtensionNames_indx < proto_ppEnabledExtensionNames_length; ppEnabledExtensionNames_indx++) {
    proto->add_ppenabledextensionnames(original_struct->ppEnabledExtensionNames[ppEnabledExtensionNames_indx]);
  }
}
void FillProtoFromStruct(vvk::server::VkMappedMemoryRange* proto, const VkMappedMemoryRange* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_memory(reinterpret_cast<uint64_t>(original_struct->memory));
  proto->set_offset(static_cast<uint64_t>(original_struct->offset));
  proto->set_size(static_cast<uint64_t>(original_struct->size));
}
void FillProtoFromStruct(vvk::server::VkMemoryAllocateInfo* proto, const VkMemoryAllocateInfo* original_struct) {
  if (original_struct->pNext) {
    const void* pNext = original_struct->pNext;
    while (pNext) {
      const VkBaseInStructure* base = reinterpret_cast<const VkBaseInStructure*>(pNext);
      if (base->sType == VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO) {
        FillProtoFromStruct(proto->add_pnext()->mutable_vkmemorydedicatedallocateinfo_chain_elem(), reinterpret_cast<const VkMemoryDedicatedAllocateInfo*>(pNext));
      }
      pNext = reinterpret_cast<const void*>(base->pNext);
    }
  }
  proto->set_allocationsize(static_cast<uint64_t>(original_struct->allocationSize));
  proto->set_memorytypeindex(original_struct->memoryTypeIndex);
}
void FillProtoFromStruct(vvk::server::VkMemoryBarrier* proto, const VkMemoryBarrier* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->srcAccessMask) {
    proto->set_srcaccessmask(original_struct->srcAccessMask);
  }
  if (original_struct->dstAccessMask) {
    proto->set_dstaccessmask(original_struct->dstAccessMask);
  }
}
void FillProtoFromStruct(vvk::server::VkMemoryDedicatedAllocateInfo* proto, const VkMemoryDedicatedAllocateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->image) {
    proto->set_image(reinterpret_cast<uint64_t>(original_struct->image));
  }
  if (original_struct->buffer) {
    proto->set_buffer(reinterpret_cast<uint64_t>(original_struct->buffer));
  }
}
void FillProtoFromStruct(vvk::server::VkMemoryDedicatedRequirements* proto, const VkMemoryDedicatedRequirements* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_prefersdedicatedallocation(original_struct->prefersDedicatedAllocation);
  proto->set_requiresdedicatedallocation(original_struct->requiresDedicatedAllocation);
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
    const void* pNext = original_struct->pNext;
    while (pNext) {
      const VkBaseInStructure* base = reinterpret_cast<const VkBaseInStructure*>(pNext);
      if (base->sType == VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS) {
        FillProtoFromStruct(proto->add_pnext()->mutable_vkmemorydedicatedrequirements_chain_elem(), reinterpret_cast<const VkMemoryDedicatedRequirements*>(pNext));
      }
      pNext = reinterpret_cast<const void*>(base->pNext);
    }
  }
  FillProtoFromStruct(proto->mutable_memoryrequirements(), &original_struct->memoryRequirements);
}
void FillProtoFromStruct(vvk::server::VkMemoryType* proto, const VkMemoryType* original_struct) {
  if (original_struct->propertyFlags) {
    proto->set_propertyflags(original_struct->propertyFlags);
  }
  proto->set_heapindex(original_struct->heapIndex);
}
void FillProtoFromStruct(vvk::server::VkOffset2D* proto, const VkOffset2D* original_struct) {
  proto->set_x(original_struct->x);
  proto->set_y(original_struct->y);
}
void FillProtoFromStruct(vvk::server::VkOffset3D* proto, const VkOffset3D* original_struct) {
  proto->set_x(original_struct->x);
  proto->set_y(original_struct->y);
  proto->set_z(original_struct->z);
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
void FillProtoFromStruct(vvk::server::VkPipelineCacheCreateInfo* proto, const VkPipelineCacheCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  if (original_struct->initialDataSize) {
    proto->set_initialdatasize(original_struct->initialDataSize);
  }
  const size_t proto_pInitialData_length = original_struct->initialDataSize;
  proto->set_pinitialdata(original_struct->pInitialData, proto_pInitialData_length);
}
void FillProtoFromStruct(vvk::server::VkPipelineColorBlendAttachmentState* proto, const VkPipelineColorBlendAttachmentState* original_struct) {
  proto->set_blendenable(original_struct->blendEnable);
  proto->set_srccolorblendfactor(static_cast<vvk::server::VkBlendFactor>(original_struct->srcColorBlendFactor));
  proto->set_dstcolorblendfactor(static_cast<vvk::server::VkBlendFactor>(original_struct->dstColorBlendFactor));
  proto->set_colorblendop(static_cast<vvk::server::VkBlendOp>(original_struct->colorBlendOp));
  proto->set_srcalphablendfactor(static_cast<vvk::server::VkBlendFactor>(original_struct->srcAlphaBlendFactor));
  proto->set_dstalphablendfactor(static_cast<vvk::server::VkBlendFactor>(original_struct->dstAlphaBlendFactor));
  proto->set_alphablendop(static_cast<vvk::server::VkBlendOp>(original_struct->alphaBlendOp));
  if (original_struct->colorWriteMask) {
    proto->set_colorwritemask(original_struct->colorWriteMask);
  }
}
void FillProtoFromStruct(vvk::server::VkPipelineColorBlendStateCreateInfo* proto, const VkPipelineColorBlendStateCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  proto->set_logicopenable(original_struct->logicOpEnable);
  proto->set_logicop(static_cast<vvk::server::VkLogicOp>(original_struct->logicOp));
  if (original_struct->attachmentCount) {
    proto->set_attachmentcount(original_struct->attachmentCount);
  }
  if (original_struct->pAttachments) {
    const size_t proto_pAttachments_length = original_struct->attachmentCount;
    for (uint32_t pAttachments_indx = 0; pAttachments_indx < proto_pAttachments_length; pAttachments_indx++) {
      FillProtoFromStruct(proto->add_pattachments(), (&original_struct->pAttachments[pAttachments_indx]));
    }
  }
  const size_t proto_blendConstants_length = std::min(4, 4);
  for (uint32_t blendConstants_indx = 0; blendConstants_indx < proto_blendConstants_length; blendConstants_indx++) {
    proto->add_blendconstants(original_struct->blendConstants[blendConstants_indx]);
  }
}
void FillProtoFromStruct(vvk::server::VkPipelineDepthStencilStateCreateInfo* proto, const VkPipelineDepthStencilStateCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  proto->set_depthtestenable(original_struct->depthTestEnable);
  proto->set_depthwriteenable(original_struct->depthWriteEnable);
  proto->set_depthcompareop(static_cast<vvk::server::VkCompareOp>(original_struct->depthCompareOp));
  proto->set_depthboundstestenable(original_struct->depthBoundsTestEnable);
  proto->set_stenciltestenable(original_struct->stencilTestEnable);
  FillProtoFromStruct(proto->mutable_front(), &original_struct->front);
  FillProtoFromStruct(proto->mutable_back(), &original_struct->back);
  proto->set_mindepthbounds(original_struct->minDepthBounds);
  proto->set_maxdepthbounds(original_struct->maxDepthBounds);
}
void FillProtoFromStruct(vvk::server::VkPipelineDynamicStateCreateInfo* proto, const VkPipelineDynamicStateCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  if (original_struct->dynamicStateCount) {
    proto->set_dynamicstatecount(original_struct->dynamicStateCount);
  }
  const size_t proto_pDynamicStates_length = original_struct->dynamicStateCount;
  for (uint32_t pDynamicStates_indx = 0; pDynamicStates_indx < proto_pDynamicStates_length; pDynamicStates_indx++) {
    proto->add_pdynamicstates(static_cast<vvk::server::VkDynamicState>(original_struct->pDynamicStates[pDynamicStates_indx]));
  }
}
void FillProtoFromStruct(vvk::server::VkPipelineInputAssemblyStateCreateInfo* proto, const VkPipelineInputAssemblyStateCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  proto->set_topology(static_cast<vvk::server::VkPrimitiveTopology>(original_struct->topology));
  proto->set_primitiverestartenable(original_struct->primitiveRestartEnable);
}
void FillProtoFromStruct(vvk::server::VkPipelineLayoutCreateInfo* proto, const VkPipelineLayoutCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  if (original_struct->setLayoutCount) {
    proto->set_setlayoutcount(original_struct->setLayoutCount);
  }
  const size_t proto_pSetLayouts_length = original_struct->setLayoutCount;
  for (uint32_t pSetLayouts_indx = 0; pSetLayouts_indx < proto_pSetLayouts_length; pSetLayouts_indx++) {
    proto->add_psetlayouts(reinterpret_cast<uint64_t>(original_struct->pSetLayouts[pSetLayouts_indx]));
  }
  if (original_struct->pushConstantRangeCount) {
    proto->set_pushconstantrangecount(original_struct->pushConstantRangeCount);
  }
  const size_t proto_pPushConstantRanges_length = original_struct->pushConstantRangeCount;
  for (uint32_t pPushConstantRanges_indx = 0; pPushConstantRanges_indx < proto_pPushConstantRanges_length; pPushConstantRanges_indx++) {
    FillProtoFromStruct(proto->add_ppushconstantranges(), (&original_struct->pPushConstantRanges[pPushConstantRanges_indx]));
  }
}
void FillProtoFromStruct(vvk::server::VkPipelineMultisampleStateCreateInfo* proto, const VkPipelineMultisampleStateCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  proto->set_rasterizationsamples(original_struct->rasterizationSamples);
  proto->set_sampleshadingenable(original_struct->sampleShadingEnable);
  proto->set_minsampleshading(original_struct->minSampleShading);
  if (original_struct->pSampleMask) {
    const size_t proto_pSampleMask_length = (original_struct->rasterizationSamples + 31) / 32;
    for (uint32_t pSampleMask_indx = 0; pSampleMask_indx < proto_pSampleMask_length; pSampleMask_indx++) {
      proto->add_psamplemask(static_cast<uint32_t>(original_struct->pSampleMask[pSampleMask_indx]));
    }
  }
  proto->set_alphatocoverageenable(original_struct->alphaToCoverageEnable);
  proto->set_alphatooneenable(original_struct->alphaToOneEnable);
}
void FillProtoFromStruct(vvk::server::VkPipelineRasterizationStateCreateInfo* proto, const VkPipelineRasterizationStateCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  proto->set_depthclampenable(original_struct->depthClampEnable);
  proto->set_rasterizerdiscardenable(original_struct->rasterizerDiscardEnable);
  proto->set_polygonmode(static_cast<vvk::server::VkPolygonMode>(original_struct->polygonMode));
  if (original_struct->cullMode) {
    proto->set_cullmode(original_struct->cullMode);
  }
  proto->set_frontface(static_cast<vvk::server::VkFrontFace>(original_struct->frontFace));
  proto->set_depthbiasenable(original_struct->depthBiasEnable);
  proto->set_depthbiasconstantfactor(original_struct->depthBiasConstantFactor);
  proto->set_depthbiasclamp(original_struct->depthBiasClamp);
  proto->set_depthbiasslopefactor(original_struct->depthBiasSlopeFactor);
  proto->set_linewidth(original_struct->lineWidth);
}
void FillProtoFromStruct(vvk::server::VkPipelineShaderStageCreateInfo* proto, const VkPipelineShaderStageCreateInfo* original_struct) {
  if (original_struct->pNext) {
    const void* pNext = original_struct->pNext;
    while (pNext) {
      const VkBaseInStructure* base = reinterpret_cast<const VkBaseInStructure*>(pNext);
      if (base->sType == VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO) {
        FillProtoFromStruct(proto->add_pnext()->mutable_vkshadermodulecreateinfo_chain_elem(), reinterpret_cast<const VkShaderModuleCreateInfo*>(pNext));
      }
      pNext = reinterpret_cast<const void*>(base->pNext);
    }
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  proto->set_stage(original_struct->stage);
  if (original_struct->module) {
    proto->set_module(reinterpret_cast<uint64_t>(original_struct->module));
  }
  proto->set_pname(original_struct->pName);
  if (original_struct->pSpecializationInfo) {
    FillProtoFromStruct(proto->mutable_pspecializationinfo(), original_struct->pSpecializationInfo);
  }
}
void FillProtoFromStruct(vvk::server::VkPipelineTessellationStateCreateInfo* proto, const VkPipelineTessellationStateCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  proto->set_patchcontrolpoints(original_struct->patchControlPoints);
}
void FillProtoFromStruct(vvk::server::VkPipelineVertexInputStateCreateInfo* proto, const VkPipelineVertexInputStateCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  if (original_struct->vertexBindingDescriptionCount) {
    proto->set_vertexbindingdescriptioncount(original_struct->vertexBindingDescriptionCount);
  }
  const size_t proto_pVertexBindingDescriptions_length = original_struct->vertexBindingDescriptionCount;
  for (uint32_t pVertexBindingDescriptions_indx = 0; pVertexBindingDescriptions_indx < proto_pVertexBindingDescriptions_length; pVertexBindingDescriptions_indx++) {
    FillProtoFromStruct(proto->add_pvertexbindingdescriptions(), (&original_struct->pVertexBindingDescriptions[pVertexBindingDescriptions_indx]));
  }
  if (original_struct->vertexAttributeDescriptionCount) {
    proto->set_vertexattributedescriptioncount(original_struct->vertexAttributeDescriptionCount);
  }
  const size_t proto_pVertexAttributeDescriptions_length = original_struct->vertexAttributeDescriptionCount;
  for (uint32_t pVertexAttributeDescriptions_indx = 0; pVertexAttributeDescriptions_indx < proto_pVertexAttributeDescriptions_length; pVertexAttributeDescriptions_indx++) {
    FillProtoFromStruct(proto->add_pvertexattributedescriptions(), (&original_struct->pVertexAttributeDescriptions[pVertexAttributeDescriptions_indx]));
  }
}
void FillProtoFromStruct(vvk::server::VkPipelineViewportStateCreateInfo* proto, const VkPipelineViewportStateCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  if (original_struct->viewportCount) {
    proto->set_viewportcount(original_struct->viewportCount);
  }
  if (original_struct->pViewports) {
    const size_t proto_pViewports_length = original_struct->viewportCount;
    for (uint32_t pViewports_indx = 0; pViewports_indx < proto_pViewports_length; pViewports_indx++) {
      FillProtoFromStruct(proto->add_pviewports(), (&original_struct->pViewports[pViewports_indx]));
    }
  }
  if (original_struct->scissorCount) {
    proto->set_scissorcount(original_struct->scissorCount);
  }
  if (original_struct->pScissors) {
    const size_t proto_pScissors_length = original_struct->scissorCount;
    for (uint32_t pScissors_indx = 0; pScissors_indx < proto_pScissors_length; pScissors_indx++) {
      FillProtoFromStruct(proto->add_pscissors(), (&original_struct->pScissors[pScissors_indx]));
    }
  }
}
void FillProtoFromStruct(vvk::server::VkProtectedSubmitInfo* proto, const VkProtectedSubmitInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_protectedsubmit(original_struct->protectedSubmit);
}
void FillProtoFromStruct(vvk::server::VkPushConstantRange* proto, const VkPushConstantRange* original_struct) {
  proto->set_stageflags(original_struct->stageFlags);
  proto->set_offset(original_struct->offset);
  proto->set_size(original_struct->size);
}
void FillProtoFromStruct(vvk::server::VkRect2D* proto, const VkRect2D* original_struct) {
  FillProtoFromStruct(proto->mutable_offset(), &original_struct->offset);
  FillProtoFromStruct(proto->mutable_extent(), &original_struct->extent);
}
void FillProtoFromStruct(vvk::server::VkRenderPassBeginInfo* proto, const VkRenderPassBeginInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_renderpass(reinterpret_cast<uint64_t>(original_struct->renderPass));
  proto->set_framebuffer(reinterpret_cast<uint64_t>(original_struct->framebuffer));
  FillProtoFromStruct(proto->mutable_renderarea(), &original_struct->renderArea);
  if (original_struct->clearValueCount) {
    proto->set_clearvaluecount(original_struct->clearValueCount);
  }
  const size_t proto_pClearValues_length = original_struct->clearValueCount;
  for (uint32_t pClearValues_indx = 0; pClearValues_indx < proto_pClearValues_length; pClearValues_indx++) {
    FillProtoFromStruct(proto->add_pclearvalues(), (&original_struct->pClearValues[pClearValues_indx]));
  }
}
void FillProtoFromStruct(vvk::server::VkRenderPassCreateInfo* proto, const VkRenderPassCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  if (original_struct->attachmentCount) {
    proto->set_attachmentcount(original_struct->attachmentCount);
  }
  const size_t proto_pAttachments_length = original_struct->attachmentCount;
  for (uint32_t pAttachments_indx = 0; pAttachments_indx < proto_pAttachments_length; pAttachments_indx++) {
    FillProtoFromStruct(proto->add_pattachments(), (&original_struct->pAttachments[pAttachments_indx]));
  }
  proto->set_subpasscount(original_struct->subpassCount);
  const size_t proto_pSubpasses_length = original_struct->subpassCount;
  for (uint32_t pSubpasses_indx = 0; pSubpasses_indx < proto_pSubpasses_length; pSubpasses_indx++) {
    FillProtoFromStruct(proto->add_psubpasses(), (&original_struct->pSubpasses[pSubpasses_indx]));
  }
  if (original_struct->dependencyCount) {
    proto->set_dependencycount(original_struct->dependencyCount);
  }
  const size_t proto_pDependencies_length = original_struct->dependencyCount;
  for (uint32_t pDependencies_indx = 0; pDependencies_indx < proto_pDependencies_length; pDependencies_indx++) {
    FillProtoFromStruct(proto->add_pdependencies(), (&original_struct->pDependencies[pDependencies_indx]));
  }
}
void FillProtoFromStruct(vvk::server::VkSamplerCreateInfo* proto, const VkSamplerCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  proto->set_magfilter(static_cast<vvk::server::VkFilter>(original_struct->magFilter));
  proto->set_minfilter(static_cast<vvk::server::VkFilter>(original_struct->minFilter));
  proto->set_mipmapmode(static_cast<vvk::server::VkSamplerMipmapMode>(original_struct->mipmapMode));
  proto->set_addressmodeu(static_cast<vvk::server::VkSamplerAddressMode>(original_struct->addressModeU));
  proto->set_addressmodev(static_cast<vvk::server::VkSamplerAddressMode>(original_struct->addressModeV));
  proto->set_addressmodew(static_cast<vvk::server::VkSamplerAddressMode>(original_struct->addressModeW));
  proto->set_miplodbias(original_struct->mipLodBias);
  proto->set_anisotropyenable(original_struct->anisotropyEnable);
  proto->set_maxanisotropy(original_struct->maxAnisotropy);
  proto->set_compareenable(original_struct->compareEnable);
  proto->set_compareop(static_cast<vvk::server::VkCompareOp>(original_struct->compareOp));
  proto->set_minlod(original_struct->minLod);
  proto->set_maxlod(original_struct->maxLod);
  proto->set_bordercolor(static_cast<vvk::server::VkBorderColor>(original_struct->borderColor));
  proto->set_unnormalizedcoordinates(original_struct->unnormalizedCoordinates);
}
void FillProtoFromStruct(vvk::server::VkSemaphoreCreateInfo* proto, const VkSemaphoreCreateInfo* original_struct) {
  if (original_struct->pNext) {
    const void* pNext = original_struct->pNext;
    while (pNext) {
      const VkBaseInStructure* base = reinterpret_cast<const VkBaseInStructure*>(pNext);
      if (base->sType == VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO) {
        FillProtoFromStruct(proto->add_pnext()->mutable_vksemaphoretypecreateinfo_chain_elem(), reinterpret_cast<const VkSemaphoreTypeCreateInfo*>(pNext));
      }
      pNext = reinterpret_cast<const void*>(base->pNext);
    }
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
}
void FillProtoFromStruct(vvk::server::VkSemaphoreSignalInfo* proto, const VkSemaphoreSignalInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_semaphore(reinterpret_cast<uint64_t>(original_struct->semaphore));
  proto->set_value(original_struct->value);
}
void FillProtoFromStruct(vvk::server::VkSemaphoreTypeCreateInfo* proto, const VkSemaphoreTypeCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_semaphoretype(static_cast<vvk::server::VkSemaphoreType>(original_struct->semaphoreType));
  proto->set_initialvalue(original_struct->initialValue);
}
void FillProtoFromStruct(vvk::server::VkShaderModuleCreateInfo* proto, const VkShaderModuleCreateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  proto->set_codesize(original_struct->codeSize);
  const size_t proto_pCode_length = original_struct->codeSize / 4;
  for (uint32_t pCode_indx = 0; pCode_indx < proto_pCode_length; pCode_indx++) {
    proto->add_pcode(original_struct->pCode[pCode_indx]);
  }
}
void FillProtoFromStruct(vvk::server::VkSpecializationInfo* proto, const VkSpecializationInfo* original_struct) {
  if (original_struct->mapEntryCount) {
    proto->set_mapentrycount(original_struct->mapEntryCount);
  }
  const size_t proto_pMapEntries_length = original_struct->mapEntryCount;
  for (uint32_t pMapEntries_indx = 0; pMapEntries_indx < proto_pMapEntries_length; pMapEntries_indx++) {
    FillProtoFromStruct(proto->add_pmapentries(), (&original_struct->pMapEntries[pMapEntries_indx]));
  }
  if (original_struct->dataSize) {
    proto->set_datasize(original_struct->dataSize);
  }
  const size_t proto_pData_length = original_struct->dataSize;
  proto->set_pdata(original_struct->pData, proto_pData_length);
}
void FillProtoFromStruct(vvk::server::VkSpecializationMapEntry* proto, const VkSpecializationMapEntry* original_struct) {
  proto->set_constantid(original_struct->constantID);
  proto->set_offset(original_struct->offset);
  proto->set_size(original_struct->size);
}
void FillProtoFromStruct(vvk::server::VkStencilOpState* proto, const VkStencilOpState* original_struct) {
  proto->set_failop(static_cast<vvk::server::VkStencilOp>(original_struct->failOp));
  proto->set_passop(static_cast<vvk::server::VkStencilOp>(original_struct->passOp));
  proto->set_depthfailop(static_cast<vvk::server::VkStencilOp>(original_struct->depthFailOp));
  proto->set_compareop(static_cast<vvk::server::VkCompareOp>(original_struct->compareOp));
  proto->set_comparemask(original_struct->compareMask);
  proto->set_writemask(original_struct->writeMask);
  proto->set_reference(original_struct->reference);
}
void FillProtoFromStruct(vvk::server::VkSubmitInfo* proto, const VkSubmitInfo* original_struct) {
  if (original_struct->pNext) {
    const void* pNext = original_struct->pNext;
    while (pNext) {
      const VkBaseInStructure* base = reinterpret_cast<const VkBaseInStructure*>(pNext);
      if (base->sType == VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO) {
        FillProtoFromStruct(proto->add_pnext()->mutable_vkprotectedsubmitinfo_chain_elem(), reinterpret_cast<const VkProtectedSubmitInfo*>(pNext));
      }
      if (base->sType == VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO) {
        FillProtoFromStruct(proto->add_pnext()->mutable_vktimelinesemaphoresubmitinfo_chain_elem(), reinterpret_cast<const VkTimelineSemaphoreSubmitInfo*>(pNext));
      }
      pNext = reinterpret_cast<const void*>(base->pNext);
    }
  }
  if (original_struct->waitSemaphoreCount) {
    proto->set_waitsemaphorecount(original_struct->waitSemaphoreCount);
  }
  const size_t proto_pWaitSemaphores_length = original_struct->waitSemaphoreCount;
  for (uint32_t pWaitSemaphores_indx = 0; pWaitSemaphores_indx < proto_pWaitSemaphores_length; pWaitSemaphores_indx++) {
    proto->add_pwaitsemaphores(reinterpret_cast<uint64_t>(original_struct->pWaitSemaphores[pWaitSemaphores_indx]));
  }
  const size_t proto_pWaitDstStageMask_length = original_struct->waitSemaphoreCount;
  for (uint32_t pWaitDstStageMask_indx = 0; pWaitDstStageMask_indx < proto_pWaitDstStageMask_length; pWaitDstStageMask_indx++) {
    proto->add_pwaitdststagemask(static_cast<VkPipelineStageFlags>(original_struct->pWaitDstStageMask[pWaitDstStageMask_indx]));
  }
  if (original_struct->commandBufferCount) {
    proto->set_commandbuffercount(original_struct->commandBufferCount);
  }
  const size_t proto_pCommandBuffers_length = original_struct->commandBufferCount;
  for (uint32_t pCommandBuffers_indx = 0; pCommandBuffers_indx < proto_pCommandBuffers_length; pCommandBuffers_indx++) {
    proto->add_pcommandbuffers(reinterpret_cast<uint64_t>(original_struct->pCommandBuffers[pCommandBuffers_indx]));
  }
  if (original_struct->signalSemaphoreCount) {
    proto->set_signalsemaphorecount(original_struct->signalSemaphoreCount);
  }
  const size_t proto_pSignalSemaphores_length = original_struct->signalSemaphoreCount;
  for (uint32_t pSignalSemaphores_indx = 0; pSignalSemaphores_indx < proto_pSignalSemaphores_length; pSignalSemaphores_indx++) {
    proto->add_psignalsemaphores(reinterpret_cast<uint64_t>(original_struct->pSignalSemaphores[pSignalSemaphores_indx]));
  }
}
void FillProtoFromStruct(vvk::server::VkSubpassDependency* proto, const VkSubpassDependency* original_struct) {
  proto->set_srcsubpass(original_struct->srcSubpass);
  proto->set_dstsubpass(original_struct->dstSubpass);
  if (original_struct->srcStageMask) {
    proto->set_srcstagemask(original_struct->srcStageMask);
  }
  if (original_struct->dstStageMask) {
    proto->set_dststagemask(original_struct->dstStageMask);
  }
  if (original_struct->srcAccessMask) {
    proto->set_srcaccessmask(original_struct->srcAccessMask);
  }
  if (original_struct->dstAccessMask) {
    proto->set_dstaccessmask(original_struct->dstAccessMask);
  }
  if (original_struct->dependencyFlags) {
    proto->set_dependencyflags(original_struct->dependencyFlags);
  }
}
void FillProtoFromStruct(vvk::server::VkSubpassDescription* proto, const VkSubpassDescription* original_struct) {
  if (original_struct->flags) {
    proto->set_flags(original_struct->flags);
  }
  proto->set_pipelinebindpoint(static_cast<vvk::server::VkPipelineBindPoint>(original_struct->pipelineBindPoint));
  if (original_struct->inputAttachmentCount) {
    proto->set_inputattachmentcount(original_struct->inputAttachmentCount);
  }
  const size_t proto_pInputAttachments_length = original_struct->inputAttachmentCount;
  for (uint32_t pInputAttachments_indx = 0; pInputAttachments_indx < proto_pInputAttachments_length; pInputAttachments_indx++) {
    FillProtoFromStruct(proto->add_pinputattachments(), (&original_struct->pInputAttachments[pInputAttachments_indx]));
  }
  if (original_struct->colorAttachmentCount) {
    proto->set_colorattachmentcount(original_struct->colorAttachmentCount);
  }
  const size_t proto_pColorAttachments_length = original_struct->colorAttachmentCount;
  for (uint32_t pColorAttachments_indx = 0; pColorAttachments_indx < proto_pColorAttachments_length; pColorAttachments_indx++) {
    FillProtoFromStruct(proto->add_pcolorattachments(), (&original_struct->pColorAttachments[pColorAttachments_indx]));
  }
  if (original_struct->pResolveAttachments) {
    const size_t proto_pResolveAttachments_length = original_struct->colorAttachmentCount;
    for (uint32_t pResolveAttachments_indx = 0; pResolveAttachments_indx < proto_pResolveAttachments_length; pResolveAttachments_indx++) {
      FillProtoFromStruct(proto->add_presolveattachments(), (&original_struct->pResolveAttachments[pResolveAttachments_indx]));
    }
  }
  if (original_struct->pDepthStencilAttachment) {
    FillProtoFromStruct(proto->mutable_pdepthstencilattachment(), original_struct->pDepthStencilAttachment);
  }
  if (original_struct->preserveAttachmentCount) {
    proto->set_preserveattachmentcount(original_struct->preserveAttachmentCount);
  }
  const size_t proto_pPreserveAttachments_length = original_struct->preserveAttachmentCount;
  for (uint32_t pPreserveAttachments_indx = 0; pPreserveAttachments_indx < proto_pPreserveAttachments_length; pPreserveAttachments_indx++) {
    proto->add_ppreserveattachments(original_struct->pPreserveAttachments[pPreserveAttachments_indx]);
  }
}
void FillProtoFromStruct(vvk::server::VkSubresourceLayout* proto, const VkSubresourceLayout* original_struct) {
  proto->set_offset(static_cast<uint64_t>(original_struct->offset));
  proto->set_size(static_cast<uint64_t>(original_struct->size));
  proto->set_rowpitch(static_cast<uint64_t>(original_struct->rowPitch));
  proto->set_arraypitch(static_cast<uint64_t>(original_struct->arrayPitch));
  proto->set_depthpitch(static_cast<uint64_t>(original_struct->depthPitch));
}
void FillProtoFromStruct(vvk::server::VkTimelineSemaphoreSubmitInfo* proto, const VkTimelineSemaphoreSubmitInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  if (original_struct->waitSemaphoreValueCount) {
    proto->set_waitsemaphorevaluecount(original_struct->waitSemaphoreValueCount);
  }
  if (original_struct->pWaitSemaphoreValues) {
    const size_t proto_pWaitSemaphoreValues_length = original_struct->waitSemaphoreValueCount;
    for (uint32_t pWaitSemaphoreValues_indx = 0; pWaitSemaphoreValues_indx < proto_pWaitSemaphoreValues_length; pWaitSemaphoreValues_indx++) {
      proto->add_pwaitsemaphorevalues(original_struct->pWaitSemaphoreValues[pWaitSemaphoreValues_indx]);
    }
  }
  if (original_struct->signalSemaphoreValueCount) {
    proto->set_signalsemaphorevaluecount(original_struct->signalSemaphoreValueCount);
  }
  if (original_struct->pSignalSemaphoreValues) {
    const size_t proto_pSignalSemaphoreValues_length = original_struct->signalSemaphoreValueCount;
    for (uint32_t pSignalSemaphoreValues_indx = 0; pSignalSemaphoreValues_indx < proto_pSignalSemaphoreValues_length; pSignalSemaphoreValues_indx++) {
      proto->add_psignalsemaphorevalues(original_struct->pSignalSemaphoreValues[pSignalSemaphoreValues_indx]);
    }
  }
}
void FillProtoFromStruct(vvk::server::VkVertexInputAttributeDescription* proto, const VkVertexInputAttributeDescription* original_struct) {
  proto->set_location(original_struct->location);
  proto->set_binding(original_struct->binding);
  proto->set_format(static_cast<vvk::server::VkFormat>(original_struct->format));
  proto->set_offset(original_struct->offset);
}
void FillProtoFromStruct(vvk::server::VkVertexInputBindingDescription* proto, const VkVertexInputBindingDescription* original_struct) {
  proto->set_binding(original_struct->binding);
  proto->set_stride(original_struct->stride);
  proto->set_inputrate(static_cast<vvk::server::VkVertexInputRate>(original_struct->inputRate));
}
void FillProtoFromStruct(vvk::server::VkViewport* proto, const VkViewport* original_struct) {
  proto->set_x(original_struct->x);
  proto->set_y(original_struct->y);
  proto->set_width(original_struct->width);
  proto->set_height(original_struct->height);
  proto->set_mindepth(original_struct->minDepth);
  proto->set_maxdepth(original_struct->maxDepth);
}
void FillProtoFromStruct(vvk::server::VkWriteDescriptorSet* proto, const VkWriteDescriptorSet* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
  proto->set_dstset(reinterpret_cast<uint64_t>(original_struct->dstSet));
  proto->set_dstbinding(original_struct->dstBinding);
  proto->set_dstarrayelement(original_struct->dstArrayElement);
  proto->set_descriptorcount(original_struct->descriptorCount);
  proto->set_descriptortype(static_cast<vvk::server::VkDescriptorType>(original_struct->descriptorType));
  const size_t proto_pImageInfo_length = original_struct->pImageInfo == nullptr ? 0 : original_struct->descriptorCount;
  for (uint32_t pImageInfo_indx = 0; pImageInfo_indx < proto_pImageInfo_length; pImageInfo_indx++) {
    FillProtoFromStruct(proto->add_pimageinfo(), (&original_struct->pImageInfo[pImageInfo_indx]));
  }
  const size_t proto_pBufferInfo_length = original_struct->pBufferInfo == nullptr ? 0 : original_struct->descriptorCount;
  for (uint32_t pBufferInfo_indx = 0; pBufferInfo_indx < proto_pBufferInfo_length; pBufferInfo_indx++) {
    FillProtoFromStruct(proto->add_pbufferinfo(), (&original_struct->pBufferInfo[pBufferInfo_indx]));
  }
  const size_t proto_pTexelBufferView_length = original_struct->pTexelBufferView == nullptr ? 0 : original_struct->descriptorCount;
  for (uint32_t pTexelBufferView_indx = 0; pTexelBufferView_indx < proto_pTexelBufferView_length; pTexelBufferView_indx++) {
    proto->add_ptexelbufferview(reinterpret_cast<uint64_t>(original_struct->pTexelBufferView[pTexelBufferView_indx]));
  }
}
void FillStructFromProto(VkConformanceVersion& original_struct, const vvk::server::VkConformanceVersion& proto) {
  original_struct.major = static_cast<uint8_t>(proto.major());
  original_struct.minor = static_cast<uint8_t>(proto.minor());
  original_struct.subminor = static_cast<uint8_t>(proto.subminor());
  original_struct.patch = static_cast<uint8_t>(proto.patch());
}
void FillStructFromProto(VkExtent3D& original_struct, const vvk::server::VkExtent3D& proto) {
  original_struct.width = proto.width();
  original_struct.height = proto.height();
  original_struct.depth = proto.depth();
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
void FillStructFromProto(VkMemoryType& original_struct, const vvk::server::VkMemoryType& proto) {
  if (proto.has_propertyflags()) {
    original_struct.propertyFlags = static_cast<VkMemoryPropertyFlags>(proto.propertyflags());
  } else {
    original_struct.propertyFlags = VkMemoryPropertyFlags{};
  }
  original_struct.heapIndex = proto.heapindex();
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
void FillStructFromProto(VkPhysicalDeviceSparseProperties& original_struct, const vvk::server::VkPhysicalDeviceSparseProperties& proto) {
  original_struct.residencyStandard2DBlockShape = proto.residencystandard2dblockshape();
  original_struct.residencyStandard2DMultisampleBlockShape = proto.residencystandard2dmultisampleblockshape();
  original_struct.residencyStandard3DBlockShape = proto.residencystandard3dblockshape();
  original_struct.residencyAlignedMipSize = proto.residencyalignedmipsize();
  original_struct.residencyNonResidentStrict = proto.residencynonresidentstrict();
}
void FillStructFromProtoNoPNext(VkMemoryDedicatedRequirements& original_struct, const vvk::server::VkMemoryDedicatedRequirements& proto) {
  original_struct.sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS;
  original_struct.prefersDedicatedAllocation = proto.prefersdedicatedallocation();
  original_struct.requiresDedicatedAllocation = proto.requiresdedicatedallocation();
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
}
VkResult PackAndCallVkCreateInstance(VvkCommandClientBidiStream& stream, const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateInstance");
  FillProtoFromStruct(request.mutable_vkcreateinstance()->mutable_pcreateinfo(), pCreateInfo);
  request.mutable_vkcreateinstance()->set_pinstance(reinterpret_cast<uint64_t>(*pInstance));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pInstance = reinterpret_cast<VkInstance>(response.vkcreateinstance().pinstance());
  return static_cast<VkResult>(response.vkcreateinstance().result());
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
    for (uint32_t pPhysicalDevices_indx = 0; pPhysicalDevices_indx < *pPhysicalDeviceCount; pPhysicalDevices_indx++) {
      pPhysicalDevices[pPhysicalDevices_indx] = reinterpret_cast<VkPhysicalDevice>(response.vkenumeratephysicaldevices().pphysicaldevices(pPhysicalDevices_indx));
    }
  }
  return static_cast<VkResult>(response.vkenumeratephysicaldevices().result());
}
void PackAndCallVkGetPhysicalDeviceProperties(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetPhysicalDeviceProperties");
  request.mutable_vkgetphysicaldeviceproperties()->set_physicaldevice(reinterpret_cast<uint64_t>(physicalDevice));
  FillProtoFromStruct(request.mutable_vkgetphysicaldeviceproperties()->mutable_pproperties(), pProperties);
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
  const size_t pProperties_ref_pipelineCacheUUID_length = std::min(VK_UUID_SIZE, VK_UUID_SIZE);
  for (uint32_t pipelineCacheUUID_indx = 0; pipelineCacheUUID_indx < pProperties_ref_pipelineCacheUUID_length; pipelineCacheUUID_indx++) {
    pProperties_ref.pipelineCacheUUID[pipelineCacheUUID_indx] = static_cast<uint8_t>(response.vkgetphysicaldeviceproperties().pproperties().pipelinecacheuuid(pipelineCacheUUID_indx));
  }
  VkPhysicalDeviceLimits &pProperties_ref_limits = pProperties_ref.limits;
  FillStructFromProto(pProperties_ref_limits, response.vkgetphysicaldeviceproperties().pproperties().limits());
  VkPhysicalDeviceSparseProperties &pProperties_ref_sparseProperties = pProperties_ref.sparseProperties;
  FillStructFromProto(pProperties_ref_sparseProperties, response.vkgetphysicaldeviceproperties().pproperties().sparseproperties());
}
void PackAndCallVkGetPhysicalDeviceFormatProperties(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties* pFormatProperties) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetPhysicalDeviceFormatProperties");
  request.mutable_vkgetphysicaldeviceformatproperties()->set_physicaldevice(reinterpret_cast<uint64_t>(physicalDevice));
  request.mutable_vkgetphysicaldeviceformatproperties()->set_format(static_cast<vvk::server::VkFormat>(format));
  FillProtoFromStruct(request.mutable_vkgetphysicaldeviceformatproperties()->mutable_pformatproperties(), pFormatProperties);
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
  FillProtoFromStruct(request.mutable_vkcreatedevice()->mutable_pcreateinfo(), pCreateInfo);
  request.mutable_vkcreatedevice()->set_pdevice(reinterpret_cast<uint64_t>(*pDevice));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pDevice = reinterpret_cast<VkDevice>(response.vkcreatedevice().pdevice());
  return static_cast<VkResult>(response.vkcreatedevice().result());
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
    for (uint32_t pProperties_indx = 0; pProperties_indx < *pPropertyCount; pProperties_indx++) {
      VkExtensionProperties& pProperties_ref = pProperties[pProperties_indx];
      strncpy(pProperties_ref.extensionName, response.vkenumerateinstanceextensionproperties().pproperties(pProperties_indx).extensionname().c_str(), VK_MAX_EXTENSION_NAME_SIZE);
      pProperties_ref.specVersion = response.vkenumerateinstanceextensionproperties().pproperties(pProperties_indx).specversion();
    }
  }
  return static_cast<VkResult>(response.vkenumerateinstanceextensionproperties().result());
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
    for (uint32_t pProperties_indx = 0; pProperties_indx < *pPropertyCount; pProperties_indx++) {
      VkExtensionProperties& pProperties_ref = pProperties[pProperties_indx];
      strncpy(pProperties_ref.extensionName, response.vkenumeratedeviceextensionproperties().pproperties(pProperties_indx).extensionname().c_str(), VK_MAX_EXTENSION_NAME_SIZE);
      pProperties_ref.specVersion = response.vkenumeratedeviceextensionproperties().pproperties(pProperties_indx).specversion();
    }
  }
  return static_cast<VkResult>(response.vkenumeratedeviceextensionproperties().result());
}
void PackAndCallVkGetPhysicalDeviceMemoryProperties(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* pMemoryProperties) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetPhysicalDeviceMemoryProperties");
  request.mutable_vkgetphysicaldevicememoryproperties()->set_physicaldevice(reinterpret_cast<uint64_t>(physicalDevice));
  FillProtoFromStruct(request.mutable_vkgetphysicaldevicememoryproperties()->mutable_pmemoryproperties(), pMemoryProperties);
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
    FillStructFromProto(pMemoryProperties_ref.memoryTypes[memoryTypes_indx], response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memorytypes(memoryTypes_indx));
  }
  pMemoryProperties_ref.memoryHeapCount = response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memoryheapcount();
  for (int memoryHeaps_indx = 0; memoryHeaps_indx < response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memoryheaps_size(); memoryHeaps_indx++) {
    FillStructFromProto(pMemoryProperties_ref.memoryHeaps[memoryHeaps_indx], response.vkgetphysicaldevicememoryproperties().pmemoryproperties().memoryheaps(memoryHeaps_indx));
  }
}
void PackAndCallVkGetPhysicalDeviceFeatures(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetPhysicalDeviceFeatures");
  request.mutable_vkgetphysicaldevicefeatures()->set_physicaldevice(reinterpret_cast<uint64_t>(physicalDevice));
  FillProtoFromStruct(request.mutable_vkgetphysicaldevicefeatures()->mutable_pfeatures(), pFeatures);
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
    for (uint32_t pQueueFamilyProperties_indx = 0; pQueueFamilyProperties_indx < *pQueueFamilyPropertyCount; pQueueFamilyProperties_indx++) {
      VkQueueFamilyProperties& pQueueFamilyProperties_ref = pQueueFamilyProperties[pQueueFamilyProperties_indx];
      if (response.vkgetphysicaldevicequeuefamilyproperties().pqueuefamilyproperties(pQueueFamilyProperties_indx).has_queueflags()) {
        pQueueFamilyProperties_ref.queueFlags = static_cast<VkQueueFlags>(response.vkgetphysicaldevicequeuefamilyproperties().pqueuefamilyproperties(pQueueFamilyProperties_indx).queueflags());
      } else {
        pQueueFamilyProperties_ref.queueFlags = VkQueueFlags{};
      }
      pQueueFamilyProperties_ref.queueCount = response.vkgetphysicaldevicequeuefamilyproperties().pqueuefamilyproperties(pQueueFamilyProperties_indx).queuecount();
      pQueueFamilyProperties_ref.timestampValidBits = response.vkgetphysicaldevicequeuefamilyproperties().pqueuefamilyproperties(pQueueFamilyProperties_indx).timestampvalidbits();
      VkExtent3D &pQueueFamilyProperties_ref_minImageTransferGranularity = pQueueFamilyProperties_ref.minImageTransferGranularity;
      FillStructFromProto(pQueueFamilyProperties_ref_minImageTransferGranularity, response.vkgetphysicaldevicequeuefamilyproperties().pqueuefamilyproperties(pQueueFamilyProperties_indx).minimagetransfergranularity());
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
  FillProtoFromStruct(request.mutable_vkcreatefence()->mutable_pcreateinfo(), pCreateInfo);
  request.mutable_vkcreatefence()->set_pfence(reinterpret_cast<uint64_t>(*pFence));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pFence = reinterpret_cast<VkFence>(response.vkcreatefence().pfence());
  return static_cast<VkResult>(response.vkcreatefence().result());
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
}
VkResult PackAndCallVkCreateSemaphore(VvkCommandClientBidiStream& stream, VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateSemaphore");
  request.mutable_vkcreatesemaphore()->set_device(reinterpret_cast<uint64_t>(device));
  FillProtoFromStruct(request.mutable_vkcreatesemaphore()->mutable_pcreateinfo(), pCreateInfo);
  request.mutable_vkcreatesemaphore()->set_psemaphore(reinterpret_cast<uint64_t>(*pSemaphore));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pSemaphore = reinterpret_cast<VkSemaphore>(response.vkcreatesemaphore().psemaphore());
  return static_cast<VkResult>(response.vkcreatesemaphore().result());
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
}
VkResult PackAndCallVkAllocateMemory(VvkCommandClientBidiStream& stream, VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory) {
  vvk::server::VvkRequest request;
  request.set_method("vkAllocateMemory");
  request.mutable_vkallocatememory()->set_device(reinterpret_cast<uint64_t>(device));
  FillProtoFromStruct(request.mutable_vkallocatememory()->mutable_pallocateinfo(), pAllocateInfo);
  request.mutable_vkallocatememory()->set_pmemory(reinterpret_cast<uint64_t>(*pMemory));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pMemory = reinterpret_cast<VkDeviceMemory>(response.vkallocatememory().pmemory());
  return static_cast<VkResult>(response.vkallocatememory().result());
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
}
VkResult PackAndCallVkCreateImage(VvkCommandClientBidiStream& stream, VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateImage");
  request.mutable_vkcreateimage()->set_device(reinterpret_cast<uint64_t>(device));
  FillProtoFromStruct(request.mutable_vkcreateimage()->mutable_pcreateinfo(), pCreateInfo);
  request.mutable_vkcreateimage()->set_pimage(reinterpret_cast<uint64_t>(*pImage));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pImage = reinterpret_cast<VkImage>(response.vkcreateimage().pimage());
  return static_cast<VkResult>(response.vkcreateimage().result());
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
  return static_cast<VkResult>(response.vkbindimagememory().result());
}
VkResult PackAndCallVkBindImageMemory2(VvkCommandClientBidiStream& stream, VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) {
  vvk::server::VvkRequest request;
  request.set_method("vkBindImageMemory2");
  request.mutable_vkbindimagememory2()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkbindimagememory2()->set_bindinfocount(bindInfoCount);
  for (uint32_t pBindInfos_indx = 0; pBindInfos_indx < bindInfoCount; pBindInfos_indx++) {
    FillProtoFromStruct(request.mutable_vkbindimagememory2()->add_pbindinfos(), &pBindInfos[pBindInfos_indx]);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.vkbindimagememory2().result());
}
void PackAndCallVkGetImageMemoryRequirements(VvkCommandClientBidiStream& stream, VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetImageMemoryRequirements");
  request.mutable_vkgetimagememoryrequirements()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkgetimagememoryrequirements()->set_image(reinterpret_cast<uint64_t>(image));
  FillProtoFromStruct(request.mutable_vkgetimagememoryrequirements()->mutable_pmemoryrequirements(), pMemoryRequirements);
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
  FillProtoFromStruct(request.mutable_vkgetimagememoryrequirements2()->mutable_pinfo(), pInfo);
  FillProtoFromStruct(request.mutable_vkgetimagememoryrequirements2()->mutable_pmemoryrequirements(), pMemoryRequirements);
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  VkMemoryRequirements2& pMemoryRequirements_ref = *pMemoryRequirements;
  pMemoryRequirements_ref.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
  VkBaseOutStructure* base = reinterpret_cast<VkBaseOutStructure*>(&pMemoryRequirements_ref);
  for (const auto& pnext : response.vkgetimagememoryrequirements2().pmemoryrequirements().pnext()) {
    if (pnext.has_vkmemorydedicatedrequirements_chain_elem()) {
      FillStructFromProtoNoPNext(*reinterpret_cast<VkMemoryDedicatedRequirements*>(base->pNext), pnext.vkmemorydedicatedrequirements_chain_elem());
    }
    base = base->pNext;
  }
  base->pNext = nullptr;
  VkMemoryRequirements &pMemoryRequirements_ref_memoryRequirements = pMemoryRequirements_ref.memoryRequirements;
  FillStructFromProto(pMemoryRequirements_ref_memoryRequirements, response.vkgetimagememoryrequirements2().pmemoryrequirements().memoryrequirements());
}
VkResult PackAndCallVkCreateImageView(VvkCommandClientBidiStream& stream, VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateImageView");
  request.mutable_vkcreateimageview()->set_device(reinterpret_cast<uint64_t>(device));
  FillProtoFromStruct(request.mutable_vkcreateimageview()->mutable_pcreateinfo(), pCreateInfo);
  request.mutable_vkcreateimageview()->set_pview(reinterpret_cast<uint64_t>(*pView));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pView = reinterpret_cast<VkImageView>(response.vkcreateimageview().pview());
  return static_cast<VkResult>(response.vkcreateimageview().result());
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
}
VkResult PackAndCallVkCreateCommandPool(VvkCommandClientBidiStream& stream, VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateCommandPool");
  request.mutable_vkcreatecommandpool()->set_device(reinterpret_cast<uint64_t>(device));
  FillProtoFromStruct(request.mutable_vkcreatecommandpool()->mutable_pcreateinfo(), pCreateInfo);
  request.mutable_vkcreatecommandpool()->set_pcommandpool(reinterpret_cast<uint64_t>(*pCommandPool));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pCommandPool = reinterpret_cast<VkCommandPool>(response.vkcreatecommandpool().pcommandpool());
  return static_cast<VkResult>(response.vkcreatecommandpool().result());
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
}
VkResult PackAndCallVkAllocateCommandBuffers(VvkCommandClientBidiStream& stream, VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers) {
  vvk::server::VvkRequest request;
  request.set_method("vkAllocateCommandBuffers");
  request.mutable_vkallocatecommandbuffers()->set_device(reinterpret_cast<uint64_t>(device));
  FillProtoFromStruct(request.mutable_vkallocatecommandbuffers()->mutable_pallocateinfo(), pAllocateInfo);
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  for (uint32_t i = 0; i < pAllocateInfo->commandBufferCount; i++) {
    pCommandBuffers[i] = reinterpret_cast<VkCommandBuffer>(response.vkallocatecommandbuffers().pcommandbuffers(i));
  }
  return static_cast<VkResult>(response.vkallocatecommandbuffers().result());
}
void PackAndCallVkFreeCommandBuffers(VvkCommandClientBidiStream& stream, VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) {
  vvk::server::VvkRequest request;
  request.set_method("vkFreeCommandBuffers");
  request.mutable_vkfreecommandbuffers()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkfreecommandbuffers()->set_commandpool(reinterpret_cast<uint64_t>(commandPool));
  request.mutable_vkfreecommandbuffers()->set_commandbuffercount(commandBufferCount);
  for (uint32_t i = 0; i < commandBufferCount; i++) {
    request.mutable_vkfreecommandbuffers()->add_pcommandbuffers(reinterpret_cast<uint64_t>(pCommandBuffers[i]));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }
}
VkResult PackAndCallVkBeginCommandBuffer(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo) {
  vvk::server::VvkRequest request;
  request.set_method("vkBeginCommandBuffer");
  request.mutable_vkbegincommandbuffer()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  FillProtoFromStruct(request.mutable_vkbegincommandbuffer()->mutable_pbegininfo(), pBeginInfo);
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.vkbegincommandbuffer().result());
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
  return static_cast<VkResult>(response.vkendcommandbuffer().result());
}
void PackAndCallVkGetImageSubresourceLayout(VvkCommandClientBidiStream& stream, VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetImageSubresourceLayout");
  request.mutable_vkgetimagesubresourcelayout()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkgetimagesubresourcelayout()->set_image(reinterpret_cast<uint64_t>(image));
  FillProtoFromStruct(request.mutable_vkgetimagesubresourcelayout()->mutable_psubresource(), pSubresource);
  FillProtoFromStruct(request.mutable_vkgetimagesubresourcelayout()->mutable_playout(), pLayout);
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
  FillProtoFromStruct(request.mutable_vkcreaterenderpass()->mutable_pcreateinfo(), pCreateInfo);
  request.mutable_vkcreaterenderpass()->set_prenderpass(reinterpret_cast<uint64_t>(*pRenderPass));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pRenderPass = reinterpret_cast<VkRenderPass>(response.vkcreaterenderpass().prenderpass());
  return static_cast<VkResult>(response.vkcreaterenderpass().result());
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
}
VkResult PackAndCallVkCreatePipelineLayout(VvkCommandClientBidiStream& stream, VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreatePipelineLayout");
  request.mutable_vkcreatepipelinelayout()->set_device(reinterpret_cast<uint64_t>(device));
  FillProtoFromStruct(request.mutable_vkcreatepipelinelayout()->mutable_pcreateinfo(), pCreateInfo);
  request.mutable_vkcreatepipelinelayout()->set_ppipelinelayout(reinterpret_cast<uint64_t>(*pPipelineLayout));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pPipelineLayout = reinterpret_cast<VkPipelineLayout>(response.vkcreatepipelinelayout().ppipelinelayout());
  return static_cast<VkResult>(response.vkcreatepipelinelayout().result());
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
}
VkResult PackAndCallVkCreateShaderModule(VvkCommandClientBidiStream& stream, VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateShaderModule");
  request.mutable_vkcreateshadermodule()->set_device(reinterpret_cast<uint64_t>(device));
  FillProtoFromStruct(request.mutable_vkcreateshadermodule()->mutable_pcreateinfo(), pCreateInfo);
  request.mutable_vkcreateshadermodule()->set_pshadermodule(reinterpret_cast<uint64_t>(*pShaderModule));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pShaderModule = reinterpret_cast<VkShaderModule>(response.vkcreateshadermodule().pshadermodule());
  return static_cast<VkResult>(response.vkcreateshadermodule().result());
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
}
VkResult PackAndCallVkCreateGraphicsPipelines(VvkCommandClientBidiStream& stream, VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateGraphicsPipelines");
  request.mutable_vkcreategraphicspipelines()->set_device(reinterpret_cast<uint64_t>(device));
  if (pipelineCache) {
    request.mutable_vkcreategraphicspipelines()->set_pipelinecache(reinterpret_cast<uint64_t>(pipelineCache));
  }
  request.mutable_vkcreategraphicspipelines()->set_createinfocount(createInfoCount);
  for (uint32_t pCreateInfos_indx = 0; pCreateInfos_indx < createInfoCount; pCreateInfos_indx++) {
    FillProtoFromStruct(request.mutable_vkcreategraphicspipelines()->add_pcreateinfos(), &pCreateInfos[pCreateInfos_indx]);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  for (uint32_t i = 0; i < createInfoCount; i++) {
    pPipelines[i] = reinterpret_cast<VkPipeline>(response.vkcreategraphicspipelines().ppipelines(i));
  }
  return static_cast<VkResult>(response.vkcreategraphicspipelines().result());
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
}
VkResult PackAndCallVkCreateFramebuffer(VvkCommandClientBidiStream& stream, VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateFramebuffer");
  request.mutable_vkcreateframebuffer()->set_device(reinterpret_cast<uint64_t>(device));
  FillProtoFromStruct(request.mutable_vkcreateframebuffer()->mutable_pcreateinfo(), pCreateInfo);
  request.mutable_vkcreateframebuffer()->set_pframebuffer(reinterpret_cast<uint64_t>(*pFramebuffer));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pFramebuffer = reinterpret_cast<VkFramebuffer>(response.vkcreateframebuffer().pframebuffer());
  return static_cast<VkResult>(response.vkcreateframebuffer().result());
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
}
VkResult PackAndCallVkWaitForFences(VvkCommandClientBidiStream& stream, VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout) {
  vvk::server::VvkRequest request;
  request.set_method("vkWaitForFences");
  request.mutable_vkwaitforfences()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkwaitforfences()->set_fencecount(fenceCount);
  for (uint32_t i = 0; i < fenceCount; i++) {
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
  return static_cast<VkResult>(response.vkwaitforfences().result());
}
VkResult PackAndCallVkResetFences(VvkCommandClientBidiStream& stream, VkDevice device, uint32_t fenceCount, const VkFence* pFences) {
  vvk::server::VvkRequest request;
  request.set_method("vkResetFences");
  request.mutable_vkresetfences()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkresetfences()->set_fencecount(fenceCount);
  for (uint32_t i = 0; i < fenceCount; i++) {
    request.mutable_vkresetfences()->add_pfences(reinterpret_cast<uint64_t>(pFences[i]));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.vkresetfences().result());
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
  return static_cast<VkResult>(response.vkresetcommandpool().result());
}
void PackAndCallVkCmdBeginRenderPass(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents) {
  vvk::server::VvkRequest request;
  request.set_method("vkCmdBeginRenderPass");
  request.mutable_vkcmdbeginrenderpass()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  FillProtoFromStruct(request.mutable_vkcmdbeginrenderpass()->mutable_prenderpassbegin(), pRenderPassBegin);
  request.mutable_vkcmdbeginrenderpass()->set_contents(static_cast<vvk::server::VkSubpassContents>(contents));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
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
}
void PackAndCallVkCmdSetViewport(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports) {
  vvk::server::VvkRequest request;
  request.set_method("vkCmdSetViewport");
  request.mutable_vkcmdsetviewport()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  request.mutable_vkcmdsetviewport()->set_firstviewport(firstViewport);
  request.mutable_vkcmdsetviewport()->set_viewportcount(viewportCount);
  for (uint32_t pViewports_indx = 0; pViewports_indx < viewportCount; pViewports_indx++) {
    FillProtoFromStruct(request.mutable_vkcmdsetviewport()->add_pviewports(), &pViewports[pViewports_indx]);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }
}
void PackAndCallVkCmdSetScissor(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors) {
  vvk::server::VvkRequest request;
  request.set_method("vkCmdSetScissor");
  request.mutable_vkcmdsetscissor()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  request.mutable_vkcmdsetscissor()->set_firstscissor(firstScissor);
  request.mutable_vkcmdsetscissor()->set_scissorcount(scissorCount);
  for (uint32_t pScissors_indx = 0; pScissors_indx < scissorCount; pScissors_indx++) {
    FillProtoFromStruct(request.mutable_vkcmdsetscissor()->add_pscissors(), &pScissors[pScissors_indx]);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
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
}
VkResult PackAndCallVkQueueSubmit(VvkCommandClientBidiStream& stream, VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence) {
  vvk::server::VvkRequest request;
  request.set_method("vkQueueSubmit");
  request.mutable_vkqueuesubmit()->set_queue(reinterpret_cast<uint64_t>(queue));
  if (submitCount) {
    request.mutable_vkqueuesubmit()->set_submitcount(submitCount);
  }
  for (uint32_t pSubmits_indx = 0; pSubmits_indx < submitCount; pSubmits_indx++) {
    FillProtoFromStruct(request.mutable_vkqueuesubmit()->add_psubmits(), &pSubmits[pSubmits_indx]);
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
  return static_cast<VkResult>(response.vkqueuesubmit().result());
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
  return static_cast<VkResult>(response.vkdevicewaitidle().result());
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
  return static_cast<VkResult>(response.vkqueuewaitidle().result());
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
  for (uint32_t pMemoryBarriers_indx = 0; pMemoryBarriers_indx < memoryBarrierCount; pMemoryBarriers_indx++) {
    FillProtoFromStruct(request.mutable_vkcmdpipelinebarrier()->add_pmemorybarriers(), &pMemoryBarriers[pMemoryBarriers_indx]);
  }
  if (bufferMemoryBarrierCount) {
    request.mutable_vkcmdpipelinebarrier()->set_buffermemorybarriercount(bufferMemoryBarrierCount);
  }
  for (uint32_t pBufferMemoryBarriers_indx = 0; pBufferMemoryBarriers_indx < bufferMemoryBarrierCount; pBufferMemoryBarriers_indx++) {
    FillProtoFromStruct(request.mutable_vkcmdpipelinebarrier()->add_pbuffermemorybarriers(), &pBufferMemoryBarriers[pBufferMemoryBarriers_indx]);
  }
  if (imageMemoryBarrierCount) {
    request.mutable_vkcmdpipelinebarrier()->set_imagememorybarriercount(imageMemoryBarrierCount);
  }
  for (uint32_t pImageMemoryBarriers_indx = 0; pImageMemoryBarriers_indx < imageMemoryBarrierCount; pImageMemoryBarriers_indx++) {
    FillProtoFromStruct(request.mutable_vkcmdpipelinebarrier()->add_pimagememorybarriers(), &pImageMemoryBarriers[pImageMemoryBarriers_indx]);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
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
  for (uint32_t pRegions_indx = 0; pRegions_indx < regionCount; pRegions_indx++) {
    FillProtoFromStruct(request.mutable_vkcmdcopyimagetobuffer()->add_pregions(), &pRegions[pRegions_indx]);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }
}
void PackAndCallVkGetPhysicalDeviceProperties2(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2* pProperties) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetPhysicalDeviceProperties2");
  request.mutable_vkgetphysicaldeviceproperties2()->set_physicaldevice(reinterpret_cast<uint64_t>(physicalDevice));
  FillProtoFromStruct(request.mutable_vkgetphysicaldeviceproperties2()->mutable_pproperties(), pProperties);
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  VkPhysicalDeviceProperties2& pProperties_ref = *pProperties;
  pProperties_ref.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
  VkBaseOutStructure* base = reinterpret_cast<VkBaseOutStructure*>(&pProperties_ref);
  for (const auto& pnext : response.vkgetphysicaldeviceproperties2().pproperties().pnext()) {
    if (pnext.has_vkphysicaldeviceprotectedmemoryproperties_chain_elem()) {
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceProtectedMemoryProperties*>(base->pNext), pnext.vkphysicaldeviceprotectedmemoryproperties_chain_elem());
    }
    if (pnext.has_vkphysicaldevicesubgroupproperties_chain_elem()) {
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceSubgroupProperties*>(base->pNext), pnext.vkphysicaldevicesubgroupproperties_chain_elem());
    }
    if (pnext.has_vkphysicaldevicetimelinesemaphoreproperties_chain_elem()) {
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceTimelineSemaphoreProperties*>(base->pNext), pnext.vkphysicaldevicetimelinesemaphoreproperties_chain_elem());
    }
    if (pnext.has_vkphysicaldevicevulkan11properties_chain_elem()) {
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceVulkan11Properties*>(base->pNext), pnext.vkphysicaldevicevulkan11properties_chain_elem());
    }
    if (pnext.has_vkphysicaldevicevulkan12properties_chain_elem()) {
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceVulkan12Properties*>(base->pNext), pnext.vkphysicaldevicevulkan12properties_chain_elem());
    }
    if (pnext.has_vkphysicaldevicevulkan13properties_chain_elem()) {
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceVulkan13Properties*>(base->pNext), pnext.vkphysicaldevicevulkan13properties_chain_elem());
    }
    if (pnext.has_vkphysicaldevicevulkan14properties_chain_elem()) {
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceVulkan14Properties*>(base->pNext), pnext.vkphysicaldevicevulkan14properties_chain_elem());
    }
    base = base->pNext;
  }
  base->pNext = nullptr;
  VkPhysicalDeviceProperties &pProperties_ref_properties = pProperties_ref.properties;
  FillStructFromProto(pProperties_ref_properties, response.vkgetphysicaldeviceproperties2().pproperties().properties());
}
void PackAndCallVkGetPhysicalDeviceFeatures2(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2* pFeatures) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetPhysicalDeviceFeatures2");
  request.mutable_vkgetphysicaldevicefeatures2()->set_physicaldevice(reinterpret_cast<uint64_t>(physicalDevice));
  FillProtoFromStruct(request.mutable_vkgetphysicaldevicefeatures2()->mutable_pfeatures(), pFeatures);
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  VkPhysicalDeviceFeatures2& pFeatures_ref = *pFeatures;
  pFeatures_ref.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
  VkBaseOutStructure* base = reinterpret_cast<VkBaseOutStructure*>(&pFeatures_ref);
  for (const auto& pnext : response.vkgetphysicaldevicefeatures2().pfeatures().pnext()) {
    if (pnext.has_vkphysicaldeviceprotectedmemoryfeatures_chain_elem()) {
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceProtectedMemoryFeatures*>(base->pNext), pnext.vkphysicaldeviceprotectedmemoryfeatures_chain_elem());
    }
    if (pnext.has_vkphysicaldeviceshaderdrawparametersfeatures_chain_elem()) {
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceShaderDrawParametersFeatures*>(base->pNext), pnext.vkphysicaldeviceshaderdrawparametersfeatures_chain_elem());
    }
    if (pnext.has_vkphysicaldevicetimelinesemaphorefeatures_chain_elem()) {
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceTimelineSemaphoreFeatures*>(base->pNext), pnext.vkphysicaldevicetimelinesemaphorefeatures_chain_elem());
    }
    if (pnext.has_vkphysicaldevicevulkan11features_chain_elem()) {
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceVulkan11Features*>(base->pNext), pnext.vkphysicaldevicevulkan11features_chain_elem());
    }
    if (pnext.has_vkphysicaldevicevulkan12features_chain_elem()) {
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceVulkan12Features*>(base->pNext), pnext.vkphysicaldevicevulkan12features_chain_elem());
    }
    if (pnext.has_vkphysicaldevicevulkan13features_chain_elem()) {
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceVulkan13Features*>(base->pNext), pnext.vkphysicaldevicevulkan13features_chain_elem());
    }
    if (pnext.has_vkphysicaldevicevulkan14features_chain_elem()) {
      FillStructFromProtoNoPNext(*reinterpret_cast<VkPhysicalDeviceVulkan14Features*>(base->pNext), pnext.vkphysicaldevicevulkan14features_chain_elem());
    }
    base = base->pNext;
  }
  base->pNext = nullptr;
  VkPhysicalDeviceFeatures &pFeatures_ref_features = pFeatures_ref.features;
  FillStructFromProto(pFeatures_ref_features, response.vkgetphysicaldevicefeatures2().pfeatures().features());
}
VkResult PackAndCallVkSignalSemaphore(VvkCommandClientBidiStream& stream, VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) {
  vvk::server::VvkRequest request;
  request.set_method("vkSignalSemaphore");
  request.mutable_vksignalsemaphore()->set_device(reinterpret_cast<uint64_t>(device));
  FillProtoFromStruct(request.mutable_vksignalsemaphore()->mutable_psignalinfo(), pSignalInfo);
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.vksignalsemaphore().result());
}
VkResult PackAndCallVkCreateBuffer(VvkCommandClientBidiStream& stream, VkDevice device, const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateBuffer");
  request.mutable_vkcreatebuffer()->set_device(reinterpret_cast<uint64_t>(device));
  FillProtoFromStruct(request.mutable_vkcreatebuffer()->mutable_pcreateinfo(), pCreateInfo);
  request.mutable_vkcreatebuffer()->set_pbuffer(reinterpret_cast<uint64_t>(*pBuffer));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pBuffer = reinterpret_cast<VkBuffer>(response.vkcreatebuffer().pbuffer());
  return static_cast<VkResult>(response.vkcreatebuffer().result());
}
void PackAndCallVkDestroyBuffer(VvkCommandClientBidiStream& stream, VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkDestroyBuffer");
  request.mutable_vkdestroybuffer()->set_device(reinterpret_cast<uint64_t>(device));
  if (buffer) {
    request.mutable_vkdestroybuffer()->set_buffer(reinterpret_cast<uint64_t>(buffer));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }
}
void PackAndCallVkGetBufferMemoryRequirements(VvkCommandClientBidiStream& stream, VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetBufferMemoryRequirements");
  request.mutable_vkgetbuffermemoryrequirements()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkgetbuffermemoryrequirements()->set_buffer(reinterpret_cast<uint64_t>(buffer));
  FillProtoFromStruct(request.mutable_vkgetbuffermemoryrequirements()->mutable_pmemoryrequirements(), pMemoryRequirements);
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  VkMemoryRequirements& pMemoryRequirements_ref = *pMemoryRequirements;
  pMemoryRequirements_ref.size = static_cast<VkDeviceSize>(response.vkgetbuffermemoryrequirements().pmemoryrequirements().size());
  pMemoryRequirements_ref.alignment = static_cast<VkDeviceSize>(response.vkgetbuffermemoryrequirements().pmemoryrequirements().alignment());
  pMemoryRequirements_ref.memoryTypeBits = response.vkgetbuffermemoryrequirements().pmemoryrequirements().memorytypebits();
}
VkResult PackAndCallVkBindBufferMemory(VvkCommandClientBidiStream& stream, VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) {
  vvk::server::VvkRequest request;
  request.set_method("vkBindBufferMemory");
  request.mutable_vkbindbuffermemory()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkbindbuffermemory()->set_buffer(reinterpret_cast<uint64_t>(buffer));
  request.mutable_vkbindbuffermemory()->set_memory(reinterpret_cast<uint64_t>(memory));
  request.mutable_vkbindbuffermemory()->set_memoryoffset(static_cast<uint64_t>(memoryOffset));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.vkbindbuffermemory().result());
}
VkResult PackAndCallVkMapMemory(VvkCommandClientBidiStream& stream, VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData) {
  vvk::server::VvkRequest request;
  request.set_method("vkMapMemory");
  request.mutable_vkmapmemory()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkmapmemory()->set_memory(reinterpret_cast<uint64_t>(memory));
  request.mutable_vkmapmemory()->set_offset(static_cast<uint64_t>(offset));
  request.mutable_vkmapmemory()->set_size(static_cast<uint64_t>(size));
  if (flags) {
    request.mutable_vkmapmemory()->set_flags(flags);
  }
  request.mutable_vkmapmemory()->set_ppdata(reinterpret_cast<uint64_t>(*ppData));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *ppData = reinterpret_cast<void*>(response.vkmapmemory().ppdata());
  return static_cast<VkResult>(response.vkmapmemory().result());
}
void PackAndCallVkUnmapMemory(VvkCommandClientBidiStream& stream, VkDevice device, VkDeviceMemory memory) {
  vvk::server::VvkRequest request;
  request.set_method("vkUnmapMemory");
  request.mutable_vkunmapmemory()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkunmapmemory()->set_memory(reinterpret_cast<uint64_t>(memory));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }
}
void PackAndCallVkCmdBindVertexBuffers(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets) {
  vvk::server::VvkRequest request;
  request.set_method("vkCmdBindVertexBuffers");
  request.mutable_vkcmdbindvertexbuffers()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  request.mutable_vkcmdbindvertexbuffers()->set_firstbinding(firstBinding);
  request.mutable_vkcmdbindvertexbuffers()->set_bindingcount(bindingCount);
  for (uint32_t i = 0; i < bindingCount; i++) {
    request.mutable_vkcmdbindvertexbuffers()->add_pbuffers(reinterpret_cast<uint64_t>(pBuffers[i]));
  }
  for (uint32_t i = 0; i < bindingCount; i++) {
    request.mutable_vkcmdbindvertexbuffers()->add_poffsets(static_cast<uint64_t>(pOffsets[i]));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }
}
VkResult PackAndCallVkCreateSampler(VvkCommandClientBidiStream& stream, VkDevice device, const VkSamplerCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateSampler");
  request.mutable_vkcreatesampler()->set_device(reinterpret_cast<uint64_t>(device));
  FillProtoFromStruct(request.mutable_vkcreatesampler()->mutable_pcreateinfo(), pCreateInfo);
  request.mutable_vkcreatesampler()->set_psampler(reinterpret_cast<uint64_t>(*pSampler));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pSampler = reinterpret_cast<VkSampler>(response.vkcreatesampler().psampler());
  return static_cast<VkResult>(response.vkcreatesampler().result());
}
void PackAndCallVkDestroySampler(VvkCommandClientBidiStream& stream, VkDevice device, VkSampler sampler, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkDestroySampler");
  request.mutable_vkdestroysampler()->set_device(reinterpret_cast<uint64_t>(device));
  if (sampler) {
    request.mutable_vkdestroysampler()->set_sampler(reinterpret_cast<uint64_t>(sampler));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }
}
VkResult PackAndCallVkCreateDescriptorSetLayout(VvkCommandClientBidiStream& stream, VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* pSetLayout) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateDescriptorSetLayout");
  request.mutable_vkcreatedescriptorsetlayout()->set_device(reinterpret_cast<uint64_t>(device));
  FillProtoFromStruct(request.mutable_vkcreatedescriptorsetlayout()->mutable_pcreateinfo(), pCreateInfo);
  request.mutable_vkcreatedescriptorsetlayout()->set_psetlayout(reinterpret_cast<uint64_t>(*pSetLayout));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pSetLayout = reinterpret_cast<VkDescriptorSetLayout>(response.vkcreatedescriptorsetlayout().psetlayout());
  return static_cast<VkResult>(response.vkcreatedescriptorsetlayout().result());
}
void PackAndCallVkDestroyDescriptorSetLayout(VvkCommandClientBidiStream& stream, VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkDestroyDescriptorSetLayout");
  request.mutable_vkdestroydescriptorsetlayout()->set_device(reinterpret_cast<uint64_t>(device));
  if (descriptorSetLayout) {
    request.mutable_vkdestroydescriptorsetlayout()->set_descriptorsetlayout(reinterpret_cast<uint64_t>(descriptorSetLayout));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }
}
VkResult PackAndCallVkCreatePipelineCache(VvkCommandClientBidiStream& stream, VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreatePipelineCache");
  request.mutable_vkcreatepipelinecache()->set_device(reinterpret_cast<uint64_t>(device));
  FillProtoFromStruct(request.mutable_vkcreatepipelinecache()->mutable_pcreateinfo(), pCreateInfo);
  request.mutable_vkcreatepipelinecache()->set_ppipelinecache(reinterpret_cast<uint64_t>(*pPipelineCache));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pPipelineCache = reinterpret_cast<VkPipelineCache>(response.vkcreatepipelinecache().ppipelinecache());
  return static_cast<VkResult>(response.vkcreatepipelinecache().result());
}
void PackAndCallVkDestroyPipelineCache(VvkCommandClientBidiStream& stream, VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkDestroyPipelineCache");
  request.mutable_vkdestroypipelinecache()->set_device(reinterpret_cast<uint64_t>(device));
  if (pipelineCache) {
    request.mutable_vkdestroypipelinecache()->set_pipelinecache(reinterpret_cast<uint64_t>(pipelineCache));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }
}
VkResult PackAndCallVkCreateDescriptorPool(VvkCommandClientBidiStream& stream, VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateDescriptorPool");
  request.mutable_vkcreatedescriptorpool()->set_device(reinterpret_cast<uint64_t>(device));
  FillProtoFromStruct(request.mutable_vkcreatedescriptorpool()->mutable_pcreateinfo(), pCreateInfo);
  request.mutable_vkcreatedescriptorpool()->set_pdescriptorpool(reinterpret_cast<uint64_t>(*pDescriptorPool));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  *pDescriptorPool = reinterpret_cast<VkDescriptorPool>(response.vkcreatedescriptorpool().pdescriptorpool());
  return static_cast<VkResult>(response.vkcreatedescriptorpool().result());
}
void PackAndCallVkDestroyDescriptorPool(VvkCommandClientBidiStream& stream, VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator) {
  vvk::server::VvkRequest request;
  request.set_method("vkDestroyDescriptorPool");
  request.mutable_vkdestroydescriptorpool()->set_device(reinterpret_cast<uint64_t>(device));
  if (descriptorPool) {
    request.mutable_vkdestroydescriptorpool()->set_descriptorpool(reinterpret_cast<uint64_t>(descriptorPool));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }
}
VkResult PackAndCallVkAllocateDescriptorSets(VvkCommandClientBidiStream& stream, VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets) {
  vvk::server::VvkRequest request;
  request.set_method("vkAllocateDescriptorSets");
  request.mutable_vkallocatedescriptorsets()->set_device(reinterpret_cast<uint64_t>(device));
  FillProtoFromStruct(request.mutable_vkallocatedescriptorsets()->mutable_pallocateinfo(), pAllocateInfo);
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  for (uint32_t i = 0; i < pAllocateInfo->descriptorSetCount; i++) {
    pDescriptorSets[i] = reinterpret_cast<VkDescriptorSet>(response.vkallocatedescriptorsets().pdescriptorsets(i));
  }
  return static_cast<VkResult>(response.vkallocatedescriptorsets().result());
}
VkResult PackAndCallVkFreeDescriptorSets(VvkCommandClientBidiStream& stream, VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets) {
  vvk::server::VvkRequest request;
  request.set_method("vkFreeDescriptorSets");
  request.mutable_vkfreedescriptorsets()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkfreedescriptorsets()->set_descriptorpool(reinterpret_cast<uint64_t>(descriptorPool));
  request.mutable_vkfreedescriptorsets()->set_descriptorsetcount(descriptorSetCount);
  for (uint32_t i = 0; i < descriptorSetCount; i++) {
    request.mutable_vkfreedescriptorsets()->add_pdescriptorsets(reinterpret_cast<uint64_t>(pDescriptorSets[i]));
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.vkfreedescriptorsets().result());
}
void PackAndCallVkUpdateDescriptorSets(VvkCommandClientBidiStream& stream, VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies) {
  vvk::server::VvkRequest request;
  request.set_method("vkUpdateDescriptorSets");
  request.mutable_vkupdatedescriptorsets()->set_device(reinterpret_cast<uint64_t>(device));
  if (descriptorWriteCount) {
    request.mutable_vkupdatedescriptorsets()->set_descriptorwritecount(descriptorWriteCount);
  }
  for (uint32_t pDescriptorWrites_indx = 0; pDescriptorWrites_indx < descriptorWriteCount; pDescriptorWrites_indx++) {
    FillProtoFromStruct(request.mutable_vkupdatedescriptorsets()->add_pdescriptorwrites(), &pDescriptorWrites[pDescriptorWrites_indx]);
  }
  if (descriptorCopyCount) {
    request.mutable_vkupdatedescriptorsets()->set_descriptorcopycount(descriptorCopyCount);
  }
  for (uint32_t pDescriptorCopies_indx = 0; pDescriptorCopies_indx < descriptorCopyCount; pDescriptorCopies_indx++) {
    FillProtoFromStruct(request.mutable_vkupdatedescriptorsets()->add_pdescriptorcopies(), &pDescriptorCopies[pDescriptorCopies_indx]);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }
}
VkResult PackAndCallVkResetCommandBuffer(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags) {
  vvk::server::VvkRequest request;
  request.set_method("vkResetCommandBuffer");
  request.mutable_vkresetcommandbuffer()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  if (flags) {
    request.mutable_vkresetcommandbuffer()->set_flags(flags);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.vkresetcommandbuffer().result());
}
void PackAndCallVkCmdBindDescriptorSets(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets) {
  vvk::server::VvkRequest request;
  request.set_method("vkCmdBindDescriptorSets");
  request.mutable_vkcmdbinddescriptorsets()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  request.mutable_vkcmdbinddescriptorsets()->set_pipelinebindpoint(static_cast<vvk::server::VkPipelineBindPoint>(pipelineBindPoint));
  request.mutable_vkcmdbinddescriptorsets()->set_layout(reinterpret_cast<uint64_t>(layout));
  request.mutable_vkcmdbinddescriptorsets()->set_firstset(firstSet);
  request.mutable_vkcmdbinddescriptorsets()->set_descriptorsetcount(descriptorSetCount);
  for (uint32_t i = 0; i < descriptorSetCount; i++) {
    request.mutable_vkcmdbinddescriptorsets()->add_pdescriptorsets(reinterpret_cast<uint64_t>(pDescriptorSets[i]));
  }
  if (dynamicOffsetCount) {
    request.mutable_vkcmdbinddescriptorsets()->set_dynamicoffsetcount(dynamicOffsetCount);
  }
  for (uint32_t i = 0; i < dynamicOffsetCount; i++) {
    request.mutable_vkcmdbinddescriptorsets()->add_pdynamicoffsets(pDynamicOffsets[i]);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }
}
VkResult PackAndCallVkFlushMappedMemoryRanges(VvkCommandClientBidiStream& stream, VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) {
  vvk::server::VvkRequest request;
  request.set_method("vkFlushMappedMemoryRanges");
  request.mutable_vkflushmappedmemoryranges()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkflushmappedmemoryranges()->set_memoryrangecount(memoryRangeCount);
  for (uint32_t pMemoryRanges_indx = 0; pMemoryRanges_indx < memoryRangeCount; pMemoryRanges_indx++) {
    FillProtoFromStruct(request.mutable_vkflushmappedmemoryranges()->add_pmemoryranges(), &pMemoryRanges[pMemoryRanges_indx]);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.vkflushmappedmemoryranges().result());
}
VkResult PackAndCallVkInvalidateMappedMemoryRanges(VvkCommandClientBidiStream& stream, VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) {
  vvk::server::VvkRequest request;
  request.set_method("vkInvalidateMappedMemoryRanges");
  request.mutable_vkinvalidatemappedmemoryranges()->set_device(reinterpret_cast<uint64_t>(device));
  request.mutable_vkinvalidatemappedmemoryranges()->set_memoryrangecount(memoryRangeCount);
  for (uint32_t pMemoryRanges_indx = 0; pMemoryRanges_indx < memoryRangeCount; pMemoryRanges_indx++) {
    FillProtoFromStruct(request.mutable_vkinvalidatemappedmemoryranges()->add_pmemoryranges(), &pMemoryRanges[pMemoryRanges_indx]);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  return static_cast<VkResult>(response.vkinvalidatemappedmemoryranges().result());
}
void PackAndCallVkCmdCopyBuffer(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions) {
  vvk::server::VvkRequest request;
  request.set_method("vkCmdCopyBuffer");
  request.mutable_vkcmdcopybuffer()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  request.mutable_vkcmdcopybuffer()->set_srcbuffer(reinterpret_cast<uint64_t>(srcBuffer));
  request.mutable_vkcmdcopybuffer()->set_dstbuffer(reinterpret_cast<uint64_t>(dstBuffer));
  request.mutable_vkcmdcopybuffer()->set_regioncount(regionCount);
  for (uint32_t pRegions_indx = 0; pRegions_indx < regionCount; pRegions_indx++) {
    FillProtoFromStruct(request.mutable_vkcmdcopybuffer()->add_pregions(), &pRegions[pRegions_indx]);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }
}
void PackAndCallVkGetBufferMemoryRequirements2KHR(VvkCommandClientBidiStream& stream, VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetBufferMemoryRequirements2KHR");
  request.mutable_vkgetbuffermemoryrequirements2khr()->set_device(reinterpret_cast<uint64_t>(device));
  FillProtoFromStruct(request.mutable_vkgetbuffermemoryrequirements2khr()->mutable_pinfo(), pInfo);
  FillProtoFromStruct(request.mutable_vkgetbuffermemoryrequirements2khr()->mutable_pmemoryrequirements(), pMemoryRequirements);
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  VkMemoryRequirements2& pMemoryRequirements_ref = *pMemoryRequirements;
  pMemoryRequirements_ref.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
  VkBaseOutStructure* base = reinterpret_cast<VkBaseOutStructure*>(&pMemoryRequirements_ref);
  for (const auto& pnext : response.vkgetbuffermemoryrequirements2khr().pmemoryrequirements().pnext()) {
    if (pnext.has_vkmemorydedicatedrequirements_chain_elem()) {
      FillStructFromProtoNoPNext(*reinterpret_cast<VkMemoryDedicatedRequirements*>(base->pNext), pnext.vkmemorydedicatedrequirements_chain_elem());
    }
    base = base->pNext;
  }
  base->pNext = nullptr;
  VkMemoryRequirements &pMemoryRequirements_ref_memoryRequirements = pMemoryRequirements_ref.memoryRequirements;
  FillStructFromProto(pMemoryRequirements_ref_memoryRequirements, response.vkgetbuffermemoryrequirements2khr().pmemoryrequirements().memoryrequirements());
}
void PackAndCallVkGetImageMemoryRequirements2KHR(VvkCommandClientBidiStream& stream, VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetImageMemoryRequirements2KHR");
  request.mutable_vkgetimagememoryrequirements2khr()->set_device(reinterpret_cast<uint64_t>(device));
  FillProtoFromStruct(request.mutable_vkgetimagememoryrequirements2khr()->mutable_pinfo(), pInfo);
  FillProtoFromStruct(request.mutable_vkgetimagememoryrequirements2khr()->mutable_pmemoryrequirements(), pMemoryRequirements);
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  VkMemoryRequirements2& pMemoryRequirements_ref = *pMemoryRequirements;
  pMemoryRequirements_ref.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
  VkBaseOutStructure* base = reinterpret_cast<VkBaseOutStructure*>(&pMemoryRequirements_ref);
  for (const auto& pnext : response.vkgetimagememoryrequirements2khr().pmemoryrequirements().pnext()) {
    if (pnext.has_vkmemorydedicatedrequirements_chain_elem()) {
      FillStructFromProtoNoPNext(*reinterpret_cast<VkMemoryDedicatedRequirements*>(base->pNext), pnext.vkmemorydedicatedrequirements_chain_elem());
    }
    base = base->pNext;
  }
  base->pNext = nullptr;
  VkMemoryRequirements &pMemoryRequirements_ref_memoryRequirements = pMemoryRequirements_ref.memoryRequirements;
  FillStructFromProto(pMemoryRequirements_ref_memoryRequirements, response.vkgetimagememoryrequirements2khr().pmemoryrequirements().memoryrequirements());
}
void PackAndCallVkGetBufferMemoryRequirements2(VvkCommandClientBidiStream& stream, VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetBufferMemoryRequirements2");
  request.mutable_vkgetbuffermemoryrequirements2()->set_device(reinterpret_cast<uint64_t>(device));
  FillProtoFromStruct(request.mutable_vkgetbuffermemoryrequirements2()->mutable_pinfo(), pInfo);
  FillProtoFromStruct(request.mutable_vkgetbuffermemoryrequirements2()->mutable_pmemoryrequirements(), pMemoryRequirements);
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  VkMemoryRequirements2& pMemoryRequirements_ref = *pMemoryRequirements;
  pMemoryRequirements_ref.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
  VkBaseOutStructure* base = reinterpret_cast<VkBaseOutStructure*>(&pMemoryRequirements_ref);
  for (const auto& pnext : response.vkgetbuffermemoryrequirements2().pmemoryrequirements().pnext()) {
    if (pnext.has_vkmemorydedicatedrequirements_chain_elem()) {
      FillStructFromProtoNoPNext(*reinterpret_cast<VkMemoryDedicatedRequirements*>(base->pNext), pnext.vkmemorydedicatedrequirements_chain_elem());
    }
    base = base->pNext;
  }
  base->pNext = nullptr;
  VkMemoryRequirements &pMemoryRequirements_ref_memoryRequirements = pMemoryRequirements_ref.memoryRequirements;
  FillStructFromProto(pMemoryRequirements_ref_memoryRequirements, response.vkgetbuffermemoryrequirements2().pmemoryrequirements().memoryrequirements());
}
void PackAndCallVkCmdCopyBufferToImage(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions) {
  vvk::server::VvkRequest request;
  request.set_method("vkCmdCopyBufferToImage");
  request.mutable_vkcmdcopybuffertoimage()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  request.mutable_vkcmdcopybuffertoimage()->set_srcbuffer(reinterpret_cast<uint64_t>(srcBuffer));
  request.mutable_vkcmdcopybuffertoimage()->set_dstimage(reinterpret_cast<uint64_t>(dstImage));
  request.mutable_vkcmdcopybuffertoimage()->set_dstimagelayout(static_cast<vvk::server::VkImageLayout>(dstImageLayout));
  request.mutable_vkcmdcopybuffertoimage()->set_regioncount(regionCount);
  for (uint32_t pRegions_indx = 0; pRegions_indx < regionCount; pRegions_indx++) {
    FillProtoFromStruct(request.mutable_vkcmdcopybuffertoimage()->add_pregions(), &pRegions[pRegions_indx]);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }
}
VkResult PackAndCallVkCreateComputePipelines(VvkCommandClientBidiStream& stream, VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) {
  vvk::server::VvkRequest request;
  request.set_method("vkCreateComputePipelines");
  request.mutable_vkcreatecomputepipelines()->set_device(reinterpret_cast<uint64_t>(device));
  if (pipelineCache) {
    request.mutable_vkcreatecomputepipelines()->set_pipelinecache(reinterpret_cast<uint64_t>(pipelineCache));
  }
  request.mutable_vkcreatecomputepipelines()->set_createinfocount(createInfoCount);
  for (uint32_t pCreateInfos_indx = 0; pCreateInfos_indx < createInfoCount; pCreateInfos_indx++) {
    FillProtoFromStruct(request.mutable_vkcreatecomputepipelines()->add_pcreateinfos(), &pCreateInfos[pCreateInfos_indx]);
  }
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
  for (uint32_t i = 0; i < createInfoCount; i++) {
    pPipelines[i] = reinterpret_cast<VkPipeline>(response.vkcreatecomputepipelines().ppipelines(i));
  }
  return static_cast<VkResult>(response.vkcreatecomputepipelines().result());
}
void PackAndCallVkCmdDispatch(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) {
  vvk::server::VvkRequest request;
  request.set_method("vkCmdDispatch");
  request.mutable_vkcmddispatch()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  request.mutable_vkcmddispatch()->set_groupcountx(groupCountX);
  request.mutable_vkcmddispatch()->set_groupcounty(groupCountY);
  request.mutable_vkcmddispatch()->set_groupcountz(groupCountZ);
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }
}
void PackAndCallVkCmdPushConstants(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues) {
  vvk::server::VvkRequest request;
  request.set_method("vkCmdPushConstants");
  request.mutable_vkcmdpushconstants()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  request.mutable_vkcmdpushconstants()->set_layout(reinterpret_cast<uint64_t>(layout));
  request.mutable_vkcmdpushconstants()->set_stageflags(stageFlags);
  request.mutable_vkcmdpushconstants()->set_offset(offset);
  request.mutable_vkcmdpushconstants()->set_size(size);
  request.mutable_vkcmdpushconstants()->set_pvalues(pValues, size);
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }
}
void PackAndCallVkCmdBindIndexBuffer(VvkCommandClientBidiStream& stream, VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) {
  vvk::server::VvkRequest request;
  request.set_method("vkCmdBindIndexBuffer");
  request.mutable_vkcmdbindindexbuffer()->set_commandbuffer(reinterpret_cast<uint64_t>(commandBuffer));
  if (buffer) {
    request.mutable_vkcmdbindindexbuffer()->set_buffer(reinterpret_cast<uint64_t>(buffer));
  }
  request.mutable_vkcmdbindindexbuffer()->set_offset(static_cast<uint64_t>(offset));
  request.mutable_vkcmdbindindexbuffer()->set_indextype(static_cast<vvk::server::VkIndexType>(indexType));
  vvk::server::VvkResponse response;

  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }
}
}  // namespace vvk

