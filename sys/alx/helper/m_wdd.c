// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

void on_init(object me, object who)
{
	if(!random(3)) me->command("cast zhua on " + who->query("id"));
}

void create()
{
	set_name("����", ({"yu shu","yushu", "shu"}));
	set("gender", "Ů��" );
	set("age", 23);
	set("long", "\n���������޵׶��Ķ����ˡ������޵�����������������������\n");
	set("title", "��ӿ����");

	set("per", 30);
	set("str", 20);	
	
	create_family("�ݿ�ɽ�޵׶�", 1, "����");

	SKI->set_list2(_this, FAMILY->skills_of("�ݿ�ɽ�޵׶�"), 1);

	set_events(
		([
			"born"		: HIY"$NͻȻ�ӵ������˳���",
			"leave"		: HIY"$N���������һ����������䣬�������в����ˡ�",
			"init"		: (: on_init :),
	
			"cmds"		: ({ "cast huanying", "cast bianfu", "cast suliao"}),
		])
	);

	setup();

	carry_object("/d/obj/cloth/nichang")->wear();
	carry_object("/d/obj/cloth/yuanxiang")->wear();
}

