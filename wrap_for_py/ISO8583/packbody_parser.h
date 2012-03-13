#ifndef __packbody_parser_h__
#define __packbody_parser_h__
#include <stdio.h>

#ifndef NULL
#define NULL 0
#endif

#define MAX_BITS 256

typedef struct tagPKT_DEF {	
	short typ;
	short fmt;
	short fil;
	int   len;
	const char *dsc;
} PKT_DEF;

typedef struct tagpkt_Field{
	unsigned char * field_pointer;
	long field_length;
}pkt_Field;

typedef struct tagPKT_MSG
{
	
	//int compress; /*是否压缩，1: BCD码生效 ， 0: BCD码当 ASC 处理,不压缩*/
	int is_error;
	//int  iso_bits; 
	int max_id_def;
	PKT_DEF iso_def[MAX_BITS + 2];
	pkt_Field field[MAX_BITS + 2];
}PKT_MSG;

#define TYP_BIT    0 
#define TYP_BCD    1
#define TYP_ASC    2
#define TYP_BIN    3

#define FMT_FIXED  0
#define FMT_LVAR   1
#define FMT_LLVAR  2
#define FMT_LLLVAR 3

#define L_BLANK    11
#define R_BLANK    12
#define L_ZERO     13
#define R_ZERO     14

PKT_MSG  * pkt_malloc(PKT_DEF* def,size_t def_size/*, PKT_FIELDS fields, int compress = 1*/);
void   pkt_free(PKT_MSG* msg);
int    pkt_set_msg(PKT_MSG* msg, const unsigned char *data, int len );
int    pkt_set_msg_hex(PKT_MSG* msg, const char *data, int len );
void   pkt_print(PKT_MSG* msg);
int    pkt_get_msg(PKT_MSG* msg, unsigned char *data, int data_max_size, int* len );
int    pkt_get_msg_hex(PKT_MSG* msg, char *data, int data_max_size, int* len );
int    pkt_set_field(PKT_MSG* msg,int idx, char *data, int len );
int    pkt_get_field(const PKT_MSG *msg, int idx, unsigned char *data, int max_len );




#endif /* __packbody_parser_h__*/
