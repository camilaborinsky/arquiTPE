#include<syscalls.h>
#include "sysInfo.h"

void localtime(char * out, int argc, char * args[]){
    sys_localtime(out);
}

void cputemp(char * out, int argc, char * args[]){
    return;
}
