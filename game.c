#include <stdio.h>
#include <pthread.h>
#include "game.h"
#include "board.h"
#include "bot.h"
#include "network.h"

// 🔒 Thread sync
pthread_mutex_t lock;

int net_r1, net_c1, net_r2, net_c2;
int move_ready = 0;

// 🧵 Thread function (receives moves)
void *receive_thread(void *arg) {
    while(1) {
        int r1,c1,r2,c2;

        receive_move(&r1,&c1,&r2,&c2);

        pthread_mutex_lock(&lock);

        net_r1 = r1;
        net_c1 = c1;
        net_r2 = r2;
        net_c2 = c2;
        move_ready = 1;

        pthread_mutex_unlock(&lock);
    }
}

void start_game() {

    char player = 'A';

    init_board();

    int mode;
    printf("1. Player vs Player\n2. Player vs Bot\n3. Network Host\n4. Network Client\nChoose mode: ");
    scanf("%d", &mode);

    // 🌐 NETWORK SETUP
    if(mode == 3) {
        start_server(8080);
    }
    else if(mode == 4) {
        char ip[50];
        printf("Enter server IP: ");
        scanf("%s", ip);
        connect_to_server(ip, 8080);
    }

    // 🧵 Start thread if network mode
    pthread_t tid;
    if(mode == 3 || mode == 4) {
        pthread_mutex_init(&lock, NULL);
        pthread_create(&tid, NULL, receive_thread, NULL);
    }

    while(!is_full()) {
        print_board();

        int res;
        int r1,c1,r2,c2;

        // 🌐 NETWORK MODE
        if(mode == 3 || mode == 4) {

            int isLocal =
                (mode == 3 && player == 'A') ||
                (mode == 4 && player == 'B');

            if(isLocal) {
                // LOCAL PLAYER
                printf("Player %c's turn. Enter the row and column of the first dot (e.g., A0 -> 0 0) and second dot:\n", player);
                scanf("%d %d %d %d", &r1, &c1, &r2, &c2);

                res = make_move(r1,c1,r2,c2,player);

                if(res != -1) {
                    send_move(r1,c1,r2,c2);
                }
            } else {
                // REMOTE PLAYER (via thread)
                printf("Waiting for opponent move...\n");

                while(1) {
                    pthread_mutex_lock(&lock);

                    if(move_ready) {
                        r1 = net_r1;
                        c1 = net_c1;
                        r2 = net_r2;
                        c2 = net_c2;
                        move_ready = 0;

                        pthread_mutex_unlock(&lock);
                        break;
                    }

                    pthread_mutex_unlock(&lock);
                }

                printf("Opponent played: %d %d %d %d\n", r1,c1,r2,c2);

                res = make_move(r1,c1,r2,c2,player);
            }
        }

        // 🤖 BOT MODE
        else if(mode == 2 && player == 'B') {
            printf("Player %c's turn. Enter the row and column of the first dot (e.g., A0 -> 0 0) and second dot:\n", player);
            res = bot_move();
        }

        // 👤 NORMAL PvP
        else {
            printf("Player %c's turn. Enter the row and column of the first dot (e.g., A0 -> 0 0) and second dot:\n", player);

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