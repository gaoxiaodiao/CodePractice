#include<iostream>
#include"UnionSet1.h"
void TestUnionSet(){
	UnionSet<> us(10);
	us.Union(0,6);
	us.Union(0,7);
	us.Union(0,8);

	us.Union(1,4);
	us.Union(1,9);

	us.Union(2,3);
	us.Union(2,5);

	std::cout<<us.GetSize()<<std::endl;
}
int friends(int n,int m,int r[][2]){
	UnionSet<> us(n+1);
	for(int i=0;i<m;++i){
		us.Union(r[i][0],r[i][1]);
	}
	return us.GetSize()-1;
}
void Testfriends(){
	const int n = 5;
	const int m = 3;
	int arr[][2]={{1,2},{2,3},{4,5}};
	std::cout<<friends(n,m,arr)<<std::endl;
}
int main(){
	Testfriends();
	TestUnionSet();
	return 0;
}