#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "tt/net/communicator.h"
#include "tt/util/noncopyable.h"

namespace net {

class TcpServer : public Communicator,
                  public util::noncopyable {
public:
    explicit TcpServer(int port);

    ~TcpServer() override;

    /**
     * 开始监听并阻塞等待客户端连接
     */
    void start_and_wait();

    /**
     * 开始监听
     */
    void start();

    /**
     * 是否有客户端请求连接
     */
    bool has_connection_request();

    /**
     * 接受客户端连接
     */
    void accept();

    /**
     * 获取客户端地址
     */
    inline std::string get_client_address() const {
        return inet_ntoa(_cli_addr.sin_addr);
    }

private:
    void _init();

private:
    /**
     * 监听套接字
     */
    Socket _listen_socket;

    /**
     * 监听套接字
     */
    socket _listenfd;

    /**
     * 客户端地址
     */
    sockaddr_in _cli_addr;

    /**
     * 客户端地址长度
     */
    socklen_t _cli_addr_size;

    /**
     * 读文件描述符集合
     */
    fd_set _listen_fd_set;
};

} // namespace net

#endif // TCP_SERVER_H
