#ifndef TETRIS_MENU_H
#define TETRIS_MENU_H

#include "tt/terminal.h"
#include "tt/ui.h"

#include <stack>

namespace menu {
/**
 * 是否显示菜单
 */
extern bool is_showing_menu;

extern bool is_searching_game_rooms;

extern bool is_sending_game_room;

extern std::stack<std::shared_ptr<ui::Window>> window_stack;

/**
 * 当前搜索到游戏房间列表
 */
extern std::set<game::Room> game_room_set;

/**
 * 显示游戏菜单
 */
void show_menu();

/**
 * 刷新顶部窗口显示
 */
inline void refresh_top_win(bool is_clean_screen = true) {
    if (is_clean_screen) {
        term::clean_screen();
    }
    auto top_win = window_stack.top();
    top_win->draw();
    top_win->draw_menu_items();
    top_win->draw_text_items();
}

/**
 * 压入窗口
 * @param win 窗口
 */
inline void push_window(const ui::WindowPtr &win, bool is_clean_screen = true) {
    window_stack.emplace(win);
    refresh_top_win(is_clean_screen);
}

/**
 * 弹出窗口
 * @param is_clean_screen 是否清屏
 */
inline void pop_window(bool is_clean_screen = true) {
    window_stack.pop();
    refresh_top_win(is_clean_screen);
}

/**
 * 搜索双人游戏
 */
void search_double_game(const ui::WindowPtr &win, const ui::WindowPtr &menu_win);

/**
 * 创建双人游戏
 */
void create_double_game(const ui::WindowPtr &win);

}

#endif //TETRIS_MENU_H
