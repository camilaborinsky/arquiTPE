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

tabStruct tab0 = {evaluator,inControllerTab0,0,{0},{0},0,12,{3,3,497,997},0,0,0,0,{0}};
tabStruct tab1 = {runGenerico,inControllerTab1,0,{0},{0},0,12,{510,3,997,997},0,0,0,0,{0}};

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
		updateTab(tabs[i]);
	}

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
			updateTab(tabs[focus]);	
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
		updateTab(currentTab);
		//printString(tabs[focus]->out,tabs[focus]);
		//printString("\n",tabs[focus]);
		tabs[focus]->inIndex=0;
	}

	return 0;
}

void runGenerico(char * in,char * out){
	return;
}


void inControllerTab1(int c){

	int width=tab1.currentScreen.xf - tab1.currentScreen.xi;
	int lettersPerLine = width / tab1.px;
	int lettersInThisLine =  tab1.current-tab1.lines[tab1.currentLine];
	if(c==8){
		if(tab1.inIndex>0)
			tab1.inIndex--;
		if(tab1.offsetCurrent<=tab1.current){
			tab1.current--;
			if(tab1.current<=tab1.lines[tab1.currentLine]) tab1.currentLine--;
		}
	}else if(c=='\n'){
		tab1.lines[tab1.currentLine++] = tab1.current+1;
	}else{
		if(lettersInThisLine>=lettersPerLine) tab1.lines[tab1.currentLine++] = tab1.current+1;
		tab1.in[tab1.inIndex++] = c;
	} 
		
	// char str[2];
	// str[0] = c;
	// str[1] = 0; 
	//if(c!=0)printString(str,tabs[0]);
	if(c!=0 && c!=8)tab1.out[tab1.current++] = c;
	
}

void inControllerTab0(int c){

	int width=tab0.currentScreen.xf - tab0.currentScreen.xi;
	int lettersPerLine = width/tab0.px;
	int lettersInThisLine =  tab0.current-tab0.lines[tab0.currentLine];
	if(c==8){
		if(tab0.inIndex>0)
			tab0.inIndex--;
		if(tab0.offsetCurrent<=tab0.current){
			tab0.current--;
			if(tab0.current<=tab0.lines[tab0.currentLine]) tab0.currentLine--;
		}
	}else if(c=='\n'){
		tab0.lines[++tab0.currentLine] = tab0.current+1;
	}else{
		if(lettersInThisLine>=lettersPerLine) tab0.lines[++tab0.currentLine] = tab0.current+1;
		tab0.in[tab0.inIndex++] = c;
	} 
		
	// char str[2];
	// str[0] = c;
	// str[1] = 0; 
	//if(c!=0)printString(str,tabs[0]);
	if(c!=0 && c!=8)tab0.out[tab0.current++] = c;
	
}

void divisionByZeroHandler(){
	longjmp(&env,1);
}

void invalidOpcodeHandler(){
	longjmp(&env,7);
}

