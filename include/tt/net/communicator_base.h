#ifndef COMMUNICATOR_BASE_H
#define COMMUNICATOR_BASE_H

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <string>

#include "tt/net/socket.h"

namespace net {

class CommunicatorBase {
public:
    explicit CommunicatorBase(const int port) : _port(port), _connfd(-1), _conn_socket(V4, TCP) {}

    virtual ~CommunicatorBase() = default;

    /**
     * 获取端口号
     * @return 端口号
     */
    inline int get_port() const {
        return _port;
    }

    /**
     * 阻塞式发送数据
     * @param data 数据
     * @param size 数据大小
     * @return 发送的字节数
     */
    virtual int send(const char *data, int size) = 0;

    /**
     * 阻塞式发送数据
     * @param data 数据
     * @return 发送的字节数
     */
    virtual int send(const std::string &data) = 0;

    /**
     * 阻塞式接收数据
     * @param data 数据
     * @param size 数据大小
     * @return 接收的字节数
     */
    virtual int recv(char *data, int size) = 0;

    /**
     * 阻塞式接收数据
     * @param data 数据
     * @param size 数据大小
     * @return 接收的字节数
     */
    virtual int recv(std::string &data, int size) = 0;

    /**
     * 阻塞式接收数据
     * @param size 数据大小
     * @return 接收的数据和字节数
     */
    virtual std::pair<std::string, int> recv(int size) = 0;

    /**
     * 是否有数据可读
     * @return bool值，有数据返回true，否则返回false
     */
    virtual bool has_data_read() = 0;

    // /**
    //  * 非阻塞式接收数据
    //  * @param data 数据
    //  * @param size 数据大小
    //  * @return 接收的字节数
    //  */
    // virtual int nonblock_recv(char *data, int size) = 0;
    //
    // /**
    //  * 非阻塞式接收数据
    //  * @param data 数据
    //  * @param size 数据大小
    //  * @return 接收的字节数
    //  */
    // virtual int nonblock_recv(std::string &data, int size) = 0;
    //
    // /**
    //  * 非阻塞式接收数据
    //  * @param size 数据大小
    //  * @return 接收的数据和字节数
    //  */
    // virtual std::pair<std::string, int> nonblock_recv(int size) = 0;

protected:
    /**
     * 通信端口
     */
    int _port;

    /**
    * 连接套接字
    */
    Socket _conn_socket;

    /**
     * 连接套接字描述符
     */
    socket _connfd;
};

} // namespace net

#endif // COMMUNICATOR_BASE_H