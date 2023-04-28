#ifndef GRAPHICS_H
#define GRAPHICS_H

#define BLOCK_SIZE  20
void draw_block(unsigned int **screen, int x, int y, unsigned char block_type);

#define GAMEFIELD_X     140
#define GAMEFIELD_Y     9
void draw_gamefield(unsigned int **screen, char** field);

#endif
