#include <syscalls.h>
#include "cami.xpm"

void printString(char * string){
    int width=1000;
    int px=12;
    int lettersPerLine = width/px; //cambiar a syscall getResolution
    static int current;
    for(int i=0;string[i]!=0;i++){
         int x_offset = px*(current%lettersPerLine);
        int y_offset = (2*px)*(current/lettersPerLine);
        sys_drawCharacter(x_offset,y_offset,px,string[i]);
        current++;
    }
    
}

int main() {

	printString(cami_xpm[0]);
	sys_drawBitmap(0,0,cami_xpm);


	return 0;
}
