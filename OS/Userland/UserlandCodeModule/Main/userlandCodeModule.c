#include <syscalls.h>

int main() {
	int scale=1;
	int offset=0;
	while(scale<43){
		sys_drawCharacter(offset+=scale,0,scale+=1,'a');
	}
	return 0;
}
