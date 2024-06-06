cmake_minimum_required(VERSION 3.29)

project(TetrisTwins)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 当使用 MSVC 编译器时, 设置输入代码的编码格式为 utf-8
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/source-charset:utf-8>")

find_package(absl REQUIRED)
find_package(Protobuf REQUIRED)

set(Absl_LIBRARIES absl::log_internal_message absl::log_internal_check_op)
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/src/proto/include")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 添加子目录
add_subdirectory("src")

