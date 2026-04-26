#ifndef NETWORK_H
#define NETWORK_H

void start_server(int port);
void connect_to_server(char *ip, int port);

void send_move(int r1, int c1, int r2, int c2);
void receive_move(int *r1, int *c1, int *r2, int *c2);

#endif