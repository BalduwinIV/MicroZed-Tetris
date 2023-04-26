#include <stdio.h>
#include <stdlib.h>

#include "image_graphics.h"
#include "colors.h"
#include "font.h"

void draw_rect(unsigned int **screen, int x, int y, int width, int height, int color) {
    for (int yi = 0; yi < height; yi++) {
        for (int xi = 0; xi < width; xi++) {
            screen[y+yi][x+xi] = color;
        }
    }
}

int main() {
    unsigned int **screen = (unsigned int **)malloc(320 * sizeof(unsigned int *));
    for (int y = 0; y < 320; y++) {
        screen[y] = (unsigned int *)malloc(480 * sizeof(unsigned int));
        for (int x = 0; x < 480; x++) {
            screen[y][x] = 0x000000;
        }
    }

    int grey = GREY_RGB888;
    int blue = BORDER_RGB888;

    draw_rect(screen, 3, 0, 120, 3, grey);
    draw_rect(screen, 0, 3, 3, 314, grey);
    draw_rect(screen, 3, 317, 120, 3, grey);
    draw_rect(screen, 123, 3, 3, 314, grey);
    draw_rect(screen, 3, 3, 3, 3, grey);
    draw_rect(screen, 3, 314, 3, 3, grey);
    draw_rect(screen, 120, 3, 3, 3, grey);
    draw_rect(screen, 120, 314, 3, 3, grey);
    draw_rect(screen, 6, 6, 114, 3, blue);


    display(screen);
}
