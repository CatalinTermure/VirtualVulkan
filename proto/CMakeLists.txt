find_library (UPB_LIBRARIES NAMES upb)
if (UPB_LIBRARIES)
    add_library(protobuf::libupb STATIC IMPORTED)
    add_executable(protobuf::protoc-gen-upb IMPORTED)
    add_executable(protobuf::protoc-gen-upbdefs IMPORTED)
    add_executable(protobuf::protoc-gen-upb_minitable IMPORTED)
endif()
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

set(PROTO_FILES vvk_server.proto vvk_types.proto vvk_presentation.proto)

add_library(vvkproto ${PROTO_FILES})
target_link_libraries(vvkproto
    PUBLIC
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)
target_include_directories(vvkproto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

if (MSVC)
    add_definitions(/bigobj)
endif()

get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET vvkproto LANGUAGE cpp)
protobuf_generate(TARGET vvkproto LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")