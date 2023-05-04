#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

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
#include "score.h"

#define BEST_SCORE_FILENAME     "bestscore.data"
#define KNOB_DEAD_ZONE_VALUE    4

static struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 14 * 1000 * 1000};
static unsigned short **screen_ptr;
static unsigned char *show_next_element_ptr;
static unsigned int **statistics_ptr;
static unsigned int *score_ptr;
static unsigned int *best_score_ptr;
static unsigned char *next_block_index_ptr;
static unsigned int *lines_number_ptr;
static unsigned char game_is_running;

static void *pause_thread(void *io);
static unsigned int get_best_score();
static void set_best_score(unsigned int value);

void start_game(unsigned short **screen, phys_addr_t *io, unsigned char blocks_speed, unsigned char show_next_element) {
    pthread_t pause_pid;

    unsigned int statistics[7] = {0, 0, 0, 0, 0, 0, 0};
    unsigned int score = 0;
    unsigned int best_score = get_best_score();
    unsigned int lines_number = 0;

    show_next_element_ptr = &show_next_element;
    screen_ptr = screen;
    statistics_ptr = statistics_ptr;
    score_ptr = &score;
    best_score_ptr = &best_score;
    lines_number_ptr = &lines_number;

    printf("Allocating memory for gamefield...\n");
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

    uint8_t red_knob_first_press = 1;
    uint8_t red_knob_current_state_value = get_red_knob_value(io);
    uint8_t red_knob_previous_state_value = red_knob_current_state_value;
    uint8_t blue_knob_current_state_value = get_blue_knob_value(io);
    uint8_t blue_knob_previous_state_value = blue_knob_current_state_value;
    unsigned int cleared_rows_at_the_moment;

    block_t *current_block = spawn_random_block(gamefield);
    unsigned char next_block_index = get_next_block_index();
    next_block_index_ptr = &next_block_index;
    printf("Current block: %d, Next block: %d\n", current_block->type, next_block_index);

    draw_background(screen);
    print_statistics(screen, statistics);
    print_score(screen, score);
    print_best_score(screen, best_score);
    print_next_block(screen, next_block_index);
    print_destroyed_lines_number(screen, lines_number);

    printf("Starting pause thread...");
    pthread_create(&pause_pid, NULL, pause_thread, (void *)io);

    printf("Starting game loop...");
    struct timespec update_call_time = {.tv_sec = 0, .tv_nsec = 0};
    clock_gettime(CLOCK_MONOTONIC, &update_call_time);

    game_is_running = 1;
    while (game_is_running) {
        /* Moving */
        blue_knob_current_state_value = get_blue_knob_value(io);
        if (blue_knob_current_state_value - blue_knob_previous_state_value > KNOB_DEAD_ZONE_VALUE) {
            if (blue_knob_current_state_value - blue_knob_previous_state_value < 4 * KNOB_DEAD_ZONE_VALUE) {
                printf("Moving current block to right...\n");
                move_block_right(gamefield, current_block);
            }
            blue_knob_previous_state_value = blue_knob_current_state_value;
        } else if (blue_knob_current_state_value - blue_knob_previous_state_value < -KNOB_DEAD_ZONE_VALUE) {
            if (blue_knob_current_state_value - blue_knob_previous_state_value > -(4 * KNOB_DEAD_ZONE_VALUE)) {
                printf("Moving current_block to left...\n");
                move_block_left(gamefield, current_block);
            }
            blue_knob_previous_state_value = blue_knob_current_state_value;
        }

        /* Rotating */
        red_knob_current_state_value = get_red_knob_value(io);
        if (red_knob_current_state_value - red_knob_previous_state_value > KNOB_DEAD_ZONE_VALUE) {
            if (red_knob_current_state_value - red_knob_previous_state_value < 4 * KNOB_DEAD_ZONE_VALUE) {
                printf("Rotating current block clockwise...\n");
                rotate_block_right(gamefield, current_block);
            }
            red_knob_previous_state_value = red_knob_current_state_value;
        } else if (red_knob_current_state_value - red_knob_previous_state_value < -KNOB_DEAD_ZONE_VALUE) {
            if (red_knob_current_state_value - red_knob_previous_state_value > -(4 * KNOB_DEAD_ZONE_VALUE)) {
                printf("Rotating current block counterclockwise...\n");
                rotate_block_left(gamefield, current_block);
            }
            red_knob_previous_state_value = red_knob_current_state_value;
        }

        /* Drop */
        if (is_red_knob_pressed(io) && red_knob_first_press) {
            red_knob_first_press = 0;
            printf("Dropping current block...\n");
            drop_block(gamefield, current_block);
        } 
        if (!red_knob_first_press && !is_red_knob_pressed(io)) {
            red_knob_first_press = 1;
        }

        /* Soft drop */
        if (is_blue_knob_pressed(io)) {
            printf("Moving block down...\n");
            move_block_down(gamefield, current_block);
        }

        if (update_gamefield(gamefield, current_block, &update_call_time, blocks_speed)) {
            statistics[current_block->type-7]++;
            print_statistics(screen, statistics);

            printf("Trying to free current block.\n");
            free(current_block);
            printf("Current block has been freed.\n");
            printf("Spawing block (%d)...\n", next_block_index);
            current_block = spawn_block(gamefield, next_block_index);
            next_block_index = get_next_block_index();
            printf("Next block: %d\n", next_block_index);

            if (show_next_element) {
                print_next_block(screen, next_block_index);
            }
        }

        cleared_rows_at_the_moment = clear_rows(gamefield, screen, io, blocks_speed);
        if (cleared_rows_at_the_moment > 0) {
            score += calculate_score(blocks_speed, cleared_rows_at_the_moment);
            print_score(screen, score);

            printf("%d rows has been cleared.\n", cleared_rows_at_the_moment);
            lines_number += cleared_rows_at_the_moment;
            print_destroyed_lines_number(screen, lines_number);
        }
        draw_gamefield(screen, gamefield);

        lcd_display(io, screen);
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }

    printf("Game loop has ended...\n");
    for (int row = 0; row < GAMEFIELD_SIZE; row++) {
        free(gamefield[row]);
    }
    free(gamefield);
    free(current_block);
    set_best_score(best_score);
}

static void *pause_thread(void *io) {
    io = (phys_addr_t *)io;
    unsigned char pause_option;
    uint8_t green_first_press = 1;
    while (game_is_running) {
        if (is_green_knob_pressed(io) && !green_first_press) {
            printf("Pause...\n");
            pause_option = pause(screen_ptr, io);
            if (pause_option == GO_TO_MENU) {
                printf("Go to menu...\n");
                game_is_running = 0;
                break;
            }
            printf("Continue...\n");
            green_first_press = 1;

            draw_background(screen_ptr);
            print_statistics(screen_ptr, *statistics_ptr);
            print_score(screen_ptr, *score_ptr);
            print_best_score(screen_ptr, *best_score_ptr);
            if (*show_next_element_ptr) {
                print_next_block(screen_ptr, *next_block_index_ptr);
            }
            print_destroyed_lines_number(screen_ptr, *lines_number_ptr);
        }
        if (green_first_press && !is_green_knob_pressed(io)) {
            green_first_press = 0;
        }
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }

    printf("Exiting pause thread...\n");
    return NULL;
}

static unsigned int get_best_score() {
    FILE *bestscore_f = fopen(BEST_SCORE_FILENAME, "rb");
    if (!bestscore_f) {
        return 0;
    }

    unsigned int return_value = (getc(bestscore_f)) | (getc(bestscore_f) << 8) | (getc(bestscore_f) << 16) | (getc(bestscore_f) << 24);
    fclose(bestscore_f);

    printf("Best score is %d.\n", return_value);
    return return_value;
}

static void set_best_score(unsigned int value) {
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
