#include<stdlib.h>

void printmem(char * pointer, char * out){
    char buffer[4];
    for(int i=0; i<32; i++){
        intToHex(pointer[i],buffer);
        out += strcpy(out,buffer);
        *out++=' ';
    }
}