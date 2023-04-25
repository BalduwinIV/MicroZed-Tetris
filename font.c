#include "font.h"

/* Characters array. */
/* [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
 *   A, B, C, D, E, F, G, H, I, J,
 *   K, L, M, N, O, P, Q, R, S, T,
 *   U, V, W, X, Y, Z] */
static unsigned int characters[36][14] {
    ...,
    /*
     * |  ******  |
     * | ******** |
     * |***    ***|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |***    ***|
     * | ******** |
     * |  ******  |
     * */
    {
        0x3f00,
        0x7f80,
        0xe1c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xe1c0,
        0x7f80,
        0x3f00
    },
    ...
};

/*
 * @param screen
 * @param x
 * @param y
 * @param ch        ASCII char code.
 * @param fg_color  character foreground color
 * @param bg_color  character background color;
 * */
static void draw_char(unsigned int **screen, int x, int y, char ch, unsigned short fg_color, unsigned short bg_color) {
    unsigned char wanted_ch = ch-65;
    int font_x;
    for (int font_y = 0; font_y < 14; font_y++) {
        font_x = x;
        if (characters[wanted_ch][y+font_y] & 0x8000) screen[y][font_x++] = fg_color else screen[y][font_x++] = bg_color;
        if (characters[wanted_ch][y+font_y] & 0x4000) ...
        if (characters[wanted_ch][y+font_y] & 0x2000) ...
        if (characters[wanted_ch][y+font_y] & 0x1000) ...
        if (characters[wanted_ch][y+font_y] & 0x0800) ...
        if (characters[wanted_ch][y+font_y] & 0x0400) ...
        if (characters[wanted_ch][y+font_y] & 0x0200) ...
        if (characters[wanted_ch][y+font_y] & 0x0100) ...
        if (characters[wanted_ch][y+font_y] & 0x0080) ...
        if (characters[wanted_ch][y+font_y] & 0x0040) ...
    }
}

void draw_string(unsigned int **screen, int x, int y, char *str, unsigned short fg_color, unsigned short bg_color) {
    for (int ch_i = 0; str[ch_i] != '\0'; ch_i++) {
        draw_char(screen, x, y, str[ch_i], fg_color, bg_color);
        x += 14;
    }
}

