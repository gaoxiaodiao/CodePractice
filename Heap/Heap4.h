/*
*文件说明:堆相关声明及实现
*作者:高小调
*日期:2017-02-22
*集成开发环境:Microsoft Visual Studio 2010 
*/
#pragma once
#include<vector>
template<typename T,typename com = std::less<T>>
class Heap{
public:
	Heap(T arr[],size_t sz)
		:_heap(arr,arr+sz){
		int idx = (sz-1)/2;
		for(;idx>=0;--idx){
			AdjustDown(idx);
		}
	}
public:
	void Push(const T& e){
		_heap.push_back(e);
		AdjustUp((_heap.size()-1)/2);
	}
	void Pop(){
		std::swap(_heap[0],_heap[_heap.size()-1]);
		AdjustDown(0);
	}
protected:
	void AdjustDown(size_t parent){
		size_t child = parent*2;
		while(child<_heap.size()){
			if(child+1<_heap.size() &&com()(_heap[child+1],_heap[child])){
				++child;
			}
			if(com()(_heap[child],_heap[parent])){
				std::swap(_heap[child],_heap[parent]);
				parent = child;
				child = parent*2;
			}else{
				break;
			}
		}
	}
	void AdjustUp(size_t parent){
		size_t child = parent*2;
		while(child<_heap.size()&&child < parent){
			if(child+1<_heap.size()&&com()(_heap[child+1],_heap[child])){
				++child;
			}
			if(com()(_heap[child],_heap[parent])){
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
