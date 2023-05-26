/* Game main file. */

#ifndef GAME_H
#define GAME_H

#include "../hardware/io_address.h"

void start_game(unsigned short **screen, phys_addr_t *io, unsigned char *blocks_speed, unsigned char *show_next_element, unsigned char *enable_audio);

#endif
