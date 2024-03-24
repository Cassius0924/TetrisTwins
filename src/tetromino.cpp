#include "tetromino.h"

// IJLOSTZ
// 1234567
game::Tetromino game::I{
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
};

game::Tetromino game::J{
        {2, 0, 0},
        {2, 2, 2},
        {0, 0, 0},
};

game::Tetromino game::L{
        {0, 0, 2},
        {2, 2, 2},
        {0, 0, 0},
};

game::Tetromino game::O{
        {0, 3, 3},
        {0, 3, 3},
        {0, 0, 0},
};

game::Tetromino game::S{
        {0, 4, 4},
        {4, 4, 0},
        {0, 0, 0},
};

game::Tetromino game::T{
        {0, 5, 0},
        {5, 5, 5},
        {0, 0, 0},
};

game::Tetromino game::Z{
        {5, 5, 0},
        {0, 5, 5},
        {0, 0, 0},
};

std::unordered_map<int,Color> game::tetro_color{
        {1, Color::Cyan},
        {2, Color::Blue},
        {3, Color::Orange},
        {4, Color::Yellow},
        {5, Color::Green},
        {6, Color::Purple},
        {7, Color::Red},
};

game::Tetromino game::rotate(game::Tetromino &t) {
    game::Tetromino result(t.size(), std::vector<int>(t.size(), 0));

    // t[i][j] = t'[j][t.size() - i - 1]
    for (int i = 0; i < t.size(); i++) {
        for (int j = 0; j < t[0].size(); j++) {
            if (t[i][j] > 0) {
                result[j][t.size() - i - 1] = t[i][j];
            }
        }
    }

    return std::move(result);
}
