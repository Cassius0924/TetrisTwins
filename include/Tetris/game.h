#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H
#include "tetrominos/tetromino.h"
#include "ui.h"

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
    extern tetro::Tetromino *cur_tetromino;
    /**
     * 方块所在行
     */
    extern int block_row;

    /**
     * 方块所在列
     */
    extern int block_col;

    /**
     * 主窗口
     */
    extern ui::Window *main_win;

    /**
     * 暂存窗口
     */
    extern ui::Window *hold_win;

    /**
     * 状态窗口
     */
    extern ui::Window *status_win;

    /**
     * 下一个方块窗口
     */
    extern ui::Window *next_win;

    /**
     * 信息窗口
     */
    extern ui::Window *info_win;

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