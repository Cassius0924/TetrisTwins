#include <iostream>

#include "ui.h"
#include "game.h"
#include "control.h"
#include "tetrominos/define.h"

namespace game {
    bool is_running;
    int block_row;
    int block_col;
    ui::Window *main_win;
    ui::Window *hold_win;
    ui::Window *status_win;
    ui::Window *next_win;
    ui::Window *info_win;
    std::unique_ptr<tetro::Tetromino> cur_tetromino;
    TetroHeap tetro_heap;
}


void game::init() {
    // 开始键盘监听
    ctrl::start_key_listener();

    is_running = true;
    block_row = 1;
    block_col = 1;
    cur_tetromino = std::make_unique<game::tetro::TetroT>();
    tetro_heap.heap = std::vector<std::vector<int>>(main_win->get_height() - 2,
                                                    std::vector<int>(main_win->get_width() - 2, 0));
    // 20 * 10
    tetro_heap.heap = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
}

void game::quit() {
    is_running = false;
}

void game::move_left() {
    // 如果没有超出左边界
    if (block_col > 1 - cur_tetromino->get_valid_offset().left &&
        !game::is_touch_heap(cur_tetromino, block_row, block_col - 1)) {
        block_col -= 1;
    }
}

void game::move_right() {
    // 如果没有超出右边界
    if (block_col < main_win->get_width() - cur_tetromino->get_valid_offset().right - 1 - 1 &&
        !game::is_touch_heap(cur_tetromino, block_row, block_col + 1)) {
        block_col += 1;
    }
}

void game::move_down() {
    // 判断是否碰到堆
    if (touch_heap(cur_tetromino, block_row, block_col, block_row + 1, block_col)) {
        return;
    }

    // 判断是否超出下边界
    if (block_row < main_win->get_height() - cur_tetromino->get_valid_offset().bottom - 1 - 1) {
        block_row += 1;
    }
}

void game::rotate() {
    cur_tetromino->rotate();
}

bool game::touch_heap(std::unique_ptr<tetro::Tetromino> &tetro, int row, int col, int next_row, int next_col) {
    // 将方块加入堆中
    if (is_touch_heap(tetro, next_row, next_col)) {
        auto voffset = tetro->get_valid_offset();

        for (int i = voffset.top; i <= voffset.bottom; i++) {
            for (int j = voffset.left; j <= voffset.right; j++) {
                if ((*tetro)[i][j] == 0) {
                    continue;
                }

                tetro_heap.heap[row - 1 + i][col - 1 + j] = (*tetro)[i][j];
            }
        }
        return true;
    }
    return false;
}

bool game::is_touch_heap(std::unique_ptr<tetro::Tetromino> &tetro, int next_row, int next_col) {
    auto voffset = tetro->get_valid_offset();
    // 判断是否碰到堆或越界
    for (int i = next_row + voffset.top - 1; i <= next_row + voffset.bottom - 1; ++i) {
        for (int j = next_col + voffset.left - 1; j <= next_col + voffset.right - 1; ++j) {
            // 是否越下界
            if (i < 0 || i >= tetro_heap.heap.size()) {
                return true;
            }
            // 是否碰到堆
            if (tetro_heap.heap[i][j] != 0 && (*tetro)[i - next_row + 1][j - next_col + 1] != 0) {
                return true;
            }
        }
    }
    return false;
}