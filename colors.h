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

/* S-type blocks color */
#define GREEN_RGB888            0x8fff4a
#define GREEN_RGB565            0x8fe9
#define GREEN_HSV_HUE           97
#define GREEN_HSV_SATURATION    71

/* Z-type blocks color */
#define RED_RGB888              0xff3215
#define RED_RGB565              0xf982
#define RED_HSV_HUE             7
#define RED_HSV_SATURATION      92

/* T-type blocks color */
#define PURPLE_RGB888           0x9c31ff
#define PURPLE_RGB565           0x999f
#define PURPLE_HSV_HUE          271
#define PURPLE_HSV_SATURATION   81

/* Square-type blocks color */
#define YELLOW_RGB888           0xffd504
#define YELLOW_RGB565           0xfea0
#define YELLOW_HSV_HUE          50
#define YELLOW_HSV_SATURATION   100

/* Mirrored-L-type blocks color */
#define DARKBLUE_RGB888         0x0660ff
#define DARKBLUE_RGB565         0x031f
#define DARKBLUE_HSV_HUE        218
#define DARKBLUE_HSV_SATURATION 100

/* L-type blocks color */
#define ORANGE_RGB888           0xff971d
#define ORANGE_RGB565           0xfca3
#define ORANGE_HSV_HUE          32
#define ORANGE_HSV_SATURATION   90

/* I-type blocks color */
#define BLUE_RGB888             0x00fff6
#define BLUE_RGB565             0x07fe
#define BLUE_HSV_HUE            178
#define BLUE_HSV_SATURATION     100


#define DEFAULT_HSV_VALUE       100     /* Blocks center color */
#define SIDES_HSV_VALUE         80      /* Blocks left and right color */
#define BOTTOM_HSV_VALUE        60      /* Blocks bottom color */
#define TOP_HSV_SATURATION      30      /* Blocks top color */

#endif
