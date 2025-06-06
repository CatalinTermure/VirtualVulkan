#ifndef VVK_SERVER_MANUAL_IMPLEMENTATIONS_H
#define VVK_SERVER_MANUAL_IMPLEMENTATIONS_H

#include "execution_context.h"
#include "vvk_server.pb.h"

void UnpackAndExecuteVkCreateInstanceManual(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request,
                                            vvk::server::VvkResponse* response);

void UnpackAndExecuteVkCreateDeviceManual(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request,
                                          vvk::server::VvkResponse* response);

void UnpackAndExecuteVkEnumeratePhysicalDevicesManual(vvk::ExecutionContext& context,
                                                      const vvk::server::VvkRequest& request,
                                                      vvk::server::VvkResponse* response);

void UnpackAndExecuteSetupPresentation(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request,
                                       vvk::server::VvkResponse* response);

void UnpackAndExecuteSetupFrame(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request,
                                vvk::server::VvkResponse* response);

#endif  // VVK_SERVER_MANUAL_IMPLEMENTATIONS_H
