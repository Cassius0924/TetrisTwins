#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <condition_variable>
#include <deque>
#include <unordered_set>

#include "tt/proto/room.pb.h"
#include "tt/tetrominos/tetromino.h"
#include "util/safe_deque.h"

namespace ui {

class Window;

} // namespace ui

/**
 * 游戏控制、状态、逻辑
 */
namespace game {

constexpr int k_PORT = 9898;

/**
 * 游戏是否正在运行
 */
extern bool is_running;

struct Room {
    int id;
    std::string ip;
    int port;
    std::string name;

    explicit Room(const proto::RoomMessage &room_message);

    bool operator==(const Room &other) const;
};

/**
 * 游戏房间列表
 */
extern std::unordered_set<Room> game_rooms;

/**
 * 被选择的游戏房间
 */
extern std::unique_ptr<Room> game_room;

/**
 * 是否已经创建房间
 */
extern bool is_created_room;

/**
 * 是否已经加入房间
 */
extern bool is_joined_room;

/**
 * 是否开始单人游戏
 */
extern bool is_single_started;

/**
 * 是否开始双人游戏
 */
extern bool is_double_started;

/**
 * 游戏开始互斥量
 */
extern std::mutex start_mutex;
extern std::mutex double_start_mutex;

/**
 * 游戏开始条件变量
 */
extern std::condition_variable start_cv;
extern std::condition_variable double_start_cv;

/**
 * 当前方块
 */
extern std::shared_ptr<tetro::Tetromino> cur_tetromino;

/**
 * 方块队列
 */
extern util::SafeDeque<std::shared_ptr<tetro::Tetromino>> tetro_queue;

/**
 * 游戏分数
 */
extern int score;

/**
 * 方块所在行
 */
extern int block_row;

/**
 * 方块所在列
 */
extern int block_col;

/**
 * 阴影块所在行
 */
extern int ghost_row;

/**
 * 主窗口
 */
extern ui::Window *main_win;

/**
 * 暂存窗口
 */
extern ui::Window *hold_win;

/**
 * 状态窗口
 */
extern ui::Window *status_win;

/**
 * 下一个方块窗口
 */
extern ui::Window *next_win;

/**
 * 信息窗口
 */
extern ui::Window *info_win;

/**
 * Next窗口是否需要更新
 */
extern bool is_next_win_updated;

/**
 * 俄罗斯方块堆
 */
struct TetroHeap {
    /**
     * 方块堆
     */
    std::vector<std::vector<int>> heap;

    /**
     * 是否更新
     */
    bool is_updated = false;
};

/**
 * 俄罗斯方块堆，用于储存沉底的方块，用方块颜色表示
 */
extern TetroHeap tetro_heap;

/**
 * 退出游戏
 */
void quit(int signal = 0);

/**
 * 初始化游戏
 */
void single_init();

/**
 * 左移方块
 */
void move_left();

/**
 * 右移方块
 */
void move_right();

/**
 * 下移方块
 */
void move_down();

/**
 * 硬降方块
 */
void hard_drop();

/**
 * 旋转方块
 */
void rotate();

/**
 * 将方块加入堆中
 * @param tetro: 方块
 * @param row: 方块泛区左上角行坐标
 * @param col: 方块泛区左上角列坐标
 */
void put_into_heap(std::shared_ptr<tetro::Tetromino> &tetro, int row, int col);

/**
 * 判断是否碰到堆
 * @param tetro: 方块
 * @param tetro_heap: 方块堆
 * @param next_row: 方块泛区下一步左上角行坐标
 * @param next_col: 方块泛区下一步左上角列坐标
 * @return 是否碰到堆
 */
bool is_touch_heap(const std::shared_ptr<tetro::Tetromino> &tetro, const TetroHeap &tetro_heap, int next_row,
                   int next_col);

/**
 * 判断是否碰到堆
 * @param tetro_data: 方块数据
 * @param heap: 方块堆
 * @param valid_offset: 有效坐标偏移量
 * @param next_row: 方块泛区下一步左上角行坐标
 * @param next_col: 方块泛区下一步左上角列坐标
 * @return 是否碰到堆
 */
bool is_touch_heap(const std::vector<std::vector<int>> &tetro_data, const std::vector<std::vector<int>> &heap,
                   tetro::ValidOffset valid_offset, int next_row, int next_col);

/**
 * 生成一个随机的俄罗斯方块
 * @return 俄罗斯方块
 */
std::shared_ptr<tetro::Tetromino> generate_tetromino();

/**
 * 移动方块到顶部中间
 * @param tetro: 俄罗斯方块
 * @param row: 方块泛区左上角行坐标
 * @param col: 方块泛区左上角列坐标
 */
void move_to_top_center(std::shared_ptr<tetro::Tetromino> &tetro, int &row, int &col);

/**
 * 计算方块的阴影块位置
 * @param tetro: 方块
 * @param tetro_heap: 方块堆
 * @param col: 方块泛区左上角行坐标
 * @param col: 方块泛区左上角列坐标
 * @return 阴影块泛区左上角行坐标
 */
int cal_ghost_tetromino_row(const std::shared_ptr<tetro::Tetromino> &tetro, const TetroHeap &tetro_heap, int row, int col);

/**
 * 检查方块堆是否触顶
 * @param row_air: 空行
 * @return 是否触顶
 */
bool is_touch_top(std::vector<int> row_air);

/**
 * 开始单人游戏
 */
void start_single_game();

/**
 * 开始双人游戏服务端
 */
void start_double_game_server();

/**
 * 开始双人游戏客户端
 */
void start_double_game_client();

}


template <>
struct std::hash<game::Room> {
    std::size_t operator()(const game::Room &room) const {
        return std::hash<int>()(room.id);
    }
};

#endif //TETRIS_GAME_H