#include "tt/control.h"

#include <future>
#include <thread>
#include <unordered_map>

#include "tt/game.h"
#include "tt/utils/utils.h"

typedef std::chrono::milliseconds MS;

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

void ctrl::gravity() {
    while (game::is_running) {
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
    // 硬降后再次按下 S 键，下降一格
    if (is_hard_drop) {
        is_hard_drop = false;
        return;
    }

    is_hard_drop = true;
    // 硬降
    game::block_row = game::ghost_row;

    // 延迟 k_LOCK_DELAY_MS 毫秒后再次移动
    std::thread t([] {
        std::this_thread::sleep_for(MS(k_LOCK_DELAY_MS));
        if (!is_hard_drop) {
            return;
        }
        game::move_down();
        is_hard_drop = false;
    });
    t.detach();
}