#include "commons/remote_call.h"
#include "layer/context/device.h"
#include "layer/functions.h"

namespace vvk {

VKAPI_ATTR VkResult VKAPI_CALL CreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo,
                                               const VkAllocationCallbacks* pAllocator, VkImageView* pView) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  VkResult result =
      PackAndCallVkCreateImageView(device_info.instance_info().command_stream(),
                                   device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator, pView);
  if (result != VK_SUCCESS) return result;

  auto it = device_info.swapchain_images.find(pCreateInfo->image);
  if (it != device_info.swapchain_images.end()) {
    device_info.swapchain_image_views.emplace(*pView, it->second);
  }

  return result;
}
VKAPI_ATTR void VKAPI_CALL DestroyImageView(VkDevice device, VkImageView imageView,
                                            const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyImageView(device_info.instance_info().command_stream(),
                                device_info.instance_info().GetRemoteHandle(device), imageView, pAllocator);
  device_info.swapchain_image_views.erase(imageView);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo,
                                           const VkAllocationCallbacks* pAllocator, VkImage* pImage) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateImage(device_info.instance_info().command_stream(),
                                  device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator, pImage);
}

VKAPI_ATTR void VKAPI_CALL DestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyImage(device_info.instance_info().command_stream(),
                            device_info.instance_info().GetRemoteHandle(device), image, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateSampler(VkDevice device, const VkSamplerCreateInfo* pCreateInfo,
                                             const VkAllocationCallbacks* pAllocator, VkSampler* pSampler) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateSampler(device_info.instance_info().command_stream(),
                                    device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator,
                                    pSampler);
}
VKAPI_ATTR void VKAPI_CALL DestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroySampler(device_info.instance_info().command_stream(),
                              device_info.instance_info().GetRemoteHandle(device), sampler, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL GetImageSubresourceLayout(VkDevice device, VkImage image,
                                                     const VkImageSubresource* pSubresource,
                                                     VkSubresourceLayout* pLayout) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkGetImageSubresourceLayout(device_info.instance_info().command_stream(),
                                         device_info.instance_info().GetRemoteHandle(device), image, pSubresource,
                                         pLayout);
}

}  // namespace vvk
