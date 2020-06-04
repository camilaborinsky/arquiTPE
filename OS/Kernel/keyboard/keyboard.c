#include<keyboard.h>
#include <video.h>

#define BUFFER_SIZE 32
 
static char buffer[BUFFER_SIZE];
static int i=0;
static int base=0;
char shiftStatus=0;
char blockMayus=0;

static char asccode[][2] = { {0,0}, {0,0}, {'1', '!'}, {'2', '@'}, {'3', '#'},{'4', '$'},{'5','%'},{'6','^'},{'7','&'},{'8','*'},{'9','('},{'0',')'},{'-','_'},{'-','+'},{'\b', '\b'},{'\t','\t'},
					  {'q','Q'}, {'w','W'}, {'e','E'},{'r','R'},{'t','T'},{'y','Y'},{'u','U'},{'i','I'},{'o','O'},{'p','P'},{'[','{'},{']','}'},
					  {'\n','\n'},{0,0},{'a','A'},{'s','S'},{'d','D'},{'f','F'},{'g','G'},{'h','H'},{'j','J'},{'k','K'},{'l','L'}, {';',':'},{'\'', '\"'},{'°','~'},{0,0},{'\\','|'},
					  {'z','Z'},{'x','X'},{'c','C'},{'v','V'},{'b','B'},{'n','N'},{'m','M'}, {',', '<'},{'.','>'},{'/','?'},{0,0},{0,0},{0,0},{' ',' '}};

void printNum(int); //borrar
void keyboard_handler(){
    unsigned char key = getKey();
	if(key==42) shiftStatus=1;
	else if(key==170) shiftStatus=0;
	else if(key==58) blockMayus=1-blockMayus;

    else if(key<58)buffer[(i++)%BUFFER_SIZE]= asccode[key][(shiftStatus | blockMayus) - (shiftStatus & blockMayus)];
	//printNum(asccode[key][0]); borrar
    
}

void readKeyboard(int * buf, int count, int * amount){
	int index;
	for(index = 0; index<(i-base) && index<count; index++){
		buf[index] = buffer[(base++)%BUFFER_SIZE];
	}
	//i-=index;
	*amount = index;
}