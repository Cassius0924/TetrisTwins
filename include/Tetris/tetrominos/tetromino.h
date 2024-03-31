#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H

#include <vector>
#include <unordered_map>

#include "color.h"

namespace game::tetro {

    enum class TetrominoState {
        Zero = 0,
        Right = 1,
        Two = 2,
        Left = 3,
    };

    /**
     * 方块数据
     */
    struct TetrominoData {
        std::vector<std::vector<int>> raw_data;
        std::vector<std::vector<int>> data;
        TetrominoState state;
    };

    /**
     * 踢墙位移
     */
    struct KickOffset {
        int x;
        int y;
    };

    struct ValidOffset {
        /**
         * 左右上下边界
         */
        int left;
        int right;
        int top;
        int bottom;
    };

    using KickTable = std::vector<std::vector<KickOffset>>;

    class Tetromino {
    protected:
        /**
         * 原始方块姿态数据
         */
        std::vector<std::vector<int>> _raw_data;

        /**
         * 当前方块姿态数据
         */
        std::vector<std::vector<int>> _data;

        /**
         * 方块姿态当前姿态
         */
        TetrominoState _state;

        /**
         * 踢墙表
         */
        KickTable _kick_table;

        /**
         * 有效坐标偏移量
         */
         ValidOffset _voffset{};

    public:
        /**
         * 方块颜色
         */
        Color color;

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

        /**
         * 获取有效坐标偏移量
         */
        ValidOffset get_valid_offset() const;

        void rotate();

        static TetrominoState nextState(TetrominoState state);

    private:
        void _rotate();

        /**
         * 校准方块数据，根据踢墙表调整位置
         */
        void _calibrate();

    };

    // J 做R旋转：顺时针旋转90度
    // 1 0 0    0 1 1
    // 1 1 1 -> 0 1 0
    // 0 0 0    0 1 0
    //
    // J_0[0][0] -> J_R[0][2]; J_0[0][1] -> J_R[1][2]; J_0[0][2] -> J_R[2][2]
    // J_0[1][0] -> J_R[0][1]; J_0[1][1] -> J_R[1][1]; J_0[1][2] -> J_R[2][1]
    // J_0[2][0] -> J_R[0][0]; J_0[2][1] -> J_R[1][0]; J_0[2][2] -> J_R[2][0]
}

#endif //TETRIS_TETROMINO_H
