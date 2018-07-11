/*************************************************************************
	> File Name: heapsort.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年07月11日 星期三 08时59分21秒
 ************************************************************************/

#include<iostream>
using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void print(int arr[], int len)
{
    for(int i = 0; i < len; ++i)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}

void heapAdjust(int arr[], int i, int n)
{
    int j = i * 2 + 1;
    while(j < n)
    {
        if(j + 1 < n && arr[j] > arr[j + 1]) //子节点中找较小的
        {
            ++j;
        }

        if(arr[i] < arr[j])
        {
            break;
        }

        swap(arr[i], arr[j]);
        i = j;
        j = i * 2 + 1;
    }
}

void makeHeap(int arr[], int n)
{
    int i = 0;
    for(i = n / 2 - 1; i >= 0; --i)
    {
        heapAdjust(arr, i, n);
    }

    cout << "make heap success" << endl;
    print(arr, n);
}

void heapSort(int arr[], int len)
{
    int i = 0;
    makeHeap(arr, len);
    for(i = len - 1; i >= 0; --i)
    {
        swap(arr[i], arr[0]);
        heapAdjust(arr, 0, i);
    }
}


int main(int argc, char** argv)
{
    int arr[] = {2,4,3,6,8,1,5,9,7};
    print(arr, 9);
    heapSort(arr, 9);
    print(arr, 9);
}
