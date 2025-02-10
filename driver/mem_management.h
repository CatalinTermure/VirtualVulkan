#include <vulkan/vk_icd.h>

#include <cstddef>

namespace vvk {

template <typename T>
T* AllocateVkHandle() {
  static_assert(sizeof(T) >= sizeof(VK_LOADER_DATA));
  auto handle = new T();
  set_loader_magic_value(handle);
  return handle;
}

}  // namespace vvk