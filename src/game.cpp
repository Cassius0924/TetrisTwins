#include "tt/game.h"

#include <iostream>
#include <thread>

#include "tt/control.h"
#include "tt/menu.h"
#include "tt/net/communicator.h"
#include "tt/net/dispatcher.h"
#include "tt/net/packer.h"
#include "tt/net/tcp_client.h"
#include "tt/net/tcp_server.h"
#include "tt/proto/next.pb.h"
#include "tt/proto/signal.pb.h"
#include "tt/proto/tetrominos.pb.h"
#include "tt/remove.h"
#include "tt/terminal.h"
#include "tt/tetrominos/define.h"
#include "tt/ui.h"
#include "tt/util/util.h"

using namespace std::chrono_literals;

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

std::shared_ptr<tetro::Tetromino> cur_tetromino;
util::SafeDeque<std::shared_ptr<tetro::Tetromino>> tetro_queue;

int score = 0;

TetroHeap tetro_heap;

bool is_next_win_updated;

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
        !is_touch_heap(cur_tetromino, block_row, block_col - 1)) {
        block_col -= 1;
        ghost_row = cal_ghost_tetromino_row(cur_tetromino, block_row, block_col);
    }
}

void move_right() {
    // 如果没有超出右边界
    if (block_col < main_win->get_inner_width() - cur_tetromino->get_valid_offset().right &&
        !is_touch_heap(cur_tetromino, block_row, block_col + 1)) {
        block_col += 1;
        ghost_row = cal_ghost_tetromino_row(cur_tetromino, block_row, block_col);
    }
}

void move_down() {
    // 判断是否碰到堆
    if (touch_heap(cur_tetromino, block_row, block_col, block_row + 1, block_col)) {
        return;
    }

    // 判断是否超出下边界
    if (block_row < main_win->get_inner_height() - cur_tetromino->get_valid_offset().bottom) {
        block_row += 1;
    }
}

void rotate() {
    cur_tetromino->rotate();
    ghost_row = cal_ghost_tetromino_row(cur_tetromino, block_row, block_col);
}

bool is_touch_heap(const std::shared_ptr<tetro::Tetromino> &tetro, int next_row, int next_col) {
    return is_touch_heap(tetro->get_data(), tetro->get_valid_offset(), next_row, next_col);
}

bool is_touch_heap(const std::vector<std::vector<int>> &tetro_data, tetro::ValidOffset valid_offset, int next_row,
                   int next_col) {
    // 判断是否碰到堆或越界
    for (int i = next_row + valid_offset.top - 1; i <= next_row + valid_offset.bottom - 1; ++i) {
        for (int j = next_col + valid_offset.left - 1; j <= next_col + valid_offset.right - 1; ++j) {
            // 是否越下界
            if (i < 0 || i >= tetro_heap.heap.size()) {
                return true;
            }
            // 是否碰到堆
            if (tetro_heap.heap[i][j] != 0 && tetro_data[i - next_row + 1][j - next_col + 1] != 0) {
                return true;
            }
        }
    }
    return false;
}

bool touch_heap(std::shared_ptr<tetro::Tetromino> &tetro, int row, int col, int next_row, int next_col) {
    // 将方块加入堆中
    if (!is_touch_heap(tetro, next_row, next_col)) {
        return false;
    }
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

    // 尝试消行
    remove_full_rows(row - 1 + voffset.top, row - 1 + voffset.bottom);

    // 判断是否触顶
    if (check_touch_top(row_air)) {
        quit(0);
        menu::refresh_top_win(true);
    }

    // 生成新的的俄罗斯方块
    cur_tetromino = std::move(tetro_queue.front());
    tetro_queue.pop_front();
    tetro_queue.emplace_back(generate_tetromino());
    move_to_top_center(cur_tetromino);

    // FIXME: 发送新方块给对端

    is_next_win_updated = true;

    ui::tetro_queue(tetro_queue, next_win);

    return true;
}

std::shared_ptr<tetro::Tetromino> generate_tetromino() {
    // 生成随机数
    for (;;) {
        switch (util::random_int(0, 6)) {
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
            default:
                continue;
        }
    }
}

void move_to_top_center(std::shared_ptr<tetro::Tetromino> &tetro) {
    auto voffset = tetro->get_valid_offset();
    block_row = 1 - voffset.top;
    block_col = 5 - (voffset.left + (voffset.right - voffset.left + 1) / 2 - 1);
    ghost_row = cal_ghost_tetromino_row(cur_tetromino, block_row, block_col);
}

int cal_ghost_tetromino_row(const std::shared_ptr<tetro::Tetromino> &tetro, int row, int col) {
    while (!is_touch_heap(tetro, row + 1, col)) {
        row += 1;
    }
    return row;
}

bool check_touch_top(std::vector<int> row_air) {
    return row_air[0] < full_air_count;
}

void single_init() {
    tetro_queue.resize(5);

    main_win = new ui::Window(10, 1, 12, 22, "TetrisTwins");
    hold_win = new ui::Window(1, 1, 9, 6, "Hold");
    status_win = new ui::Window(1, 7, 9, 16, "Status");
    next_win = new ui::Window(22, 1, 8, 18, "Next");
    info_win = new ui::Window(22, 19, 8, 4, "Info");

    hold_win->draw();
    status_win->draw();
    info_win->draw();

    tetro_heap.heap =
        std::vector<std::vector<int>>(main_win->get_inner_height(), std::vector<int>(main_win->get_inner_width(), 0));

    // 生成一个随机的俄罗斯方块
    for (auto &tetro : tetro_queue) {
        tetro = generate_tetromino();
    }
    cur_tetromino = generate_tetromino();
    move_to_top_center(cur_tetromino);

    full_air_count = main_win->get_inner_width();
    row_air = std::vector<int>(main_win->get_height() - 2, full_air_count);

    is_next_win_updated = true;

    // 创建方块重力
    ctrl::start_gravity_thread();
}

void start_single_game() {
    // 注册FPS text
    status_win->register_text_item(3, ui::block_to_col(2), [] {
        return "FPS: " + std::to_string(util::fps());
    });
    // 注册分数 text
    status_win->register_text_item(4, ui::block_to_col(2), [] {
        return "Score: " + std::to_string(score);
    });

    while (is_single_started) {
        if (is_next_win_updated) {
            next_win->draw();
            ui::tetro_queue(tetro_queue, next_win);
            is_next_win_updated = false;
        }

        // 绘制窗口
        main_win->draw();

        // 绘制文本项
        status_win->draw_text_items();

        // 显示阴影块
        ui::ghost_tetromino(cur_tetromino, main_win->absolute_col(ui::block_to_col(block_col)),
                            main_win->absolute_row(ghost_row));
        // 显示正在下落的俄罗斯方块
        ui::tetromino(cur_tetromino, main_win->absolute_col(ui::block_to_col(block_col)),
                      main_win->absolute_row(block_row));

        // 显示方块堆
        ui::tetro_heap(tetro_heap, main_win);

        term::reset_color();
        std::cout << std::flush;
        std::this_thread::sleep_for(100ms);
    }
}

void double_server_init(net::Communicator &commu) {
    // 初始化，生成next方块队列，双端同步
    proto::NextQueueMessage next_queue_message;
    auto next_queue = next_queue_message.mutable_queue();
    next_queue->Reserve(6);
    for (auto &tetro : tetro_queue) {
        tetro = generate_tetromino();
        next_queue->Add(tetro::to_proto(tetro));
    }
    commu.send(net::pack_message(next_queue_message));
    is_next_win_updated = true;

    // 同步当前方块信息
    cur_tetromino = generate_tetromino();
    proto::TetroMessage tetro_message;
    tetro_message.set_tetro(to_proto(cur_tetromino));
    commu.send(net::pack_message(tetro_message));
    move_to_top_center(cur_tetromino);

    ctrl::start_gravity_thread();
}

void double_client_init() {}

void double_init() {
    // 多一个next方块用于缓存，用于抵消网络延迟
    tetro_queue.resize(6);

    main_win = new ui::Window(10, 1, 12, 22, "Your TetrisTwins");
    hold_win = new ui::Window(1, 1, 9, 6, "Hold");
    status_win = new ui::Window(1, 7, 9, 16, "Status");
    next_win = new ui::Window(22, 1, 8, 18, "Next");
    info_win = new ui::Window(22, 19, 8, 4, "Info");

    hold_win->draw();
    status_win->draw();
    info_win->draw();

    tetro_heap.heap =
        std::vector<std::vector<int>>(main_win->get_inner_height(), std::vector<int>(main_win->get_inner_width(), 0));

    full_air_count = main_win->get_inner_width();
    row_air = std::vector<int>(main_win->get_height() - 2, full_air_count);
}

void signal_message_callback(std::unique_ptr<proto::SignalMessage> message, bool &flag,
                             std::shared_ptr<tetro::Tetromino> &tetro) {
    // flag用于标识是否传来的是START信号，tetro用于传递新方块
    switch (message->signal()) {
        case proto::SIGNAL_START: {
            flag = true;
            break;
        }
        case proto::SIGNAL_NEXT_TETRO_REQUEST: {
            // 生成新方块
            tetro = generate_tetromino();
            break;
        }
        case proto::SIGNAL_QUIT:
        case proto::SIGNAL_UNSPECIFIED:
        default: {
            quit();
            menu::pop_window(2);
            flag = false;
        }
    }
}

void next_queue_message_callback(std::unique_ptr<proto::NextQueueMessage> message,
                                 util::SafeDeque<std::shared_ptr<tetro::Tetromino>> &queue, bool &updated) {
    for (int i = 0; i < queue.size(); ++i) {
        queue[i] = tetro::from_proto(message->queue(i));
    }
    updated = true;
}

void next_tetro_message_callback(std::unique_ptr<proto::NextTetroMessage> message,
                                 util::SafeDeque<std::shared_ptr<tetro::Tetromino>> &queue) {
    queue.push_back(tetro::from_proto(message->tetro()));
}

void tetro_message_callback(std::unique_ptr<proto::TetroMessage> message,
                            std::shared_ptr<tetro::Tetromino> &cur_tetro) {
    cur_tetro = tetro::from_proto(message->tetro());
    move_to_top_center(cur_tetro);
    // 创建方块重力
    ctrl::start_gravity_thread();
}

void start_double_game(net::Communicator &commu) {
    status_win->register_text_item(3, ui::block_to_col(2), [] {
        return "FPS: " + std::to_string(util::fps());
    });
    status_win->register_text_item(4, ui::block_to_col(2), [] {
        return "Score: " + std::to_string(score);
    });

    // FIXME: 使用智能指针
    const ui::Window *peer_main_win = new ui::Window(40, 1, 12, 22, "Peer TetrisTwins");
    const ui::Window *peer_hold_win = new ui::Window(31, 1, 9, 6, "Hold");
    const ui::Window *peer_status_win = new ui::Window(31, 7, 9, 16, "Status");
    const ui::Window *peer_next_win = new ui::Window(52, 1, 8, 18, "Next");
    const ui::Window *peer_info_win = new ui::Window(52, 19, 8, 4, "Info");

    peer_main_win->draw();
    peer_hold_win->draw();
    peer_status_win->draw();
    peer_next_win->draw();
    peer_info_win->draw();

    std::shared_ptr<tetro::Tetromino> tetro_ptr = nullptr;

    net::Dispatcher dispatcher;
    // 注册消息处理回调函数
    // 信号消息处理
    dispatcher.register_message_callback<proto::SignalMessage>(
        std::bind(signal_message_callback, std::placeholders::_1, std::ref(is_double_started), std::ref(tetro_ptr)));
    // Next方块队列初始消息处理
    dispatcher.register_message_callback<proto::NextQueueMessage>(std::bind(
        next_queue_message_callback, std::placeholders::_1, std::ref(tetro_queue), std::ref(is_next_win_updated)));
    // 新Next方块消息处理
    dispatcher.register_message_callback<proto::NextTetroMessage>(
        std::bind(next_tetro_message_callback, std::placeholders::_1, std::ref(tetro_queue)));
    // 当前方块消息处理
    dispatcher.register_message_callback<proto::TetroMessage>(
        std::bind(tetro_message_callback, std::placeholders::_1, std::ref(cur_tetromino)));

    while (is_double_started) {
        if (is_next_win_updated) {
            next_win->draw();
            ui::tetro_queue(tetro_queue, next_win);
            is_next_win_updated = false;
        }

        constexpr int k_BUFFER_SIZE = 1024;
        // 同步对端游戏状态
        std::string total_buffer;
        while (commu.has_data_read()) {
            auto [data, len] = commu.recv(k_BUFFER_SIZE);
            if (len < 0 && total_buffer.empty()) {
                continue;
            }
            total_buffer.append(data);
            while (!total_buffer.empty()) {
                std::string pack_data = net::try_extract_one_pack_data(total_buffer);
                if (pack_data.empty()) {
                    break;
                }
                auto message = net::unpack_message(pack_data);

                tetro_ptr = nullptr;
                dispatcher.on_message(std::move(message));
                if (!is_double_started) {
                    return;
                }
                if (tetro_ptr != nullptr) {
                    // 新方块入队
                    tetro_queue.push_back(tetro_ptr);
                    // 发送新方块给对端
                    proto::NextTetroMessage next_tetro_message;
                    next_tetro_message.set_tetro(tetro::to_proto(tetro_ptr));
                    commu.send(net::pack_message(next_tetro_message));
                }
            }
        }

        // 绘制窗口
        main_win->draw();

        // 绘制文本项
        status_win->draw_text_items();

        // 显示阴影块
        ui::ghost_tetromino(cur_tetromino, main_win->absolute_col(ui::block_to_col(block_col)),
                            main_win->absolute_row(ghost_row));
        // 显示正在下落的俄罗斯方块
        ui::tetromino(cur_tetromino, main_win->absolute_col(ui::block_to_col(block_col)),
                      main_win->absolute_row(block_row));

        // 显示方块堆
        ui::tetro_heap(tetro_heap, main_win);

        // 发送方块位置信息给对端
        // commu.send();
        // 发送tetro_heap变化给对端

        term::reset_color();
        std::cout << std::flush;
        std::this_thread::sleep_for(100ms);
    }

    // 发送退出消息
    proto::SignalMessage signal_message;
    signal_message.set_signal(proto::SIGNAL_QUIT);
    commu.send(net::pack_message(signal_message));
}

void start_double_game_server() {
    // 创建TCP服务器
    net::TcpServer server(k_PORT);
    server.start();
    while (is_created_room) {
        if (server.has_connection_request()) {
            break;
        }
    }
    if (!is_created_room) {
        return;
    }
    server.accept();

    // 显示对手信息
    menu::window_stack.top()->display(8, ui::block_to_col(2), "对手:" + server.get_client_address());

    // TODO: 配置 Cmake 自动生成protobuf代码
    while (is_created_room) {
        std::unique_lock<std::mutex> lock(double_start_mutex);
        double_start_cv.wait(lock, [] {
            return is_double_started;
        });

        // 向客户端发送开始信号
        proto::SignalMessage signal_message;
        signal_message.set_signal(proto::SIGNAL_START);

        server.send(net::pack_message(signal_message));

        // 开始双人游戏
        double_init();
        double_server_init(server);
        start_double_game(server);
    }
}

void start_double_game_client() {
    if (game_room == nullptr) {
        exit(-1);
    }
    // 创建TCP客户端
    net::TcpClient client(game_room->ip, game_room->port);
    client.connect();

    net::Dispatcher dispatcher;
    // 注册消息处理回调函数
    dispatcher.register_message_callback<proto::SignalMessage>(std::bind(
        signal_message_callback, std::placeholders::_1, std::ref(is_double_started), std::ref(cur_tetromino)));

    // TODO: 循环条件控制
    while (is_joined_room) {
        auto [data, len] = client.recv(1024);
        if (len < 0) {
            continue;
        }
        std::unique_ptr<google::protobuf::Message> message = net::unpack_message(data);

        dispatcher.on_message(std::move(message));
        if (!is_double_started) {
            continue;
        }

        // 开始双人游戏
        double_init();
        double_client_init();
        start_double_game(client);
    }
}

} // namespace game