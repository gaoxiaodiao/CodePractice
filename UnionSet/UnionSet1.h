/*
*�ļ�˵��:���鼯���������ʵ��
*����:��С��
*����:2017-02-28
*���ɿ�������:Microsoft Visual Studio 2010 
*/
#include<vector>
template<typename T=int>
class UnionSet{
public:
	UnionSet(size_t sz){
		_usf.resize(sz,-1);
	}
public:
	//�Ҹ�
	size_t FindRoot(int x){
		while(_usf[x]>=0){
			x = _usf[x];
		}
		return x;
	}
	//�ϲ�
	void Union(int x1,int x2){
		size_t root1 = FindRoot(x1);
		size_t root2 = FindRoot(x2);

		_usf[root1] += _usf[root2];
		_usf[root2] = root1;
	}
	//���С
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