#include <iostream>
#include <vector>

#include "draw.h"
#include "terminal.h"
#include "style.h"


int draw::block_to_col(int block) {
    return block * 2 - 1;
}

void draw::window(int left, int top, int width, int height, std::string title) {
    if (top < 0 || left < 0 || width < 0 || height < 0) {
        return;
    }

    typedef draw::Style DS;

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
    std::cout << DS::tl();
    for (int col = 0; col < width - 2; ++col) {
        std::cout << DS::h_edge();
    }
    std::cout << DS::tr();

    // 绘制标题
    term::move_to(top, block_to_col(left) + (width - title.size() / 2));
    std::cout << title;

    // 绘制中间行
    for (int row = 1; row < height - 1; ++row) {
        term::move_to(top + row, block_to_col(left));
        // 中间行第一列
        std::cout << DS::vr_edge();
        // 中间列
        for (int col = 0; col < width - 2; ++col) {
            std::cout << ". ";
        }
        // 中间行最后一列
        std::cout << DS::vl_edge();
    }

    term::move_to(top + height - 1, block_to_col(left));

    // 绘制最后一行
    std::cout << DS::bl();
    for (int col = 0; col < width - 2; ++col) {
        std::cout << DS::h_edge();
    }
    std::cout << DS::br();
}

void draw::tetromino(game::tetro::Tetromino* t, int top, int left) {
    term::set_back_color(static_cast<int>(Color::Red));
    for(int i = 0; i < t->rows(); i++) {
        term::move_to(top + i, left);
        for(int j = 0; j < t->cols(); j++) {
            if((*t)[i][j] > 0) {
//                term::set_back_color(game::tetro_color[t[i][j]]);
//                term::set_back_color(static_cast<int>(game::::tetro_color[t[i][j]]));
                std::cout << "  ";
            }
            term::move_to(top + i, left + 2 * (j + 1));
        }
    }
}
