#include "tt/tetrominos/tetromino.h"

#include "tt/game.h"
#include "tt/tetrominos/tetro_i.h"
#include "tt/tetrominos/tetro_j.h"
#include "tt/tetrominos/tetro_l.h"
#include "tt/tetrominos/tetro_o.h"
#include "tt/tetrominos/tetro_s.h"
#include "tt/tetrominos/tetro_t.h"
#include "tt/tetrominos/tetro_z.h"
#include "tt/ui.h"

namespace game::tetro {

Tetromino::Tetromino(ui::Color color, TetrominoType type) : color(color), type(type), _state(TetrominoState::Zero) {}

Tetromino::Tetromino(const std::vector<std::vector<int>> &data, ui::Color color, TetrominoType type)
    : color(color), type(type), _state(TetrominoState::Zero) {
    _data = data;
    _raw_data = data;
    _voffset = {INT_MAX, INT_MIN, INT_MAX, INT_MIN};

    for (int i = 0; i < _data.size(); ++i) {
        for (int j = 0; j < _data[0].size(); ++j) {
            if (_data[i][j] > 0) {
                _voffset.left = std::min(_voffset.left, j);
                _voffset.right = std::max(_voffset.right, j);
                _voffset.top = std::min(_voffset.top, i);
                _voffset.bottom = std::max(_voffset.bottom, i);
            }
        }
    }
}

Tetromino::Tetromino(const Tetromino &other)
    : color(other.color), type(other.type), _state(other._state), _data(other._data), _raw_data(other._raw_data),
      _voffset(other._voffset), _kick_table(other._kick_table) {}

Tetromino &Tetromino::operator=(const Tetromino &other) {
    if (this != &other) {
        std::lock_guard<std::mutex> lock(_mutex);
        color = other.color;
        type = other.type;
        _state = other._state;
        _data = other._data;
        _raw_data = other._raw_data;
        _voffset = other._voffset;
        _kick_table = other._kick_table;
    }
    return *this;
}

Tetromino::Tetromino(Tetromino &&other) noexcept
    : color(other.color), type(other.type), _state(other._state), _data(std::move(other._data)),
      _raw_data(std::move(other._raw_data)), _voffset(other._voffset), _kick_table(std::move(other._kick_table)) {}

Tetromino &Tetromino::operator=(Tetromino &&other) noexcept {
    if (this != &other) {
        std::lock_guard<std::mutex> lock(_mutex);
        color = other.color;
        type = other.type;
        _state = other._state;
        _data = std::move(other._data);
        _raw_data = std::move(other._raw_data);
        _voffset = other._voffset;
        _kick_table = std::move(other._kick_table);
    }
    return *this;
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
    return TetrominoState::Zero;
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
    return TetrominoState::Zero;
}

void Tetromino::rotate() {
    std::lock_guard<std::mutex> lock(_mutex);
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
        if (is_touch_heap(_raw_data, tetro_heap.heap, _voffset, block_row - oy, block_col + ox) ||
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

proto::Tetro to_proto(std::shared_ptr<Tetromino> tetro) {
    switch (tetro->type) {
        case TetrominoType::I: {
            return proto::TETRO_I;
        }
        case TetrominoType::J: {
            return proto::TETRO_J;
        }
        case TetrominoType::L: {
            return proto::TETRO_L;
        }
        case TetrominoType::O: {
            return proto::TETRO_O;
        }
        case TetrominoType::S: {
            return proto::TETRO_S;
        }
        case TetrominoType::T: {
            return proto::TETRO_T;
        }
        case TetrominoType::Z: {
            return proto::TETRO_Z;
        }
        default: {
            return proto::TETRO_UNSPECIFIED;
        }
    }
}

std::shared_ptr<Tetromino> from_proto(proto::Tetro tetro) {
    switch (tetro) {
        case proto::TETRO_I: {
            return std::make_shared<TetroI>();
        }
        case proto::TETRO_J: {
            return std::make_shared<TetroJ>();
        }
        case proto::TETRO_L: {
            return std::make_shared<TetroL>();
        }
        case proto::TETRO_O: {
            return std::make_shared<TetroO>();
        }
        case proto::TETRO_S: {
            return std::make_shared<TetroS>();
        }
        case proto::TETRO_T: {
            return std::make_shared<TetroT>();
        }
        case proto::TETRO_Z: {
            return std::make_shared<TetroZ>();
        }
        default: {
            return nullptr;
        }
    }
}

std::shared_ptr<Tetromino> from_proto_with_data(proto::Tetro tetro, const std::vector<std::vector<int>> &data) {
    switch (tetro) {
        case proto::TETRO_I: {
            return std::make_shared<TetroI>(data);
        }
        case proto::TETRO_J: {
            return std::make_shared<TetroJ>(data);
        }
        case proto::TETRO_L: {
            return std::make_shared<TetroL>(data);
        }
        case proto::TETRO_O: {
            return std::make_shared<TetroO>(data);
        }
        case proto::TETRO_S: {
            return std::make_shared<TetroS>(data);
        }
        case proto::TETRO_T: {
            return std::make_shared<TetroT>(data);
        }
        case proto::TETRO_Z: {
            return std::make_shared<TetroZ>(data);
        }
        default: {
            return nullptr;
        }
    }
}

} // namespace game::tetro