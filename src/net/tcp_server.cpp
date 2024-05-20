#include "tt/net/tcp_server.h"

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
    _listen_socket.listen(1);
    accept();
}

void TcpServer::start() {
    _listen_socket.listen(1);
    FD_ZERO(&_listen_fd_set);
    FD_SET(_listenfd, &_listen_fd_set);
}

bool TcpServer::has_connection_request() {
    // 使用select函数，监听是否有客户端请求连接
    fd_set tmp_set = _listen_fd_set; // 创建一个副本，以防止select修改_listen_fd_set
    int ret = select(_listenfd + 1, &tmp_set, nullptr, nullptr, &_read_timeout);
    if (ret < 0) {
        return false;
    }
    if (FD_ISSET(_listenfd, &tmp_set)) {
        return true;
    }
    return false;
}

void TcpServer::accept() {
    _connfd = _listen_socket.accept(_cli_addr, _cli_addr_size);
    FD_ZERO(&_read_fd_set);         // 将read_fds清零
    FD_SET(_connfd, &_read_fd_set); // 将sockfd加入到read_fds中
}


} // namespace net