#include <syscalls.h>
#include <stdint.h>
#include <setJmp.h>
#include "pixMaps.h"
#include <windows.h>
#include <errors.h>
#include <stdlib.h>
#include "defs.h"

unsigned char focus = 0;

tabStruct tab0 = {runGenerico,inControllerTab0,0,{0},{0},0,12,{0,0,500,1000},0,0};
tabStruct tab1 = {runGenerico,inControllerTab1,0,{0},{0},0,12,{510,0,1000,1000},0,0};

tabStruct * tabs[]={&tab0,&tab1};

registerEnv env;
int main() {

	sys_drawBitmap(500,0,linea_xpm);
	
	int c=0;
	

	sys_setHandler(0,divisionByZeroHandler); //esta parte siempre justo antes del while
	sys_setHandler(6,invalidOpcodeHandler);
	int entry=setjmp(&env)-1;
	if(entry != -1){
		tabs[focus]->exceptionsHandler(entry,0);
	}


	while(1){
		while((c=getChar()) !='/n'){
			if(c=='\t'){
				focus = (focus+1)%NUM_TABS;
			}else{
				tabs[focus]->inController(c);
			}	
		}
		printString("\n",tabs[focus]);
		tabs[focus]->run(tabs[focus]->in,tabs[focus]->out);
		printString(tabs[focus]->out,tabs[focus]);
	}

	return 0;
}

void runGenerico(char * in,char * out){
	return;
}


void inControllerTab1(int c){
	tabs[1]->in[tabs[1]->inIndex++] = c;
	char str[2];
	str[0] = c;
	str[1] = 0;
	printString(str,tabs[1]);

}
void inControllerTab0(int c){
	tabs[0]->in[tabs[0]->inIndex++] = c;
	char str[2];
	str[0] = c;
	str[1] = 0; 
	printString(str,tabs[0]);
	
}

void divisionByZeroHandler(){
	longjmp(&env,1);
}

void invalidOpcodeHandler(){
	longjmp(&env,7);
}

