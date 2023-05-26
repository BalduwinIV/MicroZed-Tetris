#include "gameover.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "../hardware/io_address.h"
#include "tools/font.h"
#include "tools/colors.h"
#include "graphics.h"
#include "gamefield.h"

#define LEADERBOARD_MENU_POSITION_X     221
#define LEADERBOARD_MENU_POSITION_Y     144
#define LEADERBOARD_NAME_POSITION_X     268
#define LEADERBOARD_NAME_POSITION_Y 	203
#define LEADERBOARD_NUMBER_POSITION_X   381

#define GO_TO_MENU                  0

#define OPTIONS_NUM                 1
#define KNOB_DEAD_ZONE_VALUE        5
#define MAX_TEXT_WIDTH              136
#define TEXT_HEIGHT                 14
#define TEXT_PADDING_Y              6
#define TEXT_PADDING_X              20

static void draw_gameover_background(unsigned short **screen, unsigned int *statistics, unsigned int *score, unsigned int *lines_number);
static void draw_borders(unsigned short **screen, int x, int y, int x_dest, int y_dest);
static void play_animation(unsigned short **screen, unsigned char **gamefield, phys_addr_t *io);
static char *int_to_str3(unsigned int value);
static char *int_to_str6(unsigned int value);

unsigned char check_gameover(unsigned char **gamefield) {
    for (int y = 0; y < GAMEFIELD_SIZE - 14; y++) {
        for (int x = 0; x < 10; x++) {
            if (gamefield[y][x] >= GREEN_BLOCK_TYPE && gamefield[y][x] <= BLUE_BLOCK_TYPE) {
                return 1;
            }
        }
    }
    return 0;
}


unsigned char gameover(unsigned short** screen, unsigned char **gamefield, phys_addr_t *io, unsigned int *statistics, unsigned int *score, unsigned int *lines_number) {
    play_animation(screen, gamefield, io);
    int x = LEADERBOARD_MENU_POSITION_X;
    int y = LEADERBOARD_MENU_POSITION_Y;

    draw_rect(screen, 0, 0, 479, 319, BLACK_RGB565);
    draw_gameover_background(screen, statistics, score, lines_number);

    int vote = 0;
    uint8_t green_knob_first_press = is_green_knob_pressed(io) ? 0 : 1;
    uint8_t green_knob_current_state_value = get_green_knob_value(io);
    uint8_t green_knob_previous_state_value = green_knob_current_state_value;
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 14 * 1000 * 1000};
    while (1) {
        if (is_green_knob_pressed(io) && green_knob_first_press) {
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
        draw_rect(screen, LEADERBOARD_NAME_POSITION_X - TEXT_PADDING_X, LEADERBOARD_NAME_POSITION_Y - TEXT_PADDING_Y, LEADERBOARD_NAME_POSITION_X + TEXT_PADDING_X + MAX_TEXT_WIDTH, LEADERBOARD_NAME_POSITION_Y + TEXT_HEIGHT + TEXT_PADDING_Y, WHITE_RGB565);

        /* If "NEW GAME" option is chosen, then draw it black on white background. */
        /* White on black background otherwise. */
        if (vote == GO_TO_MENU) {
            draw_string(screen, LEADERBOARD_NAME_POSITION_X, LEADERBOARD_NAME_POSITION_Y, "GO TO MENU", BLACK_RGB565, WHITE_RGB565);
        } else {
            draw_string(screen, LEADERBOARD_NAME_POSITION_X, LEADERBOARD_NAME_POSITION_Y, "GO TO MENU", WHITE_RGB565, BLACK_RGB565);
        }

        lcd_display(io, screen);
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }
    draw_rect(screen, 0, 0, 479, 319, BLACK_RGB565);
    lcd_display(io, screen);
    
    return vote;
}

static void draw_borders(unsigned short **screen, int x, int y, int x_dest, int y_dest) {
    draw_rect(screen, x+3, y, x_dest-3, y+2, GREY_RGB565);
    draw_rect(screen, x, y+3, x+2, y_dest-3, GREY_RGB565);
    draw_rect(screen, x_dest-2, y+3, x_dest, y_dest-3, GREY_RGB565);
    draw_rect(screen, x+3, y_dest-2, x_dest-3, y_dest, GREY_RGB565);
    
    draw_rect(screen, x+3, y+3, x+5, y+5, GREY_RGB565);
    draw_rect(screen, x+3, y_dest-5, x+5, y_dest-3, GREY_RGB565);
    draw_rect(screen, x_dest-5, y+3, x_dest-3, y+5, GREY_RGB565);
    draw_rect(screen, x_dest-5, y_dest-5, x_dest-3, y_dest-3, GREY_RGB565);

    draw_rect(screen, x+6, y+6, x_dest-6, y+8, BORDER_RGB565);
    draw_rect(screen, x+6, y+9, x+8, y_dest-9, BORDER_RGB565);
    draw_rect(screen, x_dest-8, y+6, x_dest-6, y_dest-9, BORDER_RGB565);
    draw_rect(screen, x+6, y_dest-8, x_dest-6, y_dest-6, BORDER_RGB565);
}

static void draw_gameover_background(unsigned short **screen, unsigned int *statistics, unsigned int *score, unsigned int *lines_number) {
    draw_borders(screen, 0, 0, 97, 97);
    draw_borders(screen, 0, 101, 97, 198);
    draw_borders(screen, 0, 202, 97, 299);
    draw_borders(screen, 101, 0, 198, 97);
    draw_borders(screen, 101, 101, 198, 198);
    draw_borders(screen, 101, 202, 198, 299);
    draw_borders(screen, 202, 0, 319, 97);
    draw_borders(screen, 323, 0, 479, 97);
    draw_borders(screen, 202, 101, 479, 319);

    /* S */
    draw_block(screen, 39, 19, GREEN_BLOCK_TYPE);
    draw_block(screen, 59, 19, GREEN_BLOCK_TYPE);
    draw_block(screen, 19, 39, GREEN_BLOCK_TYPE);
    draw_block(screen, 39, 39, GREEN_BLOCK_TYPE);
    draw_string(screen, 30, 65, int_to_str3(statistics[0]), WHITE_RGB565, BLACK_RGB565);

    /* Z */
    draw_block(screen, 19, 120, RED_BLOCK_TYPE);
    draw_block(screen, 39, 120, RED_BLOCK_TYPE);
    draw_block(screen, 39, 140, RED_BLOCK_TYPE);
    draw_block(screen, 59, 140, RED_BLOCK_TYPE);
    draw_string(screen, 30, 166, int_to_str3(statistics[1]), WHITE_RGB565, BLACK_RGB565);

    /* T */
    draw_block(screen, 39, 221, PURPLE_BLOCK_TYPE);
    draw_block(screen, 19, 241, PURPLE_BLOCK_TYPE);
    draw_block(screen, 39, 241, PURPLE_BLOCK_TYPE);
    draw_block(screen, 59, 241, PURPLE_BLOCK_TYPE);
    draw_string(screen, 30, 267, int_to_str3(statistics[2]), WHITE_RGB565, BLACK_RGB565);

    /* O */
    draw_block(screen, 130, 19, YELLOW_BLOCK_TYPE);
    draw_block(screen, 150, 19, YELLOW_BLOCK_TYPE);
    draw_block(screen, 130, 39, YELLOW_BLOCK_TYPE);
    draw_block(screen, 150, 39, YELLOW_BLOCK_TYPE);
    draw_string(screen, 131, 65, int_to_str3(statistics[3]), WHITE_RGB565, BLACK_RGB565);

    /* J */
    draw_block(screen, 120, 120, DARKBLUE_BLOCK_TYPE);
    draw_block(screen, 120, 140, DARKBLUE_BLOCK_TYPE);
    draw_block(screen, 140, 140, DARKBLUE_BLOCK_TYPE);
    draw_block(screen, 160, 140, DARKBLUE_BLOCK_TYPE);
    draw_string(screen, 131, 166, int_to_str3(statistics[4]), WHITE_RGB565, BLACK_RGB565);

    /* L */
    draw_block(screen, 160, 221, ORANGE_BLOCK_TYPE);
    draw_block(screen, 120, 241, ORANGE_BLOCK_TYPE);
    draw_block(screen, 140, 241, ORANGE_BLOCK_TYPE);
    draw_block(screen, 160, 241, ORANGE_BLOCK_TYPE);
    draw_string(screen, 131, 267, int_to_str3(statistics[5]), WHITE_RGB565, BLACK_RGB565);

    /* I */
    draw_block(screen, 221, 29, BLUE_BLOCK_TYPE);
    draw_block(screen, 241, 29, BLUE_BLOCK_TYPE);
    draw_block(screen, 261, 29, BLUE_BLOCK_TYPE);
    draw_block(screen, 281, 29, BLUE_BLOCK_TYPE);
    draw_string(screen, 242, 65, int_to_str3(statistics[6]), WHITE_RGB565, BLACK_RGB565);

    draw_string(screen, 342, 19, "LINES", WHITE_RGB565, BLACK_RGB565);
    draw_string(screen, 423, 19, int_to_str3(*lines_number), WHITE_RGB565, BLACK_RGB565);

    draw_string(screen, 342, 45, "SCORE", WHITE_RGB565, BLACK_RGB565);
    draw_string(screen, 381, 65, int_to_str6(*score), WHITE_RGB565, BLACK_RGB565);
}

/* Converts integer to string of length 3. Used for statistics numbers and lines number. */
static char *int_to_str3(unsigned int value) {
    char *number = (char *)malloc(4*sizeof(char));
    if (!number) {
        fprintf(stderr, "Malloc failed in stats.h function (int_to_str3).\n");
        exit(1);
    }

    if (value > 999) {
        number[0] = '9';
        number[1] = '9';
        number[2] = '9';
    } else {
        number[0] = value / 100 + '0';
        number[1] = (value / 10) % 10 + '0';
        number[2] = value % 10 + '0';
    }
    number[3] = '\0';
    return number;
}

/* Converts integer to string of length 6. Used for score and best_score numbers. */
static char *int_to_str6(unsigned int value) {
    char *number = (char *)malloc(7*sizeof(char));
    if (!number) {
        fprintf(stderr, "Malloc failed in stats.h function (int_to_str6).\n");
        exit(1);
    }

    if (value > 999999) {
        number[0] = '9';
        number[1] = '9';
        number[2] = '9';
        number[3] = '9';
        number[4] = '9';
        number[5] = '9';
    } else {
        number[0] = value / 100000 + '0';
        number[1] = (value / 10000) % 10 + '0';
        number[2] = (value / 1000) % 10 + '0';
        number[3] = (value / 100) % 10 + '0';
        number[4] = (value / 10) % 10 + '0';
        number[5] = value % 10 + '0';
    }
    number[6] = '\0';
    return number;
}

/* Shows gameover animation on the screen and led panel. */
static void play_animation(unsigned short **screen, unsigned char **gamefield, phys_addr_t *io) {
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 30 * 1000 * 1000};

    for (int y = 3; y < GAMEFIELD_SIZE; y++) {
        for (int x = 0; x < 10; x++) {
            gamefield[y][x] = ANIMATION_BLOCK_TYPE;
        }
        if (y % 2) {
            set_led_line_value(io, 0xaaaaaaaa);
        } else {
            set_led_line_value(io, 0x55555555);
        }
        draw_gamefield(screen, gamefield);
        lcd_display(io, screen);
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }
    set_led_line_value(io, 0x00000000);
}
