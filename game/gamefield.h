#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "../hardware/io_address.h"

void update_gamefield(unsigned char **gamefield, struct timespec *last_call_time, unsigned char blocks_speed);
int clear_rows(unsigned char **gamefield, unsigned short **screen, phys_addr_t *io, unsigned char blocks_speed);

#endif
