#include <windows.h>
#include <stdlib.h>
#include <syscalls.h>


int strcpyTab(char * dest, char * src, tabStruct * tab){
    int i =0;
    while(src[i]!=0){
        tab->inController(src[i++]);
    }
    dest[i]=0;
    return i;
}

void clearTab(tabStruct * tab){
    int width = tab->currentScreen.xf - tab->currentScreen.xi;
    int px = tab->px;
    int lettersPerLine = width / px;
    clearFromXtoY(tab->currentLine*lettersPerLine,(tab->currentLine+1)*lettersPerLine,tab);
    return;
}


void clearFromXtoY(int x, int y, tabStruct * tab){
    int width = tab->currentScreen.xf - tab->currentScreen.xi;
    int px = tab->px;
    int lettersPerLine = width / px; //cambiar a syscall getResolution
    int current=x;
    for (int i = x; i<= y; i++){
        int x_offset = tab->currentScreen.xi + px * ((current) % lettersPerLine);
        int y_offset = tab->currentScreen.yi + (2 * px) * ((current)/ lettersPerLine);
        sys_drawCharacter(x_offset, y_offset, px, ' ');
        current++;
        
    }
}

void updateTab(tabStruct * tab){
    //clearTab(tab);
    tab->out[tab->current]=0;
    printNum(tab->currentLine);
    //printString(tab->out+tab->lines[tab->lineOffset],tab);
}


void printString(char *string, tabStruct *tab)
{
    int width = tab->currentScreen.xf - tab->currentScreen.xi;
    int px = tab->px;
    int lettersPerLine = width / px; //cambiar a syscall getResolution
    int current=0;
    for (int i = 0; string[i] != 0; i++){
        if(string[i]=='\n'){
            current+=lettersPerLine- current%lettersPerLine;
            //tab->offsetCurrent=tab->current+1;
        }
        else{
            int x_offset = tab->currentScreen.xi + px * ((current) % lettersPerLine);
            int y_offset = tab->currentScreen.yi + (2 * px) * ((current)/ lettersPerLine);
            sys_drawCharacter(x_offset, y_offset, px, string[i]);
            current++;
        }
    }
}