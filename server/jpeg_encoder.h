#ifndef VVK_SERVER_JPEG_ENCODER_H
#define VVK_SERVER_JPEG_ENCODER_H

#include <vk_mem_alloc.h>
#include <vulkan/vulkan.h>

#include <string>
#include <vulkan/vulkan.hpp>

#include "3rdparty/libjpeg-turbo/src/turbojpeg.h"
#include "server/encoder.h"
#include "server/execution_context.h"

namespace vvk {

namespace {
constexpr std::array kJpegEncodableFormats = {
    VK_FORMAT_R8G8B8A8_UNORM,
    VK_FORMAT_B8G8R8A8_UNORM,
    VK_FORMAT_R8G8B8A8_SRGB,
    VK_FORMAT_B8G8R8A8_SRGB,
};
}

class JpegEncoder : public Encoder {
 public:
  JpegEncoder(const vvk::ExecutionContext &execution_context, VkDevice device, vk::Extent2D image_extent,
              std::vector<VkImage> encodable_images, VkFormat encodable_images_format)
      : execution_context_(execution_context),
        dev_dispatch_(execution_context_.device_dispatch_table()),
        encodable_images_(std::move(encodable_images)),
        image_extent_(image_extent) {
    for (int i = 0; i < encodable_images_.size(); i++) {
      tjhandle tjpeg_instance = nullptr;
      tjpeg_instance = tj3Init(TJINIT_COMPRESS);
      if (!tjpeg_instance) {
        throw std::runtime_error(tj3GetErrorStr(tjpeg_instance));
      }
      tj3Set(tjpeg_instance, TJPARAM_QUALITY, 75);
      tj3Set(tjpeg_instance, TJPARAM_SUBSAMP, TJSAMP_444);
      tjpeg_instances_.push_back(tjpeg_instance);
    }

    // Create input buffer for encoding
    VkBufferCreateInfo buffer_create_info = {};
    buffer_create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    buffer_create_info.size = image_extent.width * image_extent.height * 4;
    buffer_create_info.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    buffer_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    VmaAllocationCreateInfo alloc_create_info = {};
    alloc_create_info.usage = VMA_MEMORY_USAGE_AUTO;
    alloc_create_info.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT | VMA_ALLOCATION_CREATE_MAPPED_BIT;
    VkResult result =
        vmaCreateBuffer(execution_context_.allocator(), &buffer_create_info, &alloc_create_info, &encode_input_buffer_,
                        &encode_input_buffer_allocation_, &encode_input_buffer_allocation_info_);
    if (result != VK_SUCCESS) {
      throw std::runtime_error("Failed to create input buffer for JPEG encoding");
    }

    encodable_images_format_ = encodable_images_format;
  }

  void WriteEncodeCommands(VkCommandBuffer command_buffer, VkImage image) override {
    // There is already a pipeline barrier in the command buffer that transitions this to TRANSFER_SRC_OPTIMAL
    dev_dispatch_.CmdCopyImageToBuffer(command_buffer, image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                                       encode_input_buffer_, 1,
                                       vk::BufferImageCopy{
                                           0,
                                           0,
                                           0,
                                           vk::ImageSubresourceLayers{vk::ImageAspectFlagBits::eColor, 0, 0, 1},
                                           vk::Offset3D{0, 0, 0},
                                           vk::Extent3D{image_extent_, 1},
                                       });
  }
  std::string GetEncodedData(VkImage image) override {
    uint32_t image_index = std::numeric_limits<uint32_t>::max();
    for (uint32_t i = 0; i < encodable_images_.size(); i++) {
      if (encodable_images_[i] == image) {
        image_index = i;
        break;
      }
    }
    if (image_index >= tjpeg_instances_.size()) {
      spdlog::error("Image index {} out of bounds for JPEG instances", image_index);
      return {};
    }
    unsigned char *data = nullptr;
    size_t data_size = 0;
    int err = tj3Compress8(tjpeg_instances_[image_index],
                           static_cast<unsigned char *>(encode_input_buffer_allocation_info_.pMappedData),
                           image_extent_.width, 0, image_extent_.height, TJPF_BGRX, &data, &data_size);
    if (err != 0) {
      spdlog::error("Failed to compress image to JPEG: {}", tj3GetErrorStr(tjpeg_instances_[image_index]));
    }
    return std::string(reinterpret_cast<char *>(data), data_size);
  }

  virtual ~JpegEncoder() {
    for (tjhandle tjpeg_instance : tjpeg_instances_) {
      tjDestroy(tjpeg_instance);
    }
    if (encode_input_buffer_) {
      vmaDestroyBuffer(execution_context_.allocator(), encode_input_buffer_, encode_input_buffer_allocation_);
      encode_input_buffer_ = VK_NULL_HANDLE;
    }
  }

 private:
  const ExecutionContext &execution_context_;
  const VkuDeviceDispatchTable &dev_dispatch_;
  vk::Extent2D image_extent_;
  VkBuffer encode_input_buffer_ = VK_NULL_HANDLE;
  VmaAllocation encode_input_buffer_allocation_ = VK_NULL_HANDLE;
  VmaAllocationInfo encode_input_buffer_allocation_info_;
  VkFormat encodable_images_format_ = VK_FORMAT_UNDEFINED;

  std::vector<tjhandle> tjpeg_instances_;
  std::vector<VkImage> encodable_images_;
};
}  // namespace vvk

#endif  // VVK_SERVER_JPEG_ENCODER_H
