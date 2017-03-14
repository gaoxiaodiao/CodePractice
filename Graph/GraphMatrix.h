/*
*文件说明:图的声明及实现(邻接矩阵)
*作者:高小调
*日期:2017-03-13
*集成开发环境:Microsoft Visual Studio 2010 
*/
#pragma once
#include<vector>
template<typename V,typename W>
class GraphMatrix{
public:
	//构造函数
	GraphMatrix(const V *vertex,size_t sz,const W & invalid = W(),bool IsDigraph = false)
		:_vertex(vertex,vertex+sz)
		,_IsDigraph(IsDigraph){
		//new二维数组第一步:开辟指针数组
		_matrix = new W*[sz];
		//第二步:开辟数据
		for(int i=0; i<sz; ++i){
			_matrix[i] = new W[sz];
			for(int j=0; j<sz; ++j){
				_matrix[i][j] = invalid;
			}
		}
	}
	//析构函数
	~GraphMatrix(){
		//先释放数据
		for(int i=0; i<_vertex.size(); ++i){
			delete[] _matrix[i]; 
		}
		//再释放指针数组
		delete[] _matrix;
	}
public:
	void AddEdge(const V& v1,const V& v2,const W& weight){
		size_t src = GetVertexIndex(v1);	//获取顶点v1的下标
		size_t dst = GetVertexIndex(v2);	//获取顶点v2的下标
		_matrix[src][dst] = weight;
		if( !_IsDigraph ){
			_matrix[dst][src] = weight;
		}
	}
protected:
	size_t GetVertexIndex(const V& v){
		for(int i=0; i<_vertex.size(); ++i){
			if(_vertex[i] == v){
				return i;
			}
		}
		return 0;
	}
private:
	std::vector<V> _vertex;
	W **_matrix;
	bool _IsDigraph;
};