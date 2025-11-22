find_package(spdlog CONFIG REQUIRED)

add_executable(
  VirtualVulkanServer
    main.cpp
    server.h server.cpp
    function_execution.h function_execution.cpp
    implementations.h implementations.cpp
    manual_implementations.h manual_implementations.cpp
    execution_context.h
    vma_implementation.cpp
    h264_encoder.h h264_encoder.cpp
  )
target_include_directories(VirtualVulkanServer PRIVATE ../)

target_link_libraries(VirtualVulkanServer PRIVATE spdlog::spdlog vvkproto vulkan turbojpeg Vulkan::Headers VulkanMemoryAllocator VulkanUtilityHeaders)

add_custom_command(
  OUTPUT ${CMAKE_SOURCE_DIR}/shaders/rgb_to_ycrcb_2plane.comp.spv
  COMMAND glslc ${CMAKE_SOURCE_DIR}/shaders/rgb_to_ycrcb_2plane.comp -o ${CMAKE_SOURCE_DIR}/shaders/rgb_to_ycrcb_2plane.comp.spv
  DEPENDS ${CMAKE_SOURCE_DIR}/shaders/rgb_to_ycrcb_2plane.comp
)
add_custom_target(
  compile_shaders
  DEPENDS ${CMAKE_SOURCE_DIR}/shaders/rgb_to_ycrcb_2plane.comp.spv
)
add_dependencies(VirtualVulkanServer compile_shaders)