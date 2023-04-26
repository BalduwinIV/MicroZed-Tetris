/*******************************************************************
  Project main function template for MicroZed based MZ_APO board
  designed by Petr Porazil at PiKRON

  change_me.c      - main file

  include your name there and license for distribution.

  Remove next text: This line should not appear in submitted
  work and project name should be change to match real application.
  If this text is there I want 10 points subtracted from final
  evaluation.

 *******************************************************************/

#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "serialize_lock.h"

#include "colors.h"
#include "font.h"

void draw_rect(unsigned int **screen, int x, int y, int width, int height, int color) {
    for (int yi = 0; yi < height; yi++) {
        for (int xi = 0; xi < width; xi++) {
            screen[y+yi][x+xi] = color;
        }
    }
}
 
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

    unsigned int **screen = (unsigned int **)malloc(320 * sizeof(unsigned int *));

    unsigned char *mem_base;
    unsigned char *parlcd_mem_base;
    unsigned char *knobs_mem_base;
    int y,x;

    printf("Starting...\n");

    mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);

      /* If mapping fails exit with error code */
    if (mem_base == NULL)
    exit(1);

    parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);

    if (parlcd_mem_base == NULL) {
        exit(1);
    }

    knobs_mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, SPILED_REG_KNOBS_8BIT_o);

    if (knobs_mem_base == NULL) {
        exit(1);
    }

    parlcd_hx8357_init(parlcd_mem_base);

    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 20 * 1000 * 1000};

    int is_running = 1;
    int x_pos = 20, y_pos = 20;
    while (is_running) {
        for (int y = 0; y < 320; y++) {
            screen[y] = (unsigned int *)malloc(480 * sizeof(unsigned int));
            for (int x = 0; x < 480; x++) {
                screen[y][x] = 0x0000;
            }
        }

        int white = WHITE_RGB565;
        int black = BLACK_RGB565;

        char str[] = "0";
        draw_string(screen, x_pos, y_pos, str, white, black);
        printf("%x\n", (volatile uint32_t*)(knobs_mem_base));

        parlcd_write_cmd(parlcd_mem_base, 0x2c);
        for (y = 0; y < 320; y++) {
            for (x = 0; x < 480; x++) {
                parlcd_write_data(parlcd_mem_base, screen[y][x]);
            }
        }
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }

    printf("Stopping...\n");

    /* Release the lock */
    serialize_unlock();

    return 0;
}
