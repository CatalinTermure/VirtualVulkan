#include "vulkan/vk_icd.h"

namespace vvk {
PFN_vkVoidFunction GetInstanceProcAddr(VkInstance instance, const char* pName);
}  // namespace vvk