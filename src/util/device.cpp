#include "tt/util/device.h"

#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <sys/socket.h>

namespace util::device {

std::string get_lan_ip_linux() {
    std::string lan_ip;

    int ret_val = 0;
    ifaddrs *if_addr_struct = nullptr;
    void *tmp_addr_ptr = nullptr;
    ret_val = getifaddrs(&if_addr_struct);
    if (0 != ret_val) {
        ret_val = errno;
        return lan_ip;
    }

    const int padress_buf_len = INET_ADDRSTRLEN;
    char address_buffer[INET_ADDRSTRLEN] = {0};

    while (nullptr != if_addr_struct) {
        if (AF_INET == if_addr_struct->ifa_addr->sa_family) {
            tmp_addr_ptr = &reinterpret_cast<sockaddr_in *>(if_addr_struct->ifa_addr)->sin_addr;
            inet_ntop(AF_INET, tmp_addr_ptr, address_buffer, padress_buf_len);
            if (strstr(address_buffer, "192.168.")) {
                lan_ip = std::string(address_buffer);
                break;
            }
            memset(address_buffer, 0, padress_buf_len);
        }
        if_addr_struct = if_addr_struct->ifa_next;
    }
    return lan_ip;
}

} // namespace util::device