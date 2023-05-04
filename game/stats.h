#ifndef STATS_H
#define STATS_H

void print_statistics(unsigned short **screen, unsigned int *statistics);

void print_score(unsigned short **screen, unsigned int score);

void print_best_score(unsigned short **screen, unsigned int best_score);

void print_next_block(unsigned short **screen, unsigned char element_index);

void print_destroyed_lines_number(unsigned short **screen, unsigned int lines_amount);

#endif
