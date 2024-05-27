#ifndef UTIL_DEVICE_H
#define UTIL_DEVICE_H

#include <string>

namespace util::device {

/**
 * 获取本地 IP 地址
 * @return 本机 IP 地址
 */
std::string get_lan_ip_linux();

}

#endif //UTIL_DEVICE_H
