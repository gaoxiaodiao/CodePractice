/*
*�ļ�˵��:AVLTree�������������
*����:��С��
*����:2017-02-09
*���ɿ�������:Microsoft Visual Studio 2010 
*/
#pragma once
#include<stack>
#include<assert.h>
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
	~AVLTree(){
		//_Destory(_root);
	}
public:
	bool Insert(const K &k,const V &v){
		if(_root==NULL){
			_root = new Node(k,v);
		}else{
			Node *parent = NULL;
			Node *cur = _root;
			//1.Ѱ�Ҳ���λ��
			while(cur!=NULL){
				if(cur->_key < k){
					parent = cur;
					cur = cur->_right;
				}else if(cur->_key > k){
					parent = cur;
					cur = cur->_left;
				}else{
					//keyֵ�ظ�
					return false;
				}
			}

			//2.�����½ڵ�
			cur = new Node(k,v);
			if(parent->_key < k){
				parent->_right = cur;
			}else{
				parent->_left = cur;
			}
			cur->_parent = parent;


			//3.����ƽ������
			while(parent!=NULL){
				//����
				if(parent->_left == cur){
					parent->_bf -= 1;
				}else{
					parent->_bf += 1;
				}

				//�ж��Ƿ��������
				if(parent->_bf == 1 ||
					parent->_bf == -1){
					//����������ϵ���
					cur = parent;
					parent = parent->_parent;
				}else if(parent->_bf == 0){
					//����Ҫ����
					break;
				}else if(parent->_bf == 2||
					parent->_bf == -2){
					//��Ҫ������ת
						if(parent->_bf == -2 &&
							cur->_bf == -1){
							//����
							RotateR(parent);
						}else if(parent->_bf == -2&&
							cur->_bf == 1){
							//������
							RotateLR(parent);
						}else if(parent->_bf == 2&&
							cur->_bf == -1){
							//������
							RotateRL(parent);
						}else{
							//����
							RotateL(parent);
						}
					//��ת���˳�ѭ��
					break;
				}else{
					//ƽ�����ӳ���
					std::cout<<"ƽ�����ӳ���,key="<<parent->_key<<std::endl;
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
			std::cout<<top->_key<<" ";
			
			cur = top->_right;
		}
		std::cout<<std::endl;
	}
protected:
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

		subR->_bf = 0;
		parent->_bf = 0;
	}
	void RotateRL(Node *parent){
		Node *subR = parent->_right;
		Node *subRL = subR->_left;
		int bf = subRL->_bf;
		
		RotateR(subR);
		RotateL(parent);
		if(bf == 0){
			parent->_bf = 0;
			subR->_bf = 0;
		}else if(bf == 1){
			parent->_bf = -1;
			subR->_bf = 0;
		}else if(bf == -1){
			parent->_bf = 0;
			subR->_bf = 1;
		}
		subRL->_bf = 0;
	}


	void RotateLR(Node *parent){
		Node *subL = parent->_left;
		Node *subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(subL);
		RotateR(parent);

		if(bf == 0){
			parent->_bf = subL->_bf = 0;
		}else if(bf == -1){
			parent->_bf = 1;
			subL->_bf = 0;
		}else{
			parent->_bf = 0;
			subL->_bf = -1;
		}
		subLR->_bf = 0;
	}
	


private:
	Node *_root;
};


/*
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
	~AVLTree(){
		if(_root!=NULL){
			_Destory(_root);
		}
	}
public:
	//��������
	bool Insert(const K &k,const V &v){
		if(_root==NULL){
			_root = new Node(k,v);
		}else{
			Node *parent = NULL;
			Node *cur = _root;
			//1.�Ҳ���λ��
			while(cur!=NULL){
				if(cur->_key < k){
					parent = cur;
					cur = cur->_right;
				}else if(cur->_key > k){
					parent = cur;
					cur = cur->_left;
				}else{
					//key�ظ�
					return false;
				}
			}

			//2.��������
			cur = new Node(k,v);
			if(parent->_key < k){
				parent->_right = cur;
			}else{
				parent->_left = cur;
			}
			cur->_parent = parent;

			//3.����ƽ������
			while(parent!=NULL){
				//�������׽ڵ��ƽ������
				if(parent->_left == cur){
					parent->_bf -= 1;
				}else{
					parent->_bf += 1;
				}
				//�ж��Ƿ��������
				if(parent->_bf == 0){
					//�Ѿ�ƽ��,����Ҫ����
					break;
				}else if(parent->_bf == -1||
					parent->_bf == 1){
					//��û��ƽ�⣬��Ҫ�������ϵ���
					cur = parent;
					parent = parent->_parent;
				}else if(parent->_bf == -2||
					parent->_bf == 2){
					//��Ҫ������ת����
						if(parent->_bf == -2 &&
							cur->_bf == -1){
							//����
								RotateR(parent);
						}else if(parent->_bf == -2 &&
							cur->_bf == 1){
							//������
								RotateLR(parent);
						}else if(parent->_bf == 2 &&
							cur->_bf == -1){
							//������
								RotateRL(parent);
						}else{
							//����
								RotateL(parent);
						}
						break;
				}else{
					//�쳣���
					std::cout<<"ƽ�������쳣,key="<<parent->_key<<std::endl;
					assert(false);
				}
			}
		}
		return true;
	}
	//�ǵݹ��������
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
	
protected:
	//�ݹ�ɾ����
	void _Destory(Node *&root){
		if(root==NULL){
			return ;
		}
		_Destory(_root->_left);
		_Destory(_root->_right);
		delete _root;
		_root = NULL;
	}
	//����
	void RotateR(Node *parent){
		Node *subL = parent->_left;
		Node *subLR = subL->_right;
		
		parent->_left = subLR;
		if(subLR!=NULL){
			subLR->_parent = parent;
		}

		Node *pParent = parent->_parent;
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
	//����
	void RotateL(Node *parent){
		Node *subR = parent->_right;
		Node *subRL = subR->_left;

		parent->_right = subRL;
		if(subRL!=NULL){
			subRL->_parent = parent;	
		}

		Node *pParent = parent->_parent;
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

		parent->_bf = 0;
		subR->_bf = 0;
	}
	//����˫��
	void RotateRL(Node *parent){
		RotateR(parent->_right);
		RotateL(parent);
	}
	//����˫��
	void RotateLR(Node *parent){
		RotateL(parent->_left);
		RotateR(parent);
	}
private:
	Node *_root;
};


//BUG�ܽ�
//1.Insert������,��ת��ɺ�,û������ѭ��
//2.����ǵݹ����,������û��pop
//3.����ǵݹ����,ѭ���ж�������д����s.empty();

//˫��,ƽ�����ӻ���û������
*/