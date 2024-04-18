#include <iostream>

#include "ui.h"
#include "game.h"
#include "control.h"
#include "tetrominos/define.h"
#include "utils.h"
#include "remove.h"

namespace game {
    bool is_running;
    int block_row;
    int block_col;
    int ghost_row;
    ui::Window *main_win;
    ui::Window *hold_win;
    ui::Window *status_win;
    ui::Window *next_win;
    ui::Window *info_win;
    std::shared_ptr<tetro::Tetromino> cur_tetromino;
    std::deque<std::shared_ptr<tetro::Tetromino>> tetro_queue(5);
    int score;
    TetroHeap tetro_heap;
    bool is_next_win_updated;
}

void game::init() {
    // 开始键盘监听
    ctrl::start_key_listener();

    is_running = true;

    tetro_heap.heap = std::vector<std::vector<int>>(main_win->get_inner_height(),
                                                    std::vector<int>(main_win->get_inner_width(), 0));
    score = 0;

    // 生成一个随机的俄罗斯方块
    for (auto &tetro: tetro_queue) {
        tetro = generate_tetromino();
    }
    cur_tetromino = generate_tetromino();
    move_to_top_center(cur_tetromino);

    full_air_count = main_win->get_inner_width();
    row_air = std::vector<int>(main_win->get_height() - 2, full_air_count);

    is_next_win_updated = true;

    // 创建方块重力
    ctrl::start_gravity_thread();
}

void game::quit(int signal) {
    is_running = false;
}

void game::move_left() {
    // 如果没有超出左边界
    if (block_col > 1 - cur_tetromino->get_valid_offset().left &&
        !is_touch_heap(cur_tetromino, block_row, block_col - 1)) {
        block_col -= 1;
        ghost_row = cal_ghost_tetromino_row(cur_tetromino, block_row, block_col);
    }
}

void game::move_right() {
    // 如果没有超出右边界
    if (block_col < main_win->get_inner_width() - cur_tetromino->get_valid_offset().right &&
        !is_touch_heap(cur_tetromino, block_row, block_col + 1)) {
        block_col += 1;
        ghost_row = cal_ghost_tetromino_row(cur_tetromino, block_row, block_col);
    }
}

void game::move_down() {
    // 判断是否碰到堆
    if (touch_heap(cur_tetromino, block_row, block_col, block_row + 1, block_col)) {
        return;
    }

    // 判断是否超出下边界
    if (block_row < main_win->get_inner_height() - cur_tetromino->get_valid_offset().bottom) {
        block_row += 1;
    }
}

void game::rotate() {
    cur_tetromino->rotate();
    ghost_row = cal_ghost_tetromino_row(cur_tetromino, block_row, block_col);
}

bool game::is_touch_heap(const std::shared_ptr<tetro::Tetromino> &tetro, int next_row, int next_col) {
    return is_touch_heap(tetro->get_data(), tetro->get_valid_offset(), next_row, next_col);
}

bool game::is_touch_heap(const std::vector<std::vector<int>> &tetro_data, tetro::ValidOffset valid_offset, int next_row,
                         int next_col) {
    // 判断是否碰到堆或越界
    for (int i = next_row + valid_offset.top - 1; i <= next_row + valid_offset.bottom - 1; ++i) {
        for (int j = next_col + valid_offset.left - 1; j <= next_col + valid_offset.right - 1; ++j) {
            // 是否越下界
            if (i < 0 || i >= tetro_heap.heap.size()) {
                return true;
            }
            // 是否碰到堆
            if (tetro_heap.heap[i][j] != 0 && tetro_data[i - next_row + 1][j - next_col + 1] != 0) {
                return true;
            }
        }
    }
    return false;
}


bool game::touch_heap(std::shared_ptr<tetro::Tetromino> &tetro, int row, int col, int next_row, int next_col) {
    // 将方块加入堆中
    if (is_touch_heap(tetro, next_row, next_col)) {
        auto voffset = tetro->get_valid_offset();

        for (int i = voffset.top; i <= voffset.bottom; i++) {
            for (int j = voffset.left; j <= voffset.right; j++) {
                if ((*tetro)[i][j] == 0) {
                    continue;
                }

                tetro_heap.heap[row - 1 + i][col - 1 + j] = static_cast<int>(tetro->color);
                dec_row_air(row - 1 + i);
            }
        }
        tetro_heap.is_updated = true;

        // 尝试消行
        remove_full_rows(row - 1 + voffset.top, row - 1 + voffset.bottom);

        // 判断是否触顶
        if (check_touch_top(row_air)) {
            quit(0);
        }

        // 生成新的的俄罗斯方块
        cur_tetromino = std::move(tetro_queue.front());
        tetro_queue.pop_front();
        tetro_queue.emplace_back(generate_tetromino());
        move_to_top_center(cur_tetromino);

        is_next_win_updated = true;

        ui::tetro_queue(tetro_queue, next_win);

        return true;
    }
    return false;
}

std::shared_ptr<game::tetro::Tetromino> game::generate_tetromino() {
    // 生成随机数
    for (;;) {
        switch (utils::random_int(0, 6)) {
            case 0:
                return std::make_unique<game::tetro::TetroI>();
            case 1:
                return std::make_unique<game::tetro::TetroJ>();
            case 2:
                return std::make_unique<game::tetro::TetroL>();
            case 3:
                return std::make_unique<game::tetro::TetroO>();
            case 4:
                return std::make_unique<game::tetro::TetroS>();
            case 5:
                return std::make_unique<game::tetro::TetroT>();
            case 6:
                return std::make_unique<game::tetro::TetroZ>();
            default:
                continue;
        }
    }
}

void game::move_to_top_center(std::shared_ptr<tetro::Tetromino> &tetro) {
    auto voffset = tetro->get_valid_offset();
    block_row = 1 - voffset.top;
    block_col = 5 - (voffset.left + (voffset.right - voffset.left + 1) / 2 - 1);
    ghost_row = cal_ghost_tetromino_row(cur_tetromino, block_row, block_col);
}

int game::cal_ghost_tetromino_row(const std::shared_ptr<tetro::Tetromino> &tetro, int row, int col) {
    while (!is_touch_heap(tetro, row + 1, col)) {
        row += 1;
    }
    return row;
}

bool game::check_touch_top(std::vector<int> row_air) {
    return row_air[0] < full_air_count;
}