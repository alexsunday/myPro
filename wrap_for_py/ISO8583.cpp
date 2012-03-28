#include "ISO8583.h"
#include "tinyxml.h"
#include <vector>
using namespace  std;

ISO8583::ISO8583() : msg(NULL) {}
ISO8583::~ISO8583() 
{
	if (msg)
	{
		ISO8583_free(msg);
	}
}

int ISO8583::setData(char* dataBuf , int dataLen , int bizType)
{
	//载入配置
	ISO8583_DEF myISO[128] ;
	memset(myISO , 0, sizeof(ISO8583_DEF)) ;
	//动态生成DEF

	int size = 0;
	ISO8583_DEF *dym = (ISO8583_DEF*)malloc(  sizeof(ISO8583_DEF)*size );
	ISO8583_DEF *tmp = dym;
	for (int i=0; i!= size ; ++i)
	{
		//*tmp->*/
	}
	//setdata
	return 0;
}

bool ISO8583::loadConfig(const std::string& configFile, vector<ISO8583_DEF>& vid)
{
	vid.clear();
	ISO8583_DEF def;

	def.typ = -1;
	def.len = -1;
	def.fmt = -1;

	vid.assign(128 , def);
	TiXmlDocument doc(configFile);
	if ( !doc.LoadFile() )
	{
		return false;
	}

	TiXmlElement *root = doc.RootElement();
	string tmp;
	int idx = -1;
	int len = 0 ;
	for (TiXmlNode* item=root->FirstChild("bit"); item ;item = item->NextSibling("bit"))
	{
		tmp = item->ToElement()->Attribute("encode") ;
		if( tmp == "BCD")
			def.typ = TYP_BCD;
		else if ( tmp == "ASC")
		{
			def.typ = TYP_ASC;
		}
		else if ( tmp == "BIN")
		{
			def.typ = TYP_BIN;
		}
		else if (tmp == "BIT")
		{
			def.typ = TYP_BIT;
		}

		tmp = item->ToElement()->Attribute("fmt");
		if ( tmp == "fixed")
		{
			def.fmt = FMT_FIXED;
		}
		else if (tmp == "lvar")
		{
			def.fmt = FMT_LVAR;
		}
		else if (tmp == "llvar")
		{
			def.fmt = FMT_LLVAR;
		}
		else if ( tmp == "lllvar")
		{
			def.fmt = FMT_LLLVAR;
		}
		item->ToElement()->QueryIntAttribute("length" , &len);
		def.len = len;

		//DSC 未实现
		item->ToElement()->QueryIntAttribute("idx", &idx);
		vid[idx] = def;
	}

	bool isLarge = false;
	for (int i=vid.size() / 2 ; i != vid.size(); ++i)
	{
		isLarge = isLarge || (vid[i].len != -1) ;
	}
	
	if ( ! isLarge )
	{
		vid.resize(64);
	}

	return true;
}