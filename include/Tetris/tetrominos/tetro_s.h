#ifndef TETRIS_TETRO_S_H
#define TETRIS_TETRO_S_H

#include "tetrominos/tetromino.h"

namespace game::tetro {
    class TetroS : public Tetromino {
    public:
        TetroS();

        explicit TetroS(TetrominoState init_state);

//        void _calibrate() override;

    };
}
#endif //TETRIS_TETRO_S_H
