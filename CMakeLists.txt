cmake_minimum_required(VERSION 3.10.0)
project(VirtualVulkan VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)

include(ExternalProject)
ExternalProject_Add(
    libjpeg-turbo
    PREFIX ${CMAKE_BINARY_DIR}/libjpeg-turbo
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libjpeg-turbo
    INSTALL_COMMAND cmake -E echo "Skipping install step for libjpeg-turbo."
)

add_subdirectory(Vulkan-Headers EXCLUDE_FROM_ALL)
add_subdirectory(Vulkan-Loader EXCLUDE_FROM_ALL)
add_subdirectory(Vulkan-Utility-Libraries EXCLUDE_FROM_ALL)
add_subdirectory(VulkanMemoryAllocator EXCLUDE_FROM_ALL)

add_subdirectory(proto)
add_subdirectory(commons)

option(VVK_DRIVER "Enable the Vulkan driver")
if (VVK_DRIVER)
  add_subdirectory(driver)
endif()

option(VVK_LAYER "Enable the Vulkan layer")
if (VVK_LAYER)
  add_subdirectory(layer)
endif()

add_subdirectory(server)

include(CTest)
enable_testing()
add_subdirectory(tests)


