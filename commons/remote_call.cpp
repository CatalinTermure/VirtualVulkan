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
void FillPNextChainToProto(vvk::server::VkMemoryRequirements2* proto, const VkMemoryRequirements2* original_struct);
void FillPNextChainToProto(vvk::server::VkPhysicalDeviceFeatures2* proto, const VkPhysicalDeviceFeatures2* original_struct);
void FillPNextChainToProto(vvk::server::VkPhysicalDeviceProperties2* proto, const VkPhysicalDeviceProperties2* original_struct);
void FillProtoFromStruct(vvk::server::VkApplicationInfo* proto, const VkApplicationInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkAttachmentDescription* proto, const VkAttachmentDescription* original_struct);
void FillProtoFromStruct(vvk::server::VkAttachmentReference* proto, const VkAttachmentReference* original_struct);
void FillProtoFromStruct(vvk::server::VkBindImageMemoryInfo* proto, const VkBindImageMemoryInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkBufferImageCopy* proto, const VkBufferImageCopy* original_struct);
void FillProtoFromStruct(vvk::server::VkBufferMemoryBarrier* proto, const VkBufferMemoryBarrier* original_struct);
void FillProtoFromStruct(vvk::server::VkClearColorValue* proto, const VkClearColorValue* original_struct);
void FillProtoFromStruct(vvk::server::VkClearDepthStencilValue* proto, const VkClearDepthStencilValue* original_struct);
void FillProtoFromStruct(vvk::server::VkClearValue* proto, const VkClearValue* original_struct);
void FillProtoFromStruct(vvk::server::VkCommandBufferAllocateInfo* proto, const VkCommandBufferAllocateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkCommandBufferBeginInfo* proto, const VkCommandBufferBeginInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkCommandBufferInheritanceInfo* proto, const VkCommandBufferInheritanceInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkCommandPoolCreateInfo* proto, const VkCommandPoolCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkComponentMapping* proto, const VkComponentMapping* original_struct);
void FillProtoFromStruct(vvk::server::VkConformanceVersion* proto, const VkConformanceVersion* original_struct);
void FillProtoFromStruct(vvk::server::VkDeviceCreateInfo* proto, const VkDeviceCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkDeviceQueueCreateInfo* proto, const VkDeviceQueueCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkExtent2D* proto, const VkExtent2D* original_struct);
void FillProtoFromStruct(vvk::server::VkExtent3D* proto, const VkExtent3D* original_struct);
void FillProtoFromStruct(vvk::server::VkFenceCreateInfo* proto, const VkFenceCreateInfo* original_struct);
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
void FillProtoFromStruct(vvk::server::VkMemoryAllocateInfo* proto, const VkMemoryAllocateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkMemoryBarrier* proto, const VkMemoryBarrier* original_struct);
void FillProtoFromStruct(vvk::server::VkOffset2D* proto, const VkOffset2D* original_struct);
void FillProtoFromStruct(vvk::server::VkOffset3D* proto, const VkOffset3D* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceFeatures* proto, const VkPhysicalDeviceFeatures* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceProtectedMemoryFeatures* proto, const VkPhysicalDeviceProtectedMemoryFeatures* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceProtectedMemoryProperties* proto, const VkPhysicalDeviceProtectedMemoryProperties* original_struct);
void FillProtoFromStruct(vvk::server::VkPhysicalDeviceShaderDrawParametersFeatures* proto, const VkPhysicalDeviceShaderDrawParametersFeatures* original_struct);
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
void FillProtoFromStruct(vvk::server::VkSemaphoreCreateInfo* proto, const VkSemaphoreCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkSemaphoreTypeCreateInfo* proto, const VkSemaphoreTypeCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkShaderModuleCreateInfo* proto, const VkShaderModuleCreateInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkSpecializationInfo* proto, const VkSpecializationInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkSpecializationMapEntry* proto, const VkSpecializationMapEntry* original_struct);
void FillProtoFromStruct(vvk::server::VkStencilOpState* proto, const VkStencilOpState* original_struct);
void FillProtoFromStruct(vvk::server::VkSubmitInfo* proto, const VkSubmitInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkSubpassDependency* proto, const VkSubpassDependency* original_struct);
void FillProtoFromStruct(vvk::server::VkSubpassDescription* proto, const VkSubpassDescription* original_struct);
void FillProtoFromStruct(vvk::server::VkTimelineSemaphoreSubmitInfo* proto, const VkTimelineSemaphoreSubmitInfo* original_struct);
void FillProtoFromStruct(vvk::server::VkVertexInputAttributeDescription* proto, const VkVertexInputAttributeDescription* original_struct);
void FillProtoFromStruct(vvk::server::VkVertexInputBindingDescription* proto, const VkVertexInputBindingDescription* original_struct);
void FillProtoFromStruct(vvk::server::VkViewport* proto, const VkViewport* original_struct);
void FillStructFromProto(VkExtent3D& original_struct, const vvk::server::VkExtent3D& proto);
void FillStructFromProto(VkMemoryHeap& original_struct, const vvk::server::VkMemoryHeap& proto);
void FillStructFromProto(VkMemoryRequirements& original_struct, const vvk::server::VkMemoryRequirements& proto);
void FillStructFromProto(VkMemoryType& original_struct, const vvk::server::VkMemoryType& proto);
void FillStructFromProto(VkPhysicalDeviceFeatures& original_struct, const vvk::server::VkPhysicalDeviceFeatures& proto);
void FillStructFromProto(VkPhysicalDeviceLimits& original_struct, const vvk::server::VkPhysicalDeviceLimits& proto);
void FillStructFromProto(VkPhysicalDeviceProperties& original_struct, const vvk::server::VkPhysicalDeviceProperties& proto);
void FillStructFromProto(VkPhysicalDeviceSparseProperties& original_struct, const vvk::server::VkPhysicalDeviceSparseProperties& proto);
void FillPNextChainToProto(vvk::server::VkMemoryRequirements2* proto, const VkMemoryRequirements2* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
  }
}
void FillPNextChainToProto(vvk::server::VkPhysicalDeviceFeatures2* proto, const VkPhysicalDeviceFeatures2* original_struct) {
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
}
void FillPNextChainToProto(vvk::server::VkPhysicalDeviceProperties2* proto, const VkPhysicalDeviceProperties2* original_struct) {
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
}
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
void FillProtoFromStruct(vvk::server::VkClearColorValue* proto, const VkClearColorValue* original_struct) {
  const size_t proto_float32_length = 4;
  for (int float32_indx = 0; float32_indx < proto_float32_length; float32_indx++) {
    proto->add_float32(original_struct->float32[float32_indx]);
  }
  const size_t proto_int32_length = 4;
  for (int int32_indx = 0; int32_indx < proto_int32_length; int32_indx++) {
    proto->add_int32(original_struct->int32[int32_indx]);
  }
  const size_t proto_uint32_length = 4;
  for (int uint32_indx = 0; uint32_indx < proto_uint32_length; uint32_indx++) {
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
void FillProtoFromStruct(vvk::server::VkConformanceVersion* proto, const VkConformanceVersion* original_struct) {
  proto->set_major(static_cast<uint32_t>(original_struct->major));
  proto->set_minor(static_cast<uint32_t>(original_struct->minor));
  proto->set_subminor(static_cast<uint32_t>(original_struct->subminor));
  proto->set_patch(static_cast<uint32_t>(original_struct->patch));
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
  for (int pQueueCreateInfos_indx = 0; pQueueCreateInfos_indx < proto_pQueueCreateInfos_length; pQueueCreateInfos_indx++) {
    FillProtoFromStruct(proto->add_pqueuecreateinfos(), (&original_struct->pQueueCreateInfos[pQueueCreateInfos_indx]));
  }
  if (original_struct->enabledLayerCount) {
    proto->set_enabledlayercount(original_struct->enabledLayerCount);
  }
  const size_t proto_ppEnabledLayerNames_length = original_struct->enabledLayerCount;
  for (int ppEnabledLayerNames_indx = 0; ppEnabledLayerNames_indx < proto_ppEnabledLayerNames_length; ppEnabledLayerNames_indx++) {
    proto->add_ppenabledlayernames(original_struct->ppEnabledLayerNames[ppEnabledLayerNames_indx]);
  }
  if (original_struct->enabledExtensionCount) {
    proto->set_enabledextensioncount(original_struct->enabledExtensionCount);
  }
  const size_t proto_ppEnabledExtensionNames_length = original_struct->enabledExtensionCount;
  for (int ppEnabledExtensionNames_indx = 0; ppEnabledExtensionNames_indx < proto_ppEnabledExtensionNames_length; ppEnabledExtensionNames_indx++) {
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
  for (int pQueuePriorities_indx = 0; pQueuePriorities_indx < proto_pQueuePriorities_length; pQueuePriorities_indx++) {
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
  for (int pAttachments_indx = 0; pAttachments_indx < proto_pAttachments_length; pAttachments_indx++) {
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
    for (int pStages_indx = 0; pStages_indx < proto_pStages_length; pStages_indx++) {
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
  for (int pQueueFamilyIndices_indx = 0; pQueueFamilyIndices_indx < proto_pQueueFamilyIndices_length; pQueueFamilyIndices_indx++) {
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
  for (int ppEnabledLayerNames_indx = 0; ppEnabledLayerNames_indx < proto_ppEnabledLayerNames_length; ppEnabledLayerNames_indx++) {
    proto->add_ppenabledlayernames(original_struct->ppEnabledLayerNames[ppEnabledLayerNames_indx]);
  }
  if (original_struct->enabledExtensionCount) {
    proto->set_enabledextensioncount(original_struct->enabledExtensionCount);
  }
  const size_t proto_ppEnabledExtensionNames_length = original_struct->enabledExtensionCount;
  for (int ppEnabledExtensionNames_indx = 0; ppEnabledExtensionNames_indx < proto_ppEnabledExtensionNames_length; ppEnabledExtensionNames_indx++) {
    proto->add_ppenabledextensionnames(original_struct->ppEnabledExtensionNames[ppEnabledExtensionNames_indx]);
  }
}
void FillProtoFromStruct(vvk::server::VkMemoryAllocateInfo* proto, const VkMemoryAllocateInfo* original_struct) {
  if (original_struct->pNext) {
    // Empty pNext chain
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
  const size_t proto_deviceUUID_length = VK_UUID_SIZE;
  for (int deviceUUID_indx = 0; deviceUUID_indx < proto_deviceUUID_length; deviceUUID_indx++) {
    proto->add_deviceuuid(static_cast<uint32_t>(original_struct->deviceUUID[deviceUUID_indx]));
  }
  const size_t proto_driverUUID_length = VK_UUID_SIZE;
  for (int driverUUID_indx = 0; driverUUID_indx < proto_driverUUID_length; driverUUID_indx++) {
    proto->add_driveruuid(static_cast<uint32_t>(original_struct->driverUUID[driverUUID_indx]));
  }
  const size_t proto_deviceLUID_length = VK_LUID_SIZE;
  for (int deviceLUID_indx = 0; deviceLUID_indx < proto_deviceLUID_length; deviceLUID_indx++) {
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
    for (int pCopySrcLayouts_indx = 0; pCopySrcLayouts_indx < proto_pCopySrcLayouts_length; pCopySrcLayouts_indx++) {
      proto->add_pcopysrclayouts(static_cast<vvk::server::VkImageLayout>(original_struct->pCopySrcLayouts[pCopySrcLayouts_indx]));
    }
  }
  if (original_struct->copyDstLayoutCount) {
    proto->set_copydstlayoutcount(original_struct->copyDstLayoutCount);
  }
  if (original_struct->pCopyDstLayouts) {
    const size_t proto_pCopyDstLayouts_length = original_struct->copyDstLayoutCount;
    for (int pCopyDstLayouts_indx = 0; pCopyDstLayouts_indx < proto_pCopyDstLayouts_length; pCopyDstLayouts_indx++) {
      proto->add_pcopydstlayouts(static_cast<vvk::server::VkImageLayout>(original_struct->pCopyDstLayouts[pCopyDstLayouts_indx]));
    }
  }
  if (original_struct->optimalTilingLayoutUUID) {
    const size_t proto_optimalTilingLayoutUUID_length = VK_UUID_SIZE;
    for (int optimalTilingLayoutUUID_indx = 0; optimalTilingLayoutUUID_indx < proto_optimalTilingLayoutUUID_length; optimalTilingLayoutUUID_indx++) {
      proto->add_optimaltilinglayoutuuid(static_cast<uint32_t>(original_struct->optimalTilingLayoutUUID[optimalTilingLayoutUUID_indx]));
    }
  }
  proto->set_identicalmemorytyperequirements(original_struct->identicalMemoryTypeRequirements);
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
    for (int pAttachments_indx = 0; pAttachments_indx < proto_pAttachments_length; pAttachments_indx++) {
      FillProtoFromStruct(proto->add_pattachments(), (&original_struct->pAttachments[pAttachments_indx]));
    }
  }
  const size_t proto_blendConstants_length = 4;
  for (int blendConstants_indx = 0; blendConstants_indx < proto_blendConstants_length; blendConstants_indx++) {
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
  for (int pDynamicStates_indx = 0; pDynamicStates_indx < proto_pDynamicStates_length; pDynamicStates_indx++) {
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
  for (int pSetLayouts_indx = 0; pSetLayouts_indx < proto_pSetLayouts_length; pSetLayouts_indx++) {
    proto->add_psetlayouts(reinterpret_cast<uint64_t>(original_struct->pSetLayouts[pSetLayouts_indx]));
  }
  if (original_struct->pushConstantRangeCount) {
    proto->set_pushconstantrangecount(original_struct->pushConstantRangeCount);
  }
  const size_t proto_pPushConstantRanges_length = original_struct->pushConstantRangeCount;
  for (int pPushConstantRanges_indx = 0; pPushConstantRanges_indx < proto_pPushConstantRanges_length; pPushConstantRanges_indx++) {
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
    for (int pSampleMask_indx = 0; pSampleMask_indx < proto_pSampleMask_length; pSampleMask_indx++) {
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
  for (int pVertexBindingDescriptions_indx = 0; pVertexBindingDescriptions_indx < proto_pVertexBindingDescriptions_length; pVertexBindingDescriptions_indx++) {
    FillProtoFromStruct(proto->add_pvertexbindingdescriptions(), (&original_struct->pVertexBindingDescriptions[pVertexBindingDescriptions_indx]));
  }
  if (original_struct->vertexAttributeDescriptionCount) {
    proto->set_vertexattributedescriptioncount(original_struct->vertexAttributeDescriptionCount);
  }
  const size_t proto_pVertexAttributeDescriptions_length = original_struct->vertexAttributeDescriptionCount;
  for (int pVertexAttributeDescriptions_indx = 0; pVertexAttributeDescriptions_indx < proto_pVertexAttributeDescriptions_length; pVertexAttributeDescriptions_indx++) {
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
    for (int pViewports_indx = 0; pViewports_indx < proto_pViewports_length; pViewports_indx++) {
      FillProtoFromStruct(proto->add_pviewports(), (&original_struct->pViewports[pViewports_indx]));
    }
  }
  if (original_struct->scissorCount) {
    proto->set_scissorcount(original_struct->scissorCount);
  }
  if (original_struct->pScissors) {
    const size_t proto_pScissors_length = original_struct->scissorCount;
    for (int pScissors_indx = 0; pScissors_indx < proto_pScissors_length; pScissors_indx++) {
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
  for (int pClearValues_indx = 0; pClearValues_indx < proto_pClearValues_length; pClearValues_indx++) {
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
  for (int pAttachments_indx = 0; pAttachments_indx < proto_pAttachments_length; pAttachments_indx++) {
    FillProtoFromStruct(proto->add_pattachments(), (&original_struct->pAttachments[pAttachments_indx]));
  }
  proto->set_subpasscount(original_struct->subpassCount);
  const size_t proto_pSubpasses_length = original_struct->subpassCount;
  for (int pSubpasses_indx = 0; pSubpasses_indx < proto_pSubpasses_length; pSubpasses_indx++) {
    FillProtoFromStruct(proto->add_psubpasses(), (&original_struct->pSubpasses[pSubpasses_indx]));
  }
  if (original_struct->dependencyCount) {
    proto->set_dependencycount(original_struct->dependencyCount);
  }
  const size_t proto_pDependencies_length = original_struct->dependencyCount;
  for (int pDependencies_indx = 0; pDependencies_indx < proto_pDependencies_length; pDependencies_indx++) {
    FillProtoFromStruct(proto->add_pdependencies(), (&original_struct->pDependencies[pDependencies_indx]));
  }
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
  for (int pCode_indx = 0; pCode_indx < proto_pCode_length; pCode_indx++) {
    proto->add_pcode(original_struct->pCode[pCode_indx]);
  }
}
void FillProtoFromStruct(vvk::server::VkSpecializationInfo* proto, const VkSpecializationInfo* original_struct) {
  if (original_struct->mapEntryCount) {
    proto->set_mapentrycount(original_struct->mapEntryCount);
  }
  const size_t proto_pMapEntries_length = original_struct->mapEntryCount;
  for (int pMapEntries_indx = 0; pMapEntries_indx < proto_pMapEntries_length; pMapEntries_indx++) {
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
  for (int pWaitSemaphores_indx = 0; pWaitSemaphores_indx < proto_pWaitSemaphores_length; pWaitSemaphores_indx++) {
    proto->add_pwaitsemaphores(reinterpret_cast<uint64_t>(original_struct->pWaitSemaphores[pWaitSemaphores_indx]));
  }
  const size_t proto_pWaitDstStageMask_length = original_struct->waitSemaphoreCount;
  for (int pWaitDstStageMask_indx = 0; pWaitDstStageMask_indx < proto_pWaitDstStageMask_length; pWaitDstStageMask_indx++) {
    proto->add_pwaitdststagemask(static_cast<VkPipelineStageFlags>(original_struct->pWaitDstStageMask[pWaitDstStageMask_indx]));
  }
  if (original_struct->commandBufferCount) {
    proto->set_commandbuffercount(original_struct->commandBufferCount);
  }
  const size_t proto_pCommandBuffers_length = original_struct->commandBufferCount;
  for (int pCommandBuffers_indx = 0; pCommandBuffers_indx < proto_pCommandBuffers_length; pCommandBuffers_indx++) {
    proto->add_pcommandbuffers(reinterpret_cast<uint64_t>(original_struct->pCommandBuffers[pCommandBuffers_indx]));
  }
  if (original_struct->signalSemaphoreCount) {
    proto->set_signalsemaphorecount(original_struct->signalSemaphoreCount);
  }
  const size_t proto_pSignalSemaphores_length = original_struct->signalSemaphoreCount;
  for (int pSignalSemaphores_indx = 0; pSignalSemaphores_indx < proto_pSignalSemaphores_length; pSignalSemaphores_indx++) {
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
  for (int pInputAttachments_indx = 0; pInputAttachments_indx < proto_pInputAttachments_length; pInputAttachments_indx++) {
    FillProtoFromStruct(proto->add_pinputattachments(), (&original_struct->pInputAttachments[pInputAttachments_indx]));
  }
  if (original_struct->colorAttachmentCount) {
    proto->set_colorattachmentcount(original_struct->colorAttachmentCount);
  }
  const size_t proto_pColorAttachments_length = original_struct->colorAttachmentCount;
  for (int pColorAttachments_indx = 0; pColorAttachments_indx < proto_pColorAttachments_length; pColorAttachments_indx++) {
    FillProtoFromStruct(proto->add_pcolorattachments(), (&original_struct->pColorAttachments[pColorAttachments_indx]));
  }
  if (original_struct->pResolveAttachments) {
    const size_t proto_pResolveAttachments_length = original_struct->colorAttachmentCount;
    for (int pResolveAttachments_indx = 0; pResolveAttachments_indx < proto_pResolveAttachments_length; pResolveAttachments_indx++) {
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
  for (int pPreserveAttachments_indx = 0; pPreserveAttachments_indx < proto_pPreserveAttachments_length; pPreserveAttachments_indx++) {
    proto->add_ppreserveattachments(original_struct->pPreserveAttachments[pPreserveAttachments_indx]);
  }
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
    for (int pWaitSemaphoreValues_indx = 0; pWaitSemaphoreValues_indx < proto_pWaitSemaphoreValues_length; pWaitSemaphoreValues_indx++) {
      proto->add_pwaitsemaphorevalues(original_struct->pWaitSemaphoreValues[pWaitSemaphoreValues_indx]);
    }
  }
  if (original_struct->signalSemaphoreValueCount) {
    proto->set_signalsemaphorevaluecount(original_struct->signalSemaphoreValueCount);
  }
  if (original_struct->pSignalSemaphoreValues) {
    const size_t proto_pSignalSemaphoreValues_length = original_struct->signalSemaphoreValueCount;
    for (int pSignalSemaphoreValues_indx = 0; pSignalSemaphoreValues_indx < proto_pSignalSemaphoreValues_length; pSignalSemaphoreValues_indx++) {
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
  for (int maxComputeWorkGroupCount_indx = 0; maxComputeWorkGroupCount_indx < 3; maxComputeWorkGroupCount_indx++) {
    original_struct.maxComputeWorkGroupCount[maxComputeWorkGroupCount_indx] = proto.maxcomputeworkgroupcount(maxComputeWorkGroupCount_indx);
  }
  original_struct.maxComputeWorkGroupInvocations = proto.maxcomputeworkgroupinvocations();
  for (int maxComputeWorkGroupSize_indx = 0; maxComputeWorkGroupSize_indx < 3; maxComputeWorkGroupSize_indx++) {
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
  for (int maxViewportDimensions_indx = 0; maxViewportDimensions_indx < 2; maxViewportDimensions_indx++) {
    original_struct.maxViewportDimensions[maxViewportDimensions_indx] = proto.maxviewportdimensions(maxViewportDimensions_indx);
  }
  for (int viewportBoundsRange_indx = 0; viewportBoundsRange_indx < 2; viewportBoundsRange_indx++) {
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
  for (int pointSizeRange_indx = 0; pointSizeRange_indx < 2; pointSizeRange_indx++) {
    original_struct.pointSizeRange[pointSizeRange_indx] = proto.pointsizerange(pointSizeRange_indx);
  }
  for (int lineWidthRange_indx = 0; lineWidthRange_indx < 2; lineWidthRange_indx++) {
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
  for (int pipelineCacheUUID_indx = 0; pipelineCacheUUID_indx < VK_UUID_SIZE; pipelineCacheUUID_indx++) {
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
  FillStructFromProto(pProperties_ref_limits, response.vkgetphysicaldeviceproperties().pproperties().limits());
  VkPhysicalDeviceSparseProperties &pProperties_ref_sparseProperties = pProperties_ref.sparseProperties;
  FillStructFromProto(pProperties_ref_sparseProperties, response.vkgetphysicaldeviceproperties().pproperties().sparseproperties());
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
    FillProtoFromStruct(request.mutable_vkbindimagememory2()->add_pbindinfos(), &pBindInfos[pBindInfos_indx]);
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
  FillProtoFromStruct(request.mutable_vkgetimagememoryrequirements2()->mutable_pinfo(), pInfo);
  FillPNextChainToProto(request.mutable_vkgetimagememoryrequirements2()->mutable_pmemoryrequirements(), pMemoryRequirements);
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
  FillProtoFromStruct(request.mutable_vkallocatecommandbuffers()->mutable_pallocateinfo(), pAllocateInfo);
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
  FillProtoFromStruct(request.mutable_vkbegincommandbuffer()->mutable_pbegininfo(), pBeginInfo);
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
  FillProtoFromStruct(request.mutable_vkgetimagesubresourcelayout()->mutable_psubresource(), pSubresource);
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
    FillProtoFromStruct(request.mutable_vkcreategraphicspipelines()->add_pcreateinfos(), &pCreateInfos[pCreateInfos_indx]);
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
  FillProtoFromStruct(request.mutable_vkcmdbeginrenderpass()->mutable_prenderpassbegin(), pRenderPassBegin);
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
    FillProtoFromStruct(request.mutable_vkcmdsetviewport()->add_pviewports(), &pViewports[pViewports_indx]);
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
    FillProtoFromStruct(request.mutable_vkcmdsetscissor()->add_pscissors(), &pScissors[pScissors_indx]);
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
    FillProtoFromStruct(request.mutable_vkcmdpipelinebarrier()->add_pmemorybarriers(), &pMemoryBarriers[pMemoryBarriers_indx]);
  }
  if (bufferMemoryBarrierCount) {
    request.mutable_vkcmdpipelinebarrier()->set_buffermemorybarriercount(bufferMemoryBarrierCount);
  }
  for (int pBufferMemoryBarriers_indx = 0; pBufferMemoryBarriers_indx < bufferMemoryBarrierCount; pBufferMemoryBarriers_indx++) {
    FillProtoFromStruct(request.mutable_vkcmdpipelinebarrier()->add_pbuffermemorybarriers(), &pBufferMemoryBarriers[pBufferMemoryBarriers_indx]);
  }
  if (imageMemoryBarrierCount) {
    request.mutable_vkcmdpipelinebarrier()->set_imagememorybarriercount(imageMemoryBarrierCount);
  }
  for (int pImageMemoryBarriers_indx = 0; pImageMemoryBarriers_indx < imageMemoryBarrierCount; pImageMemoryBarriers_indx++) {
    FillProtoFromStruct(request.mutable_vkcmdpipelinebarrier()->add_pimagememorybarriers(), &pImageMemoryBarriers[pImageMemoryBarriers_indx]);
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
    FillProtoFromStruct(request.mutable_vkcmdcopyimagetobuffer()->add_pregions(), &pRegions[pRegions_indx]);
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
  FillPNextChainToProto(request.mutable_vkgetphysicaldeviceproperties2()->mutable_pproperties(), pProperties);
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
  FillStructFromProto(pProperties_ref_properties, response.vkgetphysicaldeviceproperties2().pproperties().properties());
}
void PackAndCallVkGetPhysicalDeviceFeatures2(VvkCommandClientBidiStream& stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2* pFeatures) {
  vvk::server::VvkRequest request;
  request.set_method("vkGetPhysicalDeviceFeatures2");
  request.mutable_vkgetphysicaldevicefeatures2()->set_physicaldevice(reinterpret_cast<uint64_t>(physicalDevice));
  FillPNextChainToProto(request.mutable_vkgetphysicaldevicefeatures2()->mutable_pfeatures(), pFeatures);
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
  FillStructFromProto(pFeatures_ref_features, response.vkgetphysicaldevicefeatures2().pfeatures().features());
}
}  // namespace vvk

