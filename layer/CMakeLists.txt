find_package(spdlog CONFIG REQUIRED)

option(FFMPEG_DIR "Path to FFMPEG installation" "")

add_library(
  VirtualVulkanLayer SHARED
    vma_initializer.cpp
    layer.cpp
    function_loading.h function_loading.cpp
    functions.h functions.cpp
    context/device.h context/device.cpp
    context/instance.h context/instance.cpp
    context/swapchain.h context/swapchain.cpp
    context/fence_pool.h context/fence_pool.cpp
    context/mapped_memory.h context/mapped_memory.cpp
    dispatchable_object.h
    presentation/frame_stream.h presentation/frame_stream.cpp
    presentation/uncompressed_frame_stream.h presentation/uncompressed_frame_stream.cpp
    presentation/h264_frame_stream.h presentation/h264_frame_stream.cpp
)
target_include_directories(VirtualVulkanLayer PRIVATE ../)
target_include_directories(VirtualVulkanLayer PRIVATE ../Vulkan-Utility-Libraries/include)

target_link_libraries(VirtualVulkanLayer PRIVATE spdlog::spdlog vvkproto VirtualVulkanCommons)
set_target_properties(VirtualVulkanLayer PROPERTIES PREFIX "lib")
set_target_properties(VirtualVulkanLayer PROPERTIES OUTPUT_NAME "virtualvulkanlayer")
set_target_properties(VirtualVulkanLayer PROPERTIES SUFFIX ".so")
target_link_libraries(VirtualVulkanLayer PRIVATE vulkan)

target_include_directories(VirtualVulkanLayer PRIVATE ${FFMPEG_DIR}/include)
target_link_directories(VirtualVulkanLayer PRIVATE ${FFMPEG_DIR}/lib)
target_link_libraries(VirtualVulkanLayer PRIVATE avutil avcodec avformat swscale)


install(CODE "MESSAGE(\"Installing VirtualVulkan layer in ${CMAKE_INSTALL_PREFIX}\")")
install(TARGETS VirtualVulkanLayer DESTINATION .)
install(FILES manifests/linux.json DESTINATION .)