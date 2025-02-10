#include <spdlog/spdlog.h>

#include "function_loading.h"

namespace {

#include "vulkan/vk_icd.h"

constexpr uint32_t kSupportedLoaderIcdInterfaceVersion = 7;
uint32_t g_loader_interface_version = 0;
bool g_negotiate_loader_icd_interface_called = 0;

#if defined(__GNUC__) && __GNUC__ >= 4
#define EXPORT __attribute__((visibility("default")))
#else
#define EXPORT
#endif

}  // namespace

extern "C" {

EXPORT VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetInstanceProcAddr(VkInstance instance, const char* pName) {
  if (!g_negotiate_loader_icd_interface_called) {
    g_loader_interface_version = 1;
  }
  return vvk::GetInstanceProcAddr(instance, pName);
}

EXPORT VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vk_icdGetPhysicalDeviceProcAddr(VkInstance instance,
                                                                                const char* pName) {
  return nullptr;
}

EXPORT VKAPI_ATTR VkResult VKAPI_CALL vk_icdNegotiateLoaderICDInterfaceVersion(uint32_t* pSupportedVersion) {
  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [VvkDrv] %v");

  g_negotiate_loader_icd_interface_called = true;
  g_loader_interface_version = kSupportedLoaderIcdInterfaceVersion;
  if (*pSupportedVersion > kSupportedLoaderIcdInterfaceVersion) {
    *pSupportedVersion = kSupportedLoaderIcdInterfaceVersion;
  }
  return VK_SUCCESS;
}

}  // end extern "C"
