#include <iostream>

#include "tt/control.h"
#include "tt/menu.h"
#include "tt/style.h"
#include "tt/terminal.h"
#include "tt/tetrominos/define.h"
#include "tt/ui.h"
#include "google/protobuf/port_def.inc"

void init() {
    term::clean_screen();
    term::hide_cursor();
    ui::Style::set_style(3);
}

void show_menu() {
    ctrl::start_key_listener();
    // 显示菜单
    menu::show_menu();
}

void start() {
    while (game::is_running) {
        std::unique_lock lock(game::start_mutex);
        // 等待游戏开始
        game::start_cv.wait(lock, [] {
            return game::is_single_started || game::is_joined_room || game::is_created_room || !game::is_running;
        });

        if (game::is_single_started){
            game::start_single_game();
        } else if (game::is_joined_room) {
            game::start_double_game_client();
        } else if (game::is_created_room) {
            game::start_double_game_server();
        }

        // menu::refresh_top_win();
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
    show_menu();
    start();
    exit();

    return 0;
}
