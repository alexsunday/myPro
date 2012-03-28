#include "ISO8583.h"
#include <vector>
#include <iostream>
using namespace std;

int main()
{
	ISO8583 a;
	std::vector<ISO8583_DEF> b;
	a.loadConfig("config.xml",b);

	return 0;
}