#ifndef BLOCK_H
#define BLOCK_H

/* Blue */
#define BLOCK_I_TYPE_1  0x0f00
#define BLOCK_I_TYPE_2  0x2222
#define BLOCK_I_TYPE_3  0x00f0
#define BLOCK_I_TYPE_4  0x4444
/* unsigned short BLOCK_I_TYPE[] = {BLOCK_I_TYPE_1, BLOCK_I_TYPE_2, BLOCK_I_TYPE_3, BLOCK_I_TYPE_4}; */

/* Dark blue */
#define BLOCK_L_REVERSED_TYPE_1     0x8e00
#define BLOCK_L_REVERSED_TYPE_2     0x6440
#define BLOCK_L_REVERSED_TYPE_3     0x0e20
#define BLOCK_L_REVERSED_TYPE_4     0x44c0
/* unsigned short BLOCK_L_REVERSED_TYPE[] = {BLOCK_L_REVERSED_TYPE_1, BLOCK_L_REVERSED_TYPE_2, BLOCK_L_REVERSED_TYPE_3, BLOCK_L_REVERSED_TYPE_4}; */

/* Orange */
#define BLOCK_L_TYPE_1  0x2e00
#define BLOCK_L_TYPE_2  0x4460
#define BLOCK_L_TYPE_3  0x0e80
#define BLOCK_L_TYPE_4  0xc440
/* unsigned short BLOCK_L_TYPE[] = {BLOCK_L_TYPE_1, BLOCK_L_TYPE_2, BLOCK_L_TYPE_3, BLOCK_L_TYPE_4}; */

/* Yellow */
#define BLOCK_SQUARE_TYPE   0xcc00

/* Green */
#define BLOCK_S_TYPE_1  0x6c00
#define BLOCK_S_TYPE_2  0x4620
#define BLOCK_S_TYPE_3  0x06c0
#define BLOCK_S_TYPE_4  0x8c40
/* unsigned short BLOCK_S_TYPE[] = {BLOCK_S_TYPE_1, BLOCK_S_TYPE_2, BLOCK_S_TYPE_3, BLOCK_S_TYPE_4}; */

/* Purple */
#define BLOCK_T_TYPE_1  0x4e00
#define BLOCK_T_TYPE_2  0x4640
#define BLOCK_T_TYPE_3  0x0e40
#define BLOCK_T_TYPE_4  0x4c40
/* unsigned short BLOCK_T_TYPE[] = {BLOCK_T_TYPE_1, BLOCK_T_TYPE_2, BLOCK_T_TYPE_3, BLOCK_T_TYPE_4}; */

/* Red */
#define BLOCK_Z_TYPE_1  0xc600
#define BLOCK_Z_TYPE_2  0x2640
#define BLOCK_Z_TYPE_3  0x0c60
#define BLOCK_Z_TYPE_4  0x4c80
/* unsigned short BLOCK_Z_TYPE[] = {BLOCK_Z_TYPE_1, BLOCK_Z_TYPE_2, BLOCK_Z_TYPE_3, BLOCK_Z_TYPE_4}; */

typedef struct {
    unsigned char type; /* Block type */
    int x;    /* Blocks position */
    int y;
    unsigned char state; /* Blocks state (from 1 to 4) */
} block_t;

block_t * spawn_block(unsigned char **gamefield, unsigned char block_type);
block_t * spawn_random_block(unsigned char **gamefield);
unsigned char get_next_block_index(unsigned int *statistics, block_t *current_block);
unsigned char move_block_right(unsigned char **gamefield, block_t *block);
unsigned char move_block_left(unsigned char **gamefield, block_t *block);
unsigned char move_block_down(unsigned char **gamefield, block_t *block, unsigned char *last_row);
void drop_block(unsigned char **gamefield, block_t *block, unsigned char *last_row);
void rotate_block_right(unsigned char **gamefield, block_t *block);
void rotate_block_left(unsigned char **gamefield, block_t *block);
unsigned int get_block_led_line_value(block_t *block);

#endif
