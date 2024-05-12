#include "tt/style.h"

const std::vector<std::string> ui::Style::style1 = {" ┌", "┐ ", " └", "┘ ", "──", " │", "│ "};
const std::vector<std::string> ui::Style::style2 = {" ╔", "╗ ", " ╚", "╝ ", "══", " ║", "║ "};
const std::vector<std::string> ui::Style::style3 = {" ╭", "╮ ", " ╰", "╯ ", "──", " │", "│ "};
const std::vector<std::string> ui::Style::style4 = {" ┏", "┓ ", " ┗", "┛ ", "━━", " ┃", "┃ "};

std::vector<std::string> ui::Style::cur_style;

std::string ui::Style::tl() {
    return cur_style[0];
}

std::string ui::Style::tr() {
    return cur_style[1];
}

std::string ui::Style::bl() {
    return cur_style[2];
}

std::string ui::Style::br() {
    return cur_style[3];
}

std::string ui::Style::h_edge() {
    return cur_style[4];
}

std::string ui::Style::vr_edge() {
    return cur_style[5];
}

std::string ui::Style::vl_edge() {
    return cur_style[6];
}

void ui::Style::set_style(int style_index) {
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


