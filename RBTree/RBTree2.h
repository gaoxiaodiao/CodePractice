/*
*�ļ�˵��:��������������ʵ��
*����:��С��
*����:2017-02-14
*���ɿ�������:Microsoft Visual Studio 2010 
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

	RBTreeNode(const K&k,const V &v)
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
		//1.�Ҳ���λ��
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
		//2.����Ԫ��
		cur = new Node(k,v);
		if(parent->_key > k){
			parent->_left = cur;
		}else{
			parent->_right = cur;
		}
		cur->_parent = parent;
		//3.���ݲ�ͬ���������ת
		while(parent!=NULL && parent->_color==RED){
			Node *grandfather = parent->_parent;
			if(grandfather->_left==parent){
				Node *uncle = grandfather->_right;
				if(uncle!=NULL && uncle->_color==RED){
					//��һ�����,���б�ɫ����
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					//�������ϵ���
					cur = grandfather;
					parent = cur->_parent;
				}else{
					if(cur!=parent->_left){
						//���������
						RotateL(parent);
						//���ڸ��ӹ�ϵ!!!
						std::swap(cur,parent);
					}else{
						//�ڶ������
						RotateR(grandfather);
						parent->_color = BLACK;
						grandfather->_color = RED;
						break;
					}
				}
			}else{
				Node *uncle = grandfather->_left;
				if(uncle && uncle->_color==RED){
					//��һ�����:��ɫ����
					uncle->_color = parent->_color = BLACK;
					grandfather->_color = RED;
					//�������ϵ���
					cur = grandfather;
					parent = cur->_parent;
				}else{
					if(cur!=parent->_right){
						RotateR(parent);
						std::swap(parent,cur);
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
	
	bool IsBalance(){
		size_t num = 0;
		size_t k = 0;
		Node *cur = _root;
		while(cur!=NULL){
			if(cur->_color==BLACK)
				++k;
			cur = cur->_left;
		}
		return _CheckColor(_root)&&_CheckBlackNum(_root,num,k);
	}

protected:
	bool _CheckColor(Node *root){
		if(root==NULL){
			return true;
		}
		if(root->_color==RED && root->_parent->_color==RED){
			return false;
		}
		return _CheckColor(root->_left)&&
			_CheckColor(root->_right);
	}
	bool _CheckBlackNum(Node *root,size_t num,const size_t k){
		if(root==NULL){
			return true;
		}
		if(root->_color == BLACK){
			++num;
		}
		
		if(root->_left==NULL && root->_right==NULL && num!=k){
			return false;
		}
		return _CheckBlackNum(root->_left,num,k)&&
			_CheckBlackNum(root->_right,num,k);
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
private:
	Node *_root;
};