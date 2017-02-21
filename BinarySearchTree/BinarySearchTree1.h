/*
*�ļ�˵��:����������
*����:��С��
*����:2017-01-08
*���ɿ�������:Microsoft Visual Studio 2010 
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
	//��������
	bool Insert(const K &key){
		//����������
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
	//�������
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
				//��ɾ���ڵ�û��������
				if(cur->_left == NULL){
					if(parent==NULL){
						//ɾ��һ��û���������ĸ��ڵ�
						parent = cur;
						//û��������
						if(cur->_right==NULL){
							delete cur;
							_root = NULL;
							return true;
						}
						Node *subCur = cur->_right;
						while(subCur->_left!=NULL){
							parent = subCur;
							subCur = subCur->_left;
						}//�Ҹ��ڵ��Һ��ӵ�����ڵ�
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

					//��ɾ���ڵ�Ϊ���׵�������
					if(parent->_left == cur){
						parent->_left = cur->_right;
					}else{
						parent->_right = cur->_right;
					}//��ɾ���ڵ�Ϊ���׵�������
					delete cur;
					cur = NULL;
					return true;

				//��ɾ���ڵ�û��������
				}else if(cur->_right == NULL){
					//�ýڵ�Ϊ���ڵ�
					if(parent == NULL){
						parent = cur;
						Node* subCur = cur->_left;
						while(subCur->_right!=NULL){
							parent = subCur;
							subCur = subCur->_right;
						}//Ѱ�������������ҽڵ�
						
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
					//��ɾ���ڵ�Ϊ����
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
					}//Ѱ�������������ҽڵ�
					
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
				}//��ɾ���ڵ�,��������������Ϊ��
			}//�ҵ��˱�ɾ���ڵ�
		}//�ұ�ɾ���ڵ�
		//û�ҵ�
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
			//�ұ�ɾ���ڵ�
			if(key > cur->_key){
				parent = cur;
				cur =cur->_right;
			}else if(key < cur->_key){
				parent = cur;
				cur = cur->_left;
			}else{
				//��ɾ���ڵ�������Ϊ��
				if(parent==NULL){
					//û���������ĸ��ڵ�
					Node* subCur = cur->_right;
					//������������ڵ����
					while(subCur->_left!=NULL){
						parent = subCur;
						subCur = subCur->_right;
					}
					cur->_key = subCur->_key;
					parent->_left = subCur->_right;
					del = subCur;

				}else{
					if(cur->_left==NULL){
						//��ɾ���ڵ�Ϊ���׵�������
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
			}	//��ɾ���ڵ�������Ϊ��
			}else if(cur->_right==NULL){
				//��ɾ���ڵ�Ϊ���׵�������
				if(parent->_left == cur){
					parent->_left = cur->_left;
				}else{
					parent->_right = cur->_left;	
				}
				del = cur;
				delete del;
				return true;
			}else{
				//��ɾ���ڵ��������������Ϊ��
				parent = cur;
				Node* subCur = cur->_left;
				//�����������ҽڵ�
				while(subCur->_right!=NULL){
					parent = subCur;
					subCur = subCur->_right;
				}
				//���������ҽڵ�������滻Ϊ��ɾ���ڵ������
				cur->_key = subCur->_key;
				parent->_right = subCur->_left;
				del = subCur;
				delete del;
				return true;
			}
		}//end while
		return false;


*/