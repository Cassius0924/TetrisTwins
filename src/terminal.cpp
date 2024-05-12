#include "tt/terminal.h"

#include <iostream>

#define CSI "\033["

struct BitField {
    unsigned int a : 1; // a 占用 1 位
    unsigned int b : 3; // b 占用 3 位
    unsigned int c : 4; // c 占用 4 位
};

void term::move_to(int row, int col) {
    std::cout << CSI << row << ';' << col << 'H';
}

void term::set_fore_color(int id) {
    std::cout << CSI << "38;5;" << id << 'm';
}

void term::set_back_color(int id) {
    std::cout << CSI << "48;5;" << id << 'm';
}

void term::clean_screen() {
    std::cout << CSI << "2J";
}

void term::reset_color() {
    std::cout << CSI << "0m";
}

void term::hide_cursor() {
    std::cout << CSI << "?25l";
}

void term::show_cursor() {
    std::cout << CSI << "?25H";
}
