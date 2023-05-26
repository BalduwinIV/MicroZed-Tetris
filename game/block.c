#include "block.h"

#include <stdio.h>
#include <stdlib.h>

#include "tools/colors.h"
#include "gamefield.h"

static unsigned short blocks_type_array[7][4] = {
    { BLOCK_S_TYPE_1, BLOCK_S_TYPE_2, BLOCK_S_TYPE_3, BLOCK_S_TYPE_4 },
    { BLOCK_Z_TYPE_1, BLOCK_Z_TYPE_2, BLOCK_Z_TYPE_3, BLOCK_Z_TYPE_4 },
    { BLOCK_T_TYPE_1, BLOCK_T_TYPE_2, BLOCK_T_TYPE_3, BLOCK_T_TYPE_4 },
    { BLOCK_SQUARE_TYPE, BLOCK_SQUARE_TYPE, BLOCK_SQUARE_TYPE, BLOCK_SQUARE_TYPE },
    { BLOCK_L_REVERSED_TYPE_1, BLOCK_L_REVERSED_TYPE_2, BLOCK_L_REVERSED_TYPE_3, BLOCK_L_REVERSED_TYPE_4 },
    { BLOCK_L_TYPE_1, BLOCK_L_TYPE_2, BLOCK_L_TYPE_3, BLOCK_L_TYPE_4 },
    { BLOCK_I_TYPE_1, BLOCK_I_TYPE_2, BLOCK_I_TYPE_3, BLOCK_I_TYPE_4 }
};

/* Draws given block on the gamefield. */
static void draw_figure(unsigned char **gamefield, block_t *block) {
    for (int pixel_i = 0; pixel_i < 16; pixel_i++) {
        if ((block->y + pixel_i/4 >= 0) && (block->y + pixel_i/4 < GAMEFIELD_SIZE) && (block->x + pixel_i%4 >= 0) && (block->x + pixel_i%4 < 10)) {
            gamefield[block->y + pixel_i/4][block->x + pixel_i%4] = (blocks_type_array[block->type-8][block->state] & (0x8000 >> pixel_i)) ? block->type : gamefield[block->y + pixel_i/4][block->x + pixel_i%4]; 
        }
    }
}

/* Erases block from the gamefield. */
static void erase_block(unsigned char **gamefield, block_t *block) {
    for (int pixel_i = 0; pixel_i < 16; pixel_i++) {
        if ((block->y + pixel_i/4 >= 0) && (block->y + pixel_i/4 < GAMEFIELD_SIZE) && (block->x + pixel_i%4 >= 0) && (block->x + pixel_i%4 < 10)) {
            gamefield[block->y + pixel_i/4][block->x + pixel_i%4] = (blocks_type_array[block->type-8][block->state] & (0x8000 >> pixel_i)) ? NO_BLOCK : gamefield[block->y + pixel_i/4][block->x + pixel_i%4]; 
        }
    }
}

/* Checks if given position is free on the gamefield. */
static unsigned char is_free(unsigned char **gamefield, int x, int y) {
    if ((y >= 0) && (y < GAMEFIELD_SIZE) && (x >= 0) && (x < 10)) {
        return (gamefield[y][x] == NO_BLOCK) ? 1 : 0;
    }
    return 0;
}


block_t * spawn_block(unsigned char **gamefield, unsigned char block_type) {
    block_t *block = (block_t *)malloc(sizeof(block_t));
    if (!block) {
        fprintf(stderr, "Malloc failed (block.c).\n");
        exit(1);
    }
    block->type = block_type;
    block->state = 0;

    if (block_type == BLUE_FALLING_BLOCK_TYPE) {
        block->x = 3;
        block->y = 2;
    } else if (block_type == YELLOW_BLOCK_TYPE) {
        block->x = 4;
        block->y = 1;
    } else {
        block->x = 3;
        block->y = 1;
    }
    
    draw_figure(gamefield, block);

    return block;
}

block_t * spawn_random_block(unsigned char **gamefield) {
    unsigned char block_index = rand() % 7 + 8;
    return spawn_block(gamefield, block_index);
}

unsigned char get_next_block_index(unsigned int *statistics, block_t *current_block) {
    unsigned int minimum_count = statistics[0]+1;
    for (int i = 0; i < 7; i++) {
        if (i == current_block->type - 8) {
            if (statistics[i]+1 < minimum_count) {
                minimum_count = statistics[i]+1;
            }
        } else {
            if (statistics[i] < minimum_count) {
                minimum_count = statistics[i];
            }
        }
    }
    unsigned char number_of_less_than_average = 0;
    unsigned char less_than_average[7];

    for (int i = 0; i < 7; i++) {
        if (i == current_block->type - 8) {
            if (statistics[i]+1 == minimum_count) {
                less_than_average[number_of_less_than_average] = i;
                number_of_less_than_average++;
            }
        } else {
            if (statistics[i] == minimum_count) {
                less_than_average[number_of_less_than_average] = i;
                number_of_less_than_average++;
            }
        }
    }
    
    return less_than_average[rand() % number_of_less_than_average] + 8;
}

unsigned char move_block_right(unsigned char **gamefield, block_t *block) {
    if (block->type == BLUE_FALLING_BLOCK_TYPE) {
        if (block->state == 0) {
            if (is_free(gamefield, block->x+4, block->y+1)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 1) {
            if (is_free(gamefield, block->x+3, block->y) &&
                    is_free(gamefield, block->x+3, block->y+1) &&
                    is_free(gamefield, block->x+3, block->y+2) &&
                    is_free(gamefield, block->x+3, block->y+3)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 2) {
            if (is_free(gamefield, block->x+4, block->y+2)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 3) {
            if (is_free(gamefield, block->x+2, block->y) &&
                    is_free(gamefield, block->x+2, block->y+1) &&
                    is_free(gamefield, block->x+2, block->y+2) &&
                    is_free(gamefield, block->x+2, block->y+3)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        }
    } else if (block->type == DARKBLUE_FALLING_BLOCK_TYPE) {
        if (block->state == 0) {
            if (is_free(gamefield, block->x+1, block->y) &&
                    is_free(gamefield, block->x+3, block->y+1)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 1) {
            if (is_free(gamefield, block->x+3, block->y) &&
                    is_free(gamefield, block->x+2, block->y+1) &&
                    is_free(gamefield, block->x+2, block->y+2)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 2) {
            if (is_free(gamefield, block->x+3, block->y+1) &&
                    is_free(gamefield, block->x+3, block->y+2)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 3) {
            if (is_free(gamefield, block->x+2, block->y) &&
                    is_free(gamefield, block->x+2, block->y+1) &&
                    is_free(gamefield, block->x+2, block->y+2)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        }
    } else if (block->type == ORANGE_FALLING_BLOCK_TYPE) {
        if (block->state == 0) {
            if (is_free(gamefield, block->x+3, block->y) &&
                    is_free(gamefield, block->x+3, block->y+1)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;

            }
        } else if (block->state == 1) {
            if (is_free(gamefield, block->x+2, block->y) &&
                    is_free(gamefield, block->x+2, block->y+1) &&
                    is_free(gamefield, block->x+3, block->y+2)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 2) {
            if (is_free(gamefield, block->x+3, block->y+1) &&
                    is_free(gamefield, block->x+1, block->y+2)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 3) {
            if (is_free(gamefield, block->x+2, block->y) &&
                    is_free(gamefield, block->x+2, block->y+1) &&
                    is_free(gamefield, block->x+2, block->y+2)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        }
    } else if (block->type == YELLOW_FALLING_BLOCK_TYPE) {
        if (is_free(gamefield, block->x+2, block->y) &&
                is_free(gamefield, block->x+2, block->y+1)) {
            erase_block(gamefield, block);
            block->x++;
            draw_figure(gamefield, block);
            return 1;
        }
    } else if (block->type == GREEN_FALLING_BLOCK_TYPE) {
        if (block->state == 0) {
            if (is_free(gamefield, block->x+3, block->y) && 
                    is_free(gamefield, block->x+2, block->y+1)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 1) {
            if (is_free(gamefield, block->x+2, block->y) &&
                    is_free(gamefield, block->x+3, block->y+1) &&
                    is_free(gamefield, block->x+3, block->y+2)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 2) {
            if (is_free(gamefield, block->x+3, block->y+1) &&
                    is_free(gamefield, block->x+2, block->y+2)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 3) {
            if (is_free(gamefield, block->x+1, block->y) &&
                    is_free(gamefield, block->x+2, block->y+1) &&
                    is_free(gamefield, block->x+2, block->y+2)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        }
    } else if (block->type == PURPLE_FALLING_BLOCK_TYPE) {
        if (block->state == 0) {
            if (is_free(gamefield, block->x+2, block->y) &&
                    is_free(gamefield, block->x+3, block->y+1)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 1) {
            if (is_free(gamefield, block->x+2, block->y) &&
                    is_free(gamefield, block->x+3, block->y+1) &&
                    is_free(gamefield, block->x+2, block->y+2)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 2) {
            if (is_free(gamefield, block->x+3, block->y+1) &&
                    is_free(gamefield, block->x+2, block->y+2)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 3) {
            if (is_free(gamefield, block->x+2, block->y) &&
                    is_free(gamefield, block->x+2, block->y+1) &&
                    is_free(gamefield, block->x+2, block->y+2)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        }
    } else if (block->type == RED_FALLING_BLOCK_TYPE) {
        if (block->state == 0) {
            if (is_free(gamefield, block->x+2, block->y) &&
                    is_free(gamefield, block->x+3, block->y+1)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 1) {
            if (is_free(gamefield, block->x+3, block->y) &&
                    is_free(gamefield, block->x+3, block->y+1) &&
                    is_free(gamefield, block->x+2, block->y+2)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 2) {
            if (is_free(gamefield, block->x+2, block->y+1) &&
                    is_free(gamefield, block->x+3, block->y+2)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 3) {
            if (is_free(gamefield, block->x+2, block->y) &&
                    is_free(gamefield, block->x+2, block->y+1) &&
                    is_free(gamefield, block->x+1, block->y+2)) {
                erase_block(gamefield, block);
                block->x++;
                draw_figure(gamefield, block);
                return 1;
            }
        }
    }
    return 0;
}

unsigned char move_block_left(unsigned char **gamefield, block_t *block) {
    if (block->type == BLUE_FALLING_BLOCK_TYPE) {
        if (block->state == 0) {
            if (is_free(gamefield, block->x-1, block->y+1)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 1) {
            if (is_free(gamefield, block->x+1, block->y) &&
                    is_free(gamefield, block->x+1, block->y+1) &&
                    is_free(gamefield, block->x+1, block->y+2) &&
                    is_free(gamefield, block->x+1, block->y+3)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 2) {
            if (is_free(gamefield, block->x-1, block->y+2)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 3) {
            if (is_free(gamefield, block->x, block->y) &&
                    is_free(gamefield, block->x, block->y+1) &&
                    is_free(gamefield, block->x, block->y+2) &&
                    is_free(gamefield, block->x, block->y+3)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        }
    } else if (block->type == DARKBLUE_FALLING_BLOCK_TYPE) {
        if (block->state == 0) {
            if (is_free(gamefield, block->x-1, block->y) &&
                    is_free(gamefield, block->x-1, block->y+1)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 1) {
            if (is_free(gamefield, block->x, block->y) &&
                    is_free(gamefield, block->x, block->y+1) &&
                    is_free(gamefield, block->x, block->y+2)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 2) {
            if (is_free(gamefield, block->x-1, block->y+1) &&
                    is_free(gamefield, block->x+1, block->y+2)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 3) {
            if (is_free(gamefield, block->x, block->y) &&
                    is_free(gamefield, block->x, block->y+1) &&
                    is_free(gamefield, block->x-1, block->y+2)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        }
    } else if (block->type == ORANGE_FALLING_BLOCK_TYPE) {
        if (block->state == 0) {
            if (is_free(gamefield, block->x+1, block->y) &&
                    is_free(gamefield, block->x-1, block->y+1)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;

            }
        } else if (block->state == 1) {
            if (is_free(gamefield, block->x, block->y) &&
                    is_free(gamefield, block->x, block->y+1) &&
                    is_free(gamefield, block->x, block->y+2)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 2) {
            if (is_free(gamefield, block->x-1, block->y+1) &&
                    is_free(gamefield, block->x-1, block->y+2)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 3) {
            if (is_free(gamefield, block->x-1, block->y) &&
                    is_free(gamefield, block->x, block->y+1) &&
                    is_free(gamefield, block->x, block->y+2)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        }
    } else if (block->type == YELLOW_FALLING_BLOCK_TYPE) {
        if (is_free(gamefield, block->x-1, block->y) &&
                is_free(gamefield, block->x-1, block->y+1)) {
            erase_block(gamefield, block);
            block->x--;
            draw_figure(gamefield, block);
            return 1;
        }
    } else if (block->type == GREEN_FALLING_BLOCK_TYPE) {
        if (block->state == 0) {
            if (is_free(gamefield, block->x, block->y) && 
                    is_free(gamefield, block->x-1, block->y+1)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 1) {
            if (is_free(gamefield, block->x, block->y) &&
                    is_free(gamefield, block->x, block->y+1) &&
                    is_free(gamefield, block->x+1, block->y+2)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 2) {
            if (is_free(gamefield, block->x, block->y+1) &&
                    is_free(gamefield, block->x-1, block->y+2)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 3) {
            if (is_free(gamefield, block->x-1, block->y) &&
                    is_free(gamefield, block->x-1, block->y+1) &&
                    is_free(gamefield, block->x, block->y+2)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        }
    } else if (block->type == PURPLE_FALLING_BLOCK_TYPE) {
        if (block->state == 0) {
            if (is_free(gamefield, block->x, block->y) &&
                    is_free(gamefield, block->x-1, block->y+1)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 1) {
            if (is_free(gamefield, block->x, block->y) &&
                    is_free(gamefield, block->x, block->y+1) &&
                    is_free(gamefield, block->x, block->y+2)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 2) {
            if (is_free(gamefield, block->x-1, block->y+1) &&
                    is_free(gamefield, block->x, block->y+2)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 3) {
            if (is_free(gamefield, block->x, block->y) &&
                    is_free(gamefield, block->x-1, block->y+1) &&
                    is_free(gamefield, block->x, block->y+2)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        }
    } else if (block->type == RED_FALLING_BLOCK_TYPE) {
        if (block->state == 0) {
            if (is_free(gamefield, block->x-1, block->y) &&
                    is_free(gamefield, block->x, block->y+1)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 1) {
            if (is_free(gamefield, block->x+1, block->y) &&
                    is_free(gamefield, block->x, block->y+1) &&
                    is_free(gamefield, block->x, block->y+2)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 2) {
            if (is_free(gamefield, block->x-1, block->y+1) &&
                    is_free(gamefield, block->x, block->y+2)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        } else if (block->state == 3) {
            if (is_free(gamefield, block->x, block->y) &&
                    is_free(gamefield, block->x-1, block->y+1) &&
                    is_free(gamefield, block->x-1, block->y+2)) {
                erase_block(gamefield, block);
                block->x--;
                draw_figure(gamefield, block);
                return 1;
            }
        }
    }
    
    return 0;
}

/* Checks if it is possible to move block down. */
unsigned char possible_to_move_block_down(unsigned char **gamefield, block_t *block) {
    if (block->type == BLUE_FALLING_BLOCK_TYPE) {
        if (block->state == 0) {
            if (is_free(gamefield, block->x, block->y+2) &&
                    is_free(gamefield, block->x+1, block->y+2) &&
                    is_free(gamefield, block->x+2, block->y+2) &&
                    is_free(gamefield, block->x+3, block->y+2)) {
                return 1;
            }
        } else if (block->state == 1) {
            if (is_free(gamefield, block->x+2, block->y+4)) {
                return 1;
            }
        } else if (block->state == 2) {
            if (is_free(gamefield, block->x, block->y+3) &&
                    is_free(gamefield, block->x+1, block->y+3) &&
                    is_free(gamefield, block->x+2, block->y+3) &&
                    is_free(gamefield, block->x+3, block->y+3)) {
                return 1;
            }
        } else if (block->state == 3) {
            if (is_free(gamefield, block->x+1, block->y+4)) {
                return 1;
            }
        }
    } else if (block->type == DARKBLUE_FALLING_BLOCK_TYPE) {
        if (block->state == 0) {
            if (is_free(gamefield, block->x, block->y+2) &&
                    is_free(gamefield, block->x+1, block->y+2) &&
                    is_free(gamefield, block->x+2, block->y+2)) {
                return 1;
            }
        } else if (block->state == 1) {
            if (is_free(gamefield, block->x+1, block->y+3) &&
                    is_free(gamefield, block->x+2, block->y+1)) {
                return 1;
            }
        } else if (block->state == 2) {
            if (is_free(gamefield, block->x, block->y+2) &&
                    is_free(gamefield, block->x+1, block->y+2) &&
                    is_free(gamefield, block->x+2, block->y+3)) {
                return 1;
            }
        } else if (block->state == 3) {
            if (is_free(gamefield, block->x, block->y+3) &&
                    is_free(gamefield, block->x+1, block->y+3)) {
                return 1;
            }
        }
    } else if (block->type == ORANGE_FALLING_BLOCK_TYPE) {
        if (block->state == 0) {
            if (is_free(gamefield, block->x, block->y+2) &&
                    is_free(gamefield, block->x+1, block->y+2) &&
                    is_free(gamefield, block->x+2, block->y+2)) {
                return 1;
            }
        } else if (block->state == 1) {
            if (is_free(gamefield, block->x+1, block->y+3) &&
                    is_free(gamefield, block->x+2, block->y+3)) {
                return 1;
            }
        } else if (block->state == 2) {
            if (is_free(gamefield, block->x, block->y+3) &&
                    is_free(gamefield, block->x+1, block->y+2) &&
                    is_free(gamefield, block->x+2, block->y+2)) {
                return 1;
            }
        } else if (block->state == 3) {
            if (is_free(gamefield, block->x, block->y+1) &&
                    is_free(gamefield, block->x+1, block->y+3)) {
                return 1;
            }
        }
    } else if (block->type == YELLOW_FALLING_BLOCK_TYPE) {
        if (is_free(gamefield, block->x, block->y+2) &&
            is_free(gamefield, block->x+1, block->y+2)) {
            return 1;
        }
    } else if (block->type == GREEN_FALLING_BLOCK_TYPE) {
        if (block->state == 0) {
            if (is_free(gamefield, block->x, block->y+2) && 
                    is_free(gamefield, block->x+1, block->y+2) &&
                    is_free(gamefield, block->x+2, block->y+1)) {
                return 1;
            }
        } else if (block->state == 1) {
            if (is_free(gamefield, block->x+1, block->y+2) &&
                    is_free(gamefield, block->x+2, block->y+3)) {
                return 1;
            }
        } else if (block->state == 2) {
            if (is_free(gamefield, block->x, block->y+3) &&
                    is_free(gamefield, block->x+1, block->y+3) &&
                    is_free(gamefield, block->x+2, block->y+2)) {
                return 1;
            }
        } else if (block->state == 3) {
            if (is_free(gamefield, block->x, block->y+2) &&
                    is_free(gamefield, block->x+1, block->y+3)) {
                return 1;
            }
        }
    } else if (block->type == PURPLE_FALLING_BLOCK_TYPE) {
        if (block->state == 0) {
            if (is_free(gamefield, block->x, block->y+2) &&
                    is_free(gamefield, block->x+1, block->y+2) &&
                    is_free(gamefield, block->x+2, block->y+2)) {
                return 1;
            }
        } else if (block->state == 1) {
            if (is_free(gamefield, block->x+1, block->y+3) &&
                    is_free(gamefield, block->x+2, block->y+2)) {
                return 1;
            }
        } else if (block->state == 2) {
            if (is_free(gamefield, block->x, block->y+2) &&
                    is_free(gamefield, block->x+1, block->y+3) &&
                    is_free(gamefield, block->x+2, block->y+2)) {
                return 1;
            }
        } else if (block->state == 3) {
            if (is_free(gamefield, block->x, block->y+2) &&
                    is_free(gamefield, block->x+1, block->y+3)) {
                return 1;
            }
        }
    } else if (block->type == RED_FALLING_BLOCK_TYPE) {
        if (block->state == 0) {
            if (is_free(gamefield, block->x, block->y+1) &&
                    is_free(gamefield, block->x+1, block->y+2) &&
                    is_free(gamefield, block->x+2, block->y+2)) {
                return 1;
            }
        } else if (block->state == 1) {
            if (is_free(gamefield, block->x+1, block->y+3) &&
                    is_free(gamefield, block->x+2, block->y+2)) {
                return 1;
            }
        } else if (block->state == 2) {
            if (is_free(gamefield, block->x, block->y+2) &&
                    is_free(gamefield, block->x+1, block->y+3) &&
                    is_free(gamefield, block->x+2, block->y+3)) {
                return 1;
            }
        } else if (block->state == 3) {
            if (is_free(gamefield, block->x, block->y+3) &&
                    is_free(gamefield, block->x+1, block->y+2)) {
                return 1;
            }
        }
    }

    return 0;
}

unsigned char move_block_down(unsigned char **gamefield, block_t *block, unsigned char *last_row) {
    if (possible_to_move_block_down(gamefield, block)) {
        *last_row = 0;
        erase_block(gamefield, block);
        block->y++;
        draw_figure(gamefield, block);
        return 1;
    }
    *last_row = 1;
    return 0;
}

void drop_block(unsigned char **gamefield, block_t *block, unsigned char *last_row) {
    while(move_block_down(gamefield, block, last_row));
    for (int pixel_i = 0; pixel_i < 16; pixel_i++) {
        if ((block->y + pixel_i/4 >= 0) && (block->y + pixel_i/4 < GAMEFIELD_SIZE) && (block->x + pixel_i%4 >= 0) && (block->x + pixel_i%4 < 10)) {
            gamefield[block->y + pixel_i/4][block->x + pixel_i%4] = (blocks_type_array[block->type-8][block->state] & (0x8000 >> pixel_i)) ? block->type-7 : gamefield[block->y + pixel_i/4][block->x + pixel_i%4]; 
        }
    }
}

void rotate_block_right(unsigned char **gamefield, block_t *block) {
    unsigned char is_rotatable = 1;
    for (int pixel_i = 0; pixel_i < 16; pixel_i++) {
        if (blocks_type_array[block->type-8][(block->state + 1) % 4] & (0x8000 >> pixel_i)) {
            if ((block->y + pixel_i/4 < 0) || (block->y + pixel_i/4 >= GAMEFIELD_SIZE) || (block->x + pixel_i%4 < 0) || (block->x + pixel_i%4 >= 10) || (gamefield[block->y + pixel_i/4][block->x + pixel_i%4] != NO_BLOCK && gamefield[block->y + pixel_i/4][block->x + pixel_i%4] != block->type)) {
                is_rotatable = 0;
                break;
            }
        }
    }

    if (is_rotatable) {
        erase_block(gamefield, block);
        block->state = (block->state + 1) % 4;
        draw_figure(gamefield, block);
    }
}

void rotate_block_left(unsigned char **gamefield, block_t *block) {
    unsigned char is_rotatable = 1;
    for (int pixel_i = 0; pixel_i < 16; pixel_i++) {
        if (blocks_type_array[block->type-8][(block->state + 3) % 4] & (0x8000 >> pixel_i)) {
            if ((block->y + pixel_i/4 < 0) || (block->y + pixel_i/4 >= GAMEFIELD_SIZE) || (block->x + pixel_i%4 < 0) || (block->x + pixel_i%4 >= 10) || (gamefield[block->y + pixel_i/4][block->x + pixel_i%4] != NO_BLOCK && gamefield[block->y + pixel_i/4][block->x + pixel_i%4] != block->type)) {
                is_rotatable = 0;
                break;
            }
        }
    }

    if (is_rotatable) {
        erase_block(gamefield, block);
        block->state = (block->state + 3) % 4;
        draw_figure(gamefield, block);
    }
}

unsigned int get_block_led_line_value(block_t *block) {
    if (block->type == BLUE_FALLING_BLOCK_TYPE) {
        if (block->state == 0 || block->state == 2) {
            return 0x7ff80000 >> (block->x * 3);
        }
        if (block->state == 1) {
            return 0x01c00000 >> ((block->x+2) * 3);
        }
        if (block->state == 3) {
            return 0x0e000000 >> ((block->x+1) * 3);
        }
    } else if (block->type == DARKBLUE_FALLING_BLOCK_TYPE || 
            block->type == ORANGE_FALLING_BLOCK_TYPE || 
            block->type == GREEN_FALLING_BLOCK_TYPE ||
            block->type == PURPLE_FALLING_BLOCK_TYPE ||
            block->type == RED_FALLING_BLOCK_TYPE) {
        if (block->state == 0 || block->state == 2) {
            return 0x7fc00000 >> (block->x * 3);
        }
        if (block->state == 1) {
            return 0x0fc00000 >> ((block->x+1) * 3);
        }
        if (block->state == 3) {
            return 0x7e000000 >> (block->x * 3);
        }
    } else if (block->type == YELLOW_FALLING_BLOCK_TYPE) {
        return 0x7e000000 >> (block->x * 3);
    }
    return 0x00000000;
}
