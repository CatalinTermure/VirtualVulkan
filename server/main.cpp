#include <absl/status/status.h>
#include <absl/strings/str_format.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <spdlog/cfg/env.h>
#include <spdlog/spdlog.h>

#include <string>

#include "server/server.h"

using grpc::Server;
using grpc::ServerBuilder;
using vvk::server::VvkServerImpl;

void RunServer(uint16_t port) {
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  VvkServerImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
}

int main(int argc, char** argv) {
  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [VvkServer] [%^%l%$] %v");
  spdlog::cfg::load_env_levels("VVK_SERVER_LOG_LEVEL");
  RunServer(50051);
  return 0;
}
