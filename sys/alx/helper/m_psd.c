// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

void create()
{
	set_name("����ʮ��", ({ "chun sanshiniang", "chun", "sanshiniang" }));
	set("gender", "Ů��" );
	set("age", 23);
	set("long", "\n֩�뾫\n");
	set("title", "�һ�����");

	set("per", 90);
	set("str", 10);

	create_family("��˿��", 2, "����");

	SKI->set_list2(_this, FAMILY->skills_of("��˿��"), 1);

	set_events(
		([
			"born"		: HIM"��Լ��������Ǯ��أ���ͷ�������һ���������ݲ�������",
			"leave"		: HIM"$Nֻ��������˿����ͬ����һ��Ʈ�ߡ�",

			"cmds"		: ({ "cast pansi", "cast love", "cast yihun" }),
		])
	);

	setup();

	carry_object("/d/obj/cloth/nichang")->wear();
	carry_object("/d/obj/cloth/yuanxiang")->wear();
	carry_object("/d/obj/weapon/sword/qinghong")->wield();
}
