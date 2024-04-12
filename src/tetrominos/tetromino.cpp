#include "tetrominos/tetromino.h"
#include "tetrominos/tetro_o.h"
#include "game.h"

using namespace game::tetro;

Tetromino::Tetromino() {
    _state = TetrominoState::Zero;
}

Tetromino::Tetromino(TetrominoState init_state) {
    _state = init_state;
}

Tetromino::~Tetromino() = default;

std::vector<int> &Tetromino::operator[](int i) {
    return _data[i];
}

int Tetromino::rows() const {
    return static_cast<int>(_data.size());
}

int Tetromino::cols() const {
    return static_cast<int>(_data[0].size());
}

TetrominoState Tetromino::prevState(TetrominoState state) {
    switch (state) {
        case TetrominoState::Zero:
            return TetrominoState::Left;
        case TetrominoState::Right:
            return TetrominoState::Zero;
        case TetrominoState::Two:
            return TetrominoState::Right;
        case TetrominoState::Left:
            return TetrominoState::Two;
    }
}

TetrominoState Tetromino::nextState(TetrominoState state) {
    switch (state) {
        case TetrominoState::Zero:
            return TetrominoState::Right;
        case TetrominoState::Right:
            return TetrominoState::Two;
        case TetrominoState::Two:
            return TetrominoState::Left;
        case TetrominoState::Left:
            return TetrominoState::Zero;
    }
}

void Tetromino::rotate() {
    _state = nextState(_state);

    // TODO: 优化
    // 如果对象类型是TetroO
    if (typeid(*this) == typeid(TetroO)) {
        return;
    }
    _rotate();
    _calibrate();
}

void Tetromino::_rotate() {
    int cols = this->cols();
    int rows = this->rows();

    // 右转，顺时针
    for (int i = 0; i < cols / 2; i++) {
        for (int j = i; j < rows - i - 1; j++) {
            int temp = _raw_data[i][j];
            _raw_data[i][j] = _raw_data[rows - j - 1][i];
            _raw_data[rows - j - 1][i] = _raw_data[rows - i - 1][rows - j - 1];
            _raw_data[rows - i - 1][rows - j - 1] = _raw_data[j][rows - i - 1];
            _raw_data[j][rows - i - 1] = temp;
        }
    }

    // 同时旋转有效偏移量voffset
    _voffset = {INT_MAX, INT_MIN, INT_MAX, INT_MIN};
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (_raw_data[i][j] > 0) {
                _voffset.left = std::min(_voffset.left, j);
                _voffset.right = std::max(_voffset.right, j);
                _voffset.top = std::min(_voffset.top, i);
                _voffset.bottom = std::max(_voffset.bottom, i);
            }
        }
    }
}

void Tetromino::_calibrate() {
    int cols = this->cols();
    int rows = this->rows();

    for (int k = 0; k < _kick_table[static_cast<int>(_state)].size(); ++k) {
        auto koffset = _kick_table[static_cast<int>(_state)][k];
        auto prev_koffset = _kick_table[static_cast<int>(prevState(_state))][k];

        int ox = prev_koffset.x - koffset.x;
        int oy = prev_koffset.y - koffset.y;

        // 判断是否撞堆碰底，是否超出左右边界
        if (game::is_touch_heap(_raw_data, _voffset, block_row - oy, block_col + ox) ||
            (block_col + ox + _voffset.left - 1 < 0) ||
            (block_col + ox + _voffset.right - 1 >= main_win->get_inner_width())) {
            continue;
        }

        _data.clear();
        _data.resize(rows, std::vector<int>(cols, 0));

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (_raw_data[i][j] > 0) {
                    int nx = i - (prev_koffset.y - koffset.y);
                    int ny = j + (prev_koffset.x - koffset.x);

                    if (nx >= 0 && ny >= 0 && nx < rows && ny < cols) {
                        _data[nx][ny] = _raw_data[i][j];
                    }
                }
            }
        }
        _voffset = {_voffset.left + ox, _voffset.right + ox, _voffset.top - oy, _voffset.bottom - oy};
        return;
    }

}