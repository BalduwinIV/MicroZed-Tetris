#include "scale.h"
#include "tools/font.c"
#include "graphics.h"

void scaled_char(unsigned short **screen, unsigned short scale, int x, int y, char ch, unsigned int fg_color, unsigned int bg_color){

    if (ch == ' ') {
        draw_rect(screen, x, y, 10*scale, 14*scale, bg_color);
        return;
    }

    unsigned char wanted_ch;
    if (ch >= '0' && ch <= '9') {
        wanted_ch = ch - '0';
    } else if (ch >= 'A' && ch <= 'Z') {
        wanted_ch = ch - 'A' + 10;
    } else if (ch >= 'a' && ch <= 'z') {
        wanted_ch = ch - 'a' + 10;
    } else if (ch == '!') {
        wanted_ch = 36;
    } else if (ch == '?') {
        wanted_ch = 37;
    } else if (ch == '(') {
        wanted_ch = 38;
    } else if (ch == ')') {
        wanted_ch = 39;
    } else if (ch == '<') {
        wanted_ch = 40;
    } else if (ch == '>') {
        wanted_ch = 41;
    } else {
        wanted_ch = 42;
    }

    for (int font_y = 0; font_y < 14*scale; font_y+=scale) {
        for (int font_x = 0; font_x < 10; font_x++){
            unsigned short color = (characters[wanted_ch][font_y] & (0x8000>>font_x)) ? fg_color : bg_color;
            draw_rect(screen, x+font_x*scale, y+font_y, x+font_x*scale+scale, y+font_y+scale, color);
        }
    }
}

void draw_scaled_string(unsigned short **screen, unsigned short scale, int x, int y, char *str, unsigned int fg_color, unsigned int bg_color) {
    int ch_x_pos = x;
    for (int ch_i = 0; str[ch_i] != '\0'; ch_i+=scale) {
        scaled_char(screen, scale, ch_x_pos, y, str[ch_i], fg_color, bg_color);
        draw_rect(screen, ch_x_pos, y, 10*scale, 14*scale, bg_color);
        ch_x_pos += 14*scale;
    }
}