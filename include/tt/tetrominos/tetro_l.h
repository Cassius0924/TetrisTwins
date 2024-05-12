#ifndef TETRIS_TETRO_L_H
#define TETRIS_TETRO_L_H

#include "tt/tetrominos/tetromino.h"

namespace game::tetro {
    class TetroL : public Tetromino {
    public:
        TetroL();

        explicit TetroL(TetrominoState init_state);

        /**
         * 方块颜色
         */
        static ui::Color s_color;

        //        void _calibrate() override;
    };
} // namespace game::tetro

#endif // TETRIS_TETRO_L_H
