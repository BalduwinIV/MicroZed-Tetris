#ifndef MENU_H
#define MENU_H

#include "../hardware/io_address.h"

#define NEW_GAME            0
#define BLOCKS_SPEED        1
#define EXIT                2

int menu(unsigned short** screen, phys_addr_t *io);

#endif
