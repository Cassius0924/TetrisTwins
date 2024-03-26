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

    ui::Window(1, 1, 9, 6, "Hold").draw();
    ui::Window(1, 7, 9, 16, "Status").draw();
    ui::Window(22, 1, 8, 18, "Next").draw();
    ui::Window(22, 19, 8, 4, "Info").draw();
}

void start() {
    game::main_win = new ui::Window(10, 1, 12, 22, "TetrisTwins");
    while (game::is_running) {
        // 绘制窗口
        game::main_win->draw();

        // 显示FPS
        term::move_to(10, 4);
        std::cout << "FPS:" << utils::fps();

        // 显示下落方块
//        term::move_to(i++ % 20, 10);
//        term::move_to(game::block_row, draw::block_to_col(game::block_col));
//        term::set_back_color(15);
//        std::cout << "  ";

//        draw::tetromino(game::cur_tetromino, draw::block_to_col(game::block_col), game::block_row);
        ui::tetromino(game::cur_tetromino, ui::block_to_col(game::main_win->relative_col(game::block_col)), game::main_win->relative_row(game::block_row));
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
    std::cout << "Bye!" << std::endl;
}

int main() {
    init();
    start();
    exit();

    return 0;
}
