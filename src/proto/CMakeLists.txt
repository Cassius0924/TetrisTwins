add_library(PROTO OBJECT)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} PROTO_SRC)

target_sources(PROTO PRIVATE ${PROTO_SRC})

message(${Protobuf_INCLUDE_DIRS})
target_include_directories(PROTO PUBLIC ${INCLUDE_DIR} ${Protobuf_INCLUDE_DIRS})

list(APPEND LIBS PROTO)
set(LIBS ${LIBS} PARENT_SCOPE)
