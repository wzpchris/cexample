//file RBTree.h
//July and saturnman

#ifndef _RB_TREE_H_
#define _RB_TREE_H_
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

template<class KEY, class U>
class RB_Tree {
private:
	RB_Tree(const RB_Tree& input) {}
	const RB_Tree& operator= (const RB_Tree& input) {}
private:
	enum COLOR { RED, BLACK };
	class RB_Node 
	{
	public:
		RB_Node() {
			right = NULL;
			left = NULL;
			parent = NULL;
		}
		COLOR RB_COLOR;
		RB_Node* right;
		RB_Node* left;
		RB_Node* parent;
		KEY key;
		U data;
	};
public:
	RB_Tree() {
		this->m_nullNode = new RB_Node();
		this->m_root = m_nullNode;
		this->m_nullNode->right = this->m_root;
		this->m_nullNode->left = this->m_root;
		this->m_nullNode->parent = this->m_root;
		this->m_nullNode->RB_COLOR = BLACK;
	}
	//是否为空
	bool Empty() {
		if(this->m_root == this->m_nullNode) {
			return true;	
		}else {
			return false;
		}
	}
	//查找key
	RB_Node* find(KEY key) {
		RB_Node *index = m_root;
		while(index != m_nullNode) {
			if(key < index->key) {
				index = index->left;
			}else if(key > index->key) {
				index = index->right;
			}else {
				break;
			}
		}

		return index;
	}
	//插入节点
	//总操作
	/*RB_INSERT(T, z)
	 *y <- nil[T]    //y始终指向x的父节点
	 *x <- root[T]	 //x指向当前树的根节点
	 ×while x != nil[T]
	 *	do y <- x
	 * 		if key[z] < key[x] 	//向左,向右
	 ×			then x <- left[x]
	 *			else x <- right[x]	//为了找到合适的插入点,x探路跟踪路径,直到x成为nil为止
	 *p[z] <- y
	 *if y = nil[T] 
	 *	then root[T] <- z
	 *	else if key[z] < key[y]
	 * 		then left[y] <- z
	 * 		else right[y] <- z		//置z相关的指针		
	 *left[z] <- nil[T]
	 *right[z] <- nil[T]	//设置空
	 *color[z] <- RED		//将新插入的节点z作为红色
	 *RB_INSERT_FIXUP(T, z)	//修复性质

	*/
	bool Insert(KEY key, U data) {
		RB_Node* insert_point = m_nullNode;
		RB_Node* index = m_root;	
		while(index != m_nullNode) {
			insert_point = index;
			if(key < index->key) {
				index = index->left;
			}else if(key > index->key) {
				index = index->right;
			}else {
				return false;
			}
		}

		RB_Node *insert_node = new RB_Node();
		insert_node->key = key;
		insert_node->data = data;
		insert_node->RB_COLOR = RED;
		insert_node->right = m_nullNode;
		insert_node->left = m_nullNode;
		
		if(insert_point == m_nullNode) { //插入的是一颗空树
			m_root = insert_node;
			m_root->parent = m_nullNode;
			m_nullNode->left = m_root;
			m_nullNode->right = m_root;
			m_nullNode->parent = m_root;
		}else {
			if(key < insert_point->key) {
				insert_point->left = insert_node;
			}else {
				insert_point->right = insert_node;
			}
			insert_node->parent = insert->point;
		}
		InsertFixUp(insert_node);
	}
	//插入节点性质修复
	//3中插入情况
	/*RB_INSERT_FIXUP(T, z)
	 *while color[p[z]] = RED
	 *	do if p[z] = left[p[p[z]]]
	 *			then y <- right[p[p[z]]]
					if color[y] = RED
						then color[p[z]] <- BLACK 	//case 1
							 color[y] <- BLACK		//case 1
							 color[p[p[z]]] <- RED	//case 1
							 z <- p[p[z]]			//case 1
					else if z = right[p[z]]
						then z <- p[z] 				//case 2
								LEFT_ROTATE(T,z)	//case 2
						color[p[z]] <- BLACK		//case 3
						color[p[p[z]]] <- RED		//case 3
						RIGHT_ROTATE(T, p[p[z]])	//case 3
				else (same as then clause with "right" and "left" exchanged)
	  color[root[T]] <- BLACK
	*/
	void InsertFixUp(RB_Node* node) {
		while(node->parent->RB_COLOR == RED){
			if(node->parent == node->parent->parent->left)
			{
				RB_Node *uncle = node->parent->parent->right;
				if(uncle->RB_COLOR == RED) 	//插入情况1,z的叔叔y是红色的
				{
					node->parent->RB_COLOR = BLACK;
					uncle->RB_COLOR = BLACK;
					node->parent->parent->RB_COLOR = RED;
					node = node->parent->parent;
				}else if(uncle->RB_COLOR == BLACK) //插入情况2:z的叔叔y是黑色
				{
					if(node == node->parent->right) //且z时右孩子
					{
						node = node->parent;
						RotateLefe(node);
					}

					//插入情况3:z的叔叔y时黑色的,但z是左孩子
					node->parent->RB_COLOR = BLACK;
					node->parent->parent->RB_COLOR = RED;
					RotateRight(node->parent->parent);
				}
			}
			else {	//这部分是针对插入情况1中,z的父亲现在作为祖父的右孩子的情况
				RB_Node *uncle = node->parent->parent->left;
				if(uncle->RB_COLOR == RED)
				{
					node->parent->RB_COLOR = BLACK;
					uncle->RB_COLOR = BLACK;
					uncle->parent->RB_COLOR = RED;
					node = node->parent->parent;
				}else if(uncle->RB_COLOR == BLACK) {
					if(node == node->parent->left) {
						node = node->parent;
						RotateRight(node);	
					}

					node->parent->RB_COLOR = BLACK;
					node->parent->parent->RB_COLOR = RED;
					RotateLeft(node->parent->parent);
				}
			}
		}	
		m_root->RB_COLOR = BLACK;
	}
	//左旋
	bool RotateLeft(RB_Node* node) {
		if(node == m_nullNode || node->right == m_nullNode) {
			return false;
		}

		RB_Node *lower_right = node->right;
		lower_right->parent = node->parent;
		node->right = lower_right->left;
		if(lower_right->left != m_nullNode)	{
			lower_right->left->parent = node;
		}
		if(node->parent == m_nullNode) {
			m_root = lower_right;
			m_nullNode->left = m_root;
			m_nullNode->right = m_root;
		}else {
			if(node == node->parent->left) {
				node->parent->left = lower_right;
			}else {
				node->parent->right = lower_right;
			}
		}
		node->parent = lower_right;
		lower_right->left = node;	
	}	
	//右旋
	bool RotateRight(RB_Node *node) {
		if(node == m_nullNode || node->left == m_nullNode) {
			return false;
		}

		RB_Node *lower_left = node->left;
		node->left = lower_left->right;
		lower_left->parent = node->parent;
		if(lower_left->right != m_nullNode) {
			lower_left->right->parent = node;
		}
		if(node->parent == m_nullNode) { //node is root
			m_root = lower_left;
			m_nullNode->left = m_root;
			m_nullNode->right = m_root;
		}else {
			if(node == node->parent->right) {
				node->parent->right = lower_left;
			}else {
				node->parent->left = lower_left;
			}
		}
		node->parent = lower_left;
		lower_left->right = node;
	}
	//删除节点
	bool Delete(KEY key) {
		RB_Node *delete_point = find(key);
		if(delete_point == m_nullNode) {
			return false;
		}

		if(delete_point->left != m_nullNode && delete_point->right != m_nullNode) {
			RB_Node *successor = InOrderSuccessor(delete_point);
			delete_point->data = successor->data;
			delete_point->key = successor->key;
			delete_point = successor;
		}

		RB_Node *delete_point_child;
		if(delete_point->right != m_nullNode) {
			delete_point_child = delete_point->right;
		}else if(delete_point->left != m_nullNode) {
			delete_point_child = delete_point->left;
		}else {
			delete_point_child = m_nullNode;
		}

		delete_point_child->parent = delete_point->parent;
		if(delete_point->parent == m_nullNode) { //delete root node
			m_root = delete_point_child;
			m_nullNode->parent = m_root;
			m_nullNode->left = m_root;
			m_nullNode->right = m_root;
		}else if(delete_point == delete_point->parent->right) {
			delete_point->parent->right = delete_point_child;
		}else { 
			delete_point->parent->left = delete_point_child;
		}

		if(delete_point->RB_COLOR == BLACK && !(delete_point_child == m_nullNode && delete_point_child->parent == m_nullNode)) {
			DeleteFixUp(delete_point_child);
		}
		delete delete_point;
		return true;
	}
	//删除节点性质修复
	/*RB_DELETE_FIXUP(T,x)
	 *while x != root[T] and color[x] = BLACK
	 *	do if x = left[p[x]]
			then w <- right[p[x]]
				if color[w] = RED
					then color[w] <- BLACK		//case 1
						 color[p[x]] <- RED		//case 1
						 LeftRotate(T, p[x]) 	//case 1
						 w <- right[p[x]]		//case 1
				if color[left[w]] = BLACK and color[right[w]] = BLACK 
					then color[w] <- RED		//case 2
						 x <- p[x]				//case 2
					else if color[right[w]] = BLACK 
						then color[left[w]] <- BLACK 	//case 3
							 color[w] <- RED			//case 3
							 RightRotate(T,w)			//case 3
							 w <- right[p[x]]			//case 3
						color[w] <- color[p[x]]			//case 4
						color[p[x]] <- BLACK			//case 4
						color[right[w]] <- BLACK 		//case 4
						LeftRotate(T,p[x])				//case 4
						x <- root[T]
			else (same as then clause with "right" and "left" exchanged)
	  color[x] <- BLACK 
	*/		
	void DeleteFixUp(RB_Node *node) {
		while(node != m_root && node->RB_COLOR == BLACK) {
			if(node == node->parent->left) {
				RB_Node *brother = node->parent->right;	
				if(brother->RB_COLOR == RED) //情况1:x的兄弟w是红色的
				{
					brother->RB_COLOR = BLACK;
					node->parent->RB_COLOR = RED;
					RotateLeft(node->parent);
				}else { //情况2:x的兄弟w是黑色的
					if(brother->left->RB_COLOR == BLACK && brother->right->RB_COLOR == BLACK) {
						//且w的两个孩子都是黑色的
						brother->RB_COLOR = RED;
						node = node->parent;
					}else if(brother->right->RB_COLOR == BLACK) {
						//情况3:x的兄弟w是黑色的,w的右孩子是黑色(w的左孩子是红色)
						brother->RB_COLOR = RED;
						brother->left->RB_COLOR = BLACK;
						RotateRight(brother);
					}

					//情况4:x的兄弟w是黑色的,且w的右孩子是红色的
					brother->RB_COLOR = node->parent->RB_COLOR;
					node->parent->RB_COLOR = BLACK;
					brother->right->RB_COLOR = BLACK;
					RotateLeft(node->parent);
					node = m_root;	
				}	
			}else { //下述情况针对上面情况1中,node作为右孩子而阐述的
				RB_Node *brother = node->parent->left;	
				if(brother->RB_COLOR == RED) {
					brother->RB_COLOR = BLACK;
					node->parent->RB_COLOR = RED;
					RotateRight(node->parent);
				}else {
					if(brother->left->RB_COLOR == BLACK && brother->right->RB_COLOR == BLACK) {
						brother->RB_COLOR = RED;
						node = node->parent;
					}else if(brother->left->RB_COLOR == BLACK) {
						brother->RB_COLOR = RED;
						brother->right->RB_COLOR = BLACK;
						RotateLeft(brother);
					}

					brother->RB_COLOR = node->parent->RB_COLOR;
					node->parent->RB_COLOR = BLACK;
					brother->left->RB_COLOR = BLACK;
					RotateRight(node->parent);
					node = m_root;					
				}
			}
		}
		m_nullNode->parent = m_root; //最后将node置为根节点
		node->RB_COLOR = BLACK;		//并改为黑色
	}
	//
	inline RB_Node* InOrderPredecessor(RB_Node *node) {
		if(node == m_nullNode) {
			return m_nullNode;
		}
		RB_Node *result = node->left;
		while(result != m_nullNode) {
			if(result->right != m_nullNode) {
				result = result->right;
			}else {
				break;
			}
		}

		if(result == m_nullNode) {
			RB_Node *index = node->parent;
			result = node;
			while(index != m_nullNode && result == index->left) {
				result = index;
				index = index->parent;
			}	
			result = index;
		}
		
		return result;
	}
	//
	inline RB_Node *InOrderSuccessor(RB_Node *node) {
		if(node == m_nullNode) {
			return m_nullNode;
		}	
		RB_Node *result = node->right;
		while(result != m_nullNode) {
			if(result->left != m_nullNode) {
				result = result->left;
			}else {
				break;
			}
		}

		if(result == m_nullNode) {
			RB_Node *index = node->parent;
			result = node;
			while(index != m_nullNode && result == index->right) {
				result = index;
				index = index->parent;
			}
			result = index;
		}
		return result;
	}
	//debug
	void InOrderTraverse() {
		InOrderTraverse(m_root);
	}
	void CreateGraph(string filename) {

	}
	void InOrderCreate(ofstream& file, RB_Node *node) {
	
	}
	
	void InOrderTraverse(RB_Node *node) {
		if(node == m_nullNode) {
			return;
		}else {
			InOrderTraverse(node->left);
			cout << node->key << endl;
			InOrderTraverse(node->right);
		}
	}
	~RB_Tree() {
		clear(m_root);
		delete m_nullNode;
	}
private:
	void clear(RB_Node *node) {
		if(node == m_nullNode) {
			return;
		}else {
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}
private:
	RB_Node *m_nullNode;
	RB_Node *m_root;
};
#endif  /*_RB_TREE_H_*/
