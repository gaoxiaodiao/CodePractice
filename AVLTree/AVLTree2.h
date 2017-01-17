/*
*文件说明:AVL树相关声明及实现(二)
*作者:高小调
*日期:2017-01-15
*集成开发环境:Microsoft Visual Studio 2010 
*/
#pragma once
#include<assert.h>
#include<stack>
template<typename K,typename V>
struct AVLTreeNode{
	AVLTreeNode *_parent;
	AVLTreeNode *_left;
	AVLTreeNode *_right;
	int _bf;
	const K _key;
	V _value;

	AVLTreeNode(const K &k,const V &v)
		:_parent(NULL)
		,_left(NULL)
		,_right(NULL)
		,_bf(0)
		,_key(k)
		,_value(v){}
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
private:
	AVLTree(const AVLTree &);
	AVLTree &operator=(const AVLTree &);
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
public:
	bool Insert(const K &k,const V &v){
		if(_root == NULL){
			_root = new Node(k,v);
			return true;
		}else{
			Node *cur = _root;
			Node *parent = NULL;
			//找到被插入的位置
			while(cur!=NULL){
				if(k > cur->_key){
					parent = cur;
					cur = cur->_right;
				}else if(k < cur->_key){
					parent = cur;
					cur = cur->_left;
				}else{
					return false;
				}
			}
			//插入新节点
			cur = new Node(k,v);
			if(k < parent->_key){
				parent->_left = cur;
			}else{
				parent->_right = cur;
			}
			cur->_parent = parent;
			//调节平衡因子
			while( parent!=NULL ){
				if(parent->_left == cur){
					parent->_bf -= 1;
				}else{
					parent->_bf += 1;
				}

				if(parent->_bf == 0){
					break;
				}else if(parent->_bf==-1||
					parent->_bf == 1){
					cur = parent;
					parent = cur->_parent;
				}else if(parent->_bf==2 ||
					parent->_bf ==-2){
					if(parent->_bf == 2&&
						cur->_bf == 1 ){
						//左旋
							RotateL(parent);
					}else if(parent->_bf ==2&&
						cur->_bf == -1){
						//右左旋
							RotateRL(parent);
					}else if(parent->_bf ==-2&&
						cur->_bf == 1){
						//左右旋
							RotateLR(parent);
					}else{
						//右旋
						RotateR(parent);
					}
				}else{
					std::cout<<"平衡因子异常"<<std::endl;
					assert(false);
				}
			}
			return true;
		}
		return false;
	}

	//左旋
	void RotateL(Node *parent){
		Node *subR = parent->_right;
		Node *subRL = subR->_left;
		Node *pParent = parent->_parent;

		parent->_right = subRL;
		if(subRL!=NULL){
			subRL->_parent = parent->_right;
		}

		if(pParent==NULL){
			_root = subR;
			_root->_parent =NULL;
		}else{
			if(pParent->_left == parent){
				pParent->_left = subR;
			}else{
				pParent->_right = subR;
			}
			subR->_parent = pParent;
		}

		subR->_left = parent;
		parent->_parent = subR;

		parent->_bf = 0;
		subR->_left = 0;
	}
	void RotateLR(Node *parent){
		Node *subL = parent->_left;
		Node *subLR = subL->_right;
		int bf = subLR->_bf;
		RotateL(subL);
		RotateR(parent);
		if(bf == -1){
			parent->_bf = 1;
			subL->_bf = 0;
		}else if(bf == 0){
			parent->_bf = subL->_bf = 0;
		}else{
			parent->_bf = 0;
			subL->_bf = -1;
		}
		subLR->_bf = 0;
	}
	void RotateRL(Node *parent){
		Node *subR = parent->_right;
		Node *subRL = subR->_left;
		int bf = subRL->_bf;
		RotateR(subR);
		RotateL(parent);
		if(bf==-1){
			parent->_bf = 0;
			subR->_bf = 1;
		}else if(bf == 0 ){
			parent->_bf = subR->_bf = 0;
		}else{
			parent->_bf = -1;
			subR->_bf = 0;
		}
		subRL->_bf = 0;
	}
	//右旋
	void RotateR(Node *parent){
		Node *subL = parent->_left;
		Node *subLR = subL->_right;
		Node *pParent = parent->_parent;

		parent->_left = subLR;
		if(subLR!=NULL){
			subLR->_parent = parent;
		}

		if(pParent==NULL){
			_root = subL;
			_root->_parent = NULL;
		}else{
			if(pParent->_left == parent){
				pParent->_left = subL;
			}else{
				pParent->_right = subL;
			}
			subL->_parent = pParent;
		}
	
		subL->_right = parent;
		parent->_parent = subL;

		parent->_bf = 0;
		subL->_bf = 0;
	}
	
	size_t _Depth(Node *root){
		if(root==NULL){
			return 0;
		}
		size_t l = _Depth(root->_left);
		size_t r = _Depth(root->_right);
		return l>r?l+1:r+1;
	}

	bool IsBalance(){
		return _IsBalance(_root);
	}
	bool _IsBalance(Node *root){
		if(root==NULL){
			return true;
		}
		size_t l = _Depth(root->_left);
		size_t r = _Depth(root->_right);
		int diff = l-r;
		if(diff<=1 ||diff>=-1){
			return _IsBalance(root->_left)&&
				_IsBalance(root->_right);
		}
		return false;
	}
	bool IsBalanceOP(){
		size_t depth = 0;
		return _IsBalanceOP(_root,depth);
	}
	bool _IsBalanceOP(Node *root,size_t &depth){
		if(root==NULL){
			depth = 0;
			return true;
		}
		size_t ld = 0;
		bool l = _IsBalanceOP(root->_left,ld);
		size_t rd = 0;
		bool r = _IsBalanceOP(root->_right,rd);
		if(l && r){
			int diff = ld -rd;
			if(diff<=1 || diff >=-1){
				depth = ld>rd?ld+1:rd+1;
				return true;
			}
		}
		return false;
	}
	void InOrderNonR(){
		std::stack<Node *> s;
		Node *cur = _root;
		while(cur!=NULL  || !s.empty()){
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
private:
	Node *_root;
};
//总结:
//脑袋还是有点乱,感觉再来一遍效果会更好....
//插入时,又栽跟头在同一块地方了!!!