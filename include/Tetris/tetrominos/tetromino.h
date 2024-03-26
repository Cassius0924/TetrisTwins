#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H

#include <vector>
#include <unordered_map>

#include "color.h"

namespace game::tetro {

    enum class TetrominoState {
        Zero = '0',
        Left = 'L',
        Right = 'R',
        Two = '2',
    };

    // I[5][5]; J L O S T Z[3][3];
//    using Tetromino = std::vector<std::vector<int>>;

    class Tetromino {
    protected:
        /**
         * 方块姿态数据
         */
        std::vector<std::vector<int>> _data;

        /**
         * 方块姿态当前姿态
         */
        TetrominoState _state;

    public:
        Tetromino();

        explicit Tetromino(TetrominoState init_state);

        Tetromino(const Tetromino &tetro) = default;

//        explicit Tetromino(std::vector<std::vector<int>> data);

        virtual ~Tetromino();

        /**
         * 获取方块数据
         * @param i: 行
         * @return 方块数据
         */
        std::vector<int> &operator[](int i);

        /**
         * 获取方块行数
         * @return 行数
         */
        int rows() const;

        /**
         * 获取方块列数
         * @return 列数
         */
        int cols() const;

        void rotate();

        static TetrominoState NextState(TetrominoState state);

    private:
        void _rotate();

        // = 0
        virtual void _calibrate();
    };

    // J 做R旋转：顺时针旋转90度
    // 1 0 0    0 1 1
    // 1 1 1 -> 0 1 0
    // 0 0 0    0 1 0
    //
    // J_0[0][0] -> J_R[0][2]; J_0[0][1] -> J_R[1][2]; J_0[0][2] -> J_R[2][2]
    // J_0[1][0] -> J_R[0][1]; J_0[1][1] -> J_R[1][1]; J_0[1][2] -> J_R[2][1]
    // J_0[2][0] -> J_R[0][0]; J_0[2][1] -> J_R[1][0]; J_0[2][2] -> J_R[2][0]

//    Tetromino rotate(Tetromino &t);

    extern std::unordered_map<int, Color> tetro_color;
}

#endif //TETRIS_TETROMINO_H
