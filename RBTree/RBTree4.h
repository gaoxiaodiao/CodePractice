/*
*文件说明:红黑树相关声明及实现
*作者:高小调
*日期:2017-02-16
*集成开发环境:Microsoft Visual Studio 2010 
*/
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

	RBTreeNode(const K& key,const V &value)
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
public:
	bool Insert(const K &key,const V &value){
		if(_root==NULL){
			_root = new Node(key,value);
			_root->_color = BLACK;
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

			while(parent!=NULL&&parent->_color == RED){
				Node *grandfather = parent->_parent;
				if(parent==grandfather->_left){
					Node *uncle = grandfather->_right;
					if(uncle!=NULL&&uncle->_color==RED){
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
					if(uncle!=NULL&&uncle->_color==RED){
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
			if(pparent->_left== parent){
				pparent->_left = subL;
			}else{
				pparent->_right = subL;
			}
			subL->_parent = pparent;
		}else{
			_root = subL;
			_root->_parent=NULL;
		}

		subL->_right = parent;
		parent->_parent = subL;
	}
	bool IsBalance(){
		Node *cur = _root;
		size_t num = 0;
		size_t k = 0;
		//计算最左通路黑色节点个数
		while(cur!=NULL){
			if(cur->_color==BLACK){
				++k;
			}
			cur = cur->_left;
		}
		return _CheckColorAndBlackNum(_root,num,k);
	}
	bool _CheckColorAndBlackNum(Node *root,size_t num,const size_t k){
		if(root==NULL){
			return true;
		}
		//更新黑色节点个数
		if(root->_color==BLACK){
			++num;
		}
		//检查颜色是否正确
		if(root->_color==RED&&root->_parent->_color==RED){
			return false;
		}
		//检查黑色节点个数是否正确
		if(root->_left==NULL&&root->_right==NULL&&num!=k){
			return false;
		}
		return _CheckColorAndBlackNum(root->_left,num,k)&&
			_CheckColorAndBlackNum(root->_right,num,k);
	}
private:
	Node *_root;
};
/*
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
public:
	bool Insert(const K &key,const V &value){
		if(_root==NULL){
			_root = new Node(key,value);
			_root->_color = BLACK;
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
					if(uncle!=NULL &&uncle->_color==RED){
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
			_root->_color = BLACK;
			return true;
		}
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
		Node *cur = _root;
		size_t num  = 0;
		size_t k = 0;
		while(cur!=NULL){
			if(cur->_color==BLACK){
				++k;
			}
			cur = cur->_left;
		}
		return _CheckColor(_root)&&
			_CheckBlackNum(_root,num,k);
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
	bool _CheckBlackNum(Node *root,size_t num,size_t k){
		if(root==NULL){
			return true;
		}
		if(root->_color==BLACK){
			++num;
		}
		if(root->_left == NULL &&root->_right==NULL&&num!=k){
			return false;
		}
		return _CheckBlackNum(root->_left,num,k)&&
			_CheckBlackNum(root->_right,num,k);

	
	}
private:
	Node *_root;
};
*/