/*
*文件说明:AVL树相关声明及实现
*作者:高小调
*日期:2017-02-16
*集成开发环境:Microsoft Visual Studio 2010 
*/
#pragma once
#include<cassert>
#include<stack>
template<typename K,typename V>
struct AVLTreeNode{
	AVLTreeNode *_parent;
	AVLTreeNode *_left;
	AVLTreeNode *_right;
	const K _key;
	V _value;
	int _bf;

	AVLTreeNode(const K &key,const V &value)
		:_parent(NULL)
		,_left(NULL)
		,_right(NULL)
		,_key(key)
		,_value(value)
		,_bf(0){}
};

template<typename K,typename V>
class AVLTree{
public:
	typedef AVLTreeNode<K,V> Node;
	AVLTree()
		:_root(NULL){}
	~AVLTree(){
		_Destory(_root);
	}
public:
	bool Insert(const K&k,const V &v){
		if(_root==NULL){
			_root = new Node(k,v);
		}else{
			Node *p = NULL;
			Node *c = _root;
			while(c!=NULL){
				if(c->_key >k){
					p = c;
					c = c->_left;
				}else if(c->_key < k){
					p = c;
					c = c->_right;
				}else{
					return false;
				}
			}
			c = new Node(k,v);
			if(p->_key > k){
				p->_left = c;
			}else{
				p->_right = c;
			}
			c->_parent = p;

			while(p!=NULL){
				if(p->_left==c){
					p->_bf -= 1;
				}else{
					p->_bf += 1;
				}

				if(p->_bf == -1||
					p->_bf == 1){
					c = p;
					p = c->_parent;
				}else if(p->_bf == 0){
					break;
				}else if(p->_bf==-2||
					p->_bf == 2){
						if(p->_bf==-2&&c->_bf==-1){
							RotateR(p);
						}else if(p->_bf ==-2&&c->_bf==1){
							RotateLR(p);
						}else if(p->_bf == 2&&c->_bf==-1){
							RotateRL(p);
						}else{
							RotateL(p);
						}
						break;
				}else{
					assert(false);
					cout<<"平衡因子出错!key="<<p->_key<<endl;
				}
			}
		}
	}
	bool IsBalanceOP(){
		size_t depth = 0;
		return _IsBalanceOP(_root,depth);
	}
	void InOrderNonR(){
		stack<Node *>s;
		Node *cur = _root;
		while(cur!=NULL || !s.empty()){
			while(cur!=NULL){
				s.push(cur);
				cur = cur->_left;
			}

			Node *top = s.top();
			s.pop();
			cout<<top->_key<<" ";

			cur = top->_right;
		}
		cout<<endl;
	}
protected:
	bool _IsBalanceOP(Node *root,size_t &depth){
		if(root==NULL){
			depth = 0;
			return true;
		}
		size_t ld = 0;
		bool l = _IsBalanceOP(root->_left,ld);
		size_t rd = 0;
		bool r = _IsBalanceOP(root->_right,rd);
		if(l&&r){
			depth = ld>rd?ld+1:rd+1;
			return true;
		}
		return false;
	}
	void RotateL(Node *p){
		Node *sR = p->_right;
		Node *sRL = sR->_left;

		p->_right = sRL;
		if(sRL!=NULL){
			sRL->_parent = p;
		}

		Node *pp = p->_parent;
		if(pp!=NULL){
			if(pp->_left==p){
				pp->_left = sR;
			}else{
				pp->_right = sR;
			}
			sR->_parent = pp;
		}else{
			_root = sR;
			_root->_parent = NULL;
		}

		sR->_left = p;
		p->_parent = sR;

		p->_bf = sR->_bf = 0;
	}
	void RotateLR(Node *p){
		Node *sl = p->_left;
		Node *slr = sl->_right;
		int bf = slr->_bf;
		
		RotateL(sl);
		RotateR(p);

		if(bf==-1){
			slr->_bf = 0;
			p->_bf = 1;
		}else if(bf==0){
			slr->_bf = p->_bf = 0;	
		}else{
			slr->_bf = -1;
			p->_bf = 0;
		}
	}
	void RotateR(Node *p){
		Node *sl = p->_left;
		Node *slr = sl->_right;

		p->_left = slr;
		if(slr!=NULL){
			slr->_parent = p;
		}

		Node *pp = p->_parent;
		if(pp!=NULL){
			if(pp->_left == p){
				pp->_left = sl;
			}else{
				pp->_right = sl;
			}
			sl->_parent = pp;
		}else{
			_root = sl;
			_root->_parent = NULL;
		}

		sl->_right = p;
		p->_parent = sl;

		sl->_bf = p->_bf = 0;
	}
	void RotateRL(Node *p){
		Node *sr = p->_right;
		Node *srl = sr->_left;
		int bf = srl->_bf;

		RotateR(sr);
		RotateL(p);

		if(bf==-1){
			p->_bf = 1;
			sr->_bf = 0;
		}else if(bf ==0){
			p->_bf = sr->_bf = 0;
		}else{
			p->_bf = 0;
			sr->_bf = -1;
		}

		srl->_bf = 0;
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