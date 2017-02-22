/*
*文件说明:
*作者:高小调
*日期:
*集成开发环境:Microsoft Visual Studio 2010 
*/
#include<iostream>
#include"BitMap1.h"
#include"BloomFilter1.h"
void BitMapTest(){
	BitMap bt;
	std::cout<<bt.test(0)<<std::endl;
	std::cout<<bt.test(1)<<std::endl;
	std::cout<<bt.test(2)<<std::endl;
	std::cout<<bt.test(31)<<std::endl;
	std::cout<<bt.test(30)<<std::endl;
	std::cout<<bt.test(29)<<std::endl;
	bt.set(0);
	bt.set(1);
	bt.set(2);
	bt.set(31);
	bt.set(30);
	bt.set(29);
	bt.set(28);
	std::cout<<std::endl;
	std::cout<<bt.test(0)<<std::endl;
	std::cout<<bt.test(1)<<std::endl;
	std::cout<<bt.test(2)<<std::endl;
	std::cout<<bt.test(31)<<std::endl;
	std::cout<<bt.test(30)<<std::endl;
	std::cout<<bt.test(29)<<std::endl;
	std::cout<<std::endl;
	bt.reSet(0);
	bt.reSet(1);
	bt.reSet(2);
	bt.reSet(31);
	bt.reSet(30);
	bt.reSet(29);
	bt.reSet(28);
	std::cout<<std::endl;
	std::cout<<bt.test(0)<<std::endl;
	std::cout<<bt.test(1)<<std::endl;
	std::cout<<bt.test(2)<<std::endl;
	std::cout<<bt.test(31)<<std::endl;
	std::cout<<bt.test(30)<<std::endl;
	std::cout<<bt.test(29)<<std::endl;

}
int main(){
	BitMapTest();
	BloomFilterTest();

	return 0;
}