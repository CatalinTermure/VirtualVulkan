cmake_minimum_required(VERSION 3.10.0)
project(VirtualVulkan VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)

option(VVK_DRIVER "Enable the Vulkan driver")
if (VVK_DRIVER)
  add_subdirectory(driver)
endif()

option(VVK_LAYER "Enable the Vulkan layer")
if (VVK_LAYER)
  add_subdirectory(layer)
endif()

add_subdirectory(proto)
add_subdirectory(server)

include(CTest)
enable_testing()
add_subdirectory(tests)


