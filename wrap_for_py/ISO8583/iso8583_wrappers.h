#ifndef __iso8583_wrappers_h__
#define __iso8583_wrappers_h__
#include <stdio.h>

#ifndef NULL
#define NULL 0
#endif
#define  MY_DEBUG

#ifdef MY_DEBUG
#define MY_TRACE(x,args)  fprintf(stderr, x, args)
#else
#define MY_TRACE(x,args)
#endif
#define MY_BITGET(p,n)  ((p)[(n-1)/8]&(0x80>>((n-1)%8)))       /*取bit位*/
#define MY_BITSET(p,n)  ((p)[(n-1)/8]|=(0x80>>((n-1)%8)))      /*设bit位*/
#define MY_BITCLR(p,n)  ((p)[(n-1)/8]&=(~(0x80>>((n-1)%8))))   /*清bit位*/

typedef enum{
	BITS_64 = 64,
	BITS_128 = 128
}ISO8583_FIELDS;

typedef struct tagISO8583_DEF {	
	short typ;
	short fmt;
	int   len;
#if ISO8583_VERSION==93
	const char *dsc;
#endif
} ISO8583_DEF;

typedef struct tagISO8583_Field{
	unsigned char * field_pointer;
	int field_length;
	int field_flag; /*1：标记field_pointer末尾是否带有f, 0:不带有f结尾*/
}ISO8583_Field;

typedef struct tagISO8583_MSG
{
	int compress; /*是否压缩，1: BCD码生效 ， 0: BCD码当 ASC 处理,不压缩*/
	int is_error;
	int  iso_bits; 
	ISO8583_DEF iso_def[BITS_128 + 2];
	ISO8583_Field field[BITS_128 + 2];
}ISO8583_MSG;

#define TYP_BIT    0 
#define TYP_BCD    1
#define TYP_ASC    2
#define TYP_BIN    3

#define FMT_FIXED  0
#define FMT_LVAR   1
#define FMT_LLVAR  2
#define FMT_LLLVAR 3

ISO8583_MSG  * ISO8583_malloc(ISO8583_DEF* def,size_t def_size, ISO8583_FIELDS fields, int compress );
void   ISO8583_free(ISO8583_MSG* msg);
int    ISO8583_set_msg(ISO8583_MSG* msg, const unsigned char *data, int len );
int    ISO8583_set_msg_hex(ISO8583_MSG* msg, const char *data, int len );
void   ISO8583_print(ISO8583_MSG* msg);
int    ISO8583_get_msg(ISO8583_MSG* msg, unsigned char *data, int data_max_size, int* len );
int    ISO8583_get_msg_hex(ISO8583_MSG* msg, char *data, int data_max_size, int* len );
int    ISO8583_set_field(ISO8583_MSG* msg,int idx, char *data, int len );
int    ISO8583_get_field(const ISO8583_MSG *msg, int idx, unsigned char *data, int max_len );
int		hexToByte (const char *instr, char *outstr, int inLen, int type);
void	byteToHex (const char *in_buff, char *out_buff, int in_len);

#endif /* __iso8583_wrappers_h__*/
