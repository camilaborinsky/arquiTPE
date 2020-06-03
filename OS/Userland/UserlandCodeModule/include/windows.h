#ifndef WINDOWS_H_
#define WINDOWS_H_
#include <errors.h>

typedef struct screen{
	int xi,yi,xf,yf;
}screen;

typedef struct tabStruct{
	void  (* run)(char *, char *);
	void (* inController) (int);
	void (* exceptionsHandler)(int,errorStruct *);
	char in[512];
	char out[2000];
	int inIndex;
	int px;
	screen currentScreen;
	int offsetCurrent;
	int current;
}tabStruct;

void updateTab(tabStruct * currentTab);
void clearTab(tabStruct * currentTab);

void printString(char *, tabStruct * );
#endif