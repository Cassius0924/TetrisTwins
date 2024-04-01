#ifndef TETRIS_TETRO_Z_H
#define TETRIS_TETRO_Z_H

#include "tetromino.h"
#include "tetrominos/tetromino.h"

namespace game::tetro {

    class TetroZ : public Tetromino {
    public:
        TetroZ();

        explicit TetroZ(TetrominoState init_state);

        /**
         * 方块颜色
         */
        static ui::Color s_color;

//        void _calibrate() override;
    };
}

#endif //TETRIS_TETRO_Z_H
