#include <stdint.h>
#include "fonts.h"

typedef struct color{
    uint8_t blue;
    uint8_t green;
    uint8_t red;

} color;


struct vbe_mode_info_structure{
    uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
    uint8_t window_a;			// deprecated
    uint8_t window_b;			// deprecated
    uint16_t granularity;		// deprecated; used while calculating bank numbers
    uint16_t window_size;
    uint16_t segment_a;
    uint16_t segment_b;
    uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
    uint16_t pitch;			// number of bytes per horizontal line
    uint16_t width;			// width in pixels
    uint16_t height;			// height in pixels
    uint8_t w_char;			// unused...
    uint8_t y_char;			// ...
    uint8_t planes;
    uint8_t bpp;			// bits per pixel in this mode
    uint8_t banks;			// deprecated; total number of banks in this mode
    uint8_t memory_model;
    uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
    uint8_t image_pages;
    uint8_t reserved0;

    uint8_t red_mask;
    uint8_t red_position;
    uint8_t green_mask;
    uint8_t green_position;
    uint8_t blue_mask;
    uint8_t blue_position;
    uint8_t reserved_mask;
    uint8_t reserved_position;
    uint8_t direct_color_attributes;

    uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
    uint32_t off_screen_mem_off;
    uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
    uint8_t reserved1[206];
} __attribute__((packed));

void setPixel(int x, int y, color c);
char getBit(unsigned char index,int x, int y);

struct vbe_mode_info_structure * screen_info = 0x5C00;
void writeChar(uint8_t letter, unsigned int x, unsigned int y, double scale){
    static current;
    color white = {255,255,255};
    color black = {0,0,0};
    int lettersPerLine = (screen_info->width/(scale*letter_width));
    int x_offset = x+scale*letter_width*(current%lettersPerLine);
    int y_offset = y+scale*letter_height*(current/lettersPerLine);
   for(int j = 0; j < letter_height*scale;j++){
			for(int i = 0; i < letter_width*scale;i++){
                setPixel(i+x_offset,j+y_offset,getBit(letter,i/scale,j/scale)?white:black);
	  		}
	    }
    current++;
}

void setPixel(int x, int y, color c){
    char * framebuffer =screen_info->framebuffer;
    int absolute=3*(x+y*screen_info->width);
    char * pixel = framebuffer+absolute;
    pixel[0]=c.blue;
    pixel[1]=c.green;
    pixel[2]=c.red;
    
}

char getBit(unsigned char index,int x, int y){
  	int absolute = x + y * letter_bytes*8;
  	int pos = absolute/8;
  	int bit = absolute%8;
  	return (bitmap[index-OFFSET][pos]>>(bit))&0x01;	
 }

