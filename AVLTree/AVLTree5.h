/*
*文件说明:AVL树声明及实现
*作者:高小调
*日期:2017-02-07
*集成开发环境:Microsoft Visual Studio 2010 
*/
#pragma once
template<typename K,typename V>
struct AVLTreeNode{
	AVLTreeNode *_parent;
	AVLTreeNode *_left;
	AVLTreeNode *_right;
	const K _key;
	V _value;
	int _bf;
	AVLTreeNode(const K& k,const V& v)
		:_parent(NULL)
		,_left(NULL)
		,_right(NULL)
		,_key(k)
		,_value(v){}
};

template<typename K,typename V>
class AVLTree{
public:
	typedef AVLTreeNode<K,V> Node;
	//构造函数
	AVLTree()
		:_root(NULL){}
public:
	bool Insert(const K &k,const V &v){
		if(_root==NULL){
			_root = new Node(k,v);
		}else{
			Node *parent = NULL;
			Node *cur = _root;
			//1.找插入位置
			while(cur!=NULL){
				if(cur->_key > k){
					parent = cur;
					cur = cur->_left;
				}else if(cur->_key < k){
					parent = cur;
					cur = cur->_right;
				}else{
					//key唯一
					return false;
				}
			}
			//2.插入元素
			cur = new Node(k,v);
			if(parent->_key > key){
				parent->_left = cur;
			}else{
				parent->_right = cur;
			}
			//3.调整平衡因子
			while(parent!=NULL){
				if(parent->_bf == 0){
					break;
				}else if(parent->_bf == -1 ||
					parent->_bf == 1){
					cur = parent;
					parent = cur->_parent;
				}else if(parent->_bf == -2 ||
					parent->_bf==2){
						if(parent->_bf == -2&&
							cur->_bf == -1){
							//左旋
						}else if(parent->_bf==-2 &&
							cur->_bf == 1){
							//右左旋
						}else if(parent->_bf== 2&&
							cur->_bf == -1){
							//左右旋
						}else{
							//右旋
						}
				}else{
					std::cout<<"平衡因子出错,key="<<parent->_key<<std::endl;
					assert(false);
				}
			
			}
		}
		return true;
	}
protected:
	void RomateR(Node *parent){
		Node *subL = parent->_left;
		Node *subLR = subL->_right;
		
		parent->_left = subLR;
		if(subLR!=NULL){
			subLR->_parent = parent;
		}

		Node *pparent = parent->_parent;
		if(pparent!=NULL){
			if(parent == pparent->_left){
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

		subL->_bf = 0;
		parent->_bf = 0;
	}
	void RomateL(Node *parent){
		Node *subR = parent->_right;
		Node *subRL = subR->_left;

		parent->_right = subRL;
		if(subRL!=NULL){
			subRL->_parent = parent;
		}

		Node *pparent = parent->_parent;
		if(pparent!=NULL){
			if(parent == pparent->_left){
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

		parent->_bf = 0;
		subR->_bf = 0;
	}

private:
	Node *_root;
};