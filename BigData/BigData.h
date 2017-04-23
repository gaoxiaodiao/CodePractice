/*
*�ļ�˵��:�����ݴ����������
*����:��С��
*����:2017-04-21
*���ɿ�������:Microsoft Visual Studio 2010 
*/
#include<string>
#include<cstdlib>
#include<cassert>
typedef long long INT64;
const INT64 MaxValue = 9223372036854775807;
const INT64 MinValue = -9223372036854775808;
const size_t MaxSize = 21;	//�������19λ + ����λ + '\0'
class BigData{
friend	std::ostream &operator<<(std::ostream &,const BigData &);
friend	void TestBigData3();
public:
	BigData();					//Ĭ�Ϲ��캯��:��ʼ��Ϊ0
	BigData(INT64 value);		//INT64
	BigData(const char* value);	//�ַ���
public:
	BigData operator+(const BigData& )const;
	BigData operator-(const BigData& )const;
	BigData operator*(const BigData& )const;
	BigData operator/(const BigData& )const;
protected:
	static std::string _Add(std::string *,std::string *);
	static std::string _Sub(std::string *,std::string *);
	static std::string _Mul(std::string *,std::string *);
	static std::string _Div(std::string *,std::string *);
	//����Ƿ����
	bool _CheckIsOverflow()const;
	//ɾ������Ŀո���0
	char* _DeleteBlank(const char* str);
	//���캯��ר��
	void _StringToData(const char*str,int&);
	//��64λ����תΪ�ַ���
	void _Int64ToString(INT64,int&);
private:
	INT64 _intValue;
	std::string _strValue;
};
