#ifndef TETRIS_TETRO_J_H
#define TETRIS_TETRO_J_H

#include "tetrominos/tetromino.h"

namespace game::tetro {
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
}

#endif //TETRIS_TETRO_J_H
