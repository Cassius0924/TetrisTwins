#ifndef TETRIS_TETRO_T_H
#define TETRIS_TETRO_T_H

#include "tetrominos/tetromino.h"

namespace game::tetro {

    class TetroT : public Tetromino {
    public:
        TetroT();

        explicit TetroT(TetrominoState init_state);

//        void _calibrate() override;

    };
}

#endif //TETRIS_TETRO_T_H
