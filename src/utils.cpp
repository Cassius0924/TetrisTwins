#include <chrono>
#include <termios.h>
#include <random>

#include "utils.h"

using namespace std::chrono_literals;

int utils::fps() {
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

char utils::getch() {
    char c;
    struct termios old, cur;
    tcgetattr(0, &cur);
    old = cur;
    cfmakeraw(&cur);
    tcsetattr(0, 0, &cur);
    c = getchar();
    tcsetattr(0, 0, &old);
    return c;
}

int utils::random_int(int start, int end) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(start, end);
    return dis(gen);
}