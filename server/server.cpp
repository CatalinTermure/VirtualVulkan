#include "server.h"

#include <dlfcn.h>
#include <renderdoc_app.h>
#include <spdlog/spdlog.h>
#include <vulkan/vulkan.h>

#include "server/execution_context.h"
#include "server/function_execution.h"
#include "vvk_server.pb.h"

namespace vvk::server {

namespace {
RENDERDOC_API_1_1_2* rdoc_api = NULL;
}  // namespace

grpc::Status VvkServerImpl::CallMethods(grpc::ServerContext* context,
                                        grpc::ServerReaderWriter<VvkResponse, VvkRequest>* stream) {
  spdlog::info("Connection opened {}", context->peer());
  VvkRequest request;
  ExecutionContext execution_context;

  if (void* mod = dlopen("librenderdoc.so", RTLD_NOW | RTLD_NOLOAD)) {
    pRENDERDOC_GetAPI RENDERDOC_GetAPI = (pRENDERDOC_GetAPI)dlsym(mod, "RENDERDOC_GetAPI");
    int ret = RENDERDOC_GetAPI(eRENDERDOC_API_Version_1_1_2, (void**)&rdoc_api);
    assert(ret == 1);
  }

  while (stream->Read(&request)) {
    VvkResponse response;
    spdlog::trace("Request:\n{}", request.DebugString());
    spdlog::info("Calling {}", request.method());
    if (rdoc_api && request.method() == "setupPresentation") {
      rdoc_api->StartFrameCapture(nullptr, nullptr);
    }
    UnpackAndExecuteFunction(execution_context, request, &response);
    spdlog::trace("Response:\n{}", response.DebugString());
    stream->Write(response);
  }
  spdlog::info("Connection closed {}", context->peer());
  return grpc::Status::OK;
}

grpc::Status VvkServerImpl::GetFrameStreamingCapabilities(
    grpc::ServerContext* context, const vvk::server::VvkGetFrameStreamingCapabilitiesRequest* request,
    vvk::server::StreamingCapabilities* response) {
  response->set_supports_uncompressed_stream(true);
  uint32_t local_device_extension_count = 0;
  std::vector<::VkExtensionProperties> local_device_extensions_properties;
  VkPhysicalDevice physical_device = reinterpret_cast<VkPhysicalDevice>(request->physical_device());
  vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &local_device_extension_count, nullptr);
  local_device_extensions_properties.resize(local_device_extension_count);
  vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &local_device_extension_count,
                                       local_device_extensions_properties.data());

  bool local_device_supports_h264_encode =
      std::find_if(local_device_extensions_properties.begin(), local_device_extensions_properties.end(),
                   [](const ::VkExtensionProperties& extension) {
                     return strcmp(extension.extensionName, VK_KHR_VIDEO_ENCODE_H264_EXTENSION_NAME) == 0;
                   }) != local_device_extensions_properties.end();

  response->set_supports_h264_stream(local_device_supports_h264_encode);

  bool local_device_supports_h265_encode =
      std::find_if(local_device_extensions_properties.begin(), local_device_extensions_properties.end(),
                   [](const ::VkExtensionProperties& extension) {
                     return strcmp(extension.extensionName, VK_KHR_VIDEO_ENCODE_H265_EXTENSION_NAME) == 0;
                   }) != local_device_extensions_properties.end();
  response->set_supports_h265_stream(local_device_supports_h265_encode);

  return grpc::Status::OK;
}

grpc::Status VvkServerImpl::RequestFrame(grpc::ServerContext* context, const vvk::server::VvkGetFrameRequest* request,
                                         grpc::ServerWriter<vvk::server::VvkGetFrameResponse>* writer) {
  if (rdoc_api) rdoc_api->EndFrameCapture(NULL, NULL);

  VmaAllocator allocator = reinterpret_cast<VmaAllocator>(request->session_key());
  VmaAllocation buffer_allocation = reinterpret_cast<VmaAllocation>(request->frame_key());
  void* data = nullptr;
  vmaMapMemory(allocator, buffer_allocation, &data);
  VmaAllocationInfo allocation_info;
  vmaGetAllocationInfo(allocator, buffer_allocation, &allocation_info);
  uint32_t data_size = allocation_info.size;
  constexpr uint32_t kChunkSize = 128 * 1024;  // 128 KiB, randomly chosen
  uint32_t num_chunks = (data_size + kChunkSize - 1) / kChunkSize;
  spdlog::trace("Sending {} bytes in {} chunks", data_size, num_chunks);
  vvk::server::VvkGetFrameResponse response;
  response.mutable_frame_data()->resize(kChunkSize);
  for (uint32_t i = 0; i < num_chunks; ++i) {
    uint32_t chunk_size = std::min(kChunkSize, data_size - i * kChunkSize);
    std::memcpy(response.mutable_frame_data()->data(), static_cast<uint8_t*>(data) + i * kChunkSize, chunk_size);
    writer->Write(response);
  }

  vmaUnmapMemory(allocator, buffer_allocation);
  return grpc::Status::OK;
}

grpc::Status VvkServerImpl::WriteMappedMemory(grpc::ServerContext* context,
                                              const vvk::server::VvkWriteMappedMemoryRequest* request,
                                              google::protobuf::Empty* response) {
  // TODO: Check if the memory is mapped
  spdlog::info("Writing {} bytes at address {}", request->data().size(), request->address());
  memcpy(reinterpret_cast<void*>(request->address()), request->data().data(), request->data().size());
  return grpc::Status::OK;
}

}  // namespace vvk::server
