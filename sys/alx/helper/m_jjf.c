// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

void create()
{
	set_name("����", ({ "qin qiong", "qin" }));
	set("title", "�������󽫾�");
	set("long", "���屦�Ǵ��ƹ���������������һλ�������佫��\n");
	set("gender", "����");
	set("age", 43);

	set("str", 40);
	set("cor", 30);
	set_temp("apply/armor", 500);

	create_family("������", 2, "��");

	SKI->set_list2(_this, FAMILY->skills_of("������"), 1);

	set_events(
		([
			"born"		: CYN"�����̳��У�$N������޶�����",
			"leave"		: CYN"$Nһ����ȣ�������ȥ��",
			"init"		: 0,
			"kill"		: "���鳾����������",

			"cmds"		: ({ "exert jingxin", "perform qiangjian" }),
		])
	);

	setup();

	carry_object(__DIR__"obj/y_bow")->wear();
	carry_object(__DIR__"obj/y_bag")->wear();
	carry_object(__DIR__"obj/y_boots")->wear();
	carry_object(__DIR__"obj/y_waist")->wear();
	carry_object(__DIR__"obj/y_cloth")->wear();
	carry_object(__DIR__"obj/y_armor")->wear();
	carry_object(__DIR__"obj/y_helmet")->wear();
	carry_object(__DIR__"obj/y_mace");
	carry_object(__DIR__"obj/y_spear")->wield();

}

void init()
{
	::init();
}
