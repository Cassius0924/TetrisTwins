#include "menu.h"

#include <iostream>
#include <thread>

#include "control.h"
#include "terminal.h"
#include "utils/utils.h"

using namespace std::chrono_literals;

namespace menu {
    bool is_showing_menu = true;
    bool is_searching_game_rooms = true;
    bool is_sending_game_room = true;
    std::set<room::Room> game_room_set = {};
} // namespace menu

void menu::show_menu() {
    ui::Window menu_win(6, 1, 14, 20, "TetrisTwins");
    ui::Window game_rooms_win(7, 2, 12, 18, "Game Rooms");
    ui::Window room_win(7, 2, 12, 18, "My Room");
    ui::Window help_win(7, 2, 12, 18, "Help");

    menu_win.register_menu_item("1. 单人游戏", 2, ui::block_to_col(4), [] {
        is_showing_menu = false;
        start_single_player_game();
    });
    menu_win.register_menu_item("2. 搜索双人游戏", 3, ui::block_to_col(4), [&game_rooms_win, &menu_win] {
        search_double_player_game(game_rooms_win, menu_win);
    });
    menu_win.register_menu_item("3. 创建双人游戏", 4, ui::block_to_col(4), [&room_win] {
        create_double_player_game(room_win);
    });
    menu_win.register_menu_item("4. 帮助", 5, ui::block_to_col(4), [&help_win] {
        help_win.draw();
        ui::Window::showInteractiveMenu(help_win.menu_items);
    });
    menu_win.register_menu_item("0. 退出游戏", 17, ui::block_to_col(4), [] {
        term::clean_screen();
        term::move_to(0, 0);
        term::show_cursor();
        exit(-1);
    });

    game_rooms_win.register_menu_item("0. 返回", 16, ui::block_to_col(2), [&menu_win] {
        is_searching_game_rooms = false;
        refresh_menu_win(menu_win);
    });

    help_win.register_menu_item("0. 返回", 16, ui::block_to_col(2), [&menu_win] {
        refresh_menu_win(menu_win);
    });

    room_win.register_menu_item("1.开始游戏", 14, ui::block_to_col(2), [] {
        start_double_player_game();
    });
    room_win.register_menu_item("0.返回", 16, ui::block_to_col(2), [&menu_win] {
        is_sending_game_room = false;
        refresh_menu_win(menu_win);
    });

    refresh_menu_win(menu_win);
}

void menu::refresh_menu_win(ui::Window &menu_win) {
    menu_win.draw();
    ui::Window::showInteractiveMenu(menu_win.menu_items);
}

void menu::refresh_game_rooms_win(ui::Window &game_rooms_win) {
    game_rooms_win.draw();
    game_rooms_win.display("搜索中...", 1, ui::block_to_col(2));
    game_rooms_win.display("─ ─ ─ ─ ─ ─", 2, ui::block_to_col(2));
    ui::Window::showInteractiveMenu(game_rooms_win.menu_items);
}

void menu::refresh_room_win(ui::Window &room_win, int room_id) {
    room_win.draw();
    room_win.display("TetrisTwins Room", 1, ui::block_to_col(2));
    room_win.display("房间号: " + std::to_string(room_id), 2, ui::block_to_col(2));
    room_win.display("我:" + utils::get_lan_ip_linux(), 4, ui::block_to_col(2));
    room_win.display("─ ─ ─ VS ─ ─ ─", 6, ui::block_to_col(2));
    room_win.display("等待对手加入...", 8, ui::block_to_col(2));
    ui::Window::showInteractiveMenu(room_win.menu_items);
}

void menu::search_double_player_game(ui::Window &game_rooms_win, ui::Window &menu_win) {
    room::game_rooms.clear();
    // 删除game_rooms_win.menu_items除第一个外的所有元素
    game_rooms_win.menu_items.erase(game_rooms_win.menu_items.begin(), std::prev(game_rooms_win.menu_items.end()));
    std::this_thread::sleep_for(0.5s);

    auto bc_receiver = new room::UdpBroadcastReceiver(room::k_PORT);
    is_searching_game_rooms = true;
    std::thread t = std::thread([&game_rooms_win, bc_receiver] {
        proto::RoomMessage room_message;
        while (is_searching_game_rooms) {
            if (!bc_receiver->recv_room_message(room_message)) {
                continue;
            }

            if (room::game_rooms.count(room::Room(room_message)) > 0) {
                continue;
            }

            room::game_rooms.emplace(room_message);
            game_rooms_win.menu_items.insert(
                std::prev(game_rooms_win.menu_items.end()),
                ui::MenuItem{room_message.name() + " " + std::to_string(room_message.id()),
                             game_rooms_win.absolute_row(game_rooms_win.menu_items.size() + 3),
                             game_rooms_win.absolute_col(2), nullptr});

            for (const auto &item : game_rooms_win.menu_items) {
                term::move_to(item.arow, item.acol);
                std::cout << item.text;
            }
            std::cout << std::flush;
        }
        delete bc_receiver;
    });
    t.detach();
    refresh_game_rooms_win(game_rooms_win);
}

void menu::create_double_player_game(ui::Window &room_win) {
    room::UdpBroadcastSender bc_sender(room::k_PORT);

    proto::RoomMessage room_message;
    room_message.set_name("一个TT房间");
    int room_id = utils::random_int(1000, 9999);
    room_message.set_id(room_id);
    room_message.set_ip(utils::get_lan_ip_linux());
    room_message.set_port(room::k_PORT);

    is_sending_game_room = true;
    std::thread t = std::thread([&bc_sender, room_message] {
        while (is_sending_game_room) {
            if (bc_sender.send_room_message(room_message) < 0) {
                continue;
            }
            std::this_thread::sleep_for(1s);
        }
    });
    t.detach();
    refresh_room_win(room_win, room_id);
}

void menu::start_single_player_game() {
    game::spg_init();

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
        ui::tetromino(game::cur_tetromino, game::main_win->absolute_col(ui::block_to_col(game::block_col)),
                      game::main_win->absolute_row(game::block_row));

        // 显示方块堆
        ui::game_board(game::tetro_heap, game::main_win);

        term::reset_color();
        std::cout << std::flush;
        std::this_thread::sleep_for(100ms);
    }
}

void menu::start_double_player_game() {

}
