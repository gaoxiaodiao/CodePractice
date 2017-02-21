/*
*文件说明:红黑树相关声明及实现
*作者:高小调
*日期:2017-02-20
*集成开发环境:Microsoft Visual Studio 2010 
*/
#pragma once
enum COLOR{
	RED,
	BLACK
};
template<typename K,typename V>
struct RBTreeNode{
	RBTreeNode *_parent;
	RBTreeNode *_left;
	RBTreeNode *_right;
	K _key;
	V _value;
	COLOR _color;
	RBTreeNode(const K& key,const V &value)
		:_parent(NULL)
		,_left(NULL)
		,_right(NULL)
		,_key(key)
		,_value(value){}
};

template<typename K,typename V>
class RBTree{
public:
	typedef RBTreeNode<K,V> Node;
	RBTree():_root(NULL){}
	~RBTree(){
		_destory(_root);
	}
public:
	bool insert(const K&key,const V& value){
		if(_root==NULL){
			_root = new Node(key,value);
		}else{
			Node *parent = NULL;
			Node *cur = _root;
			while(cur!=NULL){
				if(cur->_key > key){
					parent = cur;
					cur = cur->_left;
				}else if(cur->_key < key){
					parent = cur;
					cur = cur->_right;
				}else{
					return false;
				}
			}
			cur = new Node(key,value);
			if(parent->_key > key){
				parent->_left = cur;
			}else{
				parent->_right = cur;
			}
			cur->_parent = parent;
			
			while(parent!=NULL &&parent->_color==RED){
				Node *grandfather = parent->_parent;
				if(grandfather->_left == parent){
					Node *uncle = grandfather->_right;
					if(uncle!=NULL && uncle->_color==RED){
						uncle->_color = parent->_color = BLACK;
						grandfather->_color = RED;
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
					if(uncle!=NULL &&uncle->_color==RED){
						parent->_color = uncle->_color = RED;
						grandfather->_color = BLACK;
						cur = grandfather;
						parent = cur->_parent;
					}else{
						if(cur!=parent->_right){
							RotateR(parent);
							swap(cur,parent);
						}else{
							RotateL(grandfather);
							parent->_color = BLACK;
							grandfather->_color = RED;
							break;
						}
					}
				}
			
			}
		}
		_root->_color = BLACK;
	}
	bool isBalance(){
		Node *cur = _root;
		size_t blackNodeNum = 0;
		size_t leftBlackNodeNum = 0;
		while(cur!=NULL){
			if(cur->_color == BLACK){
				++leftBlackNodeNum;
			}
			cur = cur->_left;
		}
		return _checkIsBalance(_root,blackNodeNum,leftBlackNodeNum);
	}
protected:
	bool _checkIsBalance(Node *root,size_t blacknum,const size_t k){
		if(root==NULL){
			return true;
		}
		if(root->_color==RED && root->_parent->_color==RED){
			return false;
		}
		if(root->_color == BLACK){
			++blacknum;
		}
		if(root->_left==NULL&&root->_right==NULL&&blacknum!=k){
			return false;
		}
		return _checkIsBalance(root->_left,blacknum,k)&&
			_checkIsBalance(root->_right,blacknum,k);
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
		}else{
			_root = subR;
			_root->_parent = NULL;
		}

		subR->_left = parent;
		parent->_parent = subR;
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
				parent->_right = subL;
			}
			subL->_parent = parent->_right;
		}else{
			_root = subL;
			_root->_parent = NULL;
		}

		subL->_right = parent;
		parent->_parent = subL;
	}
	void _destory(Node *&root){
		if(root!=NULL){
			_destory(root->_left);
			_destory(root->_right);
			delete root;
			root = NULL;
		}
	}
private:
	Node *_root;
};