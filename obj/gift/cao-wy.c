// by firefox 11/21/2009

inherit ITEM;
#include <ansi.h>
#include <xyj_x.h>

#define NAME			HIY"���ǲ�"NOR
#define ID				"wangyou cao"
#define FLAG			"gift/wyc"

mapping remains = ([
	//"dismantle"	: 1,	"alchemy"	: 1,
]);

void create()
{
	set_name(NAME, ({ ID }));
	set_weight(90);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ�ÿ��Żƻ���С�ݣ����º������ʦ�к��书��Ǳ�ܱ�����\n");
		set("value", 100);
		set("drug_type", "��Ʒ");
	}
	set("is_monitored", 1);
	setup();
}

void init()
{
	add_action("do_eat", "eat");
}

int do_eat(string arg)
{
	object who = this_player();
	mapping skills = who->query_skills();
			
	if(arg != ID) return 0;
	if(who->query(FLAG)) return notify_fail("���ǲ�ֻ�ܳ�һ�Ρ�\n");
	who->add(FLAG, 1);
	
	//delete all skills
	SKI->clear_all(who);

	who->set("learned_points", who->query("potential") / 10);

	//delete menpai flag
	who->delete("spell_qiankun_on");
	who->delete("yuan-learn");

	//bonze
	if(who->query("bonze/class") == "bonze")
		who->set("name", who->query("bonze/old_name"));
	who->delete("bonze");

	//delete menpai
	who->delete("betray");
	who->delete("family");
	who->delete("class");
	who->set("title", "ʧ����");

	message_vision(HIG"$N����һ��"NAME HIG"�����еļ��䶼����ģ��������һƬ�հס�\n"NOR, who);
	who->command("fool");
	
	destruct(this_object());
	return 1;
}
