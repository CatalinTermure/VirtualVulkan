#include <future>

#include "3rdparty/ctpl_stl.h"
#include "commons/remote_call.h"
#include "layer/context/device.h"
#include "layer/functions.h"

namespace vvk {

namespace {

constexpr int kThreadPoolSize = 4;
ctpl::thread_pool g_fence_wait_thread_pool(kThreadPoolSize);

}  // namespace

VKAPI_ATTR VkResult VKAPI_CALL CreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo,
                                           const VkAllocationCallbacks* pAllocator, VkFence* pFence) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  VkResult result = device_info.dispatch_table().CreateFence(device, pCreateInfo, pAllocator, pFence);
  if (result != VK_SUCCESS) {
    return result;
  }
  VkFenceCreateInfo fence_create_info_copy = *pCreateInfo;
  if (pCreateInfo->flags & VK_FENCE_CREATE_SIGNALED_BIT) {
    device_info.SetFenceLocal(*pFence);
    fence_create_info_copy.flags &= ~VK_FENCE_CREATE_SIGNALED_BIT;
  }
  VkFence remote_fence = VK_NULL_HANDLE;
  result = PackAndCallVkCreateFence(device_info.instance_info().command_stream(),
                                    device_info.instance_info().GetRemoteHandle(device), &fence_create_info_copy,
                                    pAllocator, &remote_fence);
  if (result != VK_SUCCESS) {
    device_info.dispatch_table().DestroyFence(device, *pFence, pAllocator);
    return result;
  }
  device_info.SetRemoteHandle(*pFence, remote_fence);
  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  device_info.dispatch_table().DestroyFence(device, fence, pAllocator);
  PackAndCallVkDestroyFence(device_info.instance_info().command_stream(),
                            device_info.instance_info().GetRemoteHandle(device), device_info.GetRemoteHandle(fence),
                            pAllocator);
  device_info.RemoveRemoteHandle(fence);
}

VKAPI_ATTR VkResult VKAPI_CALL WaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences,
                                             VkBool32 waitAll, uint64_t timeout) {
  if (!waitAll) {
    throw std::runtime_error("WaitForFences with waitAll=false is not supported");
  }
  DeviceInfo& device_info = GetDeviceInfo(device);

  std::vector<VkFence> local_fences;
  local_fences.reserve(fenceCount);
  std::vector<VkFence> remote_fences;
  remote_fences.reserve(fenceCount);

  for (uint32_t i = 0; i < fenceCount; i++) {
    if (device_info.IsLocalFence(pFences[i])) {
      local_fences.push_back(pFences[i]);
    } else {
      remote_fences.push_back(device_info.GetRemoteHandle(pFences[i]));
    }
  }

  VkResult local_result = VK_SUCCESS;
  VkResult remote_result = VK_SUCCESS;
  std::future<void> local_wait_future;
  std::future<void> remote_wait_future;

  if (!local_fences.empty()) {
    local_wait_future = g_fence_wait_thread_pool.push(
        [&device_info, &local_fences, &local_result, device, waitAll, timeout](int unused) {
          local_result = device_info.dispatch_table().WaitForFences(device, local_fences.size(), local_fences.data(),
                                                                    waitAll, timeout);
        });
  }
  if (!remote_fences.empty()) {
    remote_wait_future = g_fence_wait_thread_pool.push(
        [&device_info, &remote_fences, &remote_result, device, waitAll, timeout](int unused) {
          remote_result = PackAndCallVkWaitForFences(device_info.instance_info().command_stream(),
                                                     device_info.instance_info().GetRemoteHandle(device),
                                                     remote_fences.size(), remote_fences.data(), waitAll, timeout);
        });
  }

  if (!local_fences.empty()) {
    local_wait_future.wait();
  }
  if (!remote_fences.empty()) {
    remote_wait_future.wait();
  }

  if (local_result != VK_SUCCESS) {
    return local_result;
  }
  return remote_result;
}

VKAPI_ATTR VkResult VKAPI_CALL ResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences) {
  DeviceInfo& device_info = GetDeviceInfo(device);

  std::vector<VkFence> local_fences;
  local_fences.reserve(fenceCount);
  std::vector<VkFence> remote_fences;
  remote_fences.reserve(fenceCount);

  for (uint32_t i = 0; i < fenceCount; i++) {
    if (device_info.IsLocalFence(pFences[i])) {
      local_fences.push_back(pFences[i]);
    } else {
      remote_fences.push_back(device_info.GetRemoteHandle(pFences[i]));
    }
  }

  if (!local_fences.empty()) {
    VkResult result = device_info.dispatch_table().ResetFences(device, local_fences.size(), local_fences.data());
    if (result != VK_SUCCESS) {
      return result;
    }
    for (VkFence fence : local_fences) {
      device_info.ResetFenceLocal(fence);
    }
  }

  if (!remote_fences.empty()) {
    VkResult result = PackAndCallVkResetFences(device_info.instance_info().command_stream(),
                                               device_info.instance_info().GetRemoteHandle(device),
                                               remote_fences.size(), remote_fences.data());
    if (result != VK_SUCCESS) {
      return result;
    }
  }

  return VK_SUCCESS;
}

}  // namespace vvk
