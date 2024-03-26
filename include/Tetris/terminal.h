#ifndef TETRIS_TERMINAL_H
#define TETRIS_TERMINAL_H


/**
 * 终端输出打印
 */
namespace term { //terminal

    /**
     * 移动光标到指定位置
     * @param row: 行
     * @param col: 列
     */
    void move_to(int row, int col);

    /**
     * 设置前景色
     * @param id: 颜色id
     */
    void set_fore_color(int id);

    /**
     * 设置背景色
     * @param id: 颜色id
     */
    void set_back_color(int id);

    /**
     * 清屏
     */
    void clean_screen();

    /**
     * 重置颜色
     */
    void reset_color();

    /**
     * 隐藏光标
     */
    void hide_cursor();

    /**
     * 显示光标
     */
     void show_cursor();
}


#endif //TETRIS_TERMINAL_H
