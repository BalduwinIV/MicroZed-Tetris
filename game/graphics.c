#include "graphics.h"

#include <stdio.h>
#include <stdlib.h>

#include "tools/colors.h"
#include "background.h"
#include "gamefield.h"

/* Undefine when working with hardware. */
/* #define TESTING */

void draw_background(unsigned short **screen) {
    for (int y = 0; y < 320; y++) {
        for (int x = 0; x < 480; x++) {
            screen[y][x] = background[y][x];
        }
    }
}

void draw_gamefield(unsigned short **screen, unsigned char** field){
    for (int y = 3; y < GAMEFIELD_SIZE; y++){
        for(int x = 0; x < 10; x++){
            draw_block(screen, GAMEFIELD_X + (x*20), GAMEFIELD_Y + ((y-3)*20), field[y][x]);
        }
    }
}

void draw_rect(unsigned short **screen, int x, int y, int dest_x, int dest_y, int color) {
    for (int y_temp = y; y_temp <= dest_y; y_temp++) {
        for (int x_temp = x; x_temp <= dest_x; x_temp++) {
            screen[y_temp][x_temp] = color;
        }
    }
}

void draw_checkbox(unsigned short **screen, int x, int y, unsigned char state) {
    if (state) {
        for (int y_temp = y; y_temp <= y + 9; y_temp++) {
            for (int x_temp = x; x_temp <= x + 9; x_temp++) {
                if (y_temp == y || y_temp == y + 9 || x_temp == x || x_temp == x + 9) {
                    screen[y_temp][x_temp] = BLACK_RGB565;
                } else {
                    screen[y_temp][x_temp] = WHITE_RGB565;
                }
            }
        }
    } else {
        for (int y_temp = y; y_temp <= y + 9; y_temp++) {
            for (int x_temp = x; x_temp <= x + 9; x_temp++) {
                if (y_temp == y || y_temp == y + 9 || x_temp == x || x_temp == x + 9) {
                    screen[y_temp][x_temp] = WHITE_RGB565;
                } else {
                    screen[y_temp][x_temp] = BLACK_RGB565;
                }
            }
        }
    }
}

void draw_block(unsigned short **screen, int x, int y, unsigned char block_type) {
    unsigned int main_color, top_color, sides_color, bottom_color;

    if (block_type == NO_BLOCK) {
        main_color = BLACK_RGB565;
        top_color = BLACK_RGB565;
        sides_color = BLACK_RGB565;
        bottom_color = BLACK_RGB565;
    } else if (block_type == GREEN_BLOCK_TYPE || block_type == GREEN_FALLING_BLOCK_TYPE) {
#ifndef TESTING
        /* To lcd display. */
        main_color = GREEN_RGB565;
        top_color = GREEN_BLOCK_TOP565;
        sides_color = GREEN_BLOCK_SIDES565;
        bottom_color = GREEN_BLOCK_BOTTOM565;
#else
        /* To image */
        main_color = GREEN_RGB888;
        top_color = GREEN_BLOCK_TOP888;
        sides_color = GREEN_BLOCK_SIDES888;
        bottom_color = GREEN_BLOCK_BOTTOM888;
#endif
    } else if (block_type == RED_BLOCK_TYPE || block_type == RED_FALLING_BLOCK_TYPE) {
#ifndef TESTING
        /* To lcd display. */
        main_color = RED_RGB565;
        top_color = RED_BLOCK_TOP565;
        sides_color = RED_BLOCK_SIDES565;
        bottom_color = RED_BLOCK_BOTTOM565;
#else
        /* To image */
        main_color = RED_RGB888;
        top_color = RED_BLOCK_TOP888;
        sides_color = RED_BLOCK_SIDES888;
        bottom_color = RED_BLOCK_BOTTOM888;
#endif
    } else if (block_type == PURPLE_BLOCK_TYPE || block_type == PURPLE_FALLING_BLOCK_TYPE) {
#ifndef TESTING
        /* To lcd display. */
        main_color = PURPLE_RGB565;
        top_color = PURPLE_BLOCK_TOP565;
        sides_color = PURPLE_BLOCK_SIDES565;
        bottom_color = PURPLE_BLOCK_BOTTOM565;
#else
        /* To image */
        main_color = PURPLE_RGB888;
        top_color = PURPLE_BLOCK_TOP888;
        sides_color = PURPLE_BLOCK_SIDES888;
        bottom_color = PURPLE_BLOCK_BOTTOM888;
#endif
    } else if (block_type == YELLOW_BLOCK_TYPE || block_type == YELLOW_FALLING_BLOCK_TYPE) {
#ifndef TESTING
        /* To lcd display. */
        main_color = YELLOW_RGB565;
        top_color = YELLOW_BLOCK_TOP565;
        sides_color = YELLOW_BLOCK_SIDES565;
        bottom_color = YELLOW_BLOCK_BOTTOM565;
#else
        /* To image */
        main_color = YELLOW_RGB888;
        top_color = YELLOW_BLOCK_TOP888;
        sides_color = YELLOW_BLOCK_SIDES888;
        bottom_color = YELLOW_BLOCK_BOTTOM888;
#endif
    } else if (block_type == DARKBLUE_BLOCK_TYPE || block_type == DARKBLUE_FALLING_BLOCK_TYPE) {
#ifndef TESTING
        /* To lcd display. */
        main_color = DARKBLUE_RGB565;
        top_color = DARKBLUE_BLOCK_TOP565;
        sides_color = DARKBLUE_BLOCK_SIDES565;
        bottom_color = DARKBLUE_BLOCK_BOTTOM565;
#else
        /* To image */
        main_color = DARKBLUE_RGB888;
        top_color = DARKBLUE_BLOCK_TOP888;
        sides_color = DARKBLUE_BLOCK_SIDES888;
        bottom_color = DARKBLUE_BLOCK_BOTTOM888;
#endif
    } else if (block_type == ORANGE_BLOCK_TYPE || block_type == ORANGE_FALLING_BLOCK_TYPE) {
#ifndef TESTING
        /* To lcd display. */
        main_color = ORANGE_RGB565;
        top_color = ORANGE_BLOCK_TOP565;
        sides_color = ORANGE_BLOCK_SIDES565;
        bottom_color = ORANGE_BLOCK_BOTTOM565;
#else
        /* To image */
        main_color = ORANGE_RGB888;
        top_color = ORANGE_BLOCK_TOP888;
        sides_color = ORANGE_BLOCK_SIDES888;
        bottom_color = ORANGE_BLOCK_BOTTOM888;
#endif
    } else if (block_type == BLUE_BLOCK_TYPE || block_type == BLUE_FALLING_BLOCK_TYPE) {
#ifndef TESTING
        /* To lcd display. */
        main_color = BLUE_RGB565;
        top_color = BLUE_BLOCK_TOP565;
        sides_color = BLUE_BLOCK_SIDES565;
        bottom_color = BLUE_BLOCK_BOTTOM565;
#else
        /* To image */
        main_color = BLUE_RGB888;
        top_color = BLUE_BLOCK_TOP888;
        sides_color = BLUE_BLOCK_SIDES888;
        bottom_color = BLUE_BLOCK_BOTTOM888;
#endif
    } else if (block_type == ANIMATION_BLOCK_TYPE) {
        main_color = WHITE_RGB565;
        top_color = WHITE_RGB565;
        sides_color = WHITE_RGB565;
        bottom_color = WHITE_RGB565;
    }

    for (int yi = 0; yi < BLOCK_SIZE; yi++) {
        for (int xi = 0; xi < BLOCK_SIZE; xi++) {
            if ((yi > 1 && yi < BLOCK_SIZE-2) && (xi > 1 && xi < BLOCK_SIZE-2)) {
                screen[y+yi][x+xi] = main_color;
            } else if (((xi == 0 || xi == BLOCK_SIZE-1) && yi < BLOCK_SIZE-1) || ((xi == 1 || xi == BLOCK_SIZE-2) && (yi > 0 && yi < BLOCK_SIZE-2))) {
                screen[y+yi][x+xi] = sides_color;
            } else if ((yi == 0 && (xi > 0 && xi < BLOCK_SIZE-1)) || (yi == 1 && (xi > 1 && xi < BLOCK_SIZE-2))) {
                screen[y+yi][x+xi] = top_color;
            } else {
                screen[y+yi][x+xi] = bottom_color;
            }
        }
    }
}
