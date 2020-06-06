#ifndef WINDOWS_H_
#define WINDOWS_H_
#include <errors.h>

#define OUT_LENGTH 2000
#define LINES_LENGTH 50
#define IN_LENGTH 512


typedef struct colorStruct{
    uint8_t red;
    uint8_t green;
    uint8_t blue;

} colorStruct;

typedef struct rect{
    unsigned int xi,yi;
    unsigned int xf, yf;
    unsigned char fill;
    unsigned int border;
    colorStruct c;
    
}rect;


typedef struct screen{
	int xi,yi,xf,yf;
}screen;

typedef struct tabStruct{
	void  (* run)(char *, char *);
	void (* inController) (int);
	void (* exceptionsHandler)(errorStruct *);
	char in[IN_LENGTH];
	char out[OUT_LENGTH];
	int inIndex;
	int px;
	screen currentScreen;
	int offsetCurrent;
	int current;
}tabStruct;


void drawString(char *, tabStruct * );
int strcpyTab(char * src, char * dest, tabStruct * tab);

#endif