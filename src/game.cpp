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
    tetro::Tetromino *cur_tetromino;
    TetroHeap tetro_heap;
//    std::unordered_map<char, ui::Color> tetro_color = {
//            {'I', ui::Color::Cyan},
//            {'J', ui::Color::Blue},
//            {'L', ui::Color::Orange},
//            {'O', ui::Color::Yellow},
//            {'S', ui::Color::Green},
//            {'T', ui::Color::Purple},
//            {'Z', ui::Color::Red},
//    };
}


void game::init() {
    // 开始键盘监听
    ctrl::start_key_listener();

    is_running = true;
    block_row = 1;
    block_col = 1;
    cur_tetromino = new game::tetro::TetroI();
    tetro_heap.heap = std::vector<std::vector<int>>(main_win->get_height() - 2,
                                                    std::vector<int>(main_win->get_width() - 2, 0));
}

void game::quit() {
    is_running = false;
}

void game::rotate() {
    cur_tetromino->rotate();
}

void game::move_left() {
    // 判断是否超出左边界
    if (block_col > 1 - cur_tetromino->get_valid_offset().left) {
        block_col -= 1;
    }
}

void game::move_right() {
    // 判断是否超出右边界
    if (block_col < main_win->get_width() - cur_tetromino->get_valid_offset().right - 1 - 1) {
        block_col += 1;
    }
}

void game::move_down() {
    // 判断是否超出下边界
    if (block_row < main_win->get_height() - cur_tetromino->get_valid_offset().bottom - 1 - 1) {
        block_row += 1;
    }

    // 判断是否碰到堆
}