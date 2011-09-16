// by firefox 11/21/2009

inherit ITEM;

#include <xyj_x.h>
#include <ansi.h>

void create()
{
	set_name("腹中",({"fu zhong"}));

	set("short","腹中");

	set("long", "

四壁隐隐透入暗红的光线，隐约看见到处沾着粘滑的液体。能听到震
耳欲聋的心跳声，还有叽里咕噜，稀里哗啦的乱响。

");

	set_max_encumbrance(3000000);

	set("no_magic", 1);
	set("no_fight", 1);
	set("alternative_die", 1);
	set("is_fabao", 1);

	set_heart_beat(23);

	seteuid(getuid());
	setup();
}

void init()
{
	add_action("do_block", ({"burn", "ji", "throw", "cast", "perform"}));
	add_action("do_exert", ({"exert"}));
	add_action("do_drop", ({"drop"}));
}

int do_block(string arg)
{
	write("空间狭小，你施展不开。\n");
	return 1;
}

int do_exert(string arg)
{
	write("到处弥漫着腥风臭气，你无法呼吸。\n");
	return 1;
}

int do_drop(string arg)
{
	//下毒
	return 0;
}

void alternative_die(object who)
{
	who->set("kee", max2(1, who->query("kee")));
	who->set("eff_kee", max2(1, who->query("eff_kee")));
	who->set("sen", max2(1, who->query("sen")));
	who->set("sen_kee", max2(1, who->query("eff_sen")));
}

int clean_up()
{
	foreach(object ob in all_inventory()) {
		if(interactive(ob)) return 1;
	}
	destruct(_this);
	return 0;
}

void heart_beat()
{
	clean_up();
}
