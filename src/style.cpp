#include "style.h"

const std::vector<std::string> draw::Style::style1 = {" ┌", "┐ ", " └", "┘ ", "──", " │", "│ "};
const std::vector<std::string> draw::Style::style2 = {" ╔", "╗ ", " ╚", "╝ ", "══", " ║", "║ "};
const std::vector<std::string> draw::Style::style3 = {" ╭", "╮ ", " ╰", "╯ ", "──", " │", "│ "};
const std::vector<std::string> draw::Style::style4 = {" ┏", "┓ ", " ┗", "┛ ", "━━", " ┃", "┃ "};

std::vector<std::string> draw::Style::cur_style;

std::string draw::Style::tl() {
    return cur_style[0];
}

std::string draw::Style::tr() {
    return cur_style[1];
}

std::string draw::Style::bl() {
    return cur_style[2];
}

std::string draw::Style::br() {
    return cur_style[3];
}

std::string draw::Style::h_edge() {
    return cur_style[4];
}

std::string draw::Style::vr_edge() {
    return cur_style[5];
}

std::string draw::Style::vl_edge() {
    return cur_style[6];
}

void draw::Style::set_style(int style_index) {
    switch (style_index) {
        case 1:
            cur_style = style1;
            break;
        case 2:
            cur_style = style2;
            break;
        case 3:
            cur_style = style3;
            break;
        case 4:
            cur_style = style4;
            break;
        default:
            cur_style = style3;
            break;
    }
}


