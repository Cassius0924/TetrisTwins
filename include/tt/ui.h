#ifndef TETRIS_TWINS_UI_H
#define TETRIS_TWINS_UI_H

#include <list>
#include <memory>
#include <stack>
#include <string>
#include <variant>

#include "tt/game.h"
#include "tt/tetrominos/tetromino.h"

// 0	1	2	3	4	5	6	7	8	9	A	B	C	D	E	F
// U+250x	─	━	│	┃	┄	┅	┆	┇	┈	┉	┊	┋	┌	┍	┎	┏
// U+251x	┐	┑	┒	┓	└	┕	┖	┗	┘	┙	┚	┛	├	┝	┞	┟
// U+252x	┠	┡	┢	┣	┤	┥	┦	┧	┨	┩	┪	┫	┬	┭	┮	┯
// U+253x	┰	┱	┲	┳	┴	┵	┶	┷	┸	┹	┺	┻	┼	┽	┾	┿
// U+254x	╀	╁	╂	╃	╄	╅	╆	╇	╈	╉	╊	╋	╌	╍	╎	╏
// U+255x	═	║	╒	╓	╔	╕	╖	╗	╘	╙	╚	╛	╜	╝	╞	╟
// U+256x	╠	╡	╢	╣	╤	╥	╦	╧	╨	╩	╪	╫	╬	╭	╮	╯
// U+257x	╰	╱	╲	╳	╴	╵	╶	╷	╸	╹	╺	╻	╼	╽	╾	╿
// Notes
// 1.^ As of Unicode version 15.1

namespace game {

struct TetroHeap;

} // namespace game

/**
 * 绘图
 *
 */
namespace ui {
/**
 * 将方块坐标转换为行坐标
 * @param block: 方块坐标
 * @return 行坐标
 */
inline int block_to_col(int block) {
    return block * 2 - 1;
}

struct MenuItem {
    std::string text;
    int arow;
    int acol;
    std::function<void()> action;
};

struct TextItem {
    std::variant<std::string, std::function<std::string()>> text;
    int arow;
    int acol;
};

/**
 * UI 窗口类
 */
class Window {
private:
    int _left;
    int _top;
    int _width;
    int _height;
    std::string _title;

public:
    // TODO: 封装一个循环链表
    /**
     * 菜单项列表
     */
    std::list<MenuItem> menu_items;
    std::list<MenuItem>::iterator selected_menu_item;

    /**
     * 文本项列表
     */
    std::list<TextItem> text_items;

public:
    /**
     * @param left: 窗口左侧位置
     * @param top: 窗口顶部位置
     * @param width: 窗口宽度（单位：block）
     * @param height: 窗口高度
     * @param title: 窗口标题
     */
    Window(int left, int top, int width, int height, std::string title = "");

    ~Window();

    /**
     * 绘制窗口
     */
    void draw() const;

    /**
     * 绘制菜单
     */
    void draw_menu_items() const;

    /**
     * 绘制文本项
     */
    void draw_text_items() const;

    /**
     * 在此窗口的相对位置显示内容
     * @param row: 相对行坐标
     * @param col: 相对列坐标
     * @param text: 显示的内容
     */
    void display(int row, int col, const std::string &text) const;

    /**
     * 根据传入的相对行坐标，获取绝对行坐标
     * @param row: 行坐标
     * @return 绝对行坐标
     */
    inline int absolute_row(int row) const {
        return _top + row;
    }

    /**
     * 根据传入的相对列坐标，获取绝对列坐标
     * @param col: 列坐标
     * @return 绝对列坐标
     */
    inline int absolute_col(int col) const {
        return _left * 2 + col;
    }

    /**
     * 获取窗口宽度
     * @return 窗口宽度
     */
    int get_width() const;

    /**
     * 获取窗口高度
     * @return 窗口高度
     */
    int get_height() const;

    /**
     * 获取窗口内部宽度
     * @return 窗口内部宽度
     */
    int get_inner_width() const;

    /**
     * 获取窗口内部高度
     * @return 窗口内部高度
     */
    int get_inner_height() const;

    /**
     * 注册一个菜单项
     * @param row: 行坐标
     * @param col: 列坐标
     * @param text: 菜单项文本
     * @param action: 菜单项动作
     */
    inline void register_menu_item(int row, int col, const std::string &text,
                                   const std::function<void()> &action = nullptr) {
        menu_items.emplace_back(MenuItem{text, absolute_row(row), absolute_col(col), action});
        if (menu_items.size() == 1) {
            selected_menu_item = menu_items.begin();
        }
    }

    /**
     * 注册一个文本项
     * @param row: 行坐标
     * @param col: 列坐标
     * @param text: 显示的内容
     */
    inline void register_text_item(int row, int col,
                                   const std::variant<std::string, std::function<std::string()>> &text) {
        text_items.emplace_back(TextItem{text, absolute_row(row), absolute_col(col)});
    }

    /**
     * 创建Window对象shared_ptr智能指针
     */
    inline static std::shared_ptr<Window> createPtr(int left, int top, int width, int height,
                                                    const std::string &title = "") {
        return std::make_shared<Window>(left, top, width, height, title);
    };

    /**
     * 处理键盘事件
     */
    static void handleKeyEvent(char command);
};

using WindowPtr = std::shared_ptr<Window>;

/**
 * 绘制俄罗斯方块
 * @param tetro: 俄罗斯方块
 * @param left: 左侧位置
 * @param top: 顶部位置
 */
void tetromino(std::shared_ptr<game::tetro::Tetromino> tetro, int left, int top);

/**
 * 绘制俄罗斯方块堆
 * @param tetro_heap: 俄罗斯方块堆
 * @param win: 窗口
 */
void tetro_heap(const game::TetroHeap &tetro_heap, Window *win);

/**
 * 绘制方块的阴影块
 * @param tetro: 俄罗斯方块
 * @param left: 左侧位置
 * @param top: 顶部位置
 */
void ghost_tetromino(std::shared_ptr<game::tetro::Tetromino> tetro, int left, int top);

/**
 * 绘制俄罗斯方块队列
 * @param tetro_queue: 俄罗斯方块队列
 * @param win: 窗口
 */
void tetro_queue(const std::deque<std::shared_ptr<game::tetro::Tetromino>> &tetro_queue, Window *win);
}

#endif //TETRIS_TWINS_UI_H
