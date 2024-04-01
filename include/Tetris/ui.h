#ifndef TETRIS_UI_H
#define TETRIS_UI_H

#include "string"
#include "tetrominos/tetromino.h"


// 0	1	2	3	4	5	6	7	8	9	A	B	C	D	E	F
// U+250x	─	━	│	┃	┄	┅	┆	┇	┈	┉	┊	┋	┌	┍	┎	┏
// U+251x	┐	┑	┒	┓	└	┕	┖	┗	┘	┙	┚	┛	├	┝	┞	┟
// U+252x	┠	┡	┢	┣	┤	┥	┦	┧	┨	┩	┪	┫	┬	┭	┮	┯
// U+253x	┰	┱	┲	┳	┴	┵	┶	┷	┸	┹	┺	┻	┼	┽	┾	┿
// U+254x	╀	╁	╂	╃	╄	╅	╆	╇	╈	╉	╊	╋	╌	╍	╎	╏
// U+255x	═	║	╒	╓	╔	╕	╖	╗	╘	╙	╚	╛	╜	╝	╞	╟
// U+256x	╠	╡	╢	╣	╤	╥	╦	╧	╨	╩	╪	╫	╬	╭	╮	╯
// U+257x	╰	╱	╲	╳	╴	╵	╶	╷	╸	╹	╺	╻	╼	╽	╾	╿
// Notes
// 1.^ As of Unicode version 15.1

/**
 * 绘图
 *
 */
namespace ui {
    /**
     * 将方块坐标转换为行坐标
     * @param block: 方块坐标
     * @return 行坐标
     */
    inline int block_to_col(int block);

    /**
     * UI 窗口类
     */
    class Window {
    private:
        int _left;
        int _top;
        int _width;
        int _height;
        std::string _title;

    public:
        /**
         * @param left: 窗口左侧位置
         * @param top: 窗口顶部位置
         * @param width: 窗口宽度（单位：block）
         * @param height: 窗口高度
         * @param title: 窗口标题
         */
        Window(int left, int top, int width, int height, std::string title = "");
        ~Window();

        /**
         * 绘制窗口
         */
        void draw();

        /**
         * 在此窗口的相对位置显示内容
         * @param row: 相对行坐标
         * @param col: 相对列坐标
         */
        void display(const std::string &value, int row, int col) const;

        /**
         * 根据传入的相对行坐标，获取绝对行坐标
         * @param row: 行坐标
         * @return 绝对行坐标
         */
        inline int absolute_row(int row) const;

        /**
         * 根据传入的相对列坐标，获取绝对列坐标
         * @param col: 列坐标
         * @return 绝对列坐标
         */
        inline int absolute_col(int col) const;

        /**
         * 获取窗口宽度
         * @return 窗口宽度
         */
        int get_width() const;

        /**
         * 获取窗口高度
         * @return 窗口高度
         */
        int get_height() const;
    };

    /**
     * 绘制俄罗斯方块
     * @param t: 俄罗斯方块
     * @param left: 左侧位置
     * @param top: 顶部位置
     */
    void tetromino(game::tetro::Tetromino* t, int left, int top);

    /**
     * 绘制俄罗斯方块堆
     */
    void game_board(const std::vector<std::vector<char>> &tetro_stack, Window *win);


}

#endif //TETRIS_UI_H
