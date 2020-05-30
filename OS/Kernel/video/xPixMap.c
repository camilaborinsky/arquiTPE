#include "xPixMap.h"


void split(char * string, char ** buffer, char splitter){
    char * actual = buffer;
    char index = 0;
    while(*string!=0){
        if(*string==splitter){
            actual++;;
            index=0;
        }
        else
            actual[index++]=*string;
        string++;
    }
}

int atoi(char * string){
    int num=0;
    while(*string!=0) num=num*10+*string++;
    return num;
}

colorStruct stringToColor(char * string){
    colorStruct color;
    return color;
}

void loadPixelMap(infoPixelMap * info, char * pixmap[]){
    char valuesBuffer[4][4];
    split(*pixmap++,valuesBuffer,' ');
    info->values.width=atoi(valuesBuffer[0]);
    info->values.height=atoi(valuesBuffer[1]);
    info->values.colors=atoi(valuesBuffer[2]);
    for(int i=0; i<info->values.colors;i++){
        char * data=*pixmap++;
        info->colors.chars[i]=data[0];
        info->colors.colors[i]=stringToColor(data+5);
        data[0];
        
        


    }  
}

colorStruct getColor(int x, int y, infoPixelMap * pixelmap){
    char ** pixmap=pixelmap->pixmap;
    char c = pixmap[y][x];
    return getColor(0,0,pixelmap); //eliminar

    
}
