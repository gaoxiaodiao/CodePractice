/*
*文件说明:测试文件
*作者:高小调
*日期:
*集成开发环境:Microsoft Visual Studio 2010
*/
#include<iostream>
using namespace std;
#include"AVLTree3.h"
void AVLTreeTest(){
	AVLTree<int,int> t;
	int arr[] ={4,2,6,1,3,5,15,7,16,14};
	for(int i=0; i<sizeof(arr)/sizeof(arr[0]); ++i){
		t.Insert(arr[i],i);
	}
	t.InOrderNonR();
	cout<<"该树是否平衡"<<t.IsBalance() <<" "<<t.IsBalanceOP()<<endl;
}
int main(){
	AVLTreeTest();
	return 0;
}