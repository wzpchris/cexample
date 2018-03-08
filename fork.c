#include <stdio.h>
#include<sys/types.h>
#include <unistd.h>

void test1(void) {
	int i;
	for(i = 0; i < 2; i++)
	{
		printf("i=%d, pid=%u -\n", i, getpid());
		fork();
	}
}

void test2(void) {
	fork();
	printf("hello");
	fork();
	printf("hello\n");
}

int main(void)
{
	//test2();
	int a = 0;
	int b = 1;
	printf("xxxxx %d", b / a);
	return 0;
}
