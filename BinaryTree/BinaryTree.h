/*
*�ļ�˵��:���������������ʵ��
*����:��С��
*����:2017-03-20
*���ɿ�������:Microsoft Visual Studio 2010 
*/
#pragma once
//�������ڵ㶨��
#include<stack>
#include<queue>
template<typename T>
struct BinaryTreeNode{
	T _value;
	BinaryTreeNode *_left;
	BinaryTreeNode *_right;
	//���캯��
	BinaryTreeNode(const T&value)
		:_value(value)
		,_left(NULL)
		,_right(NULL){}
};

template<typename T>
class BinaryTree{
	typedef BinaryTreeNode<T> Node;
public:
	//���캯��
	BinaryTree(T arr[],size_t sz,const T& invalid=T()){
		int index = 0;
		_root = _CreateTree(arr,sz,index,invalid);
	}
	//��������
	BinaryTree(const BinaryTree & bt){
		_root = _Copy(bt._root);
	}
	//��ֵ���������
	BinaryTree &operator=(const BinaryTree & bt){
		if(_root!=bt._root){
			BinaryTree &tmp(bt);
			std::swap(tmp._root,root);
		}
		return *this;
	}
	//��������
	~BinaryTree(){
		_Destory(_root);
	}
public:
	//ǰ�����
	void PrevOrder(){
		_PrevOrder(_root);
		std::cout<<std::endl;
	}
	//ǰ������ǵݹ�
	void PrevOrderNonR(){
		Node *cur = _root;
		std::stack<Node*> s;
		while(!s.empty() || cur!=NULL){
			while(cur!=NULL){
				s.push(cur);
				cout<<cur->_value<<" ";
				cur = cur->_left;
			}

			Node *top = s.top();
			s.pop();

			cur = top->_right;
		}
		std:cout<<std::endl;
	}
	//�������
	void InOrder(){
		_InOrder(_root);
		std::cout<<std::endl;
	}
	//��������ǵݹ�
	void InOrderNonR(){
		Node *cur = _root;
		std::stack<Node*> s;
		while(!s.empty() || cur!=NULL){
			while(cur!=NULL){
				s.push(cur);
				cur = cur->_left;
			}

			Node *top = s.top();
			s.pop();
			cout<<top->_value<<" ";

			cur = top->_right;
		}
		std::cout<<std::endl;
	}
	//�������
	void PostOrder(){
		_PostOrder(_root);
		std::cout<<std::endl;
	}
	//��������ǵݹ�
	void PostOrderNonR(){
		Node *cur = _root;
		Node *prev = NULL;
		std::stack<Node*> s;
		while(!s.empty() || cur!=NULL){
			while(cur!=NULL){
				s.push(cur);
				cur = cur->_left;
			}

			Node *top = s.top();
			if(top->_right==NULL || top->_right == prev){
				prev = top;
				std::cout<<top->_value<<" ";
				s.pop();
			}else{
				cur = top->_right;
			}
		}
		std::cout<<std::endl;
	}
	//�������
	void BFS(){
		Node *cur = _root;
		std::queue<Node*> q;
		q.push(cur);
		while(!q.empty()){
			Node *front = q.front();
			if(front!=NULL){
				cout<<front->_value<<" ";
				q.push(front->_left);
				q.push(front->_right);
			}
			q.pop();
		}
		std::cout<<std::endl;
	}
	//�������ĸ߶�
	size_t Depth(){
		return _Depth(_root);
	}
	//��Ҷ�ӽڵ����
	size_t GetLeaf(){
		int count = 0;
		_GetLeap(_root,count);
		return count;
	}
	//���K��ڵ����
	size_t GetKNum(size_t k){
		int count = 0;
		_GetKNum(_root,k,count);
		return count;
	}
	//�жϽڵ��Ƿ��ڶ�������(ǰ������ǵݹ�)
	bool IsIn(const T & e){
		Node *cur = _root;
		std::stack<Node*> s;
		while(!s.empty() || cur!=NULL){
			while(cur!=NULL){
				s.push(cur);
				if(cur->_value == e){
					return true;
				}
				cur = cur->_left;
			}

			Node *top = s.top();
			s.pop();

			cur = top->_right;
		}
		return false;
	}
protected:
	void _GetKNum(Node*root,size_t k,int &count){
		if(root==NULL){
			return ;
		}
		if(k==1){
			++count;
			return ;
		}
		_GetKNum(root->_left,k-1,count);
		_GetKNum(root->_right,k-1,count);
	}
	void _GetLeap(Node*root,int &count){
		if(root==NULL){
			return ;
		}
		if(root->_left==NULL && root->_right==NULL){
			++count;
		}
		_GetLeap(root->_left,count);
		_GetLeap(root->_right,count);
	}

	size_t _Depth(Node* root){
		if(root==NULL){
			return 0;
		}
		int leftD = _Depth(root->_left);
		int rightD = _Depth(root->_right);
		return leftD>rightD?leftD+1:rightD+1;
	}
	void _PostOrder(Node* root){
		if(root==NULL){
			return ;
		}
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		std::cout<<root->_value<<" ";
	}
	void _InOrder(Node *root){
		if(root==NULL){
			return ;
		}
		_InOrder(root->_left);
		std::cout<<root->_value<<" ";
		_InOrder(root->_right);

	}
	void _PrevOrder(Node *root){
		if(root==NULL){
			return ;
		}
		std::cout<<root->_value<<" ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}
	//ɾ��
	void _Destory(Node *root){
		if(root==NULL){
			return ;
		}
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
	}
	//����
	Node *_Copy(Node *root){
		if(root==NULL){
			return NULL;
		}
		Node *newRoot = new Node(root->_value);
		newRoot->_left = _Copy(root->_left);
		newRoot->_right = _Copy(root->_right);
		return newRoot;
	}
	//������
	Node *_CreateTree(T arr[],size_t sz,int &index,const T &invalid){
		if(index<sz && arr[index]!=invalid){
			Node *root = new Node(arr[index]);
			root->_left = _CreateTree(arr,sz,++index,invalid);
			root->_right = _CreateTree(arr,sz,++index,invalid);
			return root;			
		}
		return NULL;
	}
private:
	Node *_root;
};


void TestBinaryTree(){
	int arr[] = {1,2,4,'#','#',7,'#','#',3,5,'#','#',6,'#',8};
	BinaryTree<int> t1(arr,sizeof(arr)/sizeof(*arr),'#');
	BinaryTree<int> t2(t1);
	t1.PrevOrder();
	t1.InOrder();
	t1.PostOrder();
	std::cout<<std::endl;
	t2.PrevOrder();
	t2.InOrder();
	t2.PostOrder();
	std::cout<<std::endl;
	t1.PrevOrderNonR();
	t1.InOrderNonR();
	t1.PostOrderNonR();
	t1.BFS();
	int k = 2;
	std::cout<<"t1�ĸ߶�Ϊ:"<<t1.Depth()<<std::endl;
	std::cout<<"t1Ҷ�ӽڵ�ĸ���Ϊ:"<<t1.GetLeaf()<<std::endl;
	std::cout<<"t1��"<<k<<"��ڵ�ĸ���Ϊ"<<t1.GetKNum(k)<<std::endl;
	std::cout<<"t1���нڵ�5��?>>"<<t1.IsIn(5)<<std::endl;
}