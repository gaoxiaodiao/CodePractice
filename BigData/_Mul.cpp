#include"BigData.h"

BigData BigData::operator*(const BigData& bd)const{
	//零乘任何数都为零
	if(_strValue[1] == '0' || bd._strValue[1]=='0'){
		return BigData("0");
	}
	//一乘任何数都为任何数
	if(_strValue.size()==3 && _strValue[1]=='1'){
		return bd;
	}
	if(bd._strValue.size()==3 && bd._strValue[1] == '1'){
		return *this;
	}
	//两者之一存在溢出
	if(_CheckIsOverflow() || bd._CheckIsOverflow()){
		//则用字符串进行运算
		return BigData(_Mul((std::string *)&_strValue,(std::string*)&bd._strValue).c_str());
	//两者之积溢出
	}else if(_strValue.size() + bd._strValue.size() > MaxSize+2){
		//则用字符串进行运算
		std::string ret = _Mul((std::string *)&_strValue,(std::string*)&bd._strValue).c_str();
		return BigData(ret.c_str());
	}
	//一定不会溢出,用整型直接运算
	return BigData(_intValue*bd._intValue);
}

//乘法运算
std::string BigData::_Mul(std::string *left,std::string *right){
	int LSize = left->size();
	int RSize = right->size();
	//确保左操作数位数小于右操作数位数
	if(LSize>RSize){
		std::swap(left,right);
		std::swap(LSize,RSize);
	}
	std::string ret;
	int retSize = LSize+RSize-2;
	ret.resize(retSize);
	int step = 0;
	int offset = 0;
	//乘法运算
	for(int i =0; i<LSize-2; ++i){
		int l = (*left)[LSize-i-2] - '0';	//取到左操作数
		step = 0;							//进位清0
		if(l==0){
			ret[retSize-2-offset++] = '0'; 
			continue;
		}
		//与右操作数进行运算
		for(int j=0; j<RSize-2;++j){
			int r = (*right)[RSize-j-2] - '0';	//拿到右操作数
			int sum = l*r + step;				//左、右操作数相加
			if(ret[retSize-2-j-offset]!=0){
				sum += ret[retSize-2-j-offset] - '0';		//再加上一次运算结果 
			}
			step = sum/10;
			sum %= 10;
			ret[retSize-2-j-offset] = sum + '0';
		}
		++offset;	//偏移加1
	}
	ret[0] = (*left)[0]==(*right)[0]?'+':'-';
	ret[1] = step + '0';
	return ret;
}