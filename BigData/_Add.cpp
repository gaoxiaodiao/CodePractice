#include"BigData.h"
BigData BigData::operator+(const BigData& bd)const{
	//判断两个数是否有溢出
	if(_CheckIsOverflow() || bd._CheckIsOverflow()){
		//两者其中有一个溢出,用字符串进行相加运算
		return BigData(_Add((std::string *)&_strValue,(std::string*)&bd._strValue).c_str());
	}

	//判断两个数之和是否溢出
	//10 - 3 = 7   7 6 5 4 3 2 1			//正数
	//-10 - -3 =-7  -7 -6 -5 -4 -3 -2 -1	//负数
	if(_strValue[0]=='+' && bd._strValue[0]=='+'&& MaxValue-_intValue < bd._intValue || 
		_strValue[0]=='-' && bd._strValue[0]=='-'&& MinValue - _intValue > bd._intValue){
		//两个数之和溢出,用字符串进行相加运算
			return BigData(_Add((std::string *)&_strValue,(std::string*)&bd._strValue).c_str());
	}
	//剩下情况,计算结果不会溢出,用整型计算
	return BigData(_intValue+bd._intValue);
}
std::string BigData::_Add(std::string *left,std::string* right){
	int LSize = left->size();
	int RSize = right->size();
	bool symbol = '+';
	//判断左右操作数的位数
	if(RSize > LSize ){
		//确保左操作数的位数大于右操作数
		std::swap(left,right);
		std::swap(LSize,RSize);
	}
	//对两种异号进行处理
	if((*left)[0]=='+'&&(*right)[0]=='-'){
		//即222222+ -111,对右操作数进行变号,调用减法
		(*right)[0] = '+';
		std::string ret  =  _Sub(left,right);
		(*right)[0] = '-';
		return ret;
	}else if((*left)[0] == '-' && (*right)[0]=='+'){
		//即-222222 + 1111,对左操作数进行变号,调用减法
		(*left)[0] = '+';
		std::string ret = _Sub(left,right);
		(*left)[0] = '-';
		ret[0] = '-';
		return ret;
	}
	//剩下的就是同号情况,且左操作数的长度>=右操作数长度
	int step = 0;
	std::string sum;
	sum.resize(LSize+1);
	//进行计算
	for(int i=0; i<LSize-2; ++i){
		//减掉符号位和\0
		int l = (*left)[LSize-i-1-1] - '0';	//取左操作数没有处理的最低位
		int ret = 0;
		//if(i<RSize){
		if(RSize-i-1-1 > 0){
			//右操作数,还没到符号位的
			int r = (*right)[RSize-i-1-1] - '0';	//取右操作数没有处理的最低位
			ret = l+r+step;				//进行相加					//进位后的值
		}else{
			//右操作值已经完了
			ret = l+step;
		}
		step = ret/10;					//获取新进位
		ret %= 10;	
		sum[LSize-i-1] = ret + '0';		//将进位后的值放入和里面
	}
	sum[0] = (*left)[0];
	sum[1] = step + '0';
	return sum;
}