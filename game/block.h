#ifndef BLOCK_H
#define BLOCK_H

typedef struct {
    unsigned char x;
    unsigned char y;
    unsigned char block_type;
    unsigned short matrix;
    unsigned char current_state;
} falling_block_t;

#endif
