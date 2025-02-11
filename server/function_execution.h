#include <functional>
#include <string>
#include <unordered_map>

#include "vvk_server.pb.h"

namespace vvk::server {
void UnpackAndExecuteFunction(const vvk::server::VvkRequest &request);
}