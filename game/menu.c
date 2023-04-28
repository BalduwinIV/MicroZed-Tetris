#include <stdint.h>
#include <time.h>

#include "menu.h"
#include "../hardware/io_address.h"
#include "tools/font.h"
#include "tools/colors.h"

#define OPTIONS_NUM         3
#define MAX_TEXT_WIDTH      164
#define TEXT_HEIGHT         14
#define TEXT_PADDING_Y      6
#define TEXT_PADDING_X      20

static void draw_rect(unsigned short **screen, int x, int y, int dest_x, int dest_y, int color) {
    for (int y_temp = y; y_temp <= dest_y; y_temp++) {
        for (int x_temp = x; x_temp <= dest_x; x_temp++) {
            screen[y_temp][x_temp] = color;
        }
    }
}

static int get_menu_position_x() {
    return 240 - ((TEXT_PADDING_X * 2 + MAX_TEXT_WIDTH) / 2);
}

static int get_menu_position_y() {
    return 160 - (OPTIONS_NUM * (TEXT_PADDING_Y * 2 + TEXT_HEIGHT) / 2);
}

int menu(unsigned short** screen, phys_addr_t *io){
    int x = get_menu_position_x();
    int y = get_menu_position_y();
    uint8_t vote;
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 14 * 1000 * 1000};
    while (1) {
        if (is_green_knob_pressed(io) && (vote == NEW_GAME || vote == EXIT)) break;
      
        vote = get_green_knob_value(io) % OPTIONS_NUM;

        /* Draw rectangle with width: 20px + MAX_TEXT_WIDTH + 20px (20px is padding), and height: 6px + TEXT_HEIGHT + 6px (6px is padding). */
        /* Rectangles position depends on vote value. */
        draw_rect (screen, x, y + vote * (TEXT_HEIGHT + 2 * TEXT_PADDING_Y), x + 2 * TEXT_PADDING_X + MAX_TEXT_WIDTH, y + (vote + 1) * (TEXT_HEIGHT + 2 * TEXT_PADDING_Y), WHITE_RGB565);

        /* If "NEW GAME" option is chosen, then draw it black on white background. */
        /* White on black background otherwise. */
        if (vote == NEW_GAME) {
            draw_string(screen, x + TEXT_PADDING_X, y + TEXT_PADDING_Y, "START GAME", BLACK_RGB565, WHITE_RGB565);
        } else {
            draw_string(screen, x + TEXT_PADDING_X, y + TEXT_PADDING_Y, "START GAME", WHITE_RGB565, BLACK_RGB565);
        }

        /* If "BLOCKS SPEED" option is chosen, then draw it black on white background. */
        /* White on black background otherwise. */
        if (vote == BLOCKS_SPEED) {
            draw_string(screen, x + TEXT_PADDING_X, y + 3 * TEXT_PADDING_Y + TEXT_HEIGHT, "BLOCKS SPEED", BLACK_RGB565, WHITE_RGB565);
        } else {
            draw_string(screen, x + TEXT_PADDING_X, y + 3 * TEXT_PADDING_Y + TEXT_HEIGHT, "BLOCKS SPEED", WHITE_RGB565, BLACK_RGB565);
        }
        
        /* If "EXIT" option is chosen, then draw it black on white background. */
        /* White on black background otherwise. */
        if (vote == EXIT) {
            draw_string(screen, x + TEXT_PADDING_X, y + 5 * TEXT_PADDING_Y + TEXT_HEIGHT, "EXIT", BLACK_RGB565, WHITE_RGB565);
        } else {
            draw_string(screen, x + TEXT_PADDING_X, y + 5 * TEXT_PADDING_Y + TEXT_HEIGHT, "EXIT", WHITE_RGB565, BLACK_RGB565);
        }

        lcd_display(io, screen);
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }
    
    return vote;
}
