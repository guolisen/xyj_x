// by firefox 11/21/2009

inherit ITEM;
inherit "/d/sldh2/feature/util";

#include <ansi.h>

string SKILL_PROP = "book/skill";

void create()
{
	set_name("ʯƬ", ({ "shi pian" }));
	
	if(!query(SKILL_PROP)) set(SKILL_PROP, "yaofa");

	set("long", "һ��ʯƬ����������������ּ�����Լ�ɼ���һ���ǣ���"
		+ to_chinese(query(SKILL_PROP)) + "����");
	set("unit", "��");
	set("value", 10000);
	
	setup();
}


void init()
{
	add_action("do_study", "study");
	add_action("do_study", "read");
}

int do_study(string arg)
{
	object me = this_object();
	object who = this_player();

	if(arg && present(arg, who) == me) {
		string skill = query(SKILL_PROP);
		if(who->query_skill(skill, 1)) return fail_msg("��������ݶ�����˵̫ǳ�ˡ�\n");
		who->set_skill(skill, 3);
		write(HIC"��������о���ʯƬ�ϵ����֣�ͻȻ��Ȼ���ʣ��ԡ�" + to_chinese(skill) + "����������\n"NOR);
		who->command("jump");
		message_vision("$Nһʧ�֣�$n���ڵ���ˤ�÷��顣\n", who, me);
		destruct(me);
		return 1;
	}
	return 0;
}
