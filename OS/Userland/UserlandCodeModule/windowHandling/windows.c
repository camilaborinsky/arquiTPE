#include <windows.h>
#include <stdlib.h>
#include <syscalls.h>

void drawString( char *string, tabStruct *tab)
{   
    int height = tab->currentScreen.yf - tab->currentScreen.yi;
    int width = tab->currentScreen.xf - tab->currentScreen.xi;
    int px = tab->px;
    int lettersPerLine = width / px; //cambiar a syscall getResolution
    int totalLines = height/(2*px);
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
            if((tab->current) / lettersPerLine>=(totalLines-1)){
                sys_scroll(tab->currentScreen.xi, tab->currentScreen.yi, \
                            tab->currentScreen.xf, tab->currentScreen.yf, \
                            2 * px);
                tab->current-=lettersPerLine;
            }
        }
    }
}