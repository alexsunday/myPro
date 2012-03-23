#include <iostream>
#include "SimpleIni.h"
using namespace std;


int main(int argc , char** argv)
{
	string iniFile;
	if (argc != 1)
		iniFile = argv[0] ; 
	const char *ip,*port,*timeout,*name;
	CSimpleIniA ini;

	ini.SetUnicode();
	ini.LoadFile(iniFile.c_str());
	ip  = ini.GetValue("serv" , "ip" );
	port= ini.GetValue("serv" , "port");
	timeout=ini.GetValue("serv","timeout");

	/*
	1、读取配置 ip、port、data
		读取命令行，若没有，直接读取程序名对应ini
	2、设置连接
	 开始循环
	3、发送并监听回复，异步，显示结果
	4、继续循环
*/

	return -1;
}