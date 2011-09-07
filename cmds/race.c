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

指令格式 : 

    race                        现实自己的物种信息
    race zhenshen               变回原型，展现自己的真身
    race human                  取消真身变回人形
    race skill [on sb]          使用物种绝技

HELP
	);
	return 1;
}
