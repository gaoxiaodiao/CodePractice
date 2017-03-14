/*
*�ļ�˵��:ͼ��������ʵ��(�ڽӾ���)
*����:��С��
*����:2017-03-13
*���ɿ�������:Microsoft Visual Studio 2010 
*/
#pragma once
#include<vector>
template<typename V,typename W>
class GraphMatrix{
public:
	//���캯��
	GraphMatrix(const V *vertex,size_t sz,const W & invalid = W(),bool IsDigraph = false)
		:_vertex(vertex,vertex+sz)
		,_IsDigraph(IsDigraph){
		//new��ά�����һ��:����ָ������
		_matrix = new W*[sz];
		//�ڶ���:��������
		for(int i=0; i<sz; ++i){
			_matrix[i] = new W[sz];
			for(int j=0; j<sz; ++j){
				_matrix[i][j] = invalid;
			}
		}
	}
	//��������
	~GraphMatrix(){
		//���ͷ�����
		for(int i=0; i<_vertex.size(); ++i){
			delete[] _matrix[i]; 
		}
		//���ͷ�ָ������
		delete[] _matrix;
	}
public:
	void AddEdge(const V& v1,const V& v2,const W& weight){
		size_t src = GetVertexIndex(v1);	//��ȡ����v1���±�
		size_t dst = GetVertexIndex(v2);	//��ȡ����v2���±�
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