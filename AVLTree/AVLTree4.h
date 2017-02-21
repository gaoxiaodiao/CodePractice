/*
*文件说明:AVL树声明及实现(第四遍)
*作者:高小调
*日期:2017-01-30
*集成开发环境:Microsoft Visual Studio 2010 
*/
template<typename K,typename V>
struct AVLTreeNode{
	AVLTreeNode* _left;
	AVLTreeNode* _right;
	AVLTreeNode* _parent;
	const K _key;
	V _value;
	int _bf;
	AVLTreeNode(const K key,const V value)
		:_left(NULL)
		,_right(NULL)
		,_parent(NULL)
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
public:
	bool Insert(const K key,const V value){
		Node *parent = NULL;
		Node *cur = _root;
		//找插入位置
		while(cur!=NULL){
			if(key > cur->_key){
				cur = cur->_right;
			}else if(key < cur->_key){
				cur = cur->_left;
			}else{
				//key值冲突,插入失败
				return false;
			}
		}
		//插入新节点
		cur = new Node(key,value);
		if(key > parent->_key){
			parent->_right = cur;
		}else{
			parent->_left = cur;
		}
		//调整平衡因子
		while(parent!=NULL){
			if(parent->_left == cur){
				parent->_bf -= 1;
			}else{
				parent->_bf += 1;
			}
			if(parent->_bf == -2 ||
				parent->_bf == 2){
					if(parent->_bf == -2&&
						cur->_bf == -1){
						//右旋
					}else if(parent->_bf == -2&&
						cur->_bf == 1){
						//左右
					}else if(parent->_bf == 2 &&
						cur->_bf == -1){
						//右左
					}else{//parent->_bf == 2 && cur->_bf ==1
						//左旋
					}
			}else if(parent->_bf == -1 ||
				parent->_bf == 1){
				cur = parent;
				parent = cur->_parent;
			}else if(parent->_bf == 0){
				break;
			}else{
				std::cout<<"平衡因子出错key="<<parent->_key<<std::endl;
				assert(false);
			}
		}
		return true;
	}
	void RomateL(Node *parent){
		Node *subR = parent->_right;
		Node *subRL = subR->_left;
		Node *pParent = parent->_parent;
		
		parent->_right = subRL;
		if(subRL!=NULL){
			subRL->_parent = parent;
		}

		if(pParent!=NULL){
			if(pParent->_left == parent){
				pParent->_left == subR;
			}else{
				pParent->_right == subR;
			}
			subR->_parent == pParent;
		}else{
			_root = subR;
			_root->_parent = NULL;
		}

		subR->_left = parent;
		parent->_parent = subR;

		parent->_bf = 0;
		subR->_bf = 0;
	}
	void RomateR(Node *parent){
		Node *pParent = parent->_parent;
		Node *subL = parent->_left;
		Node *subLR = subL->_right;

		parent->_right = subL;
		if(subL!=NULL){
			subL->_parent = parent;	
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
			subL->_parent = NULL;
		}

		subL->_right = parent;
		parent->_parent = subL;

		parent->_bf = 0;
		subL->_bf = 0;
	}
	void RomateRL(Node *parent){
		Node *subR = parent->_right;
		Node *subRL = subR->_left;
		int bf = subRL->_bf;
		RomateR(subR);
		RomateL(parent);
	}
private:
	Node *_root;
};
