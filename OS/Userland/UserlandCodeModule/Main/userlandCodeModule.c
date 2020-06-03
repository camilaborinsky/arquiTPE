#include <syscalls.h>
#include <stdint.h>
#include <setJmp.h>
#include "pixMaps.h"
#include <windows.h>
#include <errors.h>
#include <stdlib.h>
#include "defs.h"
#include <calculator.h>

#define RADIUS 1
unsigned char focus = 0;
#define resX  1024
#define resY  768

tabStruct tab0 = {evaluator,inControllerTab0,0,{0},{0},0,12,{3,3,(resX/2)-3,resY-3},0,0,0,0,{0}};
tabStruct tab1 = {runGenerico,inControllerTab1,0,{0},{0},0,12,{(resX/2)+5,3,resX-3,resY-3},0,0,0,0,{0}};

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

	//que arranquen las pantallas con username escrito
	for(int i=0;i<NUM_TABS;i++){
		strcpyTab(tabs[focus]->out+tabs[i]->current,"horacio:>",tabs[i]);
		tabs[i]->offsetCurrent = tabs[i]->current+1;
		tabs[i]->inIndex=0;
		updateRadius(tabs[i], RADIUS);
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
			updateRadius(tabs[focus], RADIUS);	
		}

		tabStruct * currentTab = tabs[focus];

		tabs[focus]->inController(0);
		tabs[focus]->inController('\n');
		//printString("\n",tabs[focus]);
		char buffer[64]={0};
		tabs[focus]->run(tabs[focus]->in,buffer);
		strcpyTab(currentTab->out+currentTab->current,buffer,tabs[focus]);
		tabs[focus]->inController('\n');
		strcpyTab(currentTab->out+currentTab->current,"horacio:>",tabs[focus]);
		tabs[focus]->offsetCurrent = tabs[focus]->current + 1;
		updateRadius(currentTab, RADIUS);
		//printString(tabs[focus]->out,tabs[focus]);
		//printString("\n",tabs[focus]);
		tabs[focus]->inIndex=0;
		updateTab(currentTab);
	}

	return 0;
}

void runGenerico(char * in,char * out){
	return;
}


void genericInController(int c, tabStruct * tab){
	int width=tab->currentScreen.xf - tab->currentScreen.xi;
	int height=tab->currentScreen.yf - tab->currentScreen.yi;
	int lettersPerLine = width/tab->px;
	int linesInScreen = height/(2*tab->px);
	int lettersInThisLine =  tab->current-tab->lines[tab->currentLine%LINES_LENGTH];
	if(c==8){
		if(tab->inIndex>0)
			tab->inIndex--;
		if(tab->offsetCurrent<=tab->current){
			tab->current--;
			if(tab->current<=tab->lines[tab->currentLine%LINES_LENGTH]) tab->currentLine--;
		}
	}else if(c=='\n'){
		tab->lines[++tab->currentLine%LINES_LENGTH] = tab->current+1;
		if(tab->currentLine >= linesInScreen-10) tab->lineOffset++;
	}else{
		if(lettersInThisLine>=lettersPerLine){
			tab->lines[++tab->currentLine%LINES_LENGTH] = tab->current+1;
			if(tab->currentLine >= linesInScreen-10) tab->lineOffset++;
		}
		tab->in[tab->inIndex++] = c;
	} 
		
	if(c!=0 && c!=8)tab->out[tab->current++] = c;
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

