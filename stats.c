#include <stats.h>
#include <colors.h>
#include <font.h>

void print_stats(unsigned int **screen, unsigned char block_type, char* amount, char* score){
    print_blocks_amount(screen, block_type, amount);
    draw_string(screen, 372, 38, score, WHITE_RGB565, BLACK_RGB565);
}

void print_blocks_amount(unsigned int **screen, unsigned char block_type, char* amount){
    int y = find_position(block_type);
    int x = 64;
    draw_string(screen, x, y, amount, WHITE_RGB565, BLACK_RGB565);
}

void print_best_score(unsigned int **screen, char* best_score){
    draw_string(screen, 372, 93, best_score, WHITE_RGB565, BLACK_RGB565);
}

void print_destroyed_lines(unsigned int **screen, char* amount){
    draw_string(screen, 372, 240, amount, WHITE_RGB565, BLACK_RGB565);
}

int find_position(unsigned char block_type){
    int position;
    if (block_type == GREEN_BLOCK_TYPE) {
        position = 33;
    } else if (block_type == RED_BLOCK_TYPE) {
        position = 73;
    } else if (block_type == PURPLE_BLOCK_TYPE) {
        position = 113;
    } else if (block_type == YELLOW_BLOCK_TYPE) {
        position = 153;
    } else if (block_type == DARKBLUE_BLOCK_TYPE) {
        position = 193;
    } else if (block_type == ORANGE_BLOCK_TYPE) {
        position = 233;
    } else if (block_type == BLUE_BLOCK_TYPE) {
        position = 273;
    }
    return position;
}


