cmake_minimum_required(VERSION 3.29)
project(TetrisTwins)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(absl REQUIRED)
find_package(Protobuf REQUIRED)

set(Absl_LIBRARIES absl::log_internal_message absl::log_internal_check_op)
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 添加子目录
add_subdirectory("src")

add_executable(GameRoomCreateDemo game_room_create_demo.cpp ./include/tt/proto/room.pb.h ./src/proto/room.pb.cc ./src/net/packer.cpp)
target_include_directories(GameRoomCreateDemo PUBLIC ${INCLUDE_DIR} ${Absl_INCLUDE_DIR} ${Protobuf_INCLUDE_DIR})
target_link_libraries(GameRoomCreateDemo ${Absl_LIBRARIES} ${Protobuf_LIBRARIES})
set_target_properties(GameRoomCreateDemo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(GameRoomRecvDemo game_room_recv_demo.cpp ./include/tt/proto/room.pb.h ./src/proto/room.pb.cc ./src/net/packer.cpp)
target_link_libraries(GameRoomRecvDemo ${Absl_LIBRARIES} ${Protobuf_LIBRARIES})
target_include_directories(GameRoomRecvDemo PUBLIC ${INCLUDE_DIR} ${Absl_INCLUDE_DIR} ${Protobuf_INCLUDE_DIR})
set_target_properties(GameRoomRecvDemo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(Communicate communicate.cpp ./include/TetrisTwins/proto/room.pb.h ./src/proto/room.pb.cc ./src/network/packer.cpp
        ./src/network/tcp_communicator.cpp
        ./src/network/tcp_server.cpp
        ./src/network/tcp_client.cpp
)
target_link_libraries(Communicate ${Absl_LIBRARIES} ${Protobuf_LIBRARIES})
target_include_directories(Communicate PUBLIC ${INCLUDE_DIR} ${Absl_INCLUDE_DIR} ${Protobuf_INCLUDE_DIR})
set_target_properties(Communicate PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

