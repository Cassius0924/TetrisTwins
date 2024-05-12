#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "tt/net/communicator_base.h"

namespace net {

class Communicator : public CommunicatorBase {
public:
    /**
     * 是否连接成功
     */
    bool is_connected() const;

    int send(const char *data, int size) override;
    int send(const std::string &data) override;

    int recv(char *data, int size) override;
    int recv(std::string &data, int size) override;
    std::pair<std::string, int> recv(int size) override;

    bool has_data_read() override;

    int nonblock_recv(char *data, int size) override;
    int nonblock_recv(std::string &data, int size) override;
    std::pair<std::string, int> nonblock_recv(int size) override;

protected:
    Communicator(int port);
    virtual ~Communicator();

protected:
    fd_set _read_fds;
    timeval _read_timeout;
};

} // namespace net

#endif // COMMUNICATOR_H