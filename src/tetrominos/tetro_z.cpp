#include "tetrominos/tetro_z.h"

using namespace game::tetro;


TetroZ::TetroZ() : Tetromino() {
    _data = {
            {2, 2, 0},
            {0, 2, 2},
            {0, 0, 0},
    };
    color = Color::Red;
}

TetroZ::TetroZ(TetrominoState init_state) : Tetromino(init_state) {
    _data = {
            {2, 2, 0},
            {0, 2, 2},
            {0, 0, 0},
    };
    color = Color::Red;
}

void TetroZ::_calibrate() {
}

