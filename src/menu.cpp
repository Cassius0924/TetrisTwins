#include "tt/menu.h"

#include <functional>
#include <iostream>
#include <thread>

#include "tt/control.h"
#include "tt/net/udp_bc_receiver.h"
#include "tt/net/udp_bc_sender.h"
#include "tt/terminal.h"
#include "tt/utils/utils.h"

using namespace std::chrono_literals;

namespace menu {

bool is_showing_menu = true;

bool is_searching_game_rooms = false;

bool is_sending_game_room = false;

std::set<room::Room> game_room_set = {};

std::stack<std::shared_ptr<ui::Window>> window_stack;

} // namespace menu

void menu::show_menu() {
    auto menu_win = ui::Window::createPtr(6, 1, 14, 20, "TetrisTwins");
    auto game_rooms_win = ui::Window::createPtr(7, 2, 12, 18, "Game Rooms");
    auto room_win = ui::Window::createPtr(7, 2, 12, 18, "My Room");
    auto help_win = ui::Window::createPtr(7, 2, 12, 18, "Help");

    menu_win->register_menu_item(2, ui::block_to_col(4), "1. 单人游戏", [] {
        std::unique_lock lock(game::start_mutex);
        game::is_single_started = true;
        // is_showing_menu = false;
        game::start_cv.notify_one();
    });
    menu_win->register_menu_item(3, ui::block_to_col(4), "2. 搜索双人游戏", [game_rooms_win, menu_win] {
        push_window(game_rooms_win, false);
        is_searching_game_rooms = true;
        search_double_game(game_rooms_win, menu_win);
    });
    menu_win->register_menu_item(4, ui::block_to_col(4), "3. 创建双人游戏", [room_win] {
        push_window(room_win, false);
        is_sending_game_room = true;
        create_double_game(room_win);
    });

    menu_win->register_menu_item(5, ui::block_to_col(4), "4. 帮助", [help_win] {
        push_window(help_win, false);
    });
    menu_win->register_menu_item(17, ui::block_to_col(4), "0. 退出游戏", [] {
        term::clean_screen();
        term::move_to(0, 0);
        term::show_cursor();
        exit(-1);
    });

    game_rooms_win->register_menu_item(16, ui::block_to_col(2), "0. 返回", [] {
        is_searching_game_rooms = false;
        pop_window();
    });
    game_rooms_win->register_text_item(1, ui::block_to_col(2), "搜索中...");
    game_rooms_win->register_text_item(2, ui::block_to_col(2), "─ ─ ─ ─ ─ ─");

    help_win->register_menu_item(16, ui::block_to_col(2), "0. 返回", [] {
        pop_window();
    });

    room_win->register_menu_item(14, ui::block_to_col(2), "1.开始游戏", game::start_double_game);

    room_win->register_menu_item(16, ui::block_to_col(2), "0.返回", [] {
        is_sending_game_room = false;
        pop_window();
    });
    room_win->register_text_item(1, ui::block_to_col(2), "TetrisTwins Room");
    room_win->register_text_item(4, ui::block_to_col(2), "我:" + utils::get_lan_ip_linux());
    room_win->register_text_item(6, ui::block_to_col(2), "─ ─ ─ VS ─ ─ ─");
    room_win->register_text_item(8, ui::block_to_col(2), "等待对手加入...");
    push_window(menu_win);
}

void menu::search_double_game(const ui::WindowPtr &win, const ui::WindowPtr &menu_win) {
    room::game_rooms.clear();
    // 删除game_rooms_win.menu_items除第一个外的所有元素
    win->menu_items.erase(win->menu_items.begin(), std::prev(win->menu_items.end()));
    std::this_thread::sleep_for(0.5s);
    std::thread t = std::thread([&win] {
        net::UdpBcReceiver bc_receiver(room::k_PORT);
        // 设置为非阻塞模式，以便线程自动结束
        bc_receiver.set_non_block(true);
        proto::RoomMessage room_message;

        // 加入房间函数
        auto join_room = [](int room_id) {
            // TODO: TCP连接

        };
        while (is_searching_game_rooms) {
            auto [data, len] = bc_receiver.recv(1024);
            if (len <= 0) {
                continue;
            }
            room_message.ParseFromString(data);
            if (room::game_rooms.count(room::Room(room_message)) > 0) {
                continue;
            }
            room::game_rooms.emplace(room_message);
            win->menu_items.insert(std::prev(win->menu_items.end()),
                                   ui::MenuItem{room_message.name() + " " + std::to_string(room_message.id()),
                                                win->absolute_row(win->menu_items.size() + 3), win->absolute_col(2),
                                                std::bind(join_room, room_message.id())});

            win->draw_menu_items();
        }
    });
    t.detach();
}

void menu::create_double_game(const ui::WindowPtr &room_win) {
    proto::RoomMessage room_message;
    room_message.set_name("一个TT房间");
    int room_id = utils::random_int(1000, 9999);
    room_message.set_id(room_id);
    room_message.set_ip(utils::get_lan_ip_linux());
    room_message.set_port(room::k_PORT);
    room_win->display(2, ui::block_to_col(2), "房间号: " + std::to_string(room_id));

    std::thread t = std::thread([room_message] {
        net::UdpBcSender bc_sender(room::k_PORT);
        while (is_sending_game_room) {
            bc_sender.send(room_message.SerializeAsString());
            std::this_thread::sleep_for(1s);
        }
    });
    t.detach();
}

