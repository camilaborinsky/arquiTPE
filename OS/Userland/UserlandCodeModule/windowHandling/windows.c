#include <windows.h>
#include <stdlib.h>
#include <syscalls.h>


void clearTab(tabStruct * tab){
    return;
}

void updateTab(tabStruct * tab){
    clearTab(tab);
    tab->out[tab->current+1]=0;
    printString(tab->out,tab);
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
            tab->offsetCurrent=tab->current+1;
        }
        else{
            int x_offset = tab->currentScreen.xi + px * ((current) % lettersPerLine);
            int y_offset = tab->currentScreen.yi + (2 * px) * ((current)/ lettersPerLine);
            sys_drawCharacter(x_offset, y_offset, px, string[i]);
            current++;
        }
    }
}