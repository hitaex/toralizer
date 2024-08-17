#include "toralize.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {
    char *host;
    int port, s;
    struct sockaddr_in sock;

    if (argc < 3) {
        fprintf(stderr, "USAGE: %s <host> <port>\n", argv[0]);
        return -1;
    }

    host = argv[1];
    port = atoi(argv[2]);

    // Further code to utilize `host` and `port` would go here.

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0){
        perror("Socket");
        return -1;
    }
    sock.sin_family = AF_INET;
    sock.sin_port = htons(PROXYPORT);
    sock.sin_addr.s_addr = inet_addr(PROXY);
    if (!connect(s, (struct sockaddr *)&sock, sizeof(sock))){
        perror("connect");
        return -1;
    }
    printf("Connected to proxy! ");
    close(s);


    return 0;
}
