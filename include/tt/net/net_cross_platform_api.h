#ifndef NET_CROSS_PLATFORM_API_H
#define NET_CROSS_PLATFORM_API_H

#include "tt/net/net_define.h"

/**
 * 跨平台网络编程接口
 * Cross-platform network API
 */
namespace net::cp {

#if __PLATFORM_LINUX || __PLATFORM_MAC

inline void close(int fd) {
    ::close(fd);
}

#elif __PLATFORM_WIN

inline void close(SOCKET fd) {
    ::closesocket(fd);
}

#endif

} // namespace net::cp

#endif // NET_CROSS_PLATFORM_API_H