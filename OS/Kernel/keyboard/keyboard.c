#include<keyboard.h>
#include <video.h>
#include <registersArgs.h>

#define BUFFER_SIZE 32
 
static char buffer[BUFFER_SIZE];
static registerArgs registers;
static int i=0;
static int saveReg=0;
static int base=0;
char shiftLStatus=0;
char shiftRStatus=0;
char blockMayus=0;

static char asccode[][2] = { {0,0}, {0,0}, {'1', '!'}, {'2', '@'}, {'3', '#'},{'4', '$'},{'5','%'},{'6','^'},{'7','&'},{'8','*'},{'9','('},{'0',')'},{'-','_'},{'-','+'},{'\b', '\b'},{'\t','\t'},
					  {'q','Q'}, {'w','W'}, {'e','E'},{'r','R'},{'t','T'},{'y','Y'},{'u','U'},{'i','I'},{'o','O'},{'p','P'},{'[','{'},{']','}'},
					  {'\n','\n'},{0,0},{'a','A'},{'s','S'},{'d','D'},{'f','F'},{'g','G'},{'h','H'},{'j','J'},{'k','K'},{'l','L'}, {';',':'},{'\'', '\"'},{'°','~'},{0,0},{'\\','|'},
					  {'z','Z'},{'x','X'},{'c','C'},{'v','V'},{'b','B'},{'n','N'},{'m','M'}, {',', '<'},{'.','>'},{'/','?'},{0,0},{0,0},{0,0},{' ',' '}};




void keyboard_handler(registerArgs * regs){
    unsigned char key = getKey();
	if(key==SHIFT_L) shiftLStatus=1;
	else if(key==SHIFT_R) shiftRStatus=1;
	else if (key==SHIFT_R+RELEASED)shiftRStatus=0;
	else if(key==SHIFT_L+RELEASED) shiftLStatus=0;
	else if(key==BLOCK_MAYUS) blockMayus=1-blockMayus;
	else if(key==ALT_L) 1; //nada que hacer en ALT Left
	else if(key == CTRL_L){
		saveReg=1;
		cpyRegs(&registers,regs); // con ctrl izq
	}else if(key<58)buffer[(i++)%BUFFER_SIZE]= asccode[key][( shiftRStatus | shiftLStatus | blockMayus) - ((shiftLStatus | shiftRStatus) & blockMayus)];
    
}

void retrieveRegs(registerArgs * args, int * flag){
	if(!saveReg){
		*flag = 0;
		return;
	}
	*flag=1;
	cpyRegs(args,&registers);
}

void readKeyboard(int * buf, int count, int * amount){
	int index;
	for(index = 0; index<(i-base) && index<count; index++){
		buf[index] = buffer[(base++)%BUFFER_SIZE];
	}

	*amount = index;
}