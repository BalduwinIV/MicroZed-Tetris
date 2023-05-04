#include "score.h"

#define ONE_LINE_POINTS     40
#define TWO_LINES_POINTS    100
#define THREE_LINES_POINTS  300
#define FOUR_LINES_POINTS   1200

unsigned int points[4] = { ONE_LINE_POINTS, TWO_LINES_POINTS, THREE_LINES_POINTS, FOUR_LINES_POINTS };

unsigned int calculate_score(unsigned char blocks_speed, unsigned char cleared_rows_at_the_moment) {
    return blocks_speed * points[cleared_rows_at_the_moment-1];
}
