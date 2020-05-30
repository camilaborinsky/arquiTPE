#include <syscalls.h>
#include <stdint.h>

typedef struct registerArgs{
	uint64_t r15;
	uint64_t r14;
	uint64_t r13;
	uint64_t r12;
	uint64_t r11;
	uint64_t r10;
	uint64_t r9;
	uint64_t r8;
	uint64_t rsi;
	uint64_t rdi;
	uint64_t rbp;
	uint64_t rdx;
	uint64_t rcx;
	uint64_t rbx;
	uint64_t rax;
	uint64_t rip;
	uint64_t cs;
	uint64_t flags;
	uint64_t rsp;
	uint64_t ss;
}registerArgs;

typedef struct errorStruct{
	char errorCode;
	//char * errorMessage;
	uint64_t opcode;
	registerArgs registers;
}errorStruct;
int main() {
	// int scale=1;
	// int offset=0;
	// while(scale<43){
	// 	sys_drawCharacter(offset+=scale,0,scale+=1,'a');
	// }
	//sys_drawCharacter(0,0,41,'a');
	int a = 0;
	int b = 15/a;
	sys_drawCharacter(0,0,41,'l');
	errorStruct error;
	sys_drawCharacter(0,0,41,'l');
	sys_readErrors(&error);
	sys_drawCharacter(0,0,41,'n');
	//sys_drawCharacter(0,0,41,error.errorCode + '0');
	return 0;
}
