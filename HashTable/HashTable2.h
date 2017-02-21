/*
*文件说明:哈希表相关声明及实现
*作者:高小调
*日期:2017-02-18
*集成开发环境:Microsoft Visual Studio 2010 
*/
#pragma once
#include<string>
#include<vector>
enum Status{
	EMPTY,
	EXIST,
	DELETE
};

template<typename K,typename V>
struct HashNode{
	K _key;
	V _value;
	Status _status;
	HashNode(const K &key = K(),const V& value= V())
		:_key(key)
		,_value(value)
		,_status(EMPTY){}
};

template<typename T>
struct HashFunc{
	size_t operator()(const T &key){
		return key;
	}
};

template<>
struct HashFunc<std::string>{
	size_t operator()(const std::string &s){
		size_t ret = 0;
		const char *cur = s.c_str();
		while(*cur){
			ret += 137+*cur;
			++cur;
		}
		return ret;
	}
};

template<typename K,typename V,typename HashFunc = HashFunc<K>>
class HashTable{
public:
	typedef HashNode<K,V> Node;
public:
	HashTable(size_t size)
		:_size(0){
			_tables.resize(size);
	}
public:
	std::pair<Node*,bool> Insert(const K& key,const V &value){
		_CheckCapacity();
		size_t index = _HashFunc(key);
		while(_tables[index]._status!=EMPTY){
			if(key == _tables[index]._key){
				//防冗余
				return std::make_pair(&_tables[index],false);
			}
			++index;
			if(index==_tables.size()){
				index = 0;	
			}
		}
		_tables[index]._key = key;
		_tables[index]._value = value;
		_tables[index]._status = EXIST;
		++_size;
		return std::make_pair(&_tables[index],true);
	}
	std::pair<Node*,bool> Find(const K &key){
		size_t index = _HashFunc(key);
		while(_tables[index]._status!=EMPTY){
			if(_tables[index]._key==key && _tables[index]._status == EXIST){
				return std::make_pair(&_tables[index],true);
			}
			++index;
			if(index == _tables.size()){
				index = 0;
			}
		}
		return std::make_pair((Node*)NULL,false);
	}
	void Remove(const K &key){
		std::pair<Node*,bool> del = Find(key);
		if(del.second==true){
			del.first->_status = DELETE;
		}
	}
protected:
	void _CheckCapacity(){
		if(_tables.empty()){
			//哈希表为空
			_tables.resize(7);
		}
		if(_size*10/_tables.size() >= 7){
			//荷载因子大于0.7
			size_t newSize = _getNewSize(_size);
			HashTable<K,V> tmp(newSize);
			for(size_t i=0; i<_tables.size(); ++i){
				if(_tables[i]._status == EXIST){
					tmp.Insert(_tables[i]._key,_tables[i]._value);
				}
			}
			std::swap(_tables,tmp._tables);
			std::swap(_size,tmp._size);
		}
	}
	size_t _getNewSize(size_t size= 0){
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] ={
        53ul,         97ul,         193ul,       389ul,			769ul,
        1543ul,       3079ul,       6151ul,      12289ul,		24593ul,
        49157ul,      98317ul,      196613ul,    393241ul,		786433ul,
        1572869ul,    3145739ul,    6291469ul,   12582917ul,	25165843ul,
        50331653ul,   100663319ul,  201326611ul, 402653189ul,	805306457ul,
        1610612741ul, 3221225473ul, 4294967291ul
	};
		for(size_t i=0; i<_PrimeSize; ++i){
			if(size < _PrimeList[i]){
				return _PrimeList[i];
			}
		}
		return _PrimeList[0];
	}
	size_t _HashFunc(const K &key){
		HashFunc hf;
		return hf(key)%_tables.size();
	}
private:
	std::vector<Node> _tables;
	size_t _size;
};
