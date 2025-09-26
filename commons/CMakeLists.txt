find_package(spdlog CONFIG REQUIRED)

add_library(
  VirtualVulkanCommons
    remote_call.h remote_call.cpp
    synchronized_bidi_stream.h
)

target_link_libraries(VirtualVulkanCommons PRIVATE spdlog::spdlog vvkproto Vulkan::Headers)