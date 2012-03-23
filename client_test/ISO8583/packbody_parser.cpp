#include "packbody_parser.h"
#include <stdlib.h>
#include <string.h>
int hexToByte (const char *instr, char *outstr, int inLen, int type = 0);
void byteToHex (const char *in_buff, char *out_buff, int in_len);
int BCD2INT (const unsigned char* b, int len);

void   pkt_print(PKT_MSG* msg)
{
	int i;
	char *p;
	char szBuf[2000];

	if (msg == NULL){
		printf("please set msg in pkt_print\n");
		return ;
	}

	printf("\n**********************************************\n");
	for (i = 0; i < msg->max_id_def; i++)
	{
		if (msg->field[i].field_pointer != NULL)
		{
			//if (i == 52)
			//{
			//	i = i;
			//}
			szBuf[0] = 0;
			switch(msg->iso_def[i].typ)
			{
			case TYP_BCD:
				byteToHex((char *)msg->field[i].field_pointer, szBuf, msg->field[i].field_length);
				szBuf[msg->field[i].field_length * 2] = 0;
				break;
			case TYP_BIN:
			case TYP_BIT:
				byteToHex((char *)msg->field[i].field_pointer, szBuf, msg->field[i].field_length);
				szBuf[msg->field[i].field_length * 2] = 0;
				break;
			case TYP_ASC:
				memcpy(szBuf ,msg->field[i].field_pointer, msg->field[i].field_length);
				szBuf[msg->field[i].field_length ] = 0;
			default:
				break;
			}

			//p = (char *)msg->field[i].field_pointer;
			//printf("[%2d]: {%s}\n",i,szBuf);
			printf("[%2d]: <%s>   //%s\n",i,szBuf,msg->iso_def[i].dsc);
			//printf("[%2d]:<%-16s> {%s}   //%s\n",i,msg->iso_def[i].dsc,szBuf);
		}		
	}
	printf("**********************************************\n\n");
}

PKT_MSG  * pkt_malloc(PKT_DEF* def,size_t def_size)
{
	PKT_MSG* msg = NULL;

	if (def == NULL){
		printf("please set PKT_DEF in pkt_malloc\n");
		return NULL;
	}

	msg = (PKT_MSG*)malloc(sizeof(PKT_MSG) );
	memset(msg , 0 ,sizeof(PKT_MSG));
	msg->max_id_def = (int)def_size/sizeof(PKT_DEF) ;
	msg->is_error = 0;
	memcpy(msg->iso_def , def, def_size);
	return msg;
}


int    pkt_get_field(const PKT_MSG *msg, int idx, unsigned char *data, int max_len )
{
	char *p;
	int n = 0;
	int f_len = 0;
	data[0] = 0;
	f_len = 0;
	if (msg != NULL){

		if (msg->is_error == 1){
			return 0;
		}

		if (msg->field[idx].field_pointer != NULL)
		{
			if (msg->field[idx].field_length >= max_len){
				printf("error ! please set data buffer bigger!");
				return 0;
			}		

			switch(msg->iso_def[idx].typ)
			{
			case TYP_BCD:
			case TYP_BIN:
			case TYP_BIT:
			case TYP_ASC:
				{
					switch(msg->iso_def[idx].fmt)
					{
					case FMT_FIXED: 
						switch(msg->iso_def[idx].fil)
						{
						case L_BLANK:
							p = (char *)msg->field[idx].field_pointer;							
							n = 0;
							while( n < msg->field[idx].field_length && p[n] == ' ') {
								n ++;
							}
							memcpy(data, p + n, msg->field[idx].field_length - n);
							data[msg->field[idx].field_length - n] = 0;	
							f_len = msg->field[idx].field_length - n;
							break;

						case R_BLANK:
							p = (char *)msg->field[idx].field_pointer;
							memcpy(data, p , msg->field[idx].field_length);
							data[msg->field[idx].field_length] = 0;	
							n = msg->field[idx].field_length;
							while( --n >= 0 && data[n] == ' ') {
								data[n] = 0;
							}
							f_len = n + 1;
							break;

						case L_ZERO:
							p = (char *)msg->field[idx].field_pointer;							
							n = 0;
							while( n < msg->field[idx].field_length && p[n] == '0') {
								n ++;
							}
							memcpy(data, p + n, msg->field[idx].field_length - n);
							data[msg->field[idx].field_length - n] = 0;	
							f_len = msg->field[idx].field_length - n;
							break;

						case R_ZERO:
							p = (char *)msg->field[idx].field_pointer;
							memcpy(data, p , msg->field[idx].field_length);
							data[msg->field[idx].field_length] = 0;	
							n = msg->field[idx].field_length;
							while( --n >= 0 && data[n] == '0') {
								data[n] = 0;
							}
							f_len = n + 1;
							break;
						case NULL:
							p = (char *)msg->field[idx].field_pointer;
							memcpy(data, p , msg->field[idx].field_length);
							data[msg->field[idx].field_length] = 0;	
							f_len = msg->field[idx].field_length;
							break;
						default:
							break;
						}
						break;

					case FMT_LLVAR:					
					case FMT_LLLVAR:
						p = (char *)msg->field[idx].field_pointer;
						memcpy(data, p , msg->field[idx].field_length);
						data[msg->field[idx].field_length] = 0;	
						f_len = msg->field[idx].field_length;
						break;
					}
				}
			default:
				break;
			}
		}		
	}else{
		data[0] = 0;
		f_len = 0;
	}

	return f_len;
}

//int    pkt_get_field(const PKT_MSG *msg, int idx, unsigned char *data, int max_len )
//{
//	char *p;
//	int f_len = 0;
//	if (msg != NULL){
//
//		if (msg->is_error == 1){
//			return -1;
//		}
//
//		if (msg->field[idx].field_pointer != NULL)
//		{
//			if (msg->field[idx].field_length >= max_len)
//			{
//				printf("error ! please set data buffer bigger!");
//				return 0;
//			}
//			p = (char *)msg->field[idx].field_pointer;
//			memcpy(data, p , msg->field[idx].field_length);
//			data[msg->field[idx].field_length] = 0;	
//			f_len = msg->field[idx].field_length;
//		}		
//	}else{
//		data[0] = 0;
//		f_len = 0;
//	}
//
//	return f_len;
//}


void   pkt_reset(PKT_MSG* msg)
{
	int i;
	char *p;
	if (msg != NULL){
		for (i = 0; i <msg->max_id_def; i++)
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

void   pkt_free(PKT_MSG* msg)
{
	int i;
	char *p;
	if (msg != NULL){
		pkt_reset(msg);
		free(msg);
		msg = NULL;
	}	
}

int   pkt_set_msg_hex(PKT_MSG* msg, const char *data, int len )
{
	int ret = 0;
	unsigned char *p = NULL;
	int pLen = 0;
	if (msg == NULL){
		printf("please set msg in pkt_set_msg_hex\n");
		return -1;
	}

	if (data == NULL){
		printf("please set data in pkt_set_msg_hex\n");
		msg->is_error = 1;
		return -1;
	}

	if (msg->is_error == 1){
		return -1;
	}

	p = (unsigned char *)malloc(len*sizeof(char) + 10);
	pLen = hexToByte(data, (char*)p, len);

	/*ret = */pkt_set_msg(msg, p, pLen);

	free(p);
	return ret;
}


int    pkt_set_field(PKT_MSG* msg,int idx, char *data, int len )
{
	bool flag = false;
	unsigned char *p = NULL;

	if (idx == 3)
	{
		idx = idx;
	}

	if (msg == NULL){
		printf("please set msg in pkt_set_field.\n");
		return -1;
	}

	if (data == NULL){
		printf("please set data in pkt_set_field.\n");
		msg->is_error = 1;
		return -1;
	}

	if (msg->iso_def[idx].len == NULL)
	{
		printf("FIELD[%d] NOT DEFINE. pkt_set_field.\n",idx);
		msg->is_error = 1;
		return -1;
	}

	if (msg->is_error == 1){
		return -1;
	}

	switch(msg->iso_def[idx].typ)
	{
	case TYP_BCD:
	case TYP_BIN:
	case TYP_BIT:
	case TYP_ASC:
		{
			switch(msg->iso_def[idx].fmt)
			{
			case FMT_FIXED:
				switch(msg->iso_def[idx].fil)
				{
				case L_BLANK:
				case R_BLANK:
				case L_ZERO:
				case R_ZERO:
					if (msg->iso_def[idx].len < len)
					{
						printf("Error! len  > %d. Please check FIELD[%d] len define in pkt_set_field.\n",msg->iso_def[idx].len , idx);
						msg->is_error = 1;
						return -1;
					}
					break;
				case NULL:
					if (msg->iso_def[idx].len != len)
					{
						printf("Error! len  != %d. Please check FIELD[%d] len define in pkt_set_field.\n",msg->iso_def[idx].len , idx);
						msg->is_error = 1;
						return -1;
					}
					break;
				default:
					break;
				}
				break;

			case FMT_LLVAR:					
			case FMT_LLLVAR:
				if (msg->iso_def[idx].fil != NULL)
				{
					printf("when define FMT_LLVAL or FMT_LLLVAR ,make sure msg->iso_def[idx].fil is NULL \n", idx);
					msg->is_error = 1;
					return -1;
				}
				//if(len % 2 == 1) flag = true;
				if (len > msg->iso_def[idx].len)
				{
					printf("Value:[%s] len:[%d] is lengther  , Please check FIELD[%d] LEN pkt_set_field\n",data, len, msg->iso_def[idx].len , idx);
					msg->is_error = 1;
					return -1;
				}
				break;
			}
		}
	default:
		break;
	}
	p = (unsigned char *)(msg->field[idx].field_pointer);
	if (p != NULL){
		free((unsigned char *)p);
	}
	switch(msg->iso_def[idx].typ)
	{
	case TYP_BCD:
		switch(msg->iso_def[idx].fmt)
		{
		case FMT_FIXED:			
		case FMT_LLVAR:			
		case FMT_LLLVAR:
			if (len % 2 == 1)
			{
				printf("set field value error ! length of [%s] must to be 2 twice .",data);
				msg->is_error = 1;
				return -1;
			}
			p = (unsigned char *)malloc(msg->iso_def[idx].len + 10);
			//byteToHex (data,(char *)p, len);
			hexToByte(data, (char *)p, msg->iso_def[idx].len);
			p[len / 2] = 0;
			msg->field[idx].field_pointer = (unsigned char *)p;
			msg->field[idx].field_length = len / 2;
			break;

		default:
			break;
		}

		break;
	case TYP_BIN:
	case TYP_BIT:
	case TYP_ASC:

		switch(msg->iso_def[idx].fil)
		{
		case L_BLANK:
			p = (unsigned char *)malloc(msg->iso_def[idx].len + 10);
			memset(p,' ', msg->iso_def[idx].len);
			memcpy(p + msg->iso_def[idx].len - len, data , len );
			p[msg->iso_def[idx].len] = 0;
			msg->field[idx].field_pointer = (unsigned char *)p;
			msg->field[idx].field_length = msg->iso_def[idx].len;
			break;

		case R_BLANK:
			p = (unsigned char *)malloc(msg->iso_def[idx].len + 10);
			memset(p,' ', msg->iso_def[idx].len);
			memcpy(p, data , len );
			p[msg->iso_def[idx].len] = 0;
			msg->field[idx].field_pointer = (unsigned char *)p;
			msg->field[idx].field_length = msg->iso_def[idx].len;
			break;

		case L_ZERO:
			p = (unsigned char *)malloc(msg->iso_def[idx].len + 10);
			memset(p,'0', msg->iso_def[idx].len);
			memcpy(p + msg->iso_def[idx].len - len, data , len );
			p[msg->iso_def[idx].len] = 0;
			msg->field[idx].field_pointer = (unsigned char *)p;
			msg->field[idx].field_length = msg->iso_def[idx].len;
			break;

		case R_ZERO:
			p = (unsigned char *)malloc(msg->iso_def[idx].len + 10);
			memset(p,'0', msg->iso_def[idx].len);
			memcpy(p, data , len );
			p[msg->iso_def[idx].len] = 0;
			msg->field[idx].field_pointer = (unsigned char *)p;
			msg->field[idx].field_length = msg->iso_def[idx].len;
			break;

		case NULL:
			p = (unsigned char *)malloc(msg->iso_def[idx].len + 10);
			memcpy(p, data , len );
			p[len] = 0;
			msg->field[idx].field_pointer = (unsigned char *)p;
			msg->field[idx].field_length = len;
			break;
		default:
			break;
		}
		
	default:
		break;
	}
	return len;
}

int    pkt_get_msg_hex(PKT_MSG* msg,  char *data, int data_max_size, int* len )
{
	unsigned char *p = (unsigned char *)malloc(data_max_size + 2);

	if (msg == NULL){
		printf("please set msg in pkt_get_msg_hex\n");
		return -1;
	}

	if (data == NULL){
		printf("please set data in pkt_get_msg_hex\n");
		return -1;
	}

	if (msg->is_error == 1){
		data = NULL;
		*len = 0;
		return -1;
	}

	pkt_get_msg(msg, p, data_max_size, len);
	byteToHex((char *)p, (char *)data , *len);
	data[*len*2] = 0;
	free(p);
	*len = *len * 2;
	return *len*2;
}

int    pkt_get_msg(PKT_MSG* msg, unsigned char *data, int data_max_size, int* len )
{
	int pos;
	int i,t;
	char sz[1000];
	char bitmap[16 + 1];
	char bitmap_default[] = {"000000000000000000000000"};
	char buf[1000];

	if (msg == NULL){
		printf("please set msg in pkt_get_msg\n");
		return -1;
	}

	if (data == NULL){
		printf("please set data in pkt_get_msg\n");
		return -1;
	}

	if (msg->is_error == 1){
		data = NULL;
		*len = 0;
		return -1;
	}

	memset(bitmap, 0, sizeof(bitmap));
	pos = 0;

	for (i = 0 ; i < msg->max_id_def ; i ++)
	{
		if (msg->field[i].field_pointer == NULL){
			continue;
		}

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


	data[pos] = 0;
	*len = pos;
	return pos;
}


int   pkt_set_msg(PKT_MSG* msg, const unsigned char *data, int len )
{
	char buf[32];
	unsigned char ch[1000];
	int MAX_FIELD_COUNT = 0;
	int BITMAP_BITS = 0;
	int i,field_len;
	unsigned char * p;
	unsigned char bitmap[32] = {0};
	int pos;

	if (msg == NULL){
		printf("please set msg in pkt_set_msg\n");
		pkt_reset(msg);
		return -1;
	}

	if (data == NULL){
		printf("please set data in pkt_set_msg\n");
		msg->is_error = 1;
		pkt_reset(msg);
		return -1;
	}

	if (msg->is_error == 1){
		return -1;
	}

	pos = 0;


	for (i= 0; i< msg->max_id_def; i ++)
	{
		if (msg->iso_def[i].len == NULL){
			printf("FIELD[%d] NOT DEFINE. \n",i);
			pkt_reset(msg);
			msg->is_error = 1;
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

				if (pos > len){	
					printf("packet data format is error. \n");
					pkt_reset(msg);
					msg->is_error = 1;
					return -1;
				}
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

				//field_len = field_len ;
				p = (unsigned char *)malloc(field_len + 10);
				memcpy(p ,data + pos, field_len);
				p[field_len] = 0;
				pos += field_len;
				msg->field[i].field_pointer = (unsigned char *) p;
				msg->field[i].field_length = field_len ;

				if (pos > len){	
					printf("packet data format is error. \n");
					pkt_reset(msg);
					msg->is_error = 1;
					return -1;
				}
			}

		default:
			break;
		}			
	} // for
	return 0;


}
//
//
//int BCD2INT (const unsigned char* b, int len)
//{
//	/* this function make sure len <= 4 */
//	int i,val,tmp, j;
//	unsigned char a;
//	val = 0;
//	for (i = len - 1, j = 0; i >= 0 ; i--, j++)
//	{
//		a = b[i];
//		tmp = ((a>>4)*10 + (a&15)) ;
//		if(j == 1){
//			tmp *= 100;
//		}else if(j == 2){
//			tmp *= 10000;
//		}else if(j == 3){
//			tmp *= 1000000;
//		}else if(j == 4){
//			tmp *= 100000000;
//		}
//
//		val += tmp;
//	}
//	return val;
//}
//
///*
//功能描述：变输入数据为bcd形式
//输入：	instr-字符串, inLen-instr长度, type-当inLen为奇数时补0方式,0为前补0(默认),其他为后补0
//输出：	outstr-BCD字符串
//返回：	输出字符长度
//*/
//int hexToByte (const char *instr, char *outstr, int inLen, int type)
//{
//	register int           i, j;
//	register char          ch;
//	char tmp[4096];
//
//	memset(tmp, 0, sizeof(tmp));
//	if(inLen%2)	/*奇数*/
//	{
//		if(type)	/*后补0*/
//		{
//			memcpy(tmp, instr, inLen);
//			tmp[inLen] = '0';
//		}
//		else		/*前补0*/
//		{
//			tmp[0] = '0';
//			memcpy(tmp+1, instr, inLen);
//		}
//		inLen++;
//	}
//	else
//		memcpy(tmp, instr, inLen);
//
//	for (i = j = 0; i<inLen; i++)  
//	{
//		ch = tmp[i];
//		if (ch >= '0' && ch <= '9')
//			ch -= '0';
//		else
//		{
//			if (ch >= 'a' && ch <= 'f')
//				ch = ch - 'a' + 10;
//			else
//			{
//				if (ch >= 'A' && ch <= 'F')
//					ch = ch - 'A' + 10;
//				else
//					ch = 0;
//			}
//		}
//		if (i & 1)
//			outstr[j++] += ch;
//		else
//			outstr[j] = ch << 4;
//	}
//	outstr[j] = 0;
//
//	return (j);
//}
//
///*
//convert FT_BINARY value in input buffer to hex string
//(e.g 0x137A8C (3 bytes) to "137A8C" (6 bytes),
//i.e. the reverse function of "byteToHex"
//*/
//void byteToHex (const char *in_buff, char *out_buff, int in_len)
//{
//	int   i, j;
//	char  ch;
//
//	for (i = j = 0; i < in_len; i++)  
//	{
//		ch = (in_buff[i] >> 4) & 0x0f;
//		out_buff[j++] = ch > 9 ? ch + 'A' - 10 : ch + '0';
//		ch = in_buff[i] & 0x0f;
//		out_buff[j++] = ch > 9 ? ch + 'A' - 10 : ch + '0';
//	}
//	out_buff[j] = 0;
//}
//
//
