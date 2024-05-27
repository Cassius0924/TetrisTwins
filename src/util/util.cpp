#include "tt/util/util.h"

#include <termios.h>

#include <chrono>

using namespace std::chrono_literals;

namespace util {

int fps() {
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

char getch() {
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


}