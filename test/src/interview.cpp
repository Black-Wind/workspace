#include "interview.h"
#include <stdio.h>

void interview(){

	int a=0x12345678;
	int b=0x56789abcd;
	char *p=(char*)&b;
	int *m=(int*)(p+1);
	printf("%x\n",*m);
}
