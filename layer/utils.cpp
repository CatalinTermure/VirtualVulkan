#include "utils.h"

namespace vvk {
void RemoveStructsFromChain(VkBaseOutStructure* base_struct, VkStructureType sType) {
  VkBaseOutStructure* next_struct = base_struct->pNext;
  VkBaseOutStructure* curr_struct = base_struct;
  while (next_struct) {
    if (next_struct->sType == sType) {
      curr_struct->pNext = next_struct->pNext;
      next_struct = next_struct->pNext;
    } else {
      curr_struct = next_struct;
      next_struct = next_struct->pNext;
    }
  }
}

void AddStructToChain(VkBaseOutStructure* base_struct, VkBaseOutStructure* new_struct) {
  VkBaseOutStructure* next_struct = base_struct->pNext;
  base_struct->pNext = new_struct;
  new_struct->pNext = next_struct;
}
}  // namespace vvk
