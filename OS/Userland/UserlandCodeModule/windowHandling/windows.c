#include <windows.h>
#include <stdlib.h>
#include <syscalls.h>

void printString(char *string, tabStruct *tab)
{
    int width = tab->currentScreen.xf - tab->currentScreen.xi;
    int px = tab->px;
    int lettersPerLine = width / px; //cambiar a syscall getResolution
    for (int i = 0; string[i] != 0; i++){
        if (string[i] == 8){
            if(tab->current != 0){
                string[i] = 32;
                tab->current--;
                int x_offset = tab->currentScreen.xi + px * ((tab->current) % lettersPerLine);
                int y_offset = tab->currentScreen.yi + (2 * px) * ((tab->current) / lettersPerLine);
                sys_drawCharacter(x_offset, y_offset, px, string[i]);
            }
        }
        else{
            int x_offset = tab->currentScreen.xi + px * ((tab->current) % lettersPerLine);
            int y_offset = tab->currentScreen.yi + (2 * px) * ((tab->current) / lettersPerLine);
            sys_drawCharacter(x_offset, y_offset, px, string[i]);
            tab->current++;
        }
    }
}