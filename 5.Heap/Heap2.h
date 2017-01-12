/*
*�ļ�˵��:�ѵ����������ʵ��
*����:��С��
*����:2017-01-12
*���ɿ�������:Microsoft Visual Studio 2010 
*/
#pragma once
#include<vector>
template<typename T>
struct Max{
	bool operator()(const T & l,const T &r){
		return l>r;
	}
};
template<typename T>
struct Min{
	bool operator()(const T & l,const T &r){
		return l<r;
	}
};

template<typename T,typename class Compare = Max<T>>
class Heap{
public:
	Heap(){}
	Heap(T arr[],size_t sz)
		:_heap(arr,arr+sz){
			for(int i=(_heap.size()-2)/2; i>=0; --i){
				_AdjustDown(i);
			}
	}
public:
	void Push(const T &e){
		_heap.push_back(e);
		_AdjustUp((_heap.size()-2)/2);
	}

	void Pop(){
		std::swap(_heap[0],_heap[_heap.size()-1]);
		_heap.pop_back();
		//_AdjustDown(_heap[0]);
		_AdjustDown(0)
	}
protected:
	//���µ���
	void _AdjustDown(size_t pos){
		size_t parent = pos;
		size_t child = pos*2+1;
		Compare compare;
		while(child<_heap.size()){
			//�ҳ�����
			if(child+1<_heap.size()&&
				compare(_heap[child+1],_heap[child])){
				++child;
			}
			//�ҳ����ڵ�
			if(compare(_heap[child],_heap[parent])){
				std::swap(_heap[child],_heap[parent]);
				parent = child;
				child = parent*2+1;
			}else{
				break;
			}
		}
	}

	//���ϵ���
	void _AdjustUp(size_t pos){
		size_t parent = pos;
		size_t child = parent*2+1;
		Compare compare;
		while(child<_heap.size()&&child>parent){
			//�ҳ�����
			if(child+1<_heap.size()&&
				compare(_heap[child+1],_heap[child])){
				++child;
			}
			//�ҳ����ڵ�
			if(compare(_heap[child],_heap[parent])){
				std::swap(_heap[child],_heap[parent]);
				child = parent;
				parent = (child-1)/2;
			}else{
				break;
			}
		}
	}
private:
	std::vector<T> _heap;
};

//�ܽ�:
//���û��ʲô�������,����ע�Ͳ��ֵ�С����....