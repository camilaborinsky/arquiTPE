#ifndef STDIO_H_
#define STDIO_H_

#include <stdint.h>


void printNum(uint64_t num);
void hlt();
int getChar();
uint64_t atoi(char *);
void deleteChar(char * str, char c);
int intToHex(int num, char * buffer);
int intToBase(int num, int base, char*buffer);
int intToString(int num, char * buffer);
int strcpy(char * dest, char * source);
int strcmp(char * str1, char * str2);

#endif