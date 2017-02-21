#include<iostream>
using namespace std;
#include"RBTree6.h"
void Test(){
	RBTree<int,int> t;
	int arr[2][10] = {{2,4,5,3,6,9,1,0,7,8},
					{4,2,6,1,3,5,15,7,16,14}
	};
	for(int j=0; j<2; ++j){
		for(int i=0; i<sizeof(arr[0])/sizeof(arr[0][0]); ++i){
			t.insert(arr[j][i],i);
			std::cout<<arr[j][i]<<":"<<t.isBalance()<<" ";
		}
		cout<<endl;
	}
	//t.InOrder();
}
int main(){
	Test();
	return 0;
}
#if 0
#include<iostream>
using namespace std;
#include"RBTree2.h"
void Test(){
	RBTree<int,int> t;
	int arr[2][10] = {{2,4,5,3,6,9,1,0,7,8},
					{4,2,6,1,3,5,15,7,16,14}
	};
	for(int j=0; j<2; ++j){
		for(int i=0; i<sizeof(arr[0])/sizeof(arr[0][0]); ++i){
			t.Insert(arr[j][i],i);
			std::cout<<arr[j][i]<<":"<<t.IsBalance()<<" ";
		}
		cout<<endl;
	}
	//t.InOrder();
}
int main(){
	Test();
	return 0;
}
#endif