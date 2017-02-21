/*
*�ļ�˵��:AVL��������ʵ��(���ı�)
*����:��С��
*����:2017-01-30
*���ɿ�������:Microsoft Visual Studio 2010 
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
		//�Ҳ���λ��
		while(cur!=NULL){
			if(key > cur->_key){
				cur = cur->_right;
			}else if(key < cur->_key){
				cur = cur->_left;
			}else{
				//keyֵ��ͻ,����ʧ��
				return false;
			}
		}
		//�����½ڵ�
		cur = new Node(key,value);
		if(key > parent->_key){
			parent->_right = cur;
		}else{
			parent->_left = cur;
		}
		//����ƽ������
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
						//����
					}else if(parent->_bf == -2&&
						cur->_bf == 1){
						//����
					}else if(parent->_bf == 2 &&
						cur->_bf == -1){
						//����
					}else{//parent->_bf == 2 && cur->_bf ==1
						//����
					}
			}else if(parent->_bf == -1 ||
				parent->_bf == 1){
				cur = parent;
				parent = cur->_parent;
			}else if(parent->_bf == 0){
				break;
			}else{
				std::cout<<"ƽ�����ӳ���key="<<parent->_key<<std::endl;
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
