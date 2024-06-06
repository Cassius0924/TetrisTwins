#ifndef COLOR_H
#define COLOR_H

namespace ui {

    /**
     * 俄罗斯方块颜色，颜色值对应终端颜色
     */
    enum class Color : std::uint8_t {
        CYAN = 14,
        Red = 9,
        ORANGE = 214,
        YELLOW = 11,
        GREEN = 10,
        BLUE = 12,
        PURPLE = 13,
        GRAY = 8,
        BLACK = 0,
    };

}

#endif //COLOR_H
