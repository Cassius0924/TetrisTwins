#ifndef TETRIS_DRAW_H
#define TETRIS_DRAW_H

#include "string"
#include "tetromino.h"


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

    void tetromino(game::Tetromino& t, int top, int left);


    /**
     * 窗口绘制主题
     */
    class Style {
    private:
        static const std::vector<std::string> style1;
        static const std::vector<std::string> style2;
        static const std::vector<std::string> style3;
        static const std::vector<std::string> style4;
        static std::vector<std::string> cur_style;

    public:

        /**
         * 左上角
         * @return 左上角字符块
         */
        static std::string tl();

        /**
         * 右上角
         * @return 右上角字符块
         */
        static std::string tr();

        /**
         * 左下角
         * @return 左下角字符块
         */
        static std::string bl();

        /**
         * 右下角
         * @return 右下角字符块
         */
        static std::string br();

        /**
         * 水平边框
         * @return 水平边框字符块
         */
        static std::string h_edge();


        /**
         * 靠左垂直边框
         * @return 靠左垂直边框字符块
         */
        static std::string vr_edge();

        /**
         * 靠右垂直边框
         * @return 靠右垂直边框字符块
         */
        static std::string vl_edge();

        /**
         * 更改主题
         * @param style_index: 主题索引
         */
        static void set_style(int style_index);
    };

}

#endif //TETRIS_DRAW_H
