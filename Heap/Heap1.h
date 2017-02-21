/*
*文件说明:堆的相关声明及实现(github的上第一遍)
*作者:高小调
*日期:2017-01-09
*集成开发环境:Microsoft Visual Studio 2010 
*/
#pragma once
#include<vector>
//仿函数:建立大堆
template<typename T>
struct Max{
	bool operator()(const T& l,const T& r){
		return l>r;
	}
};
//仿函数:建立小堆
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
			//循环进行向下调整
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
	//向下调整
	void _AdjustDown(size_t pos){
		size_t parent = pos;
		size_t child = pos*2+1;
		while(child < _heap.size()){
			//选出左、右孩子中值大的_heap[child+1]>_heap[child]
			if(child+1<_heap.size() &&
				Com()(_heap[child+1],_heap[child])){
				++child;
			}
			//与父亲进行比较,交换,继续向上调整_heap[parent]>_heap[child]
			if(Com()(_heap[child],_heap[parent])){
				std::swap(_heap[child],_heap[parent]);
				parent = child;
				child = parent*2+1;
			}else{
				//不需要调整,循环结束
				break;
			}
		}
	}
	//向上调整,与向下调整代码类似
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
	总结:
		最后一次敲堆的程序是在2017-1-1日.
		之前已经敲了4次的堆,
		我觉得对堆的代码已经越来越熟练,理解的越来越深刻
		本想着已经完全掌握了.
		谁知,今日再敲的时候,还是会有一些小问题.
		唉...这忘性也太大了!
		还需更多的练习,直到可以毫不思考的敲出来....
*/
