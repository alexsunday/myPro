#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <ctime>
#include <WinSock2.h>

#include "SimpleIni.h"
#include "packbody_def.h"
#include "packbody_parser.h"
using namespace std;

/*
 *解析iniFile，取出所有需要的控制信息，以map<string,string>形式装订；
 *解析所有的字段信息，以 map< int , string> 存储
 *任何错误返回 -1
 */
int loadConfig(map<string,string>& outControl ,map<int , string>& outData , const string& iniFile)
{
	const char* tmpStr = NULL;
	const char* pause  = NULL;
	const char* circle = NULL;
	const char* log    = NULL;
	const char* ip     = NULL;
	const char* port   = NULL;
	const char* timeout= NULL;
	const char* demo   = NULL;
	const char* type   = NULL;
	const char* header = NULL;
	char  tmpsprint[99]= { 0 };
	string  bitKey    ;
	string str ;
	CSimpleIniA ini;
	CSimpleIniA::TNamesDepend pe_keys;

	assert(iniFile != "" );
	outControl.clear();
	ini.SetUnicode();
	ini.LoadFile(iniFile.c_str());
	
	if (ini.IsEmpty())
	{
		return -1;
	}
	pause  = ini.GetValue("control", "pause");
	circle = ini.GetValue("control", "circle");
	log    = ini.GetValue("control", "log");

	ip     = ini.GetValue("serv" , "ip");
	port   = ini.GetValue("serv",  "port");
	timeout= ini.GetValue("serv",  "timeout");

	demo   = ini.GetValue("pe" , "demo");
	type   = ini.GetValue("pe" , "type");
	header = ini.GetValue("pe" , "header");

	if (  !(pause || circle || log || ip || port || timeout) )
	{
		return -1;
	}

	outControl["pause"]	= pause;
	outControl["circle"]	= circle;
	outControl["log"]		= log;
	outControl["ip"]		= ip;
	outControl["port"]		= port;
	outControl["timeout"]  = timeout;
	
	demo ? outControl["demo"] = demo : outControl["demo"] = "" ;
	type ? outControl["type"] = type : outControl["type"] = "" ;
	header?outControl["header"]=header:outControl["header"]="" ;

	//循环读取字段值
	//恶心的SimpleIni库，用了才发现，能把简单的问题搞这么复杂！！！！哪里simple了！
	//自作多情对返回进行排序，导致我下面的hack！
	//下面这个奇怪的装置能正常工作~
	vector<int> vi;
	ini.GetAllKeys("pe" , pe_keys);
	for (CSimpleIniA::TNamesDepend::const_iterator it = pe_keys.begin(); it != pe_keys.end() ; ++it)
	{
		str = it->pItem ;
		if (  string(str.begin() , str.begin()+3) == "bit"  )
		{
			vi.push_back( atoi(  string(str.begin() + 3,str.end()).c_str()  )   );
		}
	}
	sort(vi.begin(),vi.end());

	for(int i=0; i!= vi.size() ; ++i)
	{
		tmpStr = NULL;
		bitKey = "bit";
		sprintf_s(tmpsprint , sizeof(tmpsprint) , "%d" , vi[i]);
		bitKey += tmpsprint ;
		tmpStr = ini.GetValue("pe" , bitKey.c_str() );
		tmpStr ? outData[vi[i]] = tmpStr : 0;
	}

	return 0;
}

SOCKET setup_socket(const string& ip, const string& port )
{
	WSADATA wsd;
	SOCKADDR_IN srAddr;
	SOCKET fd;
	int i = 3;
	unsigned long ul = 1;
	timeval to;
	fd_set fs;

	to.tv_sec = 3;																//超时设定秒数
	to.tv_usec = 0;																//更精确的在此设定

	if (WSAStartup(MAKEWORD(2, 2), &wsd)) 
	{
		cerr << "WSAStartup error:" << WSAGetLastError() << endl;
		return -1;
	}

	srAddr.sin_family = AF_INET;
	srAddr.sin_addr.s_addr = inet_addr(ip.c_str());
	srAddr.sin_port = htons((short)atoi(port.c_str()));
	if ((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) 
	{
		cerr << "socket error:" << WSAGetLastError() << endl;
		return -1;
	}
	if ( connect(fd , (sockaddr*)&srAddr , sizeof(sockaddr_in)) == INVALID_SOCKET)
	{
		cerr << "connect error:" << WSAGetLastError() << endl;
		return -1;
	}
	
	return fd;
/*
	if(ioctlsocket(fd,FIONBIO,&ul) == SOCKET_ERROR )
	{
		closesocket(fd);
		cerr << "ioctlsocket error:" << WSAGetLastError() << endl;
		return -1;
	}

	do 
	{
		connect(fd , (sockaddr*)&srAddr , sizeof(sockaddr_in)) ;
		FD_ZERO(&fs);
		FD_SET(fd , &fs);

		if(select(0,0,&fs,0,&to) == SOCKET_ERROR)
		{
			closesocket(fd);
			cerr << "select error:" << WSAGetLastError() << endl;
			return -1;
		}

		if (FD_ISSET(fd , &fs))
		{
			//可写数据了！
			//重新设置为阻塞模式
			ul = 0;
			if(ioctlsocket(fd,FIONBIO,&ul) == SOCKET_ERROR )
			{
				closesocket(fd);
				cerr << "ioctlsocket error:" << WSAGetLastError() << endl;
				return -1;
			}
			return fd;
		}
		else
		{
			//timeout!
			cerr << "Connection failed, and retry... ... " << endl;
			--i;
			if(i == 0)
			{
				cerr << "Connection to " << ip << " failed!" << endl ;
				closesocket(fd);
				return -1;
			}
		}
	} while (i);

	return -1;
*/
}


bool isnotshape(char c)
{
	return c != '#' ;
}

string getrand(int number)
{
	char tmpStr[1024] = { 0 };
	char randStr[2]   = { 0 };
	
	for (int i=0; i!= number ; ++i)
	{
		sprintf_s(randStr, sizeof(randStr) , "%d" , rand()%10 );
		strcat_s(tmpStr,sizeof(tmpStr) , randStr);
	}
	
	return string(tmpStr);
}
/*
 *字符串替换:http://www.byvoid.com/blog/cpp-string/
 */
void string_replace(string & strBig, const string & strsrc, const string &strdst)
{
	string::size_type pos=0;
	string::size_type srclen=strsrc.size();
	string::size_type dstlen=strdst.size();
	while( (pos=strBig.find(strsrc, pos)) != string::npos)
	{
		strBig.replace(pos, srclen, strdst);
		pos += dstlen;
	}
}
string translate(string& msg)
{
	time_t tm = time(NULL);
	char tmpS[32] = { 0 };

	srand(tm);
	if ( !(msg[0] == '%' && msg[msg.size()-1] == '%') )
	{
		return msg;
	}

	msg.erase( 0 , 1);
	msg.erase( msg.size() -1 , 1);
	//###### rand number
	if (find_if(msg.begin(),msg.end(),isnotshape) == msg.end() )
	{
		return getrand(msg.size());
	}
	//hhmmssyyyymmdd
	strftime(tmpS , sizeof(tmpS) , "%Y" , localtime(&tm));
	string_replace(msg , "YYYY",tmpS);
	strftime(tmpS , sizeof(tmpS) , "%y" , localtime(&tm));
	string_replace(msg , "YY",tmpS);

	strftime(tmpS , sizeof(tmpS) , "%m" , localtime(&tm));
	sprintf_s(tmpS , sizeof(tmpS),  "%02d" , atoi(tmpS));
	string_replace(msg , "mm",tmpS);

	strftime(tmpS , sizeof(tmpS) , "%d" , localtime(&tm));
	string_replace(msg , "DD",tmpS);

	strftime(tmpS , sizeof(tmpS) , "%H" , localtime(&tm));
	string_replace(msg , "hh",tmpS);

	strftime(tmpS , sizeof(tmpS) , "%M" , localtime(&tm));
	string_replace(msg , "MM",tmpS);

	strftime(tmpS , sizeof(tmpS) , "%S" , localtime(&tm));
	string_replace(msg , "ss",tmpS);

	return msg;
}
/*
 *headertype为包头类型，结果将数据包体写入buf，不包括包头部分
 *返回包体长度
 *若超时，则返回超时包。
 */
int recvMSG(char* buf , int bufMaxLen , SOCKET fd , const string& headerType)
{
	char headerBuf[1024] = { 0 };
	int curRecv = 0;
	int hasRecv = 0;
	int headerLen = 0;
	int bodyLen = 0;
	//取包头
	while(  (curRecv = recv(fd , headerBuf + hasRecv , headerType.size() - hasRecv , 0 ))>0  )
	{
		curRecv += hasRecv ;
		continue ;
	}
	headerLen = atoi(headerBuf);
	//包体长度
	if (headerType[0] == 'L')
	{
		bodyLen = headerLen - headerType.size();
	}
	else if (headerType[0] == 'l')
	{
		bodyLen = headerLen ;
	}
	else
	{
		//error!
	}
	
	assert(bodyLen <= bufMaxLen );
	//取包体
	curRecv = 0;
	while (  (curRecv = recv(fd , buf + hasRecv , bodyLen - hasRecv , 0 ))>0  ) 
	{
		hasRecv += curRecv;
		continue;
	}

	return hasRecv;
}

int send_recv(const map<string,string>& control, const map<int,string>& data, SOCKET fd )
{
	PKT_MSG *msg = pkt_malloc(FA_PKT_HEAD , sizeof(FA_PKT_HEAD));
	const char*s = NULL;
	char header[1024] = { 0 };
	int headerLen     =   0;
	int headertype	  =   0;
	char buf[2048] = { 0 };
	int bufLen   = 0;
	int curSent    = 0;
	int hasSent	   = 0;

	string tmpInfo;
	for (map<int,string>::const_iterator it = data.begin(); it != data.end(); ++it)
	{
		tmpInfo = it->second ;
		tmpInfo = translate(tmpInfo).c_str();
		pkt_set_field(msg , it->first, (char *)tmpInfo.c_str()  , tmpInfo.size() );
	}

	pkt_get_msg(msg , (unsigned char*)buf + control.find("header")->second.size() ,  \
		sizeof(buf) -control.find("header")->second.size() , &bufLen);

	tmpInfo = control.find("header")->second;
	if (tmpInfo[0] == 'L')
	{
		sprintf_s(buf , tmpInfo.size() , "%d" , bufLen + tmpInfo.size());
	}
	else if (tmpInfo[0] == 'l')
	{
		sprintf_s(buf , tmpInfo.size() , "%d" , bufLen );
	}
	else
	{
		//error!
	}
	cout<< "======================================SEND======================================" << endl;
	pkt_print(msg);
	
	//send
	while( (curSent = send(fd , buf + hasSent, bufLen - hasSent, 0)) > 0 ) 
	{
		hasSent += curSent ;
		continue;
	}
	pkt_free(msg);
	msg = NULL;

	// recv
	bufLen = recvMSG(buf , sizeof(buf) , fd , control.find("header")->second);
	cout<< "======================================RECV======================================" << endl;
	msg = pkt_malloc(FA_PKT_HEAD , sizeof(FA_PKT_HEAD));
	pkt_set_msg(msg , (unsigned char*)buf , bufLen);
	pkt_print(msg);
	pkt_free(msg);
	return 0;
}

int main(int argc , char** argv)
{
	//1、读取配置 ip、port、data
	//	读取命令行，若没有，直接读取程序名对应ini

	//cout << getrand(20) << endl;
	string iniFile;
	bool isConnected = false;
	SOCKET sock;
	if (argc != 1)
		iniFile = argv[0] ; 
	else
		iniFile = "client_test.ini" ;

	map<string,string> control;
	map<int , string > data;

	if (loadConfig(control , data , iniFile) == -1)
	{
		cerr << "读取配置错误，请重试！" << endl;
		return 1;
	}
	assert(!control.empty() && ! data.empty());
	//开始循环
	int hasCircle = 0;
	do 
	{
		if (isConnected == false)
		{
			sock = setup_socket(control["ip"] , control["port"]);
			isConnected = true;
		}

		if (sock == SOCKET_ERROR)
		{
			cerr << "socket error!" << endl;
			isConnected = false ;
			continue;
		}

		send_recv(control , data , sock);

		closesocket(sock);
		isConnected = false;
		Sleep(atoi(control["pause"].c_str())*1000);
	} while ( ++hasCircle  < atoi(control["circle"].c_str()) );
	
	WSACleanup(); 
	return 0;
}

