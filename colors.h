#ifndef COLORS_H
#define COLORS_H

#define BLACK_RGB888            0x000000
#define BLACK_RGB565            0x0000
#define BLACK_HSV_HUE           0
#define BLACK_HSV_SATURATION    0
#define BLACK_HSV_VALUE         0

#define WHITE_RGB888            0xffffff
#define WHITE_RGB565            0xffff
#define WHITE_HSV_HUE           0
#define WHITE_HSV_SATURATION    0
#define WHITE_HSV_VALUE         100

/* Background grey border color */
#define GREY_RGB888             0x6c6c6c
#define GREY_RGB565             0x6b6d
#define GREY_HSV_HUE            0
#define GREY_HSV_SATURATION     0
#define GREY_HSV_VALUE          42

/* Background blue border color */
#define BORDER_RGB888           0x6dbbb9
#define BORDER_RGB565           0x6dd7
#define BORDER_HSV_HUE          178
#define BORDER_HSV_SATURATION   42
#define BORDER_HSV_VALUE        73

#define NO_BLOCK                0

/* S-type blocks color */
#define GREEN_BLOCK_TYPE        1
#define GREEN_RGB888            0x8fff4a
#define GREEN_RGB565            0x8fe9
#define GREEN_HSV_HUE           97
#define GREEN_HSV_SATURATION    71
#define GREEN_BLOCK_TOP888      0xd0ffb3
#define GREEN_BLOCK_TOP565      0xcff5
#define GREEN_BLOCK_SIDES888    0x73cc3b
#define GREEN_BLOCK_SIDES565    0x6e47
#define GREEN_BLOCK_BOTTOM888   0x56992c
#define GREEN_BLOCK_BOTTOM565   0x54a5

/* Z-type blocks color */
#define RED_BLOCK_TYPE          2
#define RED_RGB888              0xff3215
#define RED_RGB565              0xf982
#define RED_HSV_HUE             7
#define RED_HSV_SATURATION      92
#define RED_BLOCK_TOP888        0xffbcb3
#define RED_BLOCK_TOP565        0xfdd5
#define RED_BLOCK_SIDES888      0xcc2811
#define RED_BLOCK_SIDES565      0xc122
#define RED_BLOCK_BOTTOM888     0x991e0d
#define RED_BLOCK_BOTTOM565     0x90e1

/* T-type blocks color */
#define PURPLE_BLOCK_TYPE       3
#define PURPLE_RGB888           0x9c31ff
#define PURPLE_RGB565           0x999f
#define PURPLE_HSV_HUE          271
#define PURPLE_HSV_SATURATION   81
#define PURPLE_BLOCK_TOP888     0xdab3ff
#define PURPLE_BLOCK_TOP565     0xd59f
#define PURPLE_BLOCK_SIDES888   0x7d27cc
#define PURPLE_BLOCK_SIDES565   0x7938
#define PURPLE_BLOCK_BOTTOM888  0x5d1d99
#define PURPLE_BLOCK_BOTTOM56i5  0x58f2
                             
/* Square-type blocks color */
#define YELLOW_BLOCK_TYPE       4
#define YELLOW_RGB888           0xffd504
#define YELLOW_RGB565           0xfea0
#define YELLOW_HSV_HUE          50
#define YELLOW_HSV_SATURATION   100
#define YELLOW_BLOCK_TOP888     0xfff2b3
#define YELLOW_BLOCK_TOP565     0xff75
#define YELLOW_BLOCK_SIDES888   0xccaa03
#define YELLOW_BLOCK_SIDES565   0xc540
#define YELLOW_BLOCK_BOTTOM888  0x998002
#define YELLOW_BLOCK_BOTTOM565  0x93E0

/* Mirrored-L-type blocks color */
#define DARKBLUE_BLOCK_TYPE         5
#define DARKBLUE_RGB888             0x0660ff
#define DARKBLUE_RGB565             0x031f
#define DARKBLUE_HSV_HUE            218
#define DARKBLUE_HSV_SATURATION     100
#define DARKBLUE_BLOCK_TOP888       0xb3ceff
#define DARKBLUE_BLOCK_TOP565       0xae5f
#define DARKBLUE_BLOCK_SIDES888     0x044dcc
#define DARKBLUE_BLOCK_SIDES565     0x0278
#define DARKBLUE_BLOCK_BOTTOM888    0x033999
#define DARKBLUE_BLOCK_BOTTOM565    0x01d2

/* L-type blocks color */
#define ORANGE_BLOCK_TYPE       6
#define ORANGE_RGB888           0xff971d
#define ORANGE_RGB565           0xfca3
#define ORANGE_HSV_HUE          32
#define ORANGE_HSV_SATURATION   90
#define ORANGE_BLOCK_TOP888     0xffdcb3
#define ORANGE_BLOCK_TOP565     0xfed5
#define ORANGE_BLOCK_SIDES888   0xcc7917
#define ORANGE_BLOCK_SIDES565   0xc3a2
#define ORANGE_BLOCK_BOTTOM888  0x995b11
#define ORANGE_BLOCK_BOTTOM565  0x92c2

/* I-type blocks color */
#define BLUE_BLOCK_TYPE         7
#define BLUE_RGB888             0x00fff6
#define BLUE_RGB565             0x07fe
#define BLUE_HSV_HUE            178
#define BLUE_HSV_SATURATION     100
#define BLUE_BLOCK_TOP888       0xb3fffc
#define BLUE_BLOCK_TOP565       0xaffe
#define BLUE_BLOCK_SIDES888     0x00ccc5
#define BLUE_BLOCK_SIDES565     0x0657
#define BLUE_BLOCK_BOTTOM888    0x009994
#define BLUE_BLOCK_BOTTOM565    0x04b1

#define DEFAULT_HSV_VALUE       100     /* Blocks center color */
#define SIDES_HSV_VALUE         80      /* Blocks left and right color */
#define BOTTOM_HSV_VALUE        60      /* Blocks bottom color */
#define TOP_HSV_SATURATION      30      /* Blocks top color */

unsigned short hsv2rgb_lcd(int hue, int saturation, int value);
unsigned short rgb888_to_rgb565(int color);

#endif
