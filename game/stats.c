#include "stats.h"

#include <stdio.h>
#include <stdlib.h>

#include "tools/colors.h"
#include "tools/font.h"

#define BLOCK_TYPES                     7
#define STATISTICS_TEXT_POSITION_X      64
#define SCORE_NUMBER_POSITION_X         372
#define SCORE_NUMBER_POSITION_Y         38
#define BEST_SCORE_NUMBER_POSITION_X    372 
#define BEST_SCORE_NUMBER_POSITION_Y    93
#define LINES_NUMBER_POSITION_X         419
#define LINES_NUMBER_POSITION_Y         240

static int find_statistics_position_y(unsigned char block_type){
    if (block_type == GREEN_BLOCK_TYPE) {
        return 33;
    }
    if (block_type == RED_BLOCK_TYPE) {
        return 73;
    }
    if (block_type == PURPLE_BLOCK_TYPE) {
        return 113;
    }
    if (block_type == YELLOW_BLOCK_TYPE) {
        return 153;
    }
    if (block_type == DARKBLUE_BLOCK_TYPE) {
        return 193;
    }
    if (block_type == ORANGE_BLOCK_TYPE) {
        return 233;
    }
    if (block_type == BLUE_BLOCK_TYPE) {
        return 273;
    }
    return 321; /* There is no bug if you don't see it :) */
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

void print_statistics(unsigned short **screen, unsigned int *statistics) {
    char *blocks_number_str;
    for (int statistics_i = 0; statistics_i < BLOCK_TYPES; statistics_i++) {
        blocks_number_str = int_to_str3(statistics[statistics_i]);
        draw_string(screen, STATISTICS_TEXT_POSITION_X, find_statistics_position_y(statistics_i+1), blocks_number_str, WHITE_RGB565, BLACK_RGB565);
        free(blocks_number_str);
    }
}

void print_score(unsigned short **screen, unsigned int score) {
    char *score_str = int_to_str6(score);
    draw_string(screen, SCORE_NUMBER_POSITION_X, SCORE_NUMBER_POSITION_Y, score_str, WHITE_RGB565, BLACK_RGB565);
    free(score_str);
}

void print_best_score(unsigned short **screen, unsigned int best_score) {
    char *best_score_str = int_to_str6(best_score);
    draw_string(screen, BEST_SCORE_NUMBER_POSITION_X, BEST_SCORE_NUMBER_POSITION_Y, best_score_str, WHITE_RGB565, BLACK_RGB565);
    free(best_score_str);
}

void print_destroyed_lines_number(unsigned short **screen, unsigned int lines_amount) {
    char *lines_amount_str = int_to_str3(lines_amount);
    draw_string(screen, LINES_NUMBER_POSITION_X, LINES_NUMBER_POSITION_Y, lines_amount_str, WHITE_RGB565, BLACK_RGB565);
    free(lines_amount_str);
}
