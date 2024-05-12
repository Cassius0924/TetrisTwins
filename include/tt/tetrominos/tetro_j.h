#ifndef TETRIS_TETRO_J_H
#define TETRIS_TETRO_J_H

#include "tt/tetrominos/tetromino.h"

namespace game {
    namespace tetro {
        class TetroJ : public Tetromino {
        public:
            TetroJ();

            explicit TetroJ(TetrominoState init_state);

            /**
             * 方块颜色
             */
            static ui::Color s_color;

            //        void _calibrate() override;
        };
    } // namespace tetro
} // namespace game

#endif // TETRIS_TETRO_J_H
