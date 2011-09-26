#ifndef IMUD_EFUN_H_INCLUDED
#define IMUD_EFUN_H_INCLUDED

#include <imud.h>

#define PNAME						0		//玩家名
#define PID							1		//玩家ID
#define PMUD						2		//玩家MUD
#define PSCORE						3		//玩家分数


#include "/d/xyj_x/imud/_lib/efun.c"		//todo:修正该路径以及下面路径

#ifdef iMUD_FOR_XYJ
#include "/d/xyj_x/imud/_local/xyj.c"
#endif
#ifdef iMUD_FOR_XKX
#include "/d/xyj_x/imud/_local/xkx.c"
#endif
#ifdef iMUD_FOR_FY
#include "/d/xyj_x/imud/_local/fy.c"
#endif


#endif

