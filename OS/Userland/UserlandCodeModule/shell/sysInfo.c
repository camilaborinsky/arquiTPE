#include<syscalls.h>
#include "sysInfo.h"
#include<stdlib.h>


void getcpuid(char * out);

void cpuid(int argc,char * args[]){
    char buffer[32];
    getcpuid(buffer);
    puts(buffer);
}

void localtime(int argc, char * args[]){
    char buffer[32];
    sys_localtime(buffer);
    puts(buffer);
}

void cputemp( int argc, char * args[]){
    int res=0;
    sys_cputemp(&res);
    printf("%d *C",res);
}
