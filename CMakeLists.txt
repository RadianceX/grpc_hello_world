cmake_minimum_required(VERSION 3.24)
project(hello-world-grpc VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(LIB_TARGET ${PROJECT_NAME}-lib)
set(SERVER_TARGET ${PROJECT_NAME}-server)
set(CLIENT_TARGET ${PROJECT_NAME}-client)

# Find Protobuf and gRPC
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

# Create library target
set(PROTOC_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(PROTO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/helloworld.proto")
make_directory(${PROTOC_OUTPUT_DIR})

add_library(${LIB_TARGET} OBJECT "${PROTO_FILES}")
target_link_libraries(${LIB_TARGET} PUBLIC protobuf::libprotobuf gRPC::grpc++)
target_include_directories(${LIB_TARGET} PUBLIC "${PROTOC_OUTPUT_DIR}")

protobuf_generate(
    TARGET "${LIB_TARGET}"
    PROTOS "${PROTO_FILES}"
    PROTOC_OUT_DIR "${PROTOC_OUTPUT_DIR}"
)

protobuf_generate(
    TARGET "${LIB_TARGET}"
    LANGUAGE "grpc"
    GENERATE_EXTENSIONS ".grpc.pb.h" ".grpc.pb.cc"
    PLUGIN "protoc-gen-grpc=\$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
    PROTOS "${PROTO_FILES}"
    PROTOC_OUT_DIR "${PROTOC_OUTPUT_DIR}"
)

# Create Server
add_executable(${SERVER_TARGET} server.cpp)
target_link_libraries(${SERVER_TARGET} PRIVATE ${LIB_TARGET})

# Create Client
add_executable(${CLIENT_TARGET} client.cpp)
target_link_libraries(${CLIENT_TARGET} PRIVATE ${LIB_TARGET})
