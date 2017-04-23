#include"BigData.h"
BigData BigData::operator/(const BigData &bd)const{
	//除数为0
	if(bd._strValue.size()==3 && bd._strValue[1] =='0'){
		assert(false);
	}
	//被除数为0
	if(_strValue.size()==3 && _strValue[1] == '0'){
		return BigData(_strValue.c_str());
	}
	//被除数小于除数（与正负号无关）
	//-3/-5 -3/5 3/-5 3/5 结果均为0
	if(_strValue.size() < bd._strValue.size() ||
		(_strValue.size() == bd._strValue.size()&&
		std::strcmp(_strValue.c_str()+1,bd._strValue.c_str()+1) > 0)){
		return BigData((INT64)0);
	}
	//两者之一溢出
	if(_CheckIsOverflow() || bd._CheckIsOverflow()){
		return BigData(_Div((std::string *)&_strValue,(std::string*)&bd._strValue).c_str());
	}
	//没有溢出,用整型
	return BigData(_intValue/bd._intValue);
}
std::string BigData::_Div(std::string *left,std::string *right){
	//left长度一定大于right长度
	std::string ret;
	ret.resize(left->size());
	int rNum = right->size()-2;
	//除不过,补0
	for(int i=0; i<rNum;++i){
		ret[i] = '0';
	}
	const char* cLeftStart = left->c_str()+1;
	const char* cRightStart = right->c_str()+1;
	int cNum = rNum;
	while(1){
		if(std::strncmp(cLeftStart,cRightStart,cNum) < 0){
			++cNum;
			continue;
		}
		std::string strLeft("+");
		strLeft += cLeftStart;
		std::string strRight("+");

		while(_Sub())
	}



	for(int i=0;i<left->size()-1; ++i){
		if(i<right->size()-2){
			
			break;
		}
	}

	ret[0] = (*left)[0]==(*right)[0]?'+':'-';
	return "";
}