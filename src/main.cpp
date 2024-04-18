#include <iostream>
#include <thread>

#include "terminal.h"
#include "tetrominos/define.h"
#include "utils.h"
#include "ui.h"
#include "style.h"

using namespace std::chrono_literals;

void init() {
    term::clean_screen();
    term::hide_cursor();
    ui::Style::set_style(3);

    game::main_win = new ui::Window(10, 1, 12, 22, "TetrisTwins");
    game::hold_win = new ui::Window(1, 1, 9, 6, "Hold");
    game::status_win = new ui::Window(1, 7, 9, 16, "Status");
    game::next_win = new ui::Window(22, 1, 8, 18, "Next");
    game::info_win = new ui::Window(22, 19, 8, 4, "Info");

    game::hold_win->draw();
    game::status_win->draw();
    game::info_win->draw();

    // 初始化游戏
    game::init();
}

void start() {
    while (game::is_running) {

        if (game::is_next_win_updated) {
            game::next_win->draw();
            ui::tetro_queue(game::tetro_queue, game::next_win);
            game::is_next_win_updated = false;
        }

        // 绘制窗口
        game::main_win->draw();

        // 显示FPS
        game::status_win->display("FPS: " + std::to_string(utils::fps()), 3, ui::block_to_col(2));
        // 显示分数
        game::status_win->display("Score: " + std::to_string(game::score), 4, ui::block_to_col(2));

        // 显示阴影块
        ui::ghost_tetromino(game::cur_tetromino, game::main_win->absolute_col(ui::block_to_col(game::block_col)),
                            game::main_win->absolute_row(game::ghost_row));
        // 显示正在下落的俄罗斯方块
        ui::tetromino(game::cur_tetromino,
                      game::main_win->absolute_col(ui::block_to_col(game::block_col)),
                      game::main_win->absolute_row(game::block_row));

        // 显示方块堆
        ui::game_board(game::tetro_heap, game::main_win);

        term::reset_color();

        std::cout << std::flush;
        std::this_thread::sleep_for(100ms);
    }
}

void exit() {
    term::reset_color();
    term::clean_screen();
    term::show_cursor();
    term::move_to(1, 1);

    delete game::main_win;
    delete game::hold_win;
    delete game::status_win;
    delete game::next_win;
    delete game::info_win;

    std::cout << "GAME, OVER!\nBye!\n";
}

int main() {
    init();
    start();
    exit();

    return 0;
}
