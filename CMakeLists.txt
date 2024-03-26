cmake_minimum_required(VERSION 3.23)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)

# 头文件目录
include_directories(./include/Tetris)

# 源文件目录
aux_source_directory(./src SRC_DIR)
aux_source_directory(./src/tetrominos SRC_TETROMINOS_DIR)

# 添加可执行文件
add_executable(Tetris ${SRC_DIR} ${SRC_TETROMINOS_DIR})
add_executable(Test test.cpp)

# 添加链接库
#target_link_directories(TetrisTwins PRIVATE ./lib)

install(TARGETS Tetris DESTINATION bin)
