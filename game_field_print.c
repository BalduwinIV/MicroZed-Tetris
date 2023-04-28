#include <game_field_print.h>
#include <graphics.h>


void print_game_field(unsigned int **screen, char** field){
    int starting_x = 140;
    int starting_y = 9;
    for (int y = 0; y < 15; y++){
        for(int x = 0; x < 5; x++){
            unsigned char block1 = (field[y][x]>>4);
            draw_block(screen, starting_x + (x*40), starting_y + (y*20), block1);

            unsigned char block2 = (field[y][x] & 0xF);
            draw_block(screen, starting_x + (x*40 + 20), starting_y + (y*20), block1);
        }
    }
    //draw_block(screen, );
}