#include "gamefield.h"

#include <stdio.h>

#include "tools/colors.h"
#include "../hardware/io_address.h"
#include "graphics.h"

unsigned char update_gamefield(unsigned char **gamefield, block_t *current_block, struct timespec *last_call_time, unsigned char blocks_speed) {
    unsigned char spawn_new_block = 0;
    struct timespec current_time = {.tv_sec = 0, .tv_nsec = 0};
    clock_gettime(CLOCK_MONOTONIC, &current_time);

    if ((current_time.tv_sec + current_time.tv_nsec * 1.0e-9) - (last_call_time->tv_sec + last_call_time->tv_nsec * 1.0e-9) > 1.0 / blocks_speed) {
        clock_gettime(CLOCK_MONOTONIC, last_call_time);
        unsigned char is_current_block_moved = 0;
        for (int row = GAMEFIELD_SIZE-1; row >= 0; row--) {
            for (int col = 0; col < 10; col++) {
                if (row < GAMEFIELD_SIZE-1) {
                    if ((gamefield[row][col] == GREEN_FALLING_BLOCK_TYPE) || 
                            (gamefield[row][col] == RED_FALLING_BLOCK_TYPE) ||
                            (gamefield[row][col] == PURPLE_FALLING_BLOCK_TYPE) ||
                            (gamefield[row][col] == YELLOW_FALLING_BLOCK_TYPE) ||
                            (gamefield[row][col] == DARKBLUE_FALLING_BLOCK_TYPE) ||
                            (gamefield[row][col] == ORANGE_FALLING_BLOCK_TYPE) ||
                            (gamefield[row][col] == BLUE_FALLING_BLOCK_TYPE)) {
                        if (gamefield[row+1][col] == NO_BLOCK) {
                            is_current_block_moved = 1;
                            gamefield[row+1][col] = gamefield[row][col];
                            gamefield[row][col] = NO_BLOCK;
                        } else {
                            spawn_new_block = 1;
                            gamefield[row][col] = gamefield[row][col] - 7;
                            printf("Change block type to %x...\n", gamefield[row][col]);
                        }
                    }
                } else {
                    if ((gamefield[row][col] == GREEN_FALLING_BLOCK_TYPE) || 
                            (gamefield[row][col] == RED_FALLING_BLOCK_TYPE) ||
                            (gamefield[row][col] == PURPLE_FALLING_BLOCK_TYPE) ||
                            (gamefield[row][col] == YELLOW_FALLING_BLOCK_TYPE) ||
                            (gamefield[row][col] == DARKBLUE_FALLING_BLOCK_TYPE) ||
                            (gamefield[row][col] == ORANGE_FALLING_BLOCK_TYPE) ||
                            (gamefield[row][col] == BLUE_FALLING_BLOCK_TYPE)) {
                        spawn_new_block = 1;
                        gamefield[row][col] = gamefield[row][col] - 7;
                        printf("Change block type to %x...\n", gamefield[row][col]);
                    }
                }
            }
        }
        if (is_current_block_moved) {
            current_block->y += 1;
        }
    }
    return spawn_new_block;
}

unsigned char clear_rows(unsigned char **gamefield, unsigned short **screen, phys_addr_t *io, unsigned char blocks_speed) {
    unsigned char cleared_rows = 0;
    unsigned char full_row;
    for (int row = GAMEFIELD_SIZE-1; row >= 0; row--) {
        full_row = 1;
        for (int col = 0; col < 10; col++) {
            if (gamefield[row][col] == NO_BLOCK) {
                full_row = 0;
                break;
            }
        }
        if (full_row) {
            draw_gamefield(screen, gamefield);
            lcd_display(io, screen);
            cleared_rows++;
            struct timespec animation_delay = {.tv_sec = 0, .tv_nsec = (20.0/blocks_speed) * 1000 * 1000};
            uint32_t LED_line_value = 0x3 << 15;
            uint8_t screen_animation_counter = 0;
            do {
                if (screen_animation_counter == 0) {
                    gamefield[row][4] = ANIMATION_BLOCK_TYPE;
                    gamefield[row][5] = ANIMATION_BLOCK_TYPE;
                } else if (screen_animation_counter == 3) {
                    gamefield[row][3] = ANIMATION_BLOCK_TYPE;
                    gamefield[row][6] = ANIMATION_BLOCK_TYPE;
                } else if (screen_animation_counter == 6) {
                    gamefield[row][2] = ANIMATION_BLOCK_TYPE;
                    gamefield[row][7] = ANIMATION_BLOCK_TYPE;
                } else if (screen_animation_counter == 9) {
                    gamefield[row][1] = ANIMATION_BLOCK_TYPE;
                    gamefield[row][8] = ANIMATION_BLOCK_TYPE;
                } else if (screen_animation_counter == 12) {
                    gamefield[row][0] = ANIMATION_BLOCK_TYPE;
                    gamefield[row][9] = ANIMATION_BLOCK_TYPE;
                }

                draw_gamefield(screen, gamefield);
                screen_animation_counter++;
                LED_line_value = (LED_line_value << 1) | (LED_line_value >> 1);
                lcd_display(io, screen);
                set_led_line_value(io, LED_line_value);
                clock_nanosleep(CLOCK_MONOTONIC, 0, &animation_delay, NULL);
            } while (LED_line_value < 0xffffffff);
            set_led_line_value(io, 0);

            for (int upper_row = row-1; upper_row >= 0; upper_row--) {
                gamefield[upper_row+1][0] = gamefield[upper_row][0];
                gamefield[upper_row+1][1] = gamefield[upper_row][1];
                gamefield[upper_row+1][2] = gamefield[upper_row][2];
                gamefield[upper_row+1][3] = gamefield[upper_row][3];
                gamefield[upper_row+1][4] = gamefield[upper_row][4];
                gamefield[upper_row+1][5] = gamefield[upper_row][5];
                gamefield[upper_row+1][6] = gamefield[upper_row][6];
                gamefield[upper_row+1][7] = gamefield[upper_row][7];
                gamefield[upper_row+1][8] = gamefield[upper_row][8];
                gamefield[upper_row+1][9] = gamefield[upper_row][9];
            }
            gamefield[0][0] = NO_BLOCK;
            gamefield[0][1] = NO_BLOCK;
            gamefield[0][2] = NO_BLOCK;
            gamefield[0][3] = NO_BLOCK;
            gamefield[0][4] = NO_BLOCK;
            gamefield[0][5] = NO_BLOCK;
            gamefield[0][6] = NO_BLOCK;
            gamefield[0][7] = NO_BLOCK;
            gamefield[0][8] = NO_BLOCK;
            gamefield[0][9] = NO_BLOCK;
            row++;
        }
    }

    return cleared_rows;
}

