/*
*文件说明:二叉搜索树
*作者:高小调
*日期:2017-01-08
*集成开发环境:Microsoft Visual Studio 2010 
*/
template<typename K>
struct BinarySearchTreeNode{
	BinarySearchTreeNode * _left;
	BinarySearchTreeNode * _right;
	K _key;
	
	BinarySearchTreeNode(const K & key)
		:_left(NULL)
		,_right(NULL)
		,_key(key){}
};

template<typename K>
class BinarySearchTree{
	typedef BinarySearchTreeNode<K> Node;
public:
	BinarySearchTree()
		:_root(NULL){}
	//插入数据
	bool Insert(const K &key){
		//树中无数据
		if(_root == NULL){
			_root = new Node(key);
			return true;
		}
		Node *parent = NULL;
		Node *cur = _root;
		while(cur!=NULL){
			if(key > cur->_key){
				parent = cur;
				cur = cur->_right;
			}else if(key < cur->_key){
				parent = cur;
				cur = cur->_left;
			}else{
				return false;
			}
		}
		if(key > parent->_key){
			parent->_right = new Node(key);
		}else{
			parent->_left = new Node(key);
		}
		return true;
	}
	//中序遍历
	void InOrder(){
		_InOrder(_root);
		cout<<endl;
	}
	bool Remove(const K &key){
		if(_root==NULL){
			return false;
		}
		Node *parent = NULL;
		Node *cur = _root;
		while(cur!=NULL){
			if(key > cur->_key){
				parent = cur;
				cur = cur->_right;
			}else if(key < cur->_key){
				parent = cur;
				cur = cur->_left;
			}else{
				//被删除节点没有左子树
				if(cur->_left == NULL){
					if(parent==NULL){
						//删除一个没有左子树的根节点
						parent = cur;
						//没有右子树
						if(cur->_right==NULL){
							delete cur;
							_root = NULL;
							return true;
						}
						Node *subCur = cur->_right;
						while(subCur->_left!=NULL){
							parent = subCur;
							subCur = subCur->_left;
						}//找根节点右孩子的最左节点
						if(subCur == cur->_right){
							cur->_key = subCur->_key;
							parent->_right = subCur->_right;
						}else{
							cur->_key = subCur->_key;
							parent->_left = subCur->_right;
						}
						delete subCur;
						subCur = NULL;
						return true;
					}

					//被删除节点为父亲的左子树
					if(parent->_left == cur){
						parent->_left = cur->_right;
					}else{
						parent->_right = cur->_right;
					}//被删除节点为父亲的右子树
					delete cur;
					cur = NULL;
					return true;

				//被删除节点没有右子树
				}else if(cur->_right == NULL){
					//该节点为根节点
					if(parent == NULL){
						parent = cur;
						Node* subCur = cur->_left;
						while(subCur->_right!=NULL){
							parent = subCur;
							subCur = subCur->_right;
						}//寻找左子树的最右节点
						
						if(subCur == cur->_left){
							cur->_key = subCur->_key;
							parent->_left = subCur->_right;
						}else{
							cur->_key = subCur->_key;
							parent->_right = subCur->_left;
						}
						delete subCur;
						subCur = NULL;
						return true;
					}
					//被删除节点为左孩子
					if(parent->_left == cur){
						parent->_left = cur->_left;
					}else{
						parent->_right = cur->_right;
					}
					delete cur;
					cur = NULL;
				return true;
				}else{
					parent = cur;
					Node* subCur = cur->_left;
					while(subCur->_right!=NULL){
						parent = subCur;
						subCur = subCur->_right;
					}//寻找左子树的最右节点
					
					if(subCur == cur->_left){
						cur->_key = subCur->_key;
						parent->_left = subCur->_left;
					}else{
						cur->_key = subCur->_key;
						parent->_right = subCur->_left;
					}

					delete subCur;
					subCur = NULL;
					return true;
				}//被删除节点,左右子树、均不为空
			}//找到了被删除节点
		}//找被删除节点
		//没找到
		return false;
	}
private:
	void _InOrder(Node *root){
		if(root==NULL){
			return ;
		}
		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}
private:
	Node * _root;
};


/*
while(cur!=NULL){
			//找被删除节点
			if(key > cur->_key){
				parent = cur;
				cur =cur->_right;
			}else if(key < cur->_key){
				parent = cur;
				cur = cur->_left;
			}else{
				//被删除节点左子树为空
				if(parent==NULL){
					//没有左子树的根节点
					Node* subCur = cur->_right;
					//找右子树最左节点填充
					while(subCur->_left!=NULL){
						parent = subCur;
						subCur = subCur->_right;
					}
					cur->_key = subCur->_key;
					parent->_left = subCur->_right;
					del = subCur;

				}else{
					if(cur->_left==NULL){
						//被删除节点为父亲的左子树
						if(parent->_left == cur){
							parent->_left = cur->_right;
						}else{
							parent->_right = cur->_right;
						}
						del = cur;
						delete del;
						return true;
					}
				}
			}	//被删除节点右子树为空
			}else if(cur->_right==NULL){
				//被删除节点为父亲的左子树
				if(parent->_left == cur){
					parent->_left = cur->_left;
				}else{
					parent->_right = cur->_left;	
				}
				del = cur;
				delete del;
				return true;
			}else{
				//被删除节点的左右子树都不为空
				parent = cur;
				Node* subCur = cur->_left;
				//找左子树最右节点
				while(subCur->_right!=NULL){
					parent = subCur;
					subCur = subCur->_right;
				}
				//左子树最右节点的数据替换为被删除节点的数据
				cur->_key = subCur->_key;
				parent->_right = subCur->_left;
				del = subCur;
				delete del;
				return true;
			}
		}//end while
		return false;


*/