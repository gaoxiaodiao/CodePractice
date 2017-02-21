/*
*文件说明:堆的测试用例
*作者:高小调
*日期:2017-1-9
*集成开发环境:Microsoft Visual Studio 2010 
*/
#include<iostream>
#include"Heap1.h"
void TestHeap(){
	int arr[] = {10,16,18,12,11,13,15,17,14,19};
	size_t sz = sizeof(arr)/sizeof(arr[0]);
	Heap<int,Min<int>> h1(arr,sz);	//小堆 10,11,13,12,16,18,15,17,14,19
	Heap<int> h2(arr,sz);			//大堆 19,17,18,14,16,13,15,12,10,11
	
	h1.Pop();						//11,12,13,14,16,18,15,17,19
	h1.Push(5);						//5,11,13,14,12,18,15,17,19,16
	
	h2.Pop();						//18,17,15,14,16,13,11,12,10
	h2.Push(20);					//20,18,15,14,17,13,11,12,10,16
}
int main(){
	TestHeap();
	return 0;
}