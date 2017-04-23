/*
*文件说明:大数据处理相关声明
*作者:高小调
*日期:2017-04-21
*集成开发环境:Microsoft Visual Studio 2010 
*/
#include<string>
#include<cstdlib>
#include<cassert>
typedef long long INT64;
const INT64 MaxValue = 9223372036854775807;
const INT64 MinValue = -9223372036854775808;
const size_t MaxSize = 21;	//最大整型19位 + 符号位 + '\0'
class BigData{
friend	std::ostream &operator<<(std::ostream &,const BigData &);
friend	void TestBigData3();
public:
	BigData();					//默认构造函数:初始化为0
	BigData(INT64 value);		//INT64
	BigData(const char* value);	//字符串
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
	//检查是否溢出
	bool _CheckIsOverflow()const;
	//删除多余的空格与0
	char* _DeleteBlank(const char* str);
	//构造函数专用
	void _StringToData(const char*str,int&);
	//将64位整型转为字符串
	void _Int64ToString(INT64,int&);
private:
	INT64 _intValue;
	std::string _strValue;
};
