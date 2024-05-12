#include "network/tcp_server.h"

#include <iostream>

namespace net {

TcpServer::TcpServer(const int port)
    : Communicator(port), _listenfd(-1), _listen_socket(V4, TCP), _cli_addr{}, _cli_addr_size(sizeof(_cli_addr)) {
    _init();
}

TcpServer::~TcpServer() = default;

void TcpServer::_init() {
    _listenfd = _listen_socket.fd();
    _listen_socket.set_close_on_exec(true);
    _listen_socket.set_reuse_addr(true);
    _listen_socket.set_reuse_port(true);
    _listen_socket.bind_address(_port, INADDR_ANY);
}

void TcpServer::start_and_wait() {
    _listen_socket.listen_and_wait(1);

    _connfd = _listen_socket.accept(_cli_addr, _cli_addr_size);
    FD_ZERO(&_read_fds);         // 将read_fds清零
    FD_SET(_connfd, &_read_fds); // 将sockfd加入到read_fds中
}

} // namespace net