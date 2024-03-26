#ifndef TETRIS_TETRO_I_H
#define TETRIS_TETRO_I_H

#include "tetrominos/tetromino.h"

namespace game::tetro {
    class TetroI : public Tetromino {
    public:
        TetroI();

        explicit TetroI(TetrominoState init_state);

        void _calibrate() override;

    };
}

#endif //TETRIS_TETRO_I_H
