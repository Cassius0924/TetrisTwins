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

/**
 * 游戏控制命令函数
 */
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

void listen_key_event() {
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

void start_key_listener() {
    // 新建键盘监听线程
    std::thread t(listen_key_event);
    // 后台运行，与主线程分离
    t.detach();
}

void gravity() {
    while (game::is_single_started || game::is_double_started) {
        if (is_hard_drop) {
            continue;
        }
        game::move_down();
        std::this_thread::sleep_for(MS(k_GRAVITY_INTERVAL_MS));
    }
}

void start_gravity_thread() {
    std::thread t(gravity);
    t.detach();
}

void cmd_quit() {
    if (game::is_double_started) {
        menu::pop_window(2);
    } else {
        menu::refresh_top_win(true);
    }
    game::quit();
}

void cmd_pause() {}

void cmd_continue() {}

void cmd_rotate() {
    game::rotate();
}

void cmd_left() {
    game::move_left();
}

void cmd_right() {
    game::move_right();
}

void cmd_down() {
    game::hard_drop();
}

} // namespace ctrl
