#ifndef TETRIS_TETRO_O_H
#define TETRIS_TETRO_O_H

#include "tetrominos/tetromino.h"

namespace game::tetro {

    class TetroO : public Tetromino {
    public:
        TetroO();

        explicit TetroO(TetrominoState init_state);

        void _calibrate() override;
    };
}
#endif //TETRIS_TETRO_O_H
