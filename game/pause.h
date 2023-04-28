#ifndef PAUSE_H
#define PAUSE_H

#include "../hardware/io_address.h"

#define CONTINUE        0
#define GO_TO_MENU      1

unsigned char pause(unsigned short **screen, phys_addr_t *io);

#endif
