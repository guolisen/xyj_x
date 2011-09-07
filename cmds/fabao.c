// by firefox 11/21/2009

inherit F_CLEAN_UP;

#include <xyj_x.h>
#include <ansi.h>


int main(object me, string arg)
{
	string id;
	string tid;

	if(!arg) {
		FABAO_D->info(me);
	} else if(arg == "zhenshen") {
		FABAO_D->zhenshen(me);
	}
	else if(arg == "human") {
		FABAO_D->human(me);
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
			FABAO_D->skill(me, target);		
	}
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : 

    fabao                        列出宝囊中的法宝
    fabao id                     取出/放入法宝
    fabao -dest id               销毁法宝

HELP
	);
	return 1;
}
