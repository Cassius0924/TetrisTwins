#include <iostream>
#include <vector>

#include "draw.h"
#include "terminal.h"

const std::vector<std::string> draw::Style::style1 = {" ┌", "┐ ", " └", "┘ ", "──", " │", "│ "};
const std::vector<std::string> draw::Style::style2 = {" ╔", "╗ ", " ╚", "╝ ", "══", " ║", "║ "};
const std::vector<std::string> draw::Style::style3 = {" ╭", "╮ ", " ╰", "╯ ", "──", " │", "│ "};
const std::vector<std::string> draw::Style::style4 = {" ┏", "┓ ", " ┗", "┛ ", "━━", " ┃", "┃ "};
std::vector<std::string> draw::Style::cur_style;

std::string draw::Style::tl() {
    return cur_style[0];
}

std::string draw::Style::tr() {
    return cur_style[1];
}

std::string draw::Style::bl() {
    return cur_style[2];
}

std::string draw::Style::br() {
    return cur_style[3];
}

std::string draw::Style::h_edge() {
    return cur_style[4];
}

std::string draw::Style::vr_edge() {
    return cur_style[5];
}

std::string draw::Style::vl_edge() {
    return cur_style[6];
}

void draw::Style::set_style(int style_index) {
    switch (style_index) {
        case 1:
            cur_style = style1;
            break;
        case 2:
            cur_style = style2;
            break;
        case 3:
            cur_style = style3;
            break;
        case 4:
            cur_style = style4;
            break;
        default:
            cur_style = style1;
            break;
    }
}

int draw::block_to_col(int block) {
    return block * 2 - 1;
}

void draw::window(int left, int top, int width, int height, std::string title) {
    if (top < 0 || left < 0 || width < 0 || height < 0) {
        return;
    }
    typedef draw::Style ds;

    //                top=1(real top=0)
    //                 v
    //        1=left > ┌────────────────┐
    //   (real left=0) │                │ \ (real height=20)
    //                 │                │ height=5
    //                 │                │ /
    //                 └────────────────┘
    //                    \ width=10 /
    //                   (real width=20)

    term::move_to(top, block_to_col(left));

    // 绘制第一行
    // 两个字符为一个像素，所以宽度需要乘以2
    std::cout << ds::tl();
    for (int col = 0; col < width - 2; ++col) {
        std::cout << ds::h_edge();
    }
    std::cout << ds::tr();

    // 绘制标题
    term::move_to(top, block_to_col(left) + (width - title.size() / 2));
    std::cout << title;

    // 绘制中间行
    for (int row = 1; row < height - 1; ++row) {
        term::move_to(top + row, block_to_col(left));
        // 第一列
        std::cout << ds::vr_edge();
        // 中间列
        for (int col = 0; col < width - 2; ++col) {
            std::cout << "  ";
        }
        // 最后一列
        std::cout << ds::vl_edge();
    }

    term::move_to(top + height - 1, block_to_col(left));

    // 绘制最后一行
    std::cout << ds::bl();
    for (int col = 0; col < width - 2; ++col) {
        std::cout << ds::h_edge();
    }
    std::cout << ds::br();
}

void draw::tetromino(game::Tetromino& t, int top, int left) {
    for(int i = 0; i < t.size(); i++) {
        term::move_to(top + i, block_to_col(left));
        for(int j = 0; j < t[0].size(); j++) {
            if(t[i][j] > 0) {
//                term::set_back_color(game::tetro_color[t[i][j]]);
                term::set_back_color(static_cast<int>(game::tetro_color[t[i][j]]));
            } else{
                term::reset_color();
            }
            std::cout << "  ";
        }
    }
}
