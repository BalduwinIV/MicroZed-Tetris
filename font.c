#include "font.h"
#include <stdio.h>

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

static unsigned int characters[41][14] = {
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

    /*
     * |    **    |
     * |    **    |
     * |  ****    |
     * |  ****    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |  ******  |
     * |  ******  |
     * */
    {
        0x0c00,
        0x0c00,
        0x3c00,
        0x3c00,
        0x0c00,
        0x0c00,
        0x0c00,
        0x0c00,
        0x0c00,
        0x0c00,
        0x0c00,
        0x0c00,
        0x3f00,
        0x3f00
    },

    /*
     * |  ******  |
     * | ******** |
     * |***    ***|
     * |**      **|
     * |        **|
     * |        **|
     * |       ***|
     * |  ******* |
     * | *******  |
     * |***       |
     * |**        |
     * |**        |
     * |**********|
     * |**********|
     * */
    {
        0x3f00,
        0x7f80,
        0xe1c0,
        0xc0c0,
        0x00c0,
        0x00c0,
        0x01c0,
        0x3f80,
        0x7f00,
        0xe000,
        0xc000,
        0xc000,
        0xffc0,
        0xffc0
    },

    /*
     * |  ******  |
     * | ******** |
     * |***    ***|
     * |**      **|
     * |        **|
     * |       ***|
     * |   *******|
     * |   *******|
     * |       ***|
     * |        **|
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
        0x00c0,
        0x01c0,
        0x1f80,
        0x1f80,
        0x01c0,
        0x00c0,
        0xc0c0,
        0xe1c0,
        0x7f80,
        0x3f00
    },

    /*
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |***     **|
     * | *********|
     * |  ********|
     * |        **|
     * |        **|
     * |        **|
     * |        **|
     * |        **|
     * |        **|
     * */
    {
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0x7fc0,
        0x3fc0,
        0x00c0,
        0x00c0,
        0x00c0,
        0x00c0,
        0x00c0,
        0x00c0
    },

    /*
     * |**********|
     * |**********|
     * |**        |
     * |**        |
     * |**        |
     * |********  |
     * |********* |
     * |       ***|
     * |        **|
     * |        **|
     * |**      **|
     * |***    ***|
     * | ******** |
     * |  ******  |
     * */
    {
        0xffc0,
        0xffc0,
        0xc000,
        0xc000,
        0xc000,
        0xff00,
        0xff80,
        0x01c0,
        0x00c0,
        0x00c0,
        0xc0c0,
        0xe1c0,
        0x7f80,
        0x3f00
    },

    /*
     * |  ******  |
     * | ******** |
     * |***    ***|
     * |**      **|
     * |**        |
     * |********  |
     * |********* |
     * |***    ***|
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
        0xc000,
        0xff00,
        0xff80,
        0xe1c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xe1c0,
        0x7f80,
        0x3f00
    },

    /*
     * |**********|
     * |**********|
     * |**      **|
     * |**      **|
     * |        **|
     * |       ***|
     * |      *** |
     * |     ***  |
     * |    ***   |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * */
    {
        0xffc0,
        0xffc0,
        0xc0c0,
        0xc0c0,
        0x00c0,
        0x01c0,
        0x0380,
        0x0700,
        0x0e00,
        0x0c00,
        0x0c00,
        0x0c00,
        0x0c00,
        0x0c00
    },

    /*
     * |  ******  |
     * | ******** |
     * |***    ***|
     * |**      **|
     * |**      **|
     * |***    ***|
     * | ******** |
     * | ******** |
     * |***    ***|
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
        0xe1c0,
        0x7f80,
        0x7f80,
        0xe1c0,
        0xc0c0,
        0xc0c0,
        0xe1c0,
        0x7f80,
        0x3f00
    },

    /*
     * |  ******  |
     * | ******** |
     * |***    ***|
     * |**      **|
     * |**      **|
     * |***    ***|
     * | *********|
     * |  ********|
     * |        **|
     * |        **|
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
        0xe1c0,
        0x7fc0,
        0x3fc0,
        0x00c0,
        0x00c0,
        0xc0c0,
        0xe1c0,
        0x7f80,
        0x3f00
    },

  

    /*
     * |  ******  |
     * | ******** |
     * |***    ***|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**********|
     * |**********|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * */
    {
        0x3f00,
        0x7f80,
        0xe1c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xffc0,
        0xffc0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0
    }, 
    
    /*
     * |********  |
     * |********* |
     * |**     ***|
     * |**      **|
     * |**      **|
     * |**     ***|
     * |********* |
     * |********* |
     * |**     ***|
     * |**      **|
     * |**      **|
     * |**     ***|
     * |********* |
     * |********  |
     * */
    {
        0xff00,
        0xff80,
        0xc1c0,
        0xc0c0,
        0xc0c0,
        0xc1c0,
        0xff80,
        0xff80,
        0xc1c0,
        0xc0c0,
        0xc0c0,
        0xc1c0,
        0xff80,
        0xff00,
    },
    
    /*
     * |  ******  |
     * | ******** |
     * |***    ***|
     * |**      **|
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * |**      **|
     * |***    ***|
     * | ******** |
     * |  ******  |
     * */
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
    
    /*
     * |********  |
     * |********* |
     * |**     ***|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**     ***|
     * |********* |
     * |********  |
     * */
    {
        0xff00,
        0xff80,
        0xc1c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc1c0,
        0xff80,
        0xff00
    }, 
    
    /*
     * |**********|
     * |**********|
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * |**********|
     * |**********|
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * |**********|
     * |**********|
     * */
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
        0xFFC0
    },
        
    /*
     * |**********|
     * |**********|
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * |**********|
     * |**********|
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * */
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
        0xC000,
        0xC000
    },

    /*
     * |  ******  |
     * | ******** |
     * |***    ***|
     * |**      **|
     * |**        |
     * |**        |
     * |**        |
     * |**    ****|
     * |**    ****|
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
        0xc000,
        0xc000,
        0xc000,
        0xc3c0,
        0xc3c0,
        0xc0c0,
        0xc0c0,
        0xe1c0,
        0x7f80,
        0x3f00
    },
    
    /*
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**********|
     * |**********|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * */
    {
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xffc0,
        0xffc0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0
    }, 
     
    /*
     * |  ******  |
     * |  ******  |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |  ******  |
     * |  ******  |
     * */
    {
        0x3F00,
        0x3F00,
        0x0C00,
        0x0C00,
        0x0C00,
        0x0C00,
        0x0C00,
        0x0C00,
        0x0C00,
        0x0C00,
        0x0C00,
        0x0C00,
        0x3F00,
        0x3F00
    }, 
     
    /*
     * |     *****|
     * |     *****|
     * |        **|
     * |        **|
     * |        **|
     * |        **|
     * |        **|
     * |        **|
     * |        **|
     * |**      **|
     * |**      **|
     * |***    ***|
     * | ******** |
     * |  ******  |
     * */
    {
        0x07c0,
        0x07c0,
        0x00c0,
        0x00c0,
        0x00c0,
        0x00c0,
        0x00c0,
        0x00c0,
        0x00c0,
        0xc0c0,
        0xc0c0,
        0xe1c0,
        0x7f80,
        0x3f00
    },

    /*
     * |**      **|
     * |**      **|
     * |**    **  |
     * |**    **  |
     * |******    |
     * |******    |
     * |**    **  |
     * |**    **  |
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * */
    {
        0xc0c0,
        0xc0c0,
        0xc300,
        0xc300,
        0xfc00,
        0xfc00,
        0xc300,
        0xc300,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0
    }, 
     
    /*
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * |**********|
     * |**********|
     * */
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

    /*
     * |**      **|
     * |**      **|
     * |***    ***|
     * |***    ***|
     * |****  ****|
     * |****  ****|
     * |** **** **|
     * |** **** **|
     * |**  **  **|
     * |**  **  **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * */
    {
        0xc0c0,
        0xc0c0,
        0xe1c0,
        0xe1c0,
        0xf3c0,
        0xf3c0,
        0xdec0,
        0xdec0,
        0xccc0,
        0xccc0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0
    }, 
    
    /*
     * |**      **|
     * |**      **|
     * |**      **|
     * |****    **|
     * |****    **|
     * |******  **|
     * |**  **  **|
     * |**  **  **|
     * |**  ******|
     * |**    ****|
     * |**    ****|
     * |**      **|
     * |**      **|
     * |**      **|
     * */
    {
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xf0c0,
        0xf0c0,
        0xfcc0,
        0xccc0,
        0xccc0,
        0xcfc0,
        0xc3c0,
        0xc3c0,
        0xc0c0,
        0xc0c0,
        0xc0c0
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
    
    /*
     * |********  |
     * |********* |
     * |**     ***|
     * |**      **|
     * |**      **|
     * |**     ***|
     * |********* |
     * |********  |
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * |**        |
     * */
    {
        0xff00,
        0xff80,
        0xc1c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc1c0,
        0xff80,
        0xff00,
        0xc000,
        0xc000,
        0xc000,
        0xc000,
        0xc000,
    },

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
     * |**    **  |
     * |***   **  |
     * | *****  **|
     * |  ****  **|
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
        0xc300,
        0xe300,
        0x7cc0,
        0x3cc0
    },
    
    /*
     * |********  |
     * |********* |
     * |**     ***|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**     ***|
     * |********* |
     * |********* |
     * |**     ***|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * */
    {
        0xFF00,
        0xFF80,
        0xC1C0,
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
    
    /*
     * |  ********|
     * | *********|
     * |***       |
     * |**        |
     * |**        |
     * |***       |
     * | *******  |
     * |  ******* |
     * |       ***|
     * |        **|
     * |        **|
     * |       ***|
     * |********* |
     * |********  |
     * */
    {
        0x3FC0,
        0x7FC0,
        0xE000,
        0xC000,
        0xC000,
        0xE000,
        0x7F00,
        0x3F80,
        0x01C0,
        0x00C0,
        0x00C0,
        0x01C0,
        0xFF80,
        0xFF00

    }, 
    
    /*
     * |**********|
     * |**********|
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * */
    {
        0xFFC0,
        0xFFC0,
        0x0C00,
        0x0C00,
        0x0C00,
        0x0C00,
        0x0C00,
        0x0C00,
        0x0C00,
        0x0C00,
        0x0C00,
        0x0C00,
        0x0C00,
        0x0C00    
    }, 
    
    /*
     * |**      **|
     * |**      **|
     * |**      **|
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
        0xc0c0,
        0xc0c0,
        0xc0c0,
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

    /*
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |***    ***|
     * | ***  *** |
     * |  ******  |
     * |   ****   |
     * |    **    |
     * */
    {
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xe1c0,
        0x7380,
        0x3f00,
        0x1e00,
        0x0c00
    },

    /*
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |**  **  **|
     * |**  **  **|
     * |** **** **|
     * |** **** **|
     * | ***  *** |
     * | ***  *** |
     * */
    {
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xccc0,
        0xccc0,
        0xccc0,
        0xdec0,
        0xdec0,
        0x7380,
        0x7380
    },

    /*
     * |**      **|
     * |**      **|
     * |**      **|
     * | **    ** |
     * | **    ** |
     * |  ******  |
     * |   ****   |
     * |   ****   |
     * |  ******  |
     * | **    ** |
     * | **    ** |
     * |**      **|
     * |**      **|
     * |**      **|
     * */
    {
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0x6180,
        0x6180,
        0x3f00,
        0x1e00,
        0x1e00,
        0x3f00,
        0x6180,
        0x6180,
        0xc0c0,
        0xc0c0,
        0xc0c0
    },

    /*
     * |**      **|
     * |**      **|
     * |**      **|
     * |**      **|
     * |***    ***|
     * | ***  *** |
     * |  ******  |
     * |   ****   |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * */
    {
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xc0c0,
        0xe1c0,
        0x7380,
        0x3f00,
        0x1e00,
        0x0c00,
        0x0c00,
        0x0c00,
        0x0c00,
        0x0c00,
        0x0c00
    },

    /*
     * |**********|
     * |**********|
     * |        **|
     * |       ***|
     * |      *** |
     * |     ***  |
     * |    ***   |
     * |   ***    |
     * |  ***     |
     * | ***      |
     * |***       |
     * |**        |
     * |**********|
     * |**********|
     * */
    {
        0xffc0,
        0xffc0,
        0x00c0,
        0x01c0,
        0x0380,
        0x0700,
        0x0e00,
        0x1c00,
        0x3800,
        0x7000,
        0xe000,
        0xc000,
        0xffc0,
        0xffc0
    },

    /*
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |    **    |
     * |          |
     * |    **    |
     * |    **    |
     * */
    {
        0x0c00,
        0x0c00,
        0x0c00,
        0x0c00,
        0x0c00,
        0x0c00,
        0x0c00,
        0x0c00,
        0x0c00,
        0x0c00,
        0x0c00,
        0x0000,
        0x0c00,
        0x0c00
    },

    /*
     * |  ******  |
     * | ******** |
     * |***    ***|
     * |**      **|
     * |        **|
     * |       ***|
     * |      *** |
     * |     ***  |
     * |    ***   |
     * |    **    |
     * |    **    |
     * |          |
     * |    **    |
     * |    **    |
     * */
    {
        0x3f00,
        0x7f80,
        0xe1c0,
        0xc0c0,
        0xc0c0,
        0x01c0,
        0x0380,
        0x0700,
        0x0e00,
        0x0c00,
        0x0c00,
        0x0000,
        0x0c00,
        0x0c00
    },

    /*
     * |    ***   |
     * |   ***    |
     * |  ***     |
     * | ***      |
     * | ***      |
     * | ***      |
     * | ***      |
     * | ***      |
     * | ***      |
     * | ***      |
     * | ***      |
     * |  ***     |
     * |   ***    |
     * |    ***   |
     * */
    {
        0x0e00,
        0x1c00,
        0x3800,
        0x7000,
        0x7000,
        0x7000,
        0x7000,
        0x7000,
        0x7000,
        0x7000,
        0x7000,
        0x3800,
        0x1c00,
        0x0e00
    },

    /*
     * |   ***    |
     * |    ***   |
     * |     ***  |
     * |      *** |
     * |      *** |
     * |      *** |
     * |      *** |
     * |      *** |
     * |      *** |
     * |      *** |
     * |      *** |
     * |     ***  |
     * |    ***   |
     * |   ***    |
     * */
    {
        0x1c00,
        0x0e00,
        0x0700,
        0x0380,
        0x0380,
        0x0380,
        0x0380,
        0x0380,
        0x0380,
        0x0380,
        0x0380,
        0x0700,
        0x0e00,
        0x1c00
    },

    /* unknown character 
     * |* * * * * |
     * | * * * * *|
     * |* * * * * |
     * | * * * * *|
     * |* * * * * |
     * | * * * * *|
     * |* * * * * |
     * | * * * * *|
     * |* * * * * |
     * | * * * * *|
     * |* * * * * |
     * | * * * * *|
     * |* * * * * |
     * | * * * * *|
     * */
    {
        0xaa80,
        0x5540,
        0xaa80,
        0x5540,
        0xaa80,
        0x5540,
        0xaa80,
        0x5540,
        0xaa80,
        0x5540,
        0xaa80,
        0x5540,
        0xaa80,
        0x5540
    }
};

static void draw_whitespace(unsigned int **screen, int x, int y, unsigned int color) {
    for (int yi = 0; yi < 14; yi++) {
        for (int xi = 0; xi < 4; xi++) {
            screen[y+yi][x+xi] = color;
        }
    }
}

/*
 * @param screen
 * @param x
 * @param y
 * @param ch        ASCII char code.
 * @param fg_color  character foreground color
 * @param bg_color  character background color;
 * */
static void draw_char(unsigned int **screen, int x, int y, char ch, unsigned int fg_color, unsigned int bg_color) {
    if (ch == ' ') {
        draw_whitespace(screen, x, y, bg_color);
        return;
    }

    unsigned char wanted_ch;
    if (ch >= '0' && ch <= '9') {
        wanted_ch = ch - '0';
    } else if (ch >= 'A' && ch <= 'Z') {
        wanted_ch = ch - 'A' + 10;
    } else if (ch >= 'a' && ch <= 'z') {
        wanted_ch = ch - 'a' + 10;
    } else if (ch == '!') {
        wanted_ch = 36;
    } else if (ch == '?') {
        wanted_ch = 37;
    } else if (ch == '(') {
        wanted_ch = 38;
    } else if (ch == ')') {
        wanted_ch = 39;
    } else {
        wanted_ch = 40;
    }
    printf("wanted_ch = %d, ch = %d\n", wanted_ch, ch);

    for (int font_y = 0; font_y < 14; font_y++) {
        screen[y+font_y][x] = (characters[wanted_ch][font_y] & 0x8000) ? fg_color : bg_color;    /* 1st bit */
        screen[y+font_y][x+1] = (characters[wanted_ch][font_y] & 0x4000) ? fg_color : bg_color;  /* 2nd bit */
        screen[y+font_y][x+2] = (characters[wanted_ch][font_y] & 0x2000) ? fg_color : bg_color;  /* 3rd bit */
        screen[y+font_y][x+3] = (characters[wanted_ch][font_y] & 0x1000) ? fg_color : bg_color;  /* 4th bit */
        screen[y+font_y][x+4] = (characters[wanted_ch][font_y] & 0x0800) ? fg_color : bg_color;  /* 5th bit */
        screen[y+font_y][x+5] = (characters[wanted_ch][font_y] & 0x0400) ? fg_color : bg_color;  /* 6th bit */
        screen[y+font_y][x+6] = (characters[wanted_ch][font_y] & 0x0200) ? fg_color : bg_color;  /* 7th bit */
        screen[y+font_y][x+7] = (characters[wanted_ch][font_y] & 0x0100) ? fg_color : bg_color;  /* 8th bit */
        screen[y+font_y][x+8] = (characters[wanted_ch][font_y] & 0x0080) ? fg_color : bg_color;  /* 9th bit */
        screen[y+font_y][x+9] = (characters[wanted_ch][font_y] & 0x0040) ? fg_color : bg_color;  /* 10th bit */
    }
}

void draw_string(unsigned int **screen, int x, int y, char *str, unsigned int fg_color, unsigned int bg_color) {
    int ch_x_pos = x;
    for (int ch_i = 0; str[ch_i] != '\0'; ch_i++) {
        draw_char(screen, ch_x_pos, y, str[ch_i], fg_color, bg_color);
        draw_whitespace(screen, ch_x_pos+10, y, bg_color);
        ch_x_pos += 14;
    }
}

