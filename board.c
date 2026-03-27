#include <stdio.h>
#include <stdlib.h>
#include "board.h"

char h[ROWS+1][COLS];     // horizontal edges
char v[ROWS][COLS+1];     // vertical edges
char box[ROWS][COLS];     // box owners

int scoreA = 0, scoreB = 0;

void init_board() {
    for(int i=0;i<=ROWS;i++)
        for(int j=0;j<COLS;j++)
            h[i][j] = 0;

    for(int i=0;i<ROWS;i++)
        for(int j=0;j<=COLS;j++)
            v[i][j] = 0;

    for(int i=0;i<ROWS;i++)
        for(int j=0;j<COLS;j++)
            box[i][j] = ' ';
}

void print_board() {
    // column numbers
    printf("   ");
    for(int j=0;j<=COLS;j++)
        printf("%d   ", j);
    printf("\n");

    for(int i=0;i<=ROWS;i++) {

        // horizontal line row
        if(i < ROWS) printf("%d  ", i);
        else printf("   ");

        for(int j=0;j<COLS;j++) {
            printf(".");
            if(h[i][j]) printf("---");
            else printf("   ");
        }
        printf(".\n");

        if(i == ROWS) break;

        // vertical + boxes
        printf("   ");
        for(int j=0;j<COLS;j++) {
            if(v[i][j]) printf("|");
            else printf(" ");

            if(box[i][j] != ' ')
                printf("[%c]", box[i][j]);
            else
                printf("   ");
        }

        if(v[i][COLS]) printf("|");
        printf("\n");
    }
}

int check_box(int i, int j, char player) {
    if(box[i][j] != ' ') return 0;

    if(h[i][j] && h[i+1][j] &&
       v[i][j] && v[i][j+1]) {

        box[i][j] = player;
        if(player == 'A') scoreA++;
        else scoreB++;
        return 1;
    }
    return 0;
}

int make_move(int r1, int c1, int r2, int c2, char player) {
    int completed = 0;

    // horizontal
    if(r1 == r2 && abs(c1 - c2) == 1) {
        int c = (c1 < c2) ? c1 : c2;

        if(h[r1][c]) return -1;
        h[r1][c] = 1;

        if(r1 > 0) completed += check_box(r1-1, c, player);
        if(r1 < ROWS) completed += check_box(r1, c, player);
    }
    // vertical
    else if(c1 == c2 && abs(r1 - r2) == 1) {
        int r = (r1 < r2) ? r1 : r2;

        if(v[r][c1]) return -1;
        v[r][c1] = 1;

        if(c1 > 0) completed += check_box(r, c1-1, player);
        if(c1 < COLS) completed += check_box(r, c1, player);
    }
    else return -1;

    return completed;
}

int is_full() {
    for(int i=0;i<ROWS;i++)
        for(int j=0;j<COLS;j++)
            if(box[i][j] == ' ')
                return 0;
    return 1;
}

int get_scoreA() { return scoreA; }
int get_scoreB() { return scoreB; }