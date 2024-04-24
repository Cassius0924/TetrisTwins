#ifndef TETRIS_ROOM_H
#define TETRIS_ROOM_H

#include <unordered_set>
#include <netinet/in.h>

#include "proto/room.pb.h"

namespace room {
    struct Room {
        int id;
        std::string ip;
        int port;
        std::string name;

        Room(proto::RoomMessage &room_message);

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

    /**
     * UDP 广播接收器
     */
    class UdpBroadcastReceiver {
    public:
        UdpBroadcastReceiver(int port);

        ~UdpBroadcastReceiver();

    public:
        /**
         * 初始化
         */
        void init();

        /**
         * 接收广播数据
         */
        void blocking_recv_data(char *buffer) const;

        /**
         * 阻塞接收 proto 消息
         */
        void blocking_recv_room_message(proto::RoomMessage &room_message) const;

        /**
         * 非阻塞接收 proto 消息
         */
        bool recv_room_message(proto::RoomMessage &room_message) const;

    private:
        int _port;
        int _sock{};
    };

    /**
     * UDP 广播发送器
     */
    class UdpBroadcastSender {
    public:
        UdpBroadcastSender(int port);

        ~UdpBroadcastSender();

    public:
        /**
         * 初始化
         */
        void init();

        /**
         * 发送广播数据
         */
        int send_data(const char *buffer, size_t len) const;

        /**
         * 发送 proto 消息
         */
        int send_room_message(const proto::RoomMessage &room_message) const;

    private:
        int _port;
        int _sock{};
        sockaddr_in _broadcast_addr{};
        sockaddr *_addr;
    };

    /**
     * 加入游戏房间
     */
    void join_game_room(Room &room);
} // namespace room

template<>
struct std::hash<room::Room> {
    std::size_t operator()(const room::Room &room) const {
        return std::hash<int>()(room.id);
    }
};


#endif //TETRIS_ROOM_H
