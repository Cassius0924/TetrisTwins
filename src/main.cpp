#include <iostream>
#include <thread>
#include <chrono>

#include "terminal.h"
#include "utils.h"
#include "draw.h"
#include "game.h"

using namespace std::chrono_literals;

void init() {
    term::clean_screen();
    term::hide_cursor();
    draw::Style::set_style(3);

    // 初始化游戏
    game::init();

    draw::window(1,1,9,6, "Hold");
    draw::window(1,7,9,16, "Status");
    draw::window(22,1,8,18, "Next");
    draw::window(22,19,8,4, "Info");
}

void start() {
    while (game::is_running) {

        // 绘制窗口
        draw::window(10,1,12,22, "Tetris");

        // 显示FPS
        term::move_to(10, 4);
        std::cout << "FPS:" << utils::fps();

        // 显示下落方块
//        term::move_to(i++ % 20, 10);
//        term::move_to(game::block_row, draw::block_to_col(game::block_col));
//        term::set_back_color(15);
//        std::cout << "  ";

        draw::tetromino(game::cur_tetromino, game::block_row, game::block_col);
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
