#include "draw.h"
#include "game.h"
#include "control.h"

namespace game {
    bool is_running;
    int block_row;
    int block_col;
    Tetromino cur_tetromino;
}

void game::init() {
    // 开始键盘监听
    ctrl::start_key_listener();

    is_running = true;
    block_row = 2;
    block_col = draw::block_to_col(15);
    block_col = 15;
    cur_tetromino = O;
}

void game::quit() {
    is_running = false;
}

void game::rotate() {
    cur_tetromino = rotate(cur_tetromino);
}

void game::move_left() {
    block_col -= 2;
}

void game::move_right() {
    block_col += 2;
}

void game::move_down() {
    block_row += 1;
}