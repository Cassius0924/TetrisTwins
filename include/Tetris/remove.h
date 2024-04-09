#ifndef TETRIS_REMOVE_H
#define TETRIS_REMOVE_H

#include <vector>

namespace game {
    /**
     *
     */
    extern int full_air_count;

    /**
     * 每一行的空气数的数组
     */
    extern std::vector<int> row_air;

    /**
     * 减少某一行的空气数
     * @param row: 行数
     */
    inline void dec_row_air(int row) {
        --game::row_air[row];
    }

    /**
     * 检查并移除指定范围的满行
     * @param top_row: 顶行
     * @param bottom_row: 底行
     */
    void remove_full_rows(int top_row, int bottom_row);

}

#endif //TETRIS_REMOVE_H
