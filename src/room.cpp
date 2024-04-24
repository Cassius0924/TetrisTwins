#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

#include "room.h"
#include "menu.h"

namespace room {

    Room::Room(proto::RoomMessage &room_message) : id(room_message.id()), ip(room_message.ip()),
                                                   port(room_message.port()), name(room_message.name()) {}

    bool Room::operator==(const room::Room &other) const {
        return id == other.id;
    }

    std::unordered_set<Room> game_rooms;
    bool is_keep_receive_broadcast = true;
}

void room::receive_game_room_broadcast() {
}

room::UdpBroadcastReceiver::UdpBroadcastReceiver(int port) : _port(port), _sock() {
    init();
}

room::UdpBroadcastReceiver::~UdpBroadcastReceiver() {
    close(_sock);
}

void room::UdpBroadcastReceiver::init() {
    _sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (_sock < 0) {
        throw std::runtime_error("Create Socket Error");
    }

    int broadcast_enabled = 1;
    int ret = setsockopt(_sock, SOL_SOCKET, SO_BROADCAST, &broadcast_enabled, sizeof(broadcast_enabled));
    if (ret < 0) {
        throw std::runtime_error("Set SO_BROADCAST Error");
    }

    sockaddr_in bind_addr{};
    bind_addr.sin_family = AF_INET;
    bind_addr.sin_port = htons(k_PORT);
    bind_addr.sin_addr.s_addr = INADDR_ANY;

    ret = bind(_sock, reinterpret_cast<struct sockaddr *>(&bind_addr), sizeof(bind_addr));
    if (ret < 0) {
        throw std::runtime_error("Bind Address Error");
    }
}

void room::UdpBroadcastReceiver::blocking_recv_data(char *buffer) const {
    while (true) {
        sockaddr_in sender_addr{};
        socklen_t sender_addr_size = sizeof(sender_addr);
        size_t len = recvfrom(_sock, buffer, sizeof(buffer) - 1, 0,
                              reinterpret_cast<struct sockaddr *>(&sender_addr), &sender_addr_size);
        if (len < 0) {
            continue;
        }
        return;
    }
}

void room::UdpBroadcastReceiver::blocking_recv_room_message(proto::RoomMessage &room_message) const {
    char buffer[1024];
    while (true) {
        sockaddr_in sender_addr{};
        socklen_t sender_addr_size = sizeof(sender_addr);
        size_t len = recvfrom(_sock, buffer, sizeof(buffer) - 1, 0,
                              reinterpret_cast<struct sockaddr *>(&sender_addr), &sender_addr_size);
        if (len < 0) {
            continue;
        }

        room_message.ParseFromArray(buffer, len);
        return;
    }
}

bool room::UdpBroadcastReceiver::recv_room_message(proto::RoomMessage &room_message) const {
    char buffer[1024];
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(_sock, &read_fds);

    timeval timeout{};
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    // 用select函数判断是否有数据可读
    int ret = select(_sock + 1, &read_fds, nullptr, nullptr, &timeout);
    if (ret == -1 || ret == 0) {
        return false;
    } else {
        sockaddr_in sender_addr{};
        socklen_t sender_addr_size = sizeof(sender_addr);
        size_t len = recvfrom(_sock, buffer, sizeof(buffer) - 1, 0,
                              reinterpret_cast<struct sockaddr *>(&sender_addr), &sender_addr_size);
        if (len < 0) {
            return false;
        }

        room_message.ParseFromArray(buffer, len);
        return true;
    }
}

room::UdpBroadcastSender::UdpBroadcastSender(int port) : _port(port), _sock(), _broadcast_addr{}, _addr{} {
    init();
}

room::UdpBroadcastSender::~UdpBroadcastSender() {
    close(_sock);
}

void room::UdpBroadcastSender::init() {
    _sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (_sock < 0) {
        throw std::runtime_error("Create Socket Error");
    }

    int broadcast_enabled = 1;
    int ret = setsockopt(_sock, SOL_SOCKET, SO_BROADCAST, &broadcast_enabled, sizeof(broadcast_enabled));
    if (ret < 0) {
        throw std::runtime_error("Set SO_BROADCAST Error");
    }

    _broadcast_addr.sin_family = AF_INET;
    _broadcast_addr.sin_port = htons(_port);
    _broadcast_addr.sin_addr.s_addr = INADDR_BROADCAST;

    _addr = reinterpret_cast<struct sockaddr *>(&_broadcast_addr);
}

int room::UdpBroadcastSender::send_data(const char *buffer, size_t len) const{
    return sendto(_sock, buffer, len, 0, _addr, sizeof(_broadcast_addr));
}

int room::UdpBroadcastSender::send_room_message(const proto::RoomMessage &room_message) const {
    char buffer[1024];
    room_message.SerializeToArray(buffer, room_message.ByteSizeLong());
    return send_data(buffer, room_message.ByteSizeLong());
}

