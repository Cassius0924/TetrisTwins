#ifndef TETRIS_TETRO_O_H
#define TETRIS_TETRO_O_H

#include "tt/tetrominos/tetromino.h"

namespace game::tetro {

class TetroO : public Tetromino {
public:
    TetroO();

    explicit TetroO(TetrominoState init_state);

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

#endif // TETRIS_TETRO_O_H
