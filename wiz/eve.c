// by firefox 11/21/2009

inherit NPC;
inherit "/d/sldh2/feature/stat";
inherit "/d/sldh2/feature/buff";
inherit "/d/sldh2/feature/util";

#include <ansi.h>

#define SPELL_POT		20
#define DEFENSE_POT		20
#define BUFF_ID			"nfs"
#define STAT_ID			"sys_stat"
#define MAX_LVL			400

#define MM				"mm_anadem"
#define MM_LVL			200


//������������������buff


void create()
{
	set_name("����", ({ "eve", "robot" }));
	set("long", "\nһ��ͳ�ƻ����ˣ�����topָ����������ͳ����Ϣ��\n\n");
	set("title", HIY"ͳ�ƻ�����"NOR);
	set("gender", "Ů��");
	set("age", 18);
	set("per", 120);

	setup();
}

void init()
{
	add_action("do_reward", "reward");
}


int do_reward(string arg)
{

	foreach(object user in users()) {
		clear_buff(user);
	}
	return 1;

}

