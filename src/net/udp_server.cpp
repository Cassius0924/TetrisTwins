#include "tt/net/udp_server.h"

#include <iostream>
#include <memory>

namespace net {

UdpServer::UdpServer(const int port) : Communicator(port) {
    _init();
}

UdpServer::~UdpServer() = default;

void UdpServer::_init() {
    _connfd = _conn_socket.fd();
    _conn_socket.set_close_on_exec(true);
    _conn_socket.set_reuse_addr(true);
    _conn_socket.set_reuse_port(true);
    _conn_socket.bind_address(_port, INADDR_ANY);
}

void UdpServer::start_and_wait() {
    sockaddr_in cli_addr{};
    socklen_t cli_addr_size = sizeof(cli_addr);
    char c;
    int len = ::recvfrom(_connfd, &c, 1, 0, reinterpret_cast<struct sockaddr *>(&cli_addr), &cli_addr_size);
    if (len < 0) {
        std::cerr << "Error: recvfrom failed" << std::endl;
        abort();
    }

    _conn_socket.connect(&cli_addr);
    std::cout << "连接成功" << std::endl;

    FD_ZERO(&_read_fd_set);         // 将read_fds清零
    FD_SET(_connfd, &_read_fd_set); // 将sockfd加入到read_fds中
}

} // namespace net