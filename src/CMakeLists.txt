# 声明空的项目子库列表
set(LIBS)

add_subdirectory("net")
add_subdirectory("tetrominos")
add_subdirectory("utils")
add_subdirectory("proto")
#add_subdirectory("base")

# 头文件目录
aux_source_directory("${PROJECT_SOURCE_DIR}/src" SRC_FILES)

add_executable(TetrisTwins ${SRC_FILES})

target_include_directories(TetrisTwins PUBLIC ${INCLUDE_DIR}, ${Protobuf_INCLUDE_DIRS})

target_link_libraries(TetrisTwins PUBLIC ${Absl_LIBRARIES} ${Protobuf_LIBRARIES} ${LIBS})

set_target_properties(TetrisTwins PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
