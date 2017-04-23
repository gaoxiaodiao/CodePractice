/*
*文件说明:大数据处理相关实现
*作者:高小调
*日期:2017-04-21
*集成开发环境:Microsoft Visual Studio 2010 
*/
#include"BigData.h"
//缺省构造函数
BigData::BigData()
	:_intValue(0)
	,_strValue("0"){}
//整型参数的构造函数
BigData::BigData(INT64 value)
	:_intValue(value){
	int count = 2;
	_strValue.resize(MaxSize);
	_Int64ToString(value,count);
	_strValue.resize(count);
}
//字符串构造
BigData::BigData(const char *strValue)
	:_intValue(0){
	size_t len = std::strlen(strValue);
	int count = 2;
	_strValue.resize(len+2);	//还有符号位
	_StringToData(strValue,count);
	_strValue.resize(count);
}
//去除空格与0
char* BigData::_DeleteBlank(const char* str){
	while(*str=='0' || *str==' '){
		++str;
	}
	return (char*)str;
}

//将整型数字转化为字符串,并存入_strValue
void BigData::_Int64ToString(INT64 value,int &count){
	//处理符号
	_strValue[0] = value>=0?'+':'-';
	//处理数字
	char *str = (char*)_strValue.c_str()+1;
	char *start = str;
	if(value==0){
		//value为0,进行特殊处理
		*str = '0';
		count++;
		return ;
	}else if(value == MinValue){
		//value为负数最大值,无法转为正数
		//在此进行特殊处理
		strcpy(str,"9223372036854775808");
		count = MaxSize;
		return ;
	}else if(value <0){
		//如果value为负数,则将其转换为正数进行处理
		value = 0-value;
	}
	//整数转字符串,此时转出来的数字是逆序的,
	//转完之后需要进行逆序操作
	while(value){
		*str++ = value%10 +'0';
		value /= 10;
		count++;
	}
	//字符串逆序,把逆序的数字颠倒过来,让它变成正序的.
	char *end = str-1;
	while(start<end){
		char tmp = *start;
		*start = *end;
		*end = tmp;
		start++;
		end --;
	}
}
void BigData::_StringToData(const char *str,int& count){
	char symbol = '+';
	char *cur = (char*)str;
	//去除空格与多余的0("     000123456")
	cur = _DeleteBlank(cur);
	//（"00000000000"）
	if(*cur=='\0'){
		_strValue[0] = '+';
		_strValue[1] = '0';
		count++;
		return ;
	}
	//如果有符号
	if(*cur=='-' || *cur=='+'){
		//获取符号位"+123456789"、"-456123456"	
		symbol = *cur++;
	}
	//再次去除空格与多余的0("+00000123456789")
	cur  = _DeleteBlank(cur);
	if(*cur=='\0'){
		//"+000000000000"
		_strValue[0] = '+';
		_strValue[1] = '0';
		count++;
		return ;
	}
	//进入数字部分,
	//同时将参数中的数字转换为INT64
	_strValue[0] = symbol;
	char *dest = (char*)_strValue.c_str()+1;
	while(*cur>='0' && *cur<='9'){
		*dest++ = *cur;	//将参数中的数字拷入字符串中
		_intValue = _intValue*10 + *cur++ - '0';	//将参数数字转为INT64 
		++count;
	}
	if(symbol == '-'){
		_intValue = 0-_intValue;
	}
}

//检查整型值是否溢出
bool BigData::_CheckIsOverflow()const{
	if(_strValue.size() > MaxSize){
		//位数超过INT64最大值,一定溢出
		return true;
	}else if(_strValue.size() == MaxSize){
		//位数相等
		const char *Max = "+9223372036854775807";
		const char *Min = "-9223372036854775808";
		if(_strValue[0] == '+' && std::strcmp(_strValue.c_str(),Max) > 0||
			_strValue[0] == '-' && std::strcmp(_strValue.c_str(),Min) > 0){
			return true;
		}
	}
	return false;
}


BigData BigData::operator-(const BigData & bd)const{
	//两者其中之一溢出,或者都溢出
	if(_CheckIsOverflow()||bd._CheckIsOverflow()){
		//通过字符串进行加减
		return BigData(_Sub((std::string *)&_strValue,(std::string*)&bd._strValue).c_str());
	}

	//两个都不溢出,其运算结果溢出(异号且位数等于19)
	if(_strValue[0]!=bd._strValue[0] && 
	_strValue.size()>=MaxSize|| bd._strValue.size()>=MaxSize){
		//通过字符串进行加减
		return BigData(_Sub((std::string *)&_strValue,(std::string*)&bd._strValue).c_str());
	}

	//不存在溢出且同号,结果一定不溢出,通过整型进行加减
	return BigData(_intValue-bd._intValue);

}
std::string BigData::_Sub(std::string *left,std::string* right){
	int LSize = left->size();
	int RSize = right->size();
	//判断左右操作数的位数
	if(RSize > LSize){
		//右操作数位数大于左操作数位数
		std::string ret;
		if((*left)[0]=='+'&&(*right)[0]=='+'){
			//100 - 1000 = -(1000-100)
			ret = _Sub(right,left);
			ret[0] = '-';
		}else if((*left)[0] =='-'&& (*right)[0] == '-'){
			// -100 - -1000 = 1000-100
			(*left)[0] = '+';
			(*right)[0] = '+';
			ret = _Sub(right,left);
			(*left)[0] = '-';
			(*right)[0] = '-';
		}else if((*left)[0] == '+' && (*right)[0] == '-'){
			//100 - -1000   1000 + 100
			(*right)[0] = '+';
			ret = _Add(right,left);
			(*right)[0] = '-';
		}else if((*left)[0] == '-' && (*right)[0] == '+'){
			//-100 - 1000
			(*left)[0] = '+';
			ret = _Add(right,left);
			(*left)[0] = '-';
			ret[0] = '-';
		}else{
			assert(false);
		}
		return ret;
	}
	//对两种异号进行处理
	if((*left)[0]=='+'&&(*right)[0]=='-'){
		//即222222 - -111,对右操作数进行变号,调用加法
		(*right)[0] = '+';
		std::string ret  =  _Add(left,right);
		(*right)[0] = '-';
		return ret;		
	}else if((*left)[0] == '-' && (*right)[0]=='+'){
		//即-222222 - 1111,对左操作数进行变号,调用加法
		(*right)[0] = '-';
		std::string ret  = _Add(left,right);
		(*right)[0] = '+';
		ret[0] = '-';
		return ret;	//隐式转换
	}
	//剩下的就是同号情况,且左操作数长度大于右操作长度
	if((*left)[0]=='-'){
		//如果左右操作数均为负 -100 - -20 = -100 + 20
		//此时不能转换为加,因为加法将此问题转化为了减法
		(*left)[0] = (*right)[0] = '+';
		std::string ret  = _Sub(left,right);	//参数转化后递归调用自己
		(*left)[0] = (*right)[0] = '-';
		ret[0] = '-';
		return ret;
	}
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
			ret = l-step-r;
			//ret = l+r+step;				//进行相加					//进位后的值
		}else{
			//右操作值已经完了
			ret = l-step;
		}
		//借位处理
		if(ret < 0){
			ret += 10;
			step += 1;
		}
		sum[LSize-i-1] = ret + '0';		//将借位后的值放入和里面
	}
	sum[0] = (*left)[0];
	sum[1] = step + '0';
	return sum.c_str();
}



//输出函数
std::ostream &operator<<(std::ostream & _cout,const BigData & bd){
	_cout<<bd._strValue.c_str();
	return _cout;
}

/*

const char* BigData::_Sub(std::string *left,std::string* right){
	int LSize = left->size();
	int RSize = right->size();
	//判断左右操作数的位数
	if(RSize > LSize || 
		RSize==LSize&&strcmp(right->c_str(),left->c_str()) > 0){
		//确保左操作数数值大于右操作数
		std::swap(left,right);
		std::swap(LSize,RSize);
	}
	//对两种异号进行处理
	if((*left)[0]=='+'&&(*right)[0]=='-'){
		//即222222 - -111,对右操作数进行变号,调用加法
		(*right)[0] = '+';
		const char* ret =  _Add(left,right);
		(*right)[0] = '-';
		return ret;		
	}else if((*left)[0] == '-' && (*right)[0]=='+'){
		//即-222222 - 1111,对左操作数进行变号,调用加法
		(*right)[0] = '-';
		const char * ret = _Add(left,right);
		(*right)[0] = '+';
		return ret;	//隐式转换
	}
	//剩下的就是同号情况,且左操作数的数值大于右操作数数值
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
			ret = l-step-r;
			//ret = l+r+step;				//进行相加					//进位后的值
		}else{
			//右操作值已经完了
			ret = l-step;
		}
		//借位处理
		if(ret < 0){
			ret += 10;
			step += 1;
		}
		sum[LSize-i-1] = ret + '0';		//将借位后的值放入和里面
	}
	sum[0] = (*left)[0];
	sum[1] = step + '0';
	return sum.c_str();
}


*/
















































/*
//字符串加法
BigData BigData::_Add(BigData &bd){
	std::string *left = &_strValue;
	std::string *right = &bd._strValue;
	size_t LSize = left->size();
	size_t RSize = right->size();
	//确保左操作数位数比右操作数位数多
	if(RSize>LSize){
		std::swap(left,right);
		std::swap(LSize,RSize);
	}
	//处理异号相加的情况
	if((*left)[0]== '+' && (*right)[0] == '-' ){
		//对右操作数进行变号,然后调用减法程序
		(*right)[0] = '+';
		//ub()
	}
}
*/