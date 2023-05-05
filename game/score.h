#ifndef SCORE_H
#define SCORE_H

#define ONE_LINE_POINTS     40
#define TWO_LINES_POINTS    100
#define THREE_LINES_POINTS  300
#define FOUR_LINES_POINTS   1200

unsigned int calculate_score(unsigned char blocks_speed, unsigned char cleared_rows_at_the_moment);

#endif
