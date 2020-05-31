#ifndef _SETJMP_H_
#define _SETJMP_H_

#include <stdint.h>


typedef struct registerEnv{
	uint64_t r15;
    uint64_t r14;
	uint64_t r13;
	uint64_t r12;
	uint64_t rbp;
	uint64_t rbx;
	uint64_t flags;
	uint64_t rsp;
    uint64_t rip;
}registerEnv;

void longJmp(registerEnv * env, int value);
int setJmp(registerEnv * env);




#endif