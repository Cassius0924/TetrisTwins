#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H
#include "tetromino.h"

/**
 * 游戏控制、状态、逻辑
 */
namespace game {
    /**
     * 游戏是否正在运行
     */
    extern bool is_running;

    /**
     * 当前方块
     */
    extern Tetromino cur_tetromino;
    /**
     * 方块所在行
     */
    extern int block_row;

    /**
     * 方块所在列
     */
    extern int block_col;

    /**
     * 退出游戏
     */
    void quit();

    /**
     * 初始化游戏
     */
    void init();


    /**
     * 左移方块
     */
    void move_left();

    /**
     * 右移方块
     */
    void move_right();

    /**
     * 下移方块
     */
    void move_down();

    /**
     * 旋转方块
     */
    void rotate();
}

#endif //TETRIS_GAME_H