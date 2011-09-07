

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object obj, env;

	if(!arg)
		return notify_fail("你要接受谁的公开邀请？\n");

	if(arg == "none") {		
		me->set_temp("accept", 0);
		return notify_ok("OK.\n");
	}

	if(me->is_ghost())
		return notify_fail("做了鬼了，就老实点吧！\n");

	if(me->is_fighting() || me->is_busy())
		return notify_fail("你很忙，不能接受公开邀请。\n");

	obj = find_player(arg);
	if(!obj) obj = find_living(arg);    
	if(!obj) obj = LOGIN_D->find_body(arg);

	if(!obj) return notify_fail("没有这个人。\n");

	if(wizardp(obj) && !wizardp(me)) return notify_fail("没有这个人。\n");

	if(obj->query_temp("invite") != "public")
		return notify_fail(obj->query("name") + "现在并没有公开邀请别人。\n");

	if( !wizardp(me) && userp(me) )
		if (env=environment(me))
			if(!env->query("outdoors"))
				return notify_fail("你还是到外面去接受"+obj->query("name")+"的邀请吧！\n");

	if( !wizardp(me) && userp(me) ){
		if( uptime()-me->query_temp("accept_time")<10)
			return notify_fail("请稍后再接受邀请吧。\n");

		me->set_temp("accept_time",uptime());
	}

	if (me->query_temp("accept") == obj->query("id"))
		return notify_fail("你已经接受"+obj->query("name")+"的公开邀请了。\n");

	if( !wizardp(me) && userp(me) ){
		if ((obj->query("id")=="zhenyuan_daxian")   && me->query("life/live_forever") )
			return notify_fail("你已经不堕轮回了，还是把机会留给新人吧。\n");

		if ((obj->query("id")=="zhenyuan_daxian") && me->query("combat_exp") <=100000 ) 
			return notify_fail("你的本事还不够，镇元大仙不打算请你。\n");
	}
	tell_object (me,GRN"你接受"GRN+obj->query("name")+NOR GRN"的公开邀请。\n"NOR);
	tell_object (obj, me->query("name")+GRN"现在接受你的公开邀请。\n"NOR);

	me->set_temp("accept",obj->query("id"));
	return 1;
}

int help(object me)
{
write(@HELP

指令格式 : accept <某人> | none

这个指令告诉别人你接受他/她的公开邀请，或者取消放弃接受邀请。


HELP
    );
    return 1;
}

