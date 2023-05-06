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
#include "gameover.h"

#define BEST_SCORE_FILENAME     "bestscore.data"
#define MAX_BLOCKS_SPEED        24
#define KNOB_DEAD_ZONE_VALUE    3

unsigned char audio_volume = 30;
unsigned char audio_enabled;

static unsigned int get_best_score();
static void set_best_score(unsigned int value);
static void *audio_thread(void *io);

void start_game(unsigned short **screen, phys_addr_t *io, unsigned char *blocks_speed, unsigned char *show_next_element, unsigned char *enable_audio) {
    pthread_t audio_tid;

    unsigned int statistics[7] = {0, 0, 0, 0, 0, 0, 0};
    unsigned int score = 0;
    unsigned int next_level_score_trigger = *blocks_speed * 1000;
    unsigned int best_score = get_best_score();
    unsigned int lines_number = 0;

    unsigned int blocks_led_colors[7] = { GREEN_RGB888, RED_RGB888, PURPLE_RGB888, YELLOW_RGB888, DARKBLUE_RGB888, ORANGE_RGB888, BLUE_RGB888 };

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
    uint8_t green_knob_first_press = 1;
    uint8_t blue_knob_current_state_value = get_blue_knob_value(io);
    uint8_t blue_knob_previous_state_value = blue_knob_current_state_value;
    unsigned int cleared_rows_at_the_moment;
    unsigned char pause_option;
    unsigned char game_is_running;
    unsigned char last_row = 0;

    srand(time(NULL));
    block_t *current_block = spawn_random_block(gamefield);
    unsigned char next_block_index = get_next_block_index(statistics, current_block);
    printf("Current block: %d, Next block: %d\n", current_block->type, next_block_index);

    draw_background(screen);
    print_statistics(screen, statistics);
    print_score(screen, score);
    print_best_score(screen, best_score);
    if (show_next_element) {
        print_next_block(screen, next_block_index);
        set_led_rgb1_color(io, blocks_led_colors[current_block->type-8]);
        set_led_rgb2_color(io, blocks_led_colors[next_block_index-8]);
    }
    print_destroyed_lines_number(screen, lines_number);

    audio_enabled = *enable_audio;
    if (audio_enabled) {
        pthread_create(&audio_tid, NULL, audio_thread, (void *)io);
    }

    printf("Starting game loop...");
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 14 * 1000 * 1000};
    struct timespec new_block_delay = {.tv_sec = 0, .tv_nsec = 52 * 1000 * 1000};
    struct timespec update_call_time = {.tv_sec = 0, .tv_nsec = 0};
    clock_gettime(CLOCK_MONOTONIC, &update_call_time);

    game_is_running = 1;
    while (game_is_running) {
        /* Pause */
        if (is_green_knob_pressed(io) && !green_knob_first_press) {
            printf("Pause...\n");
            pause_option = pause(screen, io, enable_audio, &audio_volume);
            if (pause_option == GO_TO_MENU) {
                printf("Go to menu...\n");
                game_is_running = 0;
                audio_enabled = 0;
                break;
            }
            if (!audio_enabled && *enable_audio) {
                pthread_create(&audio_tid, NULL, audio_thread, (void *)io);
            }
            audio_enabled = *enable_audio;
            set_audio_volume(io, audio_volume);
            printf("Enable audio ? %d\n", *enable_audio);
            printf("Continue...\n");
            draw_background(screen);
            print_statistics(screen, statistics);
            print_score(screen, score);
            print_best_score(screen, best_score);
            if (show_next_element) {
                print_next_block(screen, next_block_index);
                set_led_rgb1_color(io, blocks_led_colors[current_block->type-8]);
                set_led_rgb2_color(io, blocks_led_colors[next_block_index-8]);
            }
            print_destroyed_lines_number(screen, lines_number);
            green_knob_first_press = 1;
        }
        if (green_knob_first_press && !is_green_knob_pressed(io)) {
            green_knob_first_press = 0;
        }

        /* Moving */
        blue_knob_current_state_value = get_blue_knob_value(io);
        if (blue_knob_current_state_value - blue_knob_previous_state_value > KNOB_DEAD_ZONE_VALUE) {
            if (blue_knob_current_state_value - blue_knob_previous_state_value < 10 * KNOB_DEAD_ZONE_VALUE) {
                move_block_left(gamefield, current_block);
            }
            blue_knob_previous_state_value = blue_knob_current_state_value;
        } else if (blue_knob_current_state_value - blue_knob_previous_state_value < -KNOB_DEAD_ZONE_VALUE) {
            if (blue_knob_current_state_value - blue_knob_previous_state_value > -(10 * KNOB_DEAD_ZONE_VALUE)) {
                move_block_right(gamefield, current_block);
            }
            blue_knob_previous_state_value = blue_knob_current_state_value;
        }

        /* Rotating */
        red_knob_current_state_value = get_red_knob_value(io);
        if (red_knob_current_state_value - red_knob_previous_state_value > KNOB_DEAD_ZONE_VALUE) {
            if (red_knob_current_state_value - red_knob_previous_state_value < 10 * KNOB_DEAD_ZONE_VALUE) {
                rotate_block_left(gamefield, current_block);
            }
            red_knob_previous_state_value = red_knob_current_state_value;
        } else if (red_knob_current_state_value - red_knob_previous_state_value < -KNOB_DEAD_ZONE_VALUE) {
            if (red_knob_current_state_value - red_knob_previous_state_value > -(10 * KNOB_DEAD_ZONE_VALUE)) {
                rotate_block_right(gamefield, current_block);
            }
            red_knob_previous_state_value = red_knob_current_state_value;
        }

        /* Drop */
        if (is_red_knob_pressed(io) && red_knob_first_press) {
            red_knob_first_press = 0;
            drop_block(gamefield, current_block, &last_row);
            cleared_rows_at_the_moment = clear_rows(gamefield, screen, io, *blocks_speed);
            if (cleared_rows_at_the_moment > 0) {
                score += calculate_score(*blocks_speed, cleared_rows_at_the_moment);
                if (*blocks_speed < MAX_BLOCKS_SPEED) {
                    while (score > next_level_score_trigger) {
                        (*blocks_speed)++;
                        next_level_score_trigger *= 2;

                        printf("Blocks speed became %d, next level score trigger = %d\n", *blocks_speed, next_level_score_trigger);
                    }

                }
                print_score(screen, score);

                printf("%d rows has been cleared.\n", cleared_rows_at_the_moment);
                lines_number += cleared_rows_at_the_moment;
                print_destroyed_lines_number(screen, lines_number);
            }
            statistics[current_block->type-8]++;
            print_statistics(screen, statistics);

            free(current_block);
            current_block = spawn_block(gamefield, next_block_index);
            next_block_index = get_next_block_index(statistics, current_block);

            if (show_next_element) {
                print_next_block(screen, next_block_index);
                set_led_rgb1_color(io, blocks_led_colors[current_block->type-8]);
                set_led_rgb2_color(io, blocks_led_colors[next_block_index-8]);
            }

            if (check_gameover(gamefield)) {
                printf("Gameover...\n");
                gameover(screen, gamefield, io);
                audio_enabled = 0;
                break;
            }
            clock_nanosleep(CLOCK_MONOTONIC, 0, &new_block_delay, NULL);
        } 
        if (!red_knob_first_press && !is_red_knob_pressed(io)) {
            red_knob_first_press = 1;
        }

        /* Soft drop */
        if (is_blue_knob_pressed(io)) {
            move_block_down(gamefield, current_block, &last_row);
        }

        if (update_gamefield(gamefield, current_block, &update_call_time, *blocks_speed, &last_row)) {
            cleared_rows_at_the_moment = clear_rows(gamefield, screen, io, *blocks_speed);
            if (cleared_rows_at_the_moment > 0) {
                score += calculate_score(*blocks_speed, cleared_rows_at_the_moment);
                if (*blocks_speed < MAX_BLOCKS_SPEED) {
                    while (score > next_level_score_trigger) {
                        blocks_speed++;
                        next_level_score_trigger *= 2;

                        printf("Blocks speed became %d, next level score trigger = %d\n", *blocks_speed, next_level_score_trigger);
                    }

                }
                print_score(screen, score);

                printf("%d rows has been cleared.\n", cleared_rows_at_the_moment);
                lines_number += cleared_rows_at_the_moment;
                print_destroyed_lines_number(screen, lines_number);
            }
            statistics[current_block->type-8]++;
            print_statistics(screen, statistics);

            free(current_block);
            current_block = spawn_block(gamefield, next_block_index);
            next_block_index = get_next_block_index(statistics, current_block);

            if (show_next_element) {
                print_next_block(screen, next_block_index);
                set_led_rgb1_color(io, blocks_led_colors[current_block->type-8]);
                set_led_rgb2_color(io, blocks_led_colors[next_block_index-8]);
            }

            if (check_gameover(gamefield)) {
                printf("Gameover...\n");
                gameover(screen, gamefield, io);
                audio_enabled = 0;
                break;
            }
        }

        draw_gamefield(screen, gamefield);

        set_led_line_value(io, get_block_led_line_value(current_block));
        lcd_display(io, screen);
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }

    set_led_line_value(io, 0x00000000);
    set_led_rgb1_color(io, BLACK_RGB888);
    set_led_rgb2_color(io, BLACK_RGB888);
    printf("Game loop has ended...\n");
    for (int row = 0; row < GAMEFIELD_SIZE; row++) {
        free(gamefield[row]);
    }
    free(gamefield);
    free(current_block);
    if (score > best_score) {
        set_best_score(score);
    }
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
        printf("Writing bestscore to file: (%d) %x %x %x %x.\n", value, (value & 0xff000000) >> 24, (value & 0x00ff0000) >> 16, (value & 0x0000ff00) >> 8, value & 0x000000ff);
        fputc(value & 0x000000ff, bestscore_f);
        fputc((value & 0x0000ff00) >> 8, bestscore_f);
        fputc((value & 0x00ff0000) >> 16, bestscore_f);
        fputc((value & 0xff000000) >> 24, bestscore_f);
    }
    fclose(bestscore_f);
}

#define E6      659.25511
#define B5      493.8833
#define C6      523.25113
#define D6      587.32954
#define A5      440.0
#define F6      698.45646
#define A6      880.0
#define G6      783.99087

#define DURATION_1      203125   
#define DURATION_2      406250
#define DURATION_3      609375
#define DURATION_4      812500
#define DURATION_5      1015625

#define SONG_DURATION   37

double frequency[] = {
    E6, B5, C6, D6, C6, B5,
    A5, A5, C6, E6, D6, C6,
    B5, B5, C6, D6, E6,
    C6, A5, A5,
    D6, F6, A6,
    G6, F6, E6, 
    C6, E6, D6, C6, B5,
    C6, D6, E6, C6, A5, A5
};

unsigned int duration[] = {
    DURATION_2, DURATION_1, DURATION_1, DURATION_2, DURATION_1, DURATION_1,
    DURATION_2, DURATION_1, DURATION_1, DURATION_2, DURATION_1, DURATION_1, 
    DURATION_2, DURATION_1, DURATION_1, DURATION_2, DURATION_2,
    DURATION_2, DURATION_2, DURATION_5,
    DURATION_2, DURATION_1, DURATION_2,
    DURATION_1, DURATION_1, DURATION_3,
    DURATION_1, DURATION_2, DURATION_1, DURATION_1, DURATION_3,
    DURATION_1, DURATION_2, DURATION_2, DURATION_2, DURATION_2, DURATION_4
};

unsigned int get_period(double frequency) {
    return (unsigned int)(100000000/frequency);
}

static void *audio_thread(void *io) {
    io = (phys_addr_t *)io;
    struct timespec delay;

    set_audio_volume(io, audio_volume);
    while (audio_enabled) {
        for (int i = 0; i < 37; i++) {
            if (audio_enabled == 0) {
                break;
            }
            set_audio_period(io, get_period(frequency[i]));
            if (duration[i] == DURATION_5) {
                delay.tv_sec = 1;
                delay.tv_nsec = (DURATION_5 % 1000000) * 1000;
                clock_nanosleep(CLOCK_MONOTONIC, 0, &delay, NULL);
            } else {
                delay.tv_sec = 0;
                delay.tv_nsec = duration[i] * 1000;
                clock_nanosleep(CLOCK_MONOTONIC, 0, &delay, NULL);
            }
        }
        set_audio_period(io, 0);
        delay.tv_sec = 1;
        clock_nanosleep(CLOCK_MONOTONIC, 0, &delay, NULL);
    }
    set_audio_volume(io, 0);
    set_audio_period(io, 0);

    return NULL;
}
