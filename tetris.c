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
    printf("Allocating memory for the screen.\n");
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
    unsigned char blocks_speed = 4;
    unsigned char show_next_element = 1;
    unsigned char enable_audio = 0;
    unsigned char program_is_running = 1;
    while (program_is_running) {
        printf("Starting menu...\n");
        menu_option = menu(screen, io, &blocks_speed, &show_next_element, &enable_audio);
        printf("Menu option: %d\n", menu_option);
        printf("Blocks speed: %d\n", blocks_speed);
        printf("Show next element? : %d\n", show_next_element);
        printf("Enable audio? : %d\n", enable_audio);
        if (menu_option == EXIT) {
            program_is_running = 0;
            break;
        } else if (menu_option == NEW_GAME) {
            printf("Starting game...\n");
            start_game(screen, io, &blocks_speed, &show_next_element, &enable_audio);
            printf("Game ended...\n");
        }
    }

    for (y = 0; y < SCREEN_HEIGHT; y++) {
        free(screen[y]);
    }
    free(screen);

    set_led_line_value(io, 0x00000000);
    set_led_rgb1_color(io, 0x00000000);
    set_led_rgb2_color(io, 0x00000000);
    printf("Stopping...\n");

    /* Release the lock */
    serialize_unlock();

    return 0;
}
