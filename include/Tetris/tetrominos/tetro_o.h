#ifndef TETRIS_TETRO_O_H
#define TETRIS_TETRO_O_H

#include "tetrominos/tetromino.h"

namespace game::tetro {

    class TetroO : public Tetromino {
    public:
        TetroO();

        explicit TetroO(TetrominoState init_state);

        /**
         * 方块颜色
         */
        static ui::Color s_color;

//        void _calibrate() override;
    };
}
#endif //TETRIS_TETRO_O_H
