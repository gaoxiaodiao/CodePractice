/*
*文件说明:
*作者:高小调
*日期:
*集成开发环境:Microsoft Visual Studio 2010 
*/
#include<iostream>

using namespace std;
#include"HashTable2.h"
void TestHashTable(){
	HashTable<int,int> ht(10);
	ht.Insert(89,0);
	ht.Insert(18,0);
	ht.Insert(49,0);
	ht.Insert(58,0);
	ht.Insert(9,0);
	ht.Insert(0,0);
	ht.Insert(1,0);
	ht.Insert(2,0);
	ht.Insert(3,0);
	ht.Insert(4,0);
	ht.Insert(5,0);
	ht.Insert(6,0);
	ht.Insert(7,0);
	ht.Insert(8,0);
	ht.Insert(9,0);
	
	ht.Remove(89);
	ht.Remove(49);

	cout<<ht.Find(89).first<<":"<<ht.Find(89).second<<endl;
	cout<<ht.Find(18).first->_key<<":"<<ht.Find(18).second<<endl;
	cout<<ht.Find(49).first<<":"<<ht.Find(49).second<<endl;
	cout<<ht.Find(58).first->_key<<":"<<ht.Find(58).second<<endl;
	cout<<ht.Find(9).first->_key<<":"<<ht.Find(9).second<<endl;
	cout<<ht.Find(100).first<<":"<<ht.Find(100).second<<endl;
	HashTable<string,string> ht2(7);
	ht2.Insert("left","左边");
	ht2.Insert("right","右边");

}

int main(){
	TestHashTable();
	return 0;
}