#ifndef VVK_SERVER_SERVER_H
#define VVK_SERVER_SERVER_H

#include <grpcpp/grpcpp.h>
#include <vvk_server.grpc.pb.h>

namespace vvk::server {
class VvkServerImpl final : public VvkServer::Service {
  grpc::Status CallMethods(
      grpc::ServerContext* context,
      grpc::ServerReaderWriter<vvk::server::VvkResponse, vvk::server::VvkRequest>* stream) override;

  grpc::Status RequestFrames(
      grpc::ServerContext* context,
      grpc::ServerReaderWriter<vvk::server::VvkGetFrameResponse, vvk::server::VvkGetFrameRequest>* stream) override;

  grpc::Status GetFrameStreamingCapabilities(grpc::ServerContext* context,
                                             const vvk::server::VvkGetFrameStreamingCapabilitiesRequest* request,
                                             vvk::server::VvkGetFrameStreamingCapabilitiesResponse* response) override;
};
}  // namespace vvk::server

#endif  // VVK_SERVER_SERVER_H
