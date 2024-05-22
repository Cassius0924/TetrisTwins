#ifndef TETRIS_TETRO_T_H
#define TETRIS_TETRO_T_H

#include "tt/tetrominos/tetromino.h"

namespace game::tetro {

class TetroT : public Tetromino {
public:
    TetroT();

    explicit TetroT(TetrominoState init_state);

    /**
     * 方块颜色
     */
    static ui::Color s_color;

    /**
     * 方块类型
     */
    static TetrominoType s_type;

};

} // namespace game::tetro

#endif // TETRIS_TETRO_T_H
