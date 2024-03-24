#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H
#include <vector>
#include <unordered_map>

#include "color.h"

namespace game {

    // I[5][5]; J L O S T Z[3][3];
    using Tetromino = std::vector<std::vector<int>>;

    extern Tetromino I, J, L ,O, S, T, Z;

    // J 做R旋转：顺时针旋转90度
    // 1 0 0    0 1 1
    // 1 1 1 -> 0 1 0
    // 0 0 0    0 1 0
    //
    // J_0[0][0] -> J_R[0][2]; J_0[0][1] -> J_R[1][2]; J_0[0][2] -> J_R[2][2]
    // J_0[1][0] -> J_R[0][1]; J_0[1][1] -> J_R[1][1]; J_0[1][2] -> J_R[2][1]
    // J_0[2][0] -> J_R[0][0]; J_0[2][1] -> J_R[1][0]; J_0[2][2] -> J_R[2][0]

    Tetromino rotate(Tetromino &t);

    extern std::unordered_map<int, Color> tetro_color;
}

#endif //TETRIS_TETROMINO_H
