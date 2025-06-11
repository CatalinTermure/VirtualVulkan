// clang-format off
#include "layer/wsi_support.h"
// clang-format on

#include "layer/context/device.h"
#include "layer/context/instance.h"
#include "layer/functions.h"

namespace vvk {

PFN_vkVoidFunction DefaultGetInstanceProcAddr(VkInstance instance, const char* pName) {
  return GetInstanceInfo(instance).dispatch_table().GetInstanceProcAddr(instance, pName);
}
PFN_vkVoidFunction DefaultGetDeviceProcAddr(VkDevice device, const char* pName) {
  return GetDeviceInfo(device).dispatch_table().GetDeviceProcAddr(device, pName);
}

}  // namespace vvk