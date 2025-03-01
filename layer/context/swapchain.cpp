#include "swapchain.h"

#include <map>
#include <mutex>

#include "commons/remote_call.h"

namespace vvk {

namespace {
std::mutex swapchain_info_lock;
std::map<VkSwapchainKHR, SwapchainInfo> g_swapchain_infos;
}  // namespace

SwapchainInfo::SwapchainInfo(VkDevice device, VmaAllocator allocator)
    : device_(device), allocator_(allocator), instance_info_(GetInstanceInfo(device)) {}

SwapchainInfo::~SwapchainInfo() {
  for (auto [remote_image, remote_allocation] : remote_images_) {
    vmaDestroyImage(allocator_, remote_image, remote_allocation);
  }
}

VkImage SwapchainInfo::CreateImage(const VkImageCreateInfo& create_info, const VmaAllocationCreateInfo& alloc_info) {
  VkImage remote_image;
  VmaAllocation remote_allocation;
  VkResult result = vmaCreateImage(allocator_, &create_info, &alloc_info, &remote_image, &remote_allocation, nullptr);
  if (result != VK_SUCCESS) {
    return VK_NULL_HANDLE;
  }
  remote_images_.emplace_back(remote_image, remote_allocation);
  return remote_image;
}

SwapchainInfo& GetSwapchainInfo(VkSwapchainKHR swapchain) {
  std::lock_guard lock(swapchain_info_lock);
  return g_swapchain_infos.at(swapchain);
}

SwapchainInfo& SetSwapchainInfo(VkSwapchainKHR swapchain, VkDevice device, VmaAllocator allocator) {
  std::lock_guard lock(swapchain_info_lock);
  auto [iter, inserted] = g_swapchain_infos.try_emplace(swapchain, device, allocator);
  assert(inserted);
  return iter->second;
}

void RemoveSwapchainInfo(VkSwapchainKHR swapchain) {
  std::lock_guard lock(swapchain_info_lock);
  g_swapchain_infos.erase(swapchain);
}

}  // namespace vvk