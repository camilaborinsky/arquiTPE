#ifndef KEYBOARD_H
#define KEYBOARD_H
void keyboard_handler();
void readKeyboard(int * buffer, int count,int * amount);
char getKey();
char hasKey();
char getPort64();

#endif