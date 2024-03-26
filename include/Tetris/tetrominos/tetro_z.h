#ifndef TETRIS_TETRO_Z_H
#define TETRIS_TETRO_Z_H

#include "tetromino.h"
#include "tetrominos/tetromino.h"

namespace game::tetro {

    class TetroZ : public Tetromino {
    public:
        TetroZ();

        explicit TetroZ(TetrominoState init_state);

        void _calibrate() override;
    };
}

#endif //TETRIS_TETRO_Z_H
