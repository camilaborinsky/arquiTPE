#ifndef SYS_INFO_H
#define SYS_INFO_H

void cpuid(char * out, int argc,char * args[]);
void localtime(char * out, int argc, char * args[]);
void cputemp(char * out, int argc, char * args[]);

#endif