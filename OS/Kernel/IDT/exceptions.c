
#include <stdint.h>
#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 6
#define ERROR_BUFFER_SIZE 10

static void zero_division(registerArgs * args);
static void invalid_opcode(registerArgs * args);

typedef struct errorStruct{
	char errorCode;
	//char * errorMessage;
	uint64_t opcode;
	registerArgs registers;
}errorStruct;

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


static errorStruct buffer[ERROR_BUFFER_SIZE];
static int errorIndex = -1;

//exception es el codigo que le corresponde al error
//args es una serie de parametros. args = {r15,...,r8,rsi,rdi,rbp,rdx,rcx,rbx,rax,rip,cs,flags,rsp,ss}
void exceptionDispatcher(int exception,uint64_t * args) {
	switch(exception){
		case ZERO_EXCEPTION_ID:
			zero_division(args);
			break;
		case INVALID_OPCODE_EXCEPTION_ID:
			invalid_opcode(args);
			break;
	}
}

//char * errorMessages[6] = {"Problema 1"," 2","3","4","5",};

static void zero_division(registerArgs * args) {
	// Handler para zero divisions
	
	errorStruct * error = buffer + (++errorIndex%ERROR_BUFFER_SIZE);
	error -> errorCode = ZERO_EXCEPTION_ID;
	error-> opcode = *((char *)args -> rip);
	error -> registers = *args; 

}

static void invalid_opcode(registerArgs * args){
	//Handler para manejar invalid 
	errorStruct * error = buffer + (++errorIndex%ERROR_BUFFER_SIZE);
	error -> errorCode = INVALID_OPCODE_EXCEPTION_ID;
	error-> opcode = *((char *)args -> rip);
	error -> registers = *args; 
}