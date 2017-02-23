/*
*文件说明:堆的相关声明及实现(第三遍)
*作者:高小调
*日期:2016-12-31
*集成开发环境:Microsoft Visual Studio 2010 
*/
#include<vector>
template<typename T>
struct Max{
	bool operator()(const T &l,const T &r){
		return l>r;
	}
};
template<typename T>
struct Min{
	bool operator()(const T &l,const T &r){
		return l<r;
	}
};


template<typename T,typename Compare= Max<T>>
class Heap{
public:
	Heap(){}
	Heap(T arr[],size_t sz)
		:_heap(arr,arr+sz){
		for(int i=(_heap.size()-2)/2; i>=0; --i){
			AdjustDown(i);
		}
	}
public:
	void Push(const T & e){
		_heap.push_back(e);
		AdjustUp((_heap.size()-2)/2);
	}
	void Pop(){
		swap(_heap[0],_heap[_heap.size()-1]);
		AdjustDown(0);
		_heap.pop_back();
	}
protected:
	void AdjustDown(size_t pos){
		size_t parent = pos;
		size_t child = pos*2+1;
		while(child<_heap.size()){
			if(child+1<_heap.size()&&
				Compare()(_heap[child+1],_heap[child])){
				++child;
			}
			if(Compare()(_heap[child],_heap[parent])){
				swap(_heap[child],_heap[parent]);
				parent = child;
				child = parent*2+1;
			}else{
				break;
			}
		}
	}
	void AdjustUp(int pos){
		size_t parent = pos;
		size_t child = pos*2+1;
		while(child<_heap.size() && child>parent){
			if(child+1<_heap.size() && 
				Compare()(_heap[child+1],_heap[child])){
				++child;
			}

			if(Compare()(_heap[child],_heap[parent])){
				swap(_heap[child],_heap[parent]);
				child = parent;
				parent = (child-1)/2;
			}

		}
	}
private:
	vector<T> _heap;
};