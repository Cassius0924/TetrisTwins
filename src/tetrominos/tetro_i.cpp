//#include <iostream>
//#include <vector>
//#include <map>

#include "tetrominos/tetro_i.h"

using namespace game::tetro;

//const std::unordered_map<TetrominoState, std::vector<std::pair<int, int>>> kick_table = {};

TetroI::TetroI() : Tetromino() {
    _data = {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 1, 1, 1},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
    };
}

TetroI::TetroI(TetrominoState init_state) : Tetromino(init_state) {
    _data = {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 1, 1, 1},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
    };
}

void TetroI::_calibrate() {
    int cols = this->cols();
    int rows = this->rows();
    std::vector<std::vector<int>> new_tetro(_data);

    // 根据踢墙表调整位置
    switch (_state) {
        case TetrominoState::Zero:
        case TetrominoState::Right:
        case TetrominoState::Two:
        case TetrominoState::Left: {
            for (int j = cols - 1; j >= 0; j--) {
                for (int i = 0; i < rows; i++) {
                    if (new_tetro[i][j] > 0) {
                        new_tetro[i][j + 1] = new_tetro[i][j];
                        new_tetro[i][j] = 0;
                    }
                }
            }
        }
    }
    _data = new_tetro;
}

