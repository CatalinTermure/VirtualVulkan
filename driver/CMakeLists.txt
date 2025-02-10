find_package(spdlog CONFIG REQUIRED)

add_library(
  VirtualVulkanDriver SHARED
    driver.cpp
    function_loading.h function_loading.cpp
    functions.h functions.cpp
    mem_management.h
)

target_link_libraries(VirtualVulkanDriver PRIVATE spdlog::spdlog vvkproto)
set_target_properties(VirtualVulkanDriver PROPERTIES PREFIX "lib")
set_target_properties(VirtualVulkanDriver PROPERTIES OUTPUT_NAME "virtualvulkan")
set_target_properties(VirtualVulkanDriver PROPERTIES SUFFIX ".so")
target_link_libraries(VirtualVulkanDriver PRIVATE vulkan)

install(TARGETS VirtualVulkanDriver DESTINATION .)
install(FILES manifests/linux.json DESTINATION . RENAME virtualvulkan.json)