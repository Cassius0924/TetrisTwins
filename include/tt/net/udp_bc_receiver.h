#ifndef UDP_BC_RECEIVER_H
#define UDP_BC_RECEIVER_H

#include "tt/net/socket.h"

#include <string>

namespace net {

class UdpBcReceiver : NonCopyable {
public:
    explicit UdpBcReceiver(int port);

    ~UdpBcReceiver() = default;

    void set_non_block(bool on) const;

    int recv(char *data, int size, sockaddr_in &cli_addr, socklen_t &cli_addr_size) const;

    int recv(std::string &data, int size, sockaddr_in &cli_addr, socklen_t &cli_addr_size) const;

    std::pair<std::string, int> recv(int size) const;

    std::pair<std::string, int> recv(int size, sockaddr_in &cli_addr, socklen_t &cli_addr_size) const;

private:
    void _init();

private:
    int _port;
    socket _connfd;
    Socket _conn_socket;
};

} // namespace net

#endif // UDP_BC_RECEIVER_H
