#include<keyboard.h>
#include <video.h>

static char buffer[32];
static int i=-1;
static char asccode[][2] = { {0,0}, {0,0}, {'1', '!'}, {'2', '@'}, {'3', '#'},{'4', '$'},{'5','%'},{'6','^'},{'7','&'},{'8','*'},{'9','('},{'0',')'},{'-','_'},{'-','+'},{'\b', '\b'},{'\t','\t'},
					  {'q','Q'}, {'w','W'}, {'e','E'},{'r','R'},{'t','T'},{'y','Y'},{'u','U'},{'i','I'},{'o','O'},{'p','P'},{'[','{'},{']','}'},
					  {'\n','\n'},{0,0},{'a','A'},{'s','S'},{'d','D'},{'f','F'},{'g','G'},{'h','H'},{'j','J'},{'k','K'},{'l','L'}, {';',':'},{'\'', '\"'},{'°','~'},{0,0},{'\\','|'},
					  {'z','Z'},{'x','X'},{'c','C'},{'v','V'},{'b','B'},{'n','N'},{'m','M'}, {',', '<'},{'.','>'},{'/','?'},{0,0},{0,0},{0,0},{' ',' '}};

void keyboard_handler(){
    unsigned char key = getKey();
    if(key<58)buffer[++i]= asccode[key][0];
    
}
void readKeyboard(char * buf, int count, int * amount){
	int index;
	for(index = 0; index<i && index<count;index++){
		buf[index] = buf[index];
	}
	i=0;
	*amount = index;
}