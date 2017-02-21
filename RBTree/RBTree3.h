/*
*文件说明:红黑树相关声明及实现
*作者:高小调
*日期:2017-02-14
*集成开发环境:Microsoft Visual Studio 2010 
*/
#pragma once
enum COLOR{
	BLACK,
	RED
};
template<typename K,typename V>
struct RBTreeNode{
	RBTreeNode *_parent;
	RBTreeNode *_left;
	RBTreeNode *_right;
	const K _key;
	V _value;
	COLOR _color;

	RBTreeNode(const K& k,const V &v)
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
	~RBTree(){}
public:
	bool Insert(const K& k,const V &v){
		if(_root==NULL){
			_root = new Node(k,v);
			_root->_color = BLACK;
			return true;
		}
		Node *parent=NULL;
		Node *cur = _root;
		//1.找插入位置
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
		//2.插入元素
		cur = new Node(k,v);
		if(parent->_key > k){
			parent->_left = cur;
		}else{
			parent->_right = cur;
		}
		cur->_parent = parent;
		//3.变色调整
		while(parent!=NULL && parent->_color==RED){
			Node *grandfather = parent->_parent;
			if(grandfather->_left == parent){
				Node *uncle = grandfather->_right;
				if(uncle!=NULL && uncle->_color==RED){
					//第一种情况:变色
					uncle->_color = parent->_color = BLACK;
					grandfather->_color = RED;
					//继续向上调整
					cur = grandfather;
					parent = cur->_parent;
				}else{
					if(cur!=parent->_left){
						RotateL(parent);
						std::swap(cur,parent);
					}else{
						RotateR(grandfather);
						parent->_color = BLACK;
						grandfather->_color = RED;
						break;
					}
				}
			}else{
				Node *uncle = grandfather->_left;
				if(uncle!=NULL && uncle->_color==RED){
					uncle->_color = parent->_color = BLACK;
					grandfather->_color = RED;
					cur = grandfather;
					parent = cur->_parent;
				}else{
					if(cur!=parent->_right){
						RotateR(parent);
						std::swap(cur,parent);
					}else{
						RotateL(grandfather);
						parent->_color = BLACK;
						grandfather->_color = RED;
						break;
					}
				}
			}
		}
		_root->_color = BLACK;
		return true;
	}
	bool IsBalance(){
		size_t k = 0;
		size_t num = 0;
		Node *cur = _root;
		while(cur!=NULL){
			if(cur->_color==BLACK){
				++k;
			}
			cur = cur->_left;
		}
		return _CheckColor(_root)&&_CheckBlackNum(_root,num,k);
	}
protected:
	bool _CheckBlackNum(Node *root,size_t num,const size_t k){
		if(root==NULL){
			return true;
		}
		if(root->_color==BLACK){
			++num;
		}
		if(root->_left==NULL&&root->_right==NULL&&num!=k){
			return false;
		}
		return _CheckBlackNum(root->_left,num,k)&&
			_CheckBlackNum(root->_right,num,k);
	}
	bool _CheckColor(Node *root){
		if(root==NULL){
			return true;
		}
		if(root->_color==RED&&root->_parent->_color==RED){
			return false;
		}
		return _CheckColor(root->_left)&&
			_CheckColor(root->_right);
	}
	void _Destory(Node *&root){
		if(root==NULL){
			return ;
		}
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
		root = NULL;
	}
	void RotateR(Node *parent){
		Node *subL = parent->_left;
		Node *subLR = subL->_right;

		parent->_left = subLR;
		if(subLR!=NULL){
			subLR->_parent = parent;
		}
		
		Node *pparent = parent->_parent;
		if(pparent!=NULL){
			if(pparent->_left == parent){
				pparent->_left = subL;
			}else{
				pparent->_right = subL;
			}
			subL->_parent = pparent;
		}else{
			_root = subL;
			_root->_parent = subL;
		}

		subL->_right = parent;
		parent->_parent = subL;
	}
	void RotateL(Node *parent){
		Node *subR = parent->_right;
		Node *subRL = subR->_left;

		parent->_right = subRL;
		if(subRL!=NULL){
			subRL->_parent = parent;
		}

		Node *pparent = parent->_parent;
		if(pparent!=NULL){
			if(pparent->_left == parent){
				pparent->_left = subR;
			}else{
				pparent->_right = subR;
			}
			subR->_parent = pparent;
		}
		
		subR->_left = parent;
		parent->_parent = subR;
	}
private:
	Node *_root;
};