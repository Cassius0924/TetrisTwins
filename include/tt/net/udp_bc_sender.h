#ifndef UDP_BC_SENDER_H
#define UDP_BC_SENDER_H

#include "tt/net/socket.h"

#include <string>

namespace net {

class UdpBcSender : util::noncopyable {
public:
    explicit UdpBcSender(int port);

    ~UdpBcSender() = default;

    void send(const char *data, int size) const;

    void send(const std::string &data) const;

private:
    void _init();

private:
    int _port;
    socket _connfd;
    Socket _conn_socket;
};

} // namespace net

#endif // UDP_BC_SENDER_H
