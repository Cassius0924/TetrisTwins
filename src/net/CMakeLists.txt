add_library(NETWORK OBJECT)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} NETWORK_SRC)

target_sources(NETWORK PRIVATE ${NETWORK_SRC})

target_include_directories(NETWORK PUBLIC ${INCLUDE_DIR} ${Protobuf_INCLUDE_DIRS})

list(APPEND LIBS NETWORK)
set(LIBS ${LIBS} PARENT_SCOPE)
