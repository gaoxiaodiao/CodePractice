/*
*�ļ�˵��:�ѵ����������ʵ��(github���ϵ�һ��)
*����:��С��
*����:2017-01-09
*���ɿ�������:Microsoft Visual Studio 2010 
*/
#pragma once
#include<vector>
//�º���:�������
template<typename T>
struct Max{
	bool operator()(const T& l,const T& r){
		return l>r;
	}
};
//�º���:����С��
template<typename T>
struct Min{
	bool operator()(const T& l,const T& r){
		return l<r;
	}
};

template<typename T,typename class Com = Max<T>>
class Heap{
public:
	Heap(){}
	Heap(T arr[],size_t sz)
		:_heap(arr,arr+sz){
			//ѭ���������µ���
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
		_AdjustDown(0);		//_AdjusrDown(_heap[0]);
		_heap.pop_back();
	}
protected:
	//���µ���
	void _AdjustDown(size_t pos){
		size_t parent = pos;
		size_t child = pos*2+1;
		while(child < _heap.size()){
			//ѡ�����Һ�����ֵ���_heap[child+1]>_heap[child]
			if(child+1<_heap.size() &&
				Com()(_heap[child+1],_heap[child])){
				++child;
			}
			//�븸�׽��бȽ�,����,�������ϵ���_heap[parent]>_heap[child]
			if(Com()(_heap[child],_heap[parent])){
				std::swap(_heap[child],_heap[parent]);
				parent = child;
				child = parent*2+1;
			}else{
				//����Ҫ����,ѭ������
				break;
			}
		}
	}
	//���ϵ���,�����µ�����������
	void _AdjustUp(size_t pos){
		size_t parent = pos;
		size_t child = parent*2+1;
		while(child<_heap.size() && parent<child){
			if(child+1<_heap.size()&&
				Com()(_heap[child+1],_heap[child])){
				++child;
			}

			if(Com()(_heap[child],_heap[parent])){
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

/*
	�ܽ�:
		���һ���öѵĳ�������2017-1-1��.
		֮ǰ�Ѿ�����4�εĶ�,
		�Ҿ��öԶѵĴ����Ѿ�Խ��Խ����,����Խ��Խ���
		�������Ѿ���ȫ������.
		˭֪,�������õ�ʱ��,���ǻ���һЩС����.
		��...������Ҳ̫����!
		����������ϰ,ֱ�����Ժ���˼�����ó���....
*/
