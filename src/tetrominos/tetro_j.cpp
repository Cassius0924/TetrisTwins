#include "tetrominos/tetro_j.h"


using namespace game::tetro;

TetroJ::TetroJ() : Tetromino() {
    _data = {
            {2, 0, 0},
            {2, 2, 2},
            {0, 0, 0},
    };
    color = Color::Blue;
}

TetroJ::TetroJ(TetrominoState init_state) : Tetromino(init_state) {
    _data = {
            {2, 0, 0},
            {2, 2, 2},
            {0, 0, 0},
    };
    color = Color::Blue;
}

void TetroJ::_calibrate() {
}

