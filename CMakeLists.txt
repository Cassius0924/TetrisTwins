cmake_minimum_required(VERSION 3.23)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)

# 头文件目录
include_directories(./include/Tetris)

# 源文件目录
aux_source_directory(./src cppfiles)

# 添加可执行文件
add_executable(Tetris ${cppfiles})

# 添加链接库
#target_link_directories(Tetris PRIVATE ./lib)

install(TARGETS Tetris DESTINATION bin)
