#include <stdio.h>

#include "tools/colors.h"

#define SCREEN_WIDTH    480
#define SCREEN_HEIGHT   320

void display(unsigned short **screen) {
    FILE *image = fopen("screen.ppm", "wb");
    fprintf(image, "P6\n%d %d\n%d\n", SCREEN_WIDTH, SCREEN_HEIGHT, 255);

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            fputc((screen[y][x] & 0xf800) >> 7, image);
            fputc((screen[y][x] & 0x07e0) >> 5, image);
            fputc(screen[y][x] & 0x001f, image);
        }
    }

    fclose(image);
}
