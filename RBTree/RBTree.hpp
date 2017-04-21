/*
*�ļ�˵��:��������������ʵ��
*����:��С��
*����:2017-04-21
*���ɿ�������:Microsoft Visual Studio 2010 
*/
#pragma once
//��ɫ
enum COLOR{
	RED,
	BLACK
};
//������Ľڵ�
template<typename K,typename V>
struct RBTreeNode{
	K _key;
	V _value;
	COLOR _color;
	RBTreeNode *_parent;
	RBTreeNode *_left;
	RBTreeNode *_right;
	RBTreeNode(const K &key,const V &value)
		:_key(key)
		,_value(value)
		,_color(RED)
		,_parent(NULL)
		,_left(NULL)
		,_right(NULL){}
};
//���������
template<typename K,typename V>
class RBTree{

typedef RBTreeNode<K,V> Node;

public:
	//���캯������������
	RBTree():_root(NULL){}
	~RBTree(){if(_root!=NULL){_Destroy(_root);_root=NULL;}}
private:
	//��ֹ��������ֵ
	RBTree(const RBTree&);
	RBTree& operator=(const RBTree&);
public:
	//���롢��������Ƿ�ƽ��
	void Insert(const K&,const V&){
		if(_root==NULL){
			//��ǰ��Ϊ����
			_root = new Node(key,value);
			_root->_color = BLACK;
			return ;
		}
		Node *cur = _root;
		Node *parent = NULL;
		//��Ҫ�����λ��
		while(cur!=NULL){
			if(cur->_key > _key){
				parent = cur;
				cur = cur->_left;
			}else if(cur->_key < key){
				parent = cur;
				cur = cur->_right;
			}else{
				//keyֵΨһ
				assert(false);
			}
		}
		//����ڵ�
		cur = new Node(key,value);
		if(parent->_key > key){
			parent->_left = cur;
		}else{
			parent->_right = cur;
		}
		cur->_parent = parent;
		while(parent!=NULL && parent->_color == RED){
			Node *grandfather = parent->_parent;
			if(grandfather->_left == parent){
				Node *uncle = grandfather->_right;
				//���1:���������Ϊ��
				if(uncle!=NULL && uncle->_color==RED){
					//�����ڵ�������ڵ���,үү�ڵ���
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					//�������ϵ���
					cur = grandfather;
					parent = cur->_parent;
				}else{
					//���岻���ڻ�������Ϊ��
					if(cur!=parent->_left){
						//���3:��������,�����������2
						RotateL(parent);
						std::swap(cur,parent);
					}else{
						//���2:��������,�����ڵ���,�游�ڵ���,��������
						RotateR(grandfather);
						parent->_color = BLACK;
						grandfather->_color = RED;
						break;
					}
				}
			}else{
				Node *uncle = grandfather->_left;
				if(uncle!=NULL&&uncle->_color==RED){
					//���1:������������Ϊ��
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;

					//��ɫ��������ϵ���
					cur = grandfather;
					parent = cur->_parent;
				}else{
					//���岻���ڻ�������Ϊ��
					if(cur!=parent->_right){
						//���3:�Ը��׽ڵ��������,ת������2
						RotateR(parent);
						std::swap(cur,parent);
					}else{
						//���2:���游�ڵ��������,
						//���ױ�Ϊ��ɫ,�游��Ϊ��ɫ
						//��������
						RotateL(grandfather);
						parent->_color = BLACK;
						grandfather->_color = RED;
						break;
					}
				}
			}
		}
		//��󽫸��ڵ���
		_root->_color = BLACK;
	}
	//�ж��Ƿ�ƽ��,ÿ��·����ɫ�ڵ���Ŀ���
	//�����������ĺ�ڵ�
	bool CheckIsBalance(){
		Node *cur = _root;
		int blackCount = 0;
		int count = 0;
		while(cur!=NULL){
			//��������·����ɫ�ڵ����Ŀ
			if(cur->_color==BLACK){
				++blackCount;
			}
			cur = cur->_left;
		}
		_CheckIsBalance(_root,count,blankcount);
	}

protected:
	static bool _CheckIsBalance(Node*root,size_t &count,const size_t k){
		if(root==NULL){
			return true;
		}
		if(root->_color==BLACK){
			++count;
		}
		if(root->_color==RED && root->_parent->_color==RED){
			//����������ڵ�
			return false;
		}
		if(root->_left==NULL&&root->_right==NULL&&count!=k){
			//ĳ��·����ɫ�ڵ���Ŀ������·����ɫ�ڵ���Ŀ��ͬ
			return false;
		}

		return _CheckIsBalance(root->_left,count,k)&&
			_CheckIsBalance(root->_right,count,k);
	}	//�ݹ����Ƿ�ƽ��
	static void _Destroy(){
		if(root==NULL){
			return ;
		}
		Destroy(root->_left);
		Destroy(root->_right);
		delete root;		
	}	//�ݹ�ɾ���ڵ�
	void RotateL(Node* parent){
		Node *subR = parent->_right;
		Node *subRL = subR->_left;

		parent->_right = subRL;
		if(subRL!=NULL){
			subRL->_parent = parent;
		}
		
		Node *pparent = parent->_parent;
		if(pparent==NULL){
			_root = subRL;
			subRL->_parent = NULL;
		}else{
			if(pparent->_left == parent){
				pparent->_left = subRL;
			}else{
				pparent->_right = subRL;
			}
			subRL->_parent = pparent;
		}

		subRL->_right = parent;
		parent->_parent = subRL;
	}//����
	void RotateR(Node* parent){
		Node *subL = parent->_left;
		Node *subLR = subL->_right;

		parent->_right = subLR;
		if(subLR!=NULL){
			subLR->_parent = parent;
		}

		Node *pparent = parent->_parent;
		if(pparent!=NULL){
			_root = subLR;
			_root->_parent = NULL;
		}else{
			if(pparent->_left == parent){
				pparent->_left = subLR;
			}else{
				pparent->_right = subLR;
			}
			subLR->_parent = pparent;
		}

		subLR->_left = parent;
		parent->_parent = subLR;
	}//����
private:
	Node *_root;
};