find_package(spdlog CONFIG REQUIRED)
find_package(VulkanMemoryAllocator CONFIG REQUIRED)

add_library(
  VirtualVulkanLayer SHARED
    vma_initializer.cpp
    layer.cpp
    function_loading.h function_loading.cpp
    functions.h functions.cpp
    context.h context.cpp
)
target_include_directories(VirtualVulkanLayer PRIVATE ../)

target_link_libraries(VirtualVulkanLayer PRIVATE spdlog::spdlog vvkproto VirtualVulkanCommons GPUOpen::VulkanMemoryAllocator)
set_target_properties(VirtualVulkanLayer PROPERTIES PREFIX "lib")
set_target_properties(VirtualVulkanLayer PROPERTIES OUTPUT_NAME "virtualvulkanlayer")
set_target_properties(VirtualVulkanLayer PROPERTIES SUFFIX ".so")
target_link_libraries(VirtualVulkanLayer PRIVATE vulkan)

install(CODE "MESSAGE(\"Installing VirtualVulkan layer in ${CMAKE_INSTALL_PREFIX}\")")
install(TARGETS VirtualVulkanLayer DESTINATION .)
install(FILES manifests/linux.json DESTINATION .)