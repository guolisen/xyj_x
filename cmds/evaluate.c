// by firefox 11/21/2009

inherit F_CLEAN_UP;

#include <xyj_x.h>
#include <ansi.h>


int main(object me, string arg)
{
	string id;
	string tid;

	if(!arg) {
		FABAO->info(me);
	} else if(arg == "zhenshen") {
		FABAO->zhenshen(me);
	}
	else if(arg == "human") {
		FABAO->human(me);
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
			FABAO->skill(me, target);		
	}
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : 

    comment 某人 品行             评论某人
	
品行包括：

    礼貌	无礼：刷屏，骂人，下流骂人
    

    热心
    公正

    偏颇
	道德    morals
    友善    ys    friendly      lm    冷漠
    活跃    hy    lively        ld    唠叨
    客气    kq    manner        cl    粗鲁
    诚实    cs    honest        sh    爱撒谎
    公正    gz    justness      zs    自私
    勤劳    ql    diligent      ld    懒惰



玩家的品行将影响玩家的运气。

HELP
	);
	return 1;
}

chat 的玩家得到活跃度，
可谢某人，对方得到友善度，
可投诉某人，削减对方的。

