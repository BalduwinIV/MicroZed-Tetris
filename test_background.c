#include <stdio.h>
#include <stdlib.h>

#include "game/image_graphics.h"
#include "game/tools/colors.h"
#include "game/tools/font.h"
#include "game/graphics.h"

void draw_rect(unsigned short **screen, int x, int y, int dest_x, int dest_y, int color) {
    for (int y_temp = y; y_temp <= dest_y; y_temp++) {
        for (int x_temp = x; x_temp <= dest_x; x_temp++) {
            screen[y_temp][x_temp] = color;
        }
    }
}

int main() {
    unsigned short **screen = (unsigned short **)malloc(320 * sizeof(unsigned short *));
    for (int y = 0; y < 320; y++) {
        screen[y] = (unsigned short *)malloc(480 * sizeof(unsigned short));
        for (int x = 0; x < 480; x++) {
            screen[y][x] = 0x0000;
        }
    }

    unsigned int grey = GREY_RGB565;
    unsigned int blue = BORDER_RGB565;
    unsigned int white = WHITE_RGB565;
    unsigned int black = BLACK_RGB565;

    /* Statistics */
        /* Grey border */
    draw_rect(screen, 3, 0, 124, 2, grey);
    draw_rect(screen, 0, 3, 2, 316, grey);
    draw_rect(screen, 3, 317, 124, 319, grey);
    draw_rect(screen, 125, 3, 127, 316, grey);
    draw_rect(screen, 3, 3, 5, 5, grey);
    draw_rect(screen, 3, 314, 5, 316, grey);
    draw_rect(screen, 122, 3, 124, 5, grey);
    draw_rect(screen, 122, 314, 124, 316, grey);

        /* Blue border */
    draw_rect(screen, 6, 6, 121, 8, blue);
    draw_rect(screen, 6, 9, 8, 310, blue);
    draw_rect(screen, 119, 9, 121, 310, blue);
    draw_rect(screen, 6, 311, 121, 313, blue);

    draw_block(screen, 22, 30, GREEN_BLOCK_TYPE);
    draw_block(screen, 22, 70, RED_BLOCK_TYPE);
    draw_block(screen, 22, 110, PURPLE_BLOCK_TYPE);
    draw_block(screen, 22, 150, YELLOW_BLOCK_TYPE);
    draw_block(screen, 22, 190, DARKBLUE_BLOCK_TYPE);
    draw_block(screen, 22, 230, ORANGE_BLOCK_TYPE);
    draw_block(screen, 22, 270, BLUE_BLOCK_TYPE);
    /* End statistics */

    /* Game field */
        /* Grey border */
    draw_rect(screen, 134, 0, 345, 2, grey);
    draw_rect(screen, 346, 3, 348, 316, grey);
    draw_rect(screen, 131, 3, 133, 316, grey);
    draw_rect(screen, 134, 317, 345, 319, grey);
    draw_rect(screen, 134, 3, 136, 5, grey);
    draw_rect(screen, 134, 314, 136, 316, grey);
    draw_rect(screen, 343, 314, 345, 316, grey);
    draw_rect(screen, 343, 3, 345, 5, grey);
        /* Blue border */
    draw_rect(screen, 137, 6, 342, 8, blue);
    draw_rect(screen, 340, 9, 342, 310, blue);
    draw_rect(screen, 137, 311, 342, 313, blue);
    draw_rect(screen, 137, 6, 139, 310, blue);
    /* End game field */

    /* Score */
        /* Grey border */
    draw_rect(screen, 355, 0, 473, 2, grey);
    draw_rect(screen, 474, 3, 476, 121, grey);
    draw_rect(screen, 355, 122, 473, 124, grey);
    draw_rect(screen, 352, 3, 354, 121, grey);
    draw_rect(screen, 355, 3, 357, 5, grey);
    draw_rect(screen, 471, 3, 473, 5, grey);
    draw_rect(screen, 471, 119, 473, 121, grey);
    draw_rect(screen, 355, 119, 357, 121, grey);
        /* Blue border */
    draw_rect(screen, 358, 6, 470, 8, blue);
    draw_rect(screen, 468, 9, 470, 115, blue);
    draw_rect(screen, 358, 116, 470, 118, blue);
    draw_rect(screen, 358, 9, 360, 115, blue);

    char score_label[] = "SCORE";
    draw_string(screen, 372, 18, score_label, white, black);
    
    char best_label[] = "BEST";
    draw_string(screen, 372, 73, best_label, white, black);
    /* End score */

    /* Next element */
        /* Grey border */
    draw_rect(screen, 355, 128, 473, 130, grey);
    draw_rect(screen, 474, 131, 476, 198, grey);
    draw_rect(screen, 355, 199, 473, 201, grey);
    draw_rect(screen, 352, 131, 354, 198, grey);
    draw_rect(screen, 355, 131, 357, 133, grey);
    draw_rect(screen, 471, 131, 473, 133, grey);
    draw_rect(screen, 471, 196, 473, 198, grey);
    draw_rect(screen, 355, 196, 357, 198, grey);
        /* Blue border */
    draw_rect(screen, 358, 134, 470, 136, blue);
    draw_rect(screen, 468, 137, 470, 192, blue);
    draw_rect(screen, 358, 193, 470, 195, blue);
    draw_rect(screen, 358, 137, 360, 192, blue);
    /* End next element */

    /* Lines */
        /* Grey border */
    draw_rect(screen, 355, 205, 473, 207, grey);
    draw_rect(screen, 474, 208, 476, 265, grey);
    draw_rect(screen, 355, 266, 473, 268, grey);
    draw_rect(screen, 352, 208, 354, 265, grey);
    draw_rect(screen, 355, 208, 357, 210, grey);
    draw_rect(screen, 471, 208, 473, 210, grey);
    draw_rect(screen, 471, 263, 473, 265, grey);
    draw_rect(screen, 355, 263, 357, 265, grey);
        /* Blue border */
    draw_rect(screen, 358, 211, 470, 213, blue);
    draw_rect(screen, 468, 214, 470, 259, blue);
    draw_rect(screen, 358, 260, 470, 262, blue);
    draw_rect(screen, 358, 214, 360, 259, blue);

    char lines_label[] = "LINES";
    draw_string(screen, 372, 220, lines_label, white, black);
    /* End lines */

    /* Tetris logo */
        /* Grey border */
    draw_rect(screen, 355, 272, 473, 274, grey);
    draw_rect(screen, 474, 275, 476, 316, grey);
    draw_rect(screen, 355, 317, 473, 319, grey);
    draw_rect(screen, 352, 275, 354, 316, grey);
    draw_rect(screen, 355, 275, 357, 277, grey);
    draw_rect(screen, 471, 275, 473, 277, grey);
    draw_rect(screen, 471, 314, 473, 316, grey);
    draw_rect(screen, 355, 314, 357, 316, grey);
        /* Blue border */
    draw_rect(screen, 358, 278, 470, 280, blue);
    draw_rect(screen, 468, 281, 470, 310, blue);
    draw_rect(screen, 358, 311, 470, 313, blue);
    draw_rect(screen, 358, 281, 360, 310, blue);

    unsigned int red = RED_RGB565;
    unsigned int orange = ORANGE_RGB565;
    unsigned int yellow = YELLOW_RGB565;
    unsigned int green = GREEN_RGB565;
    unsigned int blue_letter = BLUE_RGB565;
    unsigned int purple = PURPLE_RGB565;

    char red_t[] = "T";
    char orange_e[] = "E";
    char yellow_t[] = "T";
    char green_r[] = "R";
    char blue_i[] = "I";
    char purple_s[] = "S";

    draw_string(screen, 374, 289, red_t, red, black);
    draw_string(screen, 388, 289, orange_e, orange, black);
    draw_string(screen, 402, 289, yellow_t, yellow, black);
    draw_string(screen, 416, 289, green_r, green, black);
    draw_string(screen, 430, 289, blue_i, blue_letter, black);
    draw_string(screen, 444, 289, purple_s, purple, black);
    /* End tetris logo */

    FILE *data_f = fopen("screen_background.data", "wb");
    for (int y = 0; y < 320; y++) {
        for (int x = 0; x < 480; x++) {
            fputc((screen[y][x] & 0xff00) >> 8, data_f);
            fputc(screen[y][x] & 0x00ff, data_f);
        }
    }
    fclose(data_f);

    draw_background(screen);

    display(screen);
}
