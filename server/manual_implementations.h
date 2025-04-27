#ifndef VVK_SERVER_MANUAL_IMPLEMENTATIONS_H
#define VVK_SERVER_MANUAL_IMPLEMENTATIONS_H

#include "execution_context.h"
#include "vvk_server.pb.h"

void UnpackAndExecuteVkCreateInstanceManual(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request,
                                            vvk::server::VvkResponse* response);

void UnpackAndExecuteSetupPresentation(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request,
                                       vvk::server::VvkResponse* response);

#endif  // VVK_SERVER_MANUAL_IMPLEMENTATIONS_H
