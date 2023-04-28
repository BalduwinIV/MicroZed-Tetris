#ifndef GRAPHICS_H
#define GRAPHICS_H

void draw_background(unsigned short **screen);

void draw_rect(unsigned short **screen, int x, int y, int dest_x, int dest_y, int color);

void draw_checkbox(unsigned short **screen, int x, int y, unsigned char state);

#define BLOCK_SIZE  20
void draw_block(unsigned short **screen, int x, int y, unsigned char block_type);

#define GAMEFIELD_X     140
#define GAMEFIELD_Y     11
void draw_gamefield(unsigned short **screen, unsigned char** field);

#endif
