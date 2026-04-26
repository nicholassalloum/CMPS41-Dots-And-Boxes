#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int sockfd;

void start_server(int port) {
    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 1);

    printf("Waiting for connection...\n");
    sockfd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    printf("Client connected!\n");
}

void connect_to_server(char *ip, int port) {
    struct sockaddr_in serv_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    inet_pton(AF_INET, ip, &serv_addr.sin_addr);

    connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    printf("Connected to server!\n");
}

void send_move(int r1, int c1, int r2, int c2) {
    int data[4] = {r1, c1, r2, c2};
    send(sockfd, data, sizeof(data), 0);
}

void receive_move(int *r1, int *c1, int *r2, int *c2) {
    int data[4];
    recv(sockfd, data, sizeof(data), 0);

    *r1 = data[0];
    *c1 = data[1];
    *r2 = data[2];
    *c2 = data[3];
}