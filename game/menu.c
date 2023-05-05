#include "menu.h"

#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "../hardware/io_address.h"
#include "tools/font.h"
#include "tools/colors.h"
#include "graphics.h"

#define DEFAULT_BLOCKS_SPEED        4
#define DEFAULT_SHOW_NEXT_BLOCK     1
#define MAX_BLOCKS_SPEED            32

#define OPTIONS_NUM                 5
#define KNOB_DEAD_ZONE_VALUE        5
#define MAX_TEXT_WIDTH              272
#define TEXT_HEIGHT                 14
#define TEXT_PADDING_Y              6
#define TEXT_PADDING_X              20

static int get_menu_position_x() {
    return 240 - ((TEXT_PADDING_X * 2 + MAX_TEXT_WIDTH) / 2);
}

static int get_menu_position_y() {
    return 220 - (OPTIONS_NUM * (TEXT_PADDING_Y * 2 + TEXT_HEIGHT) / 2);
}

unsigned char menu(unsigned short** screen, phys_addr_t *io, unsigned char *blocks_speed, unsigned char *show_next_block, unsigned char *enable_audio){
    int x = get_menu_position_x();
    int y = get_menu_position_y();

    draw_rect(screen, 0, 0, 479, 319, BLACK_RGB565);

    /* T */
    draw_block(screen, 10, 10, RED_BLOCK_TYPE);
    draw_block(screen, 30, 10, RED_BLOCK_TYPE);
    draw_block(screen, 50, 10, RED_BLOCK_TYPE);
    draw_block(screen, 30, 30, RED_BLOCK_TYPE);
    draw_block(screen, 30, 50, RED_BLOCK_TYPE);
    draw_block(screen, 30, 70, RED_BLOCK_TYPE);
    draw_block(screen, 30, 90, RED_BLOCK_TYPE);

    /* E */
    draw_block(screen, 90, 10, ORANGE_BLOCK_TYPE);
    draw_block(screen, 110, 10, ORANGE_BLOCK_TYPE);
    draw_block(screen, 130, 10, ORANGE_BLOCK_TYPE);
    draw_block(screen, 90, 30, ORANGE_BLOCK_TYPE);
    draw_block(screen, 90, 50, ORANGE_BLOCK_TYPE);
    draw_block(screen, 110, 50, ORANGE_BLOCK_TYPE);
    draw_block(screen, 90, 70, ORANGE_BLOCK_TYPE);
    draw_block(screen, 90, 90, ORANGE_BLOCK_TYPE);
    draw_block(screen, 110, 90, ORANGE_BLOCK_TYPE);
    draw_block(screen, 130, 90, ORANGE_BLOCK_TYPE);

    /* T */
    draw_block(screen, 170, 10, YELLOW_BLOCK_TYPE);
    draw_block(screen, 190, 10, YELLOW_BLOCK_TYPE);
    draw_block(screen, 210, 10, YELLOW_BLOCK_TYPE);
    draw_block(screen, 190, 30, YELLOW_BLOCK_TYPE);
    draw_block(screen, 190, 50, YELLOW_BLOCK_TYPE);
    draw_block(screen, 190, 70, YELLOW_BLOCK_TYPE);
    draw_block(screen, 190, 90, YELLOW_BLOCK_TYPE);

    /* R */
    draw_block(screen, 250, 10, GREEN_BLOCK_TYPE);
    draw_block(screen, 270, 10, GREEN_BLOCK_TYPE);
    draw_block(screen, 290, 10, GREEN_BLOCK_TYPE);
    draw_block(screen, 250, 30, GREEN_BLOCK_TYPE);
    draw_block(screen, 290, 30, GREEN_BLOCK_TYPE);
    draw_block(screen, 250, 50, GREEN_BLOCK_TYPE);
    draw_block(screen, 270, 50, GREEN_BLOCK_TYPE);
    draw_block(screen, 250, 70, GREEN_BLOCK_TYPE);
    draw_block(screen, 250, 90, GREEN_BLOCK_TYPE);
    draw_block(screen, 290, 70, GREEN_BLOCK_TYPE);
    draw_block(screen, 290, 90, GREEN_BLOCK_TYPE);

    /* I */
    draw_block(screen, 330, 10, BLUE_BLOCK_TYPE);
    draw_block(screen, 350, 10, BLUE_BLOCK_TYPE);
    draw_block(screen, 370, 10, BLUE_BLOCK_TYPE);
    draw_block(screen, 350, 30, BLUE_BLOCK_TYPE);
    draw_block(screen, 350, 50, BLUE_BLOCK_TYPE);
    draw_block(screen, 350, 70, BLUE_BLOCK_TYPE);
    draw_block(screen, 330, 90, BLUE_BLOCK_TYPE);
    draw_block(screen, 350, 90, BLUE_BLOCK_TYPE);
    draw_block(screen, 370, 90, BLUE_BLOCK_TYPE);

    /* S */
    draw_block(screen, 410, 10, PURPLE_BLOCK_TYPE);
    draw_block(screen, 430, 10, PURPLE_BLOCK_TYPE);
    draw_block(screen, 450, 10, PURPLE_BLOCK_TYPE);
    draw_block(screen, 410, 30, PURPLE_BLOCK_TYPE);
    draw_block(screen, 410, 50, PURPLE_BLOCK_TYPE);
    draw_block(screen, 430, 50, PURPLE_BLOCK_TYPE);
    draw_block(screen, 450, 50, PURPLE_BLOCK_TYPE);
    draw_block(screen, 450, 70, PURPLE_BLOCK_TYPE);
    draw_block(screen, 410, 90, PURPLE_BLOCK_TYPE);
    draw_block(screen, 430, 90, PURPLE_BLOCK_TYPE);
    draw_block(screen, 450, 90, PURPLE_BLOCK_TYPE);

    *blocks_speed = DEFAULT_BLOCKS_SPEED;
    *show_next_block = DEFAULT_SHOW_NEXT_BLOCK;
    int vote = 0;
    uint8_t green_knob_first_press = is_green_knob_pressed(io) ? 0 : 1;
    uint8_t green_knob_current_state_value = get_green_knob_value(io);
    uint8_t green_knob_previous_state_value = green_knob_current_state_value;
    uint8_t blue_knob_current_state_value = get_blue_knob_value(io);
    uint8_t blue_knob_previous_state_value = blue_knob_current_state_value;

    set_led_line_value(io, 0xffffffff << (32 - *blocks_speed));
    if (*show_next_block) {
        set_led_rgb1_color(io, GREEN_RGB888);
    } else {
        set_led_rgb1_color(io, RED_RGB888);
    }
    if (*enable_audio) {
        set_led_rgb2_color(io, GREEN_RGB888);
    } else {
        set_led_rgb2_color(io, RED_RGB888);
    }

    char blocks_speed_str[22] = "BLOCKS SPEED    ";
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 14 * 1000 * 1000};
    while (1) {
        if (is_green_knob_pressed(io) && green_knob_first_press && (vote == NEW_GAME || vote == EXIT)) {
            green_knob_first_press = 0;
            break;
        }
        if (!green_knob_first_press && !is_green_knob_pressed(io)) {
            green_knob_first_press = 1;
        }

        /* Vote */
        green_knob_current_state_value = get_green_knob_value(io);
        if (green_knob_current_state_value - green_knob_previous_state_value > KNOB_DEAD_ZONE_VALUE) {
            if (green_knob_current_state_value - green_knob_previous_state_value < 4 * KNOB_DEAD_ZONE_VALUE) {
                vote--;
                if (vote < 0) {
                    vote = 0;
                }
            }
            green_knob_previous_state_value = green_knob_current_state_value;
        } else if (green_knob_current_state_value - green_knob_previous_state_value < -KNOB_DEAD_ZONE_VALUE) {
            if (green_knob_current_state_value - green_knob_previous_state_value > -(4 * KNOB_DEAD_ZONE_VALUE)) {
                vote++;
                if (vote >= OPTIONS_NUM) {
                    vote = OPTIONS_NUM-1;
                }
            }
            green_knob_previous_state_value = green_knob_current_state_value;
        }
      
        /* Paint background. */
        draw_rect(screen, x, y, x + 2 * TEXT_PADDING_X + MAX_TEXT_WIDTH, y + OPTIONS_NUM * (2 * TEXT_PADDING_Y + TEXT_HEIGHT), BLACK_RGB565);

        /* Draw rectangle with width: 20px + MAX_TEXT_WIDTH + 20px (20px is padding), and height: 6px + TEXT_HEIGHT + 6px (6px is padding). */
        /* Rectangles position depends on vote value. */
        draw_rect(screen, x, y + vote * (TEXT_HEIGHT + 2 * TEXT_PADDING_Y), x + 2 * TEXT_PADDING_X + MAX_TEXT_WIDTH, y + (vote + 1) * (TEXT_HEIGHT + 2 * TEXT_PADDING_Y), WHITE_RGB565);

        /* If "NEW GAME" option is chosen, then draw it black on white background. */
        /* White on black background otherwise. */
        if (vote == NEW_GAME) {
            draw_string(screen, x + TEXT_PADDING_X, y + TEXT_PADDING_Y, "START GAME", BLACK_RGB565, WHITE_RGB565);
        } else {
            draw_string(screen, x + TEXT_PADDING_X, y + TEXT_PADDING_Y, "START GAME", WHITE_RGB565, BLACK_RGB565);
        }

        /* If "BLOCKS SPEED" option is chosen, then draw it black on white background. */
        /* White on black background otherwise. */
        blocks_speed_str[16] = '<';
        blocks_speed_str[17] = *blocks_speed / 10 + '0';
        blocks_speed_str[18] = *blocks_speed % 10 + '0';
        blocks_speed_str[19] = '>';
        blocks_speed_str[20] = '\0';
        if (vote == BLOCKS_SPEED) {
            blue_knob_current_state_value = get_blue_knob_value(io);
            if (blue_knob_current_state_value - blue_knob_previous_state_value > KNOB_DEAD_ZONE_VALUE) {
                if (blue_knob_current_state_value - blue_knob_previous_state_value < 4 * KNOB_DEAD_ZONE_VALUE) {
                    (*blocks_speed)--;
                    if (*blocks_speed < 1) {
                        *blocks_speed = 1;
                    }
                }
                set_led_line_value(io, 0xffffffff << (32 - *blocks_speed));
                blue_knob_previous_state_value = blue_knob_current_state_value;
            } else if (blue_knob_current_state_value - blue_knob_previous_state_value < -KNOB_DEAD_ZONE_VALUE) {
                if (blue_knob_current_state_value - blue_knob_previous_state_value > -(4 * KNOB_DEAD_ZONE_VALUE)) {
                    (*blocks_speed)++;
                    if (*blocks_speed > MAX_BLOCKS_SPEED) {
                        *blocks_speed = MAX_BLOCKS_SPEED;
                    }
                }
                set_led_line_value(io, 0xffffffff << (32 - *blocks_speed));
                blue_knob_previous_state_value = blue_knob_current_state_value;
            }
            draw_string(screen, x + TEXT_PADDING_X, y + 3 * TEXT_PADDING_Y + TEXT_HEIGHT, blocks_speed_str, BLACK_RGB565, WHITE_RGB565);
        } else {
            draw_string(screen, x + TEXT_PADDING_X, y + 3 * TEXT_PADDING_Y + TEXT_HEIGHT, blocks_speed_str, WHITE_RGB565, BLACK_RGB565);
        }
        
        if (vote == SHOW_NEXT_ELEMENT) {
            if (is_green_knob_pressed(io) && green_knob_first_press) {
                green_knob_first_press = 0;
                if (*show_next_block) {
                    *show_next_block = 0;
                    set_led_rgb1_color(io, RED_RGB888);
                } else {
                    *show_next_block = 1;
                    set_led_rgb1_color(io, GREEN_RGB888);
                }
            }

            if (!green_knob_first_press && !is_green_knob_pressed(io)) {
                green_knob_first_press = 1;
            }
            draw_string(screen, x + TEXT_PADDING_X, y + 5 * TEXT_PADDING_Y + 2 * TEXT_HEIGHT, "SHOW NEXT BLOCK ", BLACK_RGB565, WHITE_RGB565);
        } else {
            draw_string(screen, x + TEXT_PADDING_X, y + 5 * TEXT_PADDING_Y + 2 * TEXT_HEIGHT, "SHOW NEXT BLOCK ", WHITE_RGB565, BLACK_RGB565);
        }
        draw_checkbox(screen, x + TEXT_PADDING_X + 245, y + 5 * TEXT_PADDING_Y + 2 * TEXT_HEIGHT + 2, *show_next_block);

        if (vote == ENABLE_AUDIO) {
            if (is_green_knob_pressed(io) && green_knob_first_press) {
                green_knob_first_press = 0;
                if (*enable_audio) {
                    *enable_audio = 0;
                    set_led_rgb2_color(io, RED_RGB888);
                } else {
                    *enable_audio = 1;
                    set_led_rgb2_color(io, GREEN_RGB888);
                }
            }

            if (!green_knob_first_press && !is_green_knob_pressed(io)) {
                green_knob_first_press = 1;
            }
            draw_string(screen, x + TEXT_PADDING_X, y + 7 * TEXT_PADDING_Y + 3 * TEXT_HEIGHT, "ENABLE AUDIO ", BLACK_RGB565, WHITE_RGB565);
        } else {
            draw_string(screen, x + TEXT_PADDING_X, y + 7 * TEXT_PADDING_Y + 3 * TEXT_HEIGHT, "ENABLE AUDIO ", WHITE_RGB565, BLACK_RGB565);
        }
        draw_checkbox(screen, x + TEXT_PADDING_X + 245, y + 7 * TEXT_PADDING_Y + 3 * TEXT_HEIGHT + 2, *enable_audio);
        
        /* If "EXIT" option is chosen, then draw it black on white background. */
        /* White on black background otherwise. */
        if (vote == EXIT) {
            draw_string(screen, x + TEXT_PADDING_X, y + 9 * TEXT_PADDING_Y + 4 * TEXT_HEIGHT, "EXIT", BLACK_RGB565, WHITE_RGB565);
        } else {
            draw_string(screen, x + TEXT_PADDING_X, y + 9 * TEXT_PADDING_Y + 4 * TEXT_HEIGHT, "EXIT", WHITE_RGB565, BLACK_RGB565);
        }

        lcd_display(io, screen);
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }
    draw_rect(screen, 0, 0, 479, 319, BLACK_RGB565);
    lcd_display(io, screen);
    
    return vote;
}
