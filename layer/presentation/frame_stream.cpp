#include "frame_stream.h"

#include "layer/context/instance.h"
#include "layer/presentation/h264_frame_stream.h"
#include "layer/presentation/uncompressed_frame_stream.h"

namespace vvk {

std::unique_ptr<FrameStream> FrameStream::Create(
    VkInstance local_instance, VkDevice local_device, VkPhysicalDevice remote_physical_device,
    uint32_t remote_graphics_queue_family_index, uint32_t remote_video_queue_family_index,
    const vvk::server::StreamingCapabilities &client_streaming_capabilities) {
  InstanceInfo &instance_info = GetInstanceInfo(local_instance);

  vvk::server::StreamingCapabilities server_streaming_capabilities = [&]() {
    vvk::server::VvkGetFrameStreamingCapabilitiesRequest request;
    request.set_physical_device(reinterpret_cast<uint64_t>(remote_physical_device));
    vvk::server::StreamingCapabilities response;
    grpc::ClientContext client_context;
    instance_info.stub().GetFrameStreamingCapabilities(&client_context, request, &response);
    return response;
  }();

  if (!server_streaming_capabilities.supports_uncompressed_stream()) {
    throw std::runtime_error("Uncompressed stream not supported");
  }

  if (server_streaming_capabilities.supports_h264_stream() && client_streaming_capabilities.supports_h264_stream()) {
    return std::unique_ptr<FrameStream>(new H264FrameStream(
        local_instance, local_device, remote_graphics_queue_family_index, remote_video_queue_family_index));
  }

  return std::unique_ptr<FrameStream>(
      new UncompressedFrameStream(local_instance, local_device, remote_graphics_queue_family_index));
}

}  // namespace vvk
