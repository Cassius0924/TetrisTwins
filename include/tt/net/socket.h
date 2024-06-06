#ifndef SOCKET_H
#define SOCKET_H

#include <memory>

#include "tt/net/net_define.h"
#include "tt/util/noncopyable.h"

namespace net {

#if __PLATFORM_LINUX || __PLATFORM_MAC
typedef int socket;
#elif __PLATFORM_WIN
typedef SOCKET socket;
#endif

/**
 * 地址族，IPv4：AF_INET，IPv6：AF_INET6
 */
enum class AddrFamily : std::uint8_t {
    IPV4 = AF_INET, 
    IPV6 = AF_INET6
};
constexpr AddrFamily V4 = AddrFamily::IPV4;
constexpr AddrFamily V6 = AddrFamily::IPV6;

/**
 * 套接字类型，TCP：SOCK_STREAM，UDP：SOCK_DGRAM
 */
enum class SocketType : std::uint8_t {
    TCP = SOCK_STREAM,
    UDP = SOCK_DGRAM
};
constexpr SocketType UDP = SocketType::UDP;
constexpr SocketType TCP = SocketType::TCP;

class Socket : public util::noncopyable {
public:
    /**
     * @param fd 套接字文件描述符
     */
    explicit Socket(socket fd);

    /**
     * @param family 地址族
     * @param type 套接字类型
     */
    Socket(AddrFamily family, SocketType type);

    ~Socket() override;

    /**
     * 关闭套接字
     */
    void close() const;

    /**
     * 获取套接字文件描述符
     * @return 套接字文件描述符
     */
    socket fd() const {
        return _fd;
    }

    /**
     * 获取地址族
     * @return 地址族，IPv4或IPv6
     */
    AddrFamily family() const {
        return _family;
    }

    /**
     * 获取套接字类型
     * @return 套接字类型，TCP或UDP
     */
    SocketType type() const {
        return _type;
    }

    /**
     * 设置地址复用
     * @param on true：开启，false：关闭
     */
    void set_reuse_addr(bool on) const;

    /**
     * 设置端口复用
     * @param on true：开启，false：关闭
     */
    void set_reuse_port(bool on) const;

    /**
     * 设置广播通信，仅适用于UDP
     * @param on true：开启，false：关闭
     */
    void set_broadcast(bool on) const;

    /**
     * 设置Close-on-Exec标志
     * @param on true：开启，false：关闭
     */
    void set_close_on_exec(bool on) const;

    /**
     * 绑定地址
     * @param addr 地址
     */
    void bind_address(const struct sockaddr_in *addr) const;

    /**
     * 绑定地址，family为成员变量_family
     * @param sin_port 端口
     * @param sin_addr 地址
     */
    void bind_address(int sin_port, int sin_addr) const;

    /**
     * 绑定地址
     * @param family 地址族
     * @param port 端口
     * @param addr 地址
     */
    void bind_address(int family, int port, int addr) const;

    /**
     * 连接到指定地址
     * @param addr 地址
     */
    void connect(const struct sockaddr_in *addr) const;

    /**
     * 连接到指定地址，family为成员变量_family
     * @param port 端口
     * @param addr 地址
     */
    void connect(int port, int addr) const;

    /**
     * 连接到指定地址
     * @param port 端口
     * @param addr 地址
     */
    void connect(int family, int port, int addr) const;

    /**
     * 监听连接并阻塞等待连接
     * @param backlog 最大连接数
     */
    void listen(int backlog) const;

    /**
     * 接受连接
     * @param addr 地址
     * @param addr_size 地址大小
     */
    socket accept(struct sockaddr_in &addr, socklen_t &addr_size) const;

    /**
     * 设置非阻塞
     * @param on true：开启，false：关闭
     */
    void set_non_block(bool on) const;


private:
    socket _fd;
    AddrFamily _family;
    SocketType _type;
};

typedef std::unique_ptr<Socket> SocketPtr;

}

#endif //SOCKET_H
