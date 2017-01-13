/*
*文件说明:哈夫曼树相关声明及实现(第一遍)
*作者:高小调
*日期:2017-1-13
*集成开发环境:Microsoft Visual Studio 2010 
*/
#pragma noce
#include"Heap.h"
template<typename T>
struct HuffmanTreeNode{
	T _weight;
	HuffmanTreeNode *_left;
	HuffmanTreeNode *_right;

	HuffmanTreeNode(const T &e)
		:_weight(e)
		,_left(NULL)
		,_right(NULL){}
};
template<typename T>
class HuffmanTree{
public:
	typedef HuffmanTreeNode<T> Node;
	HuffmanTree(T arr[],size_t sz,const T &invaild){
		struct Min{
			bool operator()(Node *l,Node *r){
				return l->_weight<r->_weight;
			}
		};
		Heap<Node *,Min> heap;
		for(size_t i=0; i<sz; ++i){
			if(arr[i]!=invaild){
				heap.Push(new Node(arr[i]));
			}
		}

		while(heap.Size()>1){
			Node* left = heap.Top();
			heap.Pop();
			Node * right = heap.Top();
			heap.Pop();
			
			Node *parent = new Node(left->_weight+right->_weight);
			parent->_left = left;
			parent->_right = right;

			heap.Push(parent);
		}

		_root = heap.Top();
	}
	~HuffmanTree(){
		Destory(_root);
	}
protected:
	void Destory(Node* &root){
		if(root==NULL){
			return ;
		}
		Destory(root->_left);
		Destory(root->_right);
		delete root;
		root = NULL;
	}
private:
	Node * _root;
};

void TestHuffmanTree(){
	int arr[]={4,3,2,1};
	HuffmanTree<int> huffmantree(arr,4,0);
}

//总结:
//把昨天写的堆,功能补一补,
//顺便可以构建一颗哈夫曼树
//完美!