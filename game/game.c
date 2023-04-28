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

#define BEST_SCORE_FILENAME     "bestscore.data"

static unsigned int get_best_score();
void set_best_score(unsigned int value);

void start_game(unsigned short **screen, phys_addr_t *io, unsigned char blocks_speed, unsigned char show_next_element) {
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 14 * 1000 * 1000};

    unsigned int statistics[7] = {0, 0, 0, 0, 0, 0, 0};
    unsigned int score = 0;
    unsigned int best_score = get_best_score();
    unsigned int lines_number = 0;

    unsigned char **gamefield = (unsigned char **)malloc(15 * sizeof(unsigned char *));
    if (!gamefield) {
        fprintf(stderr, "Malloc failed for gamefield.\n");
        exit(1);
    }
    unsigned char block_type = GREEN_FALLING_BLOCK_TYPE;
    for (int y = 0; y < 15; y++) {
        gamefield[y] = (unsigned char *)malloc(5 * sizeof(unsigned char));
        for (int x = 0; x < 5; x++) {
            if (y == x) {
                gamefield[y][x] = block_type << 4;
                gamefield[y][x] |= block_type;
            } else {
                gamefield[y][x] = 0x00;
            }
            printf("%x", gamefield[y][x]);
        }
        printf("\n");
        if (!gamefield[y]) {
            fprintf(stderr, "Malloc failed for gamefield.\n");
            exit(1);
        }
    }

    unsigned char pause_option;
    uint8_t first_press = 1;

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
        update_gamefield(gamefield, &update_call_time, blocks_speed);
        clear_rows(gamefield, screen, io, blocks_speed);
        draw_gamefield(screen, gamefield);

        lcd_display(io, screen);
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }

    for (int row = 0; row < 15; row++) {
        free(gamefield[row]);
    }
    free(gamefield);
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
