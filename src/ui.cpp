#include "ui.h"

#include <iostream>

#include "control.h"
#include "menu.h"
#include "style.h"
#include "terminal.h"
#include "utils/utils.h"

ui::Window::Window(int left, int top, int width, int height, std::string title)
    : _left(left), _top(top), _width(width), _height(height), _title(std::move(title)), menu_items() {}

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

ui::Window::~Window() {}

void ui::Window::display(const std::string &text, int row, int col) const {
    term::move_to(absolute_row(row), absolute_col(col));
    std::cout << text;
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

void ui::Window::register_menu_item(const std::string &text, int row, int col, std::function<void()> action) {
    menu_items.emplace_back(MenuItem{text, absolute_row(row), absolute_col(col), std::move(action)});
}

void ui::Window::showInteractiveMenu(const std::list<MenuItem> &menu_items) {
    for (auto &item : menu_items) {
        term::move_to(item.arow, item.acol);
        std::cout << item.text;
    }
    auto item = menu_items.begin();
    while (menu::is_showing_menu) {
        term::set_back_color(static_cast<int>(Color::Gray));
        term::move_to(item->arow, item->acol);
        std::cout << item->text;
        std::cout << std::flush;
        term::reset_color();
        while (true) {
            char command = utils::getch();
            if (command == ctrl::k_KEY_W || command == ctrl::k_KEY_UP) {
                if (item != menu_items.begin()) {
                    term::move_to(item->arow, item->acol);
                    std::cout << item->text;
                    item--;
                }
                break;
            } else if (command == ctrl::k_KEY_S || command == ctrl::k_KEY_DOWN) {
                if (item != --menu_items.end()) {
                    term::move_to(item->arow, item->acol);
                    std::cout << item->text;
                    item++;
                }
                break;
            } else if (command == ctrl::k_KEY_SPACE || command == ctrl::k_KEY_ENTER) {
                if (item->action) {
                    item->action();
                }
                break;
            }
        }
    }
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
        term::move_to(win->absolute_row(i + 1), win->absolute_col(block_to_col(1)));
        for (int j = 0; j < tetro_heap.heap[i].size(); j++) {
            if (tetro_heap.heap[i][j] != 0) {
                if (pre_block != tetro_heap.heap[i][j]) {
                    pre_block = tetro_heap.heap[i][j];
                    term::set_back_color(tetro_heap.heap[i][j]);
                }
                std::cout << "  ";
            }
            term::move_to(win->absolute_row(i + 1), win->absolute_col(block_to_col(j + 2)));
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
                      win->absolute_col(block_to_col(3 - (voffset.left + (voffset.right - voffset.left + 2) / 2 - 1))),
                      win->absolute_row(i * 3 + 3) - (voffset.top + (voffset.bottom - voffset.top + 1) / 2));
    }
}