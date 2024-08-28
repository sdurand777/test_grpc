
cmake_minimum_required(VERSION 3.5)
project(MyGRPCProject)

# Trouver les packages nécessaires
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)


# Vérifier si gRPC a été trouvé
if(Protobuf_FOUND)
    message(STATUS "Protobuf version: ${Protobuf_VERSION}")
else()
    message(FATAL_ERROR "Protobuf not found")
endif()



# Vérifier si gRPC a été trouvé
if(gRPC_FOUND)
    message(STATUS "gRPC version: ${gRPC_VERSION}")
else()
    message(FATAL_ERROR "gRPC not found")
endif()


# Spécifier le dossier contenant les fichiers proto
set(PROTO_FILES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/proto_files")


# Fichiers générés manuellement
set(PROTO_SRCS
    ${PROTO_FILES_DIR}/myproto.pb.cc
    ${PROTO_FILES_DIR}/myproto.grpc.pb.cc
)

set(PROTO_HDRS
    ${PROTO_FILES_DIR}/myproto.pb.h
    ${PROTO_FILES_DIR}/myproto.grpc.pb.h
)


# Ajouter les exécutables
add_executable(server server.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(server gRPC::grpc++ protobuf::libprotobuf absl::base absl::strings absl::synchronization absl::symbolize)

add_executable(client client.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(client gRPC::grpc++ protobuf::libprotobuf absl::base absl::strings absl::synchronization absl::symbolize)


# Inclure les répertoires pour trouver les fichiers générés
include_directories(${PROTO_FILES_DIR})
