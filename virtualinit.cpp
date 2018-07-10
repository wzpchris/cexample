/*************************************************************************
	> File Name: virtualinit.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月09日 星期六 17时35分40秒
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

class A {
public:
    A() { cout << "A construct" << endl; }
    ~A() { cout << "A deconstruct" << endl; }
    virtual void func1() { cout << "A::func1" << endl; }
    void func2() { cout << "A::func2" << endl; }
    int data1;
    static int data2;
};

int A::data2 = 1;

int main(int argc, char** argv)
{
    A *p = (A*)malloc(sizeof(A)); //注意这里是调用malloc函数，只负责分配内存，还没有对虚函数表指针进行初始化
    p->func1();
    return 0;
}
