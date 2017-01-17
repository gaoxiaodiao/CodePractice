/*
*文件说明:二叉平衡树相关声明及实现(三)
*作者:高小调
*日期:2017-01-16
*集成开发环境:Microsoft Visual Studio 2010 
*/
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
	AVLTree()
		:_root(NULL){}
	~AVLTree(){
		_Destory(_root);
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
public:
	bool Insert(const K& k,const V& v){
		if(_root==NULL){
			_root = new Node(k,v);
			return true;
		}

		//寻找插入位置
		Node *cur = _root;
		Node *parent = NULL;
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

		//调节平衡因子
		while(parent!=NULL){
			if(parent->_left == cur){
				parent->_bf -= 1;
			}else{
				parent->_bf += 1;
			}
			if(parent->_bf == 0){
				break;
			}else if(parent->_bf == -1 ||
				parent->_bf == 1){
				cur = parent;
				parent = cur->_parent;
			}else if(parent->_bf == 2||
				parent->_bf == -2){
					if(parent->_bf == -2 &&
						cur->_bf == -1){
							RotateR(parent);
						//右旋
					}else if(parent->_bf ==-2 &&
						cur->_bf == 1){
						//左右旋
							RotateLR(parent);
					}else if(parent->_bf == 2 &&
						cur->_bf ==-1 ){
						//左右旋
							RotateRL(parent);
					}else{
						//左旋
						RotateL(parent);
					}
			}else{
				std::cout<<"平衡因子出错!"<<endl;
				assert(false);
			}
		}
		return true;
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
		parent->_parent = subL;

		parent->_bf = 0;
		subL->_bf = 0;
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

		parent->_bf = 0;
		subR->_bf = 0;
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
		}else if(bf == 1){
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
		int bf = subR->_bf;
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
	void InOrderNonR(){
		std::stack<Node *> s;
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
	size_t _Depth(Node *root){
		if(root==NULL){
			return 0;
		}
		size_t left = _Depth(root->_left);
		size_t right = _Depth(root->_right);
		return left>right?left+1:right+1;
	}
	bool IsBalance(){
		return _IsBalance(_root);
	}

	bool _IsBalance(Node *root){
		if(root==NULL){
			return true;
		}
		size_t left = _Depth(root->_left);
		size_t right = _Depth(root->_right);
		int diff = left - right;
		if(diff<=1 || diff>= -1){
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
		size_t leftD = 0;
		bool l =_IsBalanceOP(root->_left,leftD);
		size_t rightD = 0;
		bool r = _IsBalanceOP(root->_right,rightD);
		if(l && r){
			int diff = leftD - rightD;
			if(diff<=1 || diff >=-1){
				depth = leftD>rightD?leftD+1:rightD+1;
				return true;
			}
		}
		return false;

	}

private:
	Node *_root;
};
//总结:
//单旋双旋貌似没什么问题了
//虽然不像堆那么熟练,但我觉得至少及格了.