#include <stdio.h>
#include <stdlib.h>

#include "../game/graphics.h"
#include "../game/image_graphics.h"

#define SCREEN_WIDTH    480
#define SCREEN_HEIGHT   320

int main() {
    unsigned short **screen = (unsigned short **)malloc(SCREEN_HEIGHT * sizeof(unsigned short *));
    if (!screen) {
        fprintf(stderr, "Malloc failed for screen.\n");
        exit(1);
    }
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        screen[y] = (unsigned short *)malloc(SCREEN_HEIGHT * sizeof(unsigned short));
        if (!screen[y]) {
            fprintf(stderr, "Malloc failed for screen.\n");
            exit(1);
        }
    }

    draw_background(screen);
    display(screen);

    return 0;
}
