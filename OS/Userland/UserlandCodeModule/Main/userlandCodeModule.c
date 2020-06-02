#include <syscalls.h>
#include <stdint.h>
#include <setJmp.h>
#include "pixMaps.h"
#include <windows.h>
#include <errors.h>
#include <stdlib.h>
#include "defs.h"
#include <calculator.h>

unsigned char focus = 0;

tabStruct tab0 = {evaluator,inControllerTab0,0,{0},{0},0,12,{3,3,497,997},0,0};
tabStruct tab1 = {runGenerico,inControllerTab1,0,{0},{0},0,12,{510,3,997,997},0,0};

tabStruct * tabs[]={&tab0,&tab1};

registerEnv env;
int main() {

	sys_drawBitmap(497,0,linea_vertical_color_xpm);
	sys_drawBitmap(0,0,linea_vertical_color_xpm);
	sys_drawBitmap(0,0,linea_horizontal_color_xmp);
	sys_drawBitmap(0,1000,linea_horizontal_color_xmp);
	int c=0;
	

	sys_setHandler(0,divisionByZeroHandler); //esta parte siempre justo antes del while
	sys_setHandler(6,invalidOpcodeHandler);
	int entry=setjmp(&env)-1;
	if(entry != -1){
		tabs[focus]->exceptionsHandler(entry,0);
	}

	for(int i=0;i<NUM_TABS;i++)printString("\n",tabs[i]);

	while(1){
		while((c=getChar()) !='\n'){
			if(c=='\t'){
				focus = (focus+1)%NUM_TABS;
				if(focus ==0){
					sys_drawBitmap(497,0,linea_vertical_color_xpm);
					sys_drawBitmap(500,0,linea_vertical_negra_xpm);
					sys_drawBitmap(0,0,linea_vertical_color_xpm);
					sys_drawBitmap(1000,0,linea_vertical_negra_xpm);
					sys_drawBitmap(0,0,linea_horizontal_color_xmp);
					sys_drawBitmap(0,1000,linea_horizontal_color_xmp);
					sys_drawBitmap(500,0,linea_horizontal_negra_xmp);
					sys_drawBitmap(500,1000,linea_horizontal_negra_xmp);
				}else{//estamos en la pantalla de la derecha
					sys_drawBitmap(497,0,linea_vertical_negra_xpm);
					sys_drawBitmap(500,0,linea_vertical_color_xpm);
					sys_drawBitmap(0,0,linea_vertical_negra_xpm);
					sys_drawBitmap(1000,0,linea_vertical_color_xpm);
					sys_drawBitmap(0,0,linea_horizontal_negra_xmp);
					sys_drawBitmap(0,1000,linea_horizontal_negra_xmp);
					sys_drawBitmap(500,0,linea_horizontal_color_xmp);
					sys_drawBitmap(500,1000,linea_horizontal_color_xmp);
				}
			}else{
				tabs[focus]->inController(c);
			}	
		}
		tabs[focus]->inController(0);
		printString("\n",tabs[focus]);
		tabs[focus]->run(tabs[focus]->in,tabs[focus]->out);
		printString(tabs[focus]->out,tabs[focus]);
		printString("\n",tabs[focus]);
		tabs[focus]->inIndex=0;
	}

	return 0;
}

void runGenerico(char * in,char * out){
	return;
}


void inControllerTab1(int c){
	if(c==8)
		if(tabs[1]->inIndex>0)tabs[1]->inIndex--;
	else
		tabs[1]->in[tabs[1]->inIndex++] = c;
	char str[2];
	str[0] = c;
	str[1] = 0;
	if(c!=0)printString(str,tabs[1]);

}
void inControllerTab0(int c){
	if(c==8){
		if(tabs[0]->inIndex>0)
			tabs[0]->inIndex--;
	}else
		tabs[0]->in[tabs[0]->inIndex++] = c;
	char str[2];
	str[0] = c;
	str[1] = 0; 
	if(c!=0)printString(str,tabs[0]);
	
}

void divisionByZeroHandler(){
	longjmp(&env,1);
}

void invalidOpcodeHandler(){
	longjmp(&env,7);
}

