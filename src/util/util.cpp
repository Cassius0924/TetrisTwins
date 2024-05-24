#include "tt/util/util.h"

#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <termios.h>

#include <chrono>
#include <random>

using namespace std::chrono_literals;

int util::fps() {
    static int frame_count = 0; // 帧数
    static auto start_time = std::chrono::steady_clock::now();
    auto end_time = std::chrono::steady_clock::now();
    static int fps = 0;
    // 计算帧率
    frame_count++;
    if (end_time - start_time > 1s) {
        fps = frame_count;
        frame_count = 0;
        start_time = end_time;
    }
    return fps;
}

char util::getch() {
    char c;
    termios old{}, cur{};
    tcgetattr(0, &cur);
    old = cur;
    cfmakeraw(&cur);
    tcsetattr(0, 0, &cur);
    c = getchar();
    tcsetattr(0, 0, &old);
    return c;
}

int util::random_int(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

std::string util::get_lan_ip_linux() {
    std::string lan_ip;

    int ret_val = 0;
    ifaddrs *if_addr_struct = nullptr;
    void *tmp_addr_ptr = nullptr;
    ret_val = getifaddrs(&if_addr_struct);
    if (0 != ret_val) {
        ret_val = errno;
        return lan_ip;
    }

    int padress_buf_len = INET_ADDRSTRLEN;
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