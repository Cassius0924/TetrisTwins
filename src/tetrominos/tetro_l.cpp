#include "tetrominos/tetro_l.h"

using namespace game::tetro;

TetroL::TetroL() : Tetromino() {
    _raw_data = {
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 2, 0, 0},
            {0, 0, 2, 2, 2, 0, 0},
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

    color = TetroL::s_color;
}

ui::Color TetroL::s_color = ui::Color::Orange;

TetroL::TetroL(TetrominoState init_state) : TetroL() {
}

