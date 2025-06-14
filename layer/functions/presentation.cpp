#include <spdlog/spdlog.h>

#include "commons/remote_call.h"
#include "layer/context/device.h"
#include "layer/context/swapchain.h"
#include "layer/functions.h"
#include "layer/sempahore_handle.h"

namespace vvk {

namespace {
std::optional<std::vector<VkImage>> GetLocalImagesForSwapchain(VkDevice device, VkSwapchainKHR swapchain) {
  Device& device_info = GetDeviceInfo(device);
  uint32_t swapchain_image_count = 0;
  std::vector<VkImage> client_swapchain_images;
  VkResult result =
      device_info.dispatch_table().GetSwapchainImagesKHR(device, swapchain, &swapchain_image_count, nullptr);
  if (result != VK_SUCCESS) {
    return std::nullopt;
  }

  client_swapchain_images.resize(swapchain_image_count);
  result = device_info.dispatch_table().GetSwapchainImagesKHR(device, swapchain, &swapchain_image_count,
                                                              client_swapchain_images.data());
  if (result != VK_SUCCESS) {
    return std::nullopt;
  }

  return client_swapchain_images;
}

void CleanupSwapchainInfo(Device& device_info, VkSwapchainKHR swapchain) {
  SwapchainInfo& swapchain_info = GetSwapchainInfo(swapchain);
  {
    std::lock_guard g(swapchain_info.GetLock());
    auto local_images = swapchain_info.GetLocalSwapchainImages();
    for (auto local_image : local_images) {
      device_info.RemoveRemoteHandle(local_image);
    }
  }
  RemoveSwapchainInfo(swapchain);
}
}  // namespace

VKAPI_ATTR VkResult VKAPI_CALL CreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo,
                                                  const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain) {
  spdlog::trace("CreateSwapchainKHR");

  VkSwapchainCreateInfoKHR create_info = *pCreateInfo;
  create_info.imageUsage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;

  Device& device_info = GetDeviceInfo(device);
  VkResult result = device_info.dispatch_table().CreateSwapchainKHR(device, &create_info, pAllocator, pSwapchain);
  if (result != VK_SUCCESS) {
    return result;
  }

  std::optional<std::vector<VkImage>> client_swapchain_images = GetLocalImagesForSwapchain(device, *pSwapchain);
  if (!client_swapchain_images) {
    device_info.dispatch_table().DestroySwapchainKHR(device, *pSwapchain, pAllocator);
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  if (pCreateInfo->oldSwapchain) {
    CleanupSwapchainInfo(device_info, pCreateInfo->oldSwapchain);
  }

  SwapchainInfo& swapchain_info = SetSwapchainInfo(*pSwapchain, device, device_info.remote_allocator(),
                                                   *client_swapchain_images, pCreateInfo->imageExtent);

  // Create remote images for the swapchain
  VkImageCreateInfo image_create_info = {
      .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .imageType = VK_IMAGE_TYPE_2D,
      .format = pCreateInfo->imageFormat,
      .extent = {pCreateInfo->imageExtent.width, pCreateInfo->imageExtent.height, 1},
      .mipLevels = 1,
      .arrayLayers = pCreateInfo->imageArrayLayers,
      .samples = VK_SAMPLE_COUNT_1_BIT,
      .tiling = VK_IMAGE_TILING_OPTIMAL,
      .usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | pCreateInfo->imageUsage,
      .sharingMode = pCreateInfo->imageSharingMode,
      .queueFamilyIndexCount = pCreateInfo->queueFamilyIndexCount,
      .pQueueFamilyIndices = pCreateInfo->pQueueFamilyIndices,
      .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
  };
  VmaAllocationCreateInfo alloc_create_info = {
      .flags = 0,
      .usage = VMA_MEMORY_USAGE_GPU_ONLY,
      .requiredFlags = 0,
      .preferredFlags = 0,
      .memoryTypeBits = 0,
      .pool = VK_NULL_HANDLE,
      .pUserData = nullptr,
      .priority = 0.0f,
  };
  std::uint32_t image_index = 0;
  for (VkImage client_image : *client_swapchain_images) {
    VkImage server_image;
    server_image = swapchain_info.CreateImageRemote(image_create_info, alloc_create_info);
    if (result != VK_SUCCESS) {
      device_info.dispatch_table().DestroySwapchainKHR(device, *pSwapchain, pAllocator);
      CleanupSwapchainInfo(device_info, *pSwapchain);
      return VK_ERROR_INITIALIZATION_FAILED;
    }
    device_info.swapchain_images.emplace(server_image, image_index++);
    device_info.SetRemoteHandle(client_image, server_image);
  }

  device_info.frame_stream()->AssociateSwapchain(*pSwapchain, pCreateInfo->imageExtent);

  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain,
                                               const VkAllocationCallbacks* pAllocator) {
  Device& device_info = GetDeviceInfo(device);
  try {
    CleanupSwapchainInfo(device_info, swapchain);
  } catch (std::out_of_range& e) {
    spdlog::info("Swapchain {} already had the swapchain info removed", (void*)swapchain);
  }

  device_info.frame_stream()->RemoveSwapchain(swapchain);

  device_info.dispatch_table().DestroySwapchainKHR(device, swapchain, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL GetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain,
                                                     uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages) {
  Device& device_info = GetDeviceInfo(device);

  if (pSwapchainImages == nullptr) {
    return device_info.dispatch_table().GetSwapchainImagesKHR(device, swapchain, pSwapchainImageCount, nullptr);
  }
  VkResult result =
      device_info.dispatch_table().GetSwapchainImagesKHR(device, swapchain, pSwapchainImageCount, pSwapchainImages);
  if (result != VK_SUCCESS) {
    return result;
  }

  for (uint32_t i = 0; i < *pSwapchainImageCount; i++) {
    pSwapchainImages[i] = device_info.GetRemoteHandle(pSwapchainImages[i]);
  }

  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL AcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout,
                                                   VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex) {
  Device& device_info = GetDeviceInfo(device);
  if (semaphore != VK_NULL_HANDLE) {
    if (fence != VK_NULL_HANDLE) {
      throw std::runtime_error("Cannot use both semaphore and fence in AcquireNextImageKHR");
    }
    semaphore->state = SemaphoreState::kToBeSignaledLocal;
  }
  if (fence != VK_NULL_HANDLE) {
    device_info.SetFenceLocal(fence);
  }
  spdlog::trace("Signaling acquire semaphore: {}, fence: {}", (void*)semaphore, (void*)fence);
  SwapchainInfo& swapchain_info = GetSwapchainInfo(swapchain);
  swapchain_info.SetImageAcquired();
  spdlog::trace("Acquiring next image available for swapchain {}", (void*)swapchain);
  VkResult result = device_info.dispatch_table().AcquireNextImageKHR(device, swapchain, timeout,
                                                                     semaphore->local_handle, fence, pImageIndex);
  spdlog::trace("Signaled acquire semaphore: {}, fence: {} for image: {}", (void*)semaphore, (void*)fence,
                *pImageIndex);
  if (result != VK_SUCCESS) {
    spdlog::error("AcquireNextImageKHR failed with result: {}", (int)result);
    swapchain_info.SetImageReleased();
    semaphore->state = SemaphoreState::kUnsignaled;
    device_info.ResetFenceLocal(fence);
  }

  return result;
}

VKAPI_ATTR VkResult VKAPI_CALL QueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo) {
  return GetDeviceInfo(queue).frame_stream()->PresentFrame(queue, *pPresentInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateWaylandSurfaceKHR(VkInstance instance,
                                                       const VkWaylandSurfaceCreateInfoKHR* pCreateInfo,
                                                       const VkAllocationCallbacks* pAllocator,
                                                       VkSurfaceKHR* pSurface) {
  Instance& instance_info = GetInstanceInfo(instance);
  VkResult result = instance_info.dispatch_table().CreateWaylandSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
  if (result != VK_SUCCESS) {
    return result;
  }

  instance_info.set_surface(*pSurface);

  return result;
}

VKAPI_ATTR VkResult VKAPI_CALL CreateXcbSurfaceKHR(VkInstance instance, const VkXcbSurfaceCreateInfoKHR* pCreateInfo,
                                                   const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) {
  Instance& instance_info = GetInstanceInfo(instance);
  VkResult result = instance_info.dispatch_table().CreateXcbSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
  if (result != VK_SUCCESS) {
    return result;
  }
  instance_info.set_surface(*pSurface);

  return result;
}

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice,
                                                                  uint32_t queueFamilyIndex, VkSurfaceKHR surface,
                                                                  VkBool32* pSupported) {
  Instance& instance_info = GetInstanceInfo(physicalDevice);
  uint32_t queue_family_count;
  PackAndCallVkGetPhysicalDeviceQueueFamilyProperties(instance_info.command_stream(), physicalDevice,
                                                      &queue_family_count, nullptr);
  std::vector<VkQueueFamilyProperties> queue_family_properties(queue_family_count);
  PackAndCallVkGetPhysicalDeviceQueueFamilyProperties(instance_info.command_stream(), physicalDevice,
                                                      &queue_family_count, queue_family_properties.data());
  if (queueFamilyIndex >= queue_family_count) {
    return VK_ERROR_UNKNOWN;
  }

  *pSupported = (queue_family_properties[queueFamilyIndex].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0;

  return VK_SUCCESS;
}
}  // namespace vvk
