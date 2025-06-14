#include "swapchain.h"

#include <map>
#include <mutex>

#include "commons/remote_call.h"
#include "layer/context/device.h"

namespace vvk {

namespace {
std::mutex swapchain_info_lock;
std::map<VkSwapchainKHR, SwapchainInfo> g_swapchain_infos;
}  // namespace

SwapchainInfo::SwapchainInfo(VkSwapchainKHR swapchain, VkDevice device, VmaAllocator remote_allocator,
                             const std::vector<VkImage>& swapchain_images, const VkExtent2D& swapchain_image_extent)
    : swapchain_handle_(swapchain),
      device_(device),
      instance_info_(GetInstanceInfo(device)),
      remote_allocator_(remote_allocator),
      remote_images_(),
      acquired_images_(swapchain_images.size() - 1) {
  local_swapchain_images_ = swapchain_images;
}  // namespace vvk

SwapchainInfo::~SwapchainInfo() {
  std::lock_guard g(lock_);
  Device& device_info = GetDeviceInfo(device_);
  for (auto [remote_image, remote_allocation] : remote_images_) {
    vmaDestroyImage(remote_allocator_, remote_image, remote_allocation);
    device_info.swapchain_images.erase(remote_image);
  }
}

VkImage SwapchainInfo::CreateImageRemote(const VkImageCreateInfo& create_info,
                                         const VmaAllocationCreateInfo& alloc_info) {
  VkImage remote_image;
  VmaAllocation remote_allocation;
  VkResult result =
      vmaCreateImage(remote_allocator_, &create_info, &alloc_info, &remote_image, &remote_allocation, nullptr);
  if (result != VK_SUCCESS) {
    return VK_NULL_HANDLE;
  }
  remote_images_.emplace_back(remote_image, remote_allocation);
  remote_image_format_ = create_info.format;
  return remote_image;
}

SwapchainInfo& GetSwapchainInfo(VkSwapchainKHR swapchain) {
  std::lock_guard lock(swapchain_info_lock);
  return g_swapchain_infos.at(swapchain);
}

SwapchainInfo& SetSwapchainInfo(VkSwapchainKHR swapchain, VkDevice device, VmaAllocator remote_allocator,
                                const std::vector<VkImage>& swapchain_images,
                                const VkExtent2D& swapchain_image_extent) {
  std::lock_guard lock(swapchain_info_lock);
  auto [iter, inserted] = g_swapchain_infos.try_emplace(swapchain, swapchain, device, remote_allocator,
                                                        swapchain_images, swapchain_image_extent);
  assert(inserted);
  return iter->second;
}

void RemoveSwapchainInfo(VkSwapchainKHR swapchain) {
  std::lock_guard lock(swapchain_info_lock);
  g_swapchain_infos.erase(swapchain);
}

}  // namespace vvk