/*************************************************************************
	> File Name: avl1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年07月11日 星期三 15时20分41秒
 ************************************************************************/

#include<iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

typedef struct AVLNode *Tree;
typedef int ElementType;
struct AVLNode{
    int depth; //深度,通过深度比较可得出是否平衡
    Tree parent;
    ElementType val; //结点值
    Tree lchild;
    Tree rchild;
    AVLNode(int val = 0)
    {
        parent = NULL;
        depth = 0;
        lchild = rchild = NULL;
        this->val = val;
    }
};

Tree insert_val(Tree&, Tree, Tree);
Tree remove(Tree&, ElementType);
Tree remove_val(Tree&, Tree&);
void update_depth(Tree);
Tree AVLTree(Tree&, Tree);
Tree LL_rotate(Tree);
Tree RL_rotate(Tree);
Tree RR_rotate(Tree);
Tree LR_rotate(Tree);
int get_balance(Tree);
int is_balance(Tree);
Tree *Find_Min(Tree&);

//向AVL树中插入val
//参数:根,插入的数据val
//返回:新根结点
Tree Insert(Tree &root, ElementType val)
{
    Tree temp = NULL;
    Tree node = new AVLNode(val);

    //插入结点
    temp = insert_val(root, node, NULL); //调用真正的插入函数
    if(temp)
    {
        update_depth(temp);
        root = AVLTree(root, temp); //检查树是否该调整
    }else {  //无需插入,释放结点
        delete temp;
    }

    return root;
}

//插入函数
//参数:根结点,待插结点,待插结点的父结点
//返回:插入结点
Tree insert_val(Tree &root, Tree node, Tree parent)
{
    if(NULL == root)
    {
        root = node;
        node->parent = parent; //设置当前结点的父结点
        return root; //返回插入结点
    }

    if(node->val < root->val) //插左子树
    {
        return insert_val(root->lchild, node, root);
    }else if(node->val > root->val) //插由子树
    {
        return insert_val(root->rchild, node, root);
    }
    else //已存在该结点,停止插入操作,返回NULL
    {
        return NULL;
    }
}

//AVL树调整函数
//参数:根结点,插入结点
//返回:调整后的根结点
Tree AVLTree(Tree &root, Tree node)
{
    int balance = 0; //平衡因子
    while(node != NULL)
    {
        update_depth(node); //更新当前结点的高度信息
        balance = is_balance(node); //获取当前结点的平衡因子情况
        if(balance > 1 || balance < -1) //平衡因子超标
        {
            if(balance > 1) //左子树高
            {
                if(is_balance(node->lchild) > 0) //LL型
                    node = LL_rotate(node);
                else //LR型
                    node = LR_rotate(node);
            }else { //右子树高
                if(is_balance(node->rchild) < 0) //RR型
                    node = RR_rotate(node);
                else //RL型
                    node = RL_rotate(node);
            }

            if(node->parent == NULL) //到达根结点
            {
                root = node; //设置新的根结点
                break; //退出
            }
        }

        node = node->parent;  //依次找到其父结点
    }

    return root; //返回新根
}

//查找最小结点
Tree *Find_Min(Tree &root)
{
    if(root->lchild)
    {
        return Find_Min(root->lchild);
    }

    return &root;
}

//删除操作
//参数:根,需要删除的结点
//返回:返回删除结点的父结点
Tree remove_val(Tree &root, Tree &node)
{
    Tree parent = node->parent;
    Tree temp = NULL;
    //只有左孩子
    if(node->rchild == NULL && node->lchild != NULL)
    {
        temp = node;
        node = node->lchild; //指向左孩子
        node->parent = temp->parent;
        delete temp; //释放结点
        update_depth(node); //更新当前结点信息
    }else if(node->lchild == NULL && node->rchild != NULL) //只要右孩子
    {
        temp = node;
        node = node->rchild; //指向右结点
        node->parent = temp->parent;
        delete temp; //释放结点
        update_depth(node); //更新当前结点信息
    }else if(node->rchild == NULL && node->lchild == NULL) //叶子结点
    {
        parent = node->parent; //找到其父结点
        if(parent) //如果父节点存在
        {
            delete node;
            node = NULL;
            update_depth(parent); //更新父节点高度信息
        }else { //删除的是根
            delete root;
            root = NULL;
        }
    }else 
    {   //既有左孩子也有右孩子,化繁为简
        Tree *tmp = Find_Min(node->rchild); //找到替代元素,temp为叶子结点
        node->val = (*tmp)->val; //更新值
        //判断当前叶子结点是左孩子还是右孩子
        parent = (*tmp)->parent;
        delete *tmp;
        *tmp = NULL;
        update_depth(parent);
    }
    return parent;
}

//找到删除的结点，执行删除操作，并根据情况调整AVL树
//参数:根,需要删除的val
//返回:找到删除结点的情况则返回新根,否则返回NULL
Tree remove(Tree &root, ElementType val)
{
    static Tree *temp = NULL;
    if(root == NULL)
    {
        temp = NULL;
        return NULL;
    }else if(root->val < val) //在右子树查找
    {
        remove(root->rchild, val);
    }else if(root->val > val) //在左子树查找
    {
        remove(root->lchild, val);
    }else //找到了,标记一下
        temp = &root;

    if(temp)
    {
        if(!root->parent) //如果已经返回到最后一次(也就是root是真正的树根)
        {
            Tree tmp = NULL;
            tmp = remove_val(root, *temp); //执行删除操作
            return AVLTree(root, tmp); //更新AVL树
        }

        return *temp;
    }

    return NULL;
}

//获取当前结点的深度
int get_balance(Tree node)
{
    if(node == NULL)
    {
        return 0;
    }
    return node->depth;
}

//返回当前平衡因子
int is_balance(Tree node)
{
    if(node == NULL)
    {
        return 0;    
    }else 
    {
        return get_balance(node->lchild) - get_balance(node->rchild);
    }
}

//RR型调整函数
//返回新父结点
Tree RR_rotate(Tree node)
{
    //node为离操作结点最近的失衡的结点
    Tree parent = NULL, son;
    //获取失衡结点的父节点
    parent = node->parent;
    //获取失衡结点的右孩子
    son = node->rchild;

    //设置son结点左孩子的父指针
    if(son->lchild != NULL)
    {
        son->lchild->parent = node;
    }

    //失衡结点的右孩子并更为son的左孩子
    node->rchild = son->lchild;

    //更新失衡结点的高度信息
    update_depth(node);
    //失衡结点变成son的左孩子
    son->lchild = node;
    //设置son的父节点为原失衡结点的父节点
    son->parent = parent;

    //如果失衡结点不是根结点，则开始更新父结点
    if(parent != NULL)
    {
        //如果父节点的左孩子是失衡结点，指向现在更新后的新孩子son
        if(parent->lchild == node)
        {
            parent->lchild = son;
        }else //父结点的右孩子是失衡结点
        {
            parent->rchild = son;
        }
    }

    //设置失衡结点的父亲
    node->parent = son;
    //更新son结点的高度信息
    update_depth(son);
    return son;
}

//LL型调整函数
//返回:新父结点
Tree LL_rotate(Tree node)
{
    //node为离操作结点最近的失衡的结点
    Tree parent = NULL, son;
    //获取失衡结点的父节点
    parent = node->parent;
    //获取失衡结点的左孩子
    son = node->lchild;

    //设置son结点右孩子的父指针
    if(son->rchild != NULL)
    {
        son->rchild->parent = node;
    }

    //失衡结点的左孩子变更为son的右孩子
    node->lchild = son->rchild;

    //更新失衡结点的高度信息
    update_depth(node);

    //失衡结点变成son的右孩子
    son->rchild = node;
    
    //设置son的父节点为原失衡结点的父节点
    son->parent = parent;

    //如果失衡结点不是根结点，则开始更新父结点
    if(parent != NULL)
    {
        //如果父节点的左孩子是失衡结点，指向现在更新后的新孩子son
        if(parent->lchild == node)
        {
            parent->lchild = son;
        }else { //父节点的右孩子是失衡结点
            parent->rchild = son;
        }
    }

    //设置失衡结点的父亲
    node->parent = son;
    //更新son结点的高度信息
    update_depth(son);
    return son;
}

//LR型,先左旋转,再右旋转
//返回:新父结点
Tree LR_rotate(Tree node)
{
    RR_rotate(node->lchild);
    return LL_rotate(node);
}

//RL型,先右旋转,再左旋转
//返回:新父结点
Tree RL_rotate(Tree node)
{
    LL_rotate(node->rchild);
    return RR_rotate(node);
}

//更新当前深度
void update_depth(Tree node)
{
    if(node == NULL) return;
    else {
        int depth_Lchild = get_balance(node->lchild); //左孩子深度
        int depth_Rchild = get_balance(node->rchild); //右孩子深度
        node->depth = max(depth_Lchild, depth_Rchild) + 1;
    }
}

//前序
void PreOrder(Tree root)
{
    if(root == NULL)
    {
        return;
    }
    printf("%d ", root->val);
    PreOrder(root->lchild);
    PreOrder(root->rchild);
}

//中序
void InOrder(Tree root)
{
    if(root == NULL)
    {
        return;
    }
    InOrder(root->lchild);
    printf("%d ", root->val);
    InOrder(root->rchild);
}

int main()
{
    Tree root = NULL;
    root = Insert(root, 16);
    root = Insert(root, 3);

    //插入7后LR调整
    root = Insert(root, 7);
    root = Insert(root, 11);
    
    //插入9后LL调整
    root = Insert(root, 9);

    //插入26后RR调整
    root = Insert(root, 26);

    //插入18后RL调整
    root = Insert(root, 18);
    root = Insert(root, 14);

    //插入15后LR调整
    root = Insert(root, 15);

    printf("插入:\n");
    printf("前序:");
    PreOrder(root);
    printf("\n");

    printf("中序:");
    InOrder(root);
    printf("\n");

    printf("删除:\n");

    //删除26后进行LR型调整
    remove(root, 26);
    //删除18后进行RR型
    remove(root, 18);
    remove(root, 3);
    remove(root, 9);
    //删除7后进行RL调整
    remove(root, 7);

    //删除11后进行LL调整
    remove(root, 11);
    printf("前序:");
    PreOrder(root);
    printf("\n");
    printf("中序:");
    InOrder(root);
    printf("\n");

    int a[] = {4,3,2,7,9,11,10};
    int size = sizeof(a) / sizeof(a[0]);
    Tree tree = NULL;
    for(int i = 0; i < size; ++i)
    {
        Insert(tree, a[i]);
    }

    printf("前序:");
    PreOrder(tree);
    printf("\n");
    printf("中序:");
    InOrder(tree);
    printf("\n");

    return 0;
}
