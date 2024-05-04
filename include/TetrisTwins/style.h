#ifndef TETRIS_STYLE_H
#define TETRIS_STYLE_H
#include <vector>

namespace ui {
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
#endif //TETRIS_STYLE_H
