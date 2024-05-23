#ifndef TETRIS_UTIL_H
#define TETRIS_UTIL_H

#include <string>

namespace util {
    /**
     * 获取游戏帧率
     */
    int fps();

    /**
     * 无缓存获取键盘输入
     * @return 输入字符
     */
    char getch();

    /**
     * 生成 [min, max] 之间的随机数
     * @param min 起始值
     * @param max 结束值
     * @return 随机数
     */
    int random_int(int min, int max);

    /**
     * 获取本地 IP 地址
     * @return 本机 IP 地址
     */
    std::string get_lan_ip_linux();
}


#endif //TETRIS_UTIL_H
