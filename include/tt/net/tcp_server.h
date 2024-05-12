#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "tt/net/communicator.h"

namespace net {

class TcpServer : public Communicator,
                  public NonCopyable {
public:
    explicit TcpServer(int port);

    ~TcpServer() override;

    /**
     * 开始监听
     */
    void start_and_wait();

private:
    void _init();

private:
    /**
     * 监听套接字
     */
    socket _listenfd;

    /**
     * 监听套接字
     */
    Socket _listen_socket;

    /**
     * 客户端地址
     */
    sockaddr_in _cli_addr;

    /**
     * 客户端地址长度
     */
    socklen_t _cli_addr_size;
};

} // namespace net

#endif // TCP_SERVER_H
