#include "tt/net/udp_bc_receiver.h"

#include "sys/socket.h"
#include "unistd.h"

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

int UdpBcReceiver::recv(char *data, int size, sockaddr_in &cli_addr, socklen_t &cli_addr_size) const {
    int len = ::recvfrom(_connfd, data, size, 0, reinterpret_cast<struct sockaddr *>(&cli_addr), &cli_addr_size);
    return len;
}

int UdpBcReceiver::recv(std::string &data, int size, sockaddr_in &cli_addr, socklen_t &cli_addr_size) const {
    char buffer[size];
    int len = ::recvfrom(_connfd, buffer, size, 0, reinterpret_cast<struct sockaddr *>(&cli_addr), &cli_addr_size);
    data = std::string(buffer, len);
    return len;
}

std::pair<std::string, int> UdpBcReceiver::recv(int size, sockaddr_in &cli_addr, socklen_t &cli_addr_size) const {
    char buf[size];
    int len = ::recvfrom(_connfd, buf, size, 0, reinterpret_cast<struct sockaddr *>(&cli_addr), &cli_addr_size);
    return {std::string(buf, len), len};
}

} // namespace net