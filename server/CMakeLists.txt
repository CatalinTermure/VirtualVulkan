find_package(spdlog CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

add_executable(
  VirtualVulkanServer
    main.cpp
    server.h server.cpp
    function_execution.h function_execution.cpp
    implementations.h implementations.cpp
    manual_implementations.h manual_implementations.cpp
    execution_context.h
    vma_implementation.cpp
  )
target_include_directories(VirtualVulkanServer PRIVATE ../)

target_link_libraries(VirtualVulkanServer PRIVATE spdlog::spdlog vvkproto vulkan)
target_include_directories(VirtualVulkanServer PRIVATE ${Vulkan_INCLUDE_DIRS})