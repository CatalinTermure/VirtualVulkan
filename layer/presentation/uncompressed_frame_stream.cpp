#include "uncompressed_frame_stream.h"

#include <spdlog/spdlog.h>

#include <thread>

#include "commons/remote_call.h"
#include "layer/context/device.h"
#include "layer/context/instance.h"
#include "layer/context/swapchain.h"
#include "layer/sempahore_handle.h"

namespace vvk {

UncompressedFrameStream::UncompressedFrameStream(VkInstance instance, VkDevice device, uint32_t queue_family_index)
    : local_instance(instance), local_device(device), remote_graphics_queue_family_index(queue_family_index) {}

void UncompressedFrameStream::AssociateSwapchain(VkSwapchainKHR swapchain, const VkExtent2D &swapchain_image_extent) {
  Instance &instance_info = GetInstanceInfo(local_instance);
  Swapchain &swapchain_info = GetSwapchainInfo(swapchain);
  vvk::server::VvkRequest request;
  request.set_method("setupPresentation");
  vvk::server::VvkSetupPresentationRequest &setup_presentation = *request.mutable_setuppresentation();
  setup_presentation.set_instance(reinterpret_cast<uint64_t>(instance_info.GetRemoteHandle(local_instance)));
  setup_presentation.set_device(reinterpret_cast<uint64_t>(instance_info.GetRemoteHandle(local_device)));
  for (auto &[remote_image, _] : swapchain_info.GetRemoteImages()) {
    setup_presentation.add_remote_images(reinterpret_cast<uint64_t>(remote_image));
  }
  setup_presentation.set_width(swapchain_image_extent.width);
  setup_presentation.set_height(swapchain_image_extent.height);
  setup_presentation.mutable_uncompressed_stream_create_info()->set_queue_family_index(
      remote_graphics_queue_family_index);
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
  remote_frame_keys.reserve(response.setuppresentation().frame_keys_size());
  for (int i = 0; i < response.setuppresentation().uncompressed_stream_info().remote_buffers_size(); i++) {
    remote_buffers.push_back(response.setuppresentation().uncompressed_stream_info().remote_buffers(i));
    remote_frame_keys.push_back(response.setuppresentation().frame_keys(i));
  }
  swapchains.push_back(SwapchainPresentationInfo{
      .swapchain = swapchain,
      .remote_session_key = response.setuppresentation().session_key(),
      .remote_buffers = remote_buffers,
      .remote_frame_keys = remote_frame_keys,
      .image_extent = swapchain_image_extent,
      .copy_context = MemoryToImageCopyContext(local_device, swapchain_info.GetLocalSwapchainImages(),
                                               swapchain_image_extent, BufferLayout{}, false, true),
  });
}

void UncompressedFrameStream::RemoveSwapchain(VkSwapchainKHR swapchain) {
  swapchains.erase(std::remove_if(swapchains.begin(), swapchains.end(),
                                  [swapchain](const SwapchainPresentationInfo &swapchain_present_info) {
                                    return swapchain_present_info.swapchain == swapchain;
                                  }),
                   swapchains.end());
}

void UncompressedFrameStream::SetupFrame(VkCommandBuffer remote_command_buffer, uint32_t swapchain_image_index) {
  auto &command_stream = GetInstanceInfo(local_instance).command_stream();

  for (auto &swapchain_present_info : swapchains) {
    Swapchain &swapchain_info = GetSwapchainInfo(swapchain_present_info.swapchain);
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

VkResult UncompressedFrameStream::PresentFrame(VkQueue queue, const VkPresentInfoKHR &original_present_info) {
  Device &device_info = GetDeviceInfo(queue);
  Instance &instance_info = device_info.instance_info();
  const VkuDeviceDispatchTable &dispatch_table = device_info.dispatch_table();

  std::vector<VkSemaphore> local_semaphores_to_wait;
  std::vector<VkSemaphore> remote_semaphores_to_wait;
  std::vector<VkSwapchainKHR> swapchains_to_present;
  std::vector<Swapchain *> swapchain_infos;
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
      throw std::runtime_error(
          std::format("Invalid semaphore state in QueuePresentKHR for semaphore: {}", (void *)semaphore));
    }
  }
  present_info.waitSemaphoreCount = local_semaphores_to_wait.size();
  present_info.pWaitSemaphores = local_semaphores_to_wait.data();

  for (uint32_t i = 0; i < present_info.swapchainCount; i++) {
    swapchains_to_present.push_back(present_info.pSwapchains[i]);
    swapchain_infos.push_back(&GetSwapchainInfo(present_info.pSwapchains[i]));
    image_indices.push_back(present_info.pImageIndices[i]);
  }
  present_info.pSwapchains = swapchains_to_present.data();
  present_info.pImageIndices = image_indices.data();

  if (remote_semaphores_to_wait.empty()) {
    throw std::runtime_error("No fences to wait for");
  }

  std::thread runner_thread(
      [queue, original_present_info, this, remote_semaphores_to_wait = std::move(remote_semaphores_to_wait),
       &instance_info, &device_info, present_info, local_semaphores_to_wait = std::move(local_semaphores_to_wait),
       swapchains_to_present = std::move(swapchains_to_present), image_indices = std::move(image_indices),
       swapchain_infos = std::move(swapchain_infos), &dispatch_table]() mutable {
        VkDevice local_device = GetDeviceForQueue(queue);
        VkQueue local_queue = *device_info.present_queue();
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
            PackAndCallVkQueueSubmit(instance_info.command_stream(), device_info.GetRemoteHandle(queue), 1, &submit,
                                     nullptr);
          }
        }

        std::vector<grpc::ClientContext> client_contexts(present_info.swapchainCount);
        std::vector<std::unique_ptr<grpc::ClientReader<vvk::server::VvkGetFrameResponse>>> client_readers;
        client_readers.reserve(present_info.swapchainCount);
        for (uint32_t i = 0; i < present_info.swapchainCount; i++) {
          vvk::server::VvkGetFrameRequest request;
          bool swapchain_exists = false;
          for (auto &swapchain_present_info : swapchains) {
            if (swapchain_present_info.swapchain == present_info.pSwapchains[i]) {
              request.set_session_key(swapchain_present_info.remote_session_key);
              request.set_frame_key(swapchain_present_info.remote_frame_keys[present_info.pImageIndices[i]]);
              request.set_stream_type(vvk::server::VvkStreamType::VVK_STREAM_TYPE_UNCOMPRESSED);
              swapchain_exists = true;
              break;
            }
          }
          if (!swapchain_exists) {
            spdlog::info("Swapchain {} not found in UncompressedFrameStream during present",
                         (void *)present_info.pSwapchains[i]);
            return VK_ERROR_UNKNOWN;
          }
          client_readers.emplace_back(instance_info.stub().RequestFrame(&client_contexts[i], request));
        }

        {
          for (uint32_t i = 0; i < present_info.swapchainCount; i++) {
            vvk::server::VvkGetFrameResponse response;
            std::string data;
            while (client_readers[i]->Read(&response)) {
              data.append(response.frame_data());
            }
            client_readers[i]->Finish();

            for (auto &swapchain_present_info : swapchains) {
              if (swapchain_present_info.swapchain == present_info.pSwapchains[i]) {
                swapchain_present_info.copy_context.CopyMemoryToImage(present_info.pImageIndices[i], data);
                local_semaphores_to_wait.push_back(*swapchain_present_info.copy_context.GetSemaphoreToSignal());
              }
            }
          }
        }
        present_info.waitSemaphoreCount = local_semaphores_to_wait.size();
        present_info.pWaitSemaphores = local_semaphores_to_wait.data();

        dispatch_table.QueuePresentKHR(local_queue, &present_info);
        for (uint32_t i = 0; i < present_info.swapchainCount; i++) {
          swapchain_infos[i]->SetImageReleased();
          spdlog::info("Released image {} for swapchain {}", present_info.pImageIndices[i],
                       (void *)present_info.pSwapchains[i]);
        }
        return VK_SUCCESS;
      });

  runner_thread.detach();

  return VK_SUCCESS;
}

}  // namespace vvk
