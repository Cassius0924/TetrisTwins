#ifndef TETRIS_DRAW_H
#define TETRIS_DRAW_H

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
namespace draw {
    /**
     * 将方块坐标转换为行坐标
     * @param block: 方块坐标
     * @return 行坐标
     */
    inline int block_to_col(int block);

    /**
     * 绘制窗口
     * @param left: 窗口左侧位置
     * @param top: 窗口顶部位置
     * @param width: 窗口宽度（单位：block）
     * @param height: 窗口高度
     * @param title: 窗口标题
     */
    void window(int left, int top, int width, int height, std::string title = "");

    /**
     * 绘制俄罗斯方块
     * @param t: 俄罗斯方块
     * @param left: 左侧位置
     * @param top: 顶部位置
     */
    void tetromino(game::tetro::Tetromino* t, int left, int top);

}

#endif //TETRIS_DRAW_H
