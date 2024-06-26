#ifndef TETRIS_TETRO_L_H
#define TETRIS_TETRO_L_H

#include "tt/tetrominos/tetromino.h"

namespace game::tetro {

class TetroL : public Tetromino {
public:
    TetroL();

    explicit TetroL(const std::vector<std::vector<int>> &data);

    explicit TetroL(TetrominoState init_state);

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

#endif // TETRIS_TETRO_L_H
