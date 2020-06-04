#include<shell.h>
#include "help.h"
#include "exceptionLauncher.h"
#include <stdlib.h>
#include "printmem.h"

char * messages[] = {"Command not found"};
char * commands[] = {"help","inforeg","printmem","cputemp", "cpuid", "localtime", "divisionbyzero", "invalidopcode",0};
void  (* run[])(char *) = {help, 0, printmem, 0, 0, 0, divisionbyzero, invalidopcode};

void shell(char * in, char * out){
    deleteChar(in,' ');
    int command = checkCommand(in);
    if(command == -1){
        strcpy(out, messages[0]);
    }
    else
        run[command](out);
}

int checkCommand(char * command){
    int cmp=1;
    int cmd = 0;
    while(commands[cmd] && cmp){
        cmp = strcmp(commands[cmd++],command);
    }

    return (cmp==0)?cmd-1:-1;

}