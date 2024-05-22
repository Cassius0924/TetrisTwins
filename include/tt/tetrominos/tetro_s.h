#ifndef TETRIS_TETRO_S_H
#define TETRIS_TETRO_S_H

#include "tt/tetrominos/tetromino.h"

namespace game::tetro {

class TetroS : public Tetromino {
public:
    TetroS();

    explicit TetroS(TetrominoState init_state);

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

#endif // TETRIS_TETRO_S_H
