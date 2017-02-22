/*
*文件说明:BitMap相关声明及实现
*作者:高小调
*日期:2017-02-21
*集成开发环境:Microsoft Visual Studio 2010 
*/
#pragma once
#include<vector>
class BitMap{
public:
	BitMap(size_t bitMapSize = 1024){
		_array.resize((bitMapSize>>5)+1);
	}
	void set(size_t value){
		size_t index = value>>5;
		size_t num = value%32;
		_array[index] |= (1<<num);
	}
	void reSet(size_t value){
		size_t index = value>>5;
		size_t num = value%32;
		_array[index] &= ~(1<<num);
	}
	bool test(size_t value){
		size_t index = value>>5;
		size_t num = value%32;
		return _array[index] & (1<<num);
	}
private:
	std::vector<size_t> _array;
};
