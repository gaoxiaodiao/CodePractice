/*
*文件说明:测试红黑树
*作者:高小调
*日期:2017-04-21
*集成开发环境:Microsoft Visual Studio 2010 
*/
#include<iostream>
using namespace std;
#include"RBTree.hpp"
void TestRBTree(){
	RBTree<int,int> rbt;
	int arr[][10] = {{2,4,5,3,6,9,1,0,7,8},
					{4,2,6,1,3,5,15,7,16,14}};
	for(int i=0; i<sizeof(arr)/sizeof(*arr); ++i){
		for(int j=0; j<sizeof(*arr)/sizeof(**arr); ++j){
			rbt.Insert(arr[i][j],i);
			std::cout<<arr[i][j]<<":"<<rbt.CheckIsBalance()<<std::endl;
		}
		rbt.InOrderNonR();
		std::cout<<std::endl;
	}
}
int main(){
	TestRBTree();
	return 0;
}