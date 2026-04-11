#include <stdio.h>
#include "game.h"
#include "board.h"
#include "bot.h"

void start_game() {

    
    char player = 'A';

    init_board();

    int mode;
    printf("1. Player vs Player\n2. Player vs Bot\nChoose mode: ");
    scanf("%d", &mode);

    while(!is_full()) {
        print_board();

        int res;

        if(mode == 2 && player == 'B') {
        // BOT TURN
            printf("Player %c's turn. Enter the row and column of the first dot (e.g., A0 -> 0 0) and second dot:\n", player);
            res = bot_move();   // bot plays automatically
        } else {
            // HUMAN TURN (UNCHANGED TEXT)
            printf("Player %c's turn. Enter the row and column of the first dot (e.g., A0 -> 0 0) and second dot:\n", player);

            int r1,c1,r2,c2;
            scanf("%d %d %d %d", &r1, &c1, &r2, &c2);

            res = make_move(r1,c1,r2,c2,player);
    }

        if(res == -1) {
            printf("Invalid move. Try again.\n");
            continue;
        }

        if(res == 0) {
            player = (player == 'A') ? 'B' : 'A';
        }

        printf("*********************************************************************\n");
        printf("Player A score: %d\n", get_scoreA());
        printf("Player B score: %d\n", get_scoreB());
        printf("*********************************************************************\n");
    }

    print_board();

    printf("Final Scores:\n");
    printf("Player A: %d\n", get_scoreA());
    printf("Player B: %d\n", get_scoreB());

    if(get_scoreA() > get_scoreB()) printf("Player A wins!\n");
    else if(get_scoreB() > get_scoreA()) printf("Player B wins!\n");
    else printf("Draw!\n");
}