#ifndef VVK_LAYER_CONTEXT_MAPPED_MEMORY_H
#define VVK_LAYER_CONTEXT_MAPPED_MEMORY_H

#include <cstddef>
#include <vector>

namespace vvk {
struct MappedMemoryInfo {
  void* local_memory = nullptr;
  void* remote_memory = nullptr;
  std::size_t map_size = 0;
  std::vector<std::size_t> hashes;
};
}  // namespace vvk

#endif  // VVK_LAYER_CONTEXT_MAPPED_MEMORY_H
