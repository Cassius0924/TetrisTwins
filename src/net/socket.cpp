#include "tt/net/socket.h"

#include <iostream>

#include "tt/util/platform.h"
#include "tt/net/net_cross_platform_api.h"

namespace net {

Socket::Socket(socket fd) : _fd(fd) {
    // 获取地址族
    sockaddr_in addr{};
    socklen_t addr_len = sizeof(addr);
    if (getsockname(_fd, reinterpret_cast<struct sockaddr *>(&addr), &addr_len) < 0) {
        std::cerr << "Error: getsockname failed" << std::endl;
        abort();
    }
    _family = addr.sin_family == AF_INET ? V4 : V6;

    // 获取套接字类型
    char type;
    socklen_t type_len = sizeof(type);
    if (getsockopt(_fd, SOL_SOCKET, SO_TYPE, &type, &type_len) < 0) {
        std::cerr << "Error: getsockopt failed" << std::endl;
        abort();
    }
    _type = type == SOCK_STREAM ? TCP : UDP;
}

Socket::Socket(AddrFamily family, SocketType type) : _family(family), _type(type) {
    _fd = ::socket(static_cast<int>(family), static_cast<int>(type), 0);
    if (_fd < 0) {
        std::cerr << "Error: create socket failed" << std::endl;
        abort();
    }
}

Socket::~Socket() {
    close();
}

void Socket::close() const {
    if (_fd >= 0) {
        cp::close(_fd);
    }
}

void Socket::set_reuse_addr(bool on) const {
    char opt = on ? 1 : 0;
    if (::setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "Error: setsockopt failed" << std::endl;
        abort();
    }
}

void Socket::set_reuse_port(bool on) const {
#if __PLATFORM_LINUX || __PLATFORM_MAC
    char opt = on ? 1 : 0;
    if (::setsockopt(_fd, SOL_SOCKET, SO_REUSEPORT , &opt, sizeof(opt)) < 0) {
        std::cerr << "Error: setsockopt failed" << std::endl;
        abort();
    }
#elif __PLATFORM_WIN
    set_reuse_addr(on);
#endif
}

void Socket::set_broadcast(bool on) const {
    if (_type == TCP) {
        std::cerr << "Error: set broadcast failed, not a UDP socket" << std::endl;
        return;
    }
    char opt = on ? 1 : 0;
    if (::setsockopt(_fd, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt)) < 0) {
        std::cerr << "Error: setsockopt failed" << std::endl;
        abort();
    }
}

void Socket::set_close_on_exec(bool on) const {
#if __PLATFORM_LINUX || __PLATFORM_MAC
    int flag = fcntl(_fd, F_GETFD, 0);
    if (flag < 0) {
        std::cerr << "Error: get socket flag failed" << std::endl;
        abort();
    }
    if (on) {
        flag |= FD_CLOEXEC;
    } else {
        flag &= ~FD_CLOEXEC;
    }
    if (fcntl(_fd, F_SETFD, flag) < 0) {
        std::cerr << "Error: set socket flag failed" << std::endl;
        abort();
    }
#elif __PLATFORM_WIN
    // Windows平台不支持
#endif
}

void Socket::bind_address(const sockaddr_in *addr) const {
    int ret = bind(_fd, reinterpret_cast<const struct sockaddr *>(addr), sizeof(*addr));
    if (ret < 0) {
        std::cerr << "Error: bind address failed" << std::endl;
        abort();
    }
}

void Socket::bind_address(int sin_port, int sin_addr) const {
    sockaddr_in serv_addr{};
    serv_addr.sin_family = static_cast<int>(_family);
    serv_addr.sin_port = htons(sin_port);
    serv_addr.sin_addr.s_addr = htonl(sin_addr);
    bind_address(&serv_addr);
}

void Socket::bind_address(int family, int port, int addr) const {
    sockaddr_in serv_addr{};
    serv_addr.sin_family = family;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = htonl(addr);
    bind_address(&serv_addr);
}

void Socket::connect(const sockaddr_in *addr) const {
    int ret = ::connect(_fd, reinterpret_cast<const struct sockaddr *>(addr), sizeof(*addr));
    if (ret < 0) {
        std::cerr << "Error: connect failed" << std::endl;
        abort();
    }
}

void Socket::connect(int port, int addr) const {
    sockaddr_in serv_addr{};
    serv_addr.sin_family = static_cast<int>(_family);
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = htonl(addr);
    connect(&serv_addr);
}

void Socket::connect(int family, int port, int addr) const {
    sockaddr_in serv_addr{};
    serv_addr.sin_family = family;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = htonl(addr);
    connect(&serv_addr);
}

void Socket::listen(int backlog) const {
    int ret = ::listen(_fd, backlog);
    if (ret < 0) {
        std::cerr << "Error: listen failed" << std::endl;
        abort();
    }
}

socket Socket::accept(sockaddr_in &addr, socklen_t &addr_size) const {
    socket connfd = ::accept(_fd, reinterpret_cast<struct sockaddr *>(&addr), &addr_size);
    if (connfd < 0) {
        std::cerr << "Error: accept failed" << std::endl;
        abort();
    }
    return connfd;
}

void Socket::set_non_block(bool on) const {
#if __PLATFORM_LINUX || __PLATFORM_MAC
    int flag = fcntl(_fd, F_GETFL, 0);
    if (flag < 0) {
        std::cerr << "Error: get socket flag failed" << std::endl;
        abort();
    }
    if (on) {
        flag |= O_NONBLOCK;
    } else {
        flag &= ~O_NONBLOCK;
    }
    if (fcntl(_fd, F_SETFL, flag) < 0) {
        std::cerr << "Error: set socket flag failed" << std::endl;
        abort();
    }
#elif __PLATFORM_WIN
    u_long mode = on ? 1 : 0;
    int flag = ioctlsocket(_fd, FIONBIO, &mode);
    if (flag != NO_ERROR) {
        std::cerr << "Error: ioctlsocket failed" << std::endl;
        abort();
    }
#endif
}


} // namespace net