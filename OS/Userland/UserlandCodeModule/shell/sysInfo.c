#include<syscalls.h>
#include "sysInfo.h"
#include<stdlib.h>

void localtime(char * out, int argc, char * args[]){
    sys_localtime(out);
}

void cputemp(char * out, int argc, char * args[]){
    int res=0;
    sys_cputemp(&res);
    int c = intToString(res, out);
    out[c++]=' ';
    out[c++]='*';
    out[c++]='C';
    out[c]=0; 
}
