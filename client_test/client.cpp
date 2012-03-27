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



/****************************************************************
*   Function name    : print_hex
*   Author           : Peng GuoYi
*   Coding Date      : 2012/03/14 15:53
*   Description      : ʮ�����ƴ�ӡ
*   Return type      : 
*   Argument         : 
****************************************************************/
void print_hex(char * data, int data_len)
{
	int i,t,line;
	int fix = 16;
	unsigned char ch;
	int size_line = fix * 5;
	char *pline = (char *)malloc(size_line);
	memset(pline, ' ', size_line);

	printf("--------------");
	for (i = 0; i < fix; i++)
	{
		printf("----");
	}
	printf("\n");

	line = 0;
	for (i = 0 , t = 0; i < data_len ; i ++ )
	{
		ch =  (unsigned char)data[i];
		sprintf(pline + t*3, "%02X ", ch);
		if (ch >= 0x0 && ch <= 0x0D || ch == 0xFF)
		{
			pline[fix*3 + t + 3] = '.';
		}else pline[fix*3 + t + 3] = (char)ch;


		if ((i+1) % fix == 0)
		{			
			pline[fix*3] = ' ';
			pline[fix*3 + 1] = ';';
			pline[fix*3 + fix + 3] = 0;
			printf("%08xh: ",line);
			line += fix;
			printf("%s\n",pline);
			memset(pline, ' ', size_line);
			t = 0;
		}else 
			t ++;
	}

	if(t != 0){
		pline[t*3] = ' ';
		pline[fix*3] = ' ';
		pline[fix*3 + 1] = ';';
		pline[fix*3 + fix + 3] = 0;
		printf("%08xh: ",line);
		printf("%s\n",pline);
	}
	printf("--------------");
	for (i = 0; i < fix; i++)
	{
		printf("----");
	}
	printf("\n");
	free(pline);
}

/*
 *����iniFile��ȡ��������Ҫ�Ŀ�����Ϣ����map<string,string>��ʽװ����
 *�������е��ֶ���Ϣ���� map< int , string> �洢
 *�κδ��󷵻� -1
 */
int loadConfig(map<string,string>& outControl ,map<int , string>& outData , map<int,string> retData , const string& iniFile)
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

	//ѭ����ȡ�ֶ�ֵ
	//���ĵ�SimpleIni�⣬���˲ŷ��֣��ܰѼ򵥵��������ô���ӣ�����������simple�ˣ�
	//��������Է��ؽ������򣬵����������hack��
	//���������ֵ�װ��ֻ��Ϊ�˻�ԭ ini ԭ�е�˳�򣬽�keyֵ�����ִ�С����
	vector<int> vSend,vRecv;
	ini.GetAllKeys("pe" , pe_keys);
	for (CSimpleIniA::TNamesDepend::const_iterator it = pe_keys.begin(); it != pe_keys.end() ; ++it)
	{
		str = it->pItem ;
		if (  string(str.begin() , str.begin()+3) == "bit"  )
		{
			vSend.push_back( atoi(  string(str.begin() + 3,str.end()).c_str()  )   );
		}
		else if ( string(str.begin() , str.begin() + 3) == "RET" )
		{
			vRecv.push_back( atoi(string(str.begin()+3 , str.end()).c_str() ) );
		}
	}

	sort(vSend.begin(),vSend.end());
	sort(vRecv.begin(),vRecv.end());

	string curvalue ;
	for(int i=0; i!= vSend.size() ; ++i)
	{
		tmpStr = NULL;
		bitKey = "bit";
		sprintf_s(tmpsprint , sizeof(tmpsprint) , "%d" , vSend[i]);
		bitKey += tmpsprint ;
		tmpStr = ini.GetValue("pe" , bitKey.c_str() );
		tmpStr ?  curvalue = tmpStr : 0;
		//�������Ű�Χ����ȥ�����ţ���ֵ����
		//�˴���ҪΪ�˽���󲹿ո��Ҳ��ո������
		//��ini������Ĭ�ϻ�ȥ�����ҵĿո������������ţ��ո��ڱ༭�������Է���
		if ( curvalue[0] == '"' && curvalue[curvalue.size()-1] == '"' )
		{
			curvalue.erase(0,1);
			curvalue.erase(curvalue.size()-1,1);
		}
		outData[vSend[i]] = curvalue ;
	}
	for (int i=0; i!= vRecv.size(); ++i)
	{
		tmpStr = NULL;
		bitKey = "RET";
		sprintf(tmpsprint , "%d", vRecv[i]);
		bitKey += tmpsprint;
		tmpStr = ini.GetValue("pe" , bitKey.c_str());
		tmpStr ? curvalue = tmpStr : 0;
		if( curvalue[0] == '"' && curvalue[curvalue.size()-1] == '"' )
		{
			curvalue.erase(0,1);
			curvalue.erase(curvalue.size() -1 , 1);
		}
		retData[vRecv[i]] = curvalue ;
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

	to.tv_sec = 3;																//��ʱ�趨����
	to.tv_usec = 0;																//����ȷ���ڴ��趨

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
 *�ַ����滻:http://www.byvoid.com/blog/cpp-string/
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

	//������Ҫ��ģ���滻������%��Χ������ֱ�ӷ���
	if ( !(msg[0] == '%' && msg[msg.size()-1] == '%') )
	{
		return msg;
	}

	srand(tm);
	msg.erase( 0 , 1);
	msg.erase( msg.size() -1 , 1);
	//###### �����
	if (find_if(msg.begin(),msg.end(),isnotshape) == msg.end() )
	{
		return getrand(msg.size());
	}
	//hhmmssyyyymmdd
	//���滻4��Y�����������Y�ľ�û�л���~
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
 *headertypeΪ��ͷ���ͣ���������ݰ���д��buf����������ͷ����
 *���ذ��峤��
 *����ʱ���򷵻س�ʱ����
 */
int recvMSG(char* buf , int bufMaxLen , SOCKET fd , const string& headerType)
{
	int curRecv = 0;
	int hasRecv = 0;
	int len1 = 0;
	int headerLen = headerType.size();
	int bodyLen = 0;
	//ȡ��ͷ

	do 
	{
		curRecv = recv(fd , buf + hasRecv , headerLen -hasRecv , 0);
		if (curRecv == INVALID_SOCKET)
		{
			cerr << "recv ERROR!" << endl;
		}

		hasRecv += curRecv;
	} while (hasRecv < headerLen);

	len1 = atoi(buf);
	//���峤��
	if (headerType[0] == 'L')
	{
		bodyLen = len1 - headerType.size();
	}
	else if (headerType[0] == 'l')
	{
		bodyLen = len1 ;
	}
	else
	{
		//error!
	}
	
	assert(bodyLen <= bufMaxLen );
	//ȡ����
	curRecv = 0;
	hasRecv = 0;
	do 
	{
		curRecv = recv(fd , buf + headerLen + hasRecv , bodyLen - hasRecv , 0);

		hasRecv +=curRecv ;
	} while (hasRecv < bodyLen);

	return hasRecv + headerLen;
}

/*
 *��������ֱ�Ϊ��������Ϣ���跢�͵����ݡ��������ص����ݸ�ʽ,socket
 */
int send_recv(const map<string,string>& control, const map<int,string>& data, const map<int,string>& recvData , SOCKET fd )
{
	/*
	 *��̬����PKT_DEF
	 *typedef struct tagPKT_DEF {	
	 *short typ;	TYP_ASC
	 *short fmt;	FMT_FIXED
	 *short fil;	NULL
	 *int   len;	len
	 *const char *dsc;""
	 } PKT_DEF;
	 */
	size_t  pkt_size = sizeof(PKT_DEF) * data.size() ;
	PKT_DEF *dym_pkt = (PKT_DEF *)malloc( pkt_size ) ;
	memset(dym_pkt , 0 , pkt_size);

	//ע����ʱд����
	char pkt_dsc[16] = "PKT_DSC";
	PKT_DEF *dym_pkt_tmp = dym_pkt;
	typedef map<int,string>::const_iterator ITER;
	for (ITER it=data.begin(); it != data.end(); ++it)
	{
		dym_pkt_tmp->typ = TYP_ASC;
		dym_pkt_tmp->fmt = FMT_FIXED;
		dym_pkt_tmp->fil = NULL;
		//���źͰٷֺ����⴦��
		if (  ( it->second[0] == '"'  && it->second[it->second.size()-1] == '"' )  || 
			  ( it->second[0] == '%'  && it->second[it->second.size()-1] == '%' ) )
		{
			dym_pkt_tmp->len = it->second.size() -2 ;
		}
		else
		{
			dym_pkt_tmp->len = it->second.size() ;
		}
		dym_pkt_tmp->dsc = pkt_dsc;
		++dym_pkt_tmp;
	}

	PKT_MSG *msg = pkt_malloc(dym_pkt , pkt_size ) ;
	const char*s = NULL;
	char header[1024] = { 0 };
	int headerLen     =   control.find("header")->second.size();
	int headertype	  =   0;
	char buf[2048] = { 0 };
	int bufLen     = 0;
	int curSent    = 0;
	int hasSent	   = 0;

	string tmpInfo;
	for (map<int,string>::const_iterator it = data.begin(); it != data.end(); ++it)
	{
		tmpInfo = it->second ;
		tmpInfo = translate(tmpInfo).c_str();
		pkt_set_field(msg , it->first, (char *)tmpInfo.c_str()  , tmpInfo.size() );
	}

	pkt_get_msg(msg , (unsigned char*)buf + headerLen ,	sizeof(buf) -headerLen , &bufLen);

	tmpInfo = control.find("header")->second;
	if (tmpInfo[0] == 'L')
	{
		bufLen += headerLen ;
		sprintf(header , "%04d" , bufLen );
		memcpy(buf , header , headerLen);
	}
	else if (tmpInfo[0] == 'l')
	{
		sprintf(header ,  "%04d" , bufLen );
		memcpy(buf , header , headerLen);
	}
	else
	{
		//error!
	}

	//send(fd , header , control.find("header")->second.size() , 0);
	//send
	while( (curSent = send(fd , buf + hasSent, bufLen - hasSent, 0)) > 0 ) 
	{
		hasSent += curSent ;
		continue;
	}
	cout<< "======================================SEND======================================" << endl;
	pkt_print(msg);
	cout << "RAW PRINT:" << endl;
	print_hex(buf , bufLen);
	pkt_free(msg);
	msg = NULL;
	memset(buf , 0 , sizeof(buf));

	// recv
	bufLen = recvMSG(buf , sizeof(buf) , fd , control.find("header")->second);
	cout<< "======================================RECV======================================" << endl;

	//�ٴζ�̬��������ֵ��PKT_DEF
	free(dym_pkt);
	dym_pkt = dym_pkt_tmp = NULL;

	pkt_size= sizeof(PKT_DEF) * recvData.size() ;
	dym_pkt = (PKT_DEF *)malloc(pkt_size);
	dym_pkt_tmp = dym_pkt;
	memcpy(pkt_dsc , "RETURN VALUE!" , 14 )	;//ע������д��

	for (ITER it = recvData.begin() ; it != recvData.end() ; ++ it )
	{
		dym_pkt_tmp->typ = TYP_ASC;
		dym_pkt_tmp->fmt = FMT_FIXED;
		dym_pkt_tmp->fil = NULL;
		//���źͰٷֺ����⴦��
		if (  ( it->second[0] == '"'  && it->second[it->second.size()-1] == '"' )  || 
			( it->second[0] == '%'  && it->second[it->second.size()-1] == '%' ) )
		{
			dym_pkt_tmp->len = it->second.size() -2 ;
		}
		else
		{
			dym_pkt_tmp->len = it->second.size() ;
		}
		dym_pkt_tmp->dsc = pkt_dsc;
		++dym_pkt_tmp;
	}

	msg = pkt_malloc(dym_pkt , pkt_size);
	pkt_set_msg(msg , (unsigned char*)buf + headerLen , bufLen - headerLen);
	pkt_print(msg);
	cout << "RAW PRINT:" << endl;
	print_hex(buf , bufLen);

	//cleanner!
	pkt_free(msg);
	free(dym_pkt);dym_pkt = dym_pkt_tmp = NULL;
	return 0;
}

int main(int argc , char** argv)
{
	//1����ȡ���� ip��port��data
	//	��ȡ�����У���û�У�ֱ�Ӷ�ȡ��������Ӧini

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
	map<int , string > recvData;

	if (loadConfig(control , data , recvData , iniFile) == -1)
	{
		cerr << "��ȡ���ô��������ԣ�" << endl;
		return 1;
	}
	assert(!control.empty() && ! data.empty());

	//��ʼѭ��
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

		send_recv(control , data , recvData , sock);

		closesocket(sock);
		isConnected = false;
		Sleep(atoi(control["pause"].c_str())*1000);
	} while ( ++hasCircle  < atoi(control["circle"].c_str()) );
	
	WSACleanup(); 
	return 0;
}

