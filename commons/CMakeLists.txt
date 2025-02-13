find_package(spdlog CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

add_library(
  VirtualVulkanCommons
    remote_call.h remote_call.cpp
)

target_link_libraries(VirtualVulkanCommons PRIVATE spdlog::spdlog vvkproto)
target_include_directories(VirtualVulkanCommons PRIVATE ${Vulkan_INCLUDE_DIRS})