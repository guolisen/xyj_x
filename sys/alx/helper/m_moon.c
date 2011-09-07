// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

mapping events = ([
	"born"		: HIM"�����ʻ����裬$N���Ʈ�䡣",
	"leave"		: HIW"$N����ˮ�䣬���·�ȥ��",
	"init"		: 0,
	"kill"		: "Ҫ������Ĵ��������ˣ�",

	"cmds"		: ({ "cast arrow", "cast huimeng", "cast invocation", "perform wuxue" }),
]);


void create()
{
	set_name("�϶�", ({"chang e", "change", "chang","master"}));
	set("long",
		"����ĸ�Ĵ���ӡ�����������ɷ��ȡ����ĸ֮��ҩ��\n"
		"����ʦ�Ƴ�ˮ�𡣺�úͽⲢ������ĸ�����¹�һ�š�\n"
	);
	set("title", "�¹�����");
	set("gender", "Ů��");

	set("per", 90);
	set("str", 10);

	create_family("�¹�", 2, "����");

	SKI->set_list2(_this, FAMILY->skills_of("�¹�"), 1);

	set_events(
		([
			"born"		: HIM"�����ʻ����裬$N���Ʈ�䡣",
			"leave"		: HIW"$N����ˮ�䣬���·�ȥ��",
			"init"		: 0,
			"kill"		: "Ҫ������Ĵ��������ˣ�",

			"cmds"		: ({ "cast arrow", "cast mihun", "cast shiyue" }),
		])
	);

	setup();

	carry_object("/d/moon/obj/luoyi")->wear();
	carry_object("/d/moon/obj/feijian")->wield();
}
