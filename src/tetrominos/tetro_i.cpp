#include "tetrominos/tetro_i.h"

using namespace game::tetro;

//constexpr int k_TETRO_I_RAW_DATA[5][5] = {
//        {0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0},
//        {0, 1, 1, 1, 1},
//        {0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0},
//};

TetroI::TetroI() : Tetromino() {
    _raw_data = {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 1, 1, 1},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
    };

    _data = _raw_data;

    //0 ( 0, 0)	(-1, 0)	(+2, 0)	(-1, 0)	(+2, 0)
    //R	(-1, 0)	( 0, 0)	( 0, 0)	( 0,+1)	( 0,-2)
    //2	(-1,+1)	(+1,+1)	(-2,+1)	(+1, 0)	(-2, 0)
    //L	( 0,+1)	( 0,+1)	( 0,+1)	( 0,-1)	( 0,+2)
    _kick_table = {
            {{0,  0}, {-1, 0}, {2,  0}, {-1, 0},  {2,  0}},
            {{-1, 0}, {0,  0}, {0,  0}, {0,  1},  {0,  -2}},
            {{-1, 1}, {1,  1}, {-2, 1}, {1,  0},  {-2, 0}},
            {{0,  1}, {0,  1}, {0,  1}, {0,  -1}, {0,  2}},
    };

    _voffset = {1, 4, 2, 2};

    color = TetroI::s_color;
}

ui::Color TetroI::s_color = ui::Color::Cyan;

TetroI::TetroI(TetrominoState init_state) : TetroI() {
}

