#ifndef MENU_DISPLAY_H
#define MENU_DISPLAY_H

#include "../hardware/io_address.h"

int menu(unsigned int** screen, int x, int y, phys_addr_t *io);

#endif
