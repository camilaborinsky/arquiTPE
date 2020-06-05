#include <windows.h>
#include <stdlib.h>
#include <syscalls.h>


int height=0;
int width=0;
int px=12;
int lettersPerLine=0;
int totalLines;

int checkLines(char * string, tabStruct * tab){ // returns at which line this print should end
    int currentLineLength= (tab->current) % lettersPerLine;
    int currentLine = (tab->current) / lettersPerLine;
    while(*string!=0){
        if(*string=='\n' || currentLineLength>=lettersPerLine){
            currentLine++;
            currentLineLength=0;
        }
        string++;
    }
    return currentLine;
}

void drawString( char *string, tabStruct *tab)
{   
    height = tab->currentScreen.yf - tab->currentScreen.yi;
    width = tab->currentScreen.xf - tab->currentScreen.xi;
    px = tab->px;
    lettersPerLine = width / px; //cambiar a syscall getResolution
    totalLines = height/(2*px);
    int lastLine = checkLines(string,tab);
    
     if((tab->current) / lettersPerLine>=(totalLines-1)){
                sys_scroll(tab->currentScreen.xi, tab->currentScreen.yi, \
                            tab->currentScreen.xf, tab->currentScreen.yf, \
                            2 * px);
                tab->current-=lettersPerLine;
            }


    if(lastLine>=totalLines-1){
        sys_scroll(tab->currentScreen.xi, tab->currentScreen.yi, \
                    tab->currentScreen.xf, tab->currentScreen.yf, \
                    (2 * px)*(lastLine + 1 -totalLines));
        tab->current-=lettersPerLine*(lastLine + 1-totalLines);
    }


    for (int i = 0; string[i] != 0; i++){
        if (string[i] == 8){
            if(tab->current >= tab->offsetCurrent){
                string[i] = 32;
                tab->current--;
                int x_offset = tab->currentScreen.xi + px * ((tab->current) % lettersPerLine);
                int y_offset = tab->currentScreen.yi + (2 * px) * ((tab->current) / lettersPerLine);
                sys_drawCharacter(x_offset, y_offset, px, string[i]);
            }
        } else {
            if(string[i]=='\n'){
                tab->current+=lettersPerLine- tab->current%lettersPerLine;

            }
            else{
                int x_offset = tab->currentScreen.xi + px * ((tab->current) % lettersPerLine);
                int y_offset = tab->currentScreen.yi + (2 * px) * ((tab->current)/ lettersPerLine);
                sys_drawCharacter(x_offset, y_offset, px, string[i]);
                tab->current++;
            }
        }
    }
}