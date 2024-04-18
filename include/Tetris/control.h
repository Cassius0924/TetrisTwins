#ifndef TETRIS_CONTROL_H
#define TETRIS_CONTROL_H

/**
 * 游戏控制
 */
namespace ctrl {
    constexpr char k_KEY_Q = 'q';
    constexpr char k_KEY_P = 'p';
    constexpr char k_KEY_C = 'c';
    constexpr char k_KEY_A = 'a';
    constexpr char k_KEY_S = 's';
    constexpr char k_KEY_D = 'd';
    constexpr char k_KEY_SPACE = ' ';

    /**
     * 方块重力下落间隔
     */
    constexpr int k_GRAVITY_INTERVAL_MS = 1000;
    /**
     * 方块锁定延迟
     */
    constexpr int k_LOCK_DELAY_MS = 1000;

    extern bool is_hard_drop;

    /**
     * 监听键盘事件
     */
    void listen_key_event();

    /**
     * 启动键盘监听线程
     */
    void start_key_listener();

    /**
     * 重力线程
     */
    void gravity();

    /**
     * 启动方块的重力线程
     */
    void start_gravity_thread();

    /**
     * 退出游戏命令函数
     */
    void cmd_quit();

    /**
     * 暂停游戏命令函数
     */
    void cmd_pause();

    /**
     * 继续游戏命令函数
     */
    void cmd_continue();

    /**
     * 旋转方块命令函数
     */
    void cmd_rotate();

    /**
     * 左移方块命令函数
     */
    void cmd_left();

    /**
     * 右移方块命令函数
     */
    void cmd_right();

    /**
     * 下移方块命令函数
     */
    void cmd_down();
}


#endif //TETRIS_CONTROL_H
