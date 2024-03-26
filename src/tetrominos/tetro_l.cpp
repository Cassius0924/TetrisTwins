#include "tetrominos/tetro_l.h"

using namespace game::tetro;

TetroL::TetroL() : Tetromino() {
    _data = {
            {0, 0, 2},
            {2, 2, 2},
            {0, 0, 0},
    };
}

TetroL::TetroL(TetrominoState init_state) : Tetromino(init_state) {
    _data = {
            {0, 0, 2},
            {2, 2, 2},
            {0, 0, 0},
    };
}

void TetroL::_calibrate() {
}

