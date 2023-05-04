#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <time.h>

#include "../hardware/io_address.h"
#include "block.h"

#define GAMEFIELD_SIZE  18

unsigned char update_gamefield(unsigned char **gamefield, block_t *current_block, struct timespec *last_call_time, unsigned char blocks_speed);
unsigned char clear_rows(unsigned char **gamefield, unsigned short **screen, phys_addr_t *io, unsigned char blocks_speed);

#endif
