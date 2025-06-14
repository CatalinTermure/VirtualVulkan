// clang-format off
#include "layer/wsi_support.h"
// clang-format on

#include "commons/remote_call.h"
#include "layer/context/device.h"
#include "layer/functions.h"

namespace vvk {

VKAPI_ATTR VkResult VKAPI_CALL EndCommandBuffer(VkCommandBuffer commandBuffer) {
  Device& device_info = GetDeviceInfo(commandBuffer);

  auto it = device_info.swapchain_render_command_buffers.find(commandBuffer);
  if (it != device_info.swapchain_render_command_buffers.end()) {
    device_info.frame_stream()->SetupFrame(device_info.GetRemoteHandle(commandBuffer), it->second);
    device_info.swapchain_render_command_buffers.erase(commandBuffer);
  }

  return PackAndCallVkEndCommandBuffer(device_info.instance_info().command_stream(),
                                       device_info.GetRemoteHandle(commandBuffer));
}

VKAPI_ATTR VkResult VKAPI_CALL ResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags) {
  Device& device_info = GetDeviceInfo(commandBuffer);
  device_info.swapchain_render_command_buffers.erase(commandBuffer);
  return PackAndCallVkResetCommandBuffer(device_info.instance_info().command_stream(),
                                         device_info.GetRemoteHandle(commandBuffer), flags);
}

VKAPI_ATTR void VKAPI_CALL CmdBeginRenderPass(VkCommandBuffer commandBuffer,
                                              const VkRenderPassBeginInfo* pRenderPassBegin,
                                              VkSubpassContents contents) {
  Device& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdBeginRenderPass(device_info.instance_info().command_stream(),
                                  device_info.GetRemoteHandle(commandBuffer), pRenderPassBegin, contents);
  auto it = device_info.swapchain_framebuffers.find(pRenderPassBegin->framebuffer);
  if (it != device_info.swapchain_framebuffers.end()) {
    device_info.swapchain_render_command_buffers.emplace(commandBuffer, it->second);
  }
}

VKAPI_ATTR void VKAPI_CALL CmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask,
                                              VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags,
                                              uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers,
                                              uint32_t bufferMemoryBarrierCount,
                                              const VkBufferMemoryBarrier* pBufferMemoryBarriers,
                                              uint32_t imageMemoryBarrierCount,
                                              const VkImageMemoryBarrier* pImageMemoryBarriers) {
  Device& device_info = GetDeviceInfo(commandBuffer);
  std::vector<VkImageMemoryBarrier> image_memory_barriers(imageMemoryBarrierCount);
  for (uint32_t i = 0; i < imageMemoryBarrierCount; i++) {
    image_memory_barriers[i] = pImageMemoryBarriers[i];
    if (image_memory_barriers[i].newLayout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR) {
      image_memory_barriers[i].newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    }
  }
  PackAndCallVkCmdPipelineBarrier(device_info.instance_info().command_stream(),
                                  device_info.GetRemoteHandle(commandBuffer), srcStageMask, dstStageMask,
                                  dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount,
                                  pBufferMemoryBarriers, image_memory_barriers.size(), image_memory_barriers.data());
}

VKAPI_ATTR VkResult VKAPI_CALL BeginCommandBuffer(VkCommandBuffer commandBuffer,
                                                  const VkCommandBufferBeginInfo* pBeginInfo) {
  Device& device_info = GetDeviceInfo(commandBuffer);
  return PackAndCallVkBeginCommandBuffer(device_info.instance_info().command_stream(),
                                         device_info.GetRemoteHandle(commandBuffer), pBeginInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdEndRenderPass(VkCommandBuffer commandBuffer) {
  Device& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdEndRenderPass(device_info.instance_info().command_stream(),
                                device_info.GetRemoteHandle(commandBuffer));
}

VKAPI_ATTR void VKAPI_CALL CmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount,
                                          const VkViewport* pViewports) {
  Device& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdSetViewport(device_info.instance_info().command_stream(), device_info.GetRemoteHandle(commandBuffer),
                              firstViewport, viewportCount, pViewports);
}
VKAPI_ATTR void VKAPI_CALL CmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount,
                                         const VkRect2D* pScissors) {
  Device& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdSetScissor(device_info.instance_info().command_stream(), device_info.GetRemoteHandle(commandBuffer),
                             firstScissor, scissorCount, pScissors);
}

VKAPI_ATTR void VKAPI_CALL CmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount,
                                   uint32_t firstVertex, uint32_t firstInstance) {
  Device& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdDraw(device_info.instance_info().command_stream(), device_info.GetRemoteHandle(commandBuffer),
                       vertexCount, instanceCount, firstVertex, firstInstance);
}

VKAPI_ATTR void VKAPI_CALL CmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY,
                                       uint32_t groupCountZ) {
  Device& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdDispatch(device_info.instance_info().command_stream(), device_info.GetRemoteHandle(commandBuffer),
                           groupCountX, groupCountY, groupCountZ);
}

VKAPI_ATTR void VKAPI_CALL CmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout,
                                            VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size,
                                            const void* pValues) {
  Device& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdPushConstants(device_info.instance_info().command_stream(),
                                device_info.GetRemoteHandle(commandBuffer), layout, stageFlags, offset, size, pValues);
}

VKAPI_ATTR void VKAPI_CALL CmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset,
                                              VkIndexType indexType) {
  Device& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdBindIndexBuffer(device_info.instance_info().command_stream(),
                                  device_info.GetRemoteHandle(commandBuffer), buffer, offset, indexType);
}

VKAPI_ATTR void VKAPI_CALL CmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding,
                                                uint32_t bindingCount, const VkBuffer* pBuffers,
                                                const VkDeviceSize* pOffsets) {
  Device& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdBindVertexBuffers(device_info.instance_info().command_stream(),
                                    device_info.GetRemoteHandle(commandBuffer), firstBinding, bindingCount, pBuffers,
                                    pOffsets);
}

VKAPI_ATTR void VKAPI_CALL CmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint,
                                           VkPipeline pipeline) {
  Device& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdBindPipeline(device_info.instance_info().command_stream(), device_info.GetRemoteHandle(commandBuffer),
                               pipelineBindPoint, pipeline);
}

VKAPI_ATTR void VKAPI_CALL CmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint,
                                                 VkPipelineLayout layout, uint32_t firstSet,
                                                 uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets,
                                                 uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets) {
  Device& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdBindDescriptorSets(device_info.instance_info().command_stream(),
                                     device_info.GetRemoteHandle(commandBuffer), pipelineBindPoint, layout, firstSet,
                                     descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
}

VKAPI_ATTR void VKAPI_CALL CmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount,
                                          uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) {
  Device& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdDrawIndexed(device_info.instance_info().command_stream(), device_info.GetRemoteHandle(commandBuffer),
                              indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout,
                                        VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount,
                                        const VkImageCopy* pRegions) {
  Device& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdCopyImage(device_info.instance_info().command_stream(), device_info.GetRemoteHandle(commandBuffer),
                            srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage,
                                                VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount,
                                                const VkBufferImageCopy* pRegions) {
  Device& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdCopyImageToBuffer(device_info.instance_info().command_stream(),
                                    device_info.GetRemoteHandle(commandBuffer), srcImage, srcImageLayout, dstBuffer,
                                    regionCount, pRegions);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage,
                                                VkImageLayout dstImageLayout, uint32_t regionCount,
                                                const VkBufferImageCopy* pRegions) {
  Device& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdCopyBufferToImage(device_info.instance_info().command_stream(),
                                    device_info.GetRemoteHandle(commandBuffer), srcBuffer, dstImage, dstImageLayout,
                                    regionCount, pRegions);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer,
                                         uint32_t regionCount, const VkBufferCopy* pRegions) {
  Device& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdCopyBuffer(device_info.instance_info().command_stream(), device_info.GetRemoteHandle(commandBuffer),
                             srcBuffer, dstBuffer, regionCount, pRegions);
}

}  // namespace vvk
