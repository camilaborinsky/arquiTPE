#include "help.h"
#include <stdlib.h>
void help(char * out, int argc, char * args[]){
    strcpy(out,
        "available commands: \n"
        "    help \n"
        "    inforeg \n"
        "    cpuid \n"
        "    cputemp \n"
        "    printmem \n"
        "    divisionbyzero \n"
        "    invalidopcode \n"
        "    localtime \n"
        "for more information you can use google \n"
    );
}