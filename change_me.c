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

    unsigned char *mem_base;
    unsigned char *parlcd_mem_base;
    int i,j,k;
    unsigned int c;

    printf("Starting...\n");

    mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);

      /* If mapping fails exit with error code */
    if (mem_base == NULL)
    exit(1);

    parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);

    if (parlcd_mem_base == NULL) {
        exit(1);
    }

    parlcd_hx8357_init(parlcd_mem_base);

    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (i = 0; i < 320; i++) {
        for (j = 0; j < 480; j++) {
            c = 0;
            parlcd_write_data(parlcd_mem_base, c);
        }
    }

    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (i = 0; i < 320; i++) {
        for (j = 0; j < 480; j++) {
            c = ((i & 0x1f) << 11) | (j & 0x1f);
            parlcd_write_data(parlcd_mem_base, c);
        }
    }

    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 20 * 1000 * 1000};
    for (k = 0; k < 60; k++) {
        parlcd_write_cmd(parlcd_mem_base, 0x2c);
        for (i = 0; i < 320; i++) {
            for (j = 0; j < 480; j++) {
                c = (((i+k) & 0x1f) << 11) | ((j+k) & 0x1f);
                parlcd_write_data(parlcd_mem_base, c);
            }
        }

        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }

    printf("Stopping...\n");

    /* Release the lock */
    serialize_unlock();

    return 0;
}
