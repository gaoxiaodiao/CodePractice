/*
*文件说明:图的实现(邻接表)
*作者:高小调
*日期:2017-03-20
*集成开发环境:Microsoft Visual Studio 2010 
*/
#pragma once
#include<vector>
#include<queue>
#include<stack>
#include<cassert>
#include"UnionFindSet.h"
template<typename W>
struct LinkEdge{
	int _src;			//顶点下标1
	int _dst;			//顶点下标2
	W _weight;			//权重
	LinkEdge *_next;	//邻接边的关系

	LinkEdge(int src,int dst,int weight)
		:_src(src)
		,_dst(dst)
		,_weight(weight){}
};
template<typename V,typename W>
class Graph{
	typedef LinkEdge<W> Edge;
public:
	//构造函数
	Graph(const V *arr,size_t sz,bool isDigraph=false)
		:_vertexs(arr,arr+sz)
		,_isDigraph(isDigraph){
		_linkTables.resize(sz,NULL);
	}
	//析构函数
	~Graph(){
		for(int i=0; i<_linkTables.size();++i){
			Edge *cur = _linkTables[i];
			while(cur!=NULL){
				Edge *del = cur;
				cur = cur->_next;
				delete del;
			}
		}
	}
public:
	//从顶点集合中获取顶点下标
	int GetIndexFromVertexs(const V &v){
		for(int i=0; i<_vertexs.size(); ++i){
			if(_vertexs[i] == v){
				return i;
			}
		}
		assert(false);
		return -1;
	}
	//采用头插方式插入一条边
	void _AddEdge(int src,int dst,const W &weight){
		assert(src>=0&&dst>=0);
		Edge *newHead = new Edge(src,dst,weight);
		newHead->_next = _linkTables[src];
		_linkTables[src] = newHead;
	}
	//添加一条边
	void AddEdge(const V &v1,const V& v2,const W&weight){
		int src = GetIndexFromVertexs(v1);
		int dst = GetIndexFromVertexs(v2);
		_AddEdge(src,dst,weight);
		if(!_isDigraph){
			_AddEdge(dst,src,weight);
		}
	}
	//深度优先遍历
	void DFS(const V& v){
		int index = GetIndexFromVertexs(v);
		std::vector<bool> visited(_vertexs.size(),false);
		
		std::cout<<_vertexs[index]<<" ";	//访问当前节点
		visited[index] = true;		//标记

		_DFS(index,visited);		//递归访问其他节点
		std::cout<<std::endl;
	}
	//深度优先遍历,递归
	void _DFS(int index,std::vector<bool> &visited){
		Edge *cur = _linkTables[index];
		while(cur!=NULL){
			int index = cur->_dst;
			if(!visited[index]){
				std::cout<<_vertexs[index]<<" ";	//访问当前节点
				visited[index] = true;		//标记
				_DFS(cur->_dst,visited);
			}
			cur = cur->_next;
		}
	}
	//深度优先遍历,非递归
	void DFS_NonR(const V& v){
		int index = GetIndexFromVertexs(v);
		std::stack<int> s;
		std::vector<bool> visited(_vertexs.size(),false);
		
		std::cout<<_vertexs[index]<<" ";
		visited[index] = true;
		s.push(index);

		while(!s.empty()){
			int top = s.top();
			Edge *cur = _linkTables[top];	
			while(cur!=NULL){
				if(!visited[cur->_dst]){
					std::cout<<_vertexs[cur->_dst]<<" ";
					visited[cur->_dst] = true;
					s.push(cur->_dst);
					cur = _linkTables[cur->_dst];
				}else{
					cur = cur->_next;
				}
			}
			s.pop();
		}
	}
	//广度优先遍历
	void BFS(const V& v){
		int index = GetIndexFromVertexs(v);	//获取下标
		std::vector<bool> visited(_vertexs.size(),false);
		std::queue<int> q;
		q.push(index);						//下标入队
		while(!q.empty()){
			int front = q.front();			//获取队首元素
			if(!visited[front]){
				std::cout<<_vertexs[front]<<" ";	//访问当前节点
				visited[front] = true;				//标记已访问

				//其他邻接节点入队
				Edge *cur = _linkTables[front];
				while(cur!=NULL){
					q.push(cur->_dst);
					cur = cur->_next;
				}

			}
			q.pop();
		}
	}
	//Kruskal最小生成树算法
	bool Kruskal(Graph<V,W> &minTree){
		minTree._isDigraph = _isDigraph;
		minTree._vertexs = _vertexs;
		minTree._linkTables.resize(_vertexs.size());
		struct Compare{
			bool operator()(const Edge *l,const Edge*r){
				return l->_weight < r->_weight;
			}
		}

		std::priority_queue<Edge*,std::vector<Edge*>,Compare> pq; 
		for(int i=0; i<_vertexs.size(); ++i){
			Edge *cur = _linkTables[i];
			while(cur!=NULL){
				if (cur->_src < cur->_dst){
					pq.push(cur);
				}
				cur = cur->_next;
			}
		}

		int count = 0;
		UnionFindSet ufs(_vertexs.size());
		while(!pq.empty()){
			Edge * min = pq.top();
			pq.pop();
			int src = min->_src;
			int dst = min->_dst;
			if(!ufs.IsIn(src,dst)){
				minTree.AddEdge(src,dst,min->_weight);
				minTree.AddEdge(dst,src,min->_weight);
				ufs.Union(dst,src);
				++count;
				if(count == _vertexs.size()-1){
					return true;
				}
			}
		}
		return false;
	}
private:
	std::vector<V> _vertexs;			//顶点的集合
	std::vector<Edge*> _linkTables;		//邻接表
	bool _isDigraph;					//是否为有向图
};