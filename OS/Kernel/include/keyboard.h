#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <registersArgs.h>
#include <stdint.h>


void keyboard_handler(registerArgs * regs);
void readKeyboard(int * buffer, int count,int * amount);
char getKey();
char hasKey();
char getPort64();
void retrieveRegs(registerArgs * args, int * flag);

#endif