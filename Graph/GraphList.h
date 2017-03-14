/*
*�ļ�˵��:ͼ��������ʵ��(�ڽӱ�)
*����:��С��
*����:2017-3-14
*���ɿ�������:Microsoft Visual Studio 2010 
*/
#pragma once
#include<vector>

template<typename W>
struct GraphLink{
	W _weight;
	GraphLink<W>* _next;
	size_t _src;
	size_t _dst;

	GraphLink(size_t src=0,size_t dst=0,const W& w=W())
		:_weight(w)
		,_next(NULL)
		,_src(src)
		,_dst(dst){}
};
template<typename V,typename W>
class GraphList{
	typedef GraphLink<W> Link;
public:
	//����
	GraphList(const V *vertex,size_t sz,const W &invalid = W(),bool IsDigraph = false)
		:_vertex(vertex,vertex+sz)
		,_IsDigraph(IsDigraph){
			_linktables.resize(sz,NULL);
	}
	//����
	~GraphList(){
		for(int i=0; i<_linktables.size(); ++i){
			Link *cur = _linktables[i];
			while(cur!=NULL){
				Link *del = cur;
				cur = cur->_next;
				delete del;
			}
		}
	}
public:
	//��ö����±�
	size_t GetGraphIndex(const V &v){
		for(int i=0; i<_vertex.size(); ++i){
			if(_vertex[i] == v){
				return i;
			}
		}
		return 0;
	}
	//ͷ�巽ʽ����
	void _AddEdge(size_t src,size_t dst,const  W& w){
		Link * newNode = new Link(src,dst,w);
		newNode->_next = _linktables[src];
		_linktables[src] = newNode;
	}
	//���һ����
	void AddEdge(const V& v1,const V& v2,const W& w){
		size_t src = GetGraphIndex(v1);
		size_t dst = GetGraphIndex(v2);
		_AddEdge(src,dst,w);
		if(!_IsDigraph){
			_AddEdge(dst,src,w);
		}
	}
private:
	std::vector<V> _vertex;				//���㼯��
	std::vector<Link*> _linktables;		//�ڽӱ�
	bool _IsDigraph;
};