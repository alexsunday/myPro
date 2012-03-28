#ifndef _ISO_8583_H_RAND_fi3nd
#define _ISO_8583_H_RAND_fi3nd

#include <iostream>
#include <vector>
#include "iso8583_wrappers.h"

class ISO8583
{
private:
	ISO8583_MSG *msg;

public:
	ISO8583();
	~ISO8583();

	void getField(int  fieldidx , char* outBuf, int outMaxLen);

	void setField( int fieldidx , char* fieldv , int fieldlen);

	int setData(char* dataBuf , int dataLen , int bizType);

	void getData(char* outBuf , int outMaxLen);

	std::string getField(int fieldidx);

	std::string getData_hex(int bizType);

	int setData(const std::string& hexString , int bizType)
	{
		char tmpBuf[1024] = { 0 };
		int retLen = 0;
		
		retLen = hexToByte(hexString.c_str() , tmpBuf , hexString.size() +1 ,0 );
		return setData(tmpBuf , retLen , bizType );
	}

	std::string bizType();
/*private:*/
	bool loadConfig(const std::string& configFile, std::vector<ISO8583_DEF>& vid);
};


#endif
