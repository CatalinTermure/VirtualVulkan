#ifndef VVK_SERVER_ENCODER_H
#define VVK_SERVER_ENCODER_H

#include <vulkan/vulkan_core.h>

#include <cstddef>
#include <vector>

namespace vvk {
class Encoder {
 public:
  virtual ~Encoder() = default;
  virtual void WriteEncodeCommands(VkCommandBuffer command_buffer, VkImage image) = 0;
  virtual std::vector<std::byte> GetEncodedData(VkImage image) = 0;
};
}  // namespace vvk

#endif  // VVK_SERVER_ENCODER_H
