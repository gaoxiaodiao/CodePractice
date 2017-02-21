/*
*文件说明:红黑树相关声明及定义
*作者:高小调
*日期:2017-02-17
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
	const K _key;
	V _value;
	COLOR _color;

	RBTreeNode(const K &key,const V& value)
		:_parent(NULL)
		,_left(NULL)
		,_right(NULL)
		,_key(key)
		,_value(value)
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
	bool Insert(const K&key,const V &value){
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

			while(parent!=NULL&&parent->_color==RED){
				Node *grandfather = parent->_parent;
				if(parent == grandfather->_left){
					Node *uncle = grandfather->_right;
					if(uncle!=NULL && uncle->_color==RED){
						uncle->_color = parent->_color = BLACK;
						grandfather->_color = RED;
						cur = grandfather;
						parent = cur->_parent;
					}else{
						if(cur!=parent->_left){
							RotateL(parent);
							swap(cur,parent);
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
		return true;
	}
	bool IsBalance(){
		Node *cur = _root;
		size_t blacknum = 0;	//黑色节点数目
		size_t count = 0;		//最左路径黑色节点数目
		while(cur!=NULL){
			if(cur->_color == BLACK){
				++count;
			}
			cur = cur->_left;
		}
		return _CheckColorAndBlackNum(_root,blacknum,count);
	}
protected:
	bool _CheckColorAndBlackNum(Node *root,size_t blacknum,size_t count){
		if(root==NULL){
			return true;
		}
		if(root->_color==BLACK){
			//计算黑节点数目
			++blacknum;
		}
		if(root->_color==RED&&root->_parent->_color==RED){
			//出现连续红节点
			return false;
		}
		if(root->_left==NULL&&root->_right==NULL&&blacknum!=count){
			//一条路径走完,本路径黑色节点数目与其他路径数目不同
			return false;
		}
		return  _CheckColorAndBlackNum(root->_left,blacknum,count)&&
			_CheckColorAndBlackNum(root->_right,blacknum,count);
	}
	void RotateL(Node *parent){
		Node *subR = parent->_right;
		Node *subRL = subR->_left;

		parent->_right = subRL;
		if(subRL!=NULL){
			subRL->_parent = parent;
		}

		Node *pparent= parent->_parent;
		if(pparent!=NULL){
			if(parent == pparent->_left){
				pparent->_left = subR;
			}else{
				pparent->_right = subR;
			}
			subR->_parent = pparent;
		}else{
			_root = subR;
			//_root->_parent = subR;
			_root->_parent = NULL;
		}

		subR->_left = parent;
		parent->_parent = subR;
	}

	void RotateR(Node *parent){
		Node *subL = parent->_left;
		Node *subLR = subL->_right;

		parent->_left = subLR;
		if(subLR){
			subLR->_parent = parent;
		}

		Node *pparent = parent->_parent;
		if(pparent!=NULL){
			if(pparent->_left==parent){
				pparent->_left = subL;
			}else{
				pparent->_right = subL;
			}
			subL->_parent = pparent;
		}else{
			_root = subL;
			_root->_parent = NULL;
		}
		
		subL->_right = parent;
		parent->_parent = subL;
	}
protected:
	void _Destory(Node *&root){
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