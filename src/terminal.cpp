#include <iostream>

#include "terminal.h"

#define CSI "\033["

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
