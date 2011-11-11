// by firefox 11/21/2009

inherit ITEM;

#include <xyj_x.h>
#include <ansi.h>

#define DEST		X_DIR"d/psd/yard"

void create()
{
	set_name("地上的洞", ({"hole"}));
	set("env/invisibility", 1);
	set("value", 1);
	set("no_get", 1);
	set("no_give", 1);

	set("has_box", 1);
	
	seteuid(getuid());
	setup();
}

/*****************************月光宝盒*****************************/

void init()
{
	add_action("do_dig", ({"dig", "wa"}));
}

int do_dig(string arg)
{
	string* items = ({
		({ "一条虫子",	"/d/southern/jinghe/obj/qiuyin" }),
		({ "一只盒子",	__DIR__"yg-box" }),
	});
	int i = query("has_box");

	if(!can_move(_player)) return notify_fail("你正忙着！\n");	

	_player->start_busy(1);

	if(random(3)) {
		msv(CYN"$N奋力挖起地上的浮土......\n"NOR, _player);
	}
	else if(present("yueguang baohe", _player)) {
		msv(CYN"一股强大的力量从地下传来，将$N硬生生吸了进去。\n"NOR, _player);
		_player->move(DEST);
		msv(CYN"灵光闪过，$N落在地上。\n"NOR, _player);
	} else {
		object ob = new(items[i][1]);
		if(ob->move(_player)) {
			msv(CYN"$N挖到了" + items[i][0] + "。\n"NOR, _player);
			set("has_box", 0);
		}
	}
	return 1;
}

/*****************************四处游走*****************************/

string* rooms = ({
	"/d/dntg/hgs/shifang",
	"/d/dntg/hgs/shifang",
});

void debut()
{
	set("has_box", 1);
	_this->move(random1(rooms));
}

