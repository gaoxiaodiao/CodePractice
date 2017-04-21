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
	RBTreeNode *_left;
	RBTreeNode *_right;
	RBTreeNode(const K&key,const V&value)
		:_key(key)
		,_value(value)
		,_color(RED)
		,_left(NULL)
		,_right(NULL){}
};
//红黑树声明
template<typename K,typename V>
class RBTree{
typedef RBTreeNode<K,V> Node;
public:
	//构造函数、析构函数
	RBTree();
	~RBTree();
private:
	//禁止拷贝、赋值
	RBTree(const RBTree&);
	RBTree& operator=(const RBTree&);
public:
	//插入、检查红黑树是否平衡
	void Insert(const K&,const V&);
	bool CheckIsBalance();
protected:
	static bool _CheckIsBalance(Node*,size_t&,const size_t);	//递归检查是否平衡
	static void _Destroy();										//递归删除节点
	void RotateL(Node*);										//左旋
	void RotateR(Node*);										//右旋
private:
	Node *_root;
};