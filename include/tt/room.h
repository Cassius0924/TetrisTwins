#ifndef TETRIS_ROOM_H
#define TETRIS_ROOM_H

#include <netinet/in.h>
#include <unordered_set>

#include "tt/proto/room.pb.h"

namespace room {
struct Room {
    int id;
    std::string ip;
    int port;
    std::string name;

    explicit Room(proto::RoomMessage &room_message);

    bool operator==(const Room &other) const;
};

constexpr int k_PORT = 9898;

/**
 * 是否保持接收广播
 */
extern bool is_keep_receive_broadcast;

/**
 * 游戏房间列表
 */
extern std::unordered_set<Room> game_rooms;

/**
 * 接收游戏房间 UDP 广播
 */
void receive_game_room_broadcast();

} // namespace room

template <>
struct std::hash<room::Room> {
    std::size_t operator()(const room::Room &room) const {
        return std::hash<int>()(room.id);
    }
};


#endif //TETRIS_ROOM_H
