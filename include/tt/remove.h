#ifndef TETRIS_REMOVE_H
#define TETRIS_REMOVE_H

#include <vector>

namespace game {
/**
 * 满行的空气数，即默认空气数，正常为0
 */
extern int full_air_count;

/**
 * 每一行的空气数的数组
 */
extern std::vector<int> row_air;

/**
 * 消行得分表
 */
extern int score_table[5];

/**
 * 减少某一行的空气数
 * @param row: 行数
 */
inline void dec_row_air(int row) {
    --row_air[row];
}

/**
 * 检查并移除指定范围的满行
 * @param top_row: 顶行
 * @param bottom_row: 底行
 */
void remove_full_rows(int top_row, int bottom_row);

}

#endif //TETRIS_REMOVE_H
