#include <stdio.h>
#include <stdlib.h>

#include "../game/image_graphics.h"
#include "../game/tools/colors.h"
#include "../game/tools/font.h"

int main() {
    unsigned short **screen = (unsigned short **)malloc(320 * sizeof(unsigned short *));
    for (int y = 0; y < 320; y++) {
        screen[y] = (unsigned short *)malloc(480 * sizeof(unsigned short));
        for (int x = 0; x < 480; x++) {
            screen[y][x] = 0x000000;
        }
    }

/*   A, B, C, D, E, F, G, H, I, J */
    char str1[] = "ABCDEFGHIJ";
    draw_string(screen, 10, 10, str1, WHITE_RGB565, BLACK_RGB565);

/*   K, L, M, N, O, P, Q, R, S, T */
    char str2[] = "KLMNOPQRST";
    draw_string(screen, 10, 30, str2, WHITE_RGB565, BLACK_RGB565);

/*   U, V, W, X, Y, Z */
    char str3[] = "UVWXYZ";
    draw_string(screen, 10, 50, str3, WHITE_RGB565, BLACK_RGB565);

/*   0, 1, 2, 3, 4, 5, 6, 7, 8, 9 */
    char str4[] = "0123456789";
    draw_string(screen, 10, 70, str4, WHITE_RGB565, BLACK_RGB565);

/*   !?()<unknown character>*/
    char str5[] = "!?()<>@";
    draw_string(screen, 10, 90, str5, WHITE_RGB565, BLACK_RGB565);

    char str6[] = "WHITE SPACE";
    draw_string(screen, 10, 110, str6, WHITE_RGB565, BLACK_RGB565);

    display(screen);
}
