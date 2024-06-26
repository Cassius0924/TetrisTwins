#ifndef TETRIS_TETRO_I_H
#define TETRIS_TETRO_I_H

#include "tt/tetrominos/tetromino.h"

namespace game::tetro {

class TetroI : public Tetromino {
public:
    TetroI();

    explicit TetroI(const std::vector<std::vector<int>> &data);

    explicit TetroI(TetrominoState init_state);

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

#endif // TETRIS_TETRO_I_H
