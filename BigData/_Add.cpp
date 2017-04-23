#include"BigData.h"
BigData BigData::operator+(const BigData& bd)const{
	//�ж��������Ƿ������
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
	bool symbol = '+';
	//�ж����Ҳ�������λ��
	if(RSize > LSize ){
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
	return sum;
}