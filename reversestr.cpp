/**
*这里的转换是将I am a student.转换为student. a am I
*/
#include <iostream>
#include <cstring>
using namespace std;

void reverseStr(char *str, int from, int to)
{
	if(str == NULL || from > to) return;

	char temp;
	while(from < to)
	{
		temp = str[from];
		str[from++] = str[to];
		str[to--] = temp;
	}
}

int main(int argc, char **argv)
{
	cout << "test" << endl;
	char str[128] = "I am a student.";
	cout << "before:" << str << ",len:" << strlen(str) << endl;
	reverseStr(str, 0, strlen(str) - 1);	
	cout << "1 after:" << str << endl;
	int k = 0;
	for(int i = 0; i < strlen(str); ++i)
	{
		if(str[i] == ' ')
		{
			reverseStr(str, k, i - 1);
			k = i + 1;
		}
	}

	cout << "2 after:" << str << endl;
}
