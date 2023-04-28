#include "pause.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../hardware/io_address.h"
#include "tools/font.h"
#include "tools/colors.h"
#include "graphics.h"

#define OPTIONS_NUM                 2
#define DEAD_ZONE                   4
#define MAX_TEXT_WIDTH              136
#define TEXT_HEIGHT                 14
#define TEXT_PADDING_Y              6
#define TEXT_PADDING_X              20

static int get_pause_position_x() {
    return 240 - ((TEXT_PADDING_X * 2 + MAX_TEXT_WIDTH) / 2);
}

static int get_pause_position_y() {
    return 160 - (OPTIONS_NUM * (TEXT_PADDING_Y * 2 + TEXT_HEIGHT) / 2);
}

unsigned char pause(unsigned short **screen, phys_addr_t *io) {
    int x = get_pause_position_x();
    int y = get_pause_position_y();

    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 14 * 1000 * 1000};

    uint8_t vote;
    uint8_t start_green_knob_value = get_green_knob_value(io);
    uint8_t first_press = 1;

    while(1) {
        if (is_green_knob_pressed(io) && !first_press) {
            break;
        }
        if (first_press && !is_green_knob_pressed(io)) {
            first_press = 0;
        }

        vote = (get_green_knob_value(io) + (256 - start_green_knob_value)) % (OPTIONS_NUM * DEAD_ZONE);

        /* Paint background. */
        draw_rect(screen, x, y, x + 2 * TEXT_PADDING_X + MAX_TEXT_WIDTH, y + OPTIONS_NUM * (2 * TEXT_PADDING_Y + TEXT_HEIGHT), BLACK_RGB565);

        /* Draw rectangle with width: 20px + MAX_TEXT_WIDTH + 20px (20px is padding), and height: 6px + TEXT_HEIGHT + 6px (6px is padding). */
        /* Rectangles position depends on vote value. */
        draw_rect(screen, x, y + (vote/DEAD_ZONE) * (TEXT_HEIGHT + 2 * TEXT_PADDING_Y), x + 2 * TEXT_PADDING_X + MAX_TEXT_WIDTH, y + (vote/DEAD_ZONE + 1) * (TEXT_HEIGHT + 2 * TEXT_PADDING_Y), WHITE_RGB565);

        if (vote/DEAD_ZONE == CONTINUE) {
            draw_string(screen, x + TEXT_PADDING_X, y + TEXT_PADDING_Y, "CONTINUE", BLACK_RGB565, WHITE_RGB565);
        } else {
            draw_string(screen, x + TEXT_PADDING_X, y + TEXT_PADDING_Y, "CONTINUE", WHITE_RGB565, BLACK_RGB565);
        }

        if (vote/DEAD_ZONE == GO_TO_MENU) {
            draw_string(screen, x + TEXT_PADDING_X, y + 3 * TEXT_PADDING_Y + TEXT_HEIGHT, "GO TO MENU", BLACK_RGB565, WHITE_RGB565);
        } else {
            draw_string(screen, x + TEXT_PADDING_X, y + 3 * TEXT_PADDING_Y + TEXT_HEIGHT, "GO TO MENU", WHITE_RGB565, BLACK_RGB565);
        }

        lcd_display(io, screen);
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }

    return vote/DEAD_ZONE;
}
