#include "tetrominos/tetro_s.h"

using namespace game::tetro;


TetroS::TetroS() : Tetromino() {
    _raw_data = {
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 2, 2, 0, 0},
            {0, 0, 2, 2, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
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

    _voffset = {2, 4, 2, 3};

    color = TetroS::s_color;
}

ui::Color TetroS::s_color = ui::Color::Green;

TetroS::TetroS(TetrominoState init_state) : TetroS() {
}


