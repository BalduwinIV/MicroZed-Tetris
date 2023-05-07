#include <stdio.h>

#include "tools/colors.h"

#define SCREEN_WIDTH    480
#define SCREEN_HEIGHT   320

void display(unsigned short **screen) {
    FILE *image = fopen("screen.ppm", "wb");
    fprintf(image, "P6\n%d %d\n%d\n", SCREEN_WIDTH, SCREEN_HEIGHT, 255);
    unsigned int sym;

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            if (screen[y][x] == BLACK_RGB565){
                sym = BLACK_RGB888;
            }
            else if (screen[y][x] == WHITE_RGB565){
                sym = WHITE_RGB888;
            }
            else if (screen[y][x] == GREY_RGB565){
                sym = GREY_RGB888;
            }
            else if (screen[y][x] == BORDER_RGB565){
                sym = BORDER_RGB888;
            }
            else if (screen[y][x] == GREEN_RGB565){
                sym = GREEN_RGB888;
            }
            else if (screen[y][x] == RED_RGB565){
                sym = RED_RGB888;
            }
            else if (screen[y][x] == PURPLE_RGB565){
                sym = PURPLE_RGB888;
            }
            else if (screen[y][x] == YELLOW_RGB565){
                sym = YELLOW_RGB888;
            }
            else if (screen[y][x] == DARKBLUE_RGB565){
                sym = DARKBLUE_RGB888;
            }
            else if (screen[y][x] == ORANGE_RGB565){
                sym = ORANGE_RGB888;
            }
            else if (screen[y][x] == BLUE_RGB565){
                sym = BLUE_RGB888;
            }

            fputc((sym & 0xff0000) >> 16, image);
            fputc((sym & 0xff00) >> 8, image);
            fputc(sym & 0xff, image);



            // fputc((screen[y][x] & 0xf800) >> 7, image);
            // fputc((screen[y][x] & 0x07e0) >> 5, image);
            // fputc(screen[y][x] & 0x001f, image);
        }
    }

    fclose(image);
}
