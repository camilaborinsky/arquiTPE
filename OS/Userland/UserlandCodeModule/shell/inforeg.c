#include <stdint.h>
#include "inforeg.h"
#include <stdlib.h>
#include <syscalls.h>

char * registersNames[] = {"r15","r14","r13","r12","r11","r10","r9","r8","rsi","rdi",\
                            "rbp","rdx","rcx","rbx","rax","rip","cs","flags","rsp","ss"};

void inforeg(char * out, int argc, char * args[]){
    char * buffer;
    int flag;
    registerArgs reg;
    sys_retrieveReg(&reg, &flag);
    if(flag == 0){
        strcpy(out, "No se pidio un guardado de registros. Con la tecla CTRL izquierdo puede hacerlo. \n");
        return;
    }
    
    uint64_t * registers =&reg;
    out+=strcpy(out, "registros \n");
        
    for(int i = 0 ; i < REGISTERS ; i++){

        out+=strcpy(out, registersNames[i]);
        out+=strcpy(out,"    ");
        intToHex(registers[i], buffer);
        out+=strcpy(out, buffer);
        out+=strcpy(out,"\n");
    
    }

    
    

}