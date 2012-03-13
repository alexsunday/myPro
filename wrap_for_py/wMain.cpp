#include <iostream>
#include <boost/python.hpp>

#include "iso8583_field_def.h"
#include "iso8583_wrappers.h"
using namespace std;
using namespace boost::python;
// #define PE_POS_DEF		1			//交费易POS终端
// #define PE_8583_64_DEF	2			//交费易64域
// #define DGBANK_DEF		3			//东莞银行
// #define GUANGUNIONPAY 	4			//广东银联无磁交易

class myISO8583
{
private:
	ISO8583_MSG *msg;

public:
	myISO8583():msg(NULL) {}
	~myISO8583()
	{
		if (msg)
		{
			ISO8583_free(msg);
		}
	}
	void getField(int  fieldidx , char* outBuf, int outMaxLen)
	{
		//
	}
	void setField( int fieldidx , char* fieldv , int fieldlen)
	{
		//
	}
	int setData(char* dataBuf , int dataLen , int bizType)
	{
		if (msg)
		{
			ISO8583_free(msg);
		}

		switch(bizType)
		{
		case 1:
			{
				//交费易POS终端
				msg = ISO8583_malloc(PE_POS_DEF , sizeof PE_POS_DEF , BITS_64 , 1);
				break;
			}
		case 2:
			{
				//交费易64域
				break;
			}
		case 3:
			{
				//东莞银行
				break;
			}
		case 4:
			{
				//广东银联无磁交易
				break;
			}
		default:
			{
				break;
			}
		}

		if (!msg)
		{
			return -1;
		}

		return ISO8583_set_msg(msg , (unsigned char*)dataBuf , dataLen);
	}
	void getData(char* outBuf , int outMaxLen)
	{
		//
	}
	string getField(int fieldidx)
	{
		//
	}
	string getData_hex(int bizType)
	{
		//
	}
	int setData(const string& hexString , int bizType)
	{
		char tmpBuf[1024] = { 0 };
		int retLen = 0;
		
		retLen = hexToByte(hexString.c_str() , tmpBuf , hexString.size() +1 ,0 );
		return setData(tmpBuf , retLen , bizType );
	}
	string bizType()
	{
		//
	}

};


BOOST_PYTHON_MODULE(ISO8583)
{
	class_<myISO8583>("ISO8583" ,"Just a TEST")
		.def("setData",&myISO8583::setData , "DOC string1" , arg("hexString") , arg("bizType"))
		.def("getData",&myISO8583::getData , "DOC string2" , arg("outBuf") , arg("outMaxLen"));
}

