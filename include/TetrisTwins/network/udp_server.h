#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include "base/noncopyable.h"
#include "communicator.h"

namespace net {

class UdpServer : public Communicator,
                  public NonCopyable {
public:
    explicit UdpServer(int port);

    ~UdpServer() override;

    /**
     * 开始监听
     */
    void start_and_wait();

private:
    void _init();

private:
    Socket _conn_socket;
};

} // namespace net

#endif // TCP_SERVER_H
