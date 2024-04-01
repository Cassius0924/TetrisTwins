#include "tetrominos/tetro_o.h"


using namespace game::tetro;

TetroO::TetroO() : Tetromino() {
    _raw_data = {
            {0, 2, 2},
            {0, 2, 2},
            {0, 0, 0},
    };
    _data = _raw_data;

    // 0	( 0, 0)
    // R	( 0, 0)
    // 2	( 0, 0)
    // L	( 0, 0)
    _kick_table = {
            {{0, 0},},
            {{0, 0},},
            {{0, 0},},
            {{0, 0}}
    };

    _voffset = {1, 2, 0, 1};

    color = TetroO::s_color;
}

ui::Color TetroO::s_color = ui::Color::Yellow;

TetroO::TetroO(TetrominoState init_state) : TetroO() {
}

