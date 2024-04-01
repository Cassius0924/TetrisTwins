#include <iostream>
#include <thread>
#include <chrono>

#include "terminal.h"
#include "utils.h"
#include "ui.h"
#include "style.h"
#include "game.h"

using namespace std::chrono_literals;

void init() {
    term::clean_screen();
    term::hide_cursor();
    ui::Style::set_style(3);

    // 初始化游戏
    game::init();

    game::main_win = new ui::Window(10, 1, 12, 22, "TetrisTwins");
    game::hold_win = new ui::Window(1, 1, 9, 6, "Hold");
    game::status_win = new ui::Window(1, 7, 9, 16, "Status");
    game::next_win = new ui::Window(22, 1, 8, 18, "Next");
    game::info_win = new ui::Window(22, 19, 8, 4, "Info");

    game::hold_win->draw();
    game::status_win->draw();
    game::next_win->draw();
    game::info_win->draw();
}

void start() {
    while (game::is_running) {
        // 绘制窗口
        game::main_win->draw();

        // 显示FPS
        game::status_win->display("FPS: " + std::to_string(utils::fps()), 3, ui::block_to_col(2));

        // 显示下落方块
//        term::move_to(i++ % 20, 10);
//        term::move_to(game::block_row, draw::block_to_col(game::block_col));
//        term::set_back_color(15);
//        std::cout << "  ";

        ui::tetromino(game::cur_tetromino,
                      ui::block_to_col(game::main_win->absolute_col(game::block_col)),
                      game::main_win->absolute_row(game::block_row));

        ui::game_board(game::tetro_stack, game::main_win);

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

    std::cout << "Bye!" << std::endl;
}

int main() {
    init();
    start();
    exit();

    return 0;
}
