/*
*文件说明:RBTree相关声明及实现
*作者:高小调
*日期:2017-02-13
*集成开发环境:Microsoft Visual Studio 2010 
*/
#pragma once
#include<cassert>
enum COLOR{
	RED,
	BLACK
};
template<typename K,typename V>
struct RBTreeNode{
	RBTreeNode * _parent;
	RBTreeNode * _left;
	RBTreeNode * _right;
	const K _key;
	V _value;
	COLOR _color;

	RBTreeNode(const K &k,const V &v)
		:_parent(NULL)
		,_left(NULL)
		,_right(NULL)
		,_key(k)
		,_value(v)
		,_color(RED){}

};


template<typename K,typename V>
class RBTree{
public:
	typedef RBTreeNode<K,V> Node;
	RBTree()
		:_root(NULL){}
	~RBTree(){
		_Destory(_root);
	}
public:
	bool Insert(const K &k,const V &v){
		if(_root==NULL){
			_root = new Node(k,v);
			_root->_color = BLACK;
			return true;
		}
		Node *parent = NULL;
		Node *cur = _root;
		while(cur!=NULL){
			if(cur->_key > k){
				parent = cur;
				cur = cur->_left;
			}else if(cur->_key < k){
				parent = cur;
				cur = cur->_right;
			}else{
				return false;
			}
		}
		
		cur = new Node(k,v);
		if(parent->_key > k){
			parent->_left = cur;
		}else{
			parent->_right = cur;
		}
		cur->_parent = parent;

		while(parent!=NULL && parent->_color ==RED){
			Node *pparent = parent->_parent;
			Node *uncle = NULL;
			if(pparent->_left == parent){
				uncle = pparent->_right;
			}else{
				uncle = pparent->_left;
			}
			//1.uncle存在且为红
			if(uncle!=NULL && uncle->_color==RED){
				pparent->_color = RED;
				parent->_color = uncle->_color = BLACK;
				cur = pparent;
				parent = cur->_parent;
			}else if(uncle==NULL || uncle->_color==BLACK){
				if(cur == parent->_left && parent ==pparent->_left){
					//对g进行左单旋
					RotateL(pparent);
				}else if(cur==parent->_right && parent == pparent->_right){
					//对g进行右单旋
					RotateR(pparent);
				}else if(cur==parent->_right && parent == pparent->_left){
					//对p进行左单旋
					RotateL(parent);
				}else{
					//对p进行右单旋
					RotateR(parent);
				}
			}else{
				assert(false);
			}
		}
		_root->_color = BLACK;	//保证根节点始终为黑
		return true;
	}
protected:
	void RotateR(Node *parent){
		Node *subL = parent->_left;
		Node *subLR = subL->_right;

		parent->_left = subLR;
		if(subLR!=NULL){
			subLR->_parent = parent;
		}

		Node *pparent = parent->_parent;
		if(pparent==NULL){
			_root = subL;
			_root->_parent = NULL;
		}else{
			if(pparent->_left == parent){
				pparent->_left = subL;
			}else{
				pparent->_right = subL;
			}
			subL->_parent = pparent;
		}

		subL->_right = parent;
		parent->_parent = subL;

		parent->_color = RED;
		subL->_color = BLACK;
	}
	void RotateL(Node *parent){
		Node *subR = parent->_right;
		Node *subRL = subR->_left;

		parent->_right = subRL;
		if(subRL!=NULL){
			subRL->_parent = parent;
		}

		Node *pparent = parent->_parent;
		if(pparent==NULL){
			_root = subR;
			_root->_parent = NULL;
		}else{
			if(pparent->_left == parent){
				pparent->_left = subR;
			}else{
				pparent->_right = subR;
			}
			subR->_parent = pparent;
		}

		subR->_left = parent;
		parent->_parent = subR;

		parent->_color = RED;
		subR->_color = BLACK;
	}
	void _Destory(Node *& root){
		if(root==NULL){
			return ;		
		}
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
		root = NULL;
	}
private:
	Node *_root;
};