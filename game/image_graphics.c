#include <stdio.h>

#define SCREEN_WIDTH    480
#define SCREEN_HEIGHT   320

void display(unsigned int **screen) {
    FILE *image = fopen("screen.ppm", "wb");
    fprintf(image, "P6\n%d %d\n%d\n", SCREEN_WIDTH, SCREEN_HEIGHT, 255);

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            fputc((screen[y][x] & 0xff0000) >> 16, image);
            fputc((screen[y][x] & 0x00ff00) >> 8, image);
            fputc(screen[y][x] & 0x0000ff, image);
        }
    }

    fclose(image);
}
