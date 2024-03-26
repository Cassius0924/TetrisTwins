#include "tetrominos/tetro_l.h"

using namespace game::tetro;

TetroL::TetroL() : Tetromino() {
    _data = {
            {0, 0, 2},
            {2, 2, 2},
            {0, 0, 0},
    };
    color = Color::Orange;
}

TetroL::TetroL(TetrominoState init_state) : Tetromino(init_state) {
    _data = {
            {0, 0, 2},
            {2, 2, 2},
            {0, 0, 0},
    };
    color = Color::Orange;
}

// TODO: 新增_raw_data，用于存储原始数据，用于旋转，_data用于存储旋转后的数据，_data数组大小可变
void TetroL::_calibrate() {
}

