#include "tetrominos/tetro_s.h"

using namespace game::tetro;


TetroS::TetroS() : Tetromino() {
    _data = {
            {0, 2, 2},
            {2, 2, 0},
            {0, 0, 0},
    };
    color = Color::Green;
}

TetroS::TetroS(TetrominoState init_state) : Tetromino(init_state) {
    _data = {
            {0, 2, 2},
            {2, 2, 0},
            {0, 0, 0},
    };
    color = Color::Green;
}

void TetroS::_calibrate() {
}

