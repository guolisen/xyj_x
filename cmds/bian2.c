// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit F_NO_CLEAN_UP;

#define BUFF_ID		"bian2"
#define BUFF_NAME	HIG"变化"NOR
#define DMANA		30		//原法力消耗公式 = 30 + 400 / (spells - 20)

int on_timer(mapping buff);
varargs mapping get_buff(object who, int no_cost);

int main(object me, string arg)
{
	string msg;
	mapping buff_ori = BUFF->find(me, BUFF_ID);

	if(me->query_temp("d_mana") > 0 && !buff_ori) return 0;	//抛给原来的bian命令

	seteuid(getuid());
	msg = BTL->bad_state(me, ({"fighting", "ghost", "busy"}));
	if(msg) return notify_fail("你" + msg + "\n");

	if(buff_ori && (!arg || arg == "me" || arg == me->query("id"))) {
		msv(HIY"$N口念咒语，身形一晃，现了真身。\n"NOR, me);
		BUFF->remove1(buff_ori);		
	} else {
		object who = present(arg + "", environment(me));
		if(!objectp(who) || who == me) {
			return notify_fail("你想变成谁？\n");
		} else {
			mapping req = ([
				"skill"		: ([ "spells"	: 25]),
				"prop"		: ([ "mana"		: 150,	"daoxing": 16000, "max_mana" : 640]),
			]);
			if(wizardp(who) && !wizardp(me)) return notify_fail("你的法术不足以变成巫师。\n");
			if(!BTL->require(me, BUFF_NAME, req)) return 1;
			BTL->pay(me, (["mana" : 100]));

			msv(HIY"$N手捻口诀，念动真言，摇身一变，变得和$n一模一样！\n"NOR, me, who);
			if(buff_ori) BUFF->remove1(buff_ori);
			
			BUFF->add(me, get_buff(who));
		}
	}
	return 1;
}

int cmd_filter(object me, string verb, string arg)
{
	string* verbs = ({"bian", "say", "tell", "reply", "look"});
	if(me->query_temp("is_living") == 1) return 0;
	if(member_array(verb, verbs) == -1) {
		string unit = me->query_temp("unit") ? me->query_temp("unit") : "个";
		write("别忘了你现在是一" + unit + me->name() + "！\n");
		return 1;
	}
	return 0;
}

//获取目标的变化状态buff
varargs mapping get_buff(object who, int no_cost)
{
	mapping buff = BUFF->find(who, BUFF_ID);

	if(buff) {
		buff = buff + ([]);			//复制buff
	} else {
		buff = ([					//创建新的buff
			"id"		: BUFF_ID,
			"name"		: BUFF_NAME,
			"comment"	: "变身成其他的人或物。",
			"class"		: "变身术",
			"attr"		: 2,		//隐藏buff
			"temp"		: ([
				"d_mana"		: DMANA,
				"apply/id"		: who->parse_command_id_list(),
				"apply/name"	: ({ who->name() }),
				"apply/short"	: ({ who->short() }),
				"apply/long"	: ({ who->long() }),
				"no_heal_up/bian" : 1,
				"is_living"		: living(who),
				"is_character"	: who->is_character(),
				"unit"			: who->query("unit"),			
				"gender"		: who->query("gender"),
				"age"			: who->query("age"),
				"race"			: who->query("race"),
				"family"		: who->query("family"),
			]),
			"add_temp"	: ([
				"cmd_filter/*"	: ({ (: cmd_filter :) }),
			]),
			"interval"	: (no_cost ? 0 : 5),
			"timer_act"	: (: on_timer :),
			"post_act"	: function(mapping buff) {
				object me = buff["me"];
				while( environment(me)->is_character())
					me->move(environment(environment(me)));
			},
		]);
	}
	return buff;
}

int on_timer(mapping buff)
{  
	object me = buff["me"];
	if(me->query("mana") > DMANA + 50) {
		me->add("mana", -DMANA);
		return 1;
	}
	msv(HIY"只见$N面色苍白，一个恍惚之间，已经现了原形。\n"NOR, me);
	return 0;
}

int help(object me)
{
	write(@HELP

指令格式 ： bian [<人物>|<NPC>|<me>]

变身术，这个指令让你变化成其他人物的模样。是否能变，还要取决于
你的法术和法力大小。

其他相关指令： observe。
HELP
	);
	return 1;
}
