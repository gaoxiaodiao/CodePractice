/*
*文件说明:二叉搜索树相关声明及实现(第二遍)
*作者:高小调
*日期:2017-01-17
*集成开发环境:Microsoft Visual Studio 2010 
*/
template<typename K>
struct BSTreeNode{
	BSTreeNode *_left;
	BSTreeNode *_right;
	const K _key;

	BSTreeNode(const K &k)
		,_left(NULL)
		,_right(NULL)
		,_key(k){}
};
template<typename K>
class BinarySearchTree{
public:
	typedef BSTreeNode<K> Node;
	
	BinarySearchTree()
	:_root(NULL){}

	~BinarySearch(){
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
	bool Insert(const K &k){
		if(_root==NULL){
			_root = new Node(k);
			return true;
		}
		Node *cur = Node;
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
		cur = new Node(k);
		if(k > parent->_key){
			parent->_right = cur;
		}else{
			parent->_left = cur;
		}
	}
	//从搜索二叉树中删除数据
	bool Remove(const K &k){
		Node *parent = NULL;
		Node *cur = _root;
		//找被删除数据的位置
		while(cur!=NULL){
			if(k > cur->_key){
				parent = cur;
				cur = cur->_right;
			}else if(k <cur->_key){
				parent = cur;
				cur = cur->_left
			}else{
				Node *pDel = cur;
				//被删除元素左子树为空
				if(cur->_left == NULL){
					//被删除元素为根节点
					if( parent == NULL){
						_root = cur->_right;
					}else{
						if(cur == parent->_left){
							parent->_left = cur->_right;
						}else{
							parent->_right = cur->_right;
						}
					}
					//被删除元素右子树为空
				}else if(cur->_right == NULL){
					//被删除元素为根节点
					if(parent==NULL){
						_root = cur->_left;
					}else{
						if(cur == parent->_left){
							parent->_left = cur->_left;
						}else{
							parent->_right = cur->_left;
						}
					}
					//被删除元素左右子树都不为空
				}else{

					parent = cur;					
					Node *subLR = cur->_left;
					while(subLR->_right!=NULL){
						parent = subLR;
						subLR = subL->_right;
					}
					cur = parent->_key;
					parent->_right = subLR->_left;
					pDel = subLR;
				}
				delete pDel;
				return true;
			}
		}
		return false;
	}
private:
	Node *_root;
};