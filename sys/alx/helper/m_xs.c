// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

void create()
{
	set_name("��������", ({"baixiang zunzhe", "baixiang", "zunzhe"}));
	set("title", "��������");
	set("gender", "����" );
	set("age", 43);
	set("long", "\n��λ���������������Ĵ���ʿ��\n");

	set("str", 90);

	create_family("��ѩɽ", 2, "����");

	SKI->set_list2(_this, FAMILY->skills_of("��ѩɽ"), 1);

	set_events(
		([
			"born"		: HIW"һ������֮��$N����������",
			"leave"		: HIY"һֻ������������ץס$N�ߣ�������������Ӱ�����ˡ�",
			"init"		: HIR"$N˵��������л��ˣ�",

			"cmds"		: ({ "cast juanbi", "cast tuntian", "cast juanbi" }),
		])
	);
	setup();

	carry_object("/d/obj/armor/yinjia")->wear();
	carry_object(__DIR__"obj/iceblade2")->wield();
}
