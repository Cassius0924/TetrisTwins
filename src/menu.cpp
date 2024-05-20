#include "tt/menu.h"

#include <functional>
#include <thread>

#include "tt/control.h"
#include "tt/net/packer.h"
#include "tt/net/udp_bc_receiver.h"
#include "tt/net/udp_bc_sender.h"
#include "tt/terminal.h"
#include "tt/utils/utils.h"

using namespace std::chrono_literals;

namespace menu {

bool is_showing_menu = true;

bool is_searching_game_rooms = false;

bool is_sending_game_room = false;

std::set<game::Room> game_room_set = {};

std::stack<std::shared_ptr<ui::Window>> window_stack;

void show_menu() {
    auto menu_win = ui::Window::createPtr(6, 1, 14, 20, "TetrisTwins");
    auto game_rooms_win = ui::Window::createPtr(7, 2, 12, 18, "Game Rooms");
    auto room_win = ui::Window::createPtr(7, 2, 12, 18, "My Room");
    auto help_win = ui::Window::createPtr(7, 2, 12, 18, "Help");

    menu_win->register_menu_item(2, ui::block_to_col(4), "1. 单人游戏", [] {
        game::is_single_started = true;
        // is_showing_menu = false;
        std::lock_guard<std::mutex> lock(game::start_mutex);
        game::start_cv.notify_one();
    });
    menu_win->register_menu_item(3, ui::block_to_col(4), "2. 搜索双人游戏", [game_rooms_win] {
        // 删除game_rooms_win.menu_items除第一个外的所有元素
        game_rooms_win->menu_items.erase(game_rooms_win->menu_items.begin(),
                                         std::prev(game_rooms_win->menu_items.end()));
        push_window(game_rooms_win, false);
        is_searching_game_rooms = true;
        search_double_game(game_rooms_win);
    });
    menu_win->register_menu_item(4, ui::block_to_col(4), "3. 创建双人游戏", [room_win] {
        push_window(room_win, false);
        is_sending_game_room = true;
        // 发送UDP广播
        create_double_game(room_win);
        // 开启TCP服务器
        std::lock_guard<std::mutex> lock(game::start_mutex);
        game::is_created_room = true;
        game::start_cv.notify_one();
    });
    menu_win->register_menu_item(5, ui::block_to_col(4), "4. 帮助", [help_win] {
        push_window(help_win, false);
    });
    menu_win->register_menu_item(17, ui::block_to_col(4), "0. 退出游戏", [] {
        game::is_running = false;
        std::lock_guard<std::mutex> lock(game::start_mutex);
        game::start_cv.notify_all();
    });

    game_rooms_win->register_menu_item(16, ui::block_to_col(2), "0. 返回", [] {
        is_searching_game_rooms = false;
        // std::this_thread::sleep_for(1s);
        pop_window();
    });
    game_rooms_win->register_text_item(1, ui::block_to_col(2), "搜索中...");
    game_rooms_win->register_text_item(2, ui::block_to_col(2), "─ ─ ─ ─ ─ ─");

    help_win->register_menu_item(16, ui::block_to_col(2), "0. 返回", [] {
        pop_window();
    });

    room_win->register_menu_item(14, ui::block_to_col(2), "1.开始游戏", [] {
        // FIXME: 检测玩家是否已经加入
        std::lock_guard<std::mutex> lock(game::double_start_mutex);
        game::is_double_started = true;
        game::double_start_cv.notify_one();
    });
    room_win->register_menu_item(16, ui::block_to_col(2), "0.返回", [] {
        is_sending_game_room = false;
        game::is_created_room = false;
        pop_window();
    });
    room_win->register_text_item(1, ui::block_to_col(2), "TetrisTwins Room");
    room_win->register_text_item(4, ui::block_to_col(2), "我:" + utils::get_lan_ip_linux());
    room_win->register_text_item(6, ui::block_to_col(2), "─ ─ ─ VS ─ ─ ─");
    room_win->register_text_item(8, ui::block_to_col(2), "等待对手加入...");

    push_window(menu_win);
}

// TODO: 下面两个函数换命名空间
void search_double_game(const ui::WindowPtr &win) {
    game::game_rooms.clear();
    std::this_thread::sleep_for(0.5s);
    std::thread t = std::thread([&win] {
        net::UdpBcReceiver bc_receiver(game::k_PORT);
        // 设置为非阻塞模式，以便线程自动结束
        bc_receiver.set_non_block(true);
        while (is_searching_game_rooms) {
            // 更新加载提示
            // for (int i = 0; i < 3; ++i) {
            //     win->display(1, 9+i, ".");
            //     std::this_thread::sleep_for(0.25s);
            // }
            // win->display(1, 9, "    ");

            // TODO: 任意长度接收支持
            auto [data, len] = bc_receiver.recv(1024);
            if (len <= 0) {
                continue;
            }

            std::unique_ptr<google::protobuf::Message> room_message = net::unpack_message(data);
            game::Room room = game::Room(*dynamic_cast<proto::RoomMessage *>(room_message.get()));

            if (game::game_rooms.count(room) > 0) {
                continue;
            }
            game::game_rooms.emplace(room);
            auto it = game::game_rooms.find(room);

            // TODO: 优化，封装
            // 插入在返回菜单项之前
            const std::string text = room.name + "#" + std::to_string(room.id);
            win->menu_items.insert(
                std::prev(win->menu_items.end()),
                ui::MenuItem{text, win->absolute_row(win->menu_items.size() + 3), win->absolute_col(3), [it] {
                                 // 加入游戏
                                 std::lock_guard<std::mutex> lock(game::start_mutex);
                                 game::is_joined_room = true;
                                 game::game_room = std::make_unique<game::Room>(*it);
                                 // 显示房主房间界面
                                 auto room_win = ui::Window::createPtr(7, 2, 12, 18, "Room");
                                 room_win->register_text_item(1, ui::block_to_col(2), "TetrisTwins Room");
                                 room_win->register_text_item(4, ui::block_to_col(2),
                                                              "我:" + utils::get_lan_ip_linux());
                                 room_win->register_text_item(6, ui::block_to_col(2), "─ ─ ─ VS ─ ─ ─");
                                 room_win->register_text_item(8, ui::block_to_col(2), "对手:" + it->ip);
                                 push_window(room_win, false);

                                 game::start_cv.notify_one();
                             }});
            win->draw_menu_items();

            std::this_thread::sleep_for(0.25s);
        }
    });
    t.detach();
}

void create_double_game(const ui::WindowPtr &win) {
    proto::RoomMessage room_message;
    // TODO: 随机房间名字
    room_message.set_name("Tetris房间");
    int room_id = utils::random_int(1000, 9999);
    room_message.set_id(room_id);
    room_message.set_ip(utils::get_lan_ip_linux());
    room_message.set_port(game::k_PORT);
    win->display(2, ui::block_to_col(2), "房间号: " + std::to_string(room_id));

    std::thread t = std::thread([room_message] {
        net::UdpBcSender bc_sender(game::k_PORT);
        while (is_sending_game_room) {
            bc_sender.send( net::pack_message(room_message));
            std::this_thread::sleep_for(1s);
        }
    });
    t.detach();
}


} // namespace menu
