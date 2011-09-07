// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

#define BUFF_ID		"sanmei2"

void fire(object me)
{
	mapping buff = BUFF->find(me, BUFF_ID);
	if(!buff) me->command("cast sanmei");
}

void create()
{
	set_name("红孩儿", ({"honghai er","er"}));
	set("title", "圣婴大王");
	set("long", "\n牛魔王与罗刹女的儿子，于火焰山中修炼了一身好本领。\n");
	set("gender", "男性");
	set("age", 16);

	set("cor", 90);

	create_family("火云洞", 2, "弟子");

	SKI->set_list2(_this, FAMILY->skills_of("火云洞"), 1);

	set_events(
		([
			"born"		: CYN"一个娃娃突然蹦了出来，原来是$N！",
			"leave"		: CYN"$N撒腿跑掉了。",
			"cmds"		: (: fire :),
		])
	);

	setup();

	carry_object(__DIR__"obj/f_spear")->wield();
	carry_object(__DIR__"obj/zhanpao")->wear();

}
