/**
 *1.运行该程序，查看该程序的进程ID
 *2.cd /proc/xxx
 *3.cat maps 查看内存情况
 */	
#include <stdio.h>
#include <stdlib.h>
int i1;	//BSS段
int i2 = 10;//数据段
static int i3; //BSS段
static int i4 = 20; //数据段
const int i5 = 30; //代码段
static const int i6 = 40; //代码段
const static int ig = 100;	//代码段
int *pig11 = NULL;
int *pig13 = NULL;
	

void fa(int i7) {	//栈
	int i8;	//栈
	int i9 = 50; //栈
	static int i10; //BSS段
	static int i11 = 60; //数据段
	const int i12 = 70;	//栈
	static const int i13 = 80;	//代码段
	const static int il = 101;	//代码段
	char *str;	//
	char *str1 = "abcdef";	//代码段
	char str2[] = "abcdef";	//栈
	int *pi = malloc(sizeof(int));	//堆
	printf("&i7=%p\n", &i7);
	printf("&i8=%p\n", &i8);
	printf("&i9=%p\n", &i9);
	printf("&i10=%p\n", &i10);
	printf("&i11=%p\n", &i11);
	printf("&i12=%p\n", &i12);
	printf("&i13=%p\n", &i13);
	printf("&il =%p\n", &il);
	printf("str=%p\n", str);
	printf("str1=%p\n", str1);
	printf("str2=%p\n", str2);
	printf("pi=%p\n", pi);
	pig11 = &i11;
	pig13 = &i13;
}

int main(int argc, char **argv)
{
	printf("&i1=%p\n", &i1);
	printf("&i2=%p\n", &i2);
	printf("&i3=%p\n", &i3);
	printf("&i4=%p\n", &i4);
	printf("&i5=%p\n", &i5);
	printf("&i6=%p\n", &i6);
	printf("&ig=%p\n", &ig);
	fa(1);
	printf("pig11=%d\n", *pig11);
	printf("pig13=%d\n", *pig13);
	while(1);
}
