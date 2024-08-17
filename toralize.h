#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define PROXY "127.0.0.1"
#define PROXYPORT 9050
// 8 bit 
typedef unsigned char int8 ;
// 16 bit
typedef short int int16 ;
//32 bit
typedef unsigned int32 ;
/*      +----+----+----+----+----+----+----+----+----+----+....+----+
		| VN | CD | DSTPORT |      DSTIP        | USERID       |NULL|
		+----+----+----+----+----+----+----+----+----+----+....+----+
 # of bytes:	   1    1      2              4           variable       1*/
struct proxy_req {
    int8 vn;
    int8 cd;
    int16 dstport;
    int32 dstip;
    unsigned char userid[8];
};
typedef struct proxy_req req; ;
/*+----+----+----+----+----+----+----+----+
		| VN | CD | DSTPORT |      DSTIP        |
		+----+----+----+----+----+----+----+----+
 # of bytes:	   1    1      2              4*/
 struct proxy_res{
    int8 vn;
    int8 cd;
    int16 _;
    int32 __;

 };
typedef struct proxy_res res ;