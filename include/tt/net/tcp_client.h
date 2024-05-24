#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "tt/net/communicator.h"
#include "tt/util/noncopyable.h"

namespace net {

class TcpClient : public Communicator,
                  public noncopyable {
public:
    TcpClient(const std::string &ip, int port);

    ~TcpClient() override;

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
    void connect();

    /**
     * 断开连接
     */
    void disconnect() const;

    /**
     * 获取服务器地址
     */
    inline std::string get_server_address() const {
        return inet_ntoa(_serv_addr.sin_addr);
    }

private:
    void _init();

private:
    std::string _ip;
    sockaddr_in _serv_addr;
};

} // namespace net

#endif // TCP_CLIENT_H