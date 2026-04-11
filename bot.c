#include <stdio.h>
#include "bot.h"
#include "board.h"

// Find a move that completes a box
int find_box_move(int *r1, int *c1, int *r2, int *c2) {
    for(int i=0;i<ROWS;i++) {
        for(int j=0;j<COLS;j++) {
            if(count_sides(i,j) == 3) {
                // check all 4 sides and pick missing one

                // top
                if(is_valid_move(i,j,i,j+1)) {
                    *r1=i; *c1=j; *r2=i; *c2=j+1;
                    return 1;
                }
                // bottom
                if(is_valid_move(i+1,j,i+1,j+1)) {
                    *r1=i+1; *c1=j; *r2=i+1; *c2=j+1;
                    return 1;
                }
                // left
                if(is_valid_move(i,j,i+1,j)) {
                    *r1=i; *c1=j; *r2=i+1; *c2=j;
                    return 1;
                }
                // right
                if(is_valid_move(i,j+1,i+1,j+1)) {
                    *r1=i; *c1=j+1; *r2=i+1; *c2=j+1;
                    return 1;
                }
            }
        }
    }
    return 0;
}

// Pick any valid move (basic safe fallback)
int find_safe_move(int *r1, int *c1, int *r2, int *c2) {
    // horizontal
    for(int i=0;i<=ROWS;i++) {
        for(int j=0;j<COLS;j++) {
            if(is_valid_move(i,j,i,j+1)) {
                *r1=i; *c1=j; *r2=i; *c2=j+1;
                return 1;
            }
        }
    }

    // vertical
    for(int i=0;i<ROWS;i++) {
        for(int j=0;j<=COLS;j++) {
            if(is_valid_move(i,j,i+1,j)) {
                *r1=i; *c1=j; *r2=i+1; *c2=j;
                return 1;
            }
        }
    }

    return 0;
}

int bot_move() {
    int r1,c1,r2,c2;

    // 1. Complete box if possible
    if(find_box_move(&r1,&c1,&r2,&c2)) {
        printf("Bot plays: %d %d %d %d\n", r1,c1,r2,c2);
        return make_move(r1,c1,r2,c2,'B'); // ✅ ONLY ONCE
    }

    // 2. Otherwise pick safe move
    if(find_safe_move(&r1,&c1,&r2,&c2)) {
        printf("Bot plays: %d %d %d %d\n", r1,c1,r2,c2);
        return make_move(r1,c1,r2,c2,'B'); // ✅ ONLY ONCE
    }

    return -1; // should never happen
}