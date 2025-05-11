#ifndef VVK_SERVER_SERVER_H
#define VVK_SERVER_SERVER_H

#include <grpcpp/grpcpp.h>
#include <vvk_server.grpc.pb.h>

namespace vvk::server {
class VvkServerImpl final : public VvkServer::Service {
  grpc::Status CallMethods(
      grpc::ServerContext* context,
      grpc::ServerReaderWriter<vvk::server::VvkResponse, vvk::server::VvkRequest>* stream) override;

  grpc::Status GetFrameStreamingCapabilities(grpc::ServerContext* context,
                                             const vvk::server::VvkGetFrameStreamingCapabilitiesRequest* request,
                                             vvk::server::VvkGetFrameStreamingCapabilitiesResponse* response) override;

  grpc::Status RequestFrame(grpc::ServerContext* context, const vvk::server::VvkGetFrameRequest* request,
                            grpc::ServerWriter<vvk::server::VvkGetFrameResponse>* writer);

  grpc::Status WriteMappedMemory(grpc::ServerContext* context, const vvk::server::VvkWriteMappedMemoryRequest* request,
                                 google::protobuf::Empty* response) override;
};
}  // namespace vvk::server

#endif  // VVK_SERVER_SERVER_H
