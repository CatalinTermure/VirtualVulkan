#include <spdlog/spdlog.h>

#include "3rdparty/ctpl_stl.h"
#include "commons/remote_call.h"
#include "layer/context/device.h"
#include "layer/functions.h"
#include "layer/sempahore_handle.h"

namespace vvk {

namespace {
constexpr int kThreadPoolSize = 16;
ctpl::thread_pool g_thread_pool(kThreadPoolSize);

constexpr uint64_t kVkQueueSubmitRemoteSemaphoreTimeout = UINT64_MAX - 3;
}  // namespace

VKAPI_ATTR VkResult VKAPI_CALL QueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits,
                                           VkFence fence) {
  VkDevice device = GetDeviceForQueue(queue);
  DeviceInfo& device_info = GetDeviceInfo(device);

  std::optional<VkFenceProxy> proxy_for_null_fence;
  if (fence == VK_NULL_HANDLE) {
    proxy_for_null_fence = device_info.fence_pool().GetFence();
    fence = **proxy_for_null_fence;
  }
  device_info.SetFenceLocal(fence);

  device_info.UploadMappedMemories();

  std::vector<VkSemaphore> semaphores_to_wait_local;
  semaphores_to_wait_local.reserve(submitCount);  // not the exact size but it's a good guess
  std::vector<std::binary_semaphore*> local_semaphores_to_signal_from_remote;
  local_semaphores_to_signal_from_remote.reserve(submitCount);  // not the exact size but it's a good guess
  std::vector<VkSubmitInfo> submit_infos;
  submit_infos.reserve(submitCount);
  std::vector<std::vector<VkPipelineStageFlags>> wait_stages;
  wait_stages.resize(submitCount);
  std::vector<std::vector<VkSemaphore>> semaphores_to_wait_remote;
  semaphores_to_wait_remote.resize(submitCount);
  std::vector<std::vector<VkSemaphore>> semaphores_to_signal_remote;
  semaphores_to_signal_remote.resize(submitCount);
  std::vector<std::vector<VkCommandBuffer>> command_buffers_remote;
  command_buffers_remote.resize(submitCount);

  // We look for local semaphores and remove them from the list
  // then we send the queue submit command to the server only once the semaphores are signaled
  // we check for the semaphores to be signaled using the presentation_fence of the semaphore
  // TODO: use timeline semaphores
  for (uint32_t submit_info_indx = 0; submit_info_indx < submitCount; submit_info_indx++) {
    VkSubmitInfo submit_info = pSubmits[submit_info_indx];

    for (uint32_t j = 0; j < submit_info.waitSemaphoreCount; j++) {
      if (submit_info.pWaitSemaphores[j]->state == SemaphoreState::kToBeSignaledLocal) {
        semaphores_to_wait_local.push_back(submit_info.pWaitSemaphores[j]);
      } else {
        semaphores_to_wait_remote[submit_info_indx].push_back(submit_info.pWaitSemaphores[j]->remote_handle);
        wait_stages[submit_info_indx].push_back(submit_info.pWaitDstStageMask[j]);
      }
    }
    submit_info.waitSemaphoreCount = semaphores_to_wait_remote[submit_info_indx].size();
    submit_info.pWaitSemaphores = semaphores_to_wait_remote[submit_info_indx].data();
    submit_info.pWaitDstStageMask = wait_stages[submit_info_indx].data();

    for (uint32_t j = 0; j < submit_info.commandBufferCount; j++) {
      VkCommandBuffer remote_command_buffer = device_info.GetRemoteHandle(submit_info.pCommandBuffers[j]);
      command_buffers_remote[submit_info_indx].push_back(remote_command_buffer);
      auto additional_semaphore = device_info.additional_semaphores.find(remote_command_buffer);
      if (additional_semaphore != device_info.additional_semaphores.end()) {
        semaphores_to_signal_remote[submit_info_indx].push_back(additional_semaphore->second);
      }
    }
    submit_info.commandBufferCount = command_buffers_remote[submit_info_indx].size();
    submit_info.pCommandBuffers = command_buffers_remote[submit_info_indx].data();

    for (uint32_t j = 0; j < submit_info.signalSemaphoreCount; j++) {
      semaphores_to_signal_remote[submit_info_indx].push_back(submit_info.pSignalSemaphores[j]->remote_handle);
      submit_info.pSignalSemaphores[j]->state = SemaphoreState::kToBeSignaledRemote;
      local_semaphores_to_signal_from_remote.push_back(&submit_info.pSignalSemaphores[j]->remote_to_local_semaphore);
    }
    submit_info.signalSemaphoreCount = semaphores_to_signal_remote[submit_info_indx].size();
    submit_info.pSignalSemaphores = semaphores_to_signal_remote[submit_info_indx].data();

    submit_infos.emplace_back(std::move(submit_info));
  }

  {
    std::vector<VkPipelineStageFlags> local_wait_stages(semaphores_to_wait_local.size(),
                                                        VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
    std::vector<VkSemaphore> semaphores_to_wait_local_handles(semaphores_to_wait_local.size());
    for (size_t i = 0; i < semaphores_to_wait_local.size(); i++) {
      semaphores_to_wait_local_handles[i] = semaphores_to_wait_local[i]->local_handle;
    }
    VkFenceProxy aux_fence = device_info.fence_pool().GetFence();
    VkSubmitInfo local_semaphores_submit_info{
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .pNext = nullptr,
        .waitSemaphoreCount = static_cast<uint32_t>(semaphores_to_wait_local_handles.size()),
        .pWaitSemaphores = semaphores_to_wait_local_handles.data(),
        .pWaitDstStageMask = local_wait_stages.data(),
        .commandBufferCount = 0,
        .pCommandBuffers = nullptr,
        .signalSemaphoreCount = 0,
        .pSignalSemaphores = nullptr,
    };
    device_info.dispatch_table().QueueSubmit(*device_info.present_queue(), 1, &local_semaphores_submit_info,
                                             *aux_fence);
    if (semaphores_to_wait_local.size())
      spdlog::trace("VkQueueSubmit: Waiting for local semaphore {}", (void*)semaphores_to_wait_local[0]);
    g_thread_pool.push(
        [&dispatch_table = device_info.dispatch_table(), &command_stream = device_info.instance_info().command_stream(),
         remote_queue = device_info.GetRemoteHandle(queue), remote_fence = device_info.GetRemoteHandle(fence),
         local_fence = fence, &fence_pool = device_info.fence_pool(), aux_fence = std::move(aux_fence), device,
         proxy_for_null_fence = std::move(proxy_for_null_fence),
         remote_device = device_info.instance_info().GetRemoteHandle(device), submits = std::move(submit_infos),
         present_queue = *device_info.present_queue(), semaphores_to_wait_local = std::move(semaphores_to_wait_local),
         semaphores_to_signal = std::move(local_semaphores_to_signal_from_remote),
         // we need to move the vectors into this thread so they don't get deleted
         unused1 = std::move(semaphores_to_wait_remote), unused2 = std::move(semaphores_to_signal_remote),
         unused3 = std::move(command_buffers_remote), unused4 = std::move(wait_stages)](int unused) {
          // Wait for local semaphores
          spdlog::trace("VkQueueSubmit: Waiting for local semaphores");
          VkResult result = dispatch_table.WaitForFences(device, 1, aux_fence.get(), VK_TRUE, UINT64_MAX);
          if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to wait for local semaphores");
          }
          result = dispatch_table.ResetFences(device, 1, aux_fence.get());
          if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to reset local fences");
          }
          spdlog::trace("VkQueueSubmit: Finished waiting for local semaphores");
          for (VkSemaphore semaphore : semaphores_to_wait_local) {
            semaphore->state = SemaphoreState::kUnsignaled;
          }
          // Then we can submit to the remote queue
          result = PackAndCallVkQueueSubmit(command_stream, remote_queue, submits.size(), submits.data(), remote_fence);
          if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to submit to remote queue");
          }
          spdlog::trace("VkQueueSubmit: Finished submitting to remote queue");

          // After that, we wait for the remote fence to be signaled, so we can signal the local fence
          result = PackAndCallVkWaitForFences(command_stream, remote_device, 1, &remote_fence, VK_TRUE,
                                              kVkQueueSubmitRemoteSemaphoreTimeout);
          if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to wait for remote fence");
          }
          result = PackAndCallVkResetFences(command_stream, remote_device, 1, &remote_fence);
          if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to reset remote fences");
          }
          spdlog::trace("VkQueueSubmit: Finished waiting for remote fence");
          if (!proxy_for_null_fence.has_value()) {
            dispatch_table.QueueSubmit(present_queue, 0, nullptr, local_fence);
          }
          for (auto* semaphore : semaphores_to_signal) {
            semaphore->release();
          }
          spdlog::trace("VkQueueSubmit: Finished signaling remote_to_local semaphores");
        });
  }

  return VK_SUCCESS;
}
VKAPI_ATTR VkResult VKAPI_CALL QueueWaitIdle(VkQueue queue) {
  DeviceInfo& device_info = GetDeviceInfo(queue);
  return PackAndCallVkQueueWaitIdle(device_info.instance_info().command_stream(), device_info.GetRemoteHandle(queue));
}

}  // namespace vvk
