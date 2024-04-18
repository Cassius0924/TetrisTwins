#include <iostream>
#include <utility>

#include "ui.h"
#include "terminal.h"
#include "style.h"


ui::Window::Window(int left, int top, int width, int height, std::string title) : _left(left), _top(top),
                                                                                  _width(width),
                                                                                  _height(height),
                                                                                  _title(std::move(title)) {
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
            std::cout << "  ";
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

int ui::Window::get_height() const {
    return _height;
}

int ui::Window::get_width() const {
    return _width;
}

int ui::Window::get_inner_width() const {
    return _width - 2 < 0 ? 0 : _width - 2;
}

int ui::Window::get_inner_height() const {
    return _height - 2 < 0 ? 0 : _height - 2;
}

void ui::tetromino(std::shared_ptr<game::tetro::Tetromino> &tetro, int left, int top) {
    term::set_back_color(static_cast<int>(tetro->color));
    auto voffset = tetro->get_valid_offset();
    for (int i = voffset.top; i <= voffset.bottom; i++) {
        term::move_to(top + i, left + 2 * voffset.left);
        for (int j = voffset.left; j <= voffset.right; j++) {
            if ((*tetro)[i][j] > 0) {
                std::cout << "  ";
            }
            term::move_to(top + i, left + 2 * (j + 1));
        }
    }
    term::reset_color();
}

void ui::game_board(game::TetroHeap &tetro_heap, ui::Window *win) {
    int pre_block = -1;
    for (int i = 0; i < tetro_heap.heap.size(); i++) {
        term::move_to(win->absolute_row(i + 1), block_to_col(win->absolute_col(1)));
        for (int j = 0; j < tetro_heap.heap[i].size(); j++) {
            if (tetro_heap.heap[i][j] != 0) {
                if (pre_block != tetro_heap.heap[i][j]) {
                    pre_block = tetro_heap.heap[i][j];
                    term::set_back_color(tetro_heap.heap[i][j]);
                }
                std::cout << "  ";
            }
            term::move_to(win->absolute_row(i + 1), block_to_col(win->absolute_col(j + 2)));
            std::cout << std::flush;
        }
    }
}

void ui::ghost_tetromino(std::shared_ptr<game::tetro::Tetromino> &tetro, int left, int top) {
    term::set_fore_color(static_cast<int>(tetro->color));
    auto voffset = tetro->get_valid_offset();
    for (int i = voffset.top; i <= voffset.bottom; i++) {
        term::move_to(top + i, left + 2 * voffset.left);
        for (int j = voffset.left; j <= voffset.right; j++) {
            if ((*tetro)[i][j] > 0) {
                std::cout << "[]";
            }
            term::move_to(top + i, left + 2 * (j + 1));
        }
    }
    term::reset_color();
}

void ui::tetro_queue(std::deque<std::shared_ptr<game::tetro::Tetromino>> &tetro_queue, ui::Window *win) {
    for (int i = 0; i < tetro_queue.size(); ++i) {
        auto voffset = tetro_queue[i]->get_valid_offset();
        ui::tetromino(tetro_queue[i],
                      block_to_col(win->absolute_col(3) - (voffset.left + (voffset.right - voffset.left + 2) / 2 - 1)),
                      win->absolute_row(i * 3 + 3) - (voffset.top + (voffset.bottom - voffset.top + 1) / 2));
    }
}