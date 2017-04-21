/*
*文件说明:测试文件
*作者:高小调
*日期:2017-04-21
*集成开发环境:Microsoft Visual Studio 2010 
*/
#include<iostream>
using namespace std;
#include"BigData.h"
void Caculator(const BigData &left,const char symbol,const BigData &right){
	switch(symbol){
		case '+':
			cout<<left<<" + "<<right<<" = "<<left+right<<endl;
			break;
		case '-':
			cout<<left<<" - "<<right<<" = "<<left-right<<endl;
			break;
		case '*':
			//cout<<left<<" * "<<right<<" = "<<left*right<<endl;
			break;
		case '/':
			//cout<<left<<" / "<<right<<" = "<<left/right<<endl;
			break;
		default:
			break;
	}
}
//测试加法
void TestBigData4(const char symbol){
	if(symbol!='+'&&symbol!='-'&&symbol!='*'&&symbol!='/'){
		return ;
	}
	//两个都不溢出,和也不溢出
	Caculator("1111",symbol,"2222");
	Caculator("-1111",symbol,"2222");
	Caculator("1111",symbol,"-2222");
	Caculator("-1111",symbol,"-2222");

	//两个都不溢出,和溢出
	Caculator("9223372036854775807",symbol,"100");
	Caculator("9223372036854775807",symbol,"-100");
	Caculator("-9223372036854775807",symbol,"100");
	Caculator("-9223372036854775807",symbol,"-100");

	//两个都溢出
	Caculator("11111111111111111111",symbol,"11111111111111111111111");
	Caculator("11111111111111111111",symbol,"-11111111111111111111111");
	Caculator("-11111111111111111111",symbol,"11111111111111111111111");
	Caculator("-11111111111111111111",symbol,"-11111111111111111111111");
}
void TestBigData3(){
	//测试是否溢出
	BigData bd1("-9223372036854775808");	//最小值
	cout<<bd1._CheckIsOverflow()<<endl;
	BigData bd2("9223372036854775807");		//最大值
	cout<<bd2._CheckIsOverflow()<<endl;
	BigData bd3("9223372036854775806");		//不溢出
	cout<<bd3._CheckIsOverflow()<<endl;
	BigData bd4("-9223372036854775807");	//不溢出
	cout<<bd4._CheckIsOverflow()<<endl;
	BigData bd5("-9223372036854775809");	//溢出
	cout<<bd5._CheckIsOverflow()<<endl;	
	BigData bd6("9223372036854775808");		//溢出
	cout<<bd6._CheckIsOverflow()<<endl;
}
void TestBigData2(){
	//测试BigData(const char *);
	BigData bd1("00123456789");
	BigData bd2("0000-123456789");
	BigData bd3("000000000000000");
	BigData bd4("000000+00000000000");
	BigData bd5("123456789123456789123456789123456789");
	BigData bd6("-123456789123456789123456789123456789");
	BigData bd7("000000+0000000000012313212313131");
}
void TestBigData1(){
	//测试BigData(INT64)
	BigData bd1(MaxValue);
	cout<<bd1<<endl;
	BigData bd2(123456789123);
	cout<<bd2<<endl;
	BigData bd3(MinValue);
	cout<<bd3<<endl;
	BigData bd4((INT64)0);
	cout<<bd4<<endl;
	BigData bd5(-123456789123456789);
	cout<<bd5<<endl;
	BigData bd6(MinValue-10000);
	cout<<bd6<<endl;
}

int main(){
	//ReverseString();
	TestBigData4('-');
	return 0;
}