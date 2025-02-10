find_package(spdlog CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

file(GLOB layer_tests LIST_DIRECTORIES true ./*)
foreach(test ${layer_tests})
  if(IS_DIRECTORY ${test})
    get_filename_component(short_test_name ${test} NAME)
    set(test_name "test-${short_test_name}")
    add_executable(${test_name} ${test}/main.cpp)
    target_link_libraries(${test_name} PRIVATE ${Vulkan_LIBRARIES} spdlog::spdlog)

    add_test(NAME build-${short_test_name}
      COMMAND ${CMAKE_COMMAND}
      --build "${CMAKE_BINARY_DIR}"
      --config "$<CONFIG>"
      --target ${test_name})
    set_tests_properties(build-${short_test_name} PROPERTIES FIXTURES_SETUP build-fixture-${short_test_name})

    add_test(NAME ${short_test_name}-runs COMMAND ${test_name})
    set_tests_properties(${short_test_name}-runs PROPERTIES FIXTURES_REQUIRED build-fixture-${short_test_name})
  endif()
endforeach()