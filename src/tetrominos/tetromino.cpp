#include "tetrominos/tetromino.h"
#include "tetrominos/tetro_o.h"

using namespace game::tetro;

// IJLOSTZ
// 1234567
//std::unordered_map<int, Color> game::tetro::tetro_color{
//        {1, Color::Cyan},
//        {2, Color::Blue},
//        {3, Color::Orange},
//        {4, Color::Yellow},
//        {5, Color::Green},
//        {6, Color::Purple},
//        {7, Color::Red},
//};

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

TetrominoState Tetromino::NextState(game::tetro::TetrominoState state) {
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

void Tetromino::_rotate() {
    int cols = this->cols();
    int rows = this->rows();

    std::vector<std::vector<int>> new_tetro(cols, std::vector<int>(rows, 0));

    // 右转，顺时针
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            if (_raw_data[i][j] > 0) {
                new_tetro[j][cols - i - 1] = _raw_data[i][j];
            }
        }
    }

    _raw_data = new_tetro;
}

void Tetromino::rotate() {
    _state = NextState(_state);

    // TODO: 优化
    // 如果对象类型是TetroO
    if (typeid(*this) == typeid(TetroO)) {
        return;
    }

    _rotate();
    _calibrate();
}

void Tetromino::_calibrate() {
    int cols = this->cols();
    int rows = this->rows();

    // 清空数据
    _data.clear();
    _data.resize(rows, std::vector<int>(cols, 0));
    auto offset = _kick_table[static_cast<int>(_state)][0];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (_raw_data[i][j] > 0) {
                // i是y轴，j是x轴，由于坐标轴原点在左上角，所以 i + y，j - x
                int nx = i + offset.y;
                int ny = j - offset.x;
                if (nx >= 0 && ny >= 0 && nx < rows && ny < cols) {
                    _data[nx][ny] = _raw_data[i][j];
                }
            }
        }
    }
}