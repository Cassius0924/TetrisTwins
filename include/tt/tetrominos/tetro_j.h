#ifndef TETRIS_TETRO_J_H
#define TETRIS_TETRO_J_H

#include "tt/tetrominos/tetromino.h"

namespace game::tetro {

class TetroJ : public Tetromino {
public:
    TetroJ();

    explicit TetroJ(const std::vector<std::vector<int>> &data);

    explicit TetroJ(TetrominoState init_state);

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

#endif // TETRIS_TETRO_J_H
