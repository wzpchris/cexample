/*************************************************************************
	> File Name: bst.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年07月11日 星期三 10时56分28秒
 ************************************************************************/

//二叉排序树基本操作
#include<iostream>
#include<cstdio>
#include <cstdlib>
using namespace std;

typedef struct _BitNode
{
    int data;
    struct _BitNode *lchild, *rchild;
}BitNode, *BiTree;

bool searchBST(BiTree T, int key, BiTree pre, BiTree &n)
{
    if(!T) //树为空
    {
        n = pre;
        return false;
    }else if(key == T->data)
    {
        n = T; //找到了直接返回
        return true;
    }

    if(key < T->data)
    {
        searchBST(T->lchild, key, T, n); //去左子树找
    }else 
    {
        searchBST(T->rchild, key, T, n); //去右子树找
    }
}

bool insertBST(BiTree &T, int k)
{
    BitNode *p; 
    if(!searchBST(T, k, NULL, p))
    {
        BitNode *temp = new BitNode;
        temp->data = k;
        temp->lchild = temp->rchild = NULL;
        if(!p) //树为空的
        {
            T = temp;
        }else{
            if(k < p->data) //如果不为空,加入的k就会p比较
            {
                p->lchild = temp;
            }else {
                p->rchild = temp;
            }
        }
        return true;
    }

    return false;
}

bool deleteElement(BiTree &T, int key)
{
    if(!T) //树为空的
    {
        return false;
    }

    if(T->data == key)
    {
        BitNode *s, *p;
        if(T->rchild == NULL)
        {
            s = T;
            T = T->lchild;
            free(s);
        }else if(T->lchild == NULL)
        {
            s = T;
            T = T->rchild;
            free(s);
        }else{
            p = T;
            s = T->rchild;
            while(s->lchild)
            {
                p = s; //找到要删除的节点
                s = s->lchild;
            }

            T->data = s->data;
            if(p != T)
            {
                p->lchild = NULL;
            }else{
                p->rchild = NULL;
            }

            free(s);
        }

        return true;
    }else if(key < T->data)
    {
        deleteElement(T->lchild, key); //去左子树根比较
    }else{
        deleteElement(T->rchild, key); //去右子树根比较
    }

    return false;
}

//中序遍历并输出元素
void inorderReverse(BiTree T)
{
    if(T)
    {
        inorderReverse(T->lchild);
        cout << T->data << " ";
        inorderReverse(T->rchild);
    }
}

int main()
{
    BiTree tree = NULL;
    int a[] = {60,86,50,40,35,74,51,100,37,90};
    for(int i = 0; i < 10; ++i)
    {
        insertBST(tree, a[i]);
    }

    inorderReverse(tree);
    cout << endl;
    cout << "Tree Root=" << tree->data << endl;
    cout << "===============" << endl;
    deleteElement(tree, 60);
    inorderReverse(tree);
    cout << endl;
    cout << "Tree Root=" << tree->data << endl;
    return 0;
}
