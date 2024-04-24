#ifndef TETRIS_UTILS_H
#define TETRIS_UTILS_H

namespace utils {
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
     * 生成 [start, end] 之间的随机数
     * @param start 起始值
     * @param end 结束值
     * @return 随机数
     */
    int random_int(int min, int max);

    /**
     * 获取本地 IP 地址
     * @return 本机 IP 地址
     */
    std::string get_lan_ip_linux();
}


#endif //TETRIS_UTILS_H
