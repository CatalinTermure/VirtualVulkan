find_package(spdlog CONFIG REQUIRED)
find_package(VulkanMemoryAllocator CONFIG REQUIRED)

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
    dispatchable_object.h
    presentation.h presentation.cpp
)
target_include_directories(VirtualVulkanLayer PRIVATE ../)
target_include_directories(VirtualVulkanLayer PRIVATE ../Vulkan-Utility-Libraries/include)

target_link_libraries(VirtualVulkanLayer PRIVATE spdlog::spdlog vvkproto VirtualVulkanCommons GPUOpen::VulkanMemoryAllocator)
set_target_properties(VirtualVulkanLayer PROPERTIES PREFIX "lib")
set_target_properties(VirtualVulkanLayer PROPERTIES OUTPUT_NAME "virtualvulkanlayer")
set_target_properties(VirtualVulkanLayer PROPERTIES SUFFIX ".so")
target_link_libraries(VirtualVulkanLayer PRIVATE vulkan)

install(CODE "MESSAGE(\"Installing VirtualVulkan layer in ${CMAKE_INSTALL_PREFIX}\")")
install(TARGETS VirtualVulkanLayer DESTINATION .)
install(FILES manifests/linux.json DESTINATION .)