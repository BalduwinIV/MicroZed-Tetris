#include "menu.h"

#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "../hardware/io_address.h"
#include "tools/font.h"
#include "tools/colors.h"
#include "graphics.h"

#define DEFAULT_BLOCKS_SPEED        1
#define DEFAULT_SHOW_NEXT_ELEMENT   1

#define OPTIONS_NUM                 4
#define DEAD_ZONE                   4
#define MAX_TEXT_WIDTH              258
#define TEXT_HEIGHT                 14
#define TEXT_PADDING_Y              6
#define TEXT_PADDING_X              20

static int get_menu_position_x() {
    return 240 - ((TEXT_PADDING_X * 2 + MAX_TEXT_WIDTH) / 2);
}

static int get_menu_position_y() {
    return 160 - (OPTIONS_NUM * (TEXT_PADDING_Y * 2 + TEXT_HEIGHT) / 2);
}

unsigned char menu(unsigned short** screen, phys_addr_t *io, unsigned char *blocks_speed, unsigned char *show_next_element){
    int x = get_menu_position_x();
    int y = get_menu_position_y();

    draw_rect(screen, 0, 0, 479, 319, BLACK_RGB565);

    *blocks_speed = DEFAULT_BLOCKS_SPEED;
    unsigned char tmp_block_speed = DEFAULT_BLOCKS_SPEED;
    *show_next_element = DEFAULT_SHOW_NEXT_ELEMENT;
    uint8_t vote;
    uint8_t first_press = 1;
    uint8_t previous_knob_state, current_knob_state;
    uint8_t start_green_knob_value = get_green_knob_value(io);
    uint8_t start_blue_knob_value = get_blue_knob_value(io);
    char blocks_speed_str[19] = "BLOCKS SPEED ";
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 14 * 1000 * 1000};
    while (1) {
        if (is_green_knob_pressed(io) && !first_press && (vote/DEAD_ZONE == NEW_GAME || vote/DEAD_ZONE == EXIT)) {
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

        /* If "NEW GAME" option is chosen, then draw it black on white background. */
        /* White on black background otherwise. */
        if (vote/DEAD_ZONE == NEW_GAME) {
            draw_string(screen, x + TEXT_PADDING_X, y + TEXT_PADDING_Y, "START GAME", BLACK_RGB565, WHITE_RGB565);
        } else {
            draw_string(screen, x + TEXT_PADDING_X, y + TEXT_PADDING_Y, "START GAME", WHITE_RGB565, BLACK_RGB565);
        }

        /* If "BLOCKS SPEED" option is chosen, then draw it black on white background. */
        /* White on black background otherwise. */
        blocks_speed_str[13] = '<';
        blocks_speed_str[14] = *blocks_speed / 10 + '0';
        blocks_speed_str[15] = *blocks_speed % 10 + '0';
        blocks_speed_str[16] = '>';
        blocks_speed_str[17] = '\0';
        if (vote/DEAD_ZONE == BLOCKS_SPEED) {
            *blocks_speed = ((get_blue_knob_value(io) - start_blue_knob_value) / DEAD_ZONE) + tmp_block_speed;
            if (*blocks_speed > 20) {
                *blocks_speed = 20;
            } else if (*blocks_speed < 1) {
                *blocks_speed = 1;
            }
            draw_string(screen, x + TEXT_PADDING_X, y + 3 * TEXT_PADDING_Y + TEXT_HEIGHT, blocks_speed_str, BLACK_RGB565, WHITE_RGB565);
        } else {
            tmp_block_speed = *blocks_speed;
            start_blue_knob_value = get_blue_knob_value(io);
            draw_string(screen, x + TEXT_PADDING_X, y + 3 * TEXT_PADDING_Y + TEXT_HEIGHT, blocks_speed_str, WHITE_RGB565, BLACK_RGB565);
        }
        
        if (vote/DEAD_ZONE == SHOW_NEXT_ELEMENT) {
            current_knob_state = is_green_knob_pressed(io);
            if (current_knob_state && current_knob_state != previous_knob_state) {
                if (*show_next_element) {
                    *show_next_element = 0;
                } else {
                    *show_next_element = 1;
                }
            }
            previous_knob_state = current_knob_state;
            draw_string(screen, x + TEXT_PADDING_X, y + 5 * TEXT_PADDING_Y + 2 * TEXT_HEIGHT, "SHOW NEXT ELEMENT ", BLACK_RGB565, WHITE_RGB565);
        } else {
            draw_string(screen, x + TEXT_PADDING_X, y + 5 * TEXT_PADDING_Y + 2 * TEXT_HEIGHT, "SHOW NEXT ELEMENT ", WHITE_RGB565, BLACK_RGB565);
        }

        draw_checkbox(screen, x + TEXT_PADDING_X + 252, y + 5 * TEXT_PADDING_Y + 2 * TEXT_HEIGHT + 2, *show_next_element);
        
        /* If "EXIT" option is chosen, then draw it black on white background. */
        /* White on black background otherwise. */
        if (vote/DEAD_ZONE == EXIT) {
            draw_string(screen, x + TEXT_PADDING_X, y + 7 * TEXT_PADDING_Y + 3 * TEXT_HEIGHT, "EXIT", BLACK_RGB565, WHITE_RGB565);
        } else {
            draw_string(screen, x + TEXT_PADDING_X, y + 7 * TEXT_PADDING_Y + 3 * TEXT_HEIGHT, "EXIT", WHITE_RGB565, BLACK_RGB565);
        }

        lcd_display(io, screen);
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }
    draw_rect(screen, 0, 0, 479, 319, BLACK_RGB565);
    lcd_display(io, screen);
    
    return vote/DEAD_ZONE;
}
