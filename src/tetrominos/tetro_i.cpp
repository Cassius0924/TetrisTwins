#include <iostream>
#include "tetrominos/tetro_i.h"

using namespace game::tetro;

//const std::unordered_map<TetrominoState, std::vector<std::pair<int, int>>> kick_table = {};

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

    color = Color::Cyan;
}

TetroI::TetroI(TetrominoState init_state) : TetroI() {
}

