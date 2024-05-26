#include "tt/control.h"

#include <unordered_map>

#include "tt/game.h"
#include "tt/menu.h"
#include "tt/util/util.h"

namespace ctrl {
/**
 * 游戏控制命令
 */
char command;

std::unordered_map<char, std::function<void()>> cmd_func{
    {k_KEY_Q,     cmd_quit    },
    {k_KEY_P,     cmd_pause   },
    {k_KEY_C,     cmd_continue},
    {k_KEY_SPACE, cmd_rotate  },
    {k_KEY_A,     cmd_left    },
    {k_KEY_D,     cmd_right   },
    {k_KEY_S,     cmd_down    },
};

bool is_hard_drop = false;
} // namespace ctrl

void ctrl::listen_key_event() {
    while (game::is_running) {
        command = util::getch();
        if (game::is_single_started || game::is_double_started) {
            if (cmd_func.find(command) != cmd_func.end()) {
                // 游戏开始后
                cmd_func[command]();
            }
        } else if (menu::is_showing_menu && !menu::window_stack.empty()) {
            // 菜单界面时
            ui::Window::handleKeyEvent(command);
        }
    }
}

void ctrl::start_key_listener() {
    // 新建键盘监听线程
    std::thread t(listen_key_event);
    // 后台运行，与主线程分离
    t.detach();
}

void ctrl::gravity() {
    while (game::is_single_started || game::is_double_started) {
        if (is_hard_drop) {
            continue;
        }
        game::move_down();
        std::this_thread::sleep_for(MS(ctrl::k_GRAVITY_INTERVAL_MS));
    }
}

void ctrl::start_gravity_thread() {
    std::thread t(gravity);
    t.detach();
}

void ctrl::cmd_quit() {
    if (game::is_double_started) {
        menu::pop_window(2);
    } else {
        menu::refresh_top_win(true);
    }
    game::quit();
}

void ctrl::cmd_pause() {}

void ctrl::cmd_continue() {}

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
    game::hard_drop();
}