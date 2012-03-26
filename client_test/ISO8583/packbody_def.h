#ifndef _packbody_def_h__
#define _packbody_def_h__

#include "packbody_parser.h"

static PKT_DEF FA_PKT_HEAD[] ={
	/*000*/ {TYP_ASC,  FMT_FIXED , NULL   , 4 , "交易类型"}, 
	/*001*/ {TYP_ASC,  FMT_FIXED , R_BLANK, 30, "银行帐号"}, 
	/*002*/ {TYP_ASC,  FMT_FIXED , L_ZERO , 6 , "发起方交易顺序号"}, 
	/*003*/ {TYP_ASC,  FMT_FIXED , L_ZERO , 20, "发起方流水号"}, 
	/*004*/ {TYP_ASC,  FMT_FIXED , NULL   , 8 , "交易日期"}, 
	/*005*/ {TYP_ASC,  FMT_FIXED , NULL   , 6 , "交易时间"}, 
	/*006*/ {TYP_ASC,  FMT_FIXED , R_BLANK, 12, "接收方流水号"}, 
	/*007*/ {TYP_ASC,  FMT_FIXED , NULL   , 4 , "业务代码"}, 
	/*008*/ {TYP_ASC,  FMT_FIXED , NULL   , 8 , "发起方ID"}, 
	/*009*/ {TYP_ASC,  FMT_FIXED , NULL   , 15, "发起方商户号"}, 
	/*010*/ {TYP_ASC,  FMT_FIXED , NULL   , 6 , "发起方机构代码"}, 
	/*011*/ {TYP_ASC,  FMT_FIXED , NULL   , 12, "金额"}, 
	/*012*/ {TYP_ASC,  FMT_FIXED , NULL   , 4 , "响应码"}, 
	/*013*/ {TYP_ASC,  FMT_FIXED , R_BLANK, 50, "响应码说明"}, 
	/*014*/ {TYP_BIN,  FMT_FIXED , NULL   , 8 , "MAC校验码"}, 
	/*015*/ {TYP_ASC,  FMT_FIXED , NULL   , 1 , "包体标志位"}
};


static PKT_DEF FA_PKT_B_P001_0001_REQ[] ={
	/*000*/ {TYP_ASC,  FMT_FIXED , NULL      , 2 , "证件类型"}, 
	/*001*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99, "证件号码"}, 
	/*002*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99, "银行帐号户名"}, 
	/*003*/ {TYP_ASC,  FMT_FIXED , R_BLANK   , 20, "银行帐号归属地"}, 
	/*004*/ {TYP_ASC,  FMT_FIXED , NULL      , 2 , "银行帐号所属银行代码"}, 
	/*005*/ {TYP_ASC,  FMT_FIXED , R_BLANK   , 10, "银行帐号的开户行信息"}, 
	/*006*/ {TYP_ASC,  FMT_FIXED , NULL      , 1 , "卡折标识"}, 
	/*007*/ {TYP_ASC,  FMT_FIXED , NULL      , 1 , "对公/对私标识"},
	/*008*/ {TYP_ASC,  FMT_FIXED , NULL      , 1 , "卡折标识"}, 
	/*009*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99, "联系号码"}, 
	/*010*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99, "联系地址"}, 
	/*011*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99, "信用卡有效期"}, 
	/*012*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99, "信用卡验证码"}, 
};

static PKT_DEF FA_PKT_B_R001_0001_RESP[] ={
	/*000*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99 , "签约ID"}, 
	/*001*/ {TYP_ASC,  FMT_FIXED , NULL      , 8,  "签约生效日期"}, 
	/*002*/ {TYP_ASC,  FMT_FIXED , NULL      , 8, "签约失效日期"},  
};


static PKT_DEF FA_PKT_B_P001_0006_REQ[] ={
	/*000*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99 , "签约ID"}, 
	/*001*/ {TYP_ASC,  FMT_FIXED , NULL      , 1  , "查询标识"}, 
	/*002*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99 , "代收交易发起方交易流水号"}, 
	/*003*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99 , "交易号码"}, 
	/*004*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99 , "交易终端号"}, 
	/*005*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99 , "交易时间"}, 
};



static PKT_DEF FA_PKT_B_R001_0006_RESP[] ={
	/*000*/ {TYP_ASC,  FMT_FIXED , L_ZERO    , 2 , "交易笔数"}, 
	/*001*/ {TYP_ASC,  FMT_FIXED , NULL      , 14, "交易时间"}, 
	/*002*/ {TYP_ASC,  FMT_FIXED , NULL      , 12, "交易流水号"}, 
	/*003*/ {TYP_ASC,  FMT_FIXED , NULL      , 99, "交易帐号"}, 
	/*004*/ {TYP_ASC,  FMT_FIXED , NULL      , 99 , "交易号码"}, 
	/*005*/ {TYP_ASC,  FMT_FIXED , NULL      , 8,  "交易终端号"}, 
	/*006*/ {TYP_ASC,  FMT_FIXED , NULL      , 4 , "交易结果"}, 
};



static PKT_DEF FA_PKT_B_P002_0002_REQ[] ={
	/*000*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99 , "签约ID"}, 
	/*001*/ {TYP_ASC,  FMT_FIXED , R_BLANK   , 30 , "转入银行帐号"}, 
	/*002*/ {TYP_ASC,  FMT_LLVAR , NULL      , 99 , "转入银行帐号户名"}, 
	/*003*/ {TYP_ASC,  FMT_FIXED , NULL      , 6  , "转入银行帐号所属银行代码"}, 
	/*004*/ {TYP_ASC,  FMT_FIXED , NULL      , 8  , "交易终端号"}, 
	/*005*/ {TYP_ASC,  FMT_FIXED , NULL      , 1  , "信用卡标识"}, 
};



static PKT_DEF FA_PKT_B_R002_0002_RESP[] ={
	/*000*/ {TYP_ASC,  FMT_FIXED , NULL      , 99 , "签约ID"}, 
	/*001*/ {TYP_ASC,  FMT_FIXED , L_ZERO    , 30, "转入银行帐号"}, 
	/*002*/ {TYP_ASC,  FMT_FIXED , NULL      , 8, "交易终端号"}, 
	/*003*/ {TYP_ASC,  FMT_FIXED , NULL      , 1, "转出帐户余额标志"}, 
	/*004*/ {TYP_ASC,  FMT_FIXED , NULL      , 12 , "转出帐户余额"}, 
	/*005*/ {TYP_ASC,  FMT_FIXED , NULL      , 12, "转出账户可用余额"}, 
};

static PKT_DEF FA_PKT_B_R002_0003_REQ[] ={
	/*000*/ {TYP_ASC,  FMT_FIXED , NULL      , 4 , "信息码"}, 
	/*001*/ {TYP_ASC,  FMT_FIXED , L_ZERO    , 12, "Pe系统参考号"}, 
	/*002*/ {TYP_ASC,  FMT_FIXED , NULL      , 4, "业务代码"}, 
	/*003*/ {TYP_ASC,  FMT_FIXED , NULL      , 6, "缴费省代码"}, 
	/*004*/ {TYP_ASC,  FMT_FIXED , NULL      , 6 , "缴费城市代码"}, 
	/*005*/ {TYP_ASC,  FMT_FIXED , NULL      , 4, "缴费项目编号"}, 
	/*006*/ {TYP_ASC,  FMT_FIXED , NULL		,	1, "充值产品类型"},
	/*007*/ {TYP_ASC,  FMT_FIXED , R_ZERO		,	20, "充值号码"}
};
#endif /* _packbody_def_h__*/
