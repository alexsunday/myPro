#ifndef _packbody_def_h__
#define _packbody_def_h__

#include "packbody_parser.h"

static PKT_DEF FA_PKT_HEAD[] ={
	/*000*/ {TYP_ASC,  FMT_FIXED , NULL   , 4 , "��������"}, 
	/*001*/ {TYP_ASC,  FMT_FIXED , R_BLANK, 30, "�����ʺ�"}, 
	/*002*/ {TYP_ASC,  FMT_FIXED , L_ZERO , 6 , "���𷽽���˳���"}, 
	/*003*/ {TYP_ASC,  FMT_FIXED , L_ZERO , 20, "������ˮ��"}, 
	/*004*/ {TYP_ASC,  FMT_FIXED , NULL   , 8 , "��������"}, 
	/*005*/ {TYP_ASC,  FMT_FIXED , NULL   , 6 , "����ʱ��"}, 
	/*006*/ {TYP_ASC,  FMT_FIXED , R_BLANK, 12, "���շ���ˮ��"}, 
	/*007*/ {TYP_ASC,  FMT_FIXED , NULL   , 4 , "ҵ�����"}, 
	/*008*/ {TYP_ASC,  FMT_FIXED , NULL   , 8 , "����ID"}, 
	/*009*/ {TYP_ASC,  FMT_FIXED , NULL   , 15, "�����̻���"}, 
	/*010*/ {TYP_ASC,  FMT_FIXED , NULL   , 6 , "���𷽻�������"}, 
	/*011*/ {TYP_ASC,  FMT_FIXED , NULL   , 12, "���"}, 
	/*012*/ {TYP_ASC,  FMT_FIXED , NULL   , 4 , "��Ӧ��"}, 
	/*013*/ {TYP_ASC,  FMT_FIXED , R_BLANK, 50, "��Ӧ��˵��"}, 
	/*014*/ {TYP_BIN,  FMT_FIXED , NULL   , 8 , "MACУ����"}, 
	/*015*/ {TYP_ASC,  FMT_FIXED , NULL   , 1 , "�����־λ"}
};


static PKT_DEF FA_PKT_B_P001_0001_REQ[] ={
	/*000*/ {TYP_ASC,  FMT_FIXED , NULL      , 2 , "֤������"}, 
	/*001*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99, "֤������"}, 
	/*002*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99, "�����ʺŻ���"}, 
	/*003*/ {TYP_ASC,  FMT_FIXED , R_BLANK   , 20, "�����ʺŹ�����"}, 
	/*004*/ {TYP_ASC,  FMT_FIXED , NULL      , 2 , "�����ʺ��������д���"}, 
	/*005*/ {TYP_ASC,  FMT_FIXED , R_BLANK   , 10, "�����ʺŵĿ�������Ϣ"}, 
	/*006*/ {TYP_ASC,  FMT_FIXED , NULL      , 1 , "���۱�ʶ"}, 
	/*007*/ {TYP_ASC,  FMT_FIXED , NULL      , 1 , "�Թ�/��˽��ʶ"},
	/*008*/ {TYP_ASC,  FMT_FIXED , NULL      , 1 , "���۱�ʶ"}, 
	/*009*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99, "��ϵ����"}, 
	/*010*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99, "��ϵ��ַ"}, 
	/*011*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99, "���ÿ���Ч��"}, 
	/*012*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99, "���ÿ���֤��"}, 
};

static PKT_DEF FA_PKT_B_R001_0001_RESP[] ={
	/*000*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99 , "ǩԼID"}, 
	/*001*/ {TYP_ASC,  FMT_FIXED , NULL      , 8,  "ǩԼ��Ч����"}, 
	/*002*/ {TYP_ASC,  FMT_FIXED , NULL      , 8, "ǩԼʧЧ����"},  
};


static PKT_DEF FA_PKT_B_P001_0006_REQ[] ={
	/*000*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99 , "ǩԼID"}, 
	/*001*/ {TYP_ASC,  FMT_FIXED , NULL      , 1  , "��ѯ��ʶ"}, 
	/*002*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99 , "���ս��׷��𷽽�����ˮ��"}, 
	/*003*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99 , "���׺���"}, 
	/*004*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99 , "�����ն˺�"}, 
	/*005*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99 , "����ʱ��"}, 
};



static PKT_DEF FA_PKT_B_R001_0006_RESP[] ={
	/*000*/ {TYP_ASC,  FMT_FIXED , L_ZERO    , 2 , "���ױ���"}, 
	/*001*/ {TYP_ASC,  FMT_FIXED , NULL      , 14, "����ʱ��"}, 
	/*002*/ {TYP_ASC,  FMT_FIXED , NULL      , 12, "������ˮ��"}, 
	/*003*/ {TYP_ASC,  FMT_FIXED , NULL      , 99, "�����ʺ�"}, 
	/*004*/ {TYP_ASC,  FMT_FIXED , NULL      , 99 , "���׺���"}, 
	/*005*/ {TYP_ASC,  FMT_FIXED , NULL      , 8,  "�����ն˺�"}, 
	/*006*/ {TYP_ASC,  FMT_FIXED , NULL      , 4 , "���׽��"}, 
};



static PKT_DEF FA_PKT_B_P002_0002_REQ[] ={
	/*000*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99 , "ǩԼID"}, 
	/*001*/ {TYP_ASC,  FMT_FIXED , R_BLANK   , 30 , "ת�������ʺ�"}, 
	/*002*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99 , "ת�������ʺŻ���"}, 
	/*003*/ {TYP_ASC,  FMT_FIXED , NULL      , 6  , "ת�������ʺ��������д���"}, 
	/*004*/ {TYP_ASC,  FMT_FIXED , NULL      , 8  , "�����ն˺�"}, 
	/*005*/ {TYP_ASC,  FMT_FIXED , NULL      , 1  , "���ÿ���ʶ"}, 
};



static PKT_DEF FA_PKT_B_R002_0002_RESP[] ={
	/*000*/ {TYP_ASC,  FMT_FIXED , NULL      , 99 , "ǩԼID"}, 
	/*001*/ {TYP_ASC,  FMT_FIXED , L_ZERO    , 30, "ת�������ʺ�"}, 
	/*002*/ {TYP_ASC,  FMT_FIXED , NULL      , 8, "�����ն˺�"}, 
	/*003*/ {TYP_ASC,  FMT_FIXED , NULL      , 1, "ת���ʻ�����־"}, 
	/*004*/ {TYP_ASC,  FMT_FIXED , NULL      , 12 , "ת���ʻ����"}, 
	/*005*/ {TYP_ASC,  FMT_FIXED , NULL      , 12, "ת���˻��������"}, 
};

static PKT_DEF FA_PKT_B_R002_0003_REQ[] ={
	/*000*/ {TYP_ASC,  FMT_FIXED , NULL      , 4 , "��Ϣ��"}, 
	/*001*/ {TYP_ASC,  FMT_FIXED , L_ZERO    , 12, "Peϵͳ�ο���"}, 
	/*002*/ {TYP_ASC,  FMT_FIXED , NULL      , 4, "ҵ�����"}, 
	/*003*/ {TYP_ASC,  FMT_FIXED , NULL      , 6, "�ɷ�ʡ����"}, 
	/*004*/ {TYP_ASC,  FMT_FIXED , NULL      , 6 , "�ɷѳ��д���"}, 
	/*005*/ {TYP_ASC,  FMT_FIXED , NULL      , 4, "�ɷ���Ŀ���"}, 
	/*006*/ {TYP_ASC,  FMT_FIXED , NULL		,	1, "��ֵ��Ʒ����"},
	/*007*/ {TYP_ASC,  FMT_FIXED , R_ZERO		,	20, "��ֵ����"}
};
#endif /* _packbody_def_h__*/
