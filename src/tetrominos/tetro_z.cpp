#include "tetrominos/tetro_z.h"

using namespace game::tetro;


TetroZ::TetroZ() : Tetromino() {
    _raw_data = {
            {2, 2, 0},
            {0, 2, 2},
            {0, 0, 0},
    };
    _data = _raw_data;

    // 0	( 0, 0)	( 0, 0)	( 0, 0)	( 0, 0)	( 0, 0)
    // R	( 0, 0)	(+1, 0)	(+1,-1)	( 0,+2)	(+1,+2)
    // 2	( 0, 0)	( 0, 0)	( 0, 0)	( 0, 0)	( 0, 0)
    // L	( 0, 0)	(-1, 0)	(-1,-1)	( 0,+2)	(-1,+2)
    _kick_table = {
            {{0, 0}, {0,  0}, {0,  0},  {0, 0}, {0,  0}},
            {{0, 0}, {1,  0}, {1,  -1}, {0, 2}, {1,  2}},
            {{0, 0}, {0,  0}, {0,  0},  {0, 0}, {0,  0}},
            {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}},
    };

    color = Color::Red;
}

TetroZ::TetroZ(TetrominoState init_state) : TetroZ() {
}


