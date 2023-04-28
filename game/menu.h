#ifndef MENU_H
#define MENU_H

#include "../hardware/io_address.h"

#define NEW_GAME            0
#define BLOCKS_SPEED        1
#define SHOW_NEXT_ELEMENT   2
#define EXIT                3

unsigned char menu(unsigned short** screen, phys_addr_t *io, unsigned char *blocks_speed, unsigned char *show_next_element);

#endif
