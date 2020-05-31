
#ifndef X_PIX_MAP_H
#define X_PIX_MAP_H
#include<stdint.h>


typedef struct colorStruct{
    uint8_t red;
    uint8_t green;
    uint8_t blue;

} colorStruct;


//https://es.wikipedia.org/wiki/X_PixMap#XPM
typedef struct infoValues{
    unsigned int width;
    unsigned int height;
    int colors;
    int charsPerPix; // siempre 1 creo DESCOMENTAR
}infoValues;

typedef struct infoColors{
    char chars[16];
    colorStruct colors[16];
    
}infoColors;

typedef struct infoPixelMap
{
    infoValues values;
    infoColors colors;
    char * * pixmap;
} infoPixelMap;


void split(char * string, char buffer[4][5], char splitter);

void loadPixelMap(infoPixelMap * info, char * pixmap[]);

colorStruct getColor(int x, int y, infoPixelMap * pixelMap);

#endif;