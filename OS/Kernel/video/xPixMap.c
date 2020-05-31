#include "xPixMap.h"


void printString(char * string){
    int width=1000;
    int px=12;
    int lettersPerLine = width/px; //cambiar a syscall getResolution
    static int current;
    for(int i=0;string[i]!=0;i++){
         int x_offset = px*(current%lettersPerLine);
        int y_offset = (2*px)*(current/lettersPerLine);
        drawCharacter(x_offset,y_offset,px,string[i]);
        current++;
    }
    
}
void printNum(int);
void split(char * string, char buffer[4][5], char splitter){
    char index = 0;
    char actual=0;
    while(*string!=0){
        if(*string==splitter){
            buffer[actual][index]=0;
            actual++;
            index=0;
        }
        else
            buffer[actual][index++]=*string;
        string++;
    }
   
}

unsigned int atoi(char * string){
    unsigned int num=0;
    while(*string!=0){
        num=num*10+(*string -'0');
        string++;
    } 
    return num;
}

unsigned char hexToInt(char * hex ){
    uint8_t n1,n2;
    if(hex[0] >= 'A') n1=hex[0]-'A'+10;
    else n1=hex[0] - '0';
    if(hex[0] >= 'A') n2=hex[0]-'A'+10;
    else n2=hex[0] - '0';
    return ((n1<<4)&0xf0) | ((n2&0xf0));
}

void stringToColor(char * string, colorStruct * color){
    unsigned char * colors = color;
    unsigned char aux=0;

    color->red = hexToInt(string);
    color->green = hexToInt(string+2);
    color->blue = hexToInt(string+4);

    // for(int i=0;i<6;i++){
    //     if(string[i] >= 'A') aux=string[i]-'A'+10;
    //     else aux=string[i] - '0';
    //     if(i%2==0)colors[i%2]=aux<<4;
    //     else colors[i%2]=aux;
    // }
}



void printNum(int);
void loadPixelMap(infoPixelMap * info, char * pixmap[]){
    char valuesBuffer[4][5];
    //printString(pixmap[0]);
    split(*pixmap++,valuesBuffer,' ');
    //printString(valuesBuffer[0]);
    info->values.width=atoi(valuesBuffer[0]);
    info->values.height=atoi(valuesBuffer[1]);
    info->values.colors=atoi(valuesBuffer[2]);
    for(int i=0; i<info->values.colors;i++){
        char * data=*pixmap++;
        info->colors.chars[i]=data[0];
        stringToColor(data+5,&(info->colors.colors[i]));
    }  
    info->pixmap=pixmap;
}

colorStruct getColor(int x, int y, infoPixelMap * pixelmap){
    char ** pixmap=pixelmap->pixmap;
    char c = pixmap[y][x];
    int i=0;
    while(c!=pixelmap->colors.chars[i]) i++;
    return pixelmap->colors.colors[i];

    
}
