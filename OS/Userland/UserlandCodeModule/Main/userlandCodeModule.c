#include <syscalls.h>
#include <stdint.h>
#include <setJmp.h>
#include "pixMaps.h"
#include <windows.h>
#include <errors.h>
#include <stdlib.h>
#include "defs.h"
#include <calculator.h>
#include <shell.h>

#define RADIUS 1
unsigned char focus = 0;
#define resX  1024
#define resY  768

tabStruct tab0 = {evaluator,inControllerTab0,0,{0},{0},0,15,{3,3,(resX/2)-3,resY-3},0,0};
tabStruct tab1 = {shell,inControllerTab1,0,{0},{0},0,10,{(resX/2)+5,3,resX-3,resY-3},0,0};

tabStruct * tabs[]={&tab0,&tab1};

registerEnv env;
int main() {

	sys_drawBitmap(497,0,linea_vertical_color_xpm);
	sys_drawBitmap(0,0,linea_vertical_color_xpm);
	sys_drawBitmap(0,0,linea_horizontal_color_xmp);
	sys_drawBitmap(0,1000,linea_horizontal_color_xmp);
	int c=0;
	

	sys_setExceptionHandler(0,divisionByZeroHandler); //esta parte siempre justo antes del while
	sys_setExceptionHandler(6,invalidOpcodeHandler);
	int entry=setjmp(&env)-1;
	if(entry != -1){
		tabs[focus]->exceptionsHandler(entry,0);
	}

	//que arranquen las pantallas con username escrito
	for(int i=0;i<NUM_TABS;i++){
		strcpy(tabs[i]->out+tabs[i]->current,"usr@coronavinux:>");
		drawString(tabs[i]->out,tabs[i]);
		tabs[i]->offsetCurrent = tabs[i]->current+1;
		tabs[i]->inIndex=0;
	}
	while(1){
		while((c=getChar()) !='\n'){
			if(c=='\t'){
				focus = (focus+1)%NUM_TABS;
				if(focus ==0){
					sys_drawBitmap((resX/2)-3,0,linea_vertical_color_xpm);
					sys_drawBitmap(resX/2,0,linea_vertical_negra_xpm);
					sys_drawBitmap(0,0,linea_vertical_color_xpm);
					sys_drawBitmap(resX,0,linea_vertical_negra_xpm);
					sys_drawBitmap(0,0,linea_horizontal_color_xmp);
					sys_drawBitmap(0,resY,linea_horizontal_color_xmp);
					sys_drawBitmap(resX/2,0,linea_horizontal_negra_xmp);
					sys_drawBitmap((resX/2)-3,resY,linea_horizontal_negra_xmp);
				}else{//estamos en la pantalla de la derecha
					sys_drawBitmap(497,0,linea_vertical_negra_xpm);
					sys_drawBitmap(500,0,linea_vertical_color_xpm);
					sys_drawBitmap(0,0,linea_vertical_negra_xpm);
					sys_drawBitmap(1000,0,linea_vertical_color_xpm);
					sys_drawBitmap(0,0,linea_horizontal_negra_xmp);
					sys_drawBitmap(0,1000,linea_horizontal_negra_xmp);
					sys_drawBitmap(resX/2,0,linea_horizontal_color_xmp);
					sys_drawBitmap((resX/2)-3,1000,linea_horizontal_color_xmp);
				}
			}else{
				tabs[focus]->inController(c);
			}
		}

		tabStruct * currentTab = tabs[focus];
		drawString("\n",currentTab);
		//drawString(currentTab->in,currentTab);
		//drawString("\n",currentTab);
		currentTab->run(currentTab->in,currentTab->out);
		drawString(currentTab->out,currentTab);
		drawString("\n",currentTab);
		strcpy(currentTab->out,"usr@coronavinux:>");
		drawString(currentTab->out,currentTab);
		currentTab->offsetCurrent = currentTab->current+1;
		currentTab->inIndex=0;
		currentTab->in[0]=0;
	}

	return 0;
}

void runGenerico(char * in,char * out){
	return;
}


void genericInController(int c, tabStruct * tab){
	if(c==8){
		if(tab->inIndex>0)
			tab->inIndex--;
	}
	else{
		tab->in[tab->inIndex++] = c;
		tab->in[tab->inIndex]=0;
	}

	tab->out[0]=c;
	tab->out[1]=0;
	if(c!=0)drawString(tab->out,tab);	
}

void inControllerTab1(int c){
	genericInController(c,&tab1);
	
}

void inControllerTab0(int c){

	genericInController(c,&tab0);
	
}


void divisionByZeroHandler(){
	longjmp(&env,1);
}

void invalidOpcodeHandler(){
	longjmp(&env,7);
}

