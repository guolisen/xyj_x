// by shines 02/07/2010

inherit ITEM;

#include <ansi.h>

void create()
{
	set_name(HIY"花月镜"NOR, ({"huayue jing", "jing zi", "jing", "mirror"}));

	set("long", 
		"一面华美的铜镜，可以照一下看看(kan)尊容。背面提有：\n\n"
		"    譬如镜中花，又如水中月，此皆心幻化，非是实有者。\n"
		"    若诸有智者，当知人之身，四大所假合，本无男女别。\n"
		"    但因情想别，或因贪爱分，如此诸因缘，乃分男女根。\n"
		"    诸有为和合，如星翳灯幻，梦露泡电云，应作如是观。\n\n"
		"后面看似工匠的落款：庚寅 光明(Shines)。\n\n"
		);
	set("unit", "面");
	set("value", 50000);

	setup();
}

void init()
{
	add_action("do_zhao", ({"kan"}));
}

int do_zhao(string arg)
{
	object me = this_object();
	object who = this_player();
	mapping tab = ([
		"男性"	: ({ "女性", "女人", "尖利" }),
		"女性"	: ({ "男性", "男人", "浑厚" }),
	]);

	if(arg && (present(arg, who) == me)) {
		string* arr = tab[who->query("gender")];
		if(arr) {
			who->set("gender", arr[0]);
			write(HIC"你发现一个" + arr[1] + "出现在镜子里，不尽吓了一跳！\n"NOR);
			who->command("wa1");
			write(HIC"更让你吃惊的是，你的声音如此" + arr[2] + "！\n"NOR);

			if(!random(5)) {
				message_vision("$N一失手，$n掉在地上摔碎了，破镜难圆。\n", who, me);
				destruct(me);
			}
			return 1;
		}
	}
	return 0;
}
