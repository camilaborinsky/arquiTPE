#include <windows.h>
#include <stdlib.h>
#include <syscalls.h>


int strcpyTab(char * dest, char * src, tabStruct * tab){
    int i =0;
    while(src[i]!=0){
        tab->inController(src[i++]);
        updateRadius(tab,1);
    }
    return i;
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
    int width = tab->currentScreen.xf - tab->currentScreen.xi;
    int height = tab->currentScreen.yf - tab->currentScreen.yi;
    int px = tab->px;
    int lettersPerLine = width / px; //cambiar a syscall getResolution
    int linesInScreen = height/(2*px);
    clearFromXtoY(0,linesInScreen*lettersPerLine+1,tab);
    tab->out[tab->current]=0;
    printString(0,tab->out+tab->lines[tab->lineOffset%LINES_LENGTH],tab);
}

//borra/blanquea los contenidos de los pixeles que ocupan el caracter actual y los que estan a radius de distancia
void updateRadius(tabStruct * tab, int radius){
    int width = tab->currentScreen.xf - tab->currentScreen.xi;
    int px = tab->px;
    int lettersPerLine = width / px;
    int currentLine = tab->currentLine - tab->lineOffset;
    int pos = currentLine*lettersPerLine + tab->current - tab->lines[tab->currentLine%LINES_LENGTH];
    clearFromXtoY(pos-radius,pos+radius,tab);
    tab->out[tab->current]=0;
    printString(currentLine*lettersPerLine,tab->out+tab->lines[tab->currentLine%LINES_LENGTH],tab);
}


void printString(int start, char *string, tabStruct *tab)
{
    int width = tab->currentScreen.xf - tab->currentScreen.xi;
    int px = tab->px;
    int lettersPerLine = width / px; //cambiar a syscall getResolution
    int current=start;
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