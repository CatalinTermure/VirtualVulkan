#include "server.h"

#include <spdlog/spdlog.h>
#include <vulkan/vulkan.h>

#include "execution_context.h"
#include "function_execution.h"
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
  return grpc::Status();
}
}  // namespace vvk::server
