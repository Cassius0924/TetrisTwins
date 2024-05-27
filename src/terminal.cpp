#include "tt/terminal.h"

namespace term {

constexpr const char* k_CSI = "\033[";

void move_to(int row, int col) {
    std::cout << k_CSI << row << ';' << col << 'H';
}

void set_fore_color(int id) {
    std::cout << k_CSI << "38;5;" << id << 'm';
}

void set_back_color(int id) {
    std::cout << k_CSI << "48;5;" << id << 'm';
}

void clean_screen() {
    std::cout << k_CSI << "2J";
}

void reset_color() {
    std::cout << k_CSI << "0m";
}

void hide_cursor() {
    std::cout << k_CSI << "?25l";
}

void show_cursor() {
    std::cout << k_CSI << "?25H";
}

} // namespace term