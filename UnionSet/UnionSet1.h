/*
*文件说明:并查集相关声明及实现
*作者:高小调
*日期:2017-02-28
*集成开发环境:Microsoft Visual Studio 2010 
*/
#include<vector>
template<typename T=int>
class UnionSet{
public:
	UnionSet(size_t sz){
		_usf.resize(sz,-1);
	}
public:
	//找根
	size_t FindRoot(int x){
		while(_usf[x]>=0){
			x = _usf[x];
		}
		return x;
	}
	//合并
	void Union(int x1,int x2){
		size_t root1 = FindRoot(x1);
		size_t root2 = FindRoot(x2);

		_usf[root1] += _usf[root2];
		_usf[root2] = root1;
	}
	//求大小
	size_t GetSize(){
		size_t count = 0;
		for(size_t i=0; i<_usf.size(); ++i){
			if(_usf[i]<0){
				++count;
			}
		}
		return count;
	}
private:
	std::vector<T> _usf;
};