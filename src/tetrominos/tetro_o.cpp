#include "tt/tetrominos/tetro_o.h"

namespace game::tetro {

TetroO::TetroO() : Tetromino(s_color, s_type) {
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
    _kick_table = {{{0, 0}}, {{0, 0}}, {{0, 0}}, {{0, 0}}};

    _voffset = {1, 2, 0, 1};
}

ui::Color TetroO::s_color = ui::Color::Yellow;

TetrominoType TetroO::s_type = TetrominoType::O;

} // namespace game::tetro
