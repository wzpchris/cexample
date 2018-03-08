#include <iostream>
using namespace std;

#pragma pack(2)
enum Color{
	red,
	green,
} e;
class A {
	int i;		//占4个字节,放在[0,3]的位置
	union U {
		char buff[13];
		int i;	
	} u;		//联合体中以最长字节为准,放在[4,16]的位置,自身长度为13,#pragme pack(2),去最小值2，按2字节对齐补齐，增加一个字节

	void foo() { } //不占字节
	typedef char* (*f)(void*); //不占字节
	enum {red, green, blue} color; //占4字节,放在[18,21]
};
#pragma unpack()

#pragma pack(4)
class TestB {
public:
	int aa; //占4个字节,按min(4,4)对齐,放在[0,3]
	char a;	//占1字节,按min(1,4)对齐,放在[4]
	short b;//占2字节,按min(2,4)对齐补齐,此时在a后会补齐一个字节，放在[6,7]
	char c;	//占1个字节,按min(1,4)对齐,放在[8],此时整个字节数为9
};
//整个类之间的对齐时按最大的数据成员与pack(N)的最小值进行的
//min(sizeof(int), 4),按4字节对应,整个字节为12
#pragma unpack()

#pragma pack(2)
class TestC {
public:
	int aa; //占4个字节,按min(4,2)对齐,放在[0,3]
	char a;	//占1字节,按min(1,2)对齐,放在[4]
	short b;//占2字节,按min(2,2)对齐补齐,此时在a后会补齐一个字节，放在[6,7]
	char c;	//占1个字节,按min(1,2)对齐,放在[8],此时整个字节数为9
};
//整个类之间的对齐时按最大的数据成员与pack(N)的最小值进行的
//min(sizeof(int), 2),按4字节对应,整个字节为10
#pragma unpack()

#pragma pack(4)
class TestD {
public:
	char a;	//占1字节，按min(1,4)对齐，放在[0]
	short b;//占2字节，按min(2,4)对齐,放在[2,3]
	char c;//占1字节,按min(1,4)对齐,放在[4]
};
//整个占5字节,按min(sizeof(short), 4) = 2对齐,后面再补一字节,整个类的大小为6字节
#pragma unpack()

int main(int argc, char **argv)
{
	cout << "sizeof enum = " << sizeof(e) << endl;
	cout << "sizeof A = " << sizeof(A) << endl;			//22
	cout << "sizeof TestB = " << sizeof(TestB) << endl;	//12
	cout << "sizeof TestC = " << sizeof(TestC) << endl; //10
	cout << "sizeof TestD = " << sizeof(TestD) << endl; //6
	TestD d;
	int e;
	cout << "&d = " << &d << endl;
	cout << "&d.a = " << (void*)&(d.a) << endl;
	cout << "&d.b = " << &d.b << endl;
	cout << "&d.c = " << (void*)&(d.c) << endl;
	cout << "&e = " << &e << endl;
	return 0;
}
