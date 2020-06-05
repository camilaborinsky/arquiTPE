#include<stdlib.h>


void printmem(char * out, int argc, char * args[]){
    if(argc != 1){
        strcpy(out, "cantidad de argumentos invalida");
        return;
    }
    unsigned char * pointer = atoi(args[0]);
    char buffer[4];
    for(int i=0; i<32; i++){
        intToHex(pointer[i],buffer);
        out += strcpy(out,buffer);
        *out++=' ';
    }
}