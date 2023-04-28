#include <time.h>
#include <stdio.h>

#include "tools/colors.h"
#include "../hardware/io_address.h"
#include "graphics.h"

void update_gamefield(unsigned char **gamefield, struct timespec *last_call_time, unsigned char blocks_speed) {
    struct timespec current_time = {.tv_sec = 0, .tv_nsec = 0};
    clock_gettime(CLOCK_MONOTONIC, &current_time);

    printf("Time from last call: %f\n", (current_time.tv_sec + current_time.tv_nsec * 1.0e-9) - (last_call_time->tv_sec + last_call_time->tv_nsec * 1.0e-9));
    if ((current_time.tv_sec + current_time.tv_nsec * 1.0e-9) - (last_call_time->tv_sec + last_call_time->tv_nsec * 1.0e-9) > 1.0 / blocks_speed) {
        clock_gettime(CLOCK_MONOTONIC, last_call_time);
        /* unsigned char block_type; */
        /* unsigned short block_matrix; */
        for (int row = 13; row >= 0; row--) {
            for (int col = 0; col < 5; col++) {
                if ((((gamefield[row][col] & 0xf0) >> 4) == GREEN_FALLING_BLOCK_TYPE) || 
                        (((gamefield[row][col] & 0xf0) >> 4) == RED_FALLING_BLOCK_TYPE) ||
                        (((gamefield[row][col] & 0xf0) >> 4) == PURPLE_FALLING_BLOCK_TYPE) ||
                        (((gamefield[row][col] & 0xf0) >> 4) == YELLOW_FALLING_BLOCK_TYPE) ||
                        (((gamefield[row][col] & 0xf0) >> 4) == DARKBLUE_FALLING_BLOCK_TYPE) ||
                        (((gamefield[row][col] & 0xf0) >> 4) == ORANGE_FALLING_BLOCK_TYPE) ||
                        (((gamefield[row][col] & 0xf0) >> 4) == BLUE_FALLING_BLOCK_TYPE)) {
                    if (((gamefield[row+1][col] & 0xf0) >> 4) == NO_BLOCK) {
                        gamefield[row+1][col] = (gamefield[row][col] & 0xf0) | (gamefield[row+1][col] & 0x0f);
                        gamefield[row][col] = gamefield[row][col] & 0x0f;
                        printf("Move %d to %d.\n", row, row+1);
                    }
                }
                if ((((gamefield[row][col] & 0x0f)) == GREEN_FALLING_BLOCK_TYPE) || 
                        (((gamefield[row][col] & 0x0f)) == RED_FALLING_BLOCK_TYPE) ||
                        (((gamefield[row][col] & 0x0f)) == PURPLE_FALLING_BLOCK_TYPE) ||
                        (((gamefield[row][col] & 0x0f)) == YELLOW_FALLING_BLOCK_TYPE) ||
                        (((gamefield[row][col] & 0x0f)) == DARKBLUE_FALLING_BLOCK_TYPE) ||
                        (((gamefield[row][col] & 0x0f)) == ORANGE_FALLING_BLOCK_TYPE) ||
                        (((gamefield[row][col] & 0x0f)) == BLUE_FALLING_BLOCK_TYPE)) {
                    if (((gamefield[row+1][col] & 0x0f)) == NO_BLOCK) {
                        gamefield[row+1][col] = (gamefield[row+1][col] & 0xf0) | (gamefield[row][col] & 0x0f);
                        gamefield[row][col] = gamefield[row][col] & 0xf0;
                        printf("Move %d to %d.\n", row, row+1);
                    }
                }
            }
        }
    }
}

int clear_rows(unsigned char **gamefield, unsigned short **screen, phys_addr_t *io, unsigned char blocks_speed) {
    int cleared_rows = 0;
    unsigned char full_row;
    for (int row = 14; row >= 0; row--) {
        full_row = 1;
        for (int col = 0; col < 5; col++) {
            if ((gamefield[row][col] & 0xf0) >> 4 == NO_BLOCK) {
                full_row = 0;
                break;
            }
            if ((gamefield[row][col] & 0x0f) == NO_BLOCK) {
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
                    gamefield[row][2] = (ANIMATION_BLOCK_TYPE << 4) | ANIMATION_BLOCK_TYPE;
                } else if (screen_animation_counter == 3) {
                    gamefield[row][1] = (gamefield[row][1] & 0xf0) | ANIMATION_BLOCK_TYPE;
                    gamefield[row][3] = (ANIMATION_BLOCK_TYPE << 4) | (gamefield[row][3] & 0x0f);
                } else if (screen_animation_counter == 6) {
                    gamefield[row][1] = (ANIMATION_BLOCK_TYPE << 4) | (gamefield[row][1] & 0x0f);
                    gamefield[row][3] = (gamefield[row][3] & 0xf0) | ANIMATION_BLOCK_TYPE;
                } else if (screen_animation_counter == 9) {
                    gamefield[row][0] = (gamefield[row][0] & 0xf0) | ANIMATION_BLOCK_TYPE;
                    gamefield[row][4] = (ANIMATION_BLOCK_TYPE << 4) | (gamefield[row][4] & 0x0f);
                } else if (screen_animation_counter == 12) {
                    gamefield[row][0] = (ANIMATION_BLOCK_TYPE << 4) | (gamefield[row][0] & 0x0f);
                    gamefield[row][4] = (gamefield[row][4] & 0xf0) | ANIMATION_BLOCK_TYPE;
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
            }
            row--;
        }
    }

    return cleared_rows;
}

