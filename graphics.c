#include "graphics.h"
#include "colors.h"

void draw_block(unsigned int **screen, int x, int y, unsigned char block_type) {
    unsigned int main_color, top_color, sides_color, bottom_color;

    if (block_type == NO_BLOCK) {
        main_color = BLACK_RGB565;
        top_color = BLACK_RGB565;
        sides_color = BLACK_RGB565;
        bottom_color = BLACK_RGB565;
    } else if (block_type == GREEN_BLOCK_TYPE) {
        /* To lcd display. */
        /*
        main_color = GREEN_RGB565;
        top_color = GREEN_BLOCK_TOP565;
        sides_color = GREEN_BLOCK_SIDES565;
        bottom_color = GREEN_BLOCK_BOTTOM565;
        */

        /* To image */
        main_color = GREEN_RGB888;
        top_color = GREEN_BLOCK_TOP888;
        sides_color = GREEN_BLOCK_SIDES888;
        bottom_color = GREEN_BLOCK_BOTTOM888;
    } else if (block_type == RED_BLOCK_TYPE) {
        /* To lcd display. */
        /*
        main_color = RED_RGB565;
        top_color = RED_BLOCK_TOP565;
        sides_color = RED_BLOCK_SIDES565;
        bottom_color = RED_BLOCK_BOTTOM565;
        */
        /* To image */
        main_color = RED_RGB888;
        top_color = RED_BLOCK_TOP888;
        sides_color = RED_BLOCK_SIDES888;
        bottom_color = RED_BLOCK_BOTTOM888;
    } else if (block_type == PURPLE_BLOCK_TYPE) {
        /* To lcd display. */
        /*
        main_color = PURPLE_RGB565;
        top_color = PURPLE_BLOCK_TOP565;
        sides_color = PURPLE_BLOCK_SIDES565;
        bottom_color = PURPLE_BLOCK_BOTTOM565;
        */
        /* To image */
        main_color = PURPLE_RGB888;
        top_color = PURPLE_BLOCK_TOP888;
        sides_color = PURPLE_BLOCK_SIDES888;
        bottom_color = PURPLE_BLOCK_BOTTOM888;
    } else if (block_type == YELLOW_BLOCK_TYPE) {
        /* To lcd display. */
        /*
        main_color = YELLOW_RGB565;
        top_color = YELLOW_BLOCK_TOP565;
        sides_color = YELLOW_BLOCK_SIDES565;
        bottom_color = YELLOW_BLOCK_BOTTOM565;
        */
        /* To image */
        main_color = YELLOW_RGB888;
        top_color = YELLOW_BLOCK_TOP888;
        sides_color = YELLOW_BLOCK_SIDES888;
        bottom_color = YELLOW_BLOCK_BOTTOM888;
    } else if (block_type == DARKBLUE_BLOCK_TYPE) {
        /* To lcd display. */
        /*
        main_color = DARKBLUE_RGB565;
        top_color = DARKBLUE_BLOCK_TOP565;
        sides_color = DARKBLUE_BLOCK_SIDES565;
        bottom_color = DARKBLUE_BLOCK_BOTTOM565;
        */
        /* To image */
        main_color = DARKBLUE_RGB888;
        top_color = DARKBLUE_BLOCK_TOP888;
        sides_color = DARKBLUE_BLOCK_SIDES888;
        bottom_color = DARKBLUE_BLOCK_BOTTOM888;
    } else if (block_type == ORANGE_BLOCK_TYPE) {
        /* To lcd display. */
        /*
        main_color = ORANGE_RGB565;
        top_color = ORANGE_BLOCK_TOP565;
        sides_color = ORANGE_BLOCK_SIDES565;
        bottom_color = ORANGE_BLOCK_BOTTOM565;
        */
        /* To image */
        main_color = ORANGE_RGB888;
        top_color = ORANGE_BLOCK_TOP888;
        sides_color = ORANGE_BLOCK_SIDES888;
        bottom_color = ORANGE_BLOCK_BOTTOM888;
    } else if (block_type == BLUE_BLOCK_TYPE) {
        /* To lcd display. */
        /*
        main_color = BLUE_RGB565;
        top_color = BLUE_BLOCK_TOP565;
        sides_color = BLUE_BLOCK_SIDES565;
        bottom_color = BLUE_BLOCK_BOTTOM565;
        */
        /* To image */
        main_color = BLUE_RGB888;
        top_color = BLUE_BLOCK_TOP888;
        sides_color = BLUE_BLOCK_SIDES888;
        bottom_color = BLUE_BLOCK_BOTTOM888;
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
