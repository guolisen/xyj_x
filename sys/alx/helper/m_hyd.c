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
	set_name("�캢��", ({"honghai er","er"}));
	set("title", "ʥӤ����");
	set("long", "\nţħ������ɲŮ�Ķ��ӣ��ڻ���ɽ��������һ��ñ��졣\n");
	set("gender", "����");
	set("age", 16);

	set("cor", 90);

	create_family("���ƶ�", 2, "����");

	SKI->set_list2(_this, FAMILY->skills_of("���ƶ�"), 1);

	set_events(
		([
			"born"		: CYN"һ������ͻȻ���˳�����ԭ����$N��",
			"leave"		: CYN"$N�����ܵ��ˡ�",
			"cmds"		: (: fire :),
		])
	);

	setup();

	carry_object(__DIR__"obj/f_spear")->wield();
	carry_object(__DIR__"obj/zhanpao")->wear();

}
