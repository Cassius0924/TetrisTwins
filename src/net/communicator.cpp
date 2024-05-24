#include "tt/net/communicator.h"

namespace net {
Communicator::Communicator(const int port)
    : CommunicatorBase(port), _read_timeout{0, 0}, _read_fd_set{}{}

Communicator::~Communicator() {
    close(_connfd);
}

bool Communicator::is_connected() const {
    if (errno == EINTR) {
        return true;
    }
    return false;
}

int Communicator::send(const char *data, int size) {
    int len = 0;
    while (len < size) {
        int ret = ::send(_connfd, data + len, size - len, 0);
        if (ret < 0) {
            return -1;
        }
        if (ret == 0) {
            close(_connfd);
            return 0;
        }
        len += ret;
    }
    return len;
}

int Communicator::send(const std::string &data) {
    int len = 0;
    int size = data.size();
    while (len < size) {
        int ret = ::send(_connfd, data.c_str() + len, size - len, 0);
        if (ret < 0) {
            return -1;
        }
        if (ret == 0) {
            close(_connfd);
            return 0;
        }
        len += ret;
    }
    return len;
}

int Communicator::recv(char *data, int size) {
    int ret = ::recv(_connfd, data, size, 0);
    if (ret < 0) {
        return -1;
    }
    if (ret == 0) {
        close(_connfd);
        return 0;
    }
    return ret;
}

int Communicator::recv(std::string &data, int size) {
    char buf[size];
    int ret = ::recv(_connfd, buf, size, 0);
    if (ret < 0) {
        return -1;
    }
    if (ret == 0) {
        close(_connfd);
        return 0;
    }
    data = std::string(buf, ret);
    return ret;
}

std::pair<std::string, int> Communicator::recv(int size) {
    char buf[size];
    int ret = ::recv(_connfd, buf, size, 0);
    if (ret < 0) {
        return {"", ret};
    }
    if (ret == 0) {
        close(_connfd);
        return {"", 0};
    }
    return {std::string(buf, ret), ret};
}

bool Communicator::has_data_read() {
    fd_set tmp_set = _read_fd_set;
    int ret = select(_connfd + 1, &tmp_set, nullptr, nullptr, &_read_timeout);
    if (ret < 0) {
        return false;
    }
    if (FD_ISSET(_connfd, &tmp_set)) {
        return true;
    }
    return false;
}

// int Communicator::nonblock_recv(char *data, int size) {}
//
// int Communicator::nonblock_recv(std::string &data, int size) {}
//
// std::pair<std::string, int> Communicator::nonblock_recv(int size) {}

} // namespace net
