#include "tt/room.h"

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>

namespace room {

Room::Room(proto::RoomMessage &room_message)
    : id(room_message.id()), ip(room_message.ip()), port(room_message.port()), name(room_message.name()) {}

bool Room::operator==(const room::Room &other) const {
    return id == other.id;
}

std::unordered_set<Room> game_rooms;
bool is_keep_receive_broadcast = true;

void receive_game_room_broadcast() {}

} // namespace room

