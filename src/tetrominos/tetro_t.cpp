#include "tt/tetrominos/tetro_t.h"

namespace game::tetro {

TetroT::TetroT() : Tetromino(s_color, s_type) {
    _raw_data = {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 2, 0, 0, 0},
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
        {{0, 0}, {0, 0},  {0, 0},   {0, 0}, {0, 0} },
        {{0, 0}, {1, 0},  {1, -1},  {0, 2}, {1, 2} },
        {{0, 0}, {0, 0},  {0, 0},   {0, 0}, {0, 0} },
        {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}},
    };

    _voffset = {2, 4, 2, 3};
}

TetroT::TetroT(const std::vector<std::vector<int>> &data) : Tetromino(data, s_color, s_type) {
    _kick_table = {
        {{0, 0}, {0, 0},  {0, 0},   {0, 0}, {0, 0} },
        {{0, 0}, {1, 0},  {1, -1},  {0, 2}, {1, 2} },
        {{0, 0}, {0, 0},  {0, 0},   {0, 0}, {0, 0} },
        {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}},
    };
}

ui::Color TetroT::s_color = ui::Color::PURPLE;

TetrominoType TetroT::s_type = TetrominoType::T;

} // namespace game::tetro
