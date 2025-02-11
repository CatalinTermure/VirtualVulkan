#include "server.h"

#include <spdlog/spdlog.h>
#include <vulkan/vulkan.h>

#include "function_execution.h"
#include "vvk_server.pb.h"

namespace vvk::server {

grpc::Status VvkServerImpl::CallMethods(grpc::ServerContext* context,
                                        grpc::ServerReaderWriter<VvkResponse, VvkRequest>* stream) {
  VvkRequest request;
  while (stream->Read(&request)) {
    VvkResponse response;
    spdlog::info("Calling {}", request.method());
    UnpackAndExecuteFunction(request);
    response.set_result(VK_SUCCESS);
    stream->Write(response);
  }
  return grpc::Status();
}
}  // namespace vvk::server
