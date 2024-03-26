#include "tetrominos/tetro_t.h"

using namespace game::tetro;


TetroT::TetroT() : Tetromino() {
    _data = {
            {0, 2, 0},
            {2, 2, 2},
            {0, 0, 0},
    };
}

TetroT::TetroT(TetrominoState init_state) : Tetromino(init_state) {
    _data = {
            {0, 2, 0},
            {2, 2, 2},
            {0, 0, 0},
    };
}

void TetroT::_calibrate() {
}

