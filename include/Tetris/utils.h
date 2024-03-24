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
}


#endif //TETRIS_UTILS_H
