#include "commons/remote_call.h"
#include "layer/context/device.h"
#include "layer/functions.h"

namespace vvk {

VKAPI_ATTR VkResult VKAPI_CALL CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo,
                                                const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) {
  Device& device_info = GetDeviceInfo(device);
  VkRenderPassCreateInfo remote_create_info = *pCreateInfo;
  std::vector<VkAttachmentDescription> attachment_descriptions(remote_create_info.attachmentCount);
  remote_create_info.pAttachments = attachment_descriptions.data();
  for (uint32_t i = 0; i < remote_create_info.attachmentCount; i++) {
    attachment_descriptions[i] = pCreateInfo->pAttachments[i];
    if (attachment_descriptions[i].finalLayout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR) {
      attachment_descriptions[i].finalLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    }
  }
  return PackAndCallVkCreateRenderPass(device_info.instance_info().command_stream(),
                                       device_info.instance_info().GetRemoteHandle(device), &remote_create_info,
                                       pAllocator, pRenderPass);
}
VKAPI_ATTR void VKAPI_CALL DestroyRenderPass(VkDevice device, VkRenderPass renderPass,
                                             const VkAllocationCallbacks* pAllocator) {
  Device& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyRenderPass(device_info.instance_info().command_stream(),
                                 device_info.instance_info().GetRemoteHandle(device), renderPass, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo,
                                                 const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer) {
  Device& device_info = GetDeviceInfo(device);
  VkResult result = PackAndCallVkCreateFramebuffer(device_info.instance_info().command_stream(),
                                                   device_info.instance_info().GetRemoteHandle(device), pCreateInfo,
                                                   pAllocator, pFramebuffer);
  if (result != VK_SUCCESS) return result;

  for (uint32_t i = 0; i < pCreateInfo->attachmentCount; i++) {
    auto it = device_info.swapchain_image_views.find(pCreateInfo->pAttachments[i]);
    if (it != device_info.swapchain_image_views.end()) {
      device_info.swapchain_framebuffers.emplace(*pFramebuffer, it->second);
      break;
    }
  }

  return result;
}
VKAPI_ATTR void VKAPI_CALL DestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer,
                                              const VkAllocationCallbacks* pAllocator) {
  Device& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyFramebuffer(device_info.instance_info().command_stream(),
                                  device_info.instance_info().GetRemoteHandle(device), framebuffer, pAllocator);
  device_info.swapchain_framebuffers.erase(framebuffer);
}

}  // namespace vvk
