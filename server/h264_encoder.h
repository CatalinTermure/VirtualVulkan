#ifndef VVK_SERVER_H264_ENCODER_H
#define VVK_SERVER_H264_ENCODER_H

#include <vulkan/vulkan.h>

#include <vector>
#include <vulkan/vulkan.hpp>

#include "server/encoder.h"
#include "server/execution_context.h"

namespace vvk {

namespace {
template <typename T>
requires std::is_integral_v<T> constexpr T PadValueToMultipleOf(T value, T multiple) {
  return (value + multiple - 1) / multiple * multiple;
}
}  // namespace

class H264Encoder : public Encoder {
 public:
  H264Encoder(const vvk::ExecutionContext& execution_context, VkDevice device, uint32_t video_queue_index,
              uint32_t compute_queue_index, vk::Extent2D image_extent, std::vector<VkImage> encodable_images,
              VkFormat encodable_images_format, VkSemaphore encode_wait_semaphore);

  ~H264Encoder() override;

  VkExtent2D GetPaddedSize() const { return padded_image_extent_; }

  void WriteEncodeCommands(VkCommandBuffer command_buffer, VkImage image) override;

  std::string GetEncodedData(VkImage image) override;

  std::string GetEncodedHeader() const;

 private:
  void CreateQueryPool();
  void InitializeVideoProfile();
  void AllocateCommandBuffer();
  void InitializeVideoSession();
  void BindVideoSessionMemory();
  void AllocateDpbImages();
  void InitializeVideoSessionParameters();
  void InitializeRateControl();
  void AllocateOutputBuffer();
  void AllocateInputImage();
  void AllocateIntermediaryYuvImage();
  void CreateIntermediaryRgbImage();
  void CreateRgbToYuvComputePipeline();
  void AllocateRgbToYuvDescriptorSets();
  void InitializePictureParameters();
  void UpdatePictureParameters(uint32_t picture_index);

  const vvk::ExecutionContext& execution_context_;
  const VkuDeviceDispatchTable& dev_dispatch_;
  VkDevice device_;
  uint32_t video_queue_index_;
  VkQueue video_queue_ = VK_NULL_HANDLE;
  VkSemaphore encode_wait_semaphore_ = VK_NULL_HANDLE;
  uint32_t compute_queue_index_;
  uint32_t encoded_frame_count_ = 0;
  vk::Extent2D real_image_extent_;
  vk::Extent2D padded_image_extent_;
  std::vector<VkImage> encodable_images_;
  VkFormat encodable_images_format_;
  vk::VideoEncodeRateControlInfoKHR encode_rate_control_info_;
  vk::VideoEncodeH264RateControlInfoKHR h264_rate_control_info_;
  vk::VideoEncodeRateControlLayerInfoKHR encode_rate_control_layer_info_;
  vk::VideoEncodeH264RateControlLayerInfoKHR h264_rate_control_layer_info_;
  vk::VideoProfileListInfoKHR video_profile_list_info_;
  vk::VideoProfileInfoKHR video_profile_info_;
  vk::VideoEncodeH264ProfileInfoKHR h264_profile_info_;
  StdVideoH264SpsVuiFlags std_sps_vui_flags_;
  StdVideoH264SequenceParameterSetVui std_sps_vui_;
  StdVideoH264SpsFlags std_sps_flags_;
  StdVideoH264SequenceParameterSet std_sps_;
  StdVideoH264PpsFlags std_pps_flags_;
  StdVideoH264PictureParameterSet std_pps_;
  std::vector<StdVideoEncodeH264SliceHeaderFlags> std_slice_header_flags_;
  std::vector<StdVideoEncodeH264SliceHeader> std_slice_headers_;
  std::vector<VkVideoEncodeH264NaluSliceInfoKHR> h264_nalu_slice_infos_;
  std::vector<StdVideoEncodeH264PictureInfoFlags> std_picture_info_flags_;
  std::vector<StdVideoEncodeH264PictureInfo> std_picture_infos_;
  std::vector<StdVideoEncodeH264ReferenceListsInfo> std_reference_lists_infos_;
  std::vector<VkVideoEncodeH264PictureInfoKHR> h264_picture_infos_;

  VkQueryPool query_pool_ = VK_NULL_HANDLE;
  VkCommandPool command_pool_ = VK_NULL_HANDLE;
  VkCommandBuffer video_command_buffer_ = VK_NULL_HANDLE;
  VkVideoSessionKHR video_session_ = VK_NULL_HANDLE;
  VkVideoSessionParametersKHR video_session_parameters_ = VK_NULL_HANDLE;
  std::vector<VmaAllocation> allocations_;
  VkBuffer output_buffer_ = VK_NULL_HANDLE;
  VmaAllocation output_buffer_allocation_ = VK_NULL_HANDLE;
  VmaAllocationInfo output_buffer_allocation_info_;
  char* output_buffer_data_ = nullptr;
  std::vector<VkImage> dpb_images_;
  std::vector<VmaAllocation> dpb_allocations_;
  std::vector<VmaAllocationInfo> dpb_allocation_infos_;
  std::vector<VkImageView> dpb_image_views_;
  VkImage input_image_ = VK_NULL_HANDLE;
  VmaAllocation input_image_allocation_ = VK_NULL_HANDLE;
  VmaAllocationInfo input_image_allocation_info_;
  VkImageView input_image_view_ = VK_NULL_HANDLE;
  VkImage rgb_image_ = VK_NULL_HANDLE;
  VmaAllocation rgb_image_allocation_ = VK_NULL_HANDLE;
  VmaAllocationInfo rgb_image_allocation_info_;
  VkImageView rgb_image_view_ = VK_NULL_HANDLE;
  VkImage yuv_image_ = VK_NULL_HANDLE;
  VmaAllocation yuv_image_allocation_ = VK_NULL_HANDLE;
  VmaAllocationInfo yuv_image_allocation_info_;
  VkImageView yuv_image_y_plane_view_ = VK_NULL_HANDLE;
  VkImageView yuv_image_uv_plane_view_ = VK_NULL_HANDLE;
  VkDescriptorPool compute_descriptor_pool_ = VK_NULL_HANDLE;
  VkDescriptorSet compute_descriptor_set_;
  VkDescriptorSetLayout compute_descriptor_set_layout_ = VK_NULL_HANDLE;
  VkShaderModule rgb_to_yuv_shader_module_ = VK_NULL_HANDLE;
  VkPipelineLayout compute_pipeline_layout_ = VK_NULL_HANDLE;
  VkPipeline compute_pipeline_ = VK_NULL_HANDLE;
  VkFence encode_finished_fence_ = VK_NULL_HANDLE;
};

}  // namespace vvk

#endif  // VVK_SERVER_H264_ENCODER_H
