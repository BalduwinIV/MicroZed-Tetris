#ifndef FONT_H
#define FONT_H

#define FONT_SIZE   44

void draw_string(unsigned short **screen, int x, int y, char *str, unsigned int fg_color, unsigned int bg_color);
void draw_font_character(unsigned short **screen, int x, int y, unsigned char ch_i, unsigned int fg_color, unsigned int bg_color);

#endif
