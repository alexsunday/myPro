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
	1����ȡ���� ip��port��data
		��ȡ�����У���û�У�ֱ�Ӷ�ȡ��������Ӧini
	2����������
	 ��ʼѭ��
	3�����Ͳ������ظ����첽����ʾ���
	4������ѭ��
*/

	return -1;
}