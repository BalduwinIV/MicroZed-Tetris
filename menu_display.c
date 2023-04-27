#include "stdint.h"

#include <menu_display.h>
#include <mzapo_phys.h>
#include <mzapo_regs.h>
#include <font.h>
#include <colors.h>




void draw_rect(unsigned int **screen, int x, int y, int dest_x, int dest_y, int color) {
    for (int y_temp = y; y_temp <= dest_y; y_temp++) {
        for (int x_temp = x; x_temp <= dest_x; x_temp++) {
            screen[y_temp][x_temp] = color;
        }
    }
}

int menu(unsigned int** screen, int x, int y, int frame){
    
    int frame = 3;
    int line_length = 2*frame + 10*11 + 4*9 + 12;
    int line_width = 4*frame + 14;
    unsigned char* mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    char cur_knob_value = (*(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o) & 0x0000ff00) >> 8;

    draw_string(screen, x + frame*2, y + frame*2, "START GAME", WHITE_RGB565, BLACK_RGB565);
    draw_string(screen, x + line_width + frame*2, y + frame*2, "BLOCKS SPEED", WHITE_RGB565, BLACK_RGB565);
    draw_string(screen, x + line_width*2 + frame*2, y + frame*2, "EXIT", WHITE_RGB565, BLACK_RGB565);
    //trial with a frame around "new game" on default and around chosen variant later on
    draw_rect (screen, x, y, x + line_width - 1, y + line_length, WHITE_RGB565);

    int vote = 0;
    while (1){

        if ((*(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o) & 0x2000000) >> 25){
            break;
        }

        else if (((*(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o) & 0x0000ff00) >> 8) > cur_knob_value){
            if(vote < 2){
                vote++;
            }
        }

        else if (((*(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o) & 0x0000ff00) >> 8) < cur_knob_value){
            if (vote > 0){
                vote--;
            }
        }

        else {
            continue;
        }

        draw_rect (screen, x + vote*line_width, y, x + vote*line_width - 1, y + line_length, WHITE_RGB565);
        draw_rect (screen, x + ((vote+1)%3)*line_width, y, x + ((vote+1)%3)*line_width - 1, y + line_length, BLACK_RGB565);
        draw_rect (screen, x + ((vote-1)%3)*line_width, y, x + ((vote+1)%3)*line_width - 1, y + line_length, BLACK_RGB565);
        cur_knob_value = (*(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o) & 0x0000ff00) >> 8;

    }
    
    return vote;
}

