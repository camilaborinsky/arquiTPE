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
#define BORDER 3

void exGenericHandler(errorStruct * error);
void initTabs();

tabStruct tab0 = {evaluator,inControllerTab0,exGenericHandler,{0},{0},0,10,{10,10,resX/2-10,resY/2-10},0,0};
tabStruct tab1 = {shell,inControllerTab1,exGenericHandler,{0},{0},0,10,{resX/2-10,resY/2-10,resX-10,resY-10},0,0};

tabStruct * tabs[]={&tab0,&tab1};


colorStruct colorGrey={200,200,200},colorOrange={255,125,0},colorBlack={0,0,0};
rect tab0_border;
rect tab1_border;

rect * tab_borders[]={&tab0_border,&tab1_border};
registerEnv env;

void setupBorders(){
	tab0_border.xi = tab0.currentScreen.xi-3;
	tab0_border.xf = tab0.currentScreen.xf+3;
	tab0_border.yi = tab0.currentScreen.yi-3;
	tab0_border.yf = tab0.currentScreen.yf+5;
	tab0_border.fill=0;
	tab0_border.border=3;
	tab0_border.c = colorGrey;

	

	tab1_border.xi = tab1.currentScreen.xi-3;
	tab1_border.xf = tab1.currentScreen.xf+3;
	tab1_border.yi = tab1.currentScreen.yi-3;
	tab1_border.yf = tab1.currentScreen.yf+5;
	tab1_border.fill=0;
	tab1_border.border=3;
	tab1_border.c = colorGrey;

	tab_borders[focus]->c = colorOrange;
	sys_drawRect(&tab1_border);
	sys_drawRect(&tab0_border);
}

typedef struct moves{
	int up, down,left, right;
}moves;

void superpose(tabStruct * tab1, tabStruct * tab2, moves * m){
	int width1 = tab1->currentScreen.xf - tab1->currentScreen.xi;
	int width2 = tab2->currentScreen.xf - tab2->currentScreen.xi;
	int height1 = tab1->currentScreen.yf - tab1->currentScreen.yi;
	int height2 = tab2->currentScreen.yf - tab2->currentScreen.yi;

	m->left=0;
	m->right=0;
	m->up=0;
	m->down=0;

	int dx = tab1->currentScreen.xi-tab2->currentScreen.xf;
	if(dx>0 || -dx>width1+width2 ){
		m->left=1;
		m->right=1;
	}
	

}

int main() {
	setupBorders();
		
	int c=0;
	

	sys_setExceptionHandler(0,exGenericHandler); //esta parte siempre justo antes del while
	sys_setExceptionHandler(6,exGenericHandler);
	int entry=setjmp(&env)-1;
	if(entry == -1){
		initTabs();
	}

	while(1){
		while((c=getChar()) !='\n'){
			if(c=='\t'){
				tab_borders[focus]->c=colorGrey;
				sys_drawRect(tab_borders[focus]);
				focus = (focus+1)%NUM_TABS;
				tab_borders[focus]->c=colorOrange;
				sys_drawRect(tab_borders[focus]);

			}else if(c>=200 && c<=207){
				rect eraser ={
					tabs[focus]->currentScreen.xi,
					tabs[focus]->currentScreen.yi,
					tabs[focus]->currentScreen.xf,
					tabs[focus]->currentScreen.yf,
					1,
					0,
					colorBlack};
				sys_drawRect(&eraser);
				tab_borders[focus]->c=colorBlack;
				sys_drawRect(tab_borders[focus]);

				switch (c){
					case 200:  // para arriba
						tabs[focus]->currentScreen.yi-=10;
						tabs[focus]->currentScreen.yf-=10;
						break;
					case 201: // para abajo
						tabs[focus]->currentScreen.yi+=10;
						tabs[focus]->currentScreen.yf+=10;
					break;
					case 202: // para izquierda
						tabs[focus]->currentScreen.xi-=10;
						tabs[focus]->currentScreen.xf-=10;
					break;
					case 203: // para derecha
						tabs[focus]->currentScreen.xi+=10;
						tabs[focus]->currentScreen.xf+=10;
					break;
				case 204:  // agrandar vertical
					tabs[focus]->currentScreen.yi-=10;
					break;
				case 205: //  achicar vertical
					tabs[focus]->currentScreen.yi+=10;
					break;
				case 206: // agrandar horizontal
					tabs[focus]->currentScreen.xi-=10;
					break;
				case 207: // achicar horizontal
					tabs[focus]->currentScreen.xi+=10;
					break;
				
				}
				setupBorders();
				initTabs();
				
				sys_drawRect(tab_borders[focus]);

			}else{
				tabs[focus]->inController(c);
			}
		}

		tabStruct * currentTab = tabs[focus];
		//drawString("\n input:",currentTab);
		//drawString(currentTab->in,currentTab);
		drawString("\n",currentTab);
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

void initTabs(){
	//que arranquen las pantallas con username escrito
	for(int i=0;i<NUM_TABS;i++){
		tabs[i]->current=0;
		strcpy(tabs[i]->out+tabs[i]->current,"usr@coronavinux:>");
		drawString(tabs[i]->out,tabs[i]);
		tabs[i]->offsetCurrent = tabs[i]->current+1;
		tabs[i]->inIndex=0;

	}
}

void runGenerico(char * in,char * out){
	return;
}


void genericInController(int c, tabStruct * tab){
	
	if(c==128){
		while(tab->inIndex>0){
			genericInController(8,&tab0);
		}
	}
	else{
		if(c==8){
			if(tab->inIndex>0){
				tab->inIndex--;
				tab->in[tab->inIndex]=0;
			}
		}
		else{
			tab->in[tab->inIndex++] = c;
			tab->in[tab->inIndex]=0;
		}

		tab->out[0]=c;
		tab->out[1]=0;
		if(c!=0)drawString(tab->out,tab);	
	}
}

void inControllerTab1(int c){
	genericInController(c,&tab1);
	
}

void inControllerTab0(int c){

	if((c>='0' && c<='9') || c=='+' || c=='-' || c=='/' || c=='*' || c=='(' || c==')'|| c==8 || c==128)
		genericInController(c,&tab0);
	
}


void exGenericHandler(errorStruct * error){
	
	switch (error->errorCode)
	{
	case 0:
		drawString("Excepcion de division por cero \n",tabs[focus]);
		break;
	
	case 6:
		drawString("Excepcion de codigo de operacion invalido \n",tabs[focus]);
		break;
	}
	//inforeg(error->registers);

	char * registersNames[] = {"r15","r14","r13","r12","r11","r10","r9","r8","rsi","rdi",\
                            "rbp","rdx","rcx","rbx","rax","rsp","rip","cs","flags"};
	uint64_t * registers =(uint64_t *)&(error->registers);
	drawString("\n",tabs[focus]);
	int index=0;
    index=strcpy(tabs[focus]->out, "registros \n");
    
    for(int i = 0 ; i < 19 ; i++){

        index+=strcpy(tabs[focus]->out+index, registersNames[i]);
        index+=strcpy(tabs[focus]->out+index,"    ");
        index+=intToHex(registers[i], tabs[focus]->out+index);
        index+=strcpy(tabs[focus]->out+index,"\n");
    
    }	
	strcpy(tabs[focus]->out+index,"usr@coronavinux:>");
	drawString(tabs[focus]->out,tabs[focus]);
	tabs[focus]->offsetCurrent = tabs[focus]->current+1;
	tabs[focus]->inIndex=0;
	longjmp(&env,error->errorCode+1);

}
