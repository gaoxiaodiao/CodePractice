/*
*文件说明:红黑树相关声明及实现
*作者:高小调
*日期:2017-04-21
*集成开发环境:Microsoft Visual Studio 2010 
*/
#pragma once
//颜色
enum COLOR{
	RED,
	BLACK
};
//红黑树的节点
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
//红黑树声明
template<typename K,typename V>
class RBTree{

typedef RBTreeNode<K,V> Node;

public:
	//构造函数、析构函数
	RBTree():_root(NULL){}
	~RBTree(){if(_root!=NULL){_Destroy(_root);_root=NULL;}}
private:
	//禁止拷贝、赋值
	RBTree(const RBTree&);
	RBTree& operator=(const RBTree&);
public:
	//插入、检查红黑树是否平衡
	void Insert(const K&,const V&){
		if(_root==NULL){
			//当前树为空树
			_root = new Node(key,value);
			_root->_color = BLACK;
			return ;
		}
		Node *cur = _root;
		Node *parent = NULL;
		//找要插入的位置
		while(cur!=NULL){
			if(cur->_key > _key){
				parent = cur;
				cur = cur->_left;
			}else if(cur->_key < key){
				parent = cur;
				cur = cur->_right;
			}else{
				//key值唯一
				assert(false);
			}
		}
		//插入节点
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
				//情况1:叔叔存在且为红
				if(uncle!=NULL && uncle->_color==RED){
					//将父节点与叔叔节点变黑,爷爷节点变红
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					//继续向上调整
					cur = grandfather;
					parent = cur->_parent;
				}else{
					//叔叔不存在或者叔叔为黑
					if(cur!=parent->_left){
						//情况3:进行左旋,将情况变成情况2
						RotateL(parent);
						std::swap(cur,parent);
					}else{
						//情况2:进行右旋,将父节点变黑,祖父节点变红,结束调整
						RotateR(grandfather);
						parent->_color = BLACK;
						grandfather->_color = RED;
						break;
					}
				}
			}else{
				Node *uncle = grandfather->_left;
				if(uncle!=NULL&&uncle->_color==RED){
					//情况1:如果叔叔存在且为红
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;

					//变色后继续向上调整
					cur = grandfather;
					parent = cur->_parent;
				}else{
					//叔叔不存在或者叔叔为黑
					if(cur!=parent->_right){
						//情况3:对父亲节点进行右旋,转变成情况2
						RotateR(parent);
						std::swap(cur,parent);
					}else{
						//情况2:对祖父节点进行左旋,
						//父亲变为黑色,祖父变为红色
						//结束调整
						RotateL(grandfather);
						parent->_color = BLACK;
						grandfather->_color = RED;
						break;
					}
				}
			}
		}
		//最后将根节点变黑
		_root->_color = BLACK;
	}
	//判断是否平衡,每条路径黑色节点数目相等
	//不能有连续的红节点
	bool CheckIsBalance(){
		Node *cur = _root;
		int blackCount = 0;
		int count = 0;
		while(cur!=NULL){
			//计算最左路径黑色节点的数目
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
			//遇到连续红节点
			return false;
		}
		if(root->_left==NULL&&root->_right==NULL&&count!=k){
			//某条路径黑色节点数目与最左路径黑色节点数目不同
			return false;
		}

		return _CheckIsBalance(root->_left,count,k)&&
			_CheckIsBalance(root->_right,count,k);
	}	//递归检查是否平衡
	static void _Destroy(){
		if(root==NULL){
			return ;
		}
		Destroy(root->_left);
		Destroy(root->_right);
		delete root;		
	}	//递归删除节点
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
	}//左旋
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
	}//右旋
private:
	Node *_root;
};