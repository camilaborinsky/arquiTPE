#ifndef VIDEO_H
#define VIDEO_H
#include <stdint.h>
void drawCharacter(int x, int y, int px, char letter);
void drawBitmap(int x, int y, char * bitmap[]);
void scroll(int xi, int yi, int xf, int yf, int px);
#endif