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
	RBTreeNode *_left;
	RBTreeNode *_right;
	RBTreeNode(const K&key,const V&value)
		:_key(key)
		,_value(value)
		,_color(RED)
		,_left(NULL)
		,_right(NULL){}
};
//���������
template<typename K,typename V>
class RBTree{
typedef RBTreeNode<K,V> Node;
public:
	//���캯������������
	RBTree();
	~RBTree();
private:
	//��ֹ��������ֵ
	RBTree(const RBTree&);
	RBTree& operator=(const RBTree&);
public:
	//���롢��������Ƿ�ƽ��
	void Insert(const K&,const V&);
	bool CheckIsBalance();
protected:
	static bool _CheckIsBalance(Node*,size_t&,const size_t);	//�ݹ����Ƿ�ƽ��
	static void _Destroy();										//�ݹ�ɾ���ڵ�
	void RotateL(Node*);										//����
	void RotateR(Node*);										//����
private:
	Node *_root;
};