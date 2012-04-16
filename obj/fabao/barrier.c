// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit ITEM;
inherit F_MOVE_TO;




void create()
{
	set_name("绊脚石",({"banjiao shi"}));

	set("env/invisibility", 1);
	set("no_get", 1);
	set("no_give", 1);
	set("no_drop", 1);
	
	seteuid(getuid());
	setup();
}

int success();

void init()
{
	add_action("block", ({"cast", "perform"}));
	add_action("do_go", ({"go"}));
}

int block(string arg)
{
	if(success()) return 0;
	write("你身陷奇门遁甲阵，手足无措。\n");
	return 1;
}

int do_go(string arg)
{
	object me = this_player();
	if(success()) return 0;
	message_vision(HIC"$N象只没头苍蝇般撞来撞去，可就是找不着方向。\n"NOR, me);
	return 1;
}

//比较敌我实力来判定动作能否成功
int success()
{
	object me = this_player();
	int cost = me->query("mana_factor") * 4;				//困住敌人要高昂的法力代价
	object host = query("host");
	mapping cmp_parm = ([
		"prop"		: ([ "mana" : 3, "daoxing" : 1]),
		"skill"		: ([ "spells" : 3]),
	]);
	int odds;
	if(!objectp(host) || !host->is_fighting(me) || me->is_busy()) return 1;	
	//计算成功率
	odds = BTL->cmp_parm(me, host, cmp_parm);
	if(me->query_skill_mapped("spells") == "taiyi") odds *= 2;
	if(host->query("betray/count")) odds *= 2;				//门派绝技，叛徒减半
	
	if(random(odds) >= 50) return 1;
	if(host->query("mana") < cost) return 1;
	host->add("mana", -cost);
	me->start_busy(2);
	return 0;
}
