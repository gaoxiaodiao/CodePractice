/*
*�ļ�˵��:�����ݴ������ʵ��
*����:��С��
*����:2017-04-21
*���ɿ�������:Microsoft Visual Studio 2010 
*/
#include"BigData.h"
//ȱʡ���캯��
BigData::BigData()
	:_intValue(0)
	,_strValue("0"){}
//���Ͳ����Ĺ��캯��
BigData::BigData(INT64 value)
	:_intValue(value){
	_strValue.resize(20);
	_Int64ToString(value);
}
//�ַ�������
BigData::BigData(const char *strValue)
	:_intValue(0){
	size_t len = std::strlen(strValue);
	_strValue.resize(len+1);	//���з���λ
	_StringToData(strValue);
}
//ȥ���ո���0
char* BigData::_DeleteBlank(const char* str){
	while(*str=='0' || *str==' '){
		++str;
	}
	return (char*)str;
}

//����������ת��Ϊ�ַ���,������_strValue
void BigData::_Int64ToString(INT64 value){
	//�������
	_strValue[0] = value>=0?'+':'-';
	//��������
	char *str = (char*)_strValue.c_str()+1;
	char *start = str;
	if(value==0){
		//valueΪ0,�������⴦��
		*str = '0';
		return ;
	}else if(value == MinValue){
		//valueΪ�������ֵ,�޷�תΪ����
		//�ڴ˽������⴦��
		strcpy(str,"9223372036854775808");
		return ;
	}else if(value <0){
		//���valueΪ����,����ת��Ϊ�������д���
		value = 0-value;
	}
	//����ת�ַ���,��ʱת�����������������,
	//ת��֮����Ҫ�����������
	while(value){
		*str++ = value%10 +'0';
		value /= 10;
	}
	//�ַ�������,����������ֵߵ�����,������������.
	char *end = str-1;
	while(start<end){
		char tmp = *start;
		*start = *end;
		*end = tmp;
		start++;
		end --;
	}
}
void BigData::_StringToData(const char *str){
	char symbol = '+';
	char *cur = (char*)str;
	int count = 0;
	//ȥ���ո�������0("     000123456")
	cur = _DeleteBlank(cur);
	//��"00000000000"��
	if(*cur=='\0'){
		_strValue[0] = '+';
		_strValue[1] = '0';
		return ;
	}
	//����з���
	if(*cur=='-' || *cur=='+'){
		//��ȡ����λ"+123456789"��"-456123456"	
		symbol = *cur++;
	}
	//�ٴ�ȥ���ո�������0("+00000123456789")
	cur  = _DeleteBlank(cur);
	if(*cur=='\0'){
		//"+000000000000"
		_strValue[0] = '+';
		_strValue[1] = '0';
		return ;
	}
	//�������ֲ���,
	//ͬʱ�������е�����ת��ΪINT64
	_strValue[0] = symbol;
	char *dest = (char*)_strValue.c_str()+1;
	while(*cur>='0' && *cur<='9'){
		*dest++ = *cur;	//�������е����ֿ����ַ�����
		_intValue = _intValue*10 + *cur++ - '0';	//����������תΪINT64 
		++count;
	}
	if(symbol == '-'){
		_intValue = 0-_intValue;
	}
	_strValue.resize(count+1+1);
}
//�������ֵ�Ƿ����
bool BigData::_CheckIsOverflow()const{
	if(_strValue.size() > 21){
		//λ������INT64���ֵ,һ�����
		return true;
	}else if(_strValue.size() == 21){
		//λ�����
		const char *Max = "+9223372036854775807";
		const char *Min = "-9223372036854775808";
		if(_strValue[0] == '+' && std::strcmp(_strValue.c_str(),Max) > 0||
			_strValue[0] == '-' && std::strcmp(_strValue.c_str(),Min) > 0){
			return true;
		}
	}
	return false;
}
BigData BigData::operator+(const BigData& bd)const{
	//�ж��������Ƿ������(���Ż�)
	if(_CheckIsOverflow() || bd._CheckIsOverflow()){
		//����������һ�����,���ַ��������������
		return BigData(_Add((std::string *)&_strValue,(std::string*)&bd._strValue).c_str());
	}

	//�ж�������֮���Ƿ����
	//10 - 3 = 7   7 6 5 4 3 2 1			//����
	//-10 - -3 =-7  -7 -6 -5 -4 -3 -2 -1	//����
	if(_strValue[0]=='+' && bd._strValue[0]=='+'&& MaxValue-_intValue < bd._intValue || 
		_strValue[0]=='-' && bd._strValue[0]=='-'&& MinValue - _intValue > bd._intValue){
		//������֮�����,���ַ��������������
			return BigData(_Add((std::string *)&_strValue,(std::string*)&bd._strValue).c_str());
	}
	//ʣ�����,�������������,�����ͼ���
	return BigData(_intValue+bd._intValue);
}
std::string BigData::_Add(std::string *left,std::string* right){
	int LSize = left->size();
	int RSize = right->size();
	//�ж����Ҳ�������λ��
	if(RSize > LSize){
		//ȷ�����������λ�������Ҳ�����
		std::swap(left,right);
		std::swap(LSize,RSize);
	}
	//��������Ž��д���
	if((*left)[0]=='+'&&(*right)[0]=='-'){
		//��222222+ -111,���Ҳ��������б��,���ü���
		(*right)[0] = '+';
		std::string ret  =  _Sub(left,right);
		(*right)[0] = '-';
		return ret;
	}else if((*left)[0] == '-' && (*right)[0]=='+'){
		//��-222222 + 1111,������������б��,���ü���
		(*left)[0] = '+';
		std::string ret = _Sub(left,right);
		(*left)[0] = '-';
		ret[0] = '-';
		return ret;
	}
	//ʣ�µľ���ͬ�����,����������ĳ���>=�Ҳ���������
	int step = 0;
	std::string sum;
	sum.resize(LSize+1);
	//���м���
	for(int i=0; i<LSize-2; ++i){
		//��������λ��\0
		int l = (*left)[LSize-i-1-1] - '0';	//ȡ�������û�д�������λ
		int ret = 0;
		//if(i<RSize){
		if(RSize-i-1-1 > 0){
			//�Ҳ�����,��û������λ��
			int r = (*right)[RSize-i-1-1] - '0';	//ȡ�Ҳ�����û�д�������λ
			ret = l+r+step;				//�������					//��λ���ֵ
		}else{
			//�Ҳ���ֵ�Ѿ�����
			ret = l+step;
		}
		step = ret/10;					//��ȡ�½�λ
		ret %= 10;	
		sum[LSize-i-1] = ret + '0';		//����λ���ֵ���������
	}
	sum[0] = (*left)[0];
	sum[1] = step + '0';
	return (char*)sum.c_str();
}

BigData BigData::operator-(const BigData & bd)const{
	//���ߴ������
	if(_CheckIsOverflow() || bd._CheckIsOverflow()){
		//ͨ���ַ������мӼ�
		return BigData(_Sub((std::string *)&_strValue,(std::string*)&bd._strValue).c_str());
	}
	//���
	if(_strValue[0]!=bd._strValue[0]){
		//ͨ���ַ������мӼ�
		return BigData(_Sub((std::string *)&_strValue,(std::string*)&bd._strValue).c_str());
	}
	//�����������ͬ��,���һ�������,ͨ�����ͽ��мӼ�
	return BigData(_intValue-bd._intValue);
}
std::string BigData::_Sub(std::string *left,std::string* right){
	int LSize = left->size();
	int RSize = right->size();
	//�ж����Ҳ�������λ��
	if(RSize > LSize){
		//ȷ�����������ֵ�����Ҳ�����
		std::swap(left,right);
		std::swap(LSize,RSize);
	}
	//��������Ž��д���
	if((*left)[0]=='+'&&(*right)[0]=='-'){
		//��222222 - -111,���Ҳ��������б��,���üӷ�
		(*right)[0] = '+';
		std::string ret  =  _Add(left,right);
		(*right)[0] = '-';
		return ret;		
	}else if((*left)[0] == '-' && (*right)[0]=='+'){
		//��-222222 - 1111,������������б��,���üӷ�
		(*right)[0] = '-';
		std::string ret  = _Add(left,right);
		(*right)[0] = '+';
		ret[0] = '-';
		return ret;	//��ʽת��
	}
	//ʣ�µľ���ͬ�����,������������ȴ����Ҳ�������
	if((*left)[0]=='-'){
		//������Ҳ�������Ϊ�� -100 - -20 = -100 + 20
		//��ʱ����ת��Ϊ��,��Ϊ�ӷ���������ת��Ϊ�˼���
		(*left)[0] = (*right)[0] = '+';
		std::string ret  = _Sub(left,right);	//����ת����ݹ�����Լ�
		(*left)[0] = (*right)[0] = '-';
		ret[0] = '-';
		return ret;
	}
	int step = 0;
	std::string sum;
	sum.resize(LSize+1);
	//���м���
	for(int i=0; i<LSize-2; ++i){
		//��������λ��\0
		int l = (*left)[LSize-i-1-1] - '0';	//ȡ�������û�д�������λ
		int ret = 0;
		//if(i<RSize){
		if(RSize-i-1-1 > 0){
			//�Ҳ�����,��û������λ��
			int r = (*right)[RSize-i-1-1] - '0';	//ȡ�Ҳ�����û�д�������λ
			ret = l-step-r;
			//ret = l+r+step;				//�������					//��λ���ֵ
		}else{
			//�Ҳ���ֵ�Ѿ�����
			ret = l-step;
		}
		//��λ����
		if(ret < 0){
			ret += 10;
			step += 1;
		}
		sum[LSize-i-1] = ret + '0';		//����λ���ֵ���������
	}
	sum[0] = (*left)[0];
	sum[1] = step + '0';
	return (char*)sum.c_str();
}



//�������
std::ostream &operator<<(std::ostream & _cout,const BigData & bd){
	_cout<<bd._strValue.c_str();
	return _cout;
}

/*

const char* BigData::_Sub(std::string *left,std::string* right){
	int LSize = left->size();
	int RSize = right->size();
	//�ж����Ҳ�������λ��
	if(RSize > LSize || 
		RSize==LSize&&strcmp(right->c_str(),left->c_str()) > 0){
		//ȷ�����������ֵ�����Ҳ�����
		std::swap(left,right);
		std::swap(LSize,RSize);
	}
	//��������Ž��д���
	if((*left)[0]=='+'&&(*right)[0]=='-'){
		//��222222 - -111,���Ҳ��������б��,���üӷ�
		(*right)[0] = '+';
		const char* ret =  _Add(left,right);
		(*right)[0] = '-';
		return ret;		
	}else if((*left)[0] == '-' && (*right)[0]=='+'){
		//��-222222 - 1111,������������б��,���üӷ�
		(*right)[0] = '-';
		const char * ret = _Add(left,right);
		(*right)[0] = '+';
		return ret;	//��ʽת��
	}
	//ʣ�µľ���ͬ�����,�������������ֵ�����Ҳ�������ֵ
	int step = 0;
	std::string sum;
	sum.resize(LSize+1);
	//���м���
	for(int i=0; i<LSize-2; ++i){
		//��������λ��\0
		int l = (*left)[LSize-i-1-1] - '0';	//ȡ�������û�д�������λ
		int ret = 0;
		//if(i<RSize){
		if(RSize-i-1-1 > 0){
			//�Ҳ�����,��û������λ��
			int r = (*right)[RSize-i-1-1] - '0';	//ȡ�Ҳ�����û�д�������λ
			ret = l-step-r;
			//ret = l+r+step;				//�������					//��λ���ֵ
		}else{
			//�Ҳ���ֵ�Ѿ�����
			ret = l-step;
		}
		//��λ����
		if(ret < 0){
			ret += 10;
			step += 1;
		}
		sum[LSize-i-1] = ret + '0';		//����λ���ֵ���������
	}
	sum[0] = (*left)[0];
	sum[1] = step + '0';
	return sum.c_str();
}


*/
















































/*
//�ַ����ӷ�
BigData BigData::_Add(BigData &bd){
	std::string *left = &_strValue;
	std::string *right = &bd._strValue;
	size_t LSize = left->size();
	size_t RSize = right->size();
	//ȷ���������λ�����Ҳ�����λ����
	if(RSize>LSize){
		std::swap(left,right);
		std::swap(LSize,RSize);
	}
	//���������ӵ����
	if((*left)[0]== '+' && (*right)[0] == '-' ){
		//���Ҳ��������б��,Ȼ����ü�������
		(*right)[0] = '+';
		//ub()
	}
}
*/