/*
*文件说明:AVL树相关声明及实现(一)
*作者:高小调
*日期:2017-01-13
*集成开发环境:Microsoft Visual Studio 2010 
*/
#pragma once
#include<assert.h>
#include<stack>
//AVL树节点
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
//AVL树相关函数定义及实现
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
	//插入
	bool Insert(const K &k,const V &v){
		//判断树是否为空
		if( _root==NULL ){
			_root = new Node(k,v);
			return true;
		}
		Node *cur = _root;
		Node *parent = NULL;

		//找要插入的位置
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

		//插入数据
		cur = new Node(k,v);
		if(k > parent->_key){
			parent->_right = cur;
		}else{
			parent->_left = cur;
		}	
		cur->_parent = parent;

			
		//调整平衡因子
		while(parent!=NULL){
			if(k==4){
				int a = 10;
			}
			if(parent->_left == cur){
				parent->_bf -= 1;
			}else{
				parent->_bf += 1;
			}

			if(parent->_bf == 0){
				//该树已经平衡,不需要再调整
				break;
			}else if(parent->_bf == 1 
				||parent->_bf == -1) {
				//当前节点已经平衡,判断父节点是否平衡
				cur = parent;
				parent = cur->_parent;
			}else if(parent->_bf== 2 
				||parent->_bf == -2){
				//旋转操作
					if(parent->_bf == 2 
						&&cur->_bf == -1){
						//右左旋
						RotateRL(parent);
					}else if(parent->_bf == 2
						&&cur->_bf == 1){
						//左旋
						RotateL(parent);
					}else if(parent->_bf == -2 
						&&cur->_bf ==-1){
						//右旋
						RotateR(parent);
					}else if(parent->_bf ==-2
						&&cur->_bf == 1){
						//左右旋
						RotateLR(parent);
					}
					break;
			}else{
				cout<<"平衡因子异常 key ="<<k<<",value="<<v<<endl;
				assert(false);
			}
		}
		return true;
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
		if(bf == -1){
			parent->_bf = 0;
			subR->_bf = 1;
		}else if(bf == 0){
			parent->_bf = subR->_bf = 0;	
		}else{
			parent->_bf = -1;
			subR->_bf = 0;
		}
		subRL->_bf = 0;
	}
	void RotateL(Node *parent){
		Node *subR = parent->_right;
		Node *subRL = subR->_left;
		Node *pParent = parent->_parent;
		
		parent->_right = subRL;
		if(subRL!=NULL){
			subRL->_parent = parent;
		}

		if(pParent!=NULL){
			if(pParent->_left == parent){
				pParent->_left = subR;
			}else{
				pParent->_right = subR;
			}
			subR->_parent = pParent;
		}else{
			_root = subR;
			_root->_parent = NULL;
		}

		subR->_left = parent;
		parent->_parent = subR;

		subR->_bf = 0;
		parent->_bf = 0;
	}
	
	void RotateR(Node *parent){
		Node *subL = parent->_left;
		Node *subLR = subL->_right;
		Node *pParent = parent->_parent;

		parent->_left = subLR;
		if(subLR!=NULL){
			subLR->_parent = parent;
		}

		if(pParent!=NULL){
			if(pParent->_left == parent){
				pParent->_left = subL;
			}else{
				pParent->_right = subL;
			}
			subL->_parent = pParent;
		}else{
			_root = subL;
			_root->_parent = NULL;
		}

		subL->_right = parent;
		parent->_parent =  subL;
		
		subL->_bf = 0;
		subL->_bf = 0;
	}
	void InOrder(){
		_InOrder(_root);
		cout<<endl;
	}
	void _InOrder(Node *root){
		if(root==NULL){
			return ;
		}
		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
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
	bool IsBalance(){
		return _IsBalance(_root);
	}

	bool IsBalanceOP(){
		size_t depth = 0;
		return _IsBalanceOP(_root,depth);
	}
	bool _IsBalanceOP(Node *root,size_t depth){
		if(root==NULL){
			depth = 0;
			return true;
		}

		size_t leftDepth = 0;
		size_t rightDepth = 0;
		bool left = _IsBalanceOP(root->_left,leftDepth);
		bool right = _IsBalanceOP(root->_right,rightDepth);
		if(left && right){
			int diff = leftDepth - rightDepth;
			if(diff<=1 || diff>=-1){
				depth = leftDepth>rightDepth?leftDepth+1:rightDepth+1;
				return true;
			}
		}

		return false;
	}

	bool _IsBalance(Node *root){
		if(root==NULL){
			return true;
		}
		size_t leftDepth = _Depth(root->_left);
		size_t rightDepth = _Depth(root->_right);

		if((rightDepth-leftDepth) != root->_bf)
		{
			cout<<"平衡因子异常："<<root->_key<<endl;
			//return false;
		}

		int sub = leftDepth - rightDepth;
		if(sub > 1 || sub< -1){
			return false;
		}
		return (_IsBalance(root->_left) && _IsBalance(root->_right));
	}

	size_t Depth(){
		return _Depth(_root);	
	}

	size_t _Depth(Node *root){
		if(root==NULL){
			return 0;
		}
		size_t ldepth = _Depth(root->_left);
		size_t rdepth = _Depth(root->_left);
		return ldepth>rdepth?ldepth+1:rdepth+1;
	}
private:
	Node * _root;
};
/*
总结:
	这块东西,应该是我接触数据结构以来,觉得最难的地方.
	一边敲代码,还得一边左旋、右旋、双旋的图...
	多敲几次后,在继续敲代码的过程中,脑袋里就会浮现出相应图...
	果然,要想对这块特别熟练,没有捷径,就是得不断的练习...
*/
/*
	//插入数据(非常容易犯错误的点,在这里栽了两次跟头)
	cur = new Node(k,v);
	if(parent->_left == NULL){
		parent->_left = cur;
	}else{
		parent->_right = cur;
	}
	cur->_parent = parent;
*/

//敲了N次的左旋,右旋,双旋...

/*
	void RotateL(Node *parent){
		Node *subR = parent->_right;
		Node *subRL = subR->_left;
		Node *pParent = parent->_parent;

		parent->_right = subRL;
		if(subRL!=NULL){
			subRL->_parent = parent;
		}

		if(pParent!=NULL){
			if(pParent->_left == parent){
				pParent->_left = subR;
			}else{
				pParent->_right = subR;
			}
			subR->_parent = pParent;
		}

		subR->_left = parent;
		parent->_parent = subR;

		subR->_bf = 0;
		parent->_bf =0;
	}
	*/
	/*
	void RotateL(Node *parent){
		Node *subR = parent->_right;
		Node *subRL = subR->_left;
		Node *pParent = parent->_parent;

		parent->_right = subRL;
		if(subRL!=NULL){
			subRL->_parent = parent;
		}

		if(pParent!=NULL){
			if(pParent->_left == parent){
				pParent->_left = subR;
			}else{
				pParent->_right = subR;
			}
			subR->_parent = pParent;
		}else{
			_root = subR;
			_root->_parent = NULL;
		}
		
		subR->_left = parent;
		parent->_parent = subR;

		subR->_bf = 0;
		parent->_bf = 0;

	}
	*/
	/*
	void RotateL(Node *parent){
		Node *subR = parent->_right;
		Node *subRL = subR->_left;
		Node *pParent = parent->_parent;

		parent->_right = subRL;
		if(subRL!=NULL){
			subRL->_parent = parent;
		}

		if(pParent!=NULL){
			if(pParent->_left == parent){
				pParent->_left = subR;
			}else{
				pParent->_right = subR;
			}
			subR->_parent = pParent;
		}

		subR->_left = parent;
		parent->_parent = subR;

		subR->_bf = 0;
		parent->_bf =0;
	}*/
	/*
	void RotateL(Node *parent){
		Node *subR = parent->_right;
		Node *subRL = subR->_left;
		Node *pParent = parent->_parent;

		parent->_right = subRL;
		if(subRL!=NULL){
			subRL->_parent = parent;
		}

		if(pParent!=NULL){
			if(pParent->_left==parent){
				pParent->_left = subR;
			}else{
				pParent->_right = subR;
			}
			subR->_parent = pParent;
		}
	
		subR->_left = parent;
		parent->_parent = subR;

		subR->_bf = 0;
		parent->_bf = 0;

	}*/
	/*
	void RomateL(Node *parent){

		Node *subR = parent->_right;
		Node *subRL = subR->_left;
		Node *pprent = parent->_parent;

		parent->_right = subRL;
		if(subRL!=NULL){
			subRL->_parent = parent;
		}
		
		if(pprent!=NULL){
			if(pprent->_left == parent){
				pprent->_left = subR;	
			}else{
				pprent->_right = subR;
			}
			subR->_parent = pprent;
		}else{
			_root = subR;
			_root->_parent = NULL;
		}
		
		subR->_left = parent;
		parent->_parent = subR;
		
		subR->_bf = 0;
		parent->_bf = 0;

	}
	*/
	/*2
	void RomateR(Node * parent){

		Node *subL = parent->_left;
		Node *subLR = subL->_right;
		Node *pprent = parent->_parent;
		
		//处理父节点与
		parent->_left = subLR;
		if(subLR!=NULL)
			subLR->_parent = parent->_left;
		
		//新父节点与父父节点的交接仪式
		if(pprent!=NULL){
			if(pprent->_left == parent){
				pprent->_left = subL;
			}else{
				pprent->_right = subL;
			}
			subL->_parent = pprent;
		}else{
			_root = subL;
			_root->_parent = NULL;
		}
		
		//新父节点与父节点交接仪式
		subL->_right = parent;
		parent->_parent = subL;

		parent->_bf = 0;
		subL->_bf = 0;
	}
	*/
	/*3
	void RotateR(Node *parent){
		Node *subL = parent->_left;
		Node *subLR = subL->_right;
		Node *pParent = parent->_parent;

		parent->_left = subLR;
		if(subLR!=NULL){
			subLR->_parent = parent;
		}

		if(pParent!=NULL){
			if(pParent->_left == parent){
				pParent->_left = subL;
			}else{
				pParent->_right = subL;
			}
			subL->_parent = pParent;
		}else{
			_root = subL;
			_root->_parent = NULL;
		}

		subL->_right = parent;
		parent->_parent = subL;

		subL->_bf = 0;
		parent->_bf =0;
	}
	*/
	/*4
	void RotateR(Node *parent){
		Node *subL = parent->_left;
		Node *subLR = subL->_right;
		Node *pParent = parent->_parent;

		parent->_left = subLR;
		if(subLR!=NULL){
			subLR->_parent = parent;
		}

		if(pParent!=NULL){
			if(pParent->_left == parent){
				pParent->_left = subL;
			}else{
				pParent->_right = subL;
			}
			subL->_parent = pParent;
		}else{
			_root = subL;
			_root->_parent = NULL;
		}

		subL->_right = parent;
		parent->_parent = subL;

		parent->_bf = 0;
		subL->_bf = 0;

	}
	*/
	/*5
	void RotateR(Node *parent){
		Node *subL = parent->_left;
		Node *subLR = subL->_right;
		Node *pParent = parent->_parent;

		parent->_left = subLR;
		if(subLR!=NULL){
			subLR->_parent = parent;
		}

		if(pParent!=NULL){
			if(parent == pParent->_left){
				pParent->_left = subL;
			}else{
				pParent->_right = subL;
			}
			subL->_parent = pParent;
		}else{
			_root = subL;
			_root->_parent = NULL;
		}

		subL->_right = parent;
		parent->_parent = subL;
		
		parent->_bf = 0;
		subL->_bf = 0;
	}6
	*/
	/*
	void RotateR(Node *parent){
		Node *subL = parent->_left;
		Node *subLR = subL->_right;
		Node *pParent = parent->_parent;

		parent->_left = subLR;
		if(subLR!=NULL){
			subLR->_parent = parent;
		}

		if(pParent!=NULL){
			if(pParent->_left == parent){
				pParent->_left = subL;
			}else{
				pParent->_right = subL;
			}
			subL->_parent = pParent;
		}else{
			_root = subL;
			_root->_parent =NULL;
		}

		subL->_right = parent;
		parent->_parent = subL;

		subL->_bf = 0;
		parent->_bf = 0;

	}*/
/*
	void RotateLR(Node *parent){
		Node *subL = parent->_left;
		Node *subLR = subL->_right;
		int bf = subLR->_bf;
		RotateR(subL);
		RotateL(parent);
		if(bf == 1){
			parent->_bf = 0;
			subL->_bf = -1;
		}else if(bf = -1){
			parent = 1;
			subL->_bf = 0;
		}else{
			parent->_bf = subL->_bf = 0;
		}

		subLR->_bf = 0;
	}
	*/
	/*
	void RomateLR(Node *parent){
		Node *subL = parent->_left;
		Node *subLR = subL->_right;
		int bf = subLR->_bf;
		RotateL(parent->_left);
		RotateR(parent);
		if(bf == -1){
			parent->_bf = 1;
			subL->_bf = 0;
		}else if(bf == 1){
			parent->_bf = 0;
			subL->_bf = -1;
		}else{
			subL->_bf = parent->_bf = 0;
		}
		subL->_bf = 0;
	}
	
	void RomateRL(Node *parent){
		Node *subR = parent->_right;
		Node *subRL = subR->_left;
		int bf = subRL->_bf;
		RotateR(parent->_right);
		RotateL(parent);
		if(bf == -1){
			parent->_bf = 0;
			subR->_bf = 1;
		}else if(bf == 0){
			parent->_bf = subR->_bf = 0;
		}else{
			parent->_bf = -1;
			subR->_bf= 0;
		}

		subRL->_bf = 0;

	}*/
	/*
	void RotateRL(Node *parent){
		Node *subR = parent->_right;
		Node *subRL = subR->_left;
		int bf = subRL->_bf;
		RotateR(subR);
		RotateL(parent);
		if(bf == -1){
			parent->_bf = 0;
			subR->_bf = 1;
		}else if(bf == 0){
			parent->_bf = subR->_bf = 0;
		}else{
			parent->_bf = -1;
			subR->_bf = 0;
		}
	}
	*/
/*
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
	*/