#include "network/udp_bc_sender.h"

#include "sys/socket.h"
#include "unistd.h"

namespace net {

UdpBcSender::UdpBcSender(int port) : _port(port), _connfd(-1), _conn_socket(V4, UDP) {
    _init();
}

void UdpBcSender::_init() {
    _connfd = _conn_socket.fd();
    _conn_socket.set_broadcast(true);
    _conn_socket.set_reuse_addr(true);
    _conn_socket.set_reuse_port(true);
    _conn_socket.connect(_port, INADDR_BROADCAST);
}

void UdpBcSender::send(const char *data, int size) const {
    ::send(_connfd, data, size, 0);
}

void UdpBcSender::send(const std::string &data) const {
    ::send(_connfd, data.c_str(), data.size(), 0);
}

} // namespace net