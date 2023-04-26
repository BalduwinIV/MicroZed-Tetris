#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "image_graphics.h"
#include "colors.h"
#include "font.h"

int main() {
    unsigned int **screen = (unsigned int **)malloc(320 * sizeof(unsigned int *));
    for (int y = 0; y < 320; y++) {
        screen[y] = (unsigned int *)malloc(480 * sizeof(unsigned int));
        for (int x = 0; x < 480; x++) {
            screen[y][x] = 0x000000;
        }
    }

/*   0, 1, 2, 3, 4, 5, 6, 7, 8, 9 */
    char str1[] = "0123456789";
    draw_string(screen, 10, 10, str1, WHITE_RGB565, BLACK_RGB565);

/*   A, B, C, D, E, F, G, H, I, J */
    char str2[] = "ABCDEFGHIJ";
    draw_string(screen, 10, 30, str2, WHITE_RGB565, BLACK_RGB565);

/*   K, L, M, N, O, P, Q, R, S, T */
    char str3[] = "KLMNOPQRST";
    draw_string(screen, 10, 50, str3, WHITE_RGB565, BLACK_RGB565);

/*   U, V, W, X, Y, Z */
    char str4[] = "UVWXYZ";
    draw_string(screen, 10, 70, str4, WHITE_RGB565, BLACK_RGB565);

    char str5[] = "SCORE 999";
    draw_string(screen, 10, 120, str5, WHITE_RGB565, BLACK_RGB565);

    display(screen);
}
