#include"BigData.h"

BigData BigData::operator*(const BigData& bd)const{
	//����κ�����Ϊ��
	if(_strValue[1] == '0' || bd._strValue[1]=='0'){
		return BigData("0");
	}
	//һ���κ�����Ϊ�κ���
	if(_strValue.size()==3 && _strValue[1]=='1'){
		return bd;
	}
	if(bd._strValue.size()==3 && bd._strValue[1] == '1'){
		return *this;
	}
	//����֮һ�������
	if(_CheckIsOverflow() || bd._CheckIsOverflow()){
		//�����ַ�����������
		return BigData(_Mul((std::string *)&_strValue,(std::string*)&bd._strValue).c_str());
	//����֮�����
	}else if(_strValue.size() + bd._strValue.size() > MaxSize+2){
		//�����ַ�����������
		std::string ret = _Mul((std::string *)&_strValue,(std::string*)&bd._strValue).c_str();
		return BigData(ret.c_str());
	}
	//һ���������,������ֱ������
	return BigData(_intValue*bd._intValue);
}

//�˷�����
std::string BigData::_Mul(std::string *left,std::string *right){
	int LSize = left->size();
	int RSize = right->size();
	//ȷ���������λ��С���Ҳ�����λ��
	if(LSize>RSize){
		std::swap(left,right);
		std::swap(LSize,RSize);
	}
	std::string ret;
	int retSize = LSize+RSize-2;
	ret.resize(retSize);
	int step = 0;
	int offset = 0;
	//�˷�����
	for(int i =0; i<LSize-2; ++i){
		int l = (*left)[LSize-i-2] - '0';	//ȡ���������
		step = 0;							//��λ��0
		if(l==0){
			ret[retSize-2-offset++] = '0'; 
			continue;
		}
		//���Ҳ�������������
		for(int j=0; j<RSize-2;++j){
			int r = (*right)[RSize-j-2] - '0';	//�õ��Ҳ�����
			int sum = l*r + step;				//���Ҳ��������
			if(ret[retSize-2-j-offset]!=0){
				sum += ret[retSize-2-j-offset] - '0';		//�ټ���һ�������� 
			}
			step = sum/10;
			sum %= 10;
			ret[retSize-2-j-offset] = sum + '0';
		}
		++offset;	//ƫ�Ƽ�1
	}
	ret[0] = (*left)[0]==(*right)[0]?'+':'-';
	ret[1] = step + '0';
	return ret;
}