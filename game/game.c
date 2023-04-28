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
    unsigned char block_type = GREEN_BLOCK_TYPE;
    for (int y = 0; y < 15; y++) {
        gamefield[y] = (unsigned char *)malloc(5 * sizeof(unsigned char));
        for (int x = 0; x < 5; x++) {
            gamefield[y][x] = block_type << 4;
            block_type = (block_type + 1) % 8;
            gamefield[y][x] |= block_type;
            block_type = (block_type + 1) % 8;
        }
        if (!gamefield[y]) {
            fprintf(stderr, "Malloc failed for gamefield.\n");
            exit(1);
        }
    }

    unsigned char pause_option;
    uint8_t first_press = 1;

    draw_background(screen);
    draw_gamefield(screen, gamefield);
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

        lcd_display(io, screen);
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }

    set_best_score(best_score);
}

static unsigned int get_best_score() {
    FILE *bestscore_f = fopen(BEST_SCORE_FILENAME, "rb");
    if (!bestscore_f) {
        return 0;
    }

    return (getc(bestscore_f)) | (getc(bestscore_f) << 8) | (getc(bestscore_f) << 16) | (getc(bestscore_f) << 24);
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
}
