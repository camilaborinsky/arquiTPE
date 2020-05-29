#include <syscalls.h>

int main() {
	sys_drawCharacter(0,0,10,'a');
	sys_drawCharacter(11,0,20,'a');
	sys_drawCharacter(22,0,30,'a');
	sys_drawCharacter(51,0,40,'a');
	return 0;
}
