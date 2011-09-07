// by firefox 11/21/2009

inherit ITEM;

#include <xyj_x.h>
#include <ansi.h>

void create()
{
	set_name("法宝货郎", ({"seller"}));
	set("env/invisibility", 1);

	set("long", "负责为玩家提供法宝。\n");
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
	string str = CYN"$N奋力挖起地上的浮土......，%s映入眼帘。\n"NOR;
	int i = query("has_box");

	if(cannot_move(_player)) return notify_fail("你正忙着！\n");	
	_player->start_busy(3);

	if(random(5)) {
		message_vision(CYN"$N奋力挖起地上的浮土......\n"NOR, _player);
	} else {
		object ob = new(items[i][1]);
		if(ob->move(_player)) {
			message_vision(CYN"$N挖到了" + items[i][0] + "。\n"NOR, _player);
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
	//随机选择一个法宝，设定当前法宝

	//选择一个法宝出现的位置

	//到指定位置，等待有缘人

	//有缘人来到，可能要搏斗？收服恶龙，死了得到成品还是原料？

	//死龙？龙骨鞭，龙筋？

	_this->move(random1(rooms));
}

