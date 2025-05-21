#include "presentation.h"

#include <functional>
#include <mutex>
#include <queue>
#include <thread>

#include "commons/remote_call.h"
#include "layer/context/device.h"
#include "layer/context/instance.h"
#include "layer/context/swapchain.h"
#include "layer/sempahore_handle.h"
#include "vvk_server.grpc.pb.h"

namespace vvk {

namespace {

void PresentationThreadWorker(PresentationThread *presentation_thread) {
  while (!presentation_thread->should_exit) {
    presentation_thread->work_queue_semaphore.acquire();
    if (presentation_thread->work_queue.empty()) {
      throw std::runtime_error("Work queue is empty but semaphore was acquired");
    }
    auto work = std::move(presentation_thread->work_queue.front());
    presentation_thread->work_queue.pop();
    work();
  }
}
}  // namespace

PresentationThread::PresentationThread(VkInstance instance, VkDevice device, uint32_t queue_family_index)
    : local_instance(instance),
      local_device(device),
      remote_graphics_queue_family_index(queue_family_index),
      work_queue{},
      work_queue_semaphore{0},
      should_exit{false},
      thread{std::bind(PresentationThreadWorker, this)} {}

std::unique_ptr<PresentationThread> PresentationThreadCreate(VkInstance local_instance, VkDevice local_device,
                                                             VkPhysicalDevice remote_physical_device,
                                                             uint32_t remote_graphics_queue_family_index) {
  InstanceInfo &instance_info = GetInstanceInfo(local_instance);

  vvk::server::VvkGetFrameStreamingCapabilitiesResponse server_streaming_capabilities = [&]() {
    vvk::server::VvkGetFrameStreamingCapabilitiesRequest request;
    request.set_physical_device(reinterpret_cast<uint64_t>(remote_physical_device));
    vvk::server::VvkGetFrameStreamingCapabilitiesResponse response;
    grpc::ClientContext client_context;
    instance_info.stub().GetFrameStreamingCapabilities(&client_context, request, &response);
    return response;
  }();

  if (!server_streaming_capabilities.supports_uncompressed_stream()) {
    throw std::runtime_error("Uncompressed stream not supported");
  }

  std::unique_ptr<PresentationThread> presentation_thread =
      std::make_unique<PresentationThread>(local_instance, local_device, remote_graphics_queue_family_index);

  return presentation_thread;
}

void PresentationThreadAssociateSwapchain(PresentationThread &presentation_thread, VkSwapchainKHR swapchain,
                                          const VkExtent2D &swapchain_image_extent) {
  InstanceInfo &instance_info = GetInstanceInfo(presentation_thread.local_instance);
  SwapchainInfo &swapchain_info = GetSwapchainInfo(swapchain);
  vvk::server::VvkRequest request;
  request.set_method("setupPresentation");
  vvk::server::VvkSetupPresentationRequest &setup_presentation = *request.mutable_setuppresentation();
  setup_presentation.set_instance(
      reinterpret_cast<uint64_t>(instance_info.GetRemoteHandle(presentation_thread.local_instance)));
  setup_presentation.set_device(
      reinterpret_cast<uint64_t>(instance_info.GetRemoteHandle(presentation_thread.local_device)));
  for (auto &[remote_image, _] : swapchain_info.GetRemoteImages()) {
    setup_presentation.add_remote_images(reinterpret_cast<uint64_t>(remote_image));
  }
  setup_presentation.set_width(swapchain_image_extent.width);
  setup_presentation.set_height(swapchain_image_extent.height);
  setup_presentation.mutable_uncompressed_stream_create_info()->set_queue_family_index(
      presentation_thread.remote_graphics_queue_family_index);
  if (!instance_info.command_stream().Write(request)) {
    throw std::runtime_error("Failed to send setup presentation request");
  }

  vvk::server::VvkResponse response;
  if (!instance_info.command_stream().Read(&response)) {
    throw std::runtime_error("Failed to read setup presentation response");
  }
  std::vector<uint64_t> remote_buffers;
  std::vector<uint64_t> remote_frame_keys;
  remote_buffers.reserve(response.setuppresentation().uncompressed_stream_info().remote_buffers_size());
  remote_frame_keys.reserve(response.setuppresentation().uncompressed_stream_info().frame_keys_size());
  for (int i = 0; i < response.setuppresentation().uncompressed_stream_info().remote_buffers_size(); i++) {
    remote_buffers.push_back(response.setuppresentation().uncompressed_stream_info().remote_buffers(i));
    remote_frame_keys.push_back(response.setuppresentation().uncompressed_stream_info().frame_keys(i));
  }
  presentation_thread.swapchains.push_back(SwapchainPresentationInfo{
      .swapchain = swapchain,
      .remote_session_key = response.setuppresentation().uncompressed_stream_info().session_key(),
      .remote_buffers = remote_buffers,
      .remote_frame_keys = remote_frame_keys,
      .image_extent = swapchain_image_extent,
      .swapchain_image_index = std::numeric_limits<uint32_t>::max(),
  });
}

void PresentationThreadRemoveSwapchain(PresentationThread &presentation_thread, VkSwapchainKHR swapchain) {
  presentation_thread.swapchains.erase(
      std::remove_if(presentation_thread.swapchains.begin(), presentation_thread.swapchains.end(),
                     [swapchain](const SwapchainPresentationInfo &swapchain_present_info) {
                       return swapchain_present_info.swapchain == swapchain;
                     }),
      presentation_thread.swapchains.end());
}

void PresentationThreadSetupFrame(PresentationThread &presentation_thread, VkCommandBuffer remote_command_buffer,
                                  uint32_t swapchain_image_index) {
  auto &command_stream = GetInstanceInfo(presentation_thread.local_instance).command_stream();

  for (auto &swapchain_present_info : presentation_thread.swapchains) {
    SwapchainInfo &swapchain_info = GetSwapchainInfo(swapchain_present_info.swapchain);
    VkImage remote_image = swapchain_info.GetRemoteImages()[swapchain_image_index].first;

    VkBufferImageCopy region = {
        .bufferOffset = 0,
        .bufferRowLength = 0,
        .bufferImageHeight = 0,
        .imageSubresource =
            {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .mipLevel = 0,
                .baseArrayLayer = 0,
                .layerCount = 1,
            },
        .imageOffset = {0, 0, 0},
        .imageExtent =
            {
                swapchain_present_info.image_extent.width,
                swapchain_present_info.image_extent.height,
                1,
            },
    };
    PackAndCallVkCmdCopyImageToBuffer(
        command_stream, remote_command_buffer, remote_image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
        reinterpret_cast<VkBuffer>(swapchain_present_info.remote_buffers[swapchain_image_index]), 1, &region);
  }
}

void PresentationThreadPresentFrame(PresentationThread &presentation_thread, VkQueue queue,
                                    const VkPresentInfoKHR &original_present_info) {
  DeviceInfo &device_info = GetDeviceInfo(queue);
  VkQueue local_queue = *device_info.present_queue();
  VkDevice local_device = GetDeviceForQueue(queue);
  InstanceInfo &instance_info = device_info.instance_info();
  const VkuDeviceDispatchTable &dispatch_table = device_info.dispatch_table();

  std::vector<VkSemaphore> local_semaphores_to_wait;
  std::vector<VkSemaphore> remote_semaphores_to_wait;
  std::vector<VkSwapchainKHR> swapchains;
  std::vector<uint32_t> image_indices;

  VkPresentInfoKHR present_info = original_present_info;
  for (uint32_t i = 0; i < present_info.waitSemaphoreCount; i++) {
    VkSemaphore semaphore = present_info.pWaitSemaphores[i];
    if (semaphore->state == SemaphoreState::kToBeSignaledRemote) {
      remote_semaphores_to_wait.push_back(semaphore);
      semaphore->state = SemaphoreState::kUnsignaled;
    } else if (semaphore->state == SemaphoreState::kToBeSignaledLocal) {
      local_semaphores_to_wait.push_back(semaphore->local_handle);
      semaphore->state = SemaphoreState::kUnsignaled;
    } else {
      throw std::runtime_error("Invalid semaphore state in QueuePresentKHR");
    }
  }
  present_info.waitSemaphoreCount = local_semaphores_to_wait.size();
  present_info.pWaitSemaphores = local_semaphores_to_wait.data();

  for (uint32_t i = 0; i < present_info.swapchainCount; i++) {
    swapchains.push_back(present_info.pSwapchains[i]);
    image_indices.push_back(present_info.pImageIndices[i]);
  }
  present_info.pSwapchains = swapchains.data();
  present_info.pImageIndices = image_indices.data();

  if (remote_semaphores_to_wait.empty()) {
    throw std::runtime_error("No fences to wait for");
  }

  for (auto *semaphore : remote_semaphores_to_wait) {
    semaphore->remote_to_local_semaphore.acquire();
    // Unsignal the semaphore on the remote side
    {
      VkPipelineStageFlags wait_dst_stage_mask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
      VkSubmitInfo submit = {
          .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
          .pNext = nullptr,
          .waitSemaphoreCount = 1,
          .pWaitSemaphores = &semaphore->remote_handle,
          .pWaitDstStageMask = &wait_dst_stage_mask,
          .commandBufferCount = 0,
          .pCommandBuffers = nullptr,
          .signalSemaphoreCount = 0,
          .pSignalSemaphores = nullptr,
      };
      PackAndCallVkQueueSubmit(instance_info.command_stream(), device_info.GetRemoteHandle(queue), 1, &submit, nullptr);
    }
  }

  std::vector<grpc::ClientContext> client_contexts(present_info.swapchainCount);
  std::vector<std::unique_ptr<grpc::ClientReader<vvk::server::VvkGetFrameResponse>>> client_readers;
  client_readers.reserve(present_info.swapchainCount);
  for (uint32_t i = 0; i < present_info.swapchainCount; i++) {
    vvk::server::VvkGetFrameRequest request;
    for (auto &swapchain_present_info : presentation_thread.swapchains) {
      if (swapchain_present_info.swapchain == present_info.pSwapchains[i]) {
        request.set_session_key(swapchain_present_info.remote_session_key);
        request.set_frame_key(swapchain_present_info.remote_frame_keys[swapchain_present_info.swapchain_image_index]);
        request.set_width(swapchain_present_info.image_extent.width);
        request.set_height(swapchain_present_info.image_extent.height);
        break;
      }
    }
    client_readers.emplace_back(instance_info.stub().RequestFrame(&client_contexts[i], request));
  }

  {
    std::vector<VkFenceProxy> fences;
    fences.reserve(present_info.swapchainCount);
    for (uint32_t i = 0; i < present_info.swapchainCount; i++) {
      fences.emplace_back(device_info.fence_pool().GetFence());
      vvk::server::VvkGetFrameResponse response;
      std::string data;
      while (client_readers[i]->Read(&response)) {
        data.append(response.frame_data());
      }
      client_readers[i]->Finish();

      SwapchainInfo &swapchain_info = GetSwapchainInfo(present_info.pSwapchains[i]);
      swapchain_info.CopyMemoryToImage(present_info.pImageIndices[i], data, {}, {}, {}, *fences.back());
    }

    std::vector<VkFence> fences_to_wait;
    fences_to_wait.reserve(fences.size());
    for (auto &fence : fences) {
      fences_to_wait.push_back(*fence);
    }

    dispatch_table.WaitForFences(local_device, fences_to_wait.size(), fences_to_wait.data(), VK_TRUE, UINT64_MAX);
    dispatch_table.ResetFences(local_device, fences_to_wait.size(), fences_to_wait.data());
  }

  dispatch_table.QueuePresentKHR(local_queue, &present_info);
}

}  // namespace vvk
