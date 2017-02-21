/*
*文件说明:AVLTree相关声明及实现
*作者:高小调
*日期:2017-02-13
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
	const K _key;
	V _value;
	int _bf;

	AVLTreeNode(const K &k,const V &v)
		:_parent(NULL)
		,_left(NULL)
		,_right(NULL)
		,_key(k)
		,_value(v)
		,_bf(0){}
};

template<typename K,typename V>
class AVLTree{
public:
	typedef AVLTreeNode<K,V> Node;
	AVLTree():_root(NULL){}
	~AVLTree(){}
public:
	
	bool Insert(const K &k,const V &v){
		if(_root==NULL){
			_root = new Node(k,v);
		}else{
			Node *parent = NULL;
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
					//重复key值,返回假
					return false;
				}
			}
			//2.插入数据
			cur = new Node(k,v);
			if(parent->_key > k){
				parent->_left = cur;
			}else{
				parent->_right = cur;
			}
			cur->_parent = parent;
			//3.调节平衡因子

			while(parent!=NULL){
				if(parent->_left == cur){
					parent->_bf -= 1;
				}else{
					parent->_bf += 1;
				}
				if(parent->_bf == -1 ||
					parent->_bf == 1){
					//还需继续向上调整
						cur = parent;
						parent = parent->_parent;
				}else if(parent->_bf == 0){
					//不需要调整
					break;
				}else if(parent->_bf == 2||
					parent->_bf == -2){
					//需要进行旋转操作
						if(parent->_bf == -2&&
							cur->_bf == -1){
							//右旋
							RotateR(parent);
						}else if(parent->_bf == -2&&
							cur->_bf == 1){
							//左右双旋
							RotateLR(parent);
						}else if(parent->_bf == 2 &&
							cur->_bf == -1){
							//右左双旋
							RotateRL(parent);
						}else{
							//左旋
							RotateL(parent);
						}
						break;
				}else{
					//平衡因子出错
					std::cout<<"平衡因子出错 key = "<<parent->_key<<std::endl;
					assert(false);
				}

			}
		}
		return true;
	}
	
	void InOrderNonR(){
		stack<Node *> s;
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
	/*
	void InOrderNonR(){
		stack<Node *> s;
		Node *cur = _root;

		while(cur!=NULL || !s.empty()){
			while(cur!=NULL){
				s.push(cur);
				cur = cur->_left;
			}

			Node *top = s.top();
			s.pop();
			std::cout<<top->_key<<" ";

			cur = top->_right;
		}
		std::cout<<std::endl;
	}
	*/
	size_t Depth(){
		return _Depth(_root);
	}
	bool IsBalance(){
		return _IsBalance(_root);
	}
	bool IsBalanceOP(){
		size_t depth = 0;
		return _IsBalanceOP(_root,depth);
	}
protected:

	/*
	bool _IsBalanceOP(Node *root,size_t &depth){
		if(root==NULL){
			depth = 0;
			return true;
		}
		size_t leftDepth = 0;
		size_t rightDepth = 0;
		bool left = _IsBalanceOP(root->_left,leftDepth);
		bool right = _IsBalanceOP(root->_right,rightDepth);
		if(left && right){
			int sub = leftDepth - rightDepth;
			if(sub <= 1 || sub>= -1){
				depth = leftDepth>rightDepth?leftDepth+1:rightDepth+1;
				return true;
			}
		}
		return false;
	}
	bool _IsBalanceOP(Node *root,size_t &depth){
		if(root==NULL){
			depth = 0;
			return true;
		}
		size_t ld = 0;	//leftdepth 左子树深度
		size_t rd = 0;	//rightdepth 右子树深度
		bool l = _IsBalanceOP(root->left,ld);	//l,左子树是否平衡
		bool r = _IsBalanceOP(root->_right,rd);	//r,右子树是否平衡
		if(l && r){
			int sub = ld - rd;
			if(sub<=1 || sub>=-1){
				depth = ld>rd?ld+1:rd+1;
				return true;
			}
		}
		return false;
	}
	*/
	bool _IsBalanceOP(Node* root,size_t &depth){
		if(root == NULL){
			depth = 0;
			return true;
		}
		size_t ld = 0;
		size_t rd = 0;
		bool l = _IsBalanceOP(root->_left,ld);
		bool r = _IsBalanceOP(root->_right,rd);
		if(l && r){
			int sub = ld - rd;
			if(sub<=1 || sub>=-1){
				depth = ld>rd?ld+1:rd+1;
				return true;
			}
		}
		return false;
	}
	
	bool _IsBalance(Node *root){
		if(root==NULL){
			return true;
		}
		size_t leftD = _Depth(root->_left);
		size_t rightD = _Depth(root->_right);
		int sub = rightD - leftD;
		if(sub!=root->_bf){
			std::cout<<"平衡因子异常 key="<<root->_key<<std::endl;
		}
		if(sub > 1 || sub < -1){
			return false;
		}
		return _IsBalance(root->_left)&&_IsBalance(root->_right);
	}
	
	size_t _Depth(Node * root){
		if(root==NULL){
			return 0;
		}
		size_t leftD = _Depth(root->_left);
		size_t rightD = _Depth(root->_right);
		return leftD>rightD?leftD+1:rightD+1;
	}

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

		parent->_bf = 0;
		subL->_bf = 0;
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

		parent->_bf = 0;
		subR->_bf = 0;
	}
	
	void RotateRL(Node *parent){
		Node *subR = parent->_right;
		Node *subRL = subR->_left;	
		int bf = subRL->_bf;

		RotateR(subR);
		RotateL(parent);


		//        subRL 根节点
		//parent 左孩子    subR 右孩子
		if(bf == -1){
			parent->_bf = 0;
			subR->_bf = 1;
		}else if(bf == 0){
			subR->_bf = parent->_bf = 0;
		}else{
			parent->_bf = -1;
			subR->_bf = 0;
		}

		subRL->_bf = 0;
	}
	void RotateLR(Node *parent){
		Node *subL = parent->_left;
		Node *subLR = subL->_right;
		int bf = subLR->_bf;
		
		RotateL(subL);
		RotateR(parent);

		//		 subLR 根节点
		//subL 左孩子    parent 右孩子
		if(bf == -1){
			subL->_bf = 0;
			parent->_bf = 1;
		}else if(bf == 0){
			subL->_bf = parent->_bf = 0;
		}else{
			subL->_bf = -1;
			parent->_bf = 0;
		}
		subLR->_bf = 0;
	}
private:
	Node *_root;
};
