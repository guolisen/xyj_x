// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

void create()
{
	set_name("������", ({"yanluo wang","wang", "master", "yanluo"}));
	set("long", "\n��������ۣ�ͷ���ڳ����������ף��������룬�������������\n");
	set("title", "����ʮ��֮");
	set("class", "youling");
	set("gender", "����");
	set("age", 50);

	create_family("���޵ظ�", 2, "���");

	SKI->set_list2(_this, FAMILY->skills_of("���޵ظ�"), 1);

	set_events(
		([
			"born"		: HIB"һ��ڷ�����$N������������ǰ��",
			"leave"		: HIB"$N�������һ�ɺڷ磬������Ҳ���źڷ�ɢȥ������",
			"init"		: CYN"$N˵����������·�㲻�ߣ�������������Ͷ��",
			"kill"		: 0,

			"cmds"		: ({ "cast inferno", "cast gouhun" }),
		])
	);

	setup();

	carry_object("/d/obj/cloth/mangpao")->wear();
	carry_object("/d/obj/weapon/sword/qinghong")->wield();
}
