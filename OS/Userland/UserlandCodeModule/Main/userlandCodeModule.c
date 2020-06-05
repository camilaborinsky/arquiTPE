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

void exGenericHandler(errorStruct * error);
void initTabs();

tabStruct tab0 = {evaluator,inControllerTab0,exGenericHandler,{0},{0},0,10,{3,3,(resX/2)-3,resY-3},0,0};
tabStruct tab1 = {shell,inControllerTab1,exGenericHandler,{0},{0},0,10,{(resX/2)+5,3,resX-3,resY-3},0,0};

tabStruct * tabs[]={&tab0,&tab1};

registerEnv env;
int main() {

	sys_drawBitmap(497,0,linea_vertical_color_xpm);
	sys_drawBitmap(0,0,linea_vertical_color_xpm);
	sys_drawBitmap(0,0,linea_horizontal_color_xmp);
	sys_drawBitmap(0,1000,linea_horizontal_color_xmp);
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
	if((c>='0' && c<='9') || c=='+' || c=='-' || c=='/' || c=='*' || c=='(' || c==')' || c==8)
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
	uint64_t * registers =&(error->registers);
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
