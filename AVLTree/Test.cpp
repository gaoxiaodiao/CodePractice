/*
*�ļ�˵��:�����ļ�
*����:��С��
*����:
*���ɿ�������:Microsoft Visual Studio 2010
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
	cout<<"�����Ƿ�ƽ��"<<t.IsBalance() <<" "<<t.IsBalanceOP()<<endl;
}
int main(){
	AVLTreeTest();
	return 0;
}