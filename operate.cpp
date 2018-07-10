/*************************************************************************
	> File Name: operate.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月03日 星期日 22时55分55秒
 ************************************************************************/
//operate=不能被继承
#include<iostream>
using namespace std;

class A1
{
public:
    int operator=(int a)
    {
        return 8;
    }
    int operator+(int a)
    {
        return 9;
    }
};

class B1:public A1
{
public:
    int operator-(int a)
    {
        return 7;
    }
};

int main(int argc, char** argv)
{
    B1 v;
    cout << (v+2) << endl;
    cout << (v-2) << endl;
    cout << (v=2) << endl;
    return 0;
}
