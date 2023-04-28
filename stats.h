#ifndef STATS_H
#define STATS_h

void print_stats(unsigned int **screen, unsigned char block_type, char* amount, char* score);

void print_blocks_amount(unsigned int **screen, unsigned char block_type, char* amount);

void print_destroyed_lines(unsigned int **screen, char* amount);

void print_best_score(unsigned int **screen, char* best_score);

#endif