#include <iostream>
#include <vector>

#include "ui.h"
#include "terminal.h"
#include "color.h"
#include "style.h"


int ui::block_to_col(int block) {
    return block * 2 - 1;
}


ui::Window::Window(int left, int top, int width, int height, std::string title) : _left(left), _top(top),
                                                                                  _width(width),
                                                                                  _height(height), _title(title) {
}

void ui::Window::draw() {
    if (_top < 0 || _left < 0 || _width < 0 || _height < 0) {
        return;
    }

    typedef ui::Style DS;

    //                top=1(real top=0)
    //                 v
    //       1=_left > ┌────────────────┐
    //  (real _left=0) │                │ \ (real _height=20)
    //                 │                │ _height=5
    //                 │                │ /
    //                 └────────────────┘
    //                    \ _width=10 /
    //                   (real _width=20)

    term::move_to(_top, block_to_col(_left));

    // 绘制第一行
    // 两个字符为一个像素，所以宽度需要乘以2
    std::cout << DS::tl();
    for (int col = 0; col < _width - 2; ++col) {
        std::cout << DS::h_edge();
    }
    std::cout << DS::tr();

    // 绘制标题
    term::move_to(_top, block_to_col(_left) + (_width - _title.size() / 2));
    std::cout << _title;

    // 绘制中间行
    for (int row = 1; row < _height - 1; ++row) {
        term::move_to(_top + row, block_to_col(_left));
        // 中间行第一列
        std::cout << DS::vr_edge();
        // 中间列
        for (int col = 0; col < _width - 2; ++col) {
            std::cout << ". ";
        }
        // 中间行最后一列
        std::cout << DS::vl_edge();
    }

    term::move_to(_top + _height - 1, block_to_col(_left));

    // 绘制最后一行
    std::cout << DS::bl();
    for (int col = 0; col < _width - 2; ++col) {
        std::cout << DS::h_edge();
    }
    std::cout << DS::br();
}

ui::Window::~Window() {
}

void ui::Window::display(const std::string &value, int row, int col) const {
    term::move_to(absolute_row(row), absolute_col(col));
    std::cout << value;
}

int ui::Window::absolute_col(int col) const {
    return _left + col;
}

int ui::Window::absolute_row(int row) const {
    return _top + row;
}

int ui::Window::get_height() const {
    return _height;
}

int ui::Window::get_width() const {
    return _width;
}

void ui::tetromino(game::tetro::Tetromino *t, int left, int top) {

    term::set_back_color(static_cast<int>(t->color));
    for (int i = 0; i < t->rows(); i++) {
        term::move_to(top + i, left);
        for (int j = 0; j < t->cols(); j++) {
            if ((*t)[i][j] > 0) {
//                term::set_back_color(game::tetro_color[t[i][j]]);
//                term::set_back_color(static_cast<int>(game::::tetro_color[t[i][j]]));
                std::cout << "  ";
            }
            term::move_to(top + i, left + 2 * (j + 1));
        }
    }
    term::reset_color();
}
