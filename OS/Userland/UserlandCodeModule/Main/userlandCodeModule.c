#include <syscalls.h>
#include <stdint.h>
#include <setJmp.h>

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

// divisionByZeroHandler(){
// 	longjmp(1);
// }

// invalidOpcodeHandler(){
// 	longjmp(7);
// }

int main() {

	int focus=0;
	registerEnv env;
	int i = setJmp(&env);

	sys_drawCharacter(0,0, 41, i%10+'0');
	longJmp(&env, 2);
	// setHandler(0,divisionByZeroHandler());
	// setHandler(6,invalidOpcodeHandler());
	// int entry=setjmp()-1;
	// if(entry == 0){
	// 	if(focus==0) leftDivisionByZeroHandler();
	// 	else rightDivisionByZeroHandler();
	// } else if(entry == 6){
	// 	if(focus==0) leftInvalidOpcodeHandler();
	// 	else rightInvalidOpcodeHandler();
	// }

	//NORMAL RUN
	
	return 0;
}
