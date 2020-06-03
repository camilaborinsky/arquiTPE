#include<stdint.h>
#include<syscalls.h>


int strcpy(char * dest, char * src){
    int i =0;
    while(src[i]!=0){
        dest[i] = src[i++];
    }
    dest[i]=0;
    return i;

}

int getChar(){
    int character;
    int count = 0;
    while(count!=1){
        sys_readKeyboard(&character,1,&count);
        hlt();
    }
    return character;
}

int intToString(int num, char * buffer)
{
    char stack[11];
    int c = 0;
    int i=0;
    if(num==0) stack[i++]='0';
    while(num!=0){
        stack[i]=num%10+'0';
        num = num/10;
        i++;
    }
    c=i;
    i--;
    while(i>=0){
        *buffer=stack[i];
        buffer++;
        i--;
    }
    *buffer=0;
    return c;
}

void printNum(uint64_t num){
    int width=1000;
    int px=12;
    int lettersPerLine = width/px; //cambiar a syscall getResolution
    static int current;
    char buffer[10];
    int c = intToString(num,buffer);
    buffer[c]=' ';
    buffer[c+1]=0;
    for(int i=0;buffer[i]!=0;i++){
         int x_offset = px*(current%lettersPerLine);
        int y_offset = (2*px)*(current/lettersPerLine);
        sys_drawCharacter(x_offset,y_offset,px,buffer[i]);
        current++;
    }
    
}
