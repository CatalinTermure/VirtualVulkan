find_package(spdlog CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

add_executable(VirtualVulkanServer main.cpp server.h server.cpp)
target_link_libraries(VirtualVulkanServer PRIVATE spdlog::spdlog vvkproto ${Vulkan_LIBRARIES})
target_include_directories(VirtualVulkanServer PRIVATE ${Vulkan_INCLUDE_DIRS})