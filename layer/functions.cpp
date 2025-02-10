#include "layer/functions.h"

#include <spdlog/spdlog.h>

namespace vvk {

VKAPI_ATTR VkResult VKAPI_CALL CreateInstance(const VkInstanceCreateInfo* pCreateInfo,
                                              const VkAllocationCallbacks* pAllocator, VkInstance* pInstance) {
  spdlog::debug("CreateInstance");
  return VK_SUCCESS;
}

}  // namespace vvk