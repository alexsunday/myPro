/********************************************************************
*	 Copyright (C) 天讯瑞达通信技术有限公司
*	 Filename: 	    iso8583_wrappers.cpp
*	 Created Date:	2012/02/23 18:46
*	 Author:		Peng GuoYi
* 	 Version:       1.0
*	 Description:   主要功能实现8583包解包组包
*	 Revision histroy :
*	   1:
*	 	 Date:
*	 	 Author:
*	 	 Modifiacation:
*	   ...
*********************************************************************/
#include "iso8583_wrappers.h"
#include <stdlib.h>
#include <string.h>
int hexToByte (const char *instr, char *outstr, int inLen, int type );
void byteToHex (const char *in_buff, char *out_buff, int in_len);
int BCD2INT (const unsigned char* b, int len);


/****************************************************************
*   Function name    : ISO8583_print
*   Author           : Peng GuoYi
*   Coding Date      : 2012/02/23 18:49
*   Description      : 按照特定格式打印8583包的内容
*   Return type      : void 
*   Argument         : ISO8583_MSG* msg
****************************************************************/
void   ISO8583_print(ISO8583_MSG* msg)
{
	int i;
	char * pi ;
	char szBuf[1000];

	if (msg == NULL){
		printf("please set msg in ISO8583_print\n");
		return ;
	}

	printf("\n**********************************************\n");
	for (i = 0; i <= msg->iso_bits; i++)
	{
		if (msg->field[i].field_pointer != NULL)
		{			
			szBuf[0] = 0;
			switch(msg->iso_def[i].typ)
			{
			case TYP_BCD:
			case TYP_BIN:
			case TYP_BIT:
				switch(msg->iso_def[i].fmt)
				{
				case FMT_FIXED:
					if (msg->iso_def[i].len % 2 == 1)
					{
						/*如果BCD且长度为奇数*/
						pi = (char *)malloc(msg->iso_def[i].len*sizeof(char) + 10);
						byteToHex((char *)msg->field[i].field_pointer, pi, msg->field[i].field_length);
						pi[msg->field[i].field_length * 2] = 0;
						memcpy(szBuf, pi + 1, msg->field[i].field_length * 2 - 1);
						szBuf[msg->field[i].field_length * 2 - 1] = 0;
						free(pi);
					}else{
						byteToHex((char *)msg->field[i].field_pointer, szBuf, msg->field[i].field_length);
						szBuf[msg->field[i].field_length * 2] = 0;
					}
					break;
				case FMT_LLVAR:					
				case FMT_LLLVAR:					
					byteToHex((char *)msg->field[i].field_pointer, szBuf, msg->field[i].field_length);
					szBuf[msg->field[i].field_length * 2] = 0;					
					break;
				}				
				break;
			case TYP_ASC:
				memcpy(szBuf ,msg->field[i].field_pointer, msg->field[i].field_length);
				szBuf[msg->field[i].field_length ] = 0;
			default:
				break;
			}

			printf("[%2d]: {%s}\n",i,szBuf);
		}		



		//if(ISO8583_get_field(msg, i , (unsigned char *)szBuf , sizeof (szBuf)) > 0)
		//	printf("[%2d]: {%s}\n",i,szBuf);
	}
	printf("**********************************************\n\n");
}


/****************************************************************
*   Function name    : ISO8583_malloc
*   Author           : Peng GuoYi
*   Coding Date      : 2012/02/23 19:22
*   Description      : 
*   Return type      : ISO8583_MSG*            --存放8583的内存空间
*   Argument         : ISO8583_DEF* def        --8583的定义
*                      size_t def_size         --8583的定义的大小
*                      ISO8583_FIELDS fields   --定义128还是64域数据
*                      int compress            --长度位是否BCD码压缩
****************************************************************/
ISO8583_MSG  * ISO8583_malloc(ISO8583_DEF* def,size_t def_size, ISO8583_FIELDS fields,int compress )
{
	ISO8583_MSG* msg = NULL;

	if (def == NULL){
		printf("please set ISO8583_DEF in ISO8583_malloc\n");
		return NULL;
	}

	if (def_size/sizeof(ISO8583_DEF) != fields+1){
		printf("Function ISO8583_malloc param error. def_size/sizeof(ISO8583_DEF) [%d] fields[%d]\n",def_size/sizeof(ISO8583_DEF) ,fields);
		return NULL;
	}

	msg = (ISO8583_MSG*)malloc(sizeof(ISO8583_MSG) );
	memset(msg , 0 ,sizeof(ISO8583_MSG));
	msg->compress = compress;
	msg->is_error = 0;
	msg->iso_bits = fields;	
	memcpy(msg->iso_def , def, def_size);
	return msg;
}


/****************************************************************
*   Function name    : ISO8583_get_field
*   Author           : Peng GuoYi
*   Coding Date      : 2012/02/23 19:24
*   Description      : 
*   Return type      : int --对应 field 值的长度
*   Argument         : ISO8583_MSG*            --存放8583的内存空间
*                      int idx                 --8583 对应的域
*                      unsigned char *data     --获取对应域的数据
*                      int max_len             --unsigned char *data的空间大小
****************************************************************/
int    ISO8583_get_field(const ISO8583_MSG *msg, int idx, unsigned char *data, int max_len )
{
	char * pi;
	char *p;
	int f_len = 0;
	
	if (data != NULL)
	{
		data[0] = 0;
		f_len = 0;
	}else {
		return 0;
	}

	if (msg != NULL){

		if (msg->is_error == 1){
			return -1;
		}

		if (msg->field[idx].field_pointer != NULL)
		{
			switch(msg->iso_def[idx].typ)
			{
			case TYP_BCD:
			case TYP_BIN:
			case TYP_BIT:
				{
					if (msg->field[idx].field_length * 2>= max_len)
					{
						printf("error ! please set data buffer bigger! make max_len > %d \n",msg->field[idx].field_length*2);
						return 0;
					}

					switch(msg->iso_def[idx].fmt)
					{

					case FMT_FIXED:
						if(msg->iso_def[idx].len % 2 == 1)
						{
							pi = (char *)malloc(msg->iso_def[idx].len*sizeof(char) + 10);							
							byteToHex((char *)msg->field[idx].field_pointer, pi, msg->iso_def[idx].len  + 1);
							f_len = msg->iso_def[idx].len; 
							/*pi[f_len] = 0;*/
							memcpy(data, pi + 1, f_len); /*去掉前面的0*/
							data[f_len] = 0;
							free(pi);

						}else{
							p = (char *)msg->field[idx].field_pointer;
							byteToHex(p, (char *)data, msg->field[idx].field_length);
							data[msg->field[idx].field_length * 2] = 0;	
							f_len = msg->field[idx].field_length * 2;
						}
						

						break;
					case FMT_LLVAR:	
					case FMT_LLLVAR:
						if (msg->field[idx].field_flag == 1)
						{
							/*如果BCD且长度为奇数，后补f*/
							pi = (char *)malloc(msg->iso_def[idx].len*sizeof(char) + 10);							
							byteToHex((char *)msg->field[idx].field_pointer, pi, msg->field[idx].field_length );
							f_len = msg->field[idx].field_length * 2 - 1; /*去掉后面的F*/
							pi[f_len] = 0;
							memcpy(data, pi , f_len);
							data[f_len] = 0;
							free(pi);

						}else{
							p = (char *)msg->field[idx].field_pointer;
							byteToHex(p, (char *)data, msg->field[idx].field_length);
							data[msg->field[idx].field_length * 2] = 0;	
							f_len = msg->field[idx].field_length * 2;
						}


						break;
					default:
						break;
					}					
					break;						
					
				}
			case TYP_ASC:
				{
					if (msg->field[idx].field_length >= max_len)
					{
						printf("error ! please set data buffer bigger! make max_len > %d \n",msg->field[idx].field_length);
						return 0;
					}

					p = (char *)msg->field[idx].field_pointer;
					memcpy(data, p , msg->field[idx].field_length);
					data[msg->field[idx].field_length] = 0;	
					f_len = msg->field[idx].field_length;
					break;					
				}
			default:
				data[0] = 0;
				f_len = 0;
				break;
			}			
		}		
	}else{
		data[0] = 0;
		f_len = 0;
	}

	return f_len;
}

/****************************************************************
*   Function name    : ISO8583_reset
*   Author           : Peng GuoYi
*   Coding Date      : 2012/02/23 19:30
*   Description      : 重置域的数据
*   Return type      : void
*   Argument         : ISO8583_MSG*            --存放8583包的内存空间                   
****************************************************************/
void   ISO8583_reset(ISO8583_MSG* msg)
{
	int i;
	char *p;
	if (msg != NULL){
		for (i = 0; i <= msg->iso_bits; i++)
		{
			if (msg->field[i].field_pointer != NULL)
			{
				p = (char *)msg->field[i].field_pointer;
				if(p) free(p);
				msg->field[i].field_pointer = NULL;
			}		
		}
	}	
}


/****************************************************************
*   Function name    : ISO8583_free
*   Author           : Peng GuoYi
*   Coding Date      : 2012/02/23 19:30
*   Description      : 释放内存空间
*   Return type      : void
*   Argument         : ISO8583_MSG*            --存放8583包的内存空间                     
****************************************************************/
void   ISO8583_free(ISO8583_MSG* msg)
{
	if (msg != NULL){
		ISO8583_reset(msg);
		free(msg);
		msg = NULL;
	}	
}


/****************************************************************
*   Function name    : ISO8583_set_msg_hex
*   Author           : Peng GuoYi
*   Coding Date      : 2012/02/23 19:30
*   Description      : 
*   Return type      : 
*   Argument         : ISO8583_MSG*            --存放8583包的内存空间    
*                      const char *data        --8583的数据内容HEX码格式
*                      int len                 --8583的数据长度
****************************************************************/
int   ISO8583_set_msg_hex(ISO8583_MSG* msg, const char *data, int len )
{
	int ret = 0;
	unsigned char *p = NULL;
	int pLen = 0;
	if (msg == NULL){
		printf("please set msg in ISO8583_set_msg_hex\n");
		return -1;
	}

	if (data == NULL){
		printf("please set data in ISO8583_set_msg_hex\n");
		msg->is_error = 1;
		return -1;
	}

	if (msg->is_error == 1){
		return -1;
	}

	p = (unsigned char *)malloc(len*sizeof(char) + 10);
	pLen = hexToByte(data, (char*)p, len, 0);

	/*ret = */ISO8583_set_msg(msg, p, pLen);

	free(p);
	return ret;
}

/****************************************************************
*   Function name    : ISO8583_set_field
*   Author           : Peng GuoYi
*   Coding Date      : 2012/02/23 19:24
*   Description      : 设置域值
*   Return type      : int                     --对应 field 值的长度
*   Argument         : ISO8583_MSG*            --存放8583的内存空间
*                      int idx                 --8583 对应的域
*                      char *data              --设置对应域的数据
*                      int len                 --对应域的数据的长度
****************************************************************/
int    ISO8583_set_field(ISO8583_MSG* msg,int idx, char *data, int len )
{
	unsigned char *p = NULL;
	char *pi = NULL;

	if (msg == NULL){
		printf("please set msg in ISO8583_set_field.\n");
		return -1;
	}

	if (data == NULL){
		printf("please set data in ISO8583_set_field.\n");
		msg->is_error = 1;
		return -1;
	}

	if (msg->iso_def[idx].len == NULL)
	{
		printf("FIELD[%d] NOT DEFINE. ISO8583_set_field.\n",idx);
		msg->is_error = 1;
		return -1;
	}

	
	if (msg->is_error == 1){
		return -1;
	}


	/*置 0*/
	msg->field[idx].field_flag = 0;

	switch(msg->iso_def[idx].typ)
	{
	
	case TYP_BIN:
	case TYP_BIT:
		{
			switch(msg->iso_def[idx].fmt)
			{
			case FMT_FIXED:
				if (msg->iso_def[idx].len*2 != len)
				{
					printf("Error! len  != %d. data must be hex,Please check FIELD[%d] LEN ISO8583_set_field\n",msg->iso_def[idx].len*2 , idx);
					msg->is_error = 1;
					return -1;
				}
				break;
			case FMT_LLVAR:					
			case FMT_LLLVAR:
				if (len > msg->iso_def[idx].len)
				{
					printf("Value:[%s] len:[%d] is lengther  , Please check FIELD[%d] LEN ISO8583_set_field\n",data, len, msg->iso_def[idx].len , idx);
					msg->is_error = 1;
					return -1;
				}
				break;
			default:
				printf("error in ISO8583_set_field . please check FIELD[%d] fmt define.\n", idx);
				msg->is_error = 1;
				return -1;	
			}
			break;
		}
	case TYP_BCD:
	case TYP_ASC:
		{
			switch(msg->iso_def[idx].fmt)
			{
			case FMT_FIXED:
				if (msg->iso_def[idx].len != len)
				{
					printf("Error! len  != %d. Please check FIELD[%d] LEN ISO8583_set_field\n",msg->iso_def[idx].len , idx);
					msg->is_error = 1;
					return -1;
				}
				break;
			case FMT_LLVAR:					
			case FMT_LLLVAR:
				if (len > msg->iso_def[idx].len)
				{
					printf("Value:[%s] len:[%d] is lengther  , Please check FIELD[%d] LEN ISO8583_set_field\n",data, len, msg->iso_def[idx].len , idx);
					msg->is_error = 1;
					return -1;
				}
				break;
			default:
				printf("error in ISO8583_set_field . please check FIELD[%d] fmt define.\n", idx);
				msg->is_error = 1;
				return -1;		
			}
			break;
		}
	default:
		printf("error in ISO8583_set_field . please check FIELD[%d] type define.\n", idx);
		msg->is_error = 1;
		return -1;		
	}

	p = (unsigned char *)(msg->field[idx].field_pointer);
	if (p != NULL){
		free((unsigned char *)p);
	}

	switch(msg->iso_def[idx].typ)
	{
	case TYP_BCD:
	case TYP_BIN:
	case TYP_BIT:
		switch(msg->iso_def[idx].fmt)
		{
		case FMT_FIXED:	
			if (len % 2 == 1)
			{
				/*如果长度是奇数，需要字符串前面补'0'*/
				p = (unsigned char *)malloc(len + 10);
				pi = (char *)malloc(len + 10);
				pi[0] = '0';
				memcpy(pi + 1, data, len );				
				len ++;
				pi[len] = '\0';	
				hexToByte(pi, (char *)p, len, 0);
				len = len  / 2;
				p[len ] = 0;
				msg->field[idx].field_pointer = (unsigned char *)p;
				msg->field[idx].field_length = len;
				free(pi);

			}else{
				p = (unsigned char *)malloc(len + 10);
				hexToByte(data, (char *)p, len, 0);
				len = len / 2;
				p[len ] = 0;
				msg->field[idx].field_pointer = (unsigned char *)p;
				msg->field[idx].field_length = len ;
			}

			break;
		case FMT_LLVAR:			
		case FMT_LLLVAR:	
			if (len % 2 == 1)
			{
				/*如果长度是奇数，需要字符末尾加入F进行压缩*/
				p = (unsigned char *)malloc(len + 10);
				pi = (char *)malloc(len + 10);
				memcpy(pi, data, len );
				pi[len] = 'f';
				len ++;
				pi[len] = '\0';				
				hexToByte(pi, (char *)p, len, 0);
				len = len / 2;
				p[len ] = 0;
				msg->field[idx].field_pointer = (unsigned char *)p;
				msg->field[idx].field_length = len;
				msg->field[idx].field_flag = 1;
				free(pi);
				
			}else{
				p = (unsigned char *)malloc(len + 10);
				hexToByte(data, (char *)p, len, 0);
				len = len / 2;
				p[len ] = 0;
				msg->field[idx].field_pointer = (unsigned char *)p;
				msg->field[idx].field_length = len ;
			}
			
			break;

		default:
			break;
		}

		break;
	case TYP_ASC:
		p = (unsigned char *)malloc(msg->iso_def[idx].len + 10);
		memcpy(p, data , len );
		p[len] = 0;
		msg->field[idx].field_pointer = (unsigned char *)p;
		msg->field[idx].field_length = len;


	default:
		break;
	}

	return len;
}


/****************************************************************
*   Function name    : ISO8583_get_msg
*   Author           : Peng GuoYi
*   Coding Date      : 2012/02/23 19:30
*   Description      : 得到完整的8583数据包
*   Return type      : 数据包的长度
*   Argument         : ISO8583_MSG*            --存放8583包的内存空间    
*                      const char *data        --8583的数据内容HEX数据格式
*                      int len                 --8583的数据长度
****************************************************************/
int    ISO8583_get_msg_hex(ISO8583_MSG* msg,  char *data, int data_max_size, int* len )
{
	unsigned char *p = (unsigned char *)malloc(data_max_size + 2);

	if (msg == NULL){
		printf("please set msg in ISO8583_get_msg_hex\n");
		return -1;
	}

	if (data == NULL){
		printf("please set data in ISO8583_get_msg_hex\n");
		return -1;
	}

	if (msg->is_error == 1){
		data = NULL;
		*len = 0;
		return -1;
	}

	ISO8583_get_msg(msg, p, data_max_size, len);
	byteToHex((char *)p, (char *)data , *len);
	data[*len*2] = 0;
	free(p);
	*len = *len * 2;
	return *len*2;
}

/****************************************************************
*   Function name    : ISO8583_get_msg
*   Author           : Peng GuoYi
*   Coding Date      : 2012/02/23 19:30
*   Description      : 得到完整的8583数据包
*   Return type      : 数据包的长度
*   Argument         : ISO8583_MSG*            --存放8583包的内存空间    
*                      const char *data        --8583的数据内容
*                      int len                 --8583的数据长度
****************************************************************/
int    ISO8583_get_msg(ISO8583_MSG* msg, unsigned char *data, int data_max_size, int* len )
{
	int pos;
	int i;
	char sz[1000];
	char bitmap[16 + 1];
	char bitmap_default[] = {"000000000000000000000000"};
	char buf[1000];

	if (msg == NULL){
		printf("please set msg in ISO8583_get_msg\n");
		return -1;
	}

	if (data == NULL){
		printf("please set data in ISO8583_get_msg\n");
		return -1;
	}

	if (msg->is_error == 1){
		data = NULL;
		*len = 0;
		return -1;
	}

	memset(bitmap, 0, sizeof(bitmap));
	pos = 0;
	if (msg->compress == 1)
	{
		for (i = 0 ; i <= msg->iso_bits ; i ++)
		{
			if (i == 1)
			{
				switch(msg->iso_bits)
				{
				case BITS_64:
					memcpy(data + pos, bitmap_default, 8);
					pos += 8;
					break;
				case BITS_128:
					memcpy(data + pos, bitmap_default, 16);
					pos += 16;
					break;
				default:
					printf("please set msg->iso_bits in ISO8583_get_msg\n");
					return -1;
					break;
				}
				continue;
			}

			if (msg->field[i].field_pointer == NULL){
				continue;
			}
			MY_BITSET(bitmap, i);

			switch(msg->iso_def[i].typ)
			{
			case TYP_BCD:
			case TYP_BIN:
			case TYP_BIT:
				{
					switch(msg->iso_def[i].fmt)
					{
					case FMT_FIXED:
						memcpy(data + pos, msg->field[i].field_pointer, msg->field[i].field_length);
						pos += (int)msg->field[i].field_length;
						break;
					case FMT_LLVAR:
						if (msg->field[i].field_flag == 1)
						{
							/*如果BCD且长度为奇数，后补f*/
							sprintf(sz, "%02d", msg->field[i].field_length*2 - 1); /*长度标记减1*/
							hexToByte(sz, buf , 2, 0);
							buf[1] = 0;
							memcpy(data + pos, buf, 1);
							pos += 1;

							memcpy(data + pos, msg->field[i].field_pointer, msg->field[i].field_length );
							pos += (int)msg->field[i].field_length;
						}else{
							sprintf(sz, "%02d", msg->field[i].field_length*2);
							hexToByte(sz, buf , 2, 0);
							buf[1] = 0;
							memcpy(data + pos, buf, 1);
							pos += 1;

							memcpy(data + pos, msg->field[i].field_pointer, msg->field[i].field_length);
							pos += (int)msg->field[i].field_length;
						}

						break;

					case FMT_LLLVAR:
						

						if (msg->field[i].field_flag == 1)
						{
							/*如果BCD且长度为奇数，后补f*/
							sprintf(sz, "%04d", msg->field[i].field_length*2 - 1);/*长度标记减1*/
							hexToByte(sz, buf , 4, 0);
							buf[2] = 0;
							memcpy(data + pos, buf, 2);
							pos += 2;

							memcpy(data + pos, msg->field[i].field_pointer, msg->field[i].field_length );
							pos += (int)msg->field[i].field_length ;
						}else{
							sprintf(sz, "%04d", msg->field[i].field_length*2);
							hexToByte(sz, buf , 4, 0);
							buf[2] = 0;
							memcpy(data + pos, buf, 2);
							pos += 2;

							memcpy(data + pos, msg->field[i].field_pointer, msg->field[i].field_length);
							pos += (int)msg->field[i].field_length;
						}

						break;

					default:
						break;
					}
				}
				break;


			case TYP_ASC:
				switch(msg->iso_def[i].fmt)
				{
				case FMT_FIXED:
					memcpy(data + pos, msg->field[i].field_pointer, (int)msg->field[i].field_length);
					pos += (int)msg->field[i].field_length;
					break;
				case FMT_LLVAR:
					sprintf(sz, "%02d", msg->field[i].field_length);
					hexToByte(sz, buf , 2, 0);
					buf[1] = 0;
					memcpy(data + pos, buf, 1);
					pos += 1;		
					memcpy(data + pos, msg->field[i].field_pointer, msg->field[i].field_length);
					pos += (int)msg->field[i].field_length;

					break;

				case FMT_LLLVAR:
					sprintf(sz, "%04d", msg->field[i].field_length);
					hexToByte(sz, buf , 4, 0);
					buf[2] = 0;
					memcpy(data + pos, buf, 2);
					pos += 2;
					memcpy(data + pos, msg->field[i].field_pointer, msg->field[i].field_length);
					pos += (int)msg->field[i].field_length;
					break;

				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	}else{
		for (i = 0 ; i <= msg->iso_bits ; i ++)
		{
			if (i == 1)
			{
				switch(msg->iso_bits)
				{
				case BITS_64:
					memcpy(data + pos, bitmap_default, 8);
					pos += 8;
					break;
				case BITS_128:
					memcpy(data + pos, bitmap_default, 16);
					pos += 16;
					break;
				default:
					printf("please set msg->iso_bits in ISO8583_get_msg\n");
					return -1;
					break;
				}
				continue;
			}

			if (msg->field[i].field_pointer == NULL){
				continue;
			}
			MY_BITSET(bitmap, i);

			switch(msg->iso_def[i].typ)
			{
			case TYP_BCD:
				{
					switch(msg->iso_def[i].fmt)
					{
					case FMT_FIXED:
						memcpy(data + pos, msg->field[i].field_pointer, msg->field[i].field_length);
						pos += (int)msg->field[i].field_length;
						break;
					case FMT_LLVAR:
						sprintf(sz, "%02d", msg->field[i].field_length*2);
						sz[2] = 0;
						memcpy(data + pos, sz, 2);
						pos += 2;

						memcpy(data + pos, msg->field[i].field_pointer, msg->field[i].field_length);
						pos += (int)msg->field[i].field_length;

						break;

					case FMT_LLLVAR:
						sprintf(sz, "%03d", msg->field[i].field_length*2);
						sz[3] = 0;
						memcpy(data + pos, sz, 3);
						pos += 3;

						memcpy(data + pos, msg->field[i].field_pointer, msg->field[i].field_length);
						pos += (int)msg->field[i].field_length;
						break;

					default:
						break;
					}
				}
				break;

			case TYP_BIN:
			case TYP_BIT:
			case TYP_ASC:
				switch(msg->iso_def[i].fmt)
				{
				case FMT_FIXED:
					memcpy(data + pos, msg->field[i].field_pointer, (int)msg->field[i].field_length);
					pos += (int)msg->field[i].field_length;
					break;
				case FMT_LLVAR:
					sprintf(sz, "%02d", msg->field[i].field_length);
					sz[2] = 0;
					memcpy(data + pos, sz, 2);
					pos += 2;	
					memcpy(data + pos, msg->field[i].field_pointer, (int)msg->field[i].field_length);
					pos += (int)msg->field[i].field_length;
					break;

				case FMT_LLLVAR:
					sprintf(sz, "%03d", msg->field[i].field_length);
					sz[3] = 0;
					memcpy(data + pos, sz, 3);
					pos += 3;

					memcpy(data + pos, msg->field[i].field_pointer, (int)msg->field[i].field_length);
					pos += (int)msg->field[i].field_length;
					break;

				default:
					break;
				}
				break;
			default:
				break;
			}

		}
	}

	/*reset bitmap*/
	/*MY_BITSET(bitmap, 1);*/
	if (msg->iso_bits == BITS_64)
	{
		/*MY_BITSET(bitmap, 64);*/
		switch(msg->iso_def[0].typ)
		{
		case TYP_BCD:
		case TYP_BIN:
		case TYP_BIT:
			memcpy(data + msg->iso_def[0].len / 2 , bitmap, 8);
			break;
		case TYP_ASC:
			memcpy(data + msg->iso_def[0].len  , bitmap, 8);
		default:
			break;
		}

	}else if (msg->iso_bits == BITS_128){
		/*MY_BITSET(bitmap, 128);*/
		switch(msg->iso_def[0].typ)
		{
		case TYP_BCD:
		case TYP_BIN:
		case TYP_BIT:
			memcpy(data + msg->iso_def[0].len / 2 , bitmap, 16);
			break;
		case TYP_ASC:
			memcpy(data + msg->iso_def[0].len  , bitmap, 16);
		default:
			break;
		}
	}


	/*reset mac*/	
	/*memcpy(data + pos , "12345678", 8);
	pos += 8;*/

	data[pos] = 0;
	*len = pos;
	return pos;
}

/****************************************************************
*   Function name    : ISO8583_set_msg
*   Author           : Peng GuoYi
*   Coding Date      : 2012/02/23 19:30
*   Description      : 
*   Return type      : 
*   Argument         : ISO8583_MSG*            --存放8583包的内存空间    
*                      const char *data        --8583的数据内容
*                      int len                 --8583的数据长度
****************************************************************/
int   ISO8583_set_msg(ISO8583_MSG* msg, const unsigned char *data, int len )
{
	char buf[32];
	int MAX_FIELD_COUNT = 0;
	int BITMAP_BITS = 0;
	int i,field_len;
	unsigned char * p;
	unsigned char bitmap[32] = {0};
	int pos;

	if (msg == NULL){
		printf("please set msg in ISO8583_set_msg\n");
		ISO8583_reset(msg);
		return -1;
	}

	if (data == NULL){
		printf("please set data in ISO8583_set_msg\n");
		msg->is_error = 1;
		ISO8583_reset(msg);
		return -1;
	}

	if (msg->is_error == 1){
		return -1;
	}

	
	pos = 0;

	/*get Message Type Indicator*/
	p = (unsigned char *)malloc(msg->iso_def[0].len + 10);
	switch(msg->iso_def[0].typ)
	{
	case TYP_BCD:
		field_len = msg->iso_def[0].len / 2;
		memcpy(p, data + pos, field_len);
		p [field_len] = 0;
		pos += field_len;
		msg->field[0].field_pointer = (unsigned char *) p;
		msg->field[0].field_length = field_len;
		break;
	case TYP_BIN:
	case TYP_BIT:
	case TYP_ASC:
		field_len = msg->iso_def[0].len;
		memcpy(p, data + pos, field_len);
		p [field_len] = 0;
		pos += field_len;
		msg->field[0].field_pointer = (unsigned char *) p;
		msg->field[0].field_length = field_len;
	default:
		break;
	}
	msg->field[0].field_flag = 0;

	/* get Bitmap */
	p = (unsigned char *)malloc(msg->iso_def[1].len*2 + 10);
	if (msg->iso_bits == BITS_64){
		BITMAP_BITS = 8;
		MAX_FIELD_COUNT = 64;
	}else if (msg->iso_bits == BITS_128) {
		BITMAP_BITS = 16;
		MAX_FIELD_COUNT = 128;
	}
	memcpy(bitmap, data + pos, BITMAP_BITS*sizeof(char));

	/*to hex*/
	memcpy(p, bitmap, BITMAP_BITS*sizeof(char));
	pos += BITMAP_BITS;
	msg->field[1].field_pointer = (unsigned char *) p;
	msg->field[1].field_length = BITMAP_BITS;
	msg->field[1].field_flag = 0;

	if (msg->compress == 1)
	{
		/* get 2 ... BITS_64 or BITS_128 field value*/
		for (i= 2; i<= MAX_FIELD_COUNT;i ++)
		{

			if(MY_BITGET(bitmap, i))
			{
				if (msg->iso_def[i].len == NULL){
					printf("FIELD[%d] NOT DEFINE. \n",i);
					ISO8583_reset(msg);
					return -1;
				}
				msg->field[i].field_flag = 0;

				switch(msg->iso_def[i].typ)
				{				
				case TYP_BCD:
					{
						switch(msg->iso_def[i].fmt)
						{
						case FMT_FIXED:
							field_len = msg->iso_def[i].len;
							if (field_len % 2 == 1){
								field_len += 1;
							}
							break;
						case FMT_LLVAR:	
							field_len = BCD2INT(data + pos , 1);
							pos += 1;
							if (field_len % 2 == 1){
								field_len += 1;
								msg->field[i].field_flag = 1;
							}
							break;
						case FMT_LLLVAR:
							field_len = BCD2INT(data + pos , 2);
							pos += 2;
							if (field_len % 2 == 1){
								field_len += 1;
								msg->field[i].field_flag = 1;
							}
							break;
						default:
							break;
						}
													
						field_len = field_len / 2;
						p = (unsigned char *)malloc(field_len + 10);
						memcpy(p ,data + pos, field_len);
						p[field_len] = 0;
						pos += field_len;
						msg->field[i].field_pointer = (unsigned char *) p;
						msg->field[i].field_length = field_len ;
						

						break;
					}

				case TYP_BIN:
				case TYP_BIT:
					{
						switch(msg->iso_def[i].fmt)
						{
						case FMT_FIXED:
							field_len = msg->iso_def[i].len;
							if (field_len % 2 == 1){
								field_len = (field_len + 1)  ;
							}/*else field_len = (field_len ) ;*/
							break;
						case FMT_LLVAR:	
							field_len = BCD2INT(data + pos , 1);
							pos += 1;
							if (field_len % 2 == 1){
								field_len = (field_len + 1) / 2 ;
								msg->field[i].field_flag = 1;
							}else field_len = (field_len ) / 2;
							break;
						case FMT_LLLVAR:
							field_len = BCD2INT(data + pos , 2);
							pos += 2;
							if (field_len % 2 == 1){
								field_len = (field_len + 1) / 2 ;
								msg->field[i].field_flag = 1;
							}else field_len = (field_len ) / 2;
							break;
						default:
							break;
						}
					
						p = (unsigned char *)malloc(field_len + 10);
						memcpy(p ,data + pos, field_len) ;
						p[field_len] = 0;
						pos += field_len;
						msg->field[i].field_pointer = (unsigned char *) p;
						msg->field[i].field_length = field_len ;		
						
						break;
					}				

				case TYP_ASC:
					{
						switch(msg->iso_def[i].fmt)
						{
						case FMT_FIXED:
							field_len = msg->iso_def[i].len;
							break;
						case FMT_LLVAR:	
							field_len = BCD2INT(data + pos , 1);
							pos += 1;
							break;
						case FMT_LLLVAR:
							field_len = BCD2INT(data + pos , 2);
							pos += 2;
							break;
						default:
							break;
						}

						p = (unsigned char *)malloc(field_len + 10);
						memcpy(p ,data + pos, field_len);
						p[field_len] = 0;
						pos += field_len;
						msg->field[i].field_pointer = (unsigned char *) p;
						msg->field[i].field_length = field_len ;
					}

				default:
					break;
				}
			}
/*
//////////////////////////////////////////////////////////////////////////
			if (msg->field[i].field_pointer != NULL)
			{	
				char szBuf[1000] = {0};
				szBuf[0] = 0;
				switch(msg->iso_def[i].typ)
				{
				case TYP_BCD:
					switch(msg->iso_def[i].fmt)
					{
					case FMT_FIXED:
						if (msg->iso_def[i].len % 2 == 1)
						{
							char * pi = (char *)malloc(msg->iso_def[i].len*sizeof(char) + 10);
							byteToHex((char *)msg->field[i].field_pointer, pi, msg->field[i].field_length);
							pi[msg->field[i].field_length * 2] = 0;
							memcpy(szBuf, pi + 1, msg->field[i].field_length * 2 - 1);
							szBuf[msg->field[i].field_length * 2 - 1] = 0;
							free(pi);
						}else{
							byteToHex((char *)msg->field[i].field_pointer, szBuf, msg->field[i].field_length);
							szBuf[msg->field[i].field_length * 2] = 0;
						}
						break;
					case FMT_LLVAR:					
					case FMT_LLLVAR:
						byteToHex((char *)msg->field[i].field_pointer, szBuf, msg->field[i].field_length);
						szBuf[msg->field[i].field_length * 2] = 0;
						break;
					}				
					break;

				case TYP_BIN:
				case TYP_BIT:
					switch(msg->iso_def[i].fmt)
					{
					case FMT_FIXED:
						if (msg->iso_def[i].len % 2 == 1)
						{
							char * pi = (char *)malloc(msg->iso_def[i].len*2 * sizeof(char) + 10);
							byteToHex((char *)msg->field[i].field_pointer, pi, msg->field[i].field_length);
							pi[msg->field[i].field_length * 2] = 0;
							memcpy(szBuf, pi + 1, msg->field[i].field_length * 2 - 1);
							szBuf[msg->field[i].field_length * 2 - 1] = 0;
							free(pi);
						}else{
							byteToHex((char *)msg->field[i].field_pointer, szBuf, msg->field[i].field_length);
							szBuf[msg->field[i].field_length * 2] = 0;
						}
						break;
					case FMT_LLVAR:					
					case FMT_LLLVAR:
						byteToHex((char *)msg->field[i].field_pointer, szBuf, msg->field[i].field_length);
						szBuf[msg->field[i].field_length * 2] = 0;
						break;
					}				
					break;
				case TYP_ASC:
					memcpy(szBuf ,msg->field[i].field_pointer, msg->field[i].field_length);
					szBuf[msg->field[i].field_length ] = 0;
				default:
					break;
				}

				printf("[%2d]: {%s}\n",i,szBuf);
			}
			//////////////////////////////////////////////////////////////////////////
*/

		} /*for*/
	}/* compress is false*/
	else 
	{
		/* get 2 ... BITS_64 or BITS_128 field value*/
		for (i= 2; i<= MAX_FIELD_COUNT;i ++)
		{
			if(MY_BITGET(bitmap, i))
			{
				if (msg->iso_def[i].len == NULL){
					printf("FIELD[%d] NOT DEFINE. \n",i);
					ISO8583_reset(msg);
					return -1;
				}

				switch(msg->iso_def[i].typ)
				{				
				case TYP_BCD:
					{
						switch(msg->iso_def[i].fmt)
						{
						case FMT_FIXED:
							field_len = msg->iso_def[i].len;
							break;
						case FMT_LLVAR:	
							memcpy(buf, data + pos , 2);
							buf[2] = 0;
							field_len = atoi(buf);
							pos += 2;							
							break;
						case FMT_LLLVAR:
							memcpy(buf, data + pos , 3);
							buf[3] = 0;
							field_len = atoi(buf);
							pos += 3;
							break;
						default:
							break;
						}

						field_len = field_len / 2;
						p = (unsigned char *)malloc(field_len + 10);
						memcpy(p ,data + pos, field_len);
						p[field_len] = 0;
						pos += field_len;
						msg->field[i].field_pointer = (unsigned char *) p;
						msg->field[i].field_length = field_len ;
						break;
					}
				case TYP_BIN:
				case TYP_BIT:
				case TYP_ASC:
					{
						switch(msg->iso_def[i].fmt)
						{
						case FMT_FIXED:
							field_len = msg->iso_def[i].len;
							break;
						case FMT_LLVAR:	
							memcpy(buf, data + pos , 2);
							buf[2] = 0;
							field_len = atoi(buf);
							pos += 2;							
							break;
						case FMT_LLLVAR:
							memcpy(buf, data + pos , 3);
							buf[3] = 0;
							field_len = atoi(buf);
							pos += 3;
							break;
						default:
							break;
						}

						p = (unsigned char *)malloc(field_len + 10);
						memcpy(p ,data + pos, field_len);
						p[field_len] = 0;
						pos += field_len;
						msg->field[i].field_pointer = (unsigned char *) p;
						msg->field[i].field_length = field_len ;
					}

				default:
					break;
				}

			}
		} /* for*/
	}

	return 0;


}

/****************************************************************
*   Function name    : BCD2INT
*   Author           : Peng GuoYi
*   Coding Date      : 2012/02/23 19:30
*   Description      : BCD转整形，目前只支持4个字符长度
*   Return type      : 
*   Argument         : unsigned char* b        --BCD格式的数据
*                      int len                 --长度
****************************************************************/
int BCD2INT (const unsigned char* b, int len)
{
	/* this function make sure len <= 4 */
	int i,val,tmp, j;
	unsigned char a;
	val = 0;
	for (i = len - 1, j = 0; i >= 0 ; i--, j++)
	{
		a = b[i];
		tmp = ((a>>4)*10 + (a&15)) ;
		if(j == 1){
			tmp *= 100;
		}else if(j == 2){
			tmp *= 10000;
		}else if(j == 3){
			tmp *= 1000000;
		}else if(j == 4){
			tmp *= 100000000;
		}

		val += tmp;
	}
	return val;
}


/*
功能描述：变输入数据为bcd形式
输入：	instr-字符串, inLen-instr长度, type-当inLen为奇数时补0方式,0为前补0(默认),其他为后补0
输出：	outstr-BCD字符串
返回：	输出字符长度
*/
int hexToByte (const char *instr, char *outstr, int inLen, int type)
{
	register int           i, j;
	register char          ch;
	char tmp[4096];

	memset(tmp, 0, sizeof(tmp));
	if(inLen%2)	/*奇数*/
	{
		if(type)	/*后补0*/
		{
			memcpy(tmp, instr, inLen);
			tmp[inLen] = '0';
		}
		else		/*前补0*/
		{
			tmp[0] = '0';
			memcpy(tmp+1, instr, inLen);
		}
		inLen++;
	}
	else
		memcpy(tmp, instr, inLen);

	for (i = j = 0; i<inLen; i++)  
	{
		ch = tmp[i];
		if (ch >= '0' && ch <= '9')
			ch -= '0';
		else
		{
			if (ch >= 'a' && ch <= 'f')
				ch = ch - 'a' + 10;
			else
			{
				if (ch >= 'A' && ch <= 'F')
					ch = ch - 'A' + 10;
				else
					ch = 0;
			}
		}
		if (i & 1)
			outstr[j++] += ch;
		else
			outstr[j] = ch << 4;
	}
	outstr[j] = 0;

	return (j);
}

/*
convert FT_BINARY value in input buffer to hex string
(e.g 0x137A8C (3 bytes) to "137A8C" (6 bytes),
i.e. the reverse function of "byteToHex"
*/
void byteToHex (const char *in_buff, char *out_buff, int in_len)
{
	int   i, j;
	char  ch;

	for (i = j = 0; i < in_len; i++)  
	{
		ch = (in_buff[i] >> 4) & 0x0f;
		out_buff[j++] = ch > 9 ? ch + 'a' - 10 : ch + '0';
		ch = in_buff[i] & 0x0f;
		out_buff[j++] = ch > 9 ? ch + 'a' - 10 : ch + '0';
	}
	out_buff[j] = 0;
}


