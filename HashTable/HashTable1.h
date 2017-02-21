/*
*文件说明:哈希表相关声明及实现
*作者:高小调
*日期:2017-02-17
*集成开发环境:Microsoft Visual Studio 2010 
*/
#pragma once
#include<vector>
enum Status{
	EMPTY,
	DELETE,
	EXIST
};
template<typename K,typename V>
struct HashNode{
	K _key;
	V _value;
	Status _status;
	HashNode(const K & key = K(),const V & value=V())
		:_key(key)
		,_value(value)
		,_status(EMPTY){}
};
template<typename K>
struct HashFunc{
	size_t operator()(const K& key){
		return key;
	}
};
template<typename K,typename V,typename HashFunc = HashFunc<K> >
class HashTable{
public:
	typedef HashNode<K,V> Node;
	HashTable(const size_t size = 10)
		:_size(0){
		_hash.resize(size);
	}
public:
	std::pair<Node*,bool> Insert(const K &key,const V& value){
		_CheckCapacity();
		size_t index = _HashFunc(key);
		while(_hash[index]._status==EXIST){
			if(_hash[index]._key == key){
				return make_pair(&_hash[index],false);
			}
			++index;
			if(index == _hash.size()){
				index = 0;
			}
		}
		_hash[index]._key = key;
		_hash[index]._value = value;
		_hash[index]._status = EXIST;
		++_size;
		return std::make_pair(&_hash[index],true);
	}

	std::pair<Node*,bool> Find(const K&key){
		size_t index = _HashFunc(key);
		while(_hash[index]._status!=EMPTY){
			if(_hash[index]._key == key && _hash[index]._status==EXIST){
				return std::make_pair(&_hash[index],true);
			}
			++index;
			if(index==_hash.size()){
				index = 0;
			}
		}
		return make_pair((Node *)NULL,false);
	}
	void Remove(const K&key){
		Node *del = Find(key)->first;
		if(del!=NULL){
			del->_status = DELETE;
			--_size;
		}
	}
protected:
	size_t _HashFunc(const K &key){
		HashFunc hf;
		return hf(key)%_hash.size();
	}
	void _CheckCapacity(){
		if(_hash.empty()){
			_hash.resize(7);
			return ;
		}
		if(_size*10/_hash.size()>=7){
			size_t newSize = _GetPrime(_size);
			HashTable<K,V,HashFunc> tmp(newSize);
			for(size_t i=0; i<_hash.size(); ++i){
				if(_hash[i]._status == EXIST){
					tmp.Insert(_hash[i]._key,_hash[i]._value);
				}
			}
			Swap(tmp);
		}
	}
	void Swap(HashTable<K,V,HashFunc> &v){
		std::swap(v._hash,_hash);
		std::swap(v._size,_size);
	}
	size_t _GetPrime(size_t size = 0){
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
private:
	std::vector<Node> _hash;
	size_t _size;
};
