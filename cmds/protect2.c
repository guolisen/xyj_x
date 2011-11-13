// firefox 11/11/2011

#include <ansi.h>
#include <xyj_x.h>

inherit F_CLEAN_UP;

#define CD						30
#define DURATION				3		//大约2招


//判断护法有效性
int is_valid(object me, object guard)
{
	return guard->query_temp("protect") == me
		&& living(guard) && !me->is_fighting(guard);
}

//获取护法
object* gards(object me)
{
	object env = environment(me);
	object* arr = ({});
	foreach(object ob in all_inventory(env)) {
		if(is_valid(me, ob))	{
			arr += ({ob});
		}
	}
	return arr;
}


//保护某人[舍命]
int protect_sb(object me, object who, int with_life)
{
	int now = time();

	if(!with_life) {
		me->set_temp("protect", who);		
		foreach(object ob in who->query_enemy()) {
			me->kill_ob(ob);
			ob->kill_ob(me);
		}
	} else {	
		if(!cd_start(me, "protect", CD)) return notify_fail("你不能连续拼命。\n");

		who->set_temp("protector", me);
		who->set_temp("protector_until", 1 + now + DURATION * SEC_PER_HB);
		tell_object(me, "你准备舍身保护" + who->name() + "。\n");
	}
	message_vision(HIC"$N开始保护$n。\n"NOR, me, who);
	return 1;
}

//保护人代替受难
object stand_in(object me)
{
	object who = me->query_temp("protector");
	int until = me->query_temp("protector_until");

	if(until > time() && same_env(who, me) && can_move(who)) {
		message_vision("$N不过一切挡在$n身前！\n", who, me);
		who->start_busy(DURATION);
		return who;
	}
	return me;
}

int main(object me, string arg)
{
	object who;

	if(!arg) {
		who = me->query_temp("protect");
		if(who)	tell_object(me, "你现在正在保护" + who->name() + "。\n");
		else tell_object(me, "你现在没有保护任何人。\n");
	} 
	else if(arg == "none") {
		me->set_temp("protect", 0);
		return notify_ok("OK.\n");
	}
	else if(arg == "me" || arg == me->query("id"))  
		return notify_fail("你要保护什么人？\n");
	else {
		int with_life = sscanf(arg, "-l %s", arg) == 1;

		who = present(arg, environment(me));

		if(!objectp(who))
			return notify_fail("你要保护什么人？\n");

		if(!living(who))
			return notify_fail("你不能保护" + who->name() + "。\n");

		if(me->is_fighting(who))
			return notify_fail("你不能保护战斗对象。\n");

		if(!userp(who) && who->query("owner") != me->query("id"))
			return notify_fail(who->name() + "拒绝被你保护。\n");

		if(me->query_condition("no_pk_time") > 480)
			return notify_fail("你最近杀人太多。。。\n");

		if(me->query("age") < 18)
			return notify_fail("你尚未年幼。\n");

		return protect_sb(me, who, with_life);
	}
	
	return 1;

}

int help(object me)
{
   write( @HELP
指令格式: protect [-l] [<人物>|<NPC>|none]

开始保护／放弃保护某人。可选参数-l表示舍身保护目标。
HELP
   );
   return 1;
}
