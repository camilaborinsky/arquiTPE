#include<stdint.h>
#include<video.h>
#include<keyboard.h>
#include<systemInfo.h>
#include<exceptions.h>
//void syscallsDispatcher(uint64_t id, uint64_t rdi, uint64_t rsi, ... ):

//void write(unsigned int fd, const char * buf, uint64_t count);
//void drawScreen(int x,int y, int figure, int scale);

//drawString(int x);


void syscallsDispatcher (uint64_t id, uint64_t * registers){
    switch (id)
    {
        case 0:
            readKeyboard((char *)registers[0], registers[1]);
            break;
        case 1:
            drawCharacter(registers[0],registers[1],registers[2],registers[3]);
            break;
        case 2:
            drawBitmap(registers[0], registers[1],(void *) registers[2]);
            break;
        case 3:
            cpuTemp((void *)registers[0]);
            break;
        case 4:
            readErrors((errorStruct *)registers[0]);
            break;
    }

}
//writeChar(buffer[i],0,0,0.25f);

/*void write(unsigned int fd, const char * buf, uint64_t count){
     
     char * dst = getBufferPointer(fd);
     for(int i=0;i<count;i++)
            dst[i]=buf[i];
     

        
     
}*/