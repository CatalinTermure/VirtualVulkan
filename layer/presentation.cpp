#include "presentation.h"

#include <functional>
#include <mutex>
#include <queue>
#include <thread>

#include "commons/remote_call.h"
#include "layer/context/device.h"
#include "layer/context/instance.h"
#include "layer/context/swapchain.h"
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

void PresentationThreadPresentFrame(PresentationThread &presentation_thread, VkPresentInfoKHR *present_info) {}

}  // namespace vvk
