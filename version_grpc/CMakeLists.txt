cmake_minimum_required(VERSION 3.5)
project(CheckGRPCVersion)

find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_executable(check_grpc_version version_grpc.cpp)
target_link_libraries(check_grpc_version gRPC::grpc++)
