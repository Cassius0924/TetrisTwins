#include "tt/single.h"

#include <chrono>

#include "tt/control.h"
#include "tt/game.h"
#include "tt/remove.h"
#include "tt/terminal.h"
#include "tt/ui.h"
#include "tt/util/util.h"

namespace game {

using namespace std::chrono_literals;

void single_shift_and_push_tetro_queue() {
    cur_tetromino = std::move(tetro_queue.front());
    tetro_queue.pop_front();
    tetro_queue.emplace_back(generate_tetromino());
    move_to_top_center(cur_tetromino, block_row, block_col);
    ghost_row = cal_ghost_tetromino_row(cur_tetromino, tetro_heap, block_row, block_col);
}

void single_init() {
    tetro_queue.resize(5);

    main_win = new ui::Window(10, 1, 12, 22, "TetrisTwins");
    hold_win = new ui::Window(1, 1, 9, 6, "Hold");
    status_win = new ui::Window(1, 7, 9, 16, "Status");
    next_win = new ui::Window(22, 1, 8, 18, "Next");
    info_win = new ui::Window(22, 19, 8, 4, "Info");

    hold_win->draw();
    status_win->draw();
    info_win->draw();

    tetro_heap.heap =
        std::vector<std::vector<int>>(main_win->get_inner_height(), std::vector<int>(main_win->get_inner_width(), 0));

    // 生成初始化方块队列
    for (auto &tetro : tetro_queue) {
        tetro = generate_tetromino();
    }
    cur_tetromino = generate_tetromino();
    move_to_top_center(cur_tetromino, block_row, block_col);
    ghost_row = cal_ghost_tetromino_row(cur_tetromino, tetro_heap, block_row, block_col);

    full_air_count = main_win->get_inner_width();
    row_air = std::vector<int>(main_win->get_height() - 2, full_air_count);

    shift_and_push_tetro_queue = single_shift_and_push_tetro_queue;

    // 创建方块重力
    ctrl::start_gravity_thread();
}

void start_single_game() {
    // 注册FPS text
    status_win->register_text_item(3, ui::block_to_col(2), [] {
        return "FPS: " + std::to_string(util::fps());
    });
    // 注册分数 text
    status_win->register_text_item(4, ui::block_to_col(2), [] {
        return "Score: " + std::to_string(score);
    });

    while (is_single_started) {

        // 绘制文本项
        status_win->draw_text_items();

        // 显示阴影块
        if (is_position_updated || is_state_updated) {
            // 绘制窗口
            main_win->draw();

            is_position_updated = false;
            is_state_updated = false;

            ui::ghost_tetromino(cur_tetromino, main_win->absolute_col(ui::block_to_col(block_col)),
                                main_win->absolute_row(ghost_row));
            // 显示正在下落的俄罗斯方块
            ui::tetromino(cur_tetromino, main_win->absolute_col(ui::block_to_col(block_col)),
                          main_win->absolute_row(block_row));

            // 显示方块堆
            ui::tetro_heap(tetro_heap, main_win);
            term::reset_color();
        }

        if (is_next_win_updated) {
            is_next_win_updated = false;
            next_win->draw();
            ui::tetro_queue(tetro_queue, next_win);
            term::reset_color();
        }

        std::this_thread::sleep_for(100ms);
    }
}

} // namespace game
