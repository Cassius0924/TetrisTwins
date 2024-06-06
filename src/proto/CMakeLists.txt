add_library(PROTO OBJECT)

# 自动protoc，生成pb.cc和pb.h
FILE(GLOB PROTO_FILE "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
set(PROTO_GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/include/tt/proto")

set(PROTO_SRC "")
set(PROTO_HDR "")
foreach(FIL ${PROTO_FILE})
    get_filename_component(FIL_WE ${FIL} NAME_WE)
    add_custom_command(
        OUTPUT
            "${PROTO_GENERATED_DIR}/${FIL_WE}.pb.cc"
            "${PROTO_GENERATED_DIR}/${FIL_WE}.pb.h"
        COMMAND ${Protobuf_PROTOC_EXECUTABLE}
        ARGS
            --cpp_out ${PROTO_GENERATED_DIR}
            -I ${CMAKE_CURRENT_SOURCE_DIR}
            ${FIL}
        DEPENDS ${FIL}
        COMMENT "Running C++ protocol buffer compiler on ${FIL}"
        VERBATIM
    )
    list(APPEND PROTO_SRC "${PROTO_GENERATED_DIR}/${FIL_WE}.pb.cc")
    list(APPEND PROTO_HDR "${PROTO_GENERATED_DIR}/${FIL_WE}.pb.h")
endforeach()
#打印Protobuf_PROTOC_EXECUTABLE
#message(STATUS "Protobuf_PROTOC_EXECUTABLE: ${Protobuf_PROTOC_EXECUTABLE}")

target_sources(PROTO PRIVATE ${PROTO_SRC} ${PROTO_HDR})

target_include_directories(PROTO PUBLIC ${INCLUDE_DIR} ${Protobuf_INCLUDE_DIRS})

list(APPEND LIBS PROTO)
set(LIBS ${LIBS} PARENT_SCOPE)

