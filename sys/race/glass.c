// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit ITEM;
inherit F_LIQUID;

#define NAME0		HIG"琉璃盏"NOR
#define NAME1		HIG"残破的琉璃盏"NOR
#define YUDI		"break_zhan_yudi"

void create()
{
	set_name(NAME0, ({"liuli zhan", "zhan"}));
	set_weight(70);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一只光华四射的琉璃盏。玉帝心爱之物，勿动。\n");
		set("unit", "只");
		set("value", 20);
		set("no_sell", 1);
		set("max_liquid", 15);
	}

	set("liquid", ([
		"type": "alcohol",
		"name": "仙酒",
		"remaining": 15,
		"drunk_apply": 6,
	]));
}

void debut()
{
	_this->set("name", NAME0);
	_this->move("/d/dntg/sky/lingxiao");
}

/*****************************转世相关*****************************/

void init()
{
	add_action("do_drop", ({"drop"}));
	add_action("do_say", ({"say"}));
}

int do_drop(string arg)
{
	if(_this->query("name") == NAME0 
		&& !cannot_move(_player)
		&& REI_D->precondition(_player)
		&& (arg == "liuli zhan" || arg == "zhan"))
	{
		object env = environment(_player);
		object yudi = present("yuhuang dadi", env);
		if(yudi) {
			msv(CYN"$N丢下一只$n，传来一声清脆的响声。\n"NOR, _player, _this);
			
			_this->set("name", NAME1);
			_this->move(env);
			
			yudi->command("angry " + _player->query("id"));
			msv(CYN"$N喝道：你竟敢打碎朕的琉璃盏，你可知罪？\n"NOR, yudi);

			_player->set_temp(YUDI, yudi);
		}
	}
}

int do_say(string arg)
{
	object yudi = _player->query_temp(YUDI);
	if(same_env(_player, yudi)) {
		if(arg == "不知罪" || arg == "不知") {
			msv(CYN"$N说道：" + arg + "\n"NOR, _player);
			msv(CYN"$N勃然大怒道：大胆狂徒，既然不晓天庭规矩，那就去下界重新修炼吧！\n"NOR, yudi);
			//yudi->command("chat ");
			msv("只见殿外冲进来几个护宫卫士，七手八脚地拖着$N走了出去。\n", _player);
			_player->move("/d/dntg/sky/qianyuangong");
			tell_room(environment(_player), "只见" + _player->query("name") + "被踉踉跄跄的推了出来。\n", ({_player}));
			msv("护宫卫士大喝一声：下去！$N被扔回了下界。\n",_player);
			REI_D->to_earth(_player);
			return 1;
		} else {
			yudi->command("heng");
			msv(CYN"$N这次先饶过你！\n"NOR, yudi);
		}
	}
	_player->set_temp(YUDI, 0);
	return 0;
}

