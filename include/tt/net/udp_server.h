#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include "tt/net/communicator.h"
#include "tt/util/noncopyable.h"

namespace net {

class UdpServer : public Communicator,
                  public util::noncopyable {
public:
    explicit UdpServer(int port);

    ~UdpServer() override;

    /**
     * 开始监听
     */
    void start_and_wait();

private:
    void _init();
};

} // namespace net

#endif // TCP_SERVER_H
