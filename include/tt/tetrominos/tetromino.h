#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H

#include <vector>

#include "tt/color.h"

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

enum class TetrominoType {
    I = 0,
    J = 1,
    L = 2,
    O = 3,
    S = 4,
    T = 5,
    Z = 6,
};

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
    ui::Color color;

    /**
     * 方块类型
     */
    TetrominoType type;

public:
    Tetromino(ui::Color color, TetrominoType type);

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
    inline ValidOffset get_valid_offset() const {
        return _voffset;
    }

    /**
     * 获取方块数据的拷贝
     */
    inline std::vector<std::vector<int>> get_data() const {
        return _data;
    }

    void rotate();

    static TetrominoState prevState(TetrominoState state);

    static TetrominoState nextState(TetrominoState state);

private:
    void _rotate();

    /**
     * 校准方块数据，根据踢墙表调整位置
     */
    void _calibrate();

};


}

#endif //TETRIS_TETROMINO_H
