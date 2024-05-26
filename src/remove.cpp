#include "tt/remove.h"

#include "tt/game.h"

namespace game {

int full_air_count;

std::vector<int> row_air;

int score_table[5] = {0, 100, 300, 500, 800};

void remove_full_rows(int top_row, int bottom_row) {
    int full_row_count = 0;
    int i = top_row;
    auto remove = [&]() {
        int bottom_full_row = i - 1;

        // 开始消行
        for (int j = bottom_full_row - full_row_count; j >= 0; j -= full_row_count) {
            for (int k = 0; k < full_row_count; ++k) {
                if (j - k < 0) {
                    break;
                }
                tetro_heap.heap[j + full_row_count - k] = tetro_heap.heap[j - k];
                row_air[j + full_row_count - k] = row_air[j - k];
            }
        }

        // 顶部空行，消多少行，顶部就空出多少行
        for (int j = 0; j < full_row_count; ++j) {
            tetro_heap.heap[j] = std::vector<int>(tetro_heap.heap[0].size(), 0);
            row_air[j] = full_air_count;
        }

        full_row_count = 0;
        tetro_heap.is_updated = true;
    };

    int total_air_count = 0;
    for (; i <= bottom_row; ++i) {
        if (row_air[i] == 0) {
            ++full_row_count;
        } else {
            if (full_row_count > 0) {
                total_air_count += full_row_count;
                remove();
            }
        }
    }
    if (full_row_count > 0) {
        total_air_count += full_row_count;
        remove();
    }

    if (total_air_count > 0) {
        score += score_table[total_air_count];
    }
}

} // namespace game
