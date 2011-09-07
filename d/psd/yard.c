// by firefox 02/21/2010

inherit ROOM;

#include "xyj_x.h"
#include <ansi.h>

#define DONKEY			"/d/qujing/wuzhuang/npc/xiaomaolu"
#define MEET_ZIXIA		"meet_zixia"

void meet_zixia(object env, object who);	//邂逅仙子

void create()
{
	set("short", "洞前");
	set("long", @LONG

幽幽空谷，雾霭重重。尽头横亘一块断龙石，后面隐约可见一个
石洞，上方石壁上三个篆字『盘丝洞』。

LONG
		);
	set("outdoors", 1);
	set("no_fixup", 1);
	set("exits", ([
		"west"		: "/d/dntg/hgs/shanya",
	]));

	set("objects", ([
		//__DIR__"guard" : 2,
	]));

	setup();
}

void init() 
{
	add_action("do_say", "say");
	
	if(userp(_player) && !_player->query("family")) {
		remove_call_out("meet_zixia");
		call_out("meet_zixia", 3, _this, _player);
	}
}

/*****************************砸人的门*****************************/

//找挨砸的倒霉蛋
object find_victim() 
{
	object* arr = ({});
	foreach(object who in all_inventory()) {
		if(userp(who) && who->query_skill("dodge") < 100) arr += ({ who });
	}
	if(sizeof(arr)) return random1(arr);
	return 0;
}

int talk_to_door(object talker, string arg)
{
	object_f outer = base_name(_this);
	object_f inner = __DIR__"gate";
	string in_exit = "exits/east";
	string out_exit = "exits/west";
	object_f next = base_name(environment(talker)) == outer ? inner : outer;

	if(arg != "芝麻开门" && arg != "芝麻关门") return 0;
	
	msv(CYN"$N说道：" + arg + "\n\n"NOR, talker);
	tell_room(next, CYN"隐约听见有人说道：" + arg + "\n\n"NOR);


	if(arg == "芝麻开门" && !query(in_exit)) {
		object victim = find_victim();
		set(in_exit, inner);
		inner->set(out_exit, outer);
		tell_room(inner, CYN"断龙石轰然倒下，洞门敞开。\n"NOR);
		tell_room(outer, CYN"断龙石轰然倒下，洞门敞开。\n"NOR);

		if(victim) {
			msv(HIR"$N躲闪不及，惨叫着被压在下面。\n"NOR, victim);
			tell_room(inner, HIR"外面传来一声凄厉的惨叫。\n"NOR);
			victim->start_busy(5);
			victim->receive_wound("kee", 50);
			COMBAT_D->report_status(victim, 1);			
		}
	}
	if(arg == "芝麻关门" && query(in_exit)) {
		delete(in_exit);
		inner->delete(out_exit);
		tell_room(inner, CYN"断龙石轰然归位，洞口又被遮得风雨不透。\n"NOR);
		tell_room(outer, CYN"断龙石轰然归位，洞口又被遮得风雨不透。\n"NOR);
	}
	return 1;
}

int do_say(string arg)
{
	return talk_to_door(this_player(), arg);
}

/*****************************邂逅紫霞*****************************/

#define	SAY			"$N对$n说道："

string* words = ({
	"$N正盯着$n看，不知道打些什么主意。",
	SAY"神仙？",
	SAY"妖怪？",
	SAY"谢谢。",
	SAY"这座山所有的东西都是属于我的，现在也包括你在内！\n",
	SAY"就象我的驴子一样，给你盖个章！\n"
	HIR"$N手一挥$n鞋底起火，$n赶忙扑灭火脱下鞋子，发现脚底出现七颗痣。",
	SAY"你是我的人了，如果有人欺负你，就报我的名字『盘丝大仙』！",
});

void saying(object zixia, object who)
{
	int step;
	if(!same_env(zixia, who) || (zixia->the_id() != "zi xia")) {
		if(who) who->delete_temp(MEET_ZIXIA);
		return;
	}
	step = who->query_temp(MEET_ZIXIA);
	if(step > 6) {
		if(!_this->query("exits/east")) zixia->command("say 芝麻开门");
		zixia->command("east");
		zixia->command("say 芝麻关门");
		return;
	}
	msv(CYN + words[step] + NOR"\n", zixia, who);
	who->add_temp(MEET_ZIXIA, 1);

	call_out("saying", 2, zixia, who);
}

void meet_zixia(object env, object who)
{
	object zixia = ACTOR_D->find("xia");
	if(zixia && who && env == environment(who))	{
		if(at_night()) call_out("meet_zixia", 3, env, who);
		else {
			msv("$N匆忙离开了。\n", zixia);
			zixia->move(env);
			msv("$N牵着小毛驴缓缓走过来。\n", zixia);

			call_out("saying", 2, zixia, who);
		}
	}
}

