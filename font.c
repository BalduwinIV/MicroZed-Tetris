#include "font.h"

/* Characters array. */
/* [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
 *   A, B, C, D, E, F, G, H, I, J,
 *   K, L, M, N, O, P, Q, R, S, T,
 *   U, V, W, X, Y, Z] */

/*
        0x
        0x
        0x
        0x
        0x
        0x
        0x
        0x
        0x
        0x
        0x
        0x
        0x
        0x

*/

static unsigned int characters[36][14] = {
    /*0*/
    {
        0x3f00,
        0x7f80,
        0xe1c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xe1c0,
        0x7f80,
        0x3f00
    },

    /*1*/
    {
        0x00,
        0xFC00,
        0xFC00,
        0xC00,
        0xC00,
        0xC00,
        0xC00,
        0xC00,
        0xC00,
        0xC00,
        0xC00,
        0xFFC0,
        0xFFC0,
        0x00
    },

    /*2*/
    {
        0x00,
        0x3F00,
        0x7F80,
        0xE1C0,
        0xC0C0,
        0xC0,
        0x180,
        0x3F00,
        0x7E00,
        0xE000,
        0xC000,
        0xFFC0,
        0xFFC0,
        0x00
    },

    /*3*/
    {
        0x0,
        0x3F00,
        0x7F80,
        0xE1C0,
        0xC0C0,
        0x1C0,
        0x1F80,
        0x1F80,
        0x1C0,
        0xC0C0,
        0xE1C0,
        0x7F80,
        0x3F00,
        0x0
    },

    /*4*/
    {
        0x0,
        0x3030,
        0x3030,
        0x3030,
        0x3030,
        0x3830,
        0x1F00,
        0xFF0,
        0x30,
        0x30,
        0x30,
        0x30,
        0x30,
        0x0
    },

    /*5*/
    {
        0x0,
        0xFFC00,
        0xFFC00,
        0xC000,
        0xC000,
        0xFF00,
        0x7F80,
        0x1C0,
        0xC0,
        0xC0C0,
        0xE1C0,
        0x7F80,
        0x3F00,
        0x0
    },

     /*6*/
    {
        0x0,
        0x3F00,
        0x7F80,
        0xE1C0,
        0xC0C0,
        0xC000,
        0xFF00,
        0xFF80,
        0xC1C0,
        0xC0C0,
        0xE1C0,
        0x7F80,
        0x3F00,
        0x0
    },

    /*7*/
    {
        0x0,
        0xFF80,
        0xFFC0,
        0xC0,
        0xC0,
        0x1C0,
        0x380,
        0x700,
        0xE00,
        0x1C00,
        0x1800,
        0x1800,
        0x1800,
        0x0
    },

    /*8*/
    {
        0x0,
        0x3F00,
        0xE1C0,
        0xC0C0,
        0xC0C0,
        0xE1C0,
        0x3F00,
        0x3F00,
        0xE1C0,
        0xC0C0,
        0xC0C0,
        0xE1C0,
        0x3F00,
        0x0
    },

    /*9*/
    {
        // 0x3F00,
        // 0x7F80,
        // 0xE0C0,
        // 0xC0C0,
        // 0xC0C0,
        // 0xE0C0,
        // 0x7FC0,
        // 0x3FC0,
        // 0xC0,
        // 0xC0,
        // 0xC0C0,
        // 0xE0C0,
        // 0x7F80,
        // 0x3F00
        0x0,
        0x3F00,
        0x7F80,
        0xC0C0,
        0xC0C0,
        0xC0C0,
        0x7FC4,
        0x3FC0,
        0xC0,
        0x80C0,
        0xC0C0,
        0x7F80,
        0x3F00,
        0x0
    },

  

    /*a*/{0, 0}, 
    
    /*B*/
    {
       0xFF00,
       0xFE00,
       0xC1C0,
       0xC0C0,
       0xC0C0,
       0xC1C0,
       0xFE00,
       0xFE00,
       0xC1C0,
       0xC0C0,
       0xC0C0,
       0xC1C0,
       0xFE00,
       0xFF00
    },
    
    /*C*/
    {
        0x3F00,
        0x7F80,
        0xE1C0,
        0xC0C0,
        0xC000,
        0xC000,
        0xC000,
        0xC000,
        0xC000,
        0xC000,
        0xC0C0,
        0xE1C0,
        0x7F80,
        0x3F00
    }, 
    
    /*d*/{0}, 
    
    /*E*/
    {
        0xFFC0,
        0xFFC0,
        0xC000,
        0xC000,
        0xC000,
        0xC000,
        0xFFC0,
        0xFFC0,
        0xC000,
        0xC000,
        0xC000,
        0xC000,
        0xFFC0,
        0xFFC0,
        
    },
        
     /*f*/{0}, /*g*/{0}, /*h*/{0}, 
     
     /*I*/
     {
        0x3F00,
        0x3F00,
        0xC00,
        0xC00,
        0xC00,
        0xC00,
        0xC00,
        0xC00,
        0xC00,
        0xC00,
        0xC00,
        0xC00,
        0x3F00,
        0x3F00

     }, 
     
     /*j*/{0}, /*k*/{0}, 
     
     /*L*/
     {
        0xC000,
        0xC000,
        0xC000,
        0xC000,
        0xC000,
        0xC000,
        0xC000,
        0xC000,
        0xC000,
        0xC000,
        0xC000,
        0xC000,
        0xFFC0,
        0xFFC0

     },

    /*m*/{0}, 
    
    /*N*/
    {
        0xC0C0,
        0xE0C0,
        0xF0C0,
        0xF0C0,
        0xD8C8,
        0xDCC0,
        0xCCC0,
        0xCCC0,
        0xCEC0,
        0xC6C0,
        0xC3C0,
        0xC3C0,
        0xC1C0,
        0xC0C0

    },

    /*O*/
    /*
     * |  ******  |
     * | ******** |
     * |***    ***|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |***    ***|
     * | ******** |
     * |  ******  |
     * */
    {
        0x3f00,
        0x7f80,
        0xe1c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xe1c0,
        0x7f80,
        0x3f00
    },
    
    /*p*/{0}, /*q*/{0},
    
    /*R*/
    {
        0xFF00,
        0xFF80,
        0xC0C0,
        0xC0C0,
        0xC0C0,
        0xC1C0,
        0xFF80,
        0xFF80,
        0xC1C0,
        0xC0C0,
        0xC0C0,
        0xC0C0,
        0xC0C0,
        0xC0C0
    }, 
    
    /*S*/
    {
        0x3FC0,
        0x7FC0,
        0xE000,
        0xC000,
        0xC000,
        0xE000,
        0x7F00,
        0x3F80,
        0x1C0,
        0xC0,
        0xC0,
        0x1C0,
        0xFF80,
        0xFF00

    }, 
    
    /*T*/
    {
        0xFFC0,
        0xFFC0,
        0xC00,
        0xC00,
        0xC00,
        0xC00,
        0xC00,
        0xC00,
        0xC00,
        0xC00,
        0xC00,
        0xC00,
        0xC00,
        0xC00    
    }, 
    
    /*u*/{0}, /*v*/{0}, /*w*/{0}, /*x*/{0}, /*y*/{0}, /*z*/{0}
   
    //...
};

/*
 * @param screen
 * @param x
 * @param y
 * @param ch        ASCII char code.
 * @param fg_color  character foreground color
 * @param bg_color  character background color;
 * */
static void draw_char(unsigned int **screen, int x, int y, char ch, unsigned short fg_color, unsigned short bg_color) {
    /* if ch in range <48, 57> then it is a number from 0 to 9 */
    /* else then it is a letter. */
    unsigned char wanted_ch = (ch<=57) ? ch-48 : ch-65;

    for (int font_y = 0; font_y < 14; font_y++) {
        screen[y][x] = (characters[wanted_ch][y+font_y] & 0x8000) ? fg_color : bg_color;    /* 1st bit */
        screen[y][x+1] = (characters[wanted_ch][y+font_y] & 0x4000) ? fg_color : bg_color;  /* 2nd bit */
        screen[y][x+2] = (characters[wanted_ch][y+font_y] & 0x2000) ? fg_color : bg_color;  /* 3rd bit */
        screen[y][x+3] = (characters[wanted_ch][y+font_y] & 0x1000) ? fg_color : bg_color;  /* 4th bit */
        screen[y][x+4] = (characters[wanted_ch][y+font_y] & 0x0800) ? fg_color : bg_color;  /* 5th bit */
        screen[y][x+5] = (characters[wanted_ch][y+font_y] & 0x0400) ? fg_color : bg_color;  /* 6th bit */
        screen[y][x+6] = (characters[wanted_ch][y+font_y] & 0x0200) ? fg_color : bg_color;  /* 7th bit */
        screen[y][x+7] = (characters[wanted_ch][y+font_y] & 0x0100) ? fg_color : bg_color;  /* 8th bit */
        screen[y][x+8] = (characters[wanted_ch][y+font_y] & 0x0080) ? fg_color : bg_color;  /* 9th bit */
        screen[y][x+9] = (characters[wanted_ch][y+font_y] & 0x0040) ? fg_color : bg_color;  /* 10th bit */
    }
}

static void draw_whitespace(unsigned int **screen, int x, int y, unsigned short color) {
    for (int yi = 0; yi < 14; yi++) {
        for (int xi = 0; xi < 4; xi++) {
            screen[y+yi][x+xi] = color;
        }
    }
}

void draw_string(unsigned int **screen, int x, int y, char *str, unsigned short fg_color, unsigned short bg_color) {
    int ch_x_pos = x;
    for (int ch_i = 0; str[ch_i] != '\0'; ch_i++) {
        draw_char(screen, ch_x_pos, y, str[ch_i], fg_color, bg_color);
        draw_whitespace(screen, ch_x_pos+10, y, bg_color);
        ch_x_pos += 14;
    }
}

