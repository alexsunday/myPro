
#ifndef __iso8583_field_def_h__
#define __iso8583_field_def_h__

#include "iso8583_wrappers.h"

/*������POS�ն�*/
static ISO8583_DEF PE_POS_DEF[] ={
	/*000*/ {TYP_BCD,  FMT_FIXED ,  4}, 
	/*001*/ {TYP_BIT,  FMT_FIXED ,  8}, 
	/*002*/ {TYP_BCD,  FMT_LLVAR ,  30}, 
	/*003*/ {TYP_BCD,  FMT_FIXED ,  6}, 
	/*004*/ {TYP_BCD,  FMT_FIXED ,  12}, 
	/*005*/ {TYP_BCD,  FMT_FIXED ,  NULL}, 
	/*006*/ {TYP_BCD,  FMT_FIXED ,  NULL}, 
	/*007*/ {TYP_BCD,  FMT_FIXED ,  10}, 
	/*008*/ {TYP_BCD,  FMT_FIXED ,  NULL}, 
	/*009*/ {TYP_BCD,  FMT_FIXED ,  NULL}, 
	/*010*/ {TYP_BCD,  FMT_FIXED ,  NULL}, 
	/*011*/ {TYP_BCD,  FMT_FIXED ,  6}, 
	/*012*/ {TYP_BCD,  FMT_FIXED ,  6}, 
	/*013*/ {TYP_BCD,  FMT_FIXED ,  8}, 
	/*014*/ {TYP_BCD,  FMT_FIXED ,  NULL}, 
	/*015*/ {TYP_BCD,  FMT_FIXED ,  4}, 
	/*016*/ {TYP_BCD,  FMT_FIXED ,  NULL}, 
	/*017*/ {TYP_BCD,  FMT_FIXED ,  NULL}, 
	/*018*/ {TYP_BCD,  FMT_FIXED ,  NULL}, 
	/*019*/ {TYP_BCD,  FMT_FIXED ,  NULL}, 
	/*020*/ {TYP_BCD,  FMT_FIXED ,  NULL}, 
	/*021*/ {TYP_BCD,  FMT_FIXED ,  NULL}, 
	/*022*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*023*/ {TYP_BCD,  FMT_FIXED ,  NULL}, 
	/*024*/ {TYP_BCD,  FMT_FIXED ,  3}, 
	/*025*/ {TYP_BCD,  FMT_FIXED ,  NULL}, 
	/*026*/ {TYP_BCD,  FMT_FIXED ,  NULL}, 
	/*027*/ {TYP_BCD,  FMT_FIXED ,  NULL}, 
	/*028*/ {TYP_ASC,  FMT_FIXED ,  9}, 
	/*029*/ {TYP_BCD,  FMT_FIXED ,  NULL}, 
	/*030*/ {TYP_BCD,  FMT_FIXED ,  NULL}, 
	/*031*/ {TYP_ASC,  FMT_LLVAR ,  NULL}, 
	/*032*/ {TYP_BCD,  FMT_LLVAR ,  6}, 
	/*033*/ {TYP_BCD,  FMT_LLVAR ,  NULL}, 
	/*034*/ {TYP_ASC,  FMT_LLVAR ,  99}, 
	/*035*/ {TYP_ASC,  FMT_LLVAR ,  37}, 
	/*036*/ {TYP_ASC,  FMT_LLLVAR,  104}, 
	/*037*/ {TYP_ASC,  FMT_FIXED ,  12}, 
	/*038*/ {TYP_ASC,  FMT_FIXED ,  6}, 
	/*039*/ {TYP_ASC,  FMT_FIXED ,  2}, 
	/*040*/ {TYP_BCD,  FMT_FIXED ,  NULL}, 
	/*041*/ {TYP_ASC,  FMT_FIXED ,  8}, 
	/*042*/ {TYP_ASC,  FMT_FIXED ,  15}, 
	/*043*/ {TYP_ASC,  FMT_LLVAR ,  NULL}, 
	/*044*/ {TYP_ASC,  FMT_LLVAR ,  19}, 
	/*045*/ {TYP_ASC,  FMT_LLVAR ,  NULL}, 
	/*046*/ {TYP_ASC,  FMT_LLLVAR,  16}, 
	/*047*/ {TYP_ASC,  FMT_LLLVAR,  NULL}, 
	/*048*/ {TYP_ASC,  FMT_LLLVAR,  24}, 
	/*049*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*050*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*051*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*052*/ {TYP_BIN,  FMT_FIXED ,  8}, 
	/*053*/ {TYP_BCD,  FMT_FIXED ,  16}, 
	/*054*/ {TYP_ASC,  FMT_LLLVAR,  12}, 
	/*055*/ {TYP_BIN,  FMT_LLLVAR,  999}, 
	/*056*/ {TYP_BIN,  FMT_LLLVAR,  NULL}, 
	/*057*/ {TYP_BCD,  FMT_FIXED ,  NULL}, 
	/*058*/ {TYP_BCD,  FMT_LLVAR ,  NULL}, 
	/*059*/ {TYP_ASC,  FMT_LLLVAR,  NULL}, 
	/*060*/ {TYP_ASC,  FMT_LLLVAR,  NULL}, 
	/*061*/ {TYP_ASC,  FMT_LLLVAR,  999}, 
	/*062*/ {TYP_ASC,  FMT_LLLVAR,  999}, 
	/*063*/ {TYP_ASC,  FMT_LLLVAR,  999}, 
	/*064*/ {TYP_BIN,  FMT_FIXED ,  8},
	/*065*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*066*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*067*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*068*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*069*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*070*/ {TYP_ASC,  FMT_FIXED ,  3},
	/*071*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*072*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*073*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*074*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*075*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*076*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*077*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*078*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*079*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*080*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*081*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*082*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*083*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*084*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*085*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*086*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*087*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*088*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*089*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*090*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*091*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*092*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*093*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*094*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*095*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*096*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*097*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*098*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*099*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*100*/ {TYP_BCD,  FMT_LLVAR ,  6},
	/*101*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*102*/ {TYP_ASC,  FMT_LLVAR ,  19},
	/*103*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*104*/ {TYP_ASC,  FMT_LLLVAR,  9},
	/*105*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*106*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*107*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*108*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*109*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*110*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*111*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*112*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*113*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*114*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*115*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*116*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*117*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*118*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*119*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*120*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*121*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*122*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*123*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*124*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*125*/ {TYP_ASC,  FMT_LLLVAR,  999},
	/*126*/ {TYP_ASC,  FMT_LLLVAR,  6},
	/*127*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*128*/ {TYP_BIN,  FMT_FIXED ,  8}
};


/*������64��*/
static ISO8583_DEF PE_8583_64_DEF[] ={
        /*000*/ {TYP_BCD,  FMT_FIXED ,  4},
        /*001*/ {TYP_BIT,  FMT_FIXED ,  8},
        /*002*/ {TYP_BCD,  FMT_LLVAR ,  32},
        /*003*/ {TYP_BCD,  FMT_FIXED ,  6},
        /*004*/ {TYP_BCD,  FMT_FIXED ,  12},
        /*005*/ {TYP_BCD,  FMT_FIXED ,  NULL},
        /*006*/ {TYP_BCD,  FMT_FIXED ,  NULL},
        /*007*/ {TYP_BCD,  FMT_FIXED ,  10},
        /*008*/ {TYP_BCD,  FMT_FIXED ,  NULL},
        /*009*/ {TYP_BCD,  FMT_FIXED ,  NULL},
        /*010*/ {TYP_BCD,  FMT_FIXED ,  NULL},
        /*011*/ {TYP_BCD,  FMT_FIXED ,  6},
        /*012*/ {TYP_BCD,  FMT_FIXED ,  6},
        /*013*/ {TYP_BCD,  FMT_FIXED ,  8},
        /*014*/ {TYP_BCD,  FMT_FIXED ,  NULL},
        /*015*/ {TYP_BCD,  FMT_FIXED ,  4},
        /*016*/ {TYP_BCD,  FMT_FIXED ,  NULL},
        /*017*/ {TYP_BCD,  FMT_FIXED ,  NULL},
        /*018*/ {TYP_BCD,  FMT_FIXED ,  NULL},
        /*019*/ {TYP_BCD,  FMT_FIXED ,  NULL},
        /*020*/ {TYP_BCD,  FMT_FIXED ,  NULL},
        /*021*/ {TYP_BCD,  FMT_FIXED ,  NULL},
        /*022*/ {TYP_ASC,  FMT_FIXED ,  NULL},
        /*023*/ {TYP_BCD,  FMT_FIXED ,  NULL},
        /*024*/ {TYP_BCD,  FMT_FIXED ,  3},
        /*025*/ {TYP_BCD,  FMT_FIXED ,  NULL},
        /*026*/ {TYP_BCD,  FMT_FIXED ,  NULL},
        /*027*/ {TYP_BCD,  FMT_FIXED ,  NULL},
        /*028*/ {TYP_ASC,  FMT_FIXED ,  9},
        /*029*/ {TYP_BCD,  FMT_FIXED ,  NULL},
        /*030*/ {TYP_BCD,  FMT_FIXED ,  NULL},
        /*031*/ {TYP_ASC,  FMT_LLVAR ,  NULL},
        /*032*/ {TYP_BCD,  FMT_LLVAR ,  6},
        /*033*/ {TYP_BCD,  FMT_LLVAR ,  NULL},
        /*034*/ {TYP_ASC,  FMT_LLVAR ,  99},
        /*035*/ {TYP_ASC,  FMT_LLVAR ,  37},
        /*036*/ {TYP_ASC,  FMT_LLLVAR,  104},
        /*037*/ {TYP_ASC,  FMT_FIXED ,  12},
        /*038*/ {TYP_ASC,  FMT_FIXED ,  6},
        /*039*/ {TYP_ASC,  FMT_FIXED ,  2},
        /*040*/ {TYP_BCD,  FMT_FIXED ,  NULL},
        /*041*/ {TYP_ASC,  FMT_FIXED ,  8},
        /*042*/ {TYP_ASC,  FMT_FIXED ,  15},
        /*043*/ {TYP_ASC,  FMT_LLVAR ,  NULL},
        /*044*/ {TYP_ASC,  FMT_LLVAR ,  19},
        /*045*/ {TYP_ASC,  FMT_LLVAR ,  NULL},
        /*046*/ {TYP_ASC,  FMT_LLLVAR,  16},
        /*047*/ {TYP_ASC,  FMT_LLLVAR,  NULL},
        /*048*/ {TYP_ASC,  FMT_LLLVAR,  24},
        /*049*/ {TYP_ASC,  FMT_FIXED ,  NULL},
        /*050*/ {TYP_ASC,  FMT_FIXED ,  NULL},
        /*051*/ {TYP_ASC,  FMT_FIXED ,  NULL},
        /*052*/ {TYP_BIN,  FMT_FIXED ,  8},
        /*053*/ {TYP_BCD,  FMT_FIXED ,  16},
        /*054*/ {TYP_ASC,  FMT_LLLVAR,  12},
        /*055*/ {TYP_BIN,  FMT_LLLVAR,  999},
        /*056*/ {TYP_BIN,  FMT_LLLVAR,  NULL},
        /*057*/ {TYP_BCD,  FMT_FIXED ,  NULL},
        /*058*/ {TYP_BCD,  FMT_LLVAR ,  NULL},
        /*059*/ {TYP_ASC,  FMT_LLLVAR,  NULL},
        /*060*/ {TYP_ASC,  FMT_LLLVAR,  NULL},
        /*061*/ {TYP_ASC,  FMT_LLLVAR,  999},
        /*062*/ {TYP_ASC,  FMT_LLLVAR,  999},
        /*063*/ {TYP_ASC,  FMT_LLLVAR,  999},
        /*064*/ {TYP_BIN,  FMT_FIXED ,  8},
 };



static ISO8583_DEF DGBANK_DEF[]={
	/*000*/ {TYP_ASC,  FMT_FIXED ,  4}, 
	/*001*/ {TYP_BIT,  FMT_FIXED ,  8}, 
	/*002*/ {TYP_ASC,  FMT_LLVAR ,  40}, 
	/*003*/ {TYP_ASC,  FMT_FIXED ,  6}, 
	/*004*/ {TYP_ASC,  FMT_FIXED ,  12}, 
	/*005*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*006*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*007*/ {TYP_ASC,  FMT_FIXED ,  10}, 
	/*008*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*009*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*010*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*011*/ {TYP_ASC,  FMT_FIXED ,  6}, 
	/*012*/ {TYP_ASC,  FMT_FIXED ,  6}, 
	/*013*/ {TYP_ASC,  FMT_FIXED ,  4}, 
	/*014*/ {TYP_ASC,  FMT_FIXED ,  4}, 
	/*015*/ {TYP_ASC,  FMT_FIXED ,  4}, 
	/*016*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*017*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*018*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*019*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*020*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*021*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*022*/ {TYP_ASC,  FMT_FIXED ,  3}, 
	/*023*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*024*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*025*/ {TYP_ASC,  FMT_FIXED ,  2}, 
	/*026*/ {TYP_ASC,  FMT_FIXED ,  2}, 
	/*027*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*028*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*029*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*030*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*031*/ {TYP_ASC,  FMT_LLVAR ,  NULL}, 
	/*032*/ {TYP_ASC,  FMT_LLVAR ,  11}, 
	/*033*/ {TYP_ASC,  FMT_LLVAR ,  11}, 
	/*034*/ {TYP_ASC,  FMT_LLVAR ,  NULL}, 
	/*035*/ {TYP_ASC,  FMT_LLVAR ,  37}, 
	/*036*/ {TYP_ASC,  FMT_LLLVAR,  104}, 
	/*037*/ {TYP_ASC,  FMT_FIXED ,  12}, 
	/*038*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*039*/ {TYP_ASC,  FMT_FIXED ,  2}, 
	/*040*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*041*/ {TYP_ASC,  FMT_FIXED ,  8}, 
	/*042*/ {TYP_ASC,  FMT_FIXED ,  15}, 
	/*043*/ {TYP_ASC,  FMT_FIXED ,  40}, 
	/*044*/ {TYP_ASC,  FMT_LLVAR ,  19}, 
	/*045*/ {TYP_ASC,  FMT_LLVAR ,  NULL}, 
	/*046*/ {TYP_ASC,  FMT_LLLVAR,  16}, 
	/*047*/ {TYP_ASC,  FMT_LLLVAR,  NULL}, 
	/*048*/ {TYP_ASC,  FMT_LLLVAR,  512}, 
	/*049*/ {TYP_ASC,  FMT_FIXED ,  3}, 
	/*050*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*051*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*052*/ {TYP_BIN,  FMT_FIXED ,  8}, 
	/*053*/ {TYP_ASC,  FMT_FIXED ,  16}, 
	/*054*/ {TYP_ASC,  FMT_LLVAR ,  40}, 
	/*055*/ {TYP_BIN,  FMT_LLLVAR,  NULL}, 
	/*056*/ {TYP_BIN,  FMT_LLLVAR,  NULL}, 
	/*057*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*058*/ {TYP_ASC,  FMT_LLVAR ,  NULL}, 
	/*059*/ {TYP_ASC,  FMT_LLLVAR,  600}, 
	/*060*/ {TYP_ASC,  FMT_LLLVAR, 512}, 
	/*061*/ {TYP_ASC,  FMT_LLLVAR,  512}, 
	/*062*/ {TYP_ASC,  FMT_LLLVAR,  NULL}, 
	/*063*/ {TYP_ASC,  FMT_LLLVAR,  512}, 
	/*064*/ {TYP_BIN,  FMT_FIXED ,  NULL},
	/*065*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*066*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*067*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*068*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*069*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*070*/ {TYP_ASC,  FMT_FIXED ,  3},
	/*071*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*072*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*073*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*074*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*075*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*076*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*077*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*078*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*079*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*080*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*081*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*082*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*083*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*084*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*085*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*086*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*087*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*088*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*089*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*090*/ {TYP_ASC,  FMT_FIXED ,  42},
	/*091*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*092*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*093*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*094*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*095*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*096*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*097*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*098*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*099*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*100*/ {TYP_ASC,  FMT_LLVAR ,  11},
	/*101*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*102*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*103*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*104*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*105*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*106*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*107*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*108*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*109*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*110*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*111*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*112*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*113*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*114*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*115*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*116*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*117*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*118*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*119*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*120*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*121*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*122*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*123*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*124*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*125*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*126*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*127*/ {TYP_ASC,  FMT_FIXED ,  NULL},
	/*128*/ {TYP_BIN,  FMT_FIXED ,  8}
};


/*�㶫�����޴Ž���*/
static ISO8583_DEF GUANGUNIONPAY[] = {
	/*000*/ {TYP_BCD,  FMT_FIXED ,  4}, 
	/*001*/ {TYP_BIT,  FMT_FIXED ,  8}, 
	/*002*/ {TYP_BCD,  FMT_LLVAR ,  32}, 
	/*003*/ {TYP_BCD,  FMT_FIXED ,  6}, 
	/*004*/ {TYP_BCD,  FMT_FIXED ,  12}, 
	/*005*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*006*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*007*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*008*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*009*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*010*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*011*/ {TYP_BCD,  FMT_FIXED ,  6}, 
	/*012*/ {TYP_BCD,  FMT_FIXED ,  6}, 
	/*013*/ {TYP_BCD,  FMT_FIXED ,  4}, 
	/*014*/ {TYP_BCD,  FMT_FIXED ,  4}, 
	/*015*/ {TYP_BCD,  FMT_FIXED ,  4}, 
	/*016*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*017*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*018*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*019*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*020*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*021*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*022*/ {TYP_BCD,  FMT_FIXED ,  3}, 
	/*023*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*024*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*025*/ {TYP_BCD,  FMT_FIXED ,  2}, 
	/*026*/ {TYP_BCD,  FMT_FIXED ,  2}, 
	/*027*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*028*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*029*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*030*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*031*/ {TYP_ASC,  FMT_LLVAR ,  NULL}, 
	/*032*/ {TYP_BCD,  FMT_LLVAR ,  11}, 
	/*033*/ {TYP_ASC,  FMT_LLVAR ,  NULL}, 
	/*034*/ {TYP_ASC,  FMT_LLVAR ,  NULL}, 
	/*035*/ {TYP_BCD,  FMT_LLVAR ,  37}, 
	/*036*/ {TYP_BCD,  FMT_LLLVAR,  104}, 
	/*037*/ {TYP_ASC,  FMT_FIXED ,  12}, 
	/*038*/ {TYP_ASC,  FMT_FIXED ,  6}, 
	/*039*/ {TYP_ASC,  FMT_FIXED ,  2}, 
	/*040*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*041*/ {TYP_ASC,  FMT_FIXED ,  8}, 
	/*042*/ {TYP_ASC,  FMT_FIXED ,  15}, 
	/*043*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*044*/ {TYP_ASC,  FMT_LLVAR ,  NULL}, 
	/*045*/ {TYP_ASC,  FMT_LLVAR ,  NULL}, 
	/*046*/ {TYP_ASC,  FMT_LLLVAR,  NULL}, 
	/*047*/ {TYP_ASC,  FMT_LLLVAR,  NULL}, 
	/*048*/ {TYP_ASC,  FMT_LLLVAR,  512}, 
	/*049*/ {TYP_ASC,  FMT_FIXED ,  3}, 
	/*050*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*051*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*052*/ {TYP_BIN,  FMT_FIXED ,  8}, 
	/*053*/ {TYP_BCD,  FMT_FIXED ,  16}, 
	/*054*/ {TYP_ASC,  FMT_LLVAR ,  NULL}, 
	/*055*/ {TYP_BIN,  FMT_LLLVAR,  NULL}, 
	/*056*/ {TYP_BIN,  FMT_LLLVAR,  NULL}, 
	/*057*/ {TYP_ASC,  FMT_FIXED ,  NULL}, 
	/*058*/ {TYP_ASC,  FMT_LLVAR ,  NULL}, 
	/*059*/ {TYP_ASC,  FMT_LLLVAR,  600}, 
	/*060*/ {TYP_BCD,  FMT_LLLVAR,  11}, 
	/*061*/ {TYP_ASC,  FMT_LLLVAR,  29}, 
	/*062*/ {TYP_BIN,  FMT_LLLVAR,  80}, 
	/*063*/ {TYP_ASC,  FMT_LLLVAR,  512}, 
	/*064*/ {TYP_BIN,  FMT_FIXED ,  8}
};



#endif /* __iso8583_field_def_h__*/
