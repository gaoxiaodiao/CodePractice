/*
*�ļ�˵��:AVL���������ʵ��
*����:��С��
*����:2017-04-05
*���ɿ�������:Microsoft Visual Studio 2010 
*/
#pragma once
#include<stack>
template<typename K,typename V>
struct AVLTreeNode{
	AVLTreeNode *_parent;
	AVLTreeNode *_left;
	AVLTreeNode *_right;
	int _bf;
	K _key;
	V _value;

	AVLTreeNode(const K& key,const V& value)
		:_parent(NULL)
		,_left(NULL)
		,_right(NULL)
		,_bf(0)
		,_key(key)
		,_value(value){}
};
template<typename K,typename V>
class AVLTree{
	typedef AVLTreeNode<K,V> Node;
public:
	AVLTree()
		:_root(NULL){}
	~AVLTree(){
		if(_root!=NULL){
			_Destory(_root);
		}
	}
public:
	void Insert(const K& key,const V &value){
		if(_root==NULL){
			_root = new Node(key,value);
			return ;
		}
		//�Ҳ���λ��
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
				throw "key repeat";
			}
		}
		//����Ԫ��
		cur = new Node(key,value);
		if(parent->_key > key){
			parent->_left = cur;
		}else{
			parent->_right = cur;
		}
		cur->_parent = parent;
		//����ƽ������
		while(parent!=NULL){
			//�ı丸��ƽ������
			if(parent->_left == cur){
				parent->_bf -= 1;
			}else{
				parent->_bf += 1;
			}
			//����������ϵ���
			if(parent->_bf == 1 || 
				parent->_bf ==-1){
				cur = parent;
				parent = cur->_parent;
			}else if(parent->_bf == 0){
				//�Ѿ�ƽ��
				break;
			}else if(parent->_bf == -2 || parent->_bf ==2){
				//��Ҫ������ת
				if(parent->_bf == -2&&
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
				}else if(parent->_bf == 2&&
					cur->_bf == 1){
					//����
						RotateL(parent);
				}
				break;
			}else{
				std::cout<<"ƽ�����ӳ���!"<<parent->_key<<" "<<std::endl;
			}
		}
	}
	void InOrderNonR(){
		std::stack<Node*> s;
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
	bool CheckBalance(){
		return _CheckBalance(_root);
	}
	bool CheckBalanceOP(){
		int depth = 0;
		return _CheckBalanceOP(_root,depth);
	}
protected:

	bool _CheckBalanceOP(Node *root,int &depth){
		if(root==NULL){
			depth = 0;
			return true;
		}
		int leftD = 0;
		bool left = _CheckBalanceOP(root->_left,leftD);
		int rightD = 0;
		bool right = _CheckBalanceOP(root->_right,rightD);
		//����ͼ,�������㷨,KM�㷨
		//��ķ���������ܶ���(�ҵ�)
		//
		if(left && right){
			int diff = rightD - leftD;
			if(diff!=root->_bf){
				cout<<"ƽ�����ӳ���key="<<root->_bf<<std::endl;
			}
			if(diff <= 1 || diff >= -1){
				depth = leftD>rightD?leftD+1:rightD+1;
				return true;
			}
		}

		return false;
	}

	bool _CheckBalance(Node *root){
		if(root==NULL){
			return true;
		}
		int left = _Depth(root->_left);
		int right = _Depth(root->_right);
		int diff = right-left;
		if(root->_bf != diff){
			std::cout<<"ƽ�������쳣key="<<root->_key<<std::endl;
		}
		if(diff < -1 || diff >1){
			return false;
		}
		return _CheckBalance(root->_left)&&
			_CheckBalance(root->_right);
	}

	size_t _Depth(Node *root){
		if(root==NULL){
			return 1;
		}
		int left = _Depth(root->_left);
		int right = _Depth(root->_right);
		return left>right?left+1:right+1;
	}
	//����
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

	//����
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

		subL->_bf = 0;
		parent->_bf = 0;
	
	}

	//������
	void RotateLR(Node *parent){
		Node *subL = parent->_left;
		Node *subLR = subL->_right;
		int bf = subLR->_bf;
		
		RotateL(subL);
		RotateR(parent);
		
		if(bf == 0){
			parent->_bf = subL->_bf = 0;
		}else if(bf == -1){
			subLR->_bf = 0;
			parent->_bf = 1;
		}else{
			subLR->_bf = -1;
			parent->_bf = 0;
		}
	}

	//������
	void RotateRL(Node *parent){
		Node *subR = parent->_right;
		Node *subRL = subR->_left;
		int bf = subRL->_bf;
		RotateR(subR);
		RotateL(parent);

		if(bf == 0){
			parent->_bf = subRL->_bf = 0;
		}else if(bf == 1){
			parent->_bf = -1;
			subRL->_bf = 0;
		}else if(bf == -1){
			parent->_bf = 0;
			subRL->_bf = 1;
		}
	}

protected:
	void _Destory(Node *root){
		if(root == NULL){
			return ;
		}
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
	}
private:
	Node *_root;
};


void AVLTreeTest(){
	AVLTree<int,int> t;
	int arr[] ={4,2,6,1,3,5,15,7,16,14};
	for(int i=0; i<sizeof(arr)/sizeof(arr[0]); ++i){
		t.Insert(arr[i],i);
	}
	t.InOrderNonR();
	std::cout<<"�Ƿ�ƽ��:"<<t.CheckBalance()<<std::endl;
	std::cout<<"�Ƿ�ƽ��:"<<t.CheckBalanceOP()<<std::endl;
}