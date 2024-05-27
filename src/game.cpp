#include "tt/game.h"

#include <thread>

#include "tt/control.h"
#include "tt/menu.h"
#include "tt/net/dispatcher.h"
#include "tt/proto/next.pb.h"
#include "tt/remove.h"
#include "tt/tetrominos/define.h"
#include "tt/ui.h"
#include "tt/util/util.h"

namespace game {

bool is_running = true;
bool is_created_room = false;
bool is_joined_room = false;
bool is_single_started = false;
bool is_double_started = false;

std::unordered_set<Room> game_rooms;
std::unique_ptr<Room> game_room = nullptr;

std::mutex start_mutex;
std::mutex double_start_mutex;
std::condition_variable start_cv;
std::condition_variable double_start_cv;

int block_row;
int block_col;
int ghost_row;

ui::Window *main_win;
ui::Window *hold_win;
ui::Window *status_win;
ui::Window *next_win;
ui::Window *info_win;

std::atomic<bool> is_next_win_updated = true;
std::atomic<bool> is_position_updated = true;
std::atomic<bool> is_state_updated = true;

std::shared_ptr<tetro::Tetromino> cur_tetromino;
util::stl::SafeDeque<std::shared_ptr<tetro::Tetromino>> tetro_queue;

int score = 0;

TetroHeap tetro_heap;


Room::Room(const proto::RoomMessage &room_message)
    : id(room_message.id()), ip(room_message.ip()), port(room_message.port()), name(room_message.name()) {}

bool Room::operator==(const Room &other) const {
    return id == other.id;
}

void quit(int signal) {
    is_single_started = false;
    is_double_started = false;
    is_created_room = false;
    is_joined_room = false;
    menu::is_searching_game_rooms = false;
    menu::is_sending_game_room = false;
}

void move_left() {
    // 如果没有超出左边界
    if (block_col > 1 - cur_tetromino->get_valid_offset().left &&
        !is_touch_heap(cur_tetromino, tetro_heap, block_row, block_col - 1)) {
        block_col -= 1;
        ghost_row = cal_ghost_tetromino_row(cur_tetromino, tetro_heap, block_row, block_col);
        is_position_updated = true;
    }
}

void move_right() {
    // 如果没有超出右边界
    if (block_col < main_win->get_inner_width() - cur_tetromino->get_valid_offset().right &&
        !is_touch_heap(cur_tetromino, tetro_heap, block_row, block_col + 1)) {
        block_col += 1;
        ghost_row = cal_ghost_tetromino_row(cur_tetromino, tetro_heap, block_row, block_col);
        is_position_updated = true;
    }
}

void move_down() {
    auto [vleft, vright, vtop, vbottom] = cur_tetromino->get_valid_offset();
    // 判断是否碰到堆
    if (is_touch_heap(cur_tetromino, tetro_heap, block_row + 1, block_col)) {
        put_into_heap(cur_tetromino, block_row, block_col);

        // 尝试消行
        remove_full_rows(block_row - 1 + vtop, block_row - 1 + vbottom);

        // 判断是否触顶，触顶则退出游戏
        if (is_touch_top(row_air)) {
            quit(0);
            menu::refresh_top_win(true);
        }

        // 生成新的方块，加入到next队列
        cur_tetromino = std::move(tetro_queue.front());
        tetro_queue.pop_front();
        tetro_queue.emplace_back(generate_tetromino());
        move_to_top_center(cur_tetromino, block_row, block_col);
        ghost_row = cal_ghost_tetromino_row(cur_tetromino, tetro_heap, block_row, block_col);
        is_next_win_updated = true;

        return;
    }

    // 判断是否超出下边界
    if (block_row < main_win->get_inner_height() - vbottom) {
        block_row += 1;
        is_position_updated = true;
    }
}

void hard_drop() {
    // 硬降后再次按下 S 键，下降一格
    if (ctrl::is_hard_drop) {
        ctrl::is_hard_drop = false;
        return;
    }

    ctrl::is_hard_drop = true;
    // 硬降
    block_row = ghost_row;

    // 延迟 k_LOCK_DELAY_MS 毫秒后再次移动
    std::thread t([] {
        std::this_thread::sleep_for(ctrl::MS(ctrl::k_LOCK_DELAY_MS));
        if (!ctrl::is_hard_drop) {
            return;
        }
        move_down();
        ctrl::is_hard_drop = false;
    });
    t.detach();

    is_position_updated = true;
}

void rotate() {
    cur_tetromino->rotate();
    ghost_row = cal_ghost_tetromino_row(cur_tetromino, tetro_heap, block_row, block_col);
    is_state_updated = true;
}

bool is_touch_heap(const std::shared_ptr<tetro::Tetromino> &tetro, const TetroHeap &tetro_heap, int next_row,
                   int next_col) {
    return is_touch_heap(tetro->get_data(), tetro_heap.heap, tetro->get_valid_offset(), next_row, next_col);
}

bool is_touch_heap(const std::vector<std::vector<int>> &tetro_data, const std::vector<std::vector<int>> &heap,
                   tetro::ValidOffset valid_offset, int next_row, int next_col) {
    // 判断是否碰到堆或越界
    for (int i = next_row + valid_offset.top - 1; i <= next_row + valid_offset.bottom - 1; ++i) {
        for (int j = next_col + valid_offset.left - 1; j <= next_col + valid_offset.right - 1; ++j) {
            // 是否越下界
            if (i < 0 || i >= heap.size()) {
                return true;
            }
            // 是否碰到堆
            if (heap[i][j] != 0 && tetro_data[i - next_row + 1][j - next_col + 1] != 0) {
                return true;
            }
        }
    }
    return false;
}

void put_into_heap(std::shared_ptr<tetro::Tetromino> &tetro, int row, int col) {
    // 将方块加入堆中
    auto voffset = tetro->get_valid_offset();
    for (int i = voffset.top; i <= voffset.bottom; i++) {
        for (int j = voffset.left; j <= voffset.right; j++) {
            if ((*tetro)[i][j] == 0) {
                continue;
            }

            tetro_heap.heap[row - 1 + i][col - 1 + j] = static_cast<int>(tetro->color);
            dec_row_air(row - 1 + i);
        }
    }
    tetro_heap.is_updated = true;
}

std::shared_ptr<tetro::Tetromino> generate_tetromino() {
    // 生成随机数
    for (;;) {
        switch (util::math::random_int(0, 6)) {
            case 0:
                return std::make_unique<tetro::TetroI>();
            case 1:
                return std::make_unique<tetro::TetroJ>();
            case 2:
                return std::make_unique<tetro::TetroL>();
            case 3:
                return std::make_unique<tetro::TetroO>();
            case 4:
                return std::make_unique<tetro::TetroS>();
            case 5:
                return std::make_unique<tetro::TetroT>();
            case 6:
                return std::make_unique<tetro::TetroZ>();
            default:;
                return std::make_unique<tetro::TetroI>();
        }
    }
}

void move_to_top_center(std::shared_ptr<tetro::Tetromino> &tetro, int &row, int &col) {
    auto [vleft, vright, vtop, vbottom] = tetro->get_valid_offset();
    row = 1 - vtop;
    col = 5 - (vleft + (vright - vleft + 1) / 2 - 1);
    is_position_updated = true;
}

int cal_ghost_tetromino_row(const std::shared_ptr<tetro::Tetromino> &tetro, const TetroHeap &tetro_heap, int row,
                            int col) {
    int ghost_row = row;
    while (!is_touch_heap(tetro, tetro_heap, ghost_row + 1, col)) {
        ghost_row += 1;
    }
    return ghost_row;
}

bool is_touch_top(std::vector<int> row_air) {
    return row_air[0] < full_air_count;
}

} // namespace game