#ifndef NET_NET_DEFINE_H
#define NET_NET_DEFINE_H

#include "tt/util/platform.h"

// 网络定义，包含网络相关的头文件
#ifdef __PLATFORM_LINUX // Linux平台

#include <arpa/inet.h>
#include <epoll.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ifaddrs.h>

#elif __PLATFORM_WIN // Windows平台

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <iphlpapi.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

#elif defined(__PLATFORM_MAC) // MacOS平台

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ifaddrs.h>

#endif

#endif // NET_NET_DEFINE_H