/*
*文件说明:测试文件
*作者:高小调
*日期:2017-01-08
*集成开发环境:Microsoft Visual Studio 2010 
*/
#include<iostream>
#include"BinarySearchTree1.h"
using namespace std;
void TestInsert(){
	int arr[]={5,3,4,1,7,8,2,6,0,9};
	size_t sz = sizeof(arr)/sizeof(arr[0]);
	BinarySearchTree<int> t;
	for(size_t i=0; i<sz; ++i){
		t.Insert(arr[i]);
	}
	t.InOrder();
	t.Remove(2);
	t.Remove(5);
	t.Remove(8);
	t.Remove(0);
	t.InOrder();


	t.Remove(0);
	t.Remove(1);
	t.Remove(2);
	t.Remove(3);
	t.Remove(4);
	t.Remove(5);
	t.Remove(6);
	t.Remove(7);
	t.Remove(8);
	t.Remove(9);


}
void TestRemove(){
	int arr[]={5,3,1,0,4,2};
	size_t sz = sizeof(arr)/sizeof(arr[0]);
	BinarySearchTree<int> t;
		for(size_t i=0; i<sz; ++i){
		t.Insert(arr[i]);
	}
	t.Remove(0);
	t.Remove(2);
	t.Remove(3);
	t.Remove(4);
	t.Remove(5);
	t.Remove(1);

}
int main(){
	TestRemove();
	return 0;
}