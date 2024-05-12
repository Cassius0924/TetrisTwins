#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "communicator.h"

namespace net {

class TcpClient : public Communicator,
                  public NonCopyable {
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
    void  connect();

    /**
     * 断开连接
     */
    void disconnect() const;

private:
    void _init();

private:
    std::string _ip;
    sockaddr_in _serv_addr;
    /**
     * 连接套接字
     */
    Socket _conn_socket;
};

} // namespace net

#endif // TCP_CLIENT_H