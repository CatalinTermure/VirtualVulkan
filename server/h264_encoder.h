#ifndef VVK_SERVER_H264_ENCODER_H
#define VVK_SERVER_H264_ENCODER_H

#include <vulkan/vulkan.h>

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <vector>
#include <vulkan/vulkan.hpp>

#include "server/encoder.h"
#include "server/execution_context.h"

namespace vvk {

namespace {
template <typename T>
  requires std::is_integral_v<T>
constexpr T PadValueToMultipleOf(T value, T multiple) {
  return (value + multiple - 1) / multiple * multiple;
}
}  // namespace

class H264Encoder : public Encoder {
 public:
  H264Encoder(const vvk::ExecutionContext& execution_context, VkDevice device, uint32_t video_queue_index,
              uint32_t compute_queue_index, vk::Extent2D image_extent, std::vector<VkImage> encodable_images,
              VkFormat encodable_images_format)
      : execution_context_(execution_context),
        dev_dispatch_(execution_context.device_dispatch_table()),
        device_(device),
        video_queue_index_(video_queue_index),
        compute_queue_index_(compute_queue_index),
        real_image_extent_(image_extent),
        padded_image_extent_(vk::Extent2D{
            PadValueToMultipleOf(image_extent.width, kPictureGranularity),
            PadValueToMultipleOf(image_extent.height, kPictureGranularity),
        }),
        encodable_images_(std::move(encodable_images)),
        encodable_images_format_(encodable_images_format) {
    InitializeVideoProfile();
    CreateQueryPool();
    AllocateCommandBuffer();
    InitializeVideoSession();
    BindVideoSessionMemory();
    InitializeVideoSessionParameters();
    AllocateDpbImages();
    InitializeRateControl();
    AllocateOutputBuffer();
    AllocateIntermediaryYuvImage();
    AllocateInputImage();
    CreateViewsForEncodableImages();
    CreateRgbToYuvComputePipeline();
    AllocateRgbToYuvDescriptorSets();
  }

  ~H264Encoder() override {
    if (compute_pipeline_ != VK_NULL_HANDLE) {
      dev_dispatch_.DestroyPipeline(device_, compute_pipeline_, nullptr);
      compute_pipeline_ = VK_NULL_HANDLE;
    }
    if (compute_pipeline_layout_ != VK_NULL_HANDLE) {
      dev_dispatch_.DestroyPipelineLayout(device_, compute_pipeline_layout_, nullptr);
      compute_pipeline_layout_ = VK_NULL_HANDLE;
    }
    if (rgb_to_yuv_shader_module_ != VK_NULL_HANDLE) {
      dev_dispatch_.DestroyShaderModule(device_, rgb_to_yuv_shader_module_, nullptr);
      rgb_to_yuv_shader_module_ = VK_NULL_HANDLE;
    }
    if (compute_descriptor_set_layout_ != VK_NULL_HANDLE) {
      dev_dispatch_.DestroyDescriptorSetLayout(device_, compute_descriptor_set_layout_, nullptr);
      compute_descriptor_set_layout_ = VK_NULL_HANDLE;
    }
    if (compute_descriptor_pool_ != VK_NULL_HANDLE) {
      dev_dispatch_.DestroyDescriptorPool(device_, compute_descriptor_pool_, nullptr);
      compute_descriptor_pool_ = VK_NULL_HANDLE;
    }
    if (encodable_image_views_.size() > 0) {
      for (auto image_view : encodable_image_views_) {
        dev_dispatch_.DestroyImageView(device_, image_view, nullptr);
      }
      encodable_image_views_.clear();
    }
    if (yuv_image_ != VK_NULL_HANDLE) {
      vmaDestroyImage(execution_context_.allocator(), yuv_image_, yuv_image_allocation_);
      yuv_image_ = VK_NULL_HANDLE;
      yuv_image_allocation_ = VK_NULL_HANDLE;
    }
    if (yuv_image_y_plane_view_ != VK_NULL_HANDLE) {
      dev_dispatch_.DestroyImageView(device_, yuv_image_y_plane_view_, nullptr);
      yuv_image_y_plane_view_ = VK_NULL_HANDLE;
    }
    if (yuv_image_uv_plane_view_ != VK_NULL_HANDLE) {
      dev_dispatch_.DestroyImageView(device_, yuv_image_uv_plane_view_, nullptr);
      yuv_image_uv_plane_view_ = VK_NULL_HANDLE;
    }
    if (input_image_ != VK_NULL_HANDLE) {
      vmaDestroyImage(execution_context_.allocator(), input_image_, input_image_allocation_);
      input_image_ = VK_NULL_HANDLE;
      input_image_allocation_ = VK_NULL_HANDLE;
    }
    if (input_image_view_ != VK_NULL_HANDLE) {
      dev_dispatch_.DestroyImageView(device_, input_image_view_, nullptr);
      input_image_view_ = VK_NULL_HANDLE;
    }
    if (dpb_images_.size() > 0) {
      for (size_t i = 0; i < dpb_images_.size(); i++) {
        vmaDestroyImage(execution_context_.allocator(), dpb_images_[i], dpb_allocations_[i]);
      }
      dpb_images_.clear();
      dpb_allocations_.clear();
      dpb_allocation_infos_.clear();
    }
    if (dpb_image_views_.size() > 0) {
      for (auto image_view : dpb_image_views_) {
        dev_dispatch_.DestroyImageView(device_, image_view, nullptr);
      }
      dpb_image_views_.clear();
    }
    if (output_buffer_data_ != nullptr) {
      vmaUnmapMemory(execution_context_.allocator(), output_buffer_allocation_);
      output_buffer_data_ = nullptr;
    }
    if (output_buffer_ != VK_NULL_HANDLE) {
      vmaDestroyBuffer(execution_context_.allocator(), output_buffer_, output_buffer_allocation_);
      output_buffer_ = VK_NULL_HANDLE;
      output_buffer_allocation_ = VK_NULL_HANDLE;
    }
    if (video_session_parameters_ != VK_NULL_HANDLE) {
      dev_dispatch_.DestroyVideoSessionParametersKHR(device_, video_session_parameters_, nullptr);
      video_session_parameters_ = VK_NULL_HANDLE;
    }
    if (!allocations_.empty()) {
      for (auto& allocation : allocations_) {
        vmaFreeMemory(execution_context_.allocator(), allocation);
      }
      allocations_.clear();
    }
    if (video_session_ != VK_NULL_HANDLE) {
      dev_dispatch_.DestroyVideoSessionKHR(device_, video_session_, nullptr);
      video_session_ = VK_NULL_HANDLE;
    }
    if (command_buffer_ != VK_NULL_HANDLE) {
      dev_dispatch_.FreeCommandBuffers(device_, command_pool_, 1, &command_buffer_);
      command_buffer_ = VK_NULL_HANDLE;
    }
    if (command_pool_ != VK_NULL_HANDLE) {
      dev_dispatch_.DestroyCommandPool(device_, command_pool_, nullptr);
      command_pool_ = VK_NULL_HANDLE;
    }
    if (query_pool_ != VK_NULL_HANDLE) {
      dev_dispatch_.DestroyQueryPool(device_, query_pool_, nullptr);
      query_pool_ = VK_NULL_HANDLE;
    }
  }

  void WriteEncodeCommands(VkCommandBuffer command_buffer, VkImage image) override {
    dev_dispatch_.ResetQueryPool(device_, query_pool_, 0, 1);

    bool is_idr_frame = encoded_frame_count_ % kIdrPeriod == 0;

    std::vector<vk::VideoReferenceSlotInfoKHR> reference_slots;

    vk::VideoBeginCodingInfoKHR video_begin_coding_info = {vk::VideoBeginCodingFlagsKHR{}, video_session_,
                                                           video_session_parameters_, reference_slots,
                                                           encode_rate_control_info_};

    dev_dispatch_.CmdBeginVideoCodingKHR(command_buffer, video_begin_coding_info);
  }

  std::string GetEncodedData(VkImage image) override { return {}; }

  std::string GetEncodedHeader() const {
    vk::VideoEncodeH264SessionParametersGetInfoKHR h264_param_get_info{
        VK_TRUE,  // write std SPS
        VK_TRUE,  // write std PPS
        0,        // stdSpsId
        0,        // stdPpsId
        nullptr,
    };
    vk::VideoEncodeSessionParametersGetInfoKHR param_get_info{
        video_session_parameters_,
        h264_param_get_info,
    };
    vk::VideoEncodeH264SessionParametersFeedbackInfoKHR h264_feedback_info{VK_FALSE,  // no stdSps overrides
                                                                           VK_FALSE,  // no stdPps overrides
                                                                           nullptr};
    vk::VideoEncodeSessionParametersFeedbackInfoKHR feedback_info{
        VK_FALSE,  // no overrides
        h264_feedback_info,
    };
    size_t data_size = 0;
    dev_dispatch_.GetEncodedVideoSessionParametersKHR(device_, param_get_info, feedback_info, &data_size, nullptr);
    std::string header_data(data_size, '\0');
    dev_dispatch_.GetEncodedVideoSessionParametersKHR(device_, param_get_info, feedback_info, &data_size,
                                                      header_data.data());
    return header_data;
  }

  const vvk::ExecutionContext& execution_context_;
  const VkuDeviceDispatchTable& dev_dispatch_;
  VkDevice device_;
  uint32_t video_queue_index_;
  uint32_t compute_queue_index_;
  uint32_t encoded_frame_count_ = 0;
  vk::Extent2D real_image_extent_;
  vk::Extent2D padded_image_extent_;
  std::vector<VkImage> encodable_images_;
  VkFormat encodable_images_format_;
  std::vector<VkImageView> encodable_image_views_;
  vk::VideoEncodeRateControlInfoKHR encode_rate_control_info_;
  vk::VideoEncodeH264RateControlInfoKHR h264_rate_control_info_;
  vk::VideoEncodeRateControlLayerInfoKHR encode_rate_control_layer_info_;
  vk::VideoEncodeH264RateControlLayerInfoKHR h264_rate_control_layer_info_;
  vk::VideoProfileListInfoKHR video_profile_list_info_;
  vk::VideoProfileInfoKHR video_profile_info_;
  vk::VideoEncodeH264ProfileInfoKHR h264_profile_info_;

  VkQueryPool query_pool_ = VK_NULL_HANDLE;
  VkCommandPool command_pool_ = VK_NULL_HANDLE;
  VkCommandBuffer command_buffer_ = VK_NULL_HANDLE;
  VkVideoSessionKHR video_session_ = VK_NULL_HANDLE;
  VkVideoSessionParametersKHR video_session_parameters_ = VK_NULL_HANDLE;
  std::vector<VmaAllocation> allocations_;
  VkBuffer output_buffer_ = VK_NULL_HANDLE;
  VmaAllocation output_buffer_allocation_ = VK_NULL_HANDLE;
  char* output_buffer_data_ = nullptr;
  std::vector<VkImage> dpb_images_;
  std::vector<VmaAllocation> dpb_allocations_;
  std::vector<VmaAllocationInfo> dpb_allocation_infos_;
  std::vector<VkImageView> dpb_image_views_;
  VkImage input_image_ = VK_NULL_HANDLE;
  VmaAllocation input_image_allocation_ = VK_NULL_HANDLE;
  VmaAllocationInfo input_image_allocation_info_;
  VkImageView input_image_view_ = VK_NULL_HANDLE;
  VkImage yuv_image_ = VK_NULL_HANDLE;
  VmaAllocation yuv_image_allocation_ = VK_NULL_HANDLE;
  VmaAllocationInfo yuv_image_allocation_info_;
  VkImageView yuv_image_y_plane_view_ = VK_NULL_HANDLE;
  VkImageView yuv_image_uv_plane_view_ = VK_NULL_HANDLE;
  VkDescriptorPool compute_descriptor_pool_ = VK_NULL_HANDLE;
  std::vector<VkDescriptorSet> compute_descriptor_sets_;
  VkDescriptorSetLayout compute_descriptor_set_layout_ = VK_NULL_HANDLE;
  VkShaderModule rgb_to_yuv_shader_module_ = VK_NULL_HANDLE;
  VkPipelineLayout compute_pipeline_layout_ = VK_NULL_HANDLE;
  VkPipeline compute_pipeline_ = VK_NULL_HANDLE;

 private:
  void CreateQueryPool() {
    vk::QueryPoolVideoEncodeFeedbackCreateInfoKHR query_pool_video_encode_feedback_create_info = {
        vk::VideoEncodeFeedbackFlagBitsKHR::eBitstreamBufferOffset |
            vk::VideoEncodeFeedbackFlagBitsKHR::eBitstreamBytesWritten,
        video_profile_info_,
    };

    vk::QueryPoolCreateInfo query_pool_create_info = {
        vk::QueryPoolCreateFlags{},
        vk::QueryType::eVideoEncodeFeedbackKHR,
        1,  // Query count
        vk::QueryPipelineStatisticFlags{},
        query_pool_video_encode_feedback_create_info,
    };
    dev_dispatch_.CreateQueryPool(device_, query_pool_create_info, nullptr, &query_pool_);
  }

  void InitializeVideoProfile() {
    h264_profile_info_ = vk::VideoEncodeH264ProfileInfoKHR{
        kProfileIdc,
        nullptr,
    };
    video_profile_info_ = vk::VideoProfileInfoKHR{
        vk::VideoCodecOperationFlagBitsKHR::eEncodeH264, kChromaSubsampling, vk::VideoComponentBitDepthFlagBitsKHR::e8,
        vk::VideoComponentBitDepthFlagBitsKHR::e8,       h264_profile_info_,
    };
    video_profile_list_info_ = vk::VideoProfileListInfoKHR{video_profile_info_};
  }

  void AllocateCommandBuffer() {
    vk::CommandPoolCreateInfo command_pool_create_info = {
        vk::CommandPoolCreateFlags{},
        video_queue_index_,
    };
    dev_dispatch_.CreateCommandPool(device_, command_pool_create_info, nullptr, &command_pool_);

    vk::CommandBufferAllocateInfo command_buffer_allocate_info = {
        command_pool_,
        vk::CommandBufferLevel::ePrimary,
        1,
    };
    dev_dispatch_.AllocateCommandBuffers(device_, command_buffer_allocate_info, &command_buffer_);
  }

  void InitializeVideoSession() {
    vk::ExtensionProperties h264_std_extension_version;
    strcpy(h264_std_extension_version.extensionName, VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_EXTENSION_NAME);
    h264_std_extension_version.specVersion = VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_SPEC_VERSION;
    dev_dispatch_.CreateVideoSessionKHR(device_,
                                        vk::VideoSessionCreateInfoKHR{
                                            video_queue_index_,
                                            vk::VideoSessionCreateFlagsKHR{},
                                            &video_profile_info_,
                                            kEncodeInputImageFormat,
                                            padded_image_extent_,
                                            kDpbImageFormat,
                                            kMaxDpbSlots,
                                            kMaxActiveReferenceSlots,
                                            &h264_std_extension_version,
                                        },
                                        nullptr, &video_session_);
  }

  void BindVideoSessionMemory() {
    uint32_t video_session_memory_requirements_count = 0;
    dev_dispatch_.GetVideoSessionMemoryRequirementsKHR(device_, video_session_,
                                                       &video_session_memory_requirements_count, nullptr);
    std::vector<VkVideoSessionMemoryRequirementsKHR> video_session_memory_requirements(
        video_session_memory_requirements_count);
    for (auto& video_memory_requirement : video_session_memory_requirements) {
      video_memory_requirement.sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_MEMORY_REQUIREMENTS_KHR;
    }
    dev_dispatch_.GetVideoSessionMemoryRequirementsKHR(
        device_, video_session_, &video_session_memory_requirements_count, video_session_memory_requirements.data());
    std::vector<VkBindVideoSessionMemoryInfoKHR> bind_video_session_memory_infos;
    for (const auto& video_memory_requirement : video_session_memory_requirements) {
      VmaAllocationCreateInfo allocation_create_info = {};
      allocation_create_info.memoryTypeBits = video_memory_requirement.memoryRequirements.memoryTypeBits;

      VmaAllocation allocation;
      VmaAllocationInfo allocation_info;
      VkResult result = vmaAllocateMemory(execution_context_.allocator(), &video_memory_requirement.memoryRequirements,
                                          &allocation_create_info, &allocation, &allocation_info);
      if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to allocate memory for video session");
      }
      allocations_.push_back(allocation);

      bind_video_session_memory_infos.push_back(vk::BindVideoSessionMemoryInfoKHR{
          video_memory_requirement.memoryBindIndex,
          allocation_info.deviceMemory,
          allocation_info.offset,
          allocation_info.size,
          nullptr,
      });
    }
    dev_dispatch_.BindVideoSessionMemoryKHR(device_, video_session_,
                                            static_cast<uint32_t>(bind_video_session_memory_infos.size()),
                                            bind_video_session_memory_infos.data());
  }

  void AllocateDpbImages() {
    for (int i = 0; i < kReferencePictureCount; i++) {
      VkImage image;
      VkImageView image_view;
      VmaAllocation image_allocation;
      VmaAllocationCreateInfo allocation_create_info = {};
      VmaAllocationInfo image_allocation_info = {};
      VkResult result = vmaCreateImage(execution_context_.allocator(),
                                       vk::ImageCreateInfo{
                                           vk::ImageCreateFlags{},
                                           vk::ImageType::e2D,
                                           kDpbImageFormat,
                                           vk::Extent3D{padded_image_extent_, 1},
                                           1,  // mipLevels
                                           1,  // arrayLayers
                                           vk::SampleCountFlagBits::e1,
                                           vk::ImageTiling::eOptimal,
                                           vk::ImageUsageFlagBits::eVideoEncodeDpbKHR,
                                           vk::SharingMode::eExclusive,
                                           video_queue_index_,  // pQueueFamilyIndices
                                           vk::ImageLayout::eUndefined,
                                           video_profile_list_info_,
                                       },
                                       &allocation_create_info, &image, &image_allocation, &image_allocation_info);
      if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to create image for H264 encoding DPB");
      }
      result = dev_dispatch_.CreateImageView(device_,
                                             vk::ImageViewCreateInfo{
                                                 vk::ImageViewCreateFlags{},
                                                 image,
                                                 vk::ImageViewType::e2D,
                                                 kDpbImageFormat,
                                                 vk::ComponentMapping{},
                                                 vk::ImageSubresourceRange{
                                                     vk::ImageAspectFlagBits::eColor,
                                                     0,  // baseMipLevel
                                                     1,  // levelCount
                                                     0,  // baseArrayLayer
                                                     1,  // layerCount
                                                 },
                                             },
                                             nullptr, &image_view);
      if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to create image view for H264 encoding DPB");
      }
      dpb_images_.push_back(image);
      dpb_image_views_.push_back(image_view);
      dpb_allocations_.push_back(image_allocation);
      dpb_allocation_infos_.push_back(image_allocation_info);
    }
  }

  void InitializeVideoSessionParameters() {
    StdVideoH264SpsVuiFlags std_sps_vui_flags = {
        .aspect_ratio_info_present_flag = 0u,
        .overscan_info_present_flag = 0u,
        .overscan_appropriate_flag = 0u,
        .video_signal_type_present_flag = 0u,
        .video_full_range_flag = 0u,
        .color_description_present_flag = 0u,
        .chroma_loc_info_present_flag = 0u,
        .timing_info_present_flag = 0u,
        .fixed_frame_rate_flag = 0u,
        .bitstream_restriction_flag = 0u,
        .nal_hrd_parameters_present_flag = 0u,
        .vcl_hrd_parameters_present_flag = 0u,
    };
    StdVideoH264SequenceParameterSetVui std_sps_vui = {
        .flags = std_sps_vui_flags,
        .aspect_ratio_idc = {},
        .sar_width = 0u,
        .sar_height = 0u,
        .video_format = 0u,
        .colour_primaries = 0u,
        .transfer_characteristics = 0u,
        .matrix_coefficients = 0u,
        .num_units_in_tick = 0u,
        .time_scale = 0u,
        .max_num_reorder_frames = 0u,
        .max_dec_frame_buffering = 0u,
        .chroma_sample_loc_type_top_field = 0u,
        .chroma_sample_loc_type_bottom_field = 0u,
        .reserved1 = 0u,
        .pHrdParameters = 0u,
    };
    StdVideoH264SpsFlags std_sps_flags = {
        .constraint_set0_flag = 0u,
        .constraint_set1_flag = 0u,
        .constraint_set2_flag = 0u,
        .constraint_set3_flag = 0u,
        .constraint_set4_flag = 0u,
        .constraint_set5_flag = 0u,
        .direct_8x8_inference_flag = 0u,
        .mb_adaptive_frame_field_flag = 0u,
        .frame_mbs_only_flag = 0u,
        .delta_pic_order_always_zero_flag = 0u,
        .separate_colour_plane_flag = 0u,
        .gaps_in_frame_num_value_allowed_flag = 0u,
        .qpprime_y_zero_transform_bypass_flag = 0u,
        .frame_cropping_flag = 0u,
        .seq_scaling_matrix_present_flag = 0u,
        .vui_parameters_present_flag = 1u,
    };
    StdVideoH264SequenceParameterSet std_sps = {
        .flags = std_sps_flags,
        .profile_idc = kProfileIdc,
        .level_idc = kLevelIdc,
        .chroma_format_idc = kChromaFormatIdc,
        .seq_parameter_set_id = 0u,
        .bit_depth_luma_minus8 = 0u,
        .bit_depth_chroma_minus8 = 0u,
        .log2_max_frame_num_minus4 = 0u,
        .pic_order_cnt_type = STD_VIDEO_H264_POC_TYPE_0,
        .offset_for_non_ref_pic = 0u,
        .offset_for_top_to_bottom_field = 0u,
        .log2_max_pic_order_cnt_lsb_minus4 = 0u,
        .num_ref_frames_in_pic_order_cnt_cycle = 0u,
        .max_num_ref_frames = 1u,
        .reserved1 = 0u,
        .pic_width_in_mbs_minus1 = 0u,
        .pic_height_in_map_units_minus1 = 0u,
        .frame_crop_left_offset = 0u,
        .frame_crop_right_offset = 0u,
        .frame_crop_top_offset = 0u,
        .frame_crop_bottom_offset = 0u,
        .reserved2 = 0u,
        .pOffsetForRefFrame = 0u,
        .pScalingLists = 0u,
        .pSequenceParameterSetVui = &std_sps_vui,
    };
    StdVideoH264PpsFlags std_pps_flags = {
        .transform_8x8_mode_flag = 0u,
        .redundant_pic_cnt_present_flag = 0u,
        .constrained_intra_pred_flag = 0u,
        .deblocking_filter_control_present_flag = 0u,
        .weighted_pred_flag = 0u,
        .bottom_field_pic_order_in_frame_present_flag = 0u,
        .entropy_coding_mode_flag = 0u,
        .pic_scaling_matrix_present_flag = 0u,
    };
    StdVideoH264PictureParameterSet std_pps = {
        .flags = std_pps_flags,
        .seq_parameter_set_id = 0u,
        .pic_parameter_set_id = 0u,
        .num_ref_idx_l0_default_active_minus1 = 0u,
        .num_ref_idx_l1_default_active_minus1 = 0u,
        .weighted_bipred_idc = STD_VIDEO_H264_WEIGHTED_BIPRED_IDC_DEFAULT,
        .pic_init_qp_minus26 = 0u,
        .pic_init_qs_minus26 = 0u,
        .chroma_qp_index_offset = 0u,
        .second_chroma_qp_index_offset = 0u,
        .pScalingLists = 0u,
    };
    vk::VideoEncodeH264SessionParametersAddInfoKHR h264_parameters_add_info{std_sps, std_pps};
    dev_dispatch_.CreateVideoSessionParametersKHR(device_,
                                                  vk::VideoSessionParametersCreateInfoKHR{
                                                      vk::VideoSessionParametersCreateFlagsKHR{},
                                                      {},  // videoSessionParametersTemplate
                                                      video_session_,
                                                      vk::VideoEncodeH264SessionParametersCreateInfoKHR{
                                                          1,
                                                          1,
                                                          &h264_parameters_add_info,
                                                          nullptr,
                                                      },
                                                  },
                                                  nullptr, &video_session_parameters_);
  }

  void InitializeRateControl() {
    h264_rate_control_layer_info_ = vk::VideoEncodeH264RateControlLayerInfoKHR{
        VK_FALSE,  // no min QP
        {},
        VK_FALSE,  // no max QP
        {},
        VK_FALSE,  // no max frame size
        {},
    };
    encode_rate_control_layer_info_ = vk::VideoEncodeRateControlLayerInfoKHR{
        kAverageBitrate, kMaxBitrate, kFrameRateNumerator, kFrameRateDenominator, h264_rate_control_layer_info_,
    };
    h264_rate_control_info_ = vk::VideoEncodeH264RateControlInfoKHR{
        vk::VideoEncodeH264RateControlFlagBitsKHR::eRegularGop |
            vk::VideoEncodeH264RateControlFlagBitsKHR::eReferencePatternFlat,
        kGopFrameCount,
        kIdrPeriod,
        0,  // No B-frames, since they introduce latency due to re-ordering
        1,  // Temporal layer count
        nullptr,
    };
    encode_rate_control_info_ = vk::VideoEncodeRateControlInfoKHR{
        vk::VideoEncodeRateControlFlagsKHR{},
        vk::VideoEncodeRateControlModeFlagBitsKHR::eVbr,  // should be checked before using
        encode_rate_control_layer_info_,
        kVirtualBufferSizeInMs,
        kInitialVirtualBufferSizeInMs,
        h264_rate_control_info_,
    };

    dev_dispatch_.BeginCommandBuffer(command_buffer_, vk::CommandBufferBeginInfo{});
    dev_dispatch_.CmdBeginVideoCodingKHR(command_buffer_,
                                         vk::VideoBeginCodingInfoKHR{
                                             vk::VideoBeginCodingFlagsKHR{},
                                             video_session_,
                                             video_session_parameters_,  // VideoSessionParametersKHR
                                             {},  // Reference slots are not required just to reset the video session
                                         });
    dev_dispatch_.CmdControlVideoCodingKHR(command_buffer_, vk::VideoCodingControlInfoKHR{
                                                                vk::VideoCodingControlFlagBitsKHR::eReset,
                                                                encode_rate_control_info_,
                                                            });
    dev_dispatch_.CmdEndVideoCodingKHR(command_buffer_, vk::VideoEndCodingInfoKHR{});
  }

  void AllocateOutputBuffer() {
    vk::BufferCreateInfo buffer_create_info = {
        vk::BufferCreateFlags{},     kEncodedOutputSize, vk::BufferUsageFlagBits::eVideoEncodeDstKHR,
        vk::SharingMode::eExclusive, video_queue_index_, video_profile_list_info_,
    };
    VmaAllocationCreateInfo allocation_create_info = {};
    allocation_create_info.usage = VMA_MEMORY_USAGE_AUTO;
    allocation_create_info.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT;
    VmaAllocation output_allocation;
    VkResult result = vmaCreateBuffer(execution_context_.allocator(), buffer_create_info, &allocation_create_info,
                                      &output_buffer_, &output_buffer_allocation_, nullptr);
    if (result != VK_SUCCESS) {
      throw std::runtime_error("Failed to create output buffer for H264 encoding");
    }
    result = vmaMapMemory(execution_context_.allocator(), output_buffer_allocation_,
                          reinterpret_cast<void**>(&output_buffer_data_));
    if (result != VK_SUCCESS) {
      throw std::runtime_error("Failed to map output buffer memory for H264 encoding");
    }
  }

  void AllocateInputImage() {
    VmaAllocationCreateInfo allocation_create_info = {};
    std::array queue_family_indices = {video_queue_index_, compute_queue_index_};
    VkResult result =
        vmaCreateImage(execution_context_.allocator(),
                       vk::ImageCreateInfo{
                           vk::ImageCreateFlags{},
                           vk::ImageType::e2D,
                           kEncodeInputImageFormat,
                           vk::Extent3D{padded_image_extent_, 1},
                           1,  // mipLevels
                           1,  // arrayLayers
                           vk::SampleCountFlagBits::e1,
                           vk::ImageTiling::eOptimal,
                           vk::ImageUsageFlagBits::eVideoEncodeSrcKHR | vk::ImageUsageFlagBits::eTransferDst,
                           vk::SharingMode::eConcurrent,  // NVIDIA does not observe any performance penalties for
                                                          // concurrent usage between queues
                           queue_family_indices,
                           vk::ImageLayout::eUndefined,
                           video_profile_list_info_,
                       },
                       &allocation_create_info, &input_image_, &input_image_allocation_, &input_image_allocation_info_);
    if (result != VK_SUCCESS) {
      throw std::runtime_error("Failed to create input image for H264 encoding");
    }

    vk::ImageViewCreateInfo image_view_create_info{
        vk::ImageViewCreateFlags{},
        input_image_,
        vk::ImageViewType::e2D,
        kEncodeInputImageFormat,
        vk::ComponentMapping{},
        vk::ImageSubresourceRange{
            vk::ImageAspectFlagBits::eColor,
            0,  // baseMipLevel
            1,  // levelCount
            0,  // baseArrayLayer
            1,  // layerCount
        },
    };
    result = dev_dispatch_.CreateImageView(device_, image_view_create_info, nullptr, &input_image_view_);
    if (result != VK_SUCCESS) {
      throw std::runtime_error("Failed to create image view for H264 encoding input image");
    }
  }

  void AllocateIntermediaryYuvImage() {
    VmaAllocationCreateInfo allocation_create_info = {};
    std::array queue_family_indices = {video_queue_index_, compute_queue_index_};
    VkResult result =
        vmaCreateImage(execution_context_.allocator(),
                       vk::ImageCreateInfo{
                           vk::ImageCreateFlagBits::eMutableFormat | vk::ImageCreateFlagBits::eExtendedUsage,
                           vk::ImageType::e2D,
                           kEncodeInputImageFormat,
                           vk::Extent3D{padded_image_extent_, 1},
                           1,  // mipLevels
                           1,  // arrayLayers
                           vk::SampleCountFlagBits::e1,
                           vk::ImageTiling::eOptimal,
                           vk::ImageUsageFlagBits::eStorage | vk::ImageUsageFlagBits::eTransferSrc,
                           vk::SharingMode::eConcurrent,  // NVIDIA does not observe any performance penalties for
                                                          // concurrent usage between queues
                           queue_family_indices,
                           vk::ImageLayout::eUndefined,
                           video_profile_list_info_,
                       },
                       &allocation_create_info, &yuv_image_, &yuv_image_allocation_, &yuv_image_allocation_info_);
    if (result != VK_SUCCESS) {
      throw std::runtime_error("Failed to create intermediate image for RGB to YUV conversion");
    }

    vk::ImageViewUsageCreateInfo image_view_usage_create_info{
        vk::ImageUsageFlagBits::eStorage,
    };
    vk::ImageViewCreateInfo image_view_create_info{
        vk::ImageViewCreateFlags{},
        yuv_image_,
        vk::ImageViewType::e2D,
        kYPlaneFormat,
        vk::ComponentMapping{},
        vk::ImageSubresourceRange{
            vk::ImageAspectFlagBits::ePlane0,
            0,  // baseMipLevel
            1,  // levelCount
            0,  // baseArrayLayer
            1,  // layerCount
        },
        image_view_usage_create_info,
    };
    result = dev_dispatch_.CreateImageView(device_, image_view_create_info, nullptr, &yuv_image_y_plane_view_);
    if (result != VK_SUCCESS) {
      throw std::runtime_error("Failed to create Y plane image view for intermediary YUV image");
    }
    image_view_create_info.format = kUvPlaneFormat;
    image_view_create_info.subresourceRange.aspectMask = vk::ImageAspectFlagBits::ePlane1;
    result = dev_dispatch_.CreateImageView(device_, image_view_create_info, nullptr, &yuv_image_uv_plane_view_);
    if (result != VK_SUCCESS) {
      throw std::runtime_error("Failed to create UV plane image view for intermediary YUV image");
    }
  }

  void CreateViewsForEncodableImages() {
    for (const auto& image : encodable_images_) {
      vk::ImageViewCreateInfo image_view_create_info{
          vk::ImageViewCreateFlags{},
          image,
          vk::ImageViewType::e2D,
          vk::Format{encodable_images_format_},
          vk::ComponentMapping{},
          vk::ImageSubresourceRange{
              vk::ImageAspectFlagBits::eColor,
              0,  // baseMipLevel
              1,  // levelCount
              0,  // baseArrayLayer
              1,  // layerCount
          },
      };
      VkImageView image_view;
      VkResult result = dev_dispatch_.CreateImageView(device_, image_view_create_info, nullptr, &image_view);
      if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to create image view for encodable image");
      }
      encodable_image_views_.push_back(image_view);
    }
  }

  void CreateRgbToYuvComputePipeline() {
    std::filesystem::path shader_path = std::filesystem::current_path() / "shaders" / "rgb_to_ycrcb_2plane.comp.spv";
    std::ifstream shader_file(shader_path, std::ios::binary | std::ios::ate);
    if (!shader_file.is_open()) {
      throw std::runtime_error("Failed to open shader file: " + shader_path.string());
    }
    size_t shader_file_size = shader_file.tellg();
    shader_file.seekg(0, std::ios::beg);
    std::vector<uint32_t> shader_code(shader_file_size / sizeof(uint32_t));
    shader_file.read(reinterpret_cast<char*>(shader_code.data()), shader_file_size);
    if (!shader_file) {
      throw std::runtime_error("Failed to read shader file: " + shader_path.string());
    }
    shader_file.close();
    vk::ShaderModuleCreateInfo shader_module_create_info{
        vk::ShaderModuleCreateFlags{},
        shader_code,
    };
    dev_dispatch_.CreateShaderModule(device_, shader_module_create_info, nullptr, &rgb_to_yuv_shader_module_);

    constexpr std::array descriptor_set_bindings_ = {
        vk::DescriptorSetLayoutBinding{
            0,  // binding
            vk::DescriptorType::eStorageImage,
            1,  // descriptorCount
            vk::ShaderStageFlagBits::eCompute,
        },
        vk::DescriptorSetLayoutBinding{
            1,  // binding
            vk::DescriptorType::eStorageImage,
            1,  // descriptorCount
            vk::ShaderStageFlagBits::eCompute,
        },
        vk::DescriptorSetLayoutBinding{
            2,  // binding
            vk::DescriptorType::eStorageImage,
            1,  // descriptorCount
            vk::ShaderStageFlagBits::eCompute,
        },
    };

    dev_dispatch_.CreateDescriptorSetLayout(device_,
                                            vk::DescriptorSetLayoutCreateInfo{
                                                vk::DescriptorSetLayoutCreateFlags{},
                                                descriptor_set_bindings_,
                                            },
                                            nullptr, &compute_descriptor_set_layout_);
    {
      VkPipelineLayoutCreateInfo pipeline_layout_create_info = {
          .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
          .pNext = nullptr,
          .flags = 0,
          .setLayoutCount = 1,
          .pSetLayouts = &compute_descriptor_set_layout_,
          .pushConstantRangeCount = 0,
          .pPushConstantRanges = nullptr,
      };
      dev_dispatch_.CreatePipelineLayout(device_, &pipeline_layout_create_info, nullptr, &compute_pipeline_layout_);
    }

    dev_dispatch_.CreateComputePipelines(device_, vk::PipelineCache{}, 1,
                                         vk::ComputePipelineCreateInfo{
                                             vk::PipelineCreateFlags{},
                                             vk::PipelineShaderStageCreateInfo{
                                                 vk::PipelineShaderStageCreateFlags{},
                                                 vk::ShaderStageFlagBits::eCompute,
                                                 rgb_to_yuv_shader_module_,
                                                 "main",
                                             },
                                             compute_pipeline_layout_,
                                         },
                                         nullptr, &compute_pipeline_);
  }

  void AllocateRgbToYuvDescriptorSets() {
    vk::DescriptorPoolSize descriptor_pool_size{
        vk::DescriptorType::eStorageImage,
        static_cast<uint32_t>(encodable_images_.size()),
    };
    dev_dispatch_.CreateDescriptorPool(device_,
                                       vk::DescriptorPoolCreateInfo{
                                           vk::DescriptorPoolCreateFlags{},
                                           static_cast<uint32_t>(encodable_images_.size()),
                                           descriptor_pool_size,
                                       },
                                       nullptr, &compute_descriptor_pool_);
    compute_descriptor_sets_.resize(encodable_images_.size());
    std::vector<vk::DescriptorSetLayout> layouts(encodable_images_.size(), compute_descriptor_set_layout_);
    dev_dispatch_.AllocateDescriptorSets(device_,
                                         vk::DescriptorSetAllocateInfo{
                                             compute_descriptor_pool_,
                                             layouts,
                                         },
                                         compute_descriptor_sets_.data());
    for (int i = 0; i < encodable_images_.size(); i++) {
      vk::DescriptorImageInfo rgb_image_info{
          {},                         // sampler
          encodable_image_views_[i],  // imageView
          vk::ImageLayout::eGeneral,  // imageLayout
      };
      vk::DescriptorImageInfo y_image_info{
          {},                         // sampler
          yuv_image_y_plane_view_,    // imageView
          vk::ImageLayout::eGeneral,  // imageLayout
      };
      vk::DescriptorImageInfo uv_image_info{
          {},                         // sampler
          yuv_image_uv_plane_view_,   // imageView
          vk::ImageLayout::eGeneral,  // imageLayout
      };
      std::array descriptor_writes = {
          static_cast<VkWriteDescriptorSet>(vk::WriteDescriptorSet{
              compute_descriptor_sets_[i],
              0,  // binding
              0,  // arrayElement
              vk::DescriptorType::eStorageImage,
              rgb_image_info,
          }),
          static_cast<VkWriteDescriptorSet>(vk::WriteDescriptorSet{
              compute_descriptor_sets_[i],
              1,  // binding
              0,  // arrayElement
              vk::DescriptorType::eStorageImage,
              y_image_info,
          }),
          static_cast<VkWriteDescriptorSet>(vk::WriteDescriptorSet{
              compute_descriptor_sets_[i],
              2,  // binding
              0,  // arrayElement
              vk::DescriptorType::eStorageImage,
              uv_image_info,
          }),
      };

      dev_dispatch_.UpdateDescriptorSets(device_, static_cast<uint32_t>(descriptor_writes.size()),
                                         descriptor_writes.data(), 0, nullptr);
    }
  }

  constexpr static uint32_t kIdrPeriod = 16;
  constexpr static uint32_t kGopFrameCount = 16;
  constexpr static uint32_t kMaxDpbSlots = 16;
  constexpr static uint32_t kMaxActiveReferenceSlots = 16;
  constexpr static uint32_t kPictureGranularity = 16;
  constexpr static uint32_t kReferencePictureCount = 2;
  constexpr static uint32_t kVirtualBufferSizeInMs = 200;
  constexpr static uint32_t kInitialVirtualBufferSizeInMs = 100;
  constexpr static uint32_t kAverageBitrate = 5'000'000;            // 5 Mbps
  constexpr static uint32_t kMaxBitrate = 20'000'000;               // 20 Mbps
  constexpr static uint32_t kFrameRateNumerator = 30;               // 30 fps
  constexpr static uint32_t kFrameRateDenominator = 1;              // 30 fps
  constexpr static uint32_t kEncodedOutputSize = 10 * 1024 * 1024;  // 10 MB for encoded output
  constexpr static StdVideoH264ProfileIdc kProfileIdc = STD_VIDEO_H264_PROFILE_IDC_MAIN;
  constexpr static StdVideoH264LevelIdc kLevelIdc = STD_VIDEO_H264_LEVEL_IDC_4_1;
  constexpr static vk::VideoChromaSubsamplingFlagsKHR kChromaSubsampling = vk::VideoChromaSubsamplingFlagBitsKHR::e420;
  constexpr static StdVideoH264ChromaFormatIdc kChromaFormatIdc = STD_VIDEO_H264_CHROMA_FORMAT_IDC_420;
  constexpr static vk::Format kDpbImageFormat = vk::Format::eG8B8R82Plane420Unorm;
  constexpr static vk::Format kEncodeInputImageFormat = vk::Format::eG8B8R82Plane420Unorm;
  constexpr static vk::Format kYPlaneFormat = vk::Format::eR8Unorm;
  constexpr static vk::Format kUvPlaneFormat = vk::Format::eR8G8Unorm;
};

}  // namespace vvk

#endif  // VVK_SERVER_H264_ENCODER_H
