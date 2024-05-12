#include "tt/net/udp_client.h"

#include <iostream>
#include <memory>

#include "tt/net/socket.h"

namespace net {

UdpClient::UdpClient(const std::string &ip, int port)
    : Communicator(port), _ip(ip), _serv_addr{}, _conn_socket(V4, UDP) {
    _init();
}

UdpClient::~UdpClient() = default;

void UdpClient::_init() {
    _connfd = _conn_socket.fd();
    _conn_socket.set_close_on_exec(true);

    _serv_addr.sin_family = AF_INET;
    _serv_addr.sin_port = htons(_port);
    _serv_addr.sin_addr.s_addr = inet_addr(_ip.c_str());
}

bool UdpClient::connect() {
    _conn_socket.connect(&_serv_addr);
    const char *msg = "_";
    int len = ::send(_connfd, msg, strlen(msg), 0);
    if (len < 0) {
        std::cerr << "Error: send failed" << std::endl;
        return false;
    }

    return true;
}

void UdpClient::disconnect() const {
    close(_connfd);
}

} // namespace net
