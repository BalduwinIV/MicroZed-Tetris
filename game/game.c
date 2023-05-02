#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../hardware/io_address.h"
#include "../hardware/mzapo_parlcd.h"
#include "../hardware/mzapo_phys.h"
#include "../hardware/mzapo_regs.h"
#include "tools/colors.h"
#include "graphics.h"
#include "stats.h"
#include "pause.h"
#include "gamefield.h"
#include "block.h"

#define BEST_SCORE_FILENAME     "bestscore.data"

static unsigned int get_best_score();
void set_best_score(unsigned int value);

void start_game(unsigned short **screen, phys_addr_t *io, unsigned char blocks_speed, unsigned char show_next_element) {
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 14 * 1000 * 1000};

    unsigned int statistics[7] = {0, 0, 0, 0, 0, 0, 0};
    unsigned int score = 0;
    unsigned int best_score = get_best_score();
    unsigned int lines_number = 0;

    unsigned char **gamefield = (unsigned char **)malloc(GAMEFIELD_SIZE * sizeof(unsigned char *));
    if (!gamefield) {
        fprintf(stderr, "Malloc failed for gamefield.\n");
        exit(1);
    }
    for (int y = 0; y < GAMEFIELD_SIZE; y++) {
        gamefield[y] = (unsigned char *)malloc(5 * sizeof(unsigned char));
        for (int x = 0; x < 10; x++) {
            gamefield[y][x] = NO_BLOCK;
        }
        if (!gamefield[y]) {
            fprintf(stderr, "Malloc failed for gamefield.\n");
            exit(1);
        }
    }

    unsigned char pause_option;
    uint8_t first_press = 1;
    uint8_t blue_knob_first_press = 1;
    uint8_t red_knob_first_press = 1;

    block_t *current_block = spawn_block(gamefield, DARKBLUE_FALLING_BLOCK_TYPE);

    struct timespec update_call_time = {.tv_sec = 0, .tv_nsec = 0};
    clock_gettime(CLOCK_MONOTONIC, &update_call_time);

    draw_background(screen);
    unsigned char game_is_running = 1;
    while (game_is_running) {
        if (is_green_knob_pressed(io) && !first_press) {
            printf("Pause...\n");
            pause_option = pause(screen, io);
            if (pause_option == GO_TO_MENU) {
                printf("Go to menu...\n");
                game_is_running = 0;
                break;
            }
            printf("Continue...\n");
            first_press = 1;
        }
        if (first_press && !is_green_knob_pressed(io)) {
            first_press = 0;
        }
        print_statistics(screen, statistics);
        print_score(screen, score);
        print_best_score(screen, best_score);
        print_destroyed_lines_number(screen, lines_number);

        if (is_blue_knob_pressed(io) && blue_knob_first_press) {
            rotate_block_right(gamefield, current_block);
            blue_knob_first_press = 0;
        } else if (!is_blue_knob_pressed(io) && !blue_knob_first_press){
            blue_knob_first_press = 1;
        }
        if (is_red_knob_pressed(io) && red_knob_first_press) {
            rotate_block_left(gamefield, current_block);
            red_knob_first_press = 0;
        } else if (!is_red_knob_pressed(io) && !red_knob_first_press) {
            red_knob_first_press = 1;
        }

        if (update_gamefield(gamefield, current_block, &update_call_time, blocks_speed)) {
            current_block = spawn_block(gamefield, BLUE_FALLING_BLOCK_TYPE);
        }
        clear_rows(gamefield, screen, io, blocks_speed);
        draw_gamefield(screen, gamefield);

        lcd_display(io, screen);
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }

    for (int row = 0; row < GAMEFIELD_SIZE; row++) {
        free(gamefield[row]);
    }
    free(gamefield);
    free(current_block);
    set_best_score(best_score);
}

static unsigned int get_best_score() {
    FILE *bestscore_f = fopen(BEST_SCORE_FILENAME, "rb");
    if (!bestscore_f) {
        return 0;
    }

    unsigned int return_value = (getc(bestscore_f)) | (getc(bestscore_f) << 8) | (getc(bestscore_f) << 16) | (getc(bestscore_f) << 24);
    fclose(bestscore_f);
    return return_value;
}

void set_best_score(unsigned int value) {
    FILE *bestscore_f = fopen(BEST_SCORE_FILENAME, "wb");
    if (!bestscore_f) {
        fprintf(stderr, "Error writing data for bestscore.data file.\n");
    } else {
        fputc(value & 0x000000ff, bestscore_f);
        fputc((value & 0x0000ff00) >> 8, bestscore_f);
        fputc((value & 0x00ff0000) >> 16, bestscore_f);
        fputc((value & 0xff000000) >> 24, bestscore_f);
    }
    fclose(bestscore_f);
}
