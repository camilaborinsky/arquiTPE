#include<stdint.h>
#include<syscalls.h>
#include<stdlib.h>

int intToBase(int num, int base, char*buffer);

uint64_t atoi(char * string){
    uint64_t num=0;
    while(*string!=0){
        num=num*10+(*string -'0');
        string++;
    } 
    return num;
}

double stringToDouble(char *init, char *end){
    double res = 0;
    char comma = 0;
    double exp = 1.0f / 10;
    while (init < end)
    {

        if (*init == '.' || *init == ',')
        {
            comma = 1;
        }
        else if (comma)
        {
            res += (*init - '0') * exp;
            exp = exp / 10;
        }
        else
        {
            res = res * 10 + (*init - '0');
        }
        init++;
    }
    return res;
}

int doubleToString(double value, char * buffer){
	int precision=1000000000;
    int c=0;
    if(value<0){
        value=-value;
        buffer[c++]='-';
    }
	long m=value;
    if(m<0) m=-m;
	double p = value-m;
	long r=(int)(p*precision+0.00001f);
    if(r<0)r=-r;
	c += intToString(m,buffer+c);
	buffer[c++]='.';
	int aux=r;
	while(r!=0 && 10*aux/precision<1){
		buffer[c++]='0';
		aux*=10;
	}
	
	
	
	
	intToString(r,buffer+c++);
    buffer[c]=0;
    return c;
}


int intToHex(int num, char * buffer){
    return intToBase(num,16,buffer);
}

int intToBase(int num, int base, char*buffer){
    char stack[11];
    int c = 0;
    int i=0;
    int remainder = 0;
    if(num==0) stack[i++]='0';
    while(num!=0){
        remainder = num % base;
        stack[i]=remainder>=10? remainder+'A'-10:remainder+'0';
        num = num/base;
        i++;
    }
    c=i;
    i--;
    while(i>=0){
        *buffer=stack[i];
        buffer++;
        i--;
    }
    *buffer=0;
    return c;
}

int strcpy(char * dest, char * src){
    unsigned char i =0;
    while(src[i]!=0){
        dest[i] = src[i];
        i++;
    }
    dest[i]=0;
    return i;

}

int strcmp(char * str1, char * str2){
    int i =0;
    while(str1[i] != 0 && str2[i] != 0 ){
        if(str1[i] != str2[i]){
            return str1[i]-str2[i];
        }
        i++;
    }
    return str1[i]-str2[i];
}

void deleteChar(char * str, char c){
    int i=0,j=0;
    while(str[i]!= 0){
        if(str[i] != c){ 
            str[j++]=str[i];
        }
        i++;
    }
    str[j]=0;
}

int getChar(){
    unsigned char character;
    int count = 0;
    while(count!=1){
        sys_readKeyboard((char *)&character,1,&count);
        hlt();
    }
    return count<0?-1:(int)character;
}

int intToString(int num, char * buffer)
{
    return intToBase(num,10,buffer);
}

void printNum(uint64_t num){
    int width=1000;
    int px=12;
    int lettersPerLine = width/px; //cambiar a syscall getResolution
    static int current;
    char buffer[10];
    int c = intToString(num,buffer);
    buffer[c]=' ';
    buffer[c+1]=0;
    for(int i=0;buffer[i]!=0;i++){
         int x_offset = px*(current%lettersPerLine);
        int y_offset = (2*px)*(current/lettersPerLine);
        sys_drawCharacter(x_offset,y_offset,px,buffer[i]);
        current++;
    }
    
}
