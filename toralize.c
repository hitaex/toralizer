#include "toralize.h"
#include <arpa/inet.h>
#include <dlfcn.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

req *request(struct sockaddr_in *sock2){  
    req *Req = malloc(reqsize);
    Req->vn = 4;
    Req->cd = 1;
    Req->dstport = sock2->sin_port;
    Req->dstip = sock2->sin_addr.s_addr;
    strncpy((char *)Req->userid, USERNAME, 8);
    return Req;
}


// int main(int argc, char *argv[]) {
    int connect(int s2, const struct sockaddr *sock2,
    socklen_t addrlen){
   
    int  s;
    struct sockaddr_in sock;
    char buf[ressize];
    int success;
    char tmp[512];
    int (*p)(int , const struct sockaddr*,
    socklen_t );
   

  
    p=dlsym(RTLD_NEXT, "connect");
  
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
    if (p(s, (struct sockaddr *)&sock, sizeof(sock))){
        perror("connect");
        return -1;
    }
    printf("Connected to proxy! ");
    Req = request((struct sockaddr_in*)&sock2);
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
    printf("successfully connected through the proxy ");
    
    dup2(s, s2);
    free(Req);
    

    

    
    return 0;
}
