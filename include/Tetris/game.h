#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <unordered_map>
#include <deque>

#include "tetrominos/tetromino.h"
#include "ui.h"

namespace ui {
    class Window;
}

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
    extern std::shared_ptr<tetro::Tetromino> cur_tetromino;

    /**
     * 方块队列
     */
    extern std::deque<std::shared_ptr<tetro::Tetromino>> tetro_queue;

    /**
     * 游戏分数
     */
    extern int score;

    /**
     * 方块所在行
     */
    extern int block_row;

    /**
     * 方块所在列
     */
    extern int block_col;

    /**
     * 阴影块所在行
     */
    extern int ghost_row;

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
     * Next窗口是否需要更新
     */
    extern bool is_next_win_updated;

    /**
     * 俄罗斯方块堆
     */
    struct TetroHeap {
        /**
         * 方块堆
         */
        std::vector<std::vector<int>> heap;

        /**
         * 是否更新
         */
        bool is_updated = false;
    };

    /**
     * 俄罗斯方块堆，用于储存沉底的方块，用方块颜色表示
     */
    extern TetroHeap tetro_heap;

    /**
     * 退出游戏
     */
    void quit(int signal = 0);

    /**
     * 初始化游戏
     */
    void spg_init();

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

    /**
     * 判断是否碰到堆，如果碰到堆则返回true，并将方块加入堆中，如果没有碰到堆则返回false
     * @param tetro: 方块
     * @param row: 方块泛区左上角行坐标
     * @param col: 方块泛区左上角列坐标
     * @param next_row: 方块下一步泛区左上角行坐标
     * @param next_col: 方块下一步泛区左上角列坐标
     * @return 是否碰到堆
     */
    bool touch_heap(std::shared_ptr<tetro::Tetromino> &tetro, int row, int col, int next_row, int next_col);

    /**
     * 判断是否碰到堆
     * @param tetro: 方块
     * @param next_row: 方块泛区下一步左上角行坐标
     * @param next_col: 方块泛区下一步左上角列坐标
     * @return 是否碰到堆
     */
    bool is_touch_heap(const std::shared_ptr<tetro::Tetromino> &tetro, int next_row, int next_col);

    /**
     * 判断是否碰到堆
     * @param tetro_data: 方块数据
     * @param valid_offset: 有效坐标偏移量
     * @param next_row: 方块泛区下一步左上角行坐标
     * @param next_col: 方块泛区下一步左上角列坐标
     * @return 是否碰到堆
     */
    bool is_touch_heap(const std::vector<std::vector<int>>& tetro_data, tetro::ValidOffset valid_offset, int next_row, int next_col);

    /**
     * 生成一个随机的俄罗斯方块
     * @return 俄罗斯方块
     */
    std::shared_ptr<tetro::Tetromino> generate_tetromino();

    /**
     * 移动方块到顶部中间
     * @param tetro: 俄罗斯方块
     */
    void move_to_top_center(std::shared_ptr<tetro::Tetromino> &tetro);

    /**
     * 计算方块的阴影块位置
     * @param tetro: 方块
     * @param col: 方块泛区左上角行坐标
     * @param col: 方块泛区左上角列坐标
     * @return 阴影块泛区左上角行坐标
     */
    int cal_ghost_tetromino_row(const std::shared_ptr<tetro::Tetromino> &tetro, int row, int col);

    /**
     * 检查方块堆是否触顶
     * @param row_air: 空行
     * @return 是否触顶
     */
    bool check_touch_top(std::vector<int> row_air);
}

#endif //TETRIS_GAME_H