/*************************************************************************
	> File Name: sort.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年07月10日 星期二 17时56分56秒
 ************************************************************************/

#include<iostream>
#include<cstdlib>
using namespace std;

#define MAXSIZE 9

typedef struct 
{
    int r[MAXSIZE + 1]; //用于存储要排序的数组,r[0]用作哨兵或临时变量
    int length;   //用于记录顺序表的长度
}SqList; 

//交换L中数组r的下标为i和j的值
void swap(SqList *L, int i, int j)
{
    int temp = L->r[i];
    L->r[i] = L->r[j];
    L->r[j] = temp;
}

void print(SqList *L)
{
    if(NULL == L)
    {
        return;
    }

    for(int i = 0; i <= L->length; ++i)
    {
        cout << L->r[i] << " ";
    }
    cout << endl;
}

//冒泡排序
void bubbleSort1(SqList *L)
{
    int i,j;
    for(i = 1; i < L->length; ++i)
    {
        for(j = L->length - 1; j >= i; --j) 
        {
            if(L->r[j] > L->r[j+1])
            {
                swap(L, j, j+1);
            }
        }
    }
}

void bubbleSort2(SqList *L)
{
    int i, j;
    bool flag = true; //标记后面元素时候已经有序
    for(i = 1; i < L->length && flag; ++i)
    {
        flag = false;
        for(j = L->length - 1; j >= i; --j)
        {
            if(L->r[j] > L->r[j + 1])
            {
                swap(L, j, j+1);
                flag = true;
            }
        }
    }
}

//选择排序
void selectSort(SqList *L)
{
    int i,j, min;
    for(i = 1; i < L->length; ++i)
    {
        min = i;
        for(j = i + 1; j <= L->length; ++j)
        {
            if(L->r[min] > L->r[j])
            {
                min = j; //找到最小下标
            }
        }

        if(i != min)
        {
            swap(L, i, min);
        }
    }
}

//插入排序
void insertSort(SqList *L)
{
    int i, j;
    for(i = 2; i <= L->length; ++i)
    {
        if(L->r[i] < L->r[i - 1])
        {
            L->r[0] = L->r[i]; //设置哨兵
            for(j = i-1; L->r[j] > L->r[0]; --j)
            {
                L->r[j+1] = L->r[j]; //记录后移
            }

            L->r[j + 1] = L->r[0]; //插入到正确位置
        }
    }
}

//希尔排序
//基本思想是将原来的序列分成若干子序列，每个子序列采用插入排序
void shellSort(SqList *L)
{
    int i, j;
    int increment = L->length;
    do
    {
        increment = increment / 3 + 1;
        for(i = increment + 1; i <= L->length; ++i)
        {
            if(L->r[i] < L->r[i - increment])
            {
                L->r[0] = L->r[i];
                for(j = i-increment; L->r[j] > L->r[0]; j -= increment)
                {
                    L->r[j+increment] = L->r[j]; //记录后移,查找插入位置
                }

                L->r[j + increment] = L->r[0];
            }
        }
    }while(increment > 1);
}

//堆调整
void heapAdjust(SqList *L, int s, int m)
{
    int temp, j;
    temp = L->r[s];
    //根据完全二叉树的特性，当前节点序号是s,若有左右孩子,其序号一定为2s和2s+1
    for(j = 2*s; j <= m; j *= 2)
    {
        if(j < m && L->r[j] < L->r[j+1]) //寻找较大的
        {
            ++j;
        }

        if(temp >= L->r[j])
            break;

        L->r[s] = L->r[j];
        s = j;
    }

    L->r[s] = temp;
}

//堆排序
void heapSort(SqList *L)
{
    int i;
    //基于二叉树的性质,最后一个非叶子节点为length/2
    for(i = L->length / 2; i > 0; --i)
    {
        heapAdjust(L, i, L->length);
    }

    for(i = L->length; i > 1; --i)
    {
        swap(L, 1, i); //将堆顶记录与最后一个记录交换
        heapAdjust(L, 1, i-1);
    }
}

//归并排序(递归实现)
//将有序的SR[i...m]和SR[m+1..n]归并为有序的TR[i...n]
void Merge(int SR[], int TR[], int i, int m, int n)
{
    int j, k, l;
    for(j = m + 1, k = i; i <= m && j <= n; ++k)
    {
        if(SR[i] < SR[j])
            TR[k] = SR[i++];
        else 
            TR[k] = SR[j++];
    }

    if(i <= m)
    {
        for(l = 0; l <= m-i; ++l) //将剩余的SR复制到TR
        {
            TR[k+l] = SR[i+l];
        }
    }

    if(j <= n)
    {
        for(l = 0; l <= n-j; ++l)
        {
            TR[k+l] = SR[j+l];
        }
    }
}

void MSort(int SR[], int TR1[], int s,int t)
{
    int m;
    int TR2[MAXSIZE + 1];
    if(s == t)
    {
        TR1[s] = SR[s];
    }else {
        m = (s + t) / 2;
        MSort(SR,TR2, s, m);
        MSort(SR,TR2, m+1, t);
        Merge(TR2, TR1, s, m, t);
    }
}

void MergeSort(SqList *L)
{
    MSort(L->r, L->r, 1, L->length);
}

//归并排序(非递归实现)
//将SR[]中相邻长度为s的子序列两两归并到TR[]
void MergePass(int SR[], int TR[], int s, int n)
{
    int i = 1;
    int j;
    while(i <= n - 2 * s + 1)
    {
        Merge(SR,TR, i, i + s - 1, i + 2 * s - 1); //两两归并
        i = i + 2 * s;
    }

    if(i < n - s + 1)
    {
        Merge(SR, TR, i, i + s - 1, n);
    }else {
        for(j = i; j <= n; ++j)
        {
            TR[j] = SR[j];
        }
    }
}

void MergeSort2(SqList *L)
{
    int *TR = (int*)malloc(L->length * sizeof(int));//申请空间
    int k = 1;
    while(k < L->length)
    {
        MergePass(L->r, TR, k, L->length);
        k = 2 * k;
        MergePass(TR, L->r, k, L->length);
        k = 2 * k;
    }
}

//快速排序
int partition(SqList *L, int low, int high)
{
    int pivotkey;
    pivotkey = L->r[low];
    while(low < high)
    {
        while(low < high && L->r[high] >= pivotkey)
            --high;
        swap(L, low, high);

        while(low < high && L->r[low] <= pivotkey)
            ++low;
        swap(L, low, high);
    }

    return low;
}

void QSort(SqList *L, int low, int high)
{
    int pivot;
    if(low < high)
    {
        pivot = partition(L, low, high);
        QSort(L, low, pivot - 1);
        QSort(L, pivot + 1, high);
    }
}

void quickSort(SqList *L)
{
    QSort(L, 1, L->length);
}

int main(int argc, char** argv)
{
    SqList L;
    L.length = 9;
    L.r[0] = 0;
    L.r[1] = 3;
    L.r[2] = 5;
    L.r[3] = 2;
    L.r[4] = 7;
    L.r[5] = 6;
    L.r[6] = 9;
    L.r[7] = 1;
    L.r[8] = 8;
    L.r[9] = 4;

    //bubbleSort1(&L);
    //bubbleSort2(&L);
    //selectSort(&L);
    //insertSort(&L);
    //shellSort(&L);
    //heapSort(&L);
    //MergeSort(&L);
    //MergeSort2(&L);
    quickSort(&L);
    print(&L);
    return 0;
}
