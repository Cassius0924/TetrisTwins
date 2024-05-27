#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include "communicator.h"
#include "tt/util/noncopyable.h"

namespace net {

class UdpClient : public Communicator,
                  public util::noncopyable {
public:
    UdpClient(const std::string &ip, int port);

    ~UdpClient() override;

    /**
     * 获取IP地址
     */
    std::string get_ip() const {
        return _ip;
    }

    /**
     * 连接服务器
     * @return 连接成功返回true，否则返回false
     */
    bool connect();

    /**
     * 断开连接
     */
    void disconnect() const;

private:
    void _init();

private:
    std::string _ip;
    sockaddr_in _serv_addr;
};

} // namespace net

#endif // TCP_CLIENT_H