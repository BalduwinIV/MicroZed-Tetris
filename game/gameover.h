/* Gameover methods. */

#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "../hardware/io_address.h"

unsigned char check_gameover(unsigned char **gamefield);
unsigned char gameover(unsigned short** screen, unsigned char **gamefield, phys_addr_t *io, unsigned int *statistics, unsigned int *score, unsigned int *lines_number);

#endif
