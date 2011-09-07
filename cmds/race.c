// by firefox 11/21/2009

inherit F_CLEAN_UP;

#include <xyj_x.h>
#include <ansi.h>


int main(object me, string arg)
{
	if(!arg) {
		RACE_D->info(me);
	} else if(arg == "zhenshen") {
		RACE_D->zhenshen(me);
	}
	else if(arg == "human") {
		RACE_D->human(me);
	}
	else {
		string skill, tid;
		object target;
		
		if(sscanf(arg, "%s on %s", skill, tid) == 2) {
			target = precent(tid, environment(me));
		} else if(arg == "skill") {
			skill = "skill";
			target = me;
		}
		if(skill == "skill")
			RACE_D->skill(me, target);
	}
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : 

    race                        ��ʵ�Լ���������Ϣ
    race zhenshen               ���ԭ�ͣ�չ���Լ�������
    race human                  ȡ������������
    race skill [on sb]          ʹ�����־���

HELP
	);
	return 1;
}
