// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

void create()
{
	set_name("��ƿʹ��", ({ "shizhe" }));
	set("title", "�Ϻ������̴�");   
	set("long", "\n�Ϻ�������ǰ��ƿʹ�ߡ�\n");
	set("gender", "����");
	set("age", 20);

	create_family("�Ϻ�����ɽ", 2, "����");
	
	SKI->set_list2(_this, FAMILY->skills_of("�Ϻ�����ɽ"), 1	);

	set_events(
		([
			"born"		: HIY"$N���������",				
			"leave"		: HIY"$N�����ƣ��ǲ�����������ȥ�ˡ�����",

			"cmds"		: ({ "cast heal", "cast bighammer", "cast yinshen" }),
		])
	);

	setup();

	carry_object("/obj/cloth")->wear();
	carry_object("/d/nanhai/obj/budd_staff")->wield();
}
