#include "tetrominos/tetro_o.h"


using namespace game::tetro;

TetroO::TetroO() : Tetromino() {
    _data = {
            {0, 2, 2},
            {0, 2, 2},
            {0, 0, 0},
    };
}

TetroO::TetroO(TetrominoState init_state) : Tetromino(init_state) {
    _data = {
            {0, 2, 2},
            {0, 2, 2},
            {0, 0, 0},
    };
}

void TetroO::_calibrate() { }

