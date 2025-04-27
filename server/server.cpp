#include "server.h"

#include <spdlog/spdlog.h>
#include <vulkan/vulkan.h>

#include "server/execution_context.h"
#include "server/function_execution.h"
#include "vvk_server.pb.h"

namespace vvk::server {

grpc::Status VvkServerImpl::CallMethods(grpc::ServerContext* context,
                                        grpc::ServerReaderWriter<VvkResponse, VvkRequest>* stream) {
  spdlog::info("Connection opened {}", context->peer());
  VvkRequest request;
  ExecutionContext execution_context;
  while (stream->Read(&request)) {
    VvkResponse response;
    spdlog::trace("Request:\n{}", request.DebugString());
    spdlog::info("Calling {}", request.method());
    UnpackAndExecuteFunction(execution_context, request, &response);
    spdlog::trace("Response:\n{}", response.DebugString());
    stream->Write(response);
  }
  spdlog::info("Connection closed {}", context->peer());
  return grpc::Status::OK;
}

grpc::Status VvkServerImpl::GetFrameStreamingCapabilities(
    grpc::ServerContext* context, const vvk::server::VvkGetFrameStreamingCapabilitiesRequest* request,
    vvk::server::VvkGetFrameStreamingCapabilitiesResponse* response) {
  response->set_supports_uncompressed_stream(true);
  response->set_supports_h264_stream(false);
  response->set_supports_h265_stream(false);
  return grpc::Status::OK;
}

grpc::Status VvkServerImpl::RequestFrame(grpc::ServerContext* context, const vvk::server::VvkGetFrameRequest* request,
                                         grpc::ServerWriter<vvk::server::VvkGetFrameResponse>* writer) {
  VmaAllocator allocator = reinterpret_cast<VmaAllocator>(request->session_key());
  VmaAllocation buffer_allocation = reinterpret_cast<VmaAllocation>(request->frame_key());
  void* data = nullptr;
  vmaMapMemory(allocator, buffer_allocation, &data);
  uint32_t data_size = request->width() * request->height() * 4;
  VvkGetFrameResponse response;
  response.mutable_frame_data()->resize(data_size);
  std::memcpy(response.mutable_frame_data()->data(), data, data_size);
  writer->Write(response);

  vmaUnmapMemory(allocator, buffer_allocation);
  return grpc::Status::OK;
}

}  // namespace vvk::server
