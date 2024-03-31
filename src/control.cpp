#include <thread>
#include <unordered_map>

#include "control.h"
#include "utils.h"
#include "game.h"

namespace ctrl {
    /**
     * 游戏控制命令
     */
    char command;

    std::unordered_map<char, std::function<void()>> cmd_func{
            {k_KEY_Q,     cmd_quit},
            {k_KEY_P,     cmd_pause},
            {k_KEY_C,     cmd_continue},
            {k_KEY_SPACE, cmd_rotate},
            {k_KEY_A,     cmd_left},
            {k_KEY_D,     cmd_right},
            {k_KEY_S,     cmd_down},
    };
}

void ctrl::listen_key_event() {
    while (game::is_running) {
        command = utils::getch();
        if (cmd_func.find(command) != cmd_func.end()) {
            cmd_func[command]();
        }
    }
}

void ctrl::start_key_listener() {
    // 新建键盘监听线程
    std::thread t(listen_key_event);
    // 后台运行，与主线程分离
    t.detach();
}

void ctrl::cmd_quit() {
    game::quit();
}

void ctrl::cmd_pause() {
}

void ctrl::cmd_continue() {
}

void ctrl::cmd_rotate() {
    game::rotate();
}

void ctrl::cmd_left() {
    game::move_left();
}

void ctrl::cmd_right() {
    game::move_right();
}

void ctrl::cmd_down() {
    game::move_down();
}