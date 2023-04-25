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

static unsigned int characters[36][14] {

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
    }

    /*6*/
    {
        0x0,
        0x3F00,
        0x7F80,
        0xE1C0,
        0xC0C0,
        0xC000,
        0xFF80,
        0x
        0x
        0x
        0x
        0x
        0x
        0x
    }

    /*7*/
    {
        0x0,
        0xFF80,
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
    }

    /*8*/
    {
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
    },

    /*9*/
    {
        0x3F00,
        0x7F80,
        0xE0C0,
        0xC0C0,
        0xC0C0,
        0xE0C0,
        0x7FC0,
        0x3FC0,
        0xC0,
        0xC0,
        0xC0C0,
        0xE0C0,
        0x7F80,
        0x3F00
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
    unsigned char wanted_ch = ch-65;
    int font_x;
    for (int font_y = 0; font_y < 14; font_y++) {
        font_x = x;
        if (characters[wanted_ch][y+font_y] & 0x8000) screen[y][font_x++] = fg_color else screen[y][font_x++] = bg_color;
        // if (characters[wanted_ch][y+font_y] & 0x4000) ...
        // if (characters[wanted_ch][y+font_y] & 0x2000) ...
        // if (characters[wanted_ch][y+font_y] & 0x1000) ...
        // if (characters[wanted_ch][y+font_y] & 0x0800) ...
        // if (characters[wanted_ch][y+font_y] & 0x0400) ...
        // if (characters[wanted_ch][y+font_y] & 0x0200) ...
        // if (characters[wanted_ch][y+font_y] & 0x0100) ...
        // if (characters[wanted_ch][y+font_y] & 0x0080) ...
        // if (characters[wanted_ch][y+font_y] & 0x0040) ...
    }
}

void draw_string(unsigned int **screen, int x, int y, char *str, unsigned short fg_color, unsigned short bg_color) {
    for (int ch_i = 0; str[ch_i] != '\0'; ch_i++) {
        draw_char(screen, x, y, str[ch_i], fg_color, bg_color);
        x += 14;
    }
}

