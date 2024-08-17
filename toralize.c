#include "toralize.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

  req *request(const char*dstip, const int dstport){
    req *Req;
    Req = malloc(reqsize);


    Req->vn = 4;
    Req->cd = 1;
    Req->dstport = htons(dstport);
    Req->dstip = inet_addr(dstip);
    strncpy((char *)Req->userid, USERNAME, 8);
    
    
      return Req;
    }


int main(int argc, char *argv[]) {
    char *host;
    int port, s;
    struct sockaddr_in sock;
    char buf[ressize];
    int success;
    
    if (argc < 3) {
        fprintf(stderr, "USAGE: %s <host> <port>\n", argv[0]);
        return -1;
    }

    host = argv[1];
    port = atoi(argv[2]);

  
    req *Req;
    res *Res;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0){
        perror("Socket");
        return -1;
    }
    sock.sin_family = AF_INET;
    sock.sin_port = htons(PROXYPORT);
    sock.sin_addr.s_addr = inet_addr(PROXY);
    if (connect(s, (struct sockaddr *)&sock, sizeof(sock))){
        perror("connect");
        return -1;
    }
    printf("Connected to proxy! ");
    Req = request(host, port);
    write(s, Req, reqsize);
    memset(buf, 0,ressize);
    if (read(s,buf,ressize)<1){
        perror("read");
        free(Req);
        close(s);
        return -1;
    }
    Res = (res*)buf;
    success = (Res->cd == 90);

    if(!success){
        fprintf(stderr,"unable to traverse the proxy!, Error code: %d \n", Res->cd);
        close(s);
        free(Req);
        return -1;
    }
    printf("successfully connected through the proxy to %s:%d\n", host ,port);
    close(s);
    free(Req);
    

    close(s);

    
    return 0;
}
