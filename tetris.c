#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "hardware/io_address.h"
#include "hardware/serialize_lock.h"

#include "game/tools/colors.h"
#include "game/tools/font.h"

#include "game/game.h"
#include "game/menu.h"
#include "game/graphics.h"

#define SCREEN_WIDTH    480
#define SCREEN_HEIGHT   320

int main(int argc, char *argv[])
{
    /* Serialize execution of applications */

    /* Try to acquire lock the first */
    if (serialize_lock(1) <= 0) {
        printf("System is occupied\n");

        if (1) {
            printf("Waitting\n");
            /* Wait till application holding lock releases it or exits */
            serialize_lock(0);
        }
    }

    printf("Starting...\n");

    int y;

    unsigned short **screen = (unsigned short **)malloc(SCREEN_HEIGHT * sizeof(unsigned short *));
    if (!screen) {
        fprintf(stderr, "Malloc failed for screen.\n");
        exit(1);
    }
    for (y = 0; y < SCREEN_HEIGHT; y++) {
        screen[y] = (unsigned short *)malloc(SCREEN_WIDTH * sizeof(unsigned short));
        if (!screen[y]) {
            fprintf(stderr, "Malloc failed for screen.\n");
            exit(1);
        }
    }

    printf("Mapping addresses.\n");
    phys_addr_t *io = init_io();

    unsigned char menu_option;
    unsigned char program_is_running = 1;
    while (program_is_running) {
        printf("Starting menu...\n");
        menu_option = menu(screen, io);
        if (menu_option == EXIT) {
            program_is_running = 0;
            break;
        } else if (menu_option == NEW_GAME) {
            printf("Starting game...\n");
            start_game(screen, io, 4, 1);
            printf("Game ended...\n");
        }
    }

    printf("Stopping...\n");

    /* Release the lock */
    serialize_unlock();

    return 0;
}