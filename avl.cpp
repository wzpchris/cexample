/*************************************************************************
	> File Name: avl.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年07月11日 星期三 12时24分55秒
 ************************************************************************/

#include<iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define EH 0
#define LH 1
#define RH -1
typedef struct _BitNode
{
    int data;
    int bf;  //平衡因子
    struct _BitNode *lchild, *rchild;
}BitNode, *BiTree;

//右旋操作
void R_Rotate(BiTree &T)
{
    BiTree p;
    p = T->lchild;
    T->lchild = p->rchild;
    p->rchild = T;
    T = p;
}

void L_Rotate(BiTree &T)
{
    BiTree p;
    p = T->rchild;
    T->rchild = p->lchild;
    p->lchild = T;
    T = p;
}

void RightBalance(BiTree &T)
{
    BiTree R, r1; //调用此函数时,以T为根的树,右边高于左边,则T->bf = RH
    R = T->rchild;
    switch(R->bf)
    {
        case RH: //如果T的右孩子和T它们的平衡因子符号相同，则直接左旋
            T->bf = R->bf = EH;
            L_Rotate(T);
            break;
        case EH:
            T->bf = RH;
            R->bf = LH;
            L_Rotate(T);
            break;
        case LH: //如果T的右孩子和T它们的平衡因子符号不同,需要先以T的右孩子为根右旋，在以T为根左旋
            r1 = R->lchild;
            switch(r1->bf)
            {
                case EH:
                    T->bf = R->bf = EH;
                    break;
                case RH:
                    R->bf = EH;
                    T->bf = LH;
                    break;
                case LH:
                    R->bf = RH;
                    T->bf = EH;
                    break;
                default:
                    break;
            }
            r1->bf = EH;
            R_Rotate(T->rchild); //先右旋
            L_Rotate(T);
            break;   
    }
}

void LeftBalance(BiTree &T)
{
    BiTree L, lr;
    L = T->lchild;
    switch(L->bf)
    {
        case EH:
            L->bf = RH;
            T->bf = LH;
            R_Rotate(T);
            break;
        case LH:
            L->bf = T->bf = EH;
            R_Rotate(T);
            break;
        case RH:
            lr = L->rchild;
            switch(lr->bf)
            {
                case EH:
                    L->bf = EH;
                    break;
                case RH:
                    T->bf = EH;
                    L->bf = LH;
                    break;
                case LH:
                    L->bf = EH;
                    T->bf = RH;
                    break;
            }
            lr->bf = EH;
            L_Rotate(T->lchild);
            R_Rotate(T);
            break;
        default:
            break;
    }
}

bool InsertAVLTree(BiTree &T, int key, bool &taller)
{
    if(!T)
    {
        T = new BitNode; //直接作为整棵树的根
        T->bf = EH;
        T->lchild = T->rchild = NULL;
        T->data = key;
        taller = true;
        return true;
    }else {
        if(key == T->data) //已有元素,不用插入了,返回false
        {
            taller = false;
            return false;
        }

        if(key < T->data) //所插元素小于此根的值,就找他的左孩子
        {
            if(!InsertAVLTree(T->lchild, key, taller))
            {
                return false;
            }

            if(taller) //树长高了
            {
                switch(T->bf)
                {
                    case EH:
                        T->bf = LH;
                        taller = true;
                        break;
                    case LH:
                        LeftBalance(T);
                        taller = false;
                        break;
                    case RH:
                        T->bf = EH;
                        taller = false;
                        break;
                    default:
                        break;
                }
            }
        }else{
            if(!InsertAVLTree(T->rchild, key, taller))
                return false;
            if(taller)
            {
                switch(T->bf)
                {
                    case EH:
                        T->bf = RH;
                        taller = true;
                        break;
                    case LH:
                        T->bf = EH;
                        taller = false;
                        break;
                    case RH:
                        RightBalance(T);
                        taller = false;
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

//树根,删除的元素,此树是否降低
bool DeleteElement(BiTree &T, int key, bool &lower)
{
    bool L, R; //删除的是左子树还是右子树,作为标志
    L = R = false;
    if(T == NULL)
    {
        return false;
    }

    if(key == T->data) //找到了所要删除的节点
    {
        BitNode *p, *s;
        p = T->rchild;
        s = p;
        lower = true;
        if(T->rchild == NULL) //如果所要删除的节点的右孩子为空
        {
            p = T;
            T = T->lchild; //直接删除
            free(p);
            lower = true;
            return true;
        }else{
            while(s) //如果所要删除的节点右子树不为空,就找T的后继
            {
                p = s;
                s = s->lchild;
            }

            T->data = p->data; //替换T
            DeleteElement(T->rchild, p->data, lower); //删除掉T的后继
            R = true;
        }
    }else if(key < T->data)
    {
        DeleteElement(T->lchild, key, lower);
        L = true;
    }else {
        DeleteElement(T->rchild, key, lower);
        R = true;
    }

    if(lower) //如果有节点删除
    {
        if(L)
        {
            switch(T->bf)
            {
                case LH: //没删之前LH,删后T->bf = EH
                    T->bf = EH;
                    lower = true;
                    break;
                case RH: //没删之前RH,删后导致右不平衡
                    RightBalance(T);
                    lower = false;
                    break;
                case EH: //没删之前EH,删后RH
                    T->bf = RH;
                    lower = false;
                    break;
                default:
                    break;
            }
        }else {
            switch(T->bf)
            {
                case EH:
                    T->bf = LH;
                    lower = false;
                    break;
                case RH:
                    T->bf = EH;
                    lower = true;
                    break;
                case LH:
                    LeftBalance(T);
                    lower = false;
                    break;
                default:
                    break;
            }
        }
    }
}

//中序遍历输出
void InOrderReverse(BiTree &T)
{
    if(T)
    {
        InOrderReverse(T->lchild);
        cout << T->data << " ";
        InOrderReverse(T->rchild);
    }
}

int main(int argc, char** argv)
{
    BiTree tree = NULL;
    int a[] = {4,3,2,7,9,11,10};
    bool taller = false;
    int size = sizeof(a) / sizeof(a[0]);
    for(int i = 0; i < size; ++i)
    {
        InsertAVLTree(tree, a[i], taller);
    }

    InOrderReverse(tree);
    cout << endl;
    cout << "Tree Root = " << tree->data << endl;

    bool lower;
    DeleteElement(tree, 7, lower);
    InOrderReverse(tree);
    cout << endl;
    cout << "Tree Root = " << tree->data << endl;
    return 0;
}
