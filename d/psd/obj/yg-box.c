// by firefox 02/21/2010

#include <xyj_x.h>
#include <ansi.h>

inherit ITEM;
inherit F_LOADABLE;

#define DEST		X_DIR"d/psd/yard"

void create()
{
	set_name("月光宝盒", ({"yueguang baohe", "baohe", "box"}));
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG

一只长条形的盒子，正面写着『借助月亮光华可以穿梭时空』，反面一行
梵文：『般若波罗密』。

LONG);
		set("unit", "只");
		set("value", 10);
	}

	setup();
}

void init()
{
	add_action("do_say", ({ "say", "nian" }) );	
}

int do_say(string arg)
{
	object env = environment(_player);
	object dest = load_object(DEST);
	string* arr = ({
		CYN"$N说道：哇！升仙啦！\n\n"NOR,
		CYN"$N说道：哇！又升仙啦！\n$N说道：嗯？ 我为什么要说“又” 呢？\n\n"NOR,
	});

	if(arg != "般若波罗密"
		|| !at_night()
		|| !env->query("outdoors")
		|| _player->is_busy()
	) return 0;

	msv(CYN"$N念道：般若波罗密\n\n"NOR, _player);	
	msv(HIR"一道红光从天降，$N消失在空中。\n"NOR, _player);

	foreach(object who in all_inventory(env)) {
		if(who->query("race") == "人类" && !userp(who) && living(who)) {
			msv(arr[random(3)> 0], who);			
			break;
		}
	}

	_player->move(DEST);
	_player->start_busy(2);
	
	msv(CYN"灵光闪过，$N落在地上。\n"NOR, _player);
	return 1;
}

