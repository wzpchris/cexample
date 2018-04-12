// TreeTest.cpp : 定义控制台应用程序的入口点。
//
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <deque>
using namespace std;

/*二叉树结构定义*/
typedef char TElemType;
typedef struct BiTNode {
	TElemType data;	//结点数据
	struct BiTNode *lchild, *rchild; //左右子结点
}BiTNode, *BiTree;

//创建二叉树
//按前序输入二叉树中的结点，空指针采用'#'表示 AB#D##C##
void CreateBiTree(BiTree *T)
{
	TElemType ch;
	//scanf("%c", &ch);
	//cout << "请输入结点数据:" << endl;
	cin >> ch;
	if (ch == '#')
	{
		*T = NULL;
	}
	else {
		*T = (BiTree)malloc(sizeof(BiTNode));
		if (!*T){
			exit(0);
		}

		(*T)->data = ch;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
}

/*递归遍历二叉树*/
//前序遍历
void PreOrderTraverse(BiTree T)
{
	if (NULL == T) return;
	cout << T->data << " ";
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}

//中序遍历
void InOrderTraverse(BiTree T)
{
	if (NULL == T) return;
	InOrderTraverse(T->lchild);
	cout << T->data << " ";
	InOrderTraverse(T->rchild);
}

//后序遍历
void PostOrderTraverse(BiTree T)
{
	if (NULL == T) return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	cout << T->data << " ";
}

/*非递归遍历二叉树*/
//前序遍历
void PreOrderTraverse2(BiTree T)
{
	stack<BiTree> s;
	BiTree p = T;
	while (p != NULL || !s.empty()){
		while (p){
			cout << p->data << " ";
			s.push(p);
			p = p->lchild;
		}

		if (!s.empty()){
			p = s.top();
			s.pop();
			p = p->rchild;
		}
	}
}

//中序遍历
void InOrderTraverse2(BiTree T)
{
	stack<BiTree> s;
	BiTree p = T;
	while (p != NULL || !s.empty()){
		while (p){
			s.push(p);
			p = p->lchild;
		}

		if (!s.empty()){
			p = s.top();
			s.pop();
			cout << p->data << " ";
			p = p->rchild;
		}
	}
}

//后序遍历
void PostOrderTraverse2(BiTree T)
{
	stack<BiTree> s;
	BiTree p = T;
	BiTree pre = NULL;
	s.push(p);
	while (!s.empty())
	{
		p = s.top();
		if ((p->lchild == NULL && p->rchild == NULL)
			|| (pre != NULL && (pre == p->lchild || pre == p->rchild)))
		{
			cout << p->data << " ";
			s.pop();
			pre = p;
		}
		else {
			if (p->rchild)
				s.push(p->rchild);
			if (p->lchild)
				s.push(p->lchild);
		}
	}
}

//层序遍历
void FromTopToBottom(BiTree T)
{
	deque<BiTree> s;
	BiTree p = T;
	s.push_back(p);
	while (!s.empty()){
		p = s.front();
		s.pop_front();
		cout << p->data << " ";
		if (p->lchild)
			s.push_back(p->lchild);
		if (p->rchild)
			s.push_back(p->rchild);
	}
}
int main(int argc, char** argv)
{
	BiTree T;
	//创建二叉树
	CreateBiTree(&T);
	cout << "二叉树创建完成" << endl;
	//前序递归遍历二叉树
	cout << "前序递归遍历二叉树:" << endl;
	PreOrderTraverse(T);
	cout << endl;
	cout << "中序递归遍历二叉树:" << endl;
	InOrderTraverse(T);
	cout << endl;
	cout << "后序递归遍历二叉树:" << endl;
	PostOrderTraverse(T);
	cout << endl;
	
	cout << "=======================" << endl;
	cout << "前序非递归遍历二叉树:" << endl;
	PreOrderTraverse2(T);
	cout << endl;
	cout << "中序非递归遍历二叉树:" << endl;
	InOrderTraverse2(T);
	cout << endl;
	cout << "后序非递归遍历二叉树:" << endl;
	PostOrderTraverse2(T);
	cout << endl;

	cout << "======================" << endl;
	cout << "层序遍历二叉树:" << endl;
	FromTopToBottom(T);
	cout << endl;

	char ch;
	cin >> ch;
	return 0;
}

