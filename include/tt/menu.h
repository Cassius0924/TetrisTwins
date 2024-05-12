#ifndef TETRIS_MENU_H
#define TETRIS_MENU_H

#include "tt/room.h"
#include "tt/ui.h"

namespace menu {
    /**
     * 是否显示菜单
     */
    extern bool is_showing_menu;

    extern bool is_searching_game_rooms;

    extern bool is_sending_game_room;

    /**
     * 当前搜索到游戏房间列表
     */
    extern std::set<room::Room> game_room_set;

    /**
     * 显示游戏菜单
     */
    void show_menu();

    /**
     * 刷新游戏菜单窗口显示
     */
    void refresh_menu_win(ui::Window &menu_win);

    /**
     * 刷新游戏房间搜索窗口显示
     */
    void refresh_game_rooms_win(ui::Window &game_rooms_win);

    /**
     * 刷新游戏房间窗口显示
     */
    void refresh_room_win(ui::Window &room_win, int room_id);

    /**
     * 搜索双人游戏
     */
    void search_double_player_game(ui::Window &game_rooms_win, ui::Window &menu_win);

    /**
     * 创建双人游戏
     */
    void create_double_player_game(ui::Window &room_win);

    /**
     * 开始单人游戏
     */
    void start_single_player_game();

    /**
     * 开始双人游戏
     */
    void start_double_player_game();

}

#endif //TETRIS_MENU_H
