#ifndef IMUD_EFUN_H_INCLUDED
#define IMUD_EFUN_H_INCLUDED

#include <imud.h>

#define PNAME						0		//�����
#define PID							1		//���ID
#define PMUD						2		//���MUD
#define PSCORE						3		//��ҷ���


#include "/d/xyj_x/imud/_lib/efun.c"		//todo:������·���Լ�����·��

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

