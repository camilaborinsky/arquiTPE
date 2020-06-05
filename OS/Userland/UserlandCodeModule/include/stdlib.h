#ifndef STDIO_H_
#define STDIO_H_

#include <stdint.h>


void printNum(uint64_t num);
int getChar();
uint64_t atoi(char *);
void deleteChar(char * str, char c);
int strcpy(char * dest, char * source);
int strcmp(char * str1, char * str2);

#endif