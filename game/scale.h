#ifndef MAIN_MENU_PPM
#define MAIN_MENU_PPM

void scaled_char(unsigned short **screen, unsigned short scale, int x, int y, char ch, unsigned int fg_color, unsigned int bg_color);

void draw_scaled_string(unsigned short **screen, unsigned short scale, int x, int y, char *str, unsigned int fg_color, unsigned int bg_color);


#endif
