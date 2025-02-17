#ifndef VVK_SERVER_FUNCTION_EXECUTION_H
#define VVK_SERVER_FUNCTION_EXECUTION_H

#include <functional>
#include <string>
#include <unordered_map>

#include "execution_context.h"
#include "vvk_server.pb.h"

namespace vvk::server {
void UnpackAndExecuteFunction(vvk::ExecutionContext &context, const vvk::server::VvkRequest &request,
                              vvk::server::VvkResponse *response);
}

#endif