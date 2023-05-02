#ifndef BLOCK_H
#define BLOCK_H

/* Blue */
#define BLOCK_I_TYPE_1  0x0f00
#define BLOCK_I_TYPE_2  0x2222
#define BLOCK_I_TYPE_3  0x00f0
#define BLOCK_I_TYPE_4  0x4444
unsigned short BLOCK_I_TYPE[] = {BLOCK_I_TYPE_1, BLOCK_I_TYPE_2, BLOCK_I_TYPE_3, BLOCK_I_TYPE_4};

/* Dark blue */
#define BLOCK_L_REVERSED_TYPE_1     0x8e0
#define BLOCK_L_REVERSED_TYPE_2     0x644
#define BLOCK_L_REVERSED_TYPE_3     0x0e2
#define BLOCK_L_REVERSED_TYPE_4     0x44c
unsigned short BLOCK_L_REVERSED_TYPE[] = {BLOCK_L_REVERSED_TYPE_1, BLOCK_L_REVERSED_TYPE_2, BLOCK_L_REVERSED_TYPE_3, BLOCK_L_REVERSED_TYPE_4};

/* Orange */
#define BLOCK_L_TYPE_1  0x2e0
#define BLOCK_L_TYPE_2  0x446
#define BLOCK_L_TYPE_3  0x0e8
#define BLOCK_L_TYPE_4  0xc44
unsigned short BLOCK_L_TYPE[] = {BLOCK_L_TYPE_1, BLOCK_L_TYPE_2, BLOCK_L_TYPE_3, BLOCK_L_TYPE_4};

/* Yellow */
#define BLOCK_SQUARE_TYPE   0xcc

/* Green */
#define BLOCK_S_TYPE_1  0x6c0
#define BLOCK_S_TYPE_2  0x462
#define BLOCK_S_TYPE_3  0x06c
#define BLOCK_S_TYPE_4  0x8c4
unsigned short BLOCK_S_TYPE[] = {BLOCK_S_TYPE_1, BLOCK_S_TYPE_2, BLOCK_S_TYPE_3, BLOCK_S_TYPE_4};

/* Purple */
#define BLOCK_T_TYPE_1  0x4e0
#define BLOCK_T_TYPE_2  0x464
#define BLOCK_T_TYPE_3  0x0e4
#define BLOCK_T_TYPE_4  0x4c4
unsigned short BLOCK_T_TYPE[] = {BLOCK_T_TYPE_1, BLOCK_T_TYPE_2, BLOCK_T_TYPE_3, BLOCK_T_TYPE_4};

/* Red */
#define BLOCK_Z_TYPE_1  0xc60
#define BLOCK_Z_TYPE_2  0x264
#define BLOCK_Z_TYPE_3  0x0c6
#define BLOCK_Z_TYPE_4  0x4c8
unsigned short BLOCK_Z_TYPE[] = {BLOCK_Z_TYPE_1, BLOCK_Z_TYPE_2, BLOCK_Z_TYPE_3, BLOCK_Z_TYPE_4};

typedef struct {
    unsigned char type; /* Block type */
    unsigned char x;    /* Blocks position */
    unsigned char y;
    unsigned char state; /* Blocks state (from 1 to 4) */
} block_t;

block_t * spawn_block(unsigned char **gamefield, unsigned char block_type);
void move_block_right(unsigned char **gamefield, block_t *block);
void move_block_left(unsigned char **gamefield, block_t *block);
void move_block_down(unsigned char **gamefield, block_t *block);
void drop_block(unsigned char **gamefield, block_t *block);
void rotate_block_right(unsigned char **gamefield, block_t *block);
void rotate_block_left(unsigned char **gamefield, block_t *block);

#endif
