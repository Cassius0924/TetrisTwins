#include "tt/tetrominos/tetro_i.h"

// constexpr int k_TETRO_I_RAW_DATA[5][5] = {
//         {0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0},
//         {0, 1, 1, 1, 1},
//         {0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0},
// };

namespace game::tetro {

TetroI::TetroI() : Tetromino(s_color, s_type) {
    _raw_data = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    _data = _raw_data;

    // 0    ( 0, 0)	(-1, 0)	(+2, 0)	(-1, 0)	(+2, 0)
    // R	(-1, 0)	( 0, 0)	( 0, 0)	( 0,+1)	( 0,-2)
    // 2	(-1,+1)	(+1,+1)	(-2,+1)	(+1, 0)	(-2, 0)
    // L	( 0,+1)	( 0,+1)	( 0,+1)	( 0,-1)	( 0,+2)
    //  去除偏移量，每一行都减上其Offset1
    // 0    ( 0, 0)	(-1, 0)	(+2, 0)	(-1, 0)	(+2, 0)
    // R	( 0, 0)	(+1, 0)	(+1, 0)	(+1,+1)	(+1,-2)
    // 2	( 0, 0) (+2, 0)	(-1, 0)	(+2,-1)	(-1,-1)
    // L	( 0, 0)	( 0, 0)	( 0, 0)	( 0,-2)	( 0, 1)
    _kick_table = {
        {{0, 0}, {-1, 0}, {+2, 0}, {-1, 0},  {+2, 0} },
        {{0, 0}, {+1, 0}, {+1, 0}, {+1, +1}, {+1, -2}},
        {{0, 0}, {+2, 0}, {-1, 0}, {+2, -1}, {-1, -1}},
        {{0, 0}, {0, 0},  {0, 0},  {0, -2},  {0, 1}  },
    };

    _voffset = {2, 5, 3, 3};
}

TetroI::TetroI(const std::vector<std::vector<int>> &data): Tetromino(data, s_color, s_type) {
    _kick_table = {
        {{0, 0}, {-1, 0}, {+2, 0}, {-1, 0},  {+2, 0} },
        {{0, 0}, {+1, 0}, {+1, 0}, {+1, +1}, {+1, -2}},
        {{0, 0}, {+2, 0}, {-1, 0}, {+2, -1}, {-1, -1}},
        {{0, 0}, {0, 0},  {0, 0},  {0, -2},  {0, 1}  },
    };
}

ui::Color TetroI::s_color = ui::Color::CYAN;

TetrominoType TetroI::s_type = TetrominoType::I;

}