#include "function_execution.h"

#include <spdlog/spdlog.h>

#include "implementations.h"

namespace vvk::server {

namespace {

const std::unordered_map<std::string, std::function<void(const vvk::server::VvkRequest&, vvk::server::VvkResponse*)>>
    g_jump_table = {
        {"vkCreateInstance", UnpackAndExecuteVkCreateInstance},
        {"vkDestroyInstance", UnpackAndExecuteVkDestroyInstance},
        {"vkEnumeratePhysicalDevices", UnpackAndExecuteVkEnumeratePhysicalDevices},
};

}  // namespace

void UnpackAndExecuteFunction(const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response) {
  auto it = g_jump_table.find(request.method());
  if (it != g_jump_table.end()) {
    it->second(request, response);
  } else {
    spdlog::error("Unknown method: {}", request.method());
  }
}
}  // namespace vvk::server