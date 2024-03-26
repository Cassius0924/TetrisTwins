#include "draw.h"
#include "game.h"
#include "control.h"
#include "tetrominos/define.h"

namespace game {
    bool is_running;
    int block_row;
    int block_col;
    tetro::Tetromino *cur_tetromino;
}

void game::init() {
    // 开始键盘监听
    ctrl::start_key_listener();

    is_running = true;
    block_row = 2;
    block_col = 11;
    cur_tetromino = new game::tetro::TetroZ();
}

void game::quit() {
    is_running = false;
}

void game::rotate() {
    cur_tetromino->rotate();
}

void game::move_left() {
    block_col -= 1;
}

void game::move_right() {
    block_col += 1;
}

void game::move_down() {
    block_row += 1;
}