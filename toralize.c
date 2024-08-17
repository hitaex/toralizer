#include "toralize.h"

int main(int argc, char *argv[]) {
    char *host;
    int port;

    if (argc < 3) {
        fprintf(stderr, "USAGE: %s <host> <port>\n", argv[0]);
        return -1;
    }

    host = argv[1];
    port = atoi(argv[2]);

    // Further code to utilize `host` and `port` would go here.

    return 0;
}
