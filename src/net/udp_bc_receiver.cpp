#include "tt/net/udp_bc_receiver.h"
#include "tt/net/net_define.h"

#include <iostream>
#include <vector>

namespace net {

UdpBcReceiver::UdpBcReceiver(int port) : _port(port), _connfd(-1), _conn_socket(V4, UDP) {
    _init();
}

void UdpBcReceiver::_init() {
    _connfd = _conn_socket.fd();
    _conn_socket.set_broadcast(true);
    _conn_socket.set_reuse_addr(true);
    _conn_socket.set_reuse_port(true);
    _conn_socket.bind_address(_port, INADDR_ANY);
}

void UdpBcReceiver::set_non_block(bool on) const {
    _conn_socket.set_non_block(on);
}

int UdpBcReceiver::recv(char *data, int size, sockaddr_in &cli_addr, socklen_t &cli_addr_size) const {
    int len = ::recvfrom(_connfd, data, size, 0, reinterpret_cast<struct sockaddr *>(&cli_addr), &cli_addr_size);
    return len;
}

int UdpBcReceiver::recv(std::string &data, int size, sockaddr_in &cli_addr, socklen_t &cli_addr_size) const {
    std::vector<char> buf(size);
    int len = ::recvfrom(_connfd, buf.data(), size, 0, reinterpret_cast<struct sockaddr *>(&cli_addr), &cli_addr_size);
    data = std::string(buf.data(), len);
    return len;
}

std::pair<std::string, int> UdpBcReceiver::recv(int size) const {
    std::vector<char> buf(size);
    int len = ::recvfrom(_connfd, buf.data(), size, 0, nullptr, nullptr);
    return {std::string(buf.data(), len < 0 ? 0 : len), len};
}

std::pair<std::string, int> UdpBcReceiver::recv(int size, sockaddr_in &cli_addr, socklen_t &cli_addr_size) const {
    std::vector<char> buf(size);
    int len = ::recvfrom(_connfd, buf.data(), size, 0, reinterpret_cast<struct sockaddr *>(&cli_addr), &cli_addr_size);
    return {std::string(buf.data(), len), len};
}

} // namespace net