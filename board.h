#ifndef BOARD_H
#define BOARD_H

#define ROWS 4
#define COLS 5

void init_board();
void print_board();
int make_move(int r1, int c1, int r2, int c2, char player);
int is_full();

int get_scoreA();
int get_scoreB();
int is_valid_move(int r1, int c1, int r2, int c2);
int count_sides(int i, int j);
#endif