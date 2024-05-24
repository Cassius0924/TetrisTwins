#include "tt/net/tcp_client.h"

#include <iostream>

namespace net {

TcpClient::TcpClient(const std::string &ip, int port) : Communicator(port), _ip(ip), _serv_addr{} {
    _init();
}

TcpClient::~TcpClient() = default;

void TcpClient::_init() {
    _connfd = _conn_socket.fd();
    _conn_socket.set_close_on_exec(true);

    _serv_addr.sin_family = AF_INET;
    _serv_addr.sin_port = htons(_port);
    _serv_addr.sin_addr.s_addr = inet_addr(_ip.c_str());
}

void TcpClient::connect() {
    _conn_socket.connect(&_serv_addr);

    FD_ZERO(&_read_fd_set);
    FD_SET(_connfd, &_read_fd_set);
}

void TcpClient::disconnect() const {
    close(_connfd);
}

} // namespace net
