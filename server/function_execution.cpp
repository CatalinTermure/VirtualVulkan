#include "function_execution.h"

#include <spdlog/spdlog.h>

#include "implementations.h"

namespace vvk::server {

namespace {

const std::unordered_map<std::string, std::function<void(const vvk::server::VvkRequest&)>> g_jump_table = {
    {"vkCreateInstance", UnpackAndExecuteVkCreateInstance},
};

}  // namespace

void UnpackAndExecuteFunction(const vvk::server::VvkRequest& request) {
  auto it = g_jump_table.find(request.method());
  if (it != g_jump_table.end()) {
    it->second(request);
  } else {
    spdlog::error("Unknown method: {}", request.method());
  }
}
}  // namespace vvk::server